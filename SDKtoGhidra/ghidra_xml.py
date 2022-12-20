from xml.etree.ElementTree import indent, Element, SubElement, ElementTree
import copy
import re
import clang.cindex as cindex


SPORE_NAMESPACE = '/Spore/'
VFTABLE_FIELD_PREFIX = '_vftable'
VFTABLE_TYPE_SUFFIX = '__vftable'
VDTOR_SUFFIX = '_virtual_dtor'


def align(value, alignment):
    return (value + alignment - 1) & ~(alignment - 1)


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


def get_ghidra_namespace(fullname, include_last_name=False):
    splits = fullname.split('::')
    namespace = SPORE_NAMESPACE + '/'.join(splits if include_last_name else splits[:-1])
    return namespace[:-1] if namespace.endswith('/') else namespace


def get_type_ghidra_namespace(type_obj):
    return '/'  #TODO


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
        
    def write(self, path):
        with open(path, 'wb') as output_file:
            tree = ElementTree(self.root)
            indent(tree, space='\t', level=0)
            output_file.write(bytes('<?xml version="1.0" standalone="yes"?>\n<?program_dtd version="1"?>\n', 'utf-8'))
            tree.write(output_file)
            
    def add_template_node(self, fullname, template_node):
        template_info = TemplateStructureInfo(template_node)
        self.template_infos[fullname] = template_info
        
        for child in template_node.get_children():
            if child.kind == cindex.CursorKind.TEMPLATE_TYPE_PARAMETER:
                template_info.parameters.append(child.spelling)
                
        for child in template_node.get_children():
            if child.kind == cindex.CursorKind.VAR_DECL and child.spelling.startswith('_DEFAULT_'):
                parameter_name = child.spelling[len('_DEFAULT_'):]
                template_info.default_values[parameter_name] = child.type
            
    def get_type_size(self, type_obj, template_args):
        if type_obj.spelling[-1] == '*' or type_obj.spelling[-1] == '&':
            return 4
        elif type_obj.spelling == 'void':
            return 0
        elif type_obj.get_size() > 0:
            return type_obj.get_size()
        else:
            replaced_type = template_args.get(type_obj.spelling, None) if template_args is not None else None
            if replaced_type is not None and replaced_type.get_size() > 0:
                return replaced_type.get_size()
            
            spelling = self.get_type_spelling(type_obj, template_args)
            struct = self.structures.get(spelling, None)
            if struct is None:
                raise SyntaxError(f'Trying to get size of undefined type "{spelling}"')
            return struct.size
        
    def get_type_alignment(self, type_obj, template_args):
        if type_obj.spelling[-1] == '*' or type_obj.spelling[-1] == '&':
            return 4
        elif type_obj.get_align() > 0:
            return type_obj.get_align()
        else:
            replaced_type = template_args.get(type_obj.spelling, None) if template_args is not None else None
            if replaced_type is not None:
                return replaced_type.get_align()
            else:
                spelling = self.get_type_spelling(type_obj, template_args)
                struct = self.structures.get(spelling, None)
                if struct is None:
                    raise SyntaxError(f'Trying to get alignment of undefined type "{spelling}"')
                return struct.alignment   

    def get_type_spelling(self, type_obj, template_args):
        if template_args is None:
            return type_obj.spelling
        
        spelling = type_obj.spelling
        for source, dest in template_args.items():
            spelling = re.sub(fr'\b({source})\b', dest.spelling, spelling)
        return spelling
    
    def generate_template_structures(self, type_obj):
        """Generates specialized structures for all templated types contained within the given type."""
        if type_obj.spelling not in self.structures:
            if type_obj.kind in [cindex.TypeKind.POINTER, cindex.TypeKind.LVALUEREFERENCE]:
                self.generate_template_structures(type_obj.get_pointee())
            elif type_obj.get_num_template_arguments() > 0:
                for i in range(type_obj.get_num_template_arguments()):
                    self.generate_template_structures(type_obj.get_template_argument_type(i))
                    
                untemplated_name = remove_name_templates(type_obj.spelling)
                template_info = self.template_infos.get(untemplated_name, None)
                if template_info is None:
                    raise SyntaxError(f'Unable to get template structure {untemplated_name} from type {type_obj.spelling}')
                
                template_args = dict()
                for i, param in enumerate(template_info.parameters):
                    if i < type_obj.get_num_template_arguments():
                        template_args[param] = type_obj.get_template_argument_type(i)
                    elif param in template_info.default_values:
                        template_args[param] = template_info.default_values[param]
                    else:
                        raise SyntaxError(f'No value specified for template parameter {param} in specialized type {type_obj.spelling}')
                        
                self.add_structure(type_obj.spelling, template_info.node, template_args)
                
    
    def add_structure(self, fullname, structure_node, template_args=None):
        # We need to collect all the sizes and alignments first, because
        # the first offset depends on the final alignment if there are virtual tables
        if fullname in self.structures:
            raise SyntaxError(f'Structure {fullname} is being redefined')
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
                self.generate_template_structures(child.type)
                field_alignment = self.get_type_alignment(child.type, template_args)
                struct_alignment = max(struct_alignment, field_alignment)
                fields.append(child)
                sizes.append(self.get_type_size(child.type, template_args))
                alignments.append(field_alignment)
                
            elif child.kind == cindex.CursorKind.CXX_METHOD:
                if child.is_virtual_method() and not method_is_override(child):
                    struct_info.has_vftable = True
                    virtual_functions.append(child)
                    self.add_function_def(f'{fullname}::{child.spelling}', child, fullname, template_args)
                    
            elif child.kind == cindex.CursorKind.DESTRUCTOR:
                # In destructors we never use "override", so we just have to check
                if not bases_with_vftables:
                    struct_info.has_vftable = True
                    virtual_functions.append(child)
                    vdtor_name = f'{fullname}::{structure_node.spelling}{VDTOR_SUFFIX}'
                    self.add_virtual_dtor_function_def(vdtor_name, fullname)  # ignore the ~ prefix
                
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
            class_namespace = get_ghidra_namespace(fullname, True)
            vftable_typename = f'{fullname}{VFTABLE_TYPE_SUFFIX}'
            vftable_xml = Element('STRUCTURE')
            vftable_xml.set('NAME', vftable_typename)
            vftable_xml.set('NAMESPACE', class_namespace)
            vftable_xml.set('SIZE', f'0x{len(virtual_functions)*4:x}')
            self.datatypes_root.append(vftable_xml)
            self.vftables[vftable_typename] = vftable_xml
            vftable_offset = 0
            
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
                for child in existing_vftable_xml:
                    vftable_xml.append(child)
                    vftable_offset += 4
            
            for vfunction in virtual_functions:
                is_vdtor = vfunction.kind == cindex.CursorKind.DESTRUCTOR
                function_xml = Element('MEMBER')
                function_xml.set('OFFSET', f'0x{vftable_offset:x}')
                function_xml.set('DATATYPE', f'{vdtor_name}*' if is_vdtor else f'{fullname}::{vfunction.spelling}*')
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
                
        structure_xml.set('NAME', fullname)
        structure_xml.set('NAMESPACE', get_ghidra_namespace(fullname))
        structure_xml.set('SIZE', f'0x{struct_size:x}')
                
        for field, offset, size, alignment in zip(fields, offsets, sizes, alignments):
            field_xml = Element('MEMBER')
            field_xml.set('OFFSET', f'0x{offset:x}')
            field_xml.set('DATATYPE', self.get_type_spelling(field.type, template_args))
            field_xml.set('DATATYPE_NAMESPACE', get_type_ghidra_namespace(field.type))
            field_xml.set('NAME', field.spelling)
            field_xml.set('SIZE', str(size))
            structure_xml.append(field_xml)
            
        # Add it at the end, as we might need to generate new structures (for template types) before
        self.datatypes_root.append(structure_xml)
            
    def add_vftable(self):
        pass
    
    def add_function_def(self, fullname, function_node, struct_name, template_args=None):
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', fullname)
        function_xml.set('NAMESPACE', get_ghidra_namespace(fullname))
        self.datatypes_root.append(function_xml)
        
        self.generate_template_structures(function_node.result_type)
        return_xml = Element('RETURN_TYPE')
        return_xml.set('DATATYPE', self.get_type_spelling(function_node.result_type, template_args))
        return_xml.set('DATATYPE_NAMESPACE', get_type_ghidra_namespace(function_node.result_type))
        return_xml.set('SIZE', str(self.get_type_size(function_node.result_type, template_args)))
        function_xml.append(return_xml)
        index = 0
        
        if not function_node.is_static_method():
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', f'{struct_name}*')
            parameter_xml.set('DATATYPE_NAMESPACE', get_ghidra_namespace(struct_name))
            parameter_xml.set('NAME', 'this')
            parameter_xml.set('SIZE', '4')
            function_xml.append(parameter_xml)
        
        for arg in function_node.get_arguments():
            self.generate_template_structures(arg.type)
            parameter_xml = Element('PARAMETER')
            parameter_xml.set('ORDINAL', str(index))
            parameter_xml.set('DATATYPE', fix_type_string(self.get_type_spelling(arg.type, template_args)))
            parameter_xml.set('DATATYPE_NAMESPACE', get_type_ghidra_namespace(arg.type))
            parameter_xml.set('NAME', arg.spelling if arg.spelling else f'param_{index+1}')
            parameter_xml.set('SIZE', str(max(self.get_type_size(arg.type, template_args), 4)))
            function_xml.append(parameter_xml)
            
    def add_virtual_dtor_function_def(self, fullname, struct_fullname):
        function_xml = Element('FUNCTION_DEF')
        function_xml.set('NAME', fullname)
        function_xml.set('NAMESPACE', get_ghidra_namespace(fullname))
        self.datatypes_root.append(function_xml)
        
        return_xml = Element('RETURN_TYPE')
        return_xml.set('DATATYPE', 'VOID')
        return_xml.set('DATATYPE_NAMESPACE', '/')
        return_xml.set('SIZE', '0')
        function_xml.append(return_xml)
        
        parameter_xml = Element('PARAMETER')
        parameter_xml.set('ORDINAL', '0')
        parameter_xml.set('DATATYPE', f'{struct_fullname}*')
        parameter_xml.set('DATATYPE_NAMESPACE', get_ghidra_namespace(struct_fullname))
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
            
    def add_enum(self, fullname, enum_node):
        enum_xml = Element('ENUM')
        enum_xml.set('NAME', fullname)
        enum_xml.set('NAMESPACE', get_ghidra_namespace(fullname))
        enum_xml.set('SIZE', '4')
        self.datatypes_root.append(enum_xml)
        
        for child in enum_node.get_children():
            assert(child.kind == cindex.CursorKind.ENUM_CONSTANT_DECL)
            entry_xml = Element('ENUM_ENTRY')
            entry_xml.set('NAME', child.spelling)
            entry_xml.set('VALUE', f'0x{child.enum_value:x}')
            enum_xml.append(entry_xml)
        