import os
import clang.cindex as cindex
from ghidra_xml import GhidraToXmlWriter, build_full_name, get_spore_ghidra_namespace


def check_node(node, expected_kind):
    """Returns false if the node is None or is not of the expected kind"""
    return node is not None and node.kind == expected_kind


def traverse_print(node, level):
    print("\t" * level + f'{node.displayname} {node.mangled_name} [{node.kind}] [{node.location}]')
    for c in node.get_children():
        traverse_print(c, level + 1)
        
        
class AddressesCollection:
    def __init__(self):
        self.name_to_address = dict()  # Maps name to (disk, march2017) addresses
        self.disk_to_name = dict()  # We use this to avoid repeated addresses
        self.current_namespace = []
        
    def parse_var_addresses(self, var_node):
        # The VAR_DECL node will have a CALL_EXPR, which will have a UNEXPOSED_EXPR child, which will have a
        # DECL_REF_EXPR and two UNEXPOSED_EXPR (the parameters) with an integer literal inside
        expr = next(var_node.get_children(), None)
        if not check_node(expr, cindex.CursorKind.CALL_EXPR):
            raise SyntaxError(f'Wrong VAR_DECL children [{var_node.location}]')
        
        expr_children = expr.get_children()
        expr_name = next(expr_children, None)
        if not check_node(expr_name, cindex.CursorKind.UNEXPOSED_EXPR):
            raise SyntaxError(f'Wrong VAR_DECL children [{var_node.location}]')
        
        #print(var_node.displayname)
        #traverse_print(var_node, 0)
        expr_arg0 = next(expr_children, None)
        if not check_node(expr_arg0, cindex.CursorKind.UNEXPOSED_EXPR):
            raise SyntaxError(f'Expected 2 int arguments [{var_node.location}]')
        expr_arg0_value = next(expr_arg0.get_children(), None)
        if not check_node(expr_arg0_value, cindex.CursorKind.INTEGER_LITERAL):
            raise SyntaxError(f'Expected an INTEGER_LITERAL node [{var_node.location}]')
        
        expr_arg1 = next(expr_children, None)
        if not check_node(expr_arg1, cindex.CursorKind.UNEXPOSED_EXPR):
            raise SyntaxError(f'Expected 2 int arguments [{var_node.location}]')
        expr_arg1_value = next(expr_arg1.get_children(), None)
        if not check_node(expr_arg1_value, cindex.CursorKind.INTEGER_LITERAL):
            raise SyntaxError(f'Expected an INTEGER_LITERAL node [{var_node.location}]')
        
        result = (next(expr_arg0_value.get_tokens()).spelling, next(expr_arg1_value.get_tokens()).spelling)
        return (int(result[0], 0), int(result[1], 0))
        
        
    def find_addresses(self, node, level):
        #print("\t" * level + f'Found {node.displayname} {node.mangled_name} [{node.kind}] [{node.location}]')
        
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.append(node.displayname.removesuffix('_addresses'))
            
        elif node.kind == cindex.CursorKind.VAR_DECL:
            address_set = self.parse_var_addresses(node)
            fullname = build_full_name(self.current_namespace, node.displayname)
            if address_set[0] in self.disk_to_name:
                # Replace the old address, only keep the new one
                del self.name_to_address[self.disk_to_name[address_set[0]]]
            self.name_to_address[fullname] = address_set
            self.disk_to_name[address_set[0]] = fullname
        
        # Recurse for children of this node)
        for c in node.get_children():
            self.find_addresses(c, level + 1)
            
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.pop()
        

class FunctionProcessor:
    def __init__(self, xml_writer: GhidraToXmlWriter) -> None:
        self.current_namespace = []
        self.xml_writer = xml_writer
        # Only files in these paths will be exported
        self.exportable_paths = []
    
    def must_be_exported(self, node):
        if node.location is None or node.location.file is None:
            return True
        abs_name = os.path.abspath(node.location.file.name)
        return any(abs_name.startswith(path) for path in self.exportable_paths)
    
    def process(self, node, forced_name=None):
        if not self.must_be_exported(node):
            return
        
        is_empty = next(node.get_children(), None) is None
        process_children = True
        must_pop_namespace = False
        
        node_name = node.displayname if forced_name is None else forced_name
        
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.append(node_name)
            must_pop_namespace = True
            
        elif node.kind == cindex.CursorKind.UNION_DECL:
            self.current_namespace.append(node_name)
            must_pop_namespace = True
            process_children = False
            
        elif node.kind in [cindex.CursorKind.STRUCT_DECL, cindex.CursorKind.CLASS_DECL]:
            if node.displayname == '':
                print(f'EMPTY STRUCTURE DISPLAYNAME: [{node.location}]')
            
            # Even if the structure is empty (i.e. it's a forward declaration) we need to register it so we can know its namespace
            ghidra_namespace_list = self.current_namespace
            # We don't apply this to the fullname, so that it can still be found in the get_type_... methods
            if str(node.location.file).endswith('d3d9.h') or str(node.location.file).endswith('d3d9types.h'):
                ghidra_namespace_list = ['Direct3D'] + ghidra_namespace_list
            ghidra_namespace = get_spore_ghidra_namespace(ghidra_namespace_list)
            fullname = build_full_name(self.current_namespace, node_name)
            self.xml_writer.structure_namespaces[fullname] = ghidra_namespace
            
            self.current_namespace.append(node_name)
            must_pop_namespace = True
            
        elif node.kind == cindex.CursorKind.TYPEDEF_DECL:
            fullname = build_full_name(self.current_namespace, node_name)
            #print(f'Adding typedef\t{fullname}')
            self.xml_writer.add_typedef(self.current_namespace, node_name, node)
                
        elif not is_empty and node.kind == cindex.CursorKind.CLASS_TEMPLATE:
            fullname = build_full_name(self.current_namespace, node.spelling)

            self.xml_writer.add_template_node(fullname, node) 
            self.current_namespace.append(node.spelling)
            must_pop_namespace = True
            # We don't want to process typedefs, inner structs, etc inside the template, as they won't be specialized
            process_children = False
                
        elif not is_empty and node.kind == cindex.CursorKind.ENUM_DECL:
            fullname = build_full_name(self.current_namespace, node_name)
            #print(f'Adding enum\t{fullname}')
            if node.displayname == '':
                print(f'EMPTY ENUM DISPLAYNAME: [{node.location}]')
            self.xml_writer.add_enum(self.current_namespace, node_name, node)
            
        # CXX_METHOD is for class methods. FUNCTION_DECL is for non-class methods
        elif node.kind == cindex.CursorKind.FUNCTION_DECL:
            fullname = build_full_name(self.current_namespace, node.spelling)
            address = self.xml_writer.addresses_dict.get(fullname, None)
            if address is not None and fullname not in self.xml_writer.added_address_names:
                self.xml_writer.add_function_def_from_node(self.current_namespace, node, None)
            
        elif node.kind == cindex.CursorKind.VAR_DECL:
            fullname = build_full_name(self.current_namespace, node.spelling)
            address = self.xml_writer.addresses_dict.get(fullname, None)
            if address is not None and fullname not in self.xml_writer.added_address_names:
                self.xml_writer.add_symbol_address(fullname, self.current_namespace, node.type)
            
        # Recurse for children of this node
        if process_children:
            for c in node.get_children():
                self.process(c)
            
        if must_pop_namespace:
            self.current_namespace.pop()
            
        # We process it AFTER its children, as there might be classes inside
        if not is_empty and node.kind in [cindex.CursorKind.STRUCT_DECL, cindex.CursorKind.CLASS_DECL]:
            fullname = build_full_name(self.current_namespace, node_name)
            #print(f'Adding struct\t{fullname}')
            self.xml_writer.add_structure(self.current_namespace, node_name, node)
            
        # If the union does not have a name then it is a field, and is handled by add_structure()
        elif not is_empty and node.kind == cindex.CursorKind.UNION_DECL and node.displayname:
            self.xml_writer.add_union(self.current_namespace, node_name, node)
    

# with open('output.txt', 'w') as output_file:
#     function_processor = FunctionProcessor(addresses.addresses, output_file)
#     function_processor.process(tu.cursor)

def extract_includes(input_file, output_file):
    """
    Writes input_file to output_file, but excluding any #include lines,
    and adding an additional include to 'address_include.h'
    The #include lines are returned in a list.
    """
    includes = []
    output_file.write('#include "address_include.h"\n')
    for line in input_file.readlines():
        if line.startswith('#include'):
            includes.append(line)
        else:
            output_file.write(line)
    output_file.write('\n')
    return includes
            
            
def load_additional_addresses(file_path):
    with open(file_path, 'r') as f:
        result = [line.split('=', 1) for line in f.readlines()]
        return [(int(r[0], 0), r[1].strip()) for r in result]
    

def main():
    include_path = r'E:\Eric\Spore ModAPI SDK\Spore ModAPI'
    temp_path = 'temp.cpp'
    folder_path = os.path.join(include_path, r'SourceCode\DLL')
    addresses_files = [name for name in os.listdir(folder_path) if name.startswith('Addresses') and name.endswith('.cpp')]
    includes = []
    
    print('Extracting includes...')
    # First we want to extract the addresses, then the function signatures
    # For the addresses, it's simpler to ignore the includes
    with open(temp_path, 'w') as output_file:
        for file_name in addresses_files:
            with open(os.path.join(folder_path, file_name), 'r') as input_file:
                includes.extend(extract_includes(input_file, output_file))

    print('Parsing addrseses file...')
    index = cindex.Index.create()
    tu = index.parse(temp_path, args=[
        #'-DMODAPI_DLL_EXPORT',
        #'-DAddresses(name)=name##_addresses',
        '-x', 'c++',
        '-DSDK_TO_GHIDRA',
    ])
    
    for diag in tu.diagnostics:
        print(diag)
        
    #traverse_print(tu.cursor, 0)
        
    print('Extracting addresses...')
    addresses = AddressesCollection()
    addresses.find_addresses(tu.cursor, 0)
    
    # disk_address_names = dict()
    # march2017_address_names = dict()
    # for name, address_set in addresses.name_to_address.items():
    #     address0 = int(address_set[0], 0)
    #     address1 = int(address_set[1], 0)
    #     disk_address_names[name] = address0
    #     march2017_address_names[name] = address1
        
    print('Parsing SDK files...')
    includes.clear()
    for root, dirs, files in os.walk(os.path.join(include_path, 'Spore')):
        for file in files:
            if file.endswith('.h'):
                complete_path = os.path.join(os.path.relpath(root, include_path), file)
                includes.append(f'#include <{complete_path}>\n')
        
    #includes.clear()
    #includes.append('#include "test_file.h"\n')
    # Now create a file only with the includes, then process its structures
    includes.insert(0, '#include <Spore\\CppRevEngBase.h>\n')
    includes.insert(0, '#include "eastl_include.h"\n')
    includes.insert(0, '#include <wintypes.h>\n')
    with open(temp_path, 'w') as output_file:
        output_file.writelines(includes)
        
    tu = cindex.TranslationUnit.from_source(temp_path, args=[
        '-x', 'c++',
        '-target', 'x86_64-PC-Win32-MSVC',
        '-m32',
        '-DSDK_TO_GHIDRA',
        '-fdeclspec',
        '-Wignored-attributes',
        r'-IE:\Eric\Spore ModAPI SDK\Spore ModAPI',
        r'-IE:\Eric\Spore ModAPI SDK\SDKtoGhidra\fake_includes'
        ])

    for diag in tu.diagnostics:
        print(diag)
    
    print('Extracting SDK data...')
    xml_writer = GhidraToXmlWriter(addresses.name_to_address)
    function_processor = FunctionProcessor(xml_writer)
    function_processor.exportable_paths.append(r'E:\Eric\Spore ModAPI SDK')
    function_processor.process(tu.cursor)
    xml_writer.create_objecttype_enum()
    
    print(f'Added {len(xml_writer.added_address_names)} addresses. Remaining:')
    for address_name in addresses.name_to_address.keys():
        if address_name not in xml_writer.added_address_names:
            print(address_name)
    
    print('Loading additional addresses...')
    with open('excluded_names.txt') as f:
        excluded_names = [line.strip() for line in f.readlines()]
    for i in range(2):
        additional_addresses = load_additional_addresses(['additional_disk.txt', 'additional_march2017.txt'][i])
        for addr_value, addr_name in additional_addresses:
            if addr_name not in excluded_names and addr_value not in xml_writer.added_address_values[i]:
                xml_writer.add_single_symbol_address(addr_name, addr_value, i)
    
    xml_writer.write('SporeGhidra_disk.xml', 0)
    xml_writer.write('SporeGhidra_march2017.xml', 1)


if __name__ == '__main__':
    main()