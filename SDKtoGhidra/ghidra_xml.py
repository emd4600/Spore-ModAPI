from xml.etree.ElementTree import indent, Element, ElementTree
import copy
import re
import clang.cindex as cindex


SPORE_NAMESPACE = '/Spore/'
VFTABLE_FIELD_PREFIX = '_vftable'
VFTABLE_TYPE_SUFFIX = '__vftable'
VDTOR_SUFFIX = '_virtual_dtor'


def traverse_print(node, level):
    print("\t" * level + f'{node.displayname} {node.mangled_name} [{node.kind}] [{node.location}]')
    for c in node.get_children():
        traverse_print(c, level + 1)


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


def get_spore_ghidra_namespace(namespace_list):
    namespace = SPORE_NAMESPACE + '/'.join(namespace_list)
    return namespace[:-1] if namespace.endswith('/') else namespace


def generate_name(namespace_list, obj_name):
    return obj_name  # for now, Ghidra doesn't support '::' in the names, and we use the Ghidra Namespace to differentiate


def get_dependent_array_count(type_obj, template_args):
    spelling = type_obj.spelling
    assert(spelling[-1] == ']')
    size_expression:str = spelling[spelling.rindex('[')+1 : -1]
    # We are not interested in float division
    size_expression = size_expression.replace('/', '//')
    # Make a copy of the dictionary, as for some reason this adds a '__builtins__' element to it
    evaluated_count = eval(size_expression, {s: d for s, d in template_args.items() if type(d) == int})
    return evaluated_count


def extract_TYPE_value(var_decl_node, template_args):
    integer_literal = None
    for c in var_decl_node.get_children():
        if c.kind == cindex.CursorKind.INTEGER_LITERAL:
            integer_literal = next(c.get_tokens()).spelling
        elif c.kind == cindex.CursorKind.UNEXPOSED_EXPR:
            integer_literal = next(next(c.get_children()).get_tokens()).spelling
        elif c.kind == cindex.CursorKind.DECL_REF_EXPR:
            integer_literal = c.spelling
            if template_args is not None and integer_literal in template_args:
                integer_literal = template_args[integer_literal]
        
    assert(integer_literal)
    return int(integer_literal, 0) if type(integer_literal) == str else integer_literal


def get_this_type_list_for_function(structure_info, function_name):
    """Finds the first base class that contains a virtual function with that name, then returns the 'namespace list' of that class"""
    def inner(struct, name):
        is_first = True
        for vf in struct.virtual_functions_no_overrides:
            if vf.spelling == name:
                return struct.full_namespace_list, is_first
        for base in struct.bases_with_vftables:
            result, was_first = inner(base, name)
            if result is not None:
                return result, was_first and is_first
            is_first = False 
        return None, False   
            
    fullname, is_first = inner(structure_info, function_name)
    
    # Virtual functions on the first base are not offseted, so we can use the original class
    return structure_info.full_namespace_list if is_first else fullname
    

class StructureInfo:
    def __init__(self) -> None:
        self.has_vftable = False
        self.size = 0
        self.alignment = 0
        self.xml_element = None
        self.full_namespace_list = None
        self.bases_with_vftables = []
        self.bases_without_vftables = []
        self.virtual_functions_no_overrides = []
        self.virtual_function_names = set()  # used to ensure we have all overrides
        

class TemplateStructureInfo:
    def __init__(self, node) -> None:
        self.parameters = []
        self.default_values = dict()
        self.node = node


class GhidraToXmlWriter:
    def __init__(self, addresses_dict) -> None:
        self.root = Element('PROGRAM')
        self.root.set('NAME', 'Spore')
        
        processor = Element('PROCESSOR')
        processor.set('NAME', 'metapc')
        processor.set('ENDIAN', 'little')
        processor.set('ADDRESS_MODEL', '32-bit')
        self.root.append(processor)
        
        self.datatypes_root = Element('DATATYPES')
        self.root.append(self.datatypes_root)
        
        self.symbols_root = [Element('SYMBOL_TABLE'), Element('SYMBOL_TABLE')]
        # self.root.append(self.symbols_root)
        
        self.defined_data_root = [Element('DEFINED_DATA'), Element('DEFINED_DATA')]
        # self.root.append(self.defined_data_root)
        
        self.function_addresses_root = [Element('FUNCTION_ADDRESSES'), Element('FUNCTION_ADDRESSES')]
        # self.root.append(self.function_addresses_root)
        
        self.addresses_dict = addresses_dict   # fullname -> [address_disk, address_march2017]
        self.added_address_names = set()
        self.added_address_values = [set(), set()]
        self.structures = dict()  # name -> StructureInfo
        self.vftables = dict()  # name -> vftable xml element
        self.template_infos = dict()  # name -> TemplateStructureInfo
        self.structure_namespaces = dict()
        self.typedef_namespaces = dict()
        self.enum_namespaces = dict()
        self.union_namespaces = dict()
        # Special enum: it is made of the TYPE static fields on classes, as it is useful for Cast() operations
        self.objecttype_enum_values = []
        
    def write(self, path, address_set_index):
        self.root.append(self.symbols_root[address_set_index])
        self.root.append(self.defined_data_root[address_set_index])
        self.root.append(self.function_addresses_root[address_set_index])
        
        with open(path, 'wb') as output_file:
            tree = ElementTree(self.root)
            indent(tree, space='\t', level=0)
            output_file.write(bytes('<?xml version="1.0" standalone="yes"?>\n<?program_dtd version="1"?>\n', 'utf-8'))
            tree.write(output_file)
            
        self.root.remove(self.symbols_root[address_set_index])
        self.root.remove(self.defined_data_root[address_set_index])
        self.root.remove(self.function_addresses_root[address_set_index])
            
    def get_type_ghidra_namespace(self, type_obj, template_args, namespace_list):
        if type_obj.kind in [cindex.TypeKind.POINTER, cindex.TypeKind.LVALUEREFERENCE]:
            return self.get_type_ghidra_namespace(type_obj.get_pointee(), template_args, namespace_list)
        
        array_type = type_obj.get_array_element_type()
        if array_type.kind != cindex.TypeKind.INVALID:
            return self.get_type_ghidra_namespace(array_type, template_args, namespace_list)
        
        if template_args is not None and type_obj.spelling in template_args:
            return self.get_type_ghidra_namespace(template_args[type_obj.spelling], template_args, namespace_list)
        
        # if type_obj.spelling in ['int8_t', 'uint8_t', 'int16_t', 'uint16_t', 'int32_t', 'uint32_t', 'int64_t', 'uint64_t']:
        #     # return '/windows_vs12_32/stdint.h'
        #     return '/stdint.h'
        
        #print(f'{type_obj.spelling}   {type_obj.get_canonical().spelling}    {type_obj.kind}')
        
        base_name = self.get_type_spelling(type_obj, template_args, namespace_list, False)  # replace any inner template parameters

        namespace, fullname = try_namespace_list(self.structure_namespaces, base_name, namespace_list)
        if namespace is not None:
            return namespace
        
        namespace, fullname = try_namespace_list(self.typedef_namespaces, base_name, namespace_list)
        if namespace is not None:
            return namespace
        
        namespace, fullname = try_namespace_list(self.enum_namespaces, base_name, namespace_list)
        if namespace is not None:
            return namespace
        
        namespace, fullname = try_namespace_list(self.union_namespaces, base_name, namespace_list)
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
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED] and type_obj.get_canonical().kind != cindex.TypeKind.UNEXPOSED:
            return self.get_type_size(type_obj.get_canonical(), template_args, namespace_list)
        
        elif type_obj.kind == cindex.TypeKind.CONSTANTARRAY:
            element_size = self.get_type_size(type_obj.get_array_element_type(), template_args, namespace_list)
            return element_size * type_obj.get_array_size()
        
        elif type_obj.kind == cindex.TypeKind.DEPENDENTSIZEDARRAY:
            element_size = self.get_type_size(type_obj.get_array_element_type(), template_args, namespace_list)
            return element_size * get_dependent_array_count(type_obj, template_args)
        
        elif type_obj.spelling[-1] == '*' or type_obj.spelling[-1] == '&':
            return 4
        
        elif type_obj.spelling == 'void':
            return 0
        
        elif type_obj.get_size() > 0:
            return type_obj.get_size()
        
        else:
            replaced_type = template_args.get(type_obj.spelling, None) if template_args is not None else None
            if replaced_type is not None and replaced_type.get_size() > 0:
                return replaced_type.get_size()
            
            spelling = self.get_type_spelling(type_obj, template_args, namespace_list, False)
            struct, _ = try_namespace_list(self.structures, spelling, namespace_list)
            if struct is None:
                raise SyntaxError(f'Trying to get size of undefined type "{spelling}"')
            return struct.size
        
    def get_type_alignment(self, type_obj, template_args, namespace_list):
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED] and type_obj.get_canonical().kind != cindex.TypeKind.UNEXPOSED:
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
                spelling = self.get_type_spelling(type_obj, template_args, namespace_list, False)
                struct, _ = try_namespace_list(self.structures, spelling, namespace_list)
                if struct is None:
                    raise SyntaxError(f'Trying to get alignment of undefined type "{spelling}"')
                return struct.alignment   

    def get_type_spelling(self, type_obj, template_args, namespace_list, remove_namespaces = True):
        # When referencing a typedef with its full name, such as 'Graphics::ModelPredicate_t', it is considered ELABORATED
        # and the canonical is already the POINTER. So lets try to see if this is a typedef first
        typedef_namespace, typedef_fullname = try_namespace_list(self.typedef_namespaces, type_obj.spelling, namespace_list)
        if typedef_namespace is not None:
            return split_in_namespaces(type_obj.spelling)[-1] if remove_namespaces else typedef_fullname
        
        # We cannot always use .get_canonical(), as in types like 'pair<Key, T>' it removes those parameter names
        #if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED]:
        if type_obj.kind == cindex.TypeKind.ELABORATED and type_obj.get_canonical().kind != cindex.TypeKind.UNEXPOSED:
            # This ensures that the types within template parameters are canonically named (i.e with namespaces, no typedefs)
            return self.get_type_spelling(type_obj.get_canonical(), template_args, namespace_list, remove_namespaces)
            
        elif type_obj.kind in [cindex.TypeKind.POINTER, cindex.TypeKind.LVALUEREFERENCE]:
            return self.get_type_spelling(type_obj.get_pointee(), template_args, namespace_list, remove_namespaces) + " *"
        
        elif type_obj.kind == cindex.TypeKind.DEPENDENTSIZEDARRAY:
            # We don't want a name like 'items[count / 2]', we want 'items[18]'
            element_count = get_dependent_array_count(type_obj, template_args)
            element_spelling = self.get_type_spelling(type_obj.get_array_element_type(), template_args, namespace_list, remove_namespaces)
            return f'{element_spelling}[{element_count}]'
        
        elif type_obj.kind == cindex.TypeKind.CONSTANTARRAY:
            # We want typedef arrays to stay that way
            element_count = type_obj.get_array_size()
            element_spelling = self.get_type_spelling(type_obj.get_array_element_type(), template_args, namespace_list, remove_namespaces)
            return f'{element_spelling}[{element_count}]'
        
        if type_obj.kind == cindex.TypeKind.UNEXPOSED or (
            type_obj.kind == cindex.TypeKind.ELABORATED and type_obj.get_canonical().kind == cindex.TypeKind.UNEXPOSED
        ):
            # We don't use the namespaces in the name, as Ghidra doesn't support that in the XML
            spelling = split_in_namespaces(type_obj.spelling)[-1] if remove_namespaces else type_obj.spelling
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
                    # We call .get_canonical() to ensure we don't have typedefs and we have the full namespaces, which is what is done in generate_template_structures
                    spelling1 = re.sub(fr'\b({source})\b', str(dest) if type(dest) == int else self.get_type_spelling(dest.get_canonical(), None, namespace_list, True), spelling1)
                    spelling2 = re.sub(fr'\b({source})\b', str(dest) if type(dest) == int else self.get_type_spelling(dest.get_canonical(), None, namespace_list, False), spelling2)
            spelling = spelling1 + spelling2
            
        elif type_obj.kind == cindex.TypeKind.TYPEDEF:
            spelling = split_in_namespaces(type_obj.spelling)[-1] if remove_namespaces else type_obj.spelling
            
        else:
            type_obj = type_obj.get_canonical()
            spelling = split_in_namespaces(type_obj.spelling)[-1] if remove_namespaces else type_obj.spelling
                
        spelling = re.sub(fr'\b(long long)\b', 'longlong', spelling)
        spelling = re.sub(fr'\b(char16_t)\b', 'wchar16', spelling)
        
        if spelling.startswith('const'):
            spelling = spelling[len('const '):]
            
        # In Ghidra, unsigned int is uint, etc
        if spelling.startswith('unsigned '):
            spelling = spelling.replace('unsigned ', 'u', 1)
            
        spelling = spelling.replace('&', ' *')
            
        return spelling
    
    def generate_template_structures(self, type_obj, namespace_list: list, parent_template_args):
        """Generates specialized structures for all templated types contained within the given type."""
        # if type_obj.kind == cindex.TypeKind.ELABORATED:
        #     print(f'ELABORATED {type_obj.spelling}   {type_obj.get_canonical().spelling}   {type_obj.get_canonical().kind}')
        if type_obj.kind in [cindex.TypeKind.TYPEDEF, cindex.TypeKind.ELABORATED] and type_obj.get_canonical().kind != cindex.TypeKind.UNEXPOSED:
            # This ensures that the types within template parameters are canonically named (i.e with namespaces, no typedefs)
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
            last_name = self.get_type_spelling(type_obj, parent_template_args, namespace_list, True)
                
            fullname = build_full_name(template_full_name_splits[:-1], last_name)
            if fullname not in self.structures:
                self.add_structure(template_full_name_splits[:-1], last_name, template_info.node, template_args)
            
    def add_typedef(self, namespace_list, obj_name, typedef_node):    
        fullname = build_full_name(namespace_list, obj_name)
        if fullname in self.typedef_namespaces:
            raise SyntaxError(f'Typedef {fullname} is being redefined')
            
        ghidra_namespace_list = namespace_list
        # We don't apply this to the fullname, so that it can still be found in the get_type_... methods
        if str(typedef_node.location.file).endswith('d3d9.h') or str(typedef_node.location.file).endswith('d3d9types.h'):
            ghidra_namespace_list = ['Direct3D'] + ghidra_namespace_list
            
        ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list)
        self.typedef_namespaces[fullname] = ghidra_namespace
            
        underlying_type = typedef_node.underlying_typedef_type.get_canonical()
        self.generate_template_structures(underlying_type, namespace_list, None)
        
        if underlying_type.get_pointee().kind == cindex.TypeKind.FUNCTIONPROTO:
            function_pointer = underlying_type.get_pointee()
            param_names = []
            param_types = []
            for arg in function_pointer.argument_types():
                param_types.append(arg)
                param_names.append(None)
            self.add_function_def(obj_name, 
                                  function_pointer.get_result(),
                                  param_types,
                                  param_names,
                                  None,
                                  ghidra_namespace_list + [obj_name],
                                  None,
                                  None)
            datatype = obj_name + " *"
            datatype_namespace = get_spore_ghidra_namespace(ghidra_namespace_list + [obj_name])
        else:
            datatype = self.get_type_spelling(underlying_type, None, namespace_list)
            datatype_namespace = self.get_type_ghidra_namespace(underlying_type, None, namespace_list)
        
        typedef_xml = Element('TYPE_DEF')
        typedef_xml.set('NAME', obj_name)
        typedef_xml.set('NAMESPACE', ghidra_namespace)
        typedef_xml.set('DATATYPE', datatype)
        typedef_xml.set('DATATYPE_NAMESPACE', datatype_namespace)
        self.datatypes_root.append(typedef_xml)
    
    def add_structure(self, namespace_list, obj_name, structure_node, template_args=None):
        # We need to collect all the sizes and alignments first, because
        # the first offset depends on the final alignment if there are virtual tables
        fullname = build_full_name(namespace_list, obj_name)
        if fullname in self.structures:
            raise SyntaxError(f'Structure {fullname} is being redefined')
        
        ghidra_namespace_list = namespace_list
        # We don't apply this to the fullname, so that it can still be found in the get_type_... methods
        if str(structure_node.location.file).endswith('d3d9.h') or str(structure_node.location.file).endswith('d3d9types.h'):
            ghidra_namespace_list = ['Direct3D'] + ghidra_namespace_list
              
        full_namespace_list = namespace_list + [obj_name]
        full_ghidra_namespace_list = ghidra_namespace_list + [obj_name]
        struct_info = StructureInfo()
        struct_info.full_namespace_list = full_ghidra_namespace_list
        self.structures[fullname] = struct_info
        struct_alignment = 4
        fields = []
        sizes = []
        alignments = []
        virtual_functions = []
        skip_next_child = False
        unnamed_union_index = 0
        union_names = dict()
        for child in structure_node.get_children():
            if skip_next_child:
                skip_next_child = False
                continue
            if child.kind == cindex.CursorKind.FIELD_DECL:
                self.generate_template_structures(child.type, full_namespace_list, template_args)
                field_alignment = self.get_type_alignment(child.type, template_args, full_namespace_list)
                struct_alignment = max(struct_alignment, field_alignment)
                fields.append(child)
                sizes.append(self.get_type_size(child.type, template_args, full_namespace_list))
                alignments.append(field_alignment)
                
            elif child.kind == cindex.CursorKind.CXX_METHOD:
                if child.is_virtual_method():
                    struct_info.virtual_function_names.add(child.spelling)
                
                if child.is_virtual_method() and not method_is_override(child):
                    for base in struct_info.bases_with_vftables:
                            if child.spelling in base.virtual_function_names:
                                print(f'WARNING: Function {fullname}::{child.spelling} is not marked override')
                                break
                    
                    struct_info.has_vftable = True
                    struct_info.virtual_functions_no_overrides.append(child)
                    struct_info.virtual_function_names.add(child.spelling)
                    virtual_functions.append(child)
                    this_type_namespace_list = None if child.is_static_method() else full_ghidra_namespace_list 
                    self.add_function_def_from_node(full_ghidra_namespace_list, child, this_type_namespace_list, template_args)
                
                else:
                    function_fullname = build_full_name(full_namespace_list, child.spelling)
                    if function_fullname in self.addresses_dict:
                        if child.is_virtual_method():
                            this_type_namespace_list = get_this_type_list_for_function(struct_info, child.spelling)
                        elif child.is_static_method():
                            this_type_namespace_list = None
                        else:
                            this_type_namespace_list = full_ghidra_namespace_list
                            
                        self.add_function_def_from_node(full_ghidra_namespace_list, child, this_type_namespace_list, template_args)
                    
            elif child.kind == cindex.CursorKind.DESTRUCTOR:
                # In destructors we never use "override", so we just have to check
                if child.is_virtual_method() and not struct_info.bases_with_vftables:
                    struct_info.has_vftable = True
                    virtual_functions.append(child)
                    vdtor_name = f'{structure_node.spelling}{VDTOR_SUFFIX}'
                    self.add_virtual_dtor_function_def(full_ghidra_namespace_list, vdtor_name)  # ignore the ~ prefix
                
            elif child.kind == cindex.CursorKind.CXX_BASE_SPECIFIER:
                # The displayname has 'class ' at the beginning
                basename = child.displayname.split(' ')[-1]
                base_structure = self.structures.get(basename, None)
                if base_structure is None:
                    raise SyntaxError(f'Unrecognized base class {basename}')
                
                struct_alignment = max(struct_alignment, base_structure.alignment)
                if base_structure.has_vftable:
                    struct_info.has_vftable = True
                    struct_info.bases_with_vftables.append(base_structure)
                else:
                    struct_info.bases_without_vftables.append(base_structure)
                    
            elif child.kind == cindex.CursorKind.UNION_DECL and not child.displayname:
                # Unnamed unions act as fields
                # If the union field has a name, add the union with that name; otherwise, generate a name
                iterator = structure_node.get_children()
                while next(iterator) != child:
                    pass
                # Try to get the next item to see if it's a field
                next_child = next(iterator, None)
                if next_child is not None and next_child.kind == cindex.CursorKind.FIELD_DECL:
                    union_name = next_child.displayname
                    skip_next_child = True
                else:
                    union_name = f'_unnamed_{unnamed_union_index}'
                    unnamed_union_index += 1
                    
                self.add_union(full_namespace_list, union_name, child)
                
                union_names[child.type.spelling] = union_name
                fields.append(child)
                sizes.append(child.type.get_size())
                alignments.append(child.type.get_align())

            elif child.kind == cindex.CursorKind.VAR_DECL and child.spelling == 'TYPE':
                self.objecttype_enum_values.append((fullname, extract_TYPE_value(child, template_args)))
                   
        # Calculate offset of fields
        offset = 0
        structure_xml = Element('STRUCTURE')
        
        # The structure is
        #  BASE CLASSES WITH VFTABLES (or this class VFTABLE)
        #  BASE CLASSES WITHOUT VFTABLES
        #  FIELDS
        vftable_index = 0
        
        for base in struct_info.bases_with_vftables:
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
            class_namespace = get_spore_ghidra_namespace(full_ghidra_namespace_list)
            vftable_typename = f'{obj_name}{VFTABLE_TYPE_SUFFIX}'
            vftable_xml = Element('STRUCTURE')
            self.datatypes_root.append(vftable_xml)
            self.vftables[vftable_typename] = vftable_xml
            vftable_offset = 0
            vftable_size = len(virtual_functions)*4
            
            # Add offset for the virtual function table, only if there are no vftables yet
            if not struct_info.bases_with_vftables:
                vftable_element = Element('MEMBER')
                vftable_element.set('OFFSET', f'0x{offset:x}')
                vftable_element.set('DATATYPE', f'{vftable_typename} *')
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
                first_element.set('DATATYPE', f'{vftable_typename} *')
                first_element.set('DATATYPE_NAMESPACE', class_namespace)
                # We need to add the existing functions before the new ones
                assert(previous_vftable_type.endswith(f'{VFTABLE_TYPE_SUFFIX} *'))
                existing_vftable_xml = self.vftables[previous_vftable_type[:-2]]
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
                function_xml.set('DATATYPE', f'{vdtor_name}*' if is_vdtor else f'{vfunction.spelling} *')
                function_xml.set('DATATYPE_NAMESPACE', class_namespace)
                function_xml.set('NAME', '_virtual_dtor' if is_vdtor else vfunction.spelling)
                function_xml.set('SIZE', '4')
                vftable_xml.append(function_xml)
                vftable_offset += 4
                
        for base in struct_info.bases_without_vftables:
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
        
        ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list)
        self.structure_namespaces[fullname] = ghidra_namespace
                
        structure_xml.set('NAME', obj_name)
        structure_xml.set('NAMESPACE', ghidra_namespace)
        structure_xml.set('SIZE', f'0x{struct_size:x}')
                
        for field, offset, size, alignment in zip(fields, offsets, sizes, alignments):
            if field.kind == cindex.CursorKind.UNION_DECL:
                field_name = union_names[field.type.spelling]
                datatype = union_names[field.type.spelling]
                datatype_namespace = get_spore_ghidra_namespace(full_ghidra_namespace_list)
            else:
                field_name = field.spelling
                datatype = self.get_type_spelling(field.type, template_args, full_namespace_list)
                datatype_namespace = self.get_type_ghidra_namespace(field.type, template_args, full_namespace_list)
            
            field_xml = Element('MEMBER')
            field_xml.set('OFFSET', f'0x{offset:x}')
            field_xml.set('DATATYPE', datatype)
            field_xml.set('DATATYPE_NAMESPACE', datatype_namespace)
            field_xml.set('NAME', field_name)
            field_xml.set('SIZE', f'0x{size:x}')
            structure_xml.append(field_xml)
            
        # Add it at the end, as we might need to generate new structures (for template types) before
        self.datatypes_root.append(structure_xml)
        
        return struct_info
    
    def add_function_def(self, function_name, return_type, parameter_types, parameter_names, this_type_list, namespace_list, template_args, calling_convention):
        # this_type_list: None if is static function, 
        
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', function_name)
        function_xml.set('NAMESPACE', get_spore_ghidra_namespace(namespace_list))
        
        if not calling_convention and this_type_list is not None:
            calling_convention = 'thiscall'
            
        if calling_convention:
            function_xml.set('CONVENTION', calling_convention)
            
        return_type_fullname = self.get_type_spelling(return_type, template_args, namespace_list, False)
        return_is_first_parameter = False
        if return_type_fullname in self.structures:
            # When returning structs that are bigger than 8 bytes, we are actually getting a reference as first parameter and returning a pointer to it
            #TODO actually, ResourceID is returned as eax:edx, but Vector2 is not (because it has floats)
            return_is_first_parameter = self.structures[return_type_fullname].size >= 8
        
        self.generate_template_structures(return_type, namespace_list, template_args)
        return_xml = Element('RETURN_TYPE')
        if return_is_first_parameter:
            return_xml.set('DATATYPE', self.get_type_spelling(return_type, template_args, namespace_list) + " *")
            return_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(return_type, template_args, namespace_list))
            return_xml.set('SIZE', '4')
        else:
            return_xml.set('DATATYPE', self.get_type_spelling(return_type, template_args, namespace_list))
            return_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(return_type, template_args, namespace_list))
            return_xml.set('SIZE', str(self.get_type_size(return_type, template_args, namespace_list)))
        function_xml.append(return_xml)
        index = 0
        name_index = 1
        
        if this_type_list is not None:
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', f'{this_type_list[-1]} *')
            parameter_xml.set('DATATYPE_NAMESPACE', get_spore_ghidra_namespace(this_type_list[:-1]))
            parameter_xml.set('NAME', 'this')
            parameter_xml.set('SIZE', '4')
            function_xml.append(parameter_xml)
            index += 1
            
        if return_is_first_parameter:
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', self.get_type_spelling(return_type, template_args, namespace_list) + " *")
            parameter_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(return_type, template_args, namespace_list))  # the namespace list also contains the class name
            parameter_xml.set('NAME', 'auto_return_dst')
            parameter_xml.set('SIZE', '4')
            function_xml.append(parameter_xml)
            index += 1
            
        # Special case: we consider Cast() operations as if they had an ObjectTYPE argument,
        # which is the enum we build from the TYPE static variables in classes
        # This is more useful than seeing the raw integer
        if function_name == 'Cast' and this_type_list is not None and len(parameter_types) == 1 and parameter_types[0].spelling == 'uint32_t':
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', 'ObjectTYPE')
            parameter_xml.set('DATATYPE_NAMESPACE', '/Spore')
            parameter_xml.set('NAME', 'typeID')
            parameter_xml.set('SIZE', '4')
            function_xml.append(parameter_xml)
        
        else:
            for param_type, param_name in zip(parameter_types, parameter_names):
                self.generate_template_structures(param_type, namespace_list, template_args)
                parameter_xml = Element('PARAMETER')
                parameter_xml.set('ORDINAL', str(index))
                parameter_xml.set('DATATYPE', self.get_type_spelling(param_type, template_args, namespace_list))
                parameter_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(param_type, template_args, namespace_list))
                parameter_xml.set('NAME', param_name if param_name else f'param_{name_index}')
                parameter_xml.set('SIZE', str(max(self.get_type_size(param_type, template_args, namespace_list), 4)))
                function_xml.append(parameter_xml)
                index += 1
                name_index += 1
            
        self.datatypes_root.append(function_xml)
        
        # Add address if necessary
        fullname = build_full_name(namespace_list, function_name)
        if fullname in self.addresses_dict:
            self.add_function_address(fullname, function_name, get_spore_ghidra_namespace(namespace_list))
    
    def add_function_def_from_node(self, namespace_list, function_node, this_type_list, template_args=None):
        type_spelling = function_node.type.spelling
        if '__attribute__((stdcall))' in type_spelling:
            calling_convention = 'stdcall'
        elif '__attribute__((cdecl))' in type_spelling:
            calling_convention = 'cdecl'
        elif '__attribute__((thiscall))' in type_spelling:
            calling_convention = 'thiscall'
        elif '__attribute__((fastcall))' in type_spelling:
            calling_convention = 'fastcall'
        else:
            calling_convention = None
        
        param_names = []
        param_types = []
        for arg in function_node.get_arguments():
            param_names.append(arg.spelling)
            param_types.append(arg.type)
        self.add_function_def(function_node.spelling,
                              function_node.result_type,
                              param_types,
                              param_names,
                              this_type_list,
                              namespace_list,
                              template_args,
                              calling_convention)
            
    def add_virtual_dtor_function_def(self, namespace_list, function_name):
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', function_name)
        function_xml.set('NAMESPACE', get_spore_ghidra_namespace(namespace_list))
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
        parameter_xml.set('DATATYPE_NAMESPACE', get_spore_ghidra_namespace(namespace_list[:-1]))
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
        if fullname in self.enum_namespaces:
            raise SyntaxError(f'Enum {fullname} is being redefined')
        
        ghidra_namespace_list = namespace_list
        # We don't apply this to the fullname, so that it can still be found in the get_type_... methods
        if str(enum_node.location.file).endswith('d3d9.h') or str(enum_node.location.file).endswith('d3d9types.h'):
            ghidra_namespace_list = ['Direct3D'] + ghidra_namespace_list
            
        ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list)
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
            entry_xml.set('VALUE', f'0x{child.enum_value & 0xFFFFFFFF:x}')
            enum_xml.append(entry_xml)
            
    def add_union(self, namespace_list, obj_name, union_node):
        def add_union_member(name, size, datatype, datatype_namespace):
            field_xml = Element('MEMBER')
            field_xml.set('OFFSET', f'0')
            field_xml.set('DATATYPE', datatype)
            field_xml.set('DATATYPE_NAMESPACE', datatype_namespace)
            field_xml.set('NAME', name)
            field_xml.set('SIZE', str(size))
            union_xml.append(field_xml)
        
        fullname = build_full_name(namespace_list, obj_name)
        if fullname in self.union_namespaces:
            raise SyntaxError(f'Union {fullname} is being redefined')
        
        ghidra_namespace_list = namespace_list
        # We don't apply this to the fullname, so that it can still be found in the get_type_... methods
        if str(union_node.location.file).endswith('d3d9.h') or str(union_node.location.file).endswith('d3d9types.h'):
            ghidra_namespace_list = ['Direct3D'] + ghidra_namespace_list
        
        ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list)
        self.union_namespaces[fullname] = ghidra_namespace
        complete_namespace_list = namespace_list + [obj_name]
        members_ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list + [obj_name])
        
        union_xml = Element('UNION')
        union_xml.set('NAME', obj_name)
        union_xml.set('NAMESPACE', ghidra_namespace)
        union_xml.set('SIZE', f'{union_node.type.get_size():x}')
        self.datatypes_root.append(union_xml)
                
        # Inside a union there are three possible cases:
        # - Named structure, in this case the 'member' has the name of the structure
        # - Unnamed structure but named field, then the structure should have the name of the field
        # - Unnamed structure and field, we must generate a name for this
        # We don't support structures inside of structures inside of unions
        
        last_structure = None
        unnamed_index = 0
        inner_structures = dict()
        inner_structures_names = dict()
        for c in union_node.get_children():
            if last_structure is not None:
                if c.kind == cindex.CursorKind.FIELD_DECL:
                    field_name = c.displayname
                else:
                    # We had a structure followed by something else, this counts as a field
                    if last_structure.displayname:
                        # Named structure, in this case the 'member' uses the name of the structure
                        field_name = c.displayname
                    else:
                        # Unnamed structure and field, we must generate a name for this
                        field_name = f'_unnamed_{unnamed_index}'
                        unnamed_index += 1
                        
                # Add the structure, if it doesn't have a name use the field name
                structure_name = last_structure.displayname
                if not structure_name:
                    structure_name = field_name
                struct_info = self.add_structure(complete_namespace_list, structure_name, last_structure)
                inner_structures[c.type.spelling] = struct_info
                inner_structures_names[c.type.spelling] = structure_name
                        
                add_union_member(field_name, struct_info.size, structure_name, members_ghidra_namespace)
                last_structure = None
                
            elif c.kind == cindex.CursorKind.FIELD_DECL:
                # Only look at fields regularly if they are not from a struct
                struct_info = inner_structures.get(c.type.spelling, None)
                if struct_info is None:
                    self.generate_template_structures(c.type, complete_namespace_list, None)
                    add_union_member(c.displayname, 
                                    self.get_type_size(c.type, None, complete_namespace_list), 
                                    self.get_type_spelling(c.type, None, namespace_list),
                                    self.get_type_ghidra_namespace(c.type, None, complete_namespace_list))
                else:
                    add_union_member(c.displayname, struct_info.size, inner_structures_names[c.type.spelling], members_ghidra_namespace)
            
            if c.kind in [cindex.CursorKind.STRUCT_DECL, cindex.CursorKind.CLASS_DECL]:
                last_structure = c
                
    def add_symbol_address(self, fullname, namespace_list, var_type):
        address = self.addresses_dict[fullname]
        self.added_address_names.add(fullname)
        
        for i, addr in enumerate(address):
            self.added_address_values[i].add(addr)
            # <SYMBOL ADDRESS="01570b50" NAME="cStarRecord__attributes" NAMESPACE="" TYPE="global" SOURCE_TYPE="USER_DEFINED" PRIMARY="y" />
            symbol_xml = Element('SYMBOL')
            symbol_xml.set('ADDRESS', f'{addr:08x}')
            symbol_xml.set('NAME', fullname)
            symbol_xml.set('NAMESPACE', '')
            symbol_xml.set('TYPE', 'GLOBAL')
            symbol_xml.set('SOURCE_TYPE', 'IMPORTED')
            symbol_xml.set('PRIMARY', 'y')
            self.symbols_root[i].append(symbol_xml)
            
            # <DEFINED_DATA ADDRESS="01570b50" DATATYPE="Attribute[14]" DATATYPE_NAMESPACE="/Spore/Simulator" SIZE="0x348" />
            data_xml = Element('DEFINED_DATA')
            data_xml.set('ADDDRESS', f'{addr:08x}')
            data_xml.set('DATATYPE', self.get_type_spelling(var_type, None, namespace_list))
            data_xml.set('DATATYPE_NAMESPACE', self.get_type_ghidra_namespace(var_type, None, namespace_list))
            data_xml.set('SIZE', f'0x{self.get_type_size(var_type, None, namespace_list):x}')
            self.defined_data_root[i].append(data_xml) 
            
    def add_single_symbol_address(self, fullname, addr, address_set_index):
        self.added_address_values[address_set_index].add(addr)
        # <SYMBOL ADDRESS="01570b50" NAME="cStarRecord__attributes" NAMESPACE="" TYPE="global" SOURCE_TYPE="USER_DEFINED" PRIMARY="y" />
        symbol_xml = Element('SYMBOL')
        symbol_xml.set('ADDRESS', f'{addr:08x}')
        symbol_xml.set('NAME', fullname)
        symbol_xml.set('NAMESPACE', '')
        symbol_xml.set('TYPE', 'GLOBAL')
        symbol_xml.set('SOURCE_TYPE', 'IMPORTED')
        symbol_xml.set('PRIMARY', 'y')
        self.symbols_root[address_set_index].append(symbol_xml)
        
    def add_function_address(self, fullname, datatype, datatype_namespace):
        address = self.addresses_dict[fullname]
        self.added_address_names.add(fullname)
        
        for i, addr in enumerate(address):
            self.added_address_values[i].add(addr)
            function_xml = Element('FUNCTION')
            function_xml.set('ADDRESS', f'{addr:08x}')
            function_xml.set('NAME', fullname)
            function_xml.set('NAMESPACE', '')
            function_xml.set('DATATYPE', datatype)
            function_xml.set('DATATYPE_NAMESPACE', datatype_namespace)
            self.function_addresses_root[i].append(function_xml)
            
    def create_objecttype_enum(self):
        enum_xml = Element('ENUM')
        enum_xml.set('NAME', 'ObjectTYPE')
        enum_xml.set('NAMESPACE', '/Spore')
        enum_xml.set('SIZE', '4')
        self.datatypes_root.append(enum_xml)
        
        for name, value in self.objecttype_enum_values:
            entry_xml = Element('ENUM_ENTRY')
            entry_xml.set('NAME', name)
            entry_xml.set('VALUE', f'0x{value:x}')
            enum_xml.append(entry_xml)
