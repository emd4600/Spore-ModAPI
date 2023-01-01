from xml.etree.ElementTree import indent, Element, ElementTree
import copy
import re
import clang.cindex as cindex


SPORE_NAMESPACE = '/Spore/'
VFTABLE_FIELD_PREFIX = '_vftable'
VFTABLE_TYPE_SUFFIX = '__vftable'
VDTOR_SUFFIX = '_virtual_dtor'


def try_namespace_list(search_list, search_name, namespace_list):
    namespace_str = ''
    for s in namespace_list:
        result = search_list.get(namespace_str + search_name, None)
        if result is not None:
            return result, namespace_str + search_name
        namespace_str = f'{namespace_str}{s}::'
    return search_list.get(namespace_str + search_name, None), namespace_str + search_name


def build_full_name(namespace_list, var_name):
    return var_name if not namespace_list else ('::'.join(namespace_list) + '::' + var_name)


def align(value, alignment):
    return (value + alignment - 1) & ~(alignment - 1)


def split_in_namespaces(name: str):
    """Splits into a namespace list, this method is aware of template < > symbols"""
    result = []
    current = ''
    template_level = 0
    i = 0
    while i < len(name):
        if i+1 < len(name) and name[i:i+2] == '::' and template_level == 0:
            result.append(current)
            current = ''
            i += 2
            continue
        elif name[i] == '<':
            template_level += 1
        elif name[i] == '>':
            template_level -= 1
            
        current += name[i]
        i += 1
    result.append(current)
    return result


def split_in_template_params(name: str):
    i = name.index('<') + 1
    result = []
    current = ''
    template_level = 0
    while i < len(name):
        c = name[i]
        if c == '<':
            current += c
            template_level += 1
        elif c == '>' and template_level > 0:
            current += c
            template_level -= 1
        elif c == '>' and template_level == 0:
            result.append(current.strip())
            break
        elif c == ',' and template_level == 0:
            result.append(current.strip())
            current = ''
        else:
            current += c
        i += 1
    return result


def fix_type_string(type_string: str):
    if type_string.startswith('const'):
        type_string = type_string[len('const '):]
    return type_string.replace('&', '*')


def remove_name_templates(name: str):
    """Returns the given string until the first '<' character, removing any trailing template generics"""
    return name.split('<')[0]


# Careful! This method requires that the function explicitly uses "override"
def method_is_override(method_node):
    return any(child.kind == cindex.CursorKind.CXX_OVERRIDE_ATTR for child in method_node.get_children())


def get_ghidra_namespace(namespace_list):
    namespace = SPORE_NAMESPACE + '/'.join(namespace_list)
    return namespace[:-1] if namespace.endswith('/') else namespace


def generate_name(namespace_list, obj_name):
    return obj_name  # for now, Ghidra doesn't support '::' in the names, and we use the Ghidra Namespace to differentiate


class StructureInfo:
    def __init__(self) -> None:
        self.has_vftable = False
        self.size = 0
        self.alignment = 0
        self.xml_element = None
        

class TemplateStructureInfo:
    def __init__(self, node) -> None:
        self.parameters = []
        self.default_values = dict()
        self.node = node


class GhidraToXmlWriter:
    def __init__(self) -> None:
        self.root = Element('PROGRAM')
        self.root.set('NAME', 'Spore')
        
        processor = Element('PROCESSOR')
        processor.set('NAME', 'metapc')
        processor.set('ENDIAN', 'little')
        processor.set('ADDRESS_MODEL', '32-bit')
        self.root.append(processor)
        
        self.datatypes_root = Element('DATATYPES')
        self.root.append(self.datatypes_root)
        
        self.structures = dict()  # name -> StructureInfo
        self.vftables = dict()  # name -> vftable xml element
        self.template_infos = dict()  # name -> TemplateStructureInfo
        self.typedef_namespaces = dict()
        self.enum_namespaces = dict()
        
    def write(self, path):
        with open(path, 'wb') as output_file:
            tree = ElementTree(self.root)
            indent(tree, space='\t', level=0)
            output_file.write(bytes('<?xml version="1.0" standalone="yes"?>\n<?program_dtd version="1"?>\n', 'utf-8'))
            tree.write(output_file)
            
    def get_type_ghidra_namespace(self, type_obj, template_args, namespace_list):
        if type_obj.kind in [cindex.TypeKind.POINTER, cindex.TypeKind.LVALUEREFERENCE]:
            return self.get_type_ghidra_namespace(type_obj.get_pointee(), template_args, namespace_list)
        
        array_type = type_obj.get_array_element_type()
        if array_type.kind != cindex.TypeKind.INVALID:
            return self.get_type_ghidra_namespace(array_type, template_args, namespace_list)
        
        if template_args is not None and type_obj.spelling in template_args:
            type_obj = template_args[type_obj.spelling]
        
        # if type_obj.spelling in ['int8_t', 'uint8_t', 'int16_t', 'uint16_t', 'int32_t', 'uint32_t', 'int64_t', 'uint64_t']:
        #     # return '/windows_vs12_32/stdint.h'
        #     return '/stdint.h'
        
        base_name = self.get_type_spelling(type_obj, template_args, False)  # replace any inner template parameters
        #base_name = type_obj.spelling
        
        struct, fullname = try_namespace_list(self.structures, base_name, namespace_list)
        if struct is not None:
            splits = split_in_namespaces(fullname)
            namespace = SPORE_NAMESPACE + '/'.join(splits[:-1])
            return namespace[:-1] if namespace.endswith('/') else namespace
        
        namespace, fullname = try_namespace_list(self.typedef_namespaces, base_name, namespace_list)
        if namespace is not None:
            return namespace
        
        namespace, fullname = try_namespace_list(self.enum_namespaces, base_name, namespace_list)
        if namespace is not None:
            return namespace
            
        return '/'
            
    def add_template_node(self, fullname, template_node):
        template_info = TemplateStructureInfo(template_node)
        self.template_infos[fullname] = template_info
        
        for child in template_node.get_children():
            if child.kind in [cindex.CursorKind.TEMPLATE_TYPE_PARAMETER, cindex.CursorKind.TEMPLATE_NON_TYPE_PARAMETER]:
                template_info.parameters.append(child)

            elif child.kind == cindex.CursorKind.VAR_DECL and child.spelling.startswith('_DEFAULT_'):
                parameter_name = child.spelling[len('_DEFAULT_'):]
                template_info.default_values[parameter_name] = child.type
            
    def get_type_size(self, type_obj, template_args, namespace_list):
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED]:
            return self.get_type_size(type_obj.get_canonical(), template_args, namespace_list)
        
        elif type_obj.kind == cindex.TypeKind.DEPENDENTSIZEDARRAY:
            element_size = self.get_type_size(type_obj.get_array_element_type(), template_args, namespace_list)
            spelling = type_obj.spelling
            assert(spelling[-1] == ']')
            size_expression:str = spelling[spelling.rindex('[')+1 : -1]
            # We are not interested in float division
            size_expression = size_expression.replace('/', '//')
            # Make a copy of the dictionary, as for some reason this adds a '__builtins__' element to it
            evaluated_count = eval(size_expression, {s: d for s, d in template_args.items() if type(d) == int})
            return element_size * evaluated_count
        
        elif type_obj.spelling[-1] == '*' or type_obj.spelling[-1] == '&':
            return 4
        
        elif type_obj.spelling == 'void':
            return 0
        
        # cindex.TypeKind.CONSTANTARRAY is in this case, it returns the corret size
        elif type_obj.get_size() > 0:
            return type_obj.get_size()
        
        else:
            replaced_type = template_args.get(type_obj.spelling, None) if template_args is not None else None
            if replaced_type is not None and replaced_type.get_size() > 0:
                return replaced_type.get_size()
            
            spelling = self.get_type_spelling(type_obj, template_args, False)
            struct, _ = try_namespace_list(self.structures, spelling, namespace_list)
            if struct is None:
                raise SyntaxError(f'Trying to get size of undefined type "{spelling}"')
            return struct.size
        
    def get_type_alignment(self, type_obj, template_args, namespace_list):
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED]:
            return self.get_type_alignment(type_obj.get_canonical(), template_args, namespace_list)
        elif type_obj.kind in [cindex.TypeKind.CONSTANTARRAY, cindex.TypeKind.DEPENDENTSIZEDARRAY]:
            return self.get_type_alignment(type_obj.get_array_element_type(), template_args, namespace_list)
        elif type_obj.spelling[-1] == '*' or type_obj.spelling[-1] == '&':
            return 4
        elif type_obj.get_align() > 0:
            return type_obj.get_align()
        else:
            replaced_type = template_args.get(type_obj.spelling, None) if template_args is not None else None
            if replaced_type is not None:
                return replaced_type.get_align()
            else:
                spelling = self.get_type_spelling(type_obj, template_args, False)
                struct, _ = try_namespace_list(self.structures, spelling, namespace_list)
                if struct is None:
                    raise SyntaxError(f'Trying to get alignment of undefined type "{spelling}"')
                return struct.alignment   

    def get_type_spelling(self, type_obj, template_args, remove_namespaces = True):
        # We don't use the namespaces in the name, as Ghidra doesn't support that in the XML
        spelling:str = split_in_namespaces(type_obj.spelling)[-1] if remove_namespaces else type_obj.spelling
        # We don't to remove namespaces inside < > template parameters, but we do on the rest on the name, so we separate it
        if '<' not in spelling:
            spelling1 = spelling
            spelling2 = ''
        else:
            index = spelling.index('<')
            spelling1 = spelling[:index]
            spelling2 = spelling[index:]
        if template_args is not None:
            for source, dest in template_args.items():
                spelling1 = re.sub(fr'\b({source})\b', str(dest) if type(dest) == int else self.get_type_spelling(dest, None, True), spelling1)
                spelling2 = re.sub(fr'\b({source})\b', str(dest) if type(dest) == int else self.get_type_spelling(dest, None, False), spelling2)
                
        spelling = spelling1 + spelling2
        spelling = re.sub(fr'\b(long long)\b', 'longlong', spelling)
        spelling = re.sub(fr'\b(char16_t)\b', 'wchar16', spelling)
        # In Ghidra, unsigned int is uint, etc
        if spelling.startswith('unsigned '):
            spelling = spelling.replace('unsigned ', 'u', 1)
            
        if spelling.startswith('const'):
            spelling = spelling[len('const '):]
        spelling = spelling.replace('&', '*')
            
        return spelling
    
    def generate_template_structures(self, type_obj, namespace_list: list, parent_template_args):
        """Generates specialized structures for all templated types contained within the given type."""
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED]:
            self.generate_template_structures(type_obj.get_canonical(), namespace_list, parent_template_args)
            
        elif type_obj.kind in [cindex.TypeKind.POINTER, cindex.TypeKind.LVALUEREFERENCE]:
            self.generate_template_structures(type_obj.get_pointee(), namespace_list, parent_template_args)
            
        elif type_obj.get_array_element_type().kind != cindex.TypeKind.INVALID:
            self.generate_template_structures(type_obj.get_array_element_type(), namespace_list, parent_template_args)
            
        elif type_obj.get_num_template_arguments() > 0 and type_obj.spelling not in self.structures:
            for i in range(type_obj.get_num_template_arguments()):
                self.generate_template_structures(type_obj.get_template_argument_type(i), namespace_list, parent_template_args)
                
            untemplated_name = remove_name_templates(fix_type_string(type_obj.spelling))
            template_info, template_full_name = try_namespace_list(self.template_infos, untemplated_name, namespace_list)        
            
            if template_info is None:
                raise SyntaxError(f'Unable to get template structure {untemplated_name} from type {type_obj.spelling}')
            
            template_args = dict()
            template_param_strings = split_in_template_params(type_obj.spelling)  # we only use this for integers
            for i, param_cursor in enumerate(template_info.parameters):
                param = param_cursor.spelling
                if i < type_obj.get_num_template_arguments():
                    if param_cursor.kind == cindex.CursorKind.TEMPLATE_TYPE_PARAMETER:
                        arg_type = type_obj.get_template_argument_type(i)
                        if parent_template_args is not None and arg_type.spelling in parent_template_args:
                            arg_type = parent_template_args[arg_type.spelling]
                        template_args[param] = arg_type
                    else:
                        # The numeric value might be an expression
                        template_args[param] = eval(template_param_strings[i], parent_template_args)
                elif param in template_info.default_values:
                    template_args[param] = template_info.default_values[param]
                else:
                    raise SyntaxError(f'No value specified for template parameter {param} in specialized type {type_obj.spelling}')
                    
                
            # template_full_name_splits = split_in_namespaces(template_full_name)
            # last_name = split_in_namespaces(type_obj.spelling)[-1]
            # # Replace parent template args
            # if parent_template_args is not None:
            #     for source, dest in parent_template_args.items():
            #         last_name = re.sub(fr'\b({source})\b', dest.spelling, last_name)
            
            template_full_name_splits = split_in_namespaces(template_full_name)
            last_name = self.get_type_spelling(type_obj, parent_template_args, True)
                
            fullname = build_full_name(template_full_name_splits[:-1], last_name)
            if fullname not in self.structures:
                self.add_structure(template_full_name_splits[:-1], last_name, template_info.node, template_args)
            
    def add_typedef(self, namespace_list, obj_name, typedef_node):
        underlying_type = typedef_node.underlying_typedef_type.get_canonical()
        #print(f'{underlying_type.spelling}  {underlying_type.get_canonical().spelling}')
        self.generate_template_structures(underlying_type, namespace_list, None)
        
        fullname = build_full_name(namespace_list, obj_name)
        ghidra_namespace = get_ghidra_namespace(namespace_list)
        if fullname in self.typedef_namespaces:
            raise SyntaxError(f'Typedef {fullname} is being redefined')
        self.typedef_namespaces[fullname] = ghidra_namespace
        
        typedef_xml = Element('TYPE_DEF')
        typedef_xml.set('NAME', obj_name)
        typedef_xml.set('NAMESPACE', ghidra_namespace)
        typedef_xml.set('DATATYPE', self.get_type_spelling(underlying_type, None))
        typedef_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(underlying_type, None, namespace_list))
        self.datatypes_root.append(typedef_xml)
    
    def add_structure(self, namespace_list, obj_name, structure_node, template_args=None):
        # We need to collect all the sizes and alignments first, because
        # the first offset depends on the final alignment if there are virtual tables
        fullname = build_full_name(namespace_list, obj_name)
        if fullname in self.structures:
            raise SyntaxError(f'Structure {fullname} is being redefined')
        functions_namespace_list = namespace_list + [obj_name]
        struct_info = StructureInfo()
        self.structures[fullname] = struct_info
        struct_alignment = 4
        fields = []
        sizes = []
        alignments = []
        bases_with_vftables = []
        bases_without_vftables = []
        virtual_functions = []
        for child in structure_node.get_children():
            if child.kind == cindex.CursorKind.FIELD_DECL:
                self.generate_template_structures(child.type, functions_namespace_list, template_args)
                field_alignment = self.get_type_alignment(child.type, template_args, functions_namespace_list)
                struct_alignment = max(struct_alignment, field_alignment)
                fields.append(child)
                sizes.append(self.get_type_size(child.type, template_args, functions_namespace_list))
                alignments.append(field_alignment)
                
            elif child.kind == cindex.CursorKind.CXX_METHOD:
                if child.is_virtual_method() and not method_is_override(child):
                    struct_info.has_vftable = True
                    virtual_functions.append(child)
                    self.add_function_def(functions_namespace_list, child, template_args)
                    
            elif child.kind == cindex.CursorKind.DESTRUCTOR:
                # In destructors we never use "override", so we just have to check
                if not bases_with_vftables:
                    struct_info.has_vftable = True
                    virtual_functions.append(child)
                    vdtor_name = f'{structure_node.spelling}{VDTOR_SUFFIX}'
                    self.add_virtual_dtor_function_def(functions_namespace_list, vdtor_name)  # ignore the ~ prefix
                
            elif child.kind == cindex.CursorKind.CXX_BASE_SPECIFIER:
                # The displayname has 'class ' at the beginning
                basename = child.displayname.split(' ')[-1]
                base_structure = self.structures.get(basename, None)
                if base_structure is None:
                    raise SyntaxError(f'Unrecognized base class {basename}')
                
                struct_alignment = max(struct_alignment, base_structure.alignment)
                if base_structure.has_vftable:
                    bases_with_vftables.append(base_structure)
                else:
                    bases_without_vftables.append(base_structure)
                   
        # Calculate offset of fields
        offset = 0
        structure_xml = Element('STRUCTURE')
        
        # The structure is
        #  BASE CLASSES WITH VFTABLES (or this class VFTABLE)
        #  BASE CLASSES WITHOUT VFTABLES
        #  FIELDS
        vftable_index = 0
        
        for base in bases_with_vftables:
            offset = align(offset, base.alignment)
            for child_xml in base.xml_element:
                copy_xml = copy.deepcopy(child_xml)
                structure_xml.append(copy_xml)
                copy_xml.set('OFFSET', f'0x{offset + int(copy_xml.get("OFFSET"), 0):x}')
                if copy_xml.get('NAME').startswith(VFTABLE_FIELD_PREFIX):
                    copy_xml.set('NAME', f'{VFTABLE_FIELD_PREFIX}{vftable_index}')
                    vftable_index += 1
            offset += base.size
                    
        if virtual_functions:
            # Create a structure for the virtual function table
            class_namespace = get_ghidra_namespace(namespace_list + [obj_name])
            vftable_typename = f'{obj_name}{VFTABLE_TYPE_SUFFIX}'
            vftable_xml = Element('STRUCTURE')
            self.datatypes_root.append(vftable_xml)
            self.vftables[vftable_typename] = vftable_xml
            vftable_offset = 0
            vftable_size = len(virtual_functions)*4
            
            # Add offset for the virtual function table, only if there are no vftables yet
            if not bases_with_vftables:
                vftable_element = Element('MEMBER')
                vftable_element.set('OFFSET', f'0x{offset:x}')
                vftable_element.set('DATATYPE', f'{vftable_typename}*')
                vftable_element.set('DATATYPE_NAMESPACE', class_namespace)
                vftable_element.set('NAME', f'{VFTABLE_FIELD_PREFIX}{vftable_index}')
                vftable_index += 1
                vftable_element.set('SIZE', '4')
                structure_xml.append(vftable_element)
                offset += 4
            else:
                # We already have base classes with vftable, but we have new methods: we need to replace the first vftable
                first_element = structure_xml[0]
                previous_vftable_type = first_element.get('DATATYPE')
                first_element.set('DATATYPE', f'{vftable_typename}*')
                first_element.set('DATATYPE_NAMESPACE', class_namespace)
                # We need to add the existing functions before the new ones
                assert(previous_vftable_type.endswith(f'{VFTABLE_TYPE_SUFFIX}*'))
                existing_vftable_xml = self.vftables[previous_vftable_type[:-1]]
                vftable_size += len(existing_vftable_xml) * 4
                for child in existing_vftable_xml:
                    vftable_xml.append(child)
                    vftable_offset += 4
                    
            vftable_xml.set('NAME', vftable_typename)
            vftable_xml.set('NAMESPACE', class_namespace)
            vftable_xml.set('SIZE', f'0x{vftable_size:x}')
            
            for vfunction in virtual_functions:
                is_vdtor = vfunction.kind == cindex.CursorKind.DESTRUCTOR
                function_xml = Element('MEMBER')
                function_xml.set('OFFSET', f'0x{vftable_offset:x}')
                function_xml.set('DATATYPE', f'{vdtor_name}*' if is_vdtor else f'{vfunction.spelling}*')
                function_xml.set('DATATYPE_NAMESPACE', class_namespace)
                function_xml.set('NAME', '_virtual_dtor' if is_vdtor else vfunction.spelling)
                function_xml.set('SIZE', '4')
                vftable_xml.append(function_xml)
                vftable_offset += 4
                
        for base in bases_without_vftables:
            offset = align(offset, base.alignment)
            for child_xml in base.xml_element:
                copy_xml = copy.deepcopy(child_xml)
                copy_xml.set('OFFSET', str(offset + int(copy_xml.get('OFFSET'), 0)))
                structure_xml.append(copy_xml)
            offset += base.size
                
        for base in bases_without_vftables:
            offset = align(offset, base.alignment)
            for child_xml in base.xml_element:
                copy_xml = copy.deepcopy(child_xml)
                copy_xml.set('OFFSET', str(offset + int(copy_xml.get('OFFSET'), 0)))
                structure_xml.append(copy_xml)
            offset += base.size
         
        offsets = []
        for field, size, alignment in zip(fields, sizes, alignments):
            # Ensure field is aligned
            offset = align(offset, alignment)
            offsets.append(offset)
            offset += size
            
        struct_size = offset if not offsets else align(offsets[-1] + sizes[-1], struct_alignment)
        struct_size = max(1, struct_size)
                
        struct_info.xml_element = structure_xml
        struct_info.size = struct_size
        struct_info.alignment = struct_alignment
                
        structure_xml.set('NAME', obj_name)
        structure_xml.set('NAMESPACE', get_ghidra_namespace(namespace_list))
        structure_xml.set('SIZE', f'0x{struct_size:x}')
                
        for field, offset, size, alignment in zip(fields, offsets, sizes, alignments):
            field_xml = Element('MEMBER')
            field_xml.set('OFFSET', f'0x{offset:x}')
            field_xml.set('DATATYPE', self.get_type_spelling(field.type, template_args))
            field_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(field.type, template_args, namespace_list))
            field_xml.set('NAME', field.spelling)
            field_xml.set('SIZE', str(size))
            structure_xml.append(field_xml)
            
        # Add it at the end, as we might need to generate new structures (for template types) before
        self.datatypes_root.append(structure_xml)
            
    def add_vftable(self):
        pass
    
    def add_function_def(self, namespace_list, function_node, template_args=None):
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', function_node.spelling)
        function_xml.set('NAMESPACE', get_ghidra_namespace(namespace_list))
        
        self.generate_template_structures(function_node.result_type, namespace_list, template_args)
        return_xml = Element('RETURN_TYPE')
        return_xml.set('DATATYPE', self.get_type_spelling(function_node.result_type, template_args))
        return_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(function_node.result_type, template_args, namespace_list))
        return_xml.set('SIZE', str(self.get_type_size(function_node.result_type, template_args, namespace_list)))
        function_xml.append(return_xml)
        index = 0
        name_index = 1
        
        if not function_node.is_static_method():
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', f'{namespace_list[-1]}*')
            parameter_xml.set('DATATYPE_NAMESPACE', get_ghidra_namespace(namespace_list[:-1]))  # the namespace list also contains the class name
            parameter_xml.set('NAME', 'this')
            parameter_xml.set('SIZE', '4')
            function_xml.append(parameter_xml)
            index += 1
        
        for arg in function_node.get_arguments():
            self.generate_template_structures(arg.type, namespace_list, template_args)
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', fix_type_string(self.get_type_spelling(arg.type, template_args)))
            parameter_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(arg.type, template_args, namespace_list))
            parameter_xml.set('NAME', arg.spelling if arg.spelling else f'param_{name_index}')
            parameter_xml.set('SIZE', str(max(self.get_type_size(arg.type, template_args, namespace_list), 4)))
            function_xml.append(parameter_xml)
            index += 1
            name_index += 1
            
        self.datatypes_root.append(function_xml)
            
    def add_virtual_dtor_function_def(self, namespace_list, function_name):
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', function_name)
        function_xml.set('NAMESPACE', get_ghidra_namespace(namespace_list))
        self.datatypes_root.append(function_xml)
        
        return_xml = Element('RETURN_TYPE')
        return_xml.set('DATATYPE', 'void')
        return_xml.set('DATATYPE_NAMESPACE', '/')
        return_xml.set('SIZE', '0')
        function_xml.append(return_xml)
        
        parameter_xml = Element('PARAMETER')
        parameter_xml.set('ORDINAL', '0')
        # the namespace list also contains the class name
        parameter_xml.set('DATATYPE', f'{namespace_list[-1]}*')
        parameter_xml.set('DATATYPE_NAMESPACE', get_ghidra_namespace(namespace_list[:-1]))
        parameter_xml.set('NAME', 'this')
        parameter_xml.set('SIZE', '4')
        function_xml.append(parameter_xml)
        
        parameter_xml = Element('PARAMETER')
        parameter_xml.set('ORDINAL', '1')
        parameter_xml.set('DATATYPE', 'int')
        parameter_xml.set('DATATYPE_NAMESPACE', '/')
        parameter_xml.set('NAME', 'param_2')
        parameter_xml.set('SIZE', '4')
        function_xml.append(parameter_xml)
            
    def add_enum(self, namespace_list, obj_name, enum_node):
        fullname = build_full_name(namespace_list, obj_name)
        ghidra_namespace = get_ghidra_namespace(namespace_list)
        if fullname in self.enum_namespaces:
            raise SyntaxError(f'Enum {fullname} is being redefined')
        self.enum_namespaces[fullname] = ghidra_namespace
        
        enum_xml = Element('ENUM')
        enum_xml.set('NAME', obj_name)
        enum_xml.set('NAMESPACE', ghidra_namespace)
        enum_xml.set('SIZE', f'{enum_node.type.get_size():x}')
        self.datatypes_root.append(enum_xml)
        
        for child in enum_node.get_children():
            assert(child.kind == cindex.CursorKind.ENUM_CONSTANT_DECL)
            entry_xml = Element('ENUM_ENTRY')
            entry_xml.set('NAME', child.spelling)
            entry_xml.set('VALUE', f'0x{child.enum_value:x}')
            enum_xml.append(entry_xml)
        