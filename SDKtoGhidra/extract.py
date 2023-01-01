import os
import clang.cindex as cindex
from ghidra_xml import GhidraToXmlWriter, build_full_name


def check_node(node, expected_kind):
    """Returns false if the node is None or is not of the expected kind"""
    return node is not None and node.kind == expected_kind


def traverse_print(node, level):
    print("\t" * level + f'{node.displayname} {node.mangled_name} [{node.kind}] [{node.location}]')
    for c in node.get_children():
        traverse_print(c, level + 1)
        
        
class AddressesCollection:
    def __init__(self):
        self.addresses = dict()  # Maps name to (disk, march2017) addresses
        self.current_namespace = []
        
    def parse_select_address(self, node):
        # It should have two children INTEGER_LITERAL nodes
        addresses = []
        for c in node.get_children():
            if c.kind == cindex.CursorKind.INTEGER_LITERAL:
                if len(addresses) == 2:
                    raise SyntaxError(f'Too many children in SelectAddress [{node.location}]')
                addresses.append(c)
            else:
                raise SyntaxError(f'Unknown children of kind {c.kind} in SelectAddress [{node.location}]')
            
    def parse_var_addresses(self, var_node):
        # The VAR_DECL node will have a UNEXPOSED_EXPR child, which will have a
        # DECL_REF_EXPR (with a 'SelectAddress' OVERLOADED_DECL_REF child), and two integer literals (the parameters)
        expr = next(var_node.get_children(), None)
        if not check_node(expr, cindex.CursorKind.UNEXPOSED_EXPR):
            raise SyntaxError(f'Wrong VAR_DECL children [{var_node.location}]')
        
        expr_children = expr.get_children()
        expr_name = next(expr_children, None)
        if not check_node(expr_name, cindex.CursorKind.DECL_REF_EXPR):
            raise SyntaxError(f'Wrong UNEXPOSED_EXPR children [{var_node.location}]')
        
        expr_arg0 = next(expr_children, None)
        if not check_node(expr_arg0, cindex.CursorKind.INTEGER_LITERAL):
            raise SyntaxError(f'Expected 2 INTEGER_LITERAL arguments [{var_node.location}]')
        
        expr_arg1 = next(expr_children, None)
        if not check_node(expr_arg1, cindex.CursorKind.INTEGER_LITERAL):
            raise SyntaxError(f'Expected 2 INTEGER_LITERAL arguments [{var_node.location}]')
        
        return (next(expr_arg0.get_tokens()).spelling, next(expr_arg1.get_tokens()).spelling)
        
        
    def find_addresses(self, node, level):
        #print("\t" * level + f'Found {node.displayname} {node.mangled_name} [{node.kind}] [{node.location}]')
        
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.append(node.displayname.removesuffix('_addresses'))
            
        elif node.kind == cindex.CursorKind.VAR_DECL:
            self.addresses[build_full_name(self.current_namespace, node.displayname)] = self.parse_var_addresses(node)
        
        # Recurse for children of this node)
        for c in node.get_children():
            self.find_addresses(c, level + 1)
            
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.pop()
        

class FunctionProcessor:
    def __init__(self, addresses: dict, xml_writer: GhidraToXmlWriter) -> None:
        self.current_namespace = []
        self.addresses = addresses
        self.xml_writer = xml_writer
        # Only files in these paths will be exported
        self.exportable_paths = []
    
    def must_be_exported(self, node):
        if node.location is None or node.location.file is None:
            return True
        abs_name = os.path.abspath(node.location.file.name)
        return any(abs_name.startswith(path) for path in self.exportable_paths)
    
    def process(self, node):
        if not self.must_be_exported(node):
            return
        
        is_empty = next(node.get_children(), None) is None
        process_children = True
        must_pop_namespace = False
        
        if node.kind == cindex.CursorKind.NAMESPACE:
            self.current_namespace.append(node.displayname)
            must_pop_namespace = True
            
        elif node.kind == cindex.CursorKind.UNION_DECL:
            return  #TODO
            
        elif not is_empty and node.kind in [cindex.CursorKind.STRUCT_DECL, cindex.CursorKind.CLASS_DECL]:
            if node.displayname == '':
                print(f'EMPTY STRUCTURE DISPLAYNAME: [{node.location}]')
                
            #print(build_full_name(self.current_namespace, node.displayname))
            for c in node.get_children():
                if c.kind == cindex.CursorKind.FIELD_DECL:
                    pass
                    #print(f'    {c.type.spelling} {c.displayname}')
        
            self.current_namespace.append(node.displayname)
            must_pop_namespace = True
            
        elif node.kind == cindex.CursorKind.TYPEDEF_DECL:
            fullname = build_full_name(self.current_namespace, node.displayname)
            #print(f'Adding typedef\t{fullname}')
            self.xml_writer.add_typedef(self.current_namespace, node.displayname, node)
                
        elif not is_empty and node.kind == cindex.CursorKind.CLASS_TEMPLATE:
            fullname = build_full_name(self.current_namespace, node.spelling)

            self.xml_writer.add_template_node(fullname, node) 
            self.current_namespace.append(node.spelling)
            must_pop_namespace = True
            # We don't want to process typedefs, inner structs, etc inside the template, as they won't be specialized
            process_children = False
                
        elif not is_empty and node.kind == cindex.CursorKind.ENUM_DECL:
            fullname = build_full_name(self.current_namespace, node.displayname)
            #print(f'Adding enum\t{fullname}')
            if node.displayname == '':
                print(f'EMPTY ENUM DISPLAYNAME: [{node.location}]')
            self.xml_writer.add_enum(self.current_namespace, node.displayname, node)
            
        elif node.kind == cindex.CursorKind.CXX_METHOD:
            pass
            #method_full_name = self.build_full_var_name(node.spelling)
            # address = self.addresses.get(method_full_name, None)
            # if address is not None:
            #     fullname = node.result_type.spelling
            #     arg_types = [arg.type.spelling for arg in node.get_arguments()]
            #     #self.output_file.write(f'{method_full_name} {address[0]} {address[1]} {fullname}({", ".join(arg_types)})\n')
            
        # Recurse for children of this node
        if process_children:
            for c in node.get_children():
                self.process(c)
            
        if must_pop_namespace:
            self.current_namespace.pop()
            
        # We process it AFTER its children, as there might be classes inside
        if not is_empty and node.kind in [cindex.CursorKind.STRUCT_DECL, cindex.CursorKind.CLASS_DECL]:
            fullname = build_full_name(self.current_namespace, node.displayname)
            #print(f'Adding struct\t{fullname}')
            self.xml_writer.add_structure(self.current_namespace, node.displayname, node)
    

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
    output_file.write('#include "address_include.h"')
    for line in input_file.readlines():
        if line.startswith('#include'):
            includes.append(line)
        else:
            output_file.write(line)
    return includes        


if __name__ == '__main__22':
    tu = cindex.TranslationUnit.from_source('test.cpp', args=[
        '-x', 'c++',
        #'-target', 'x86_64-PC-Win32-MSVC',
        r'-IE:\Eric\Spore ModAPI SDK\Spore ModAPI'
        ])

    for diag in tu.diagnostics:
        print(diag)
    
    xml_writer = GhidraToXmlWriter()
    function_processor = FunctionProcessor(None, xml_writer)
    function_processor.exportable_paths.append(r'E:\Eric\Spore ModAPI SDK')
    function_processor.process(tu.cursor)
    
    xml_writer.write('output.xml')


if __name__ == '__main__':
    #sdk_path = '..\\'
    include_path = r'E:\Eric\Spore ModAPI SDK\Spore ModAPI'
    path = os.path.join(include_path, r'SourceCode\DLL\AddressesApp.cpp')
    temp_path = 'temp.cpp'
    
    # First we want to extract the addresses, then the function signatures
    # For the addresses, it's simpler to ignore the includes
    with open(path, 'r') as input_file, open(temp_path, 'w') as output_file:
        includes = extract_includes(input_file, output_file)

    index = cindex.Index.create()
    tu = index.parse(temp_path, args=[
        '-DMODAPI_DLL_EXPORT',
        '-DAddresses(name)=name##_addresses',
        '-x', 'c++'
    ])
    
    for diag in tu.diagnostics:
        print(diag)
        
    addresses = AddressesCollection()
    addresses.find_addresses(tu.cursor, 0)
    
    for i in addresses.addresses.items():
        print(i)
        
    #includes.clear()
    #includes.append('#include "test_file.h"\n')
    # Now create a file only with the includes, then process its structures
    includes.insert(0, '#include <Spore\CppRevEngBase.h>\n')
    includes.insert(0, '#include "eastl_include.h"\n')
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
    
    xml_writer = GhidraToXmlWriter()
    function_processor = FunctionProcessor(addresses.addresses, xml_writer)
    function_processor.exportable_paths.append(r'E:\Eric\Spore ModAPI SDK')
    function_processor.process(tu.cursor)
    
    xml_writer.write('output.xml')