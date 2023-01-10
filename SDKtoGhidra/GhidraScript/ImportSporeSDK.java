// Imports data types and functions from the Spore ModAPI SDK
//@author 
//@category Data
//@keybinding 
//@menupath 
//@toolbar 

import ghidra.app.script.GhidraScript;
import ghidra.program.model.util.*;
import ghidra.program.model.reloc.*;
import ghidra.program.model.data.*;
import ghidra.program.model.block.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.scalar.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.address.*;
import ghidra.util.data.DataTypeParser;
import ghidra.util.exception.*;
import ghidra.app.util.xml.*;
import ghidra.app.util.importer.*;
import ghidra.app.cmd.function.*;
import ghidra.util.xml.*;
import ghidra.util.task.*;
import ghidra.util.*;
import ghidra.xml.*;
import java.io.IOException;
import java.io.File;
import java.util.*;
import org.xml.sax.*;

public class ImportSporeSDK extends GhidraScript {

    public void run() throws Exception {
        printf("ImportSporeSDK.java - Import datatypes and addresses from the Spore ModAPI SDK\n");

        File inputFile = askFile("Select SDKtoGhidra.xml file", "Import file");

        XmlProgramOptions xmlOptions = new XmlProgramOptions();
        xmlOptions.setInstructions(true);
        xmlOptions.setComments(true);
        xmlOptions.setData(false);  // Important! We do this manually, as Ghidra generates '.conflict' structures by default
        xmlOptions.setEquates(true);
        xmlOptions.setFunctions(true);
        xmlOptions.setMemoryBlocks(true);
        xmlOptions.setMemoryContents(true);
        xmlOptions.setProperties(true);
        xmlOptions.setReferences(true);
        xmlOptions.setSymbols(true);
        xmlOptions.setTrees(true);
        xmlOptions.setBookmarks(true);
        xmlOptions.setRegisters(true);
        xmlOptions.setRelocationTable(true);
        xmlOptions.setEntryPoints(true);
        xmlOptions.setExternalLibraries(true);
        xmlOptions.setOverwriteBookmarkConflicts(true);
        xmlOptions.setOverwriteMemoryConflicts(true);
        xmlOptions.setOverwriteDataConflicts(true);
        xmlOptions.setOverwritePropertyConflicts(true);
        xmlOptions.setOverwriteReferenceConflicts(true);
        xmlOptions.setOverwriteSymbolConflicts(true);
        xmlOptions.setAddToProgram(true);

		MessageLog log = new XmlMessageLog();
        parseXmlDatatypes(inputFile, log);

		printf(log.toString());

		ProgramXmlMgr xmlMgr = new ProgramXmlMgr(inputFile);
        log = xmlMgr.read(currentProgram, monitor, xmlOptions);

		postProcessXml(inputFile, log);
		printf(log.toString());
    }

	private void postProcessXml(File file, MessageLog log) throws Exception
    {
        XmlPullParser parser = XmlPullParserFactory.create(file, new MyErrorHandler(log), false);
        final XmlElement programStart = parser.start("PROGRAM");
		try {
			while (parser.hasNext() && parser.peek().isStart() && !monitor.isCancelled()) {
				XmlElement element = parser.peek();
				String name = element.getName();

				/*if (name.equals("DATATYPES")) {
					monitor.setMessage("Processing DATA TYPES ...");
					
                    // We want to find the FUNCTION_DEF types
                    //TODO findFunctionDefs(parser, log);
				}
                else */if (name.equals("FUNCTION_ADDRESSES")) {
                    monitor.setMessage("Processing FUNCTION ADDRESSES ...");

                    processFunctionAddresses(parser, log);
                }
				else {
					monitor.setMessage("Skipping over " + name + " ...");
					parser.discardSubTree(name);
				}
			}
			parser.end(programStart);
		}
		catch (CancelledException e) {
			throw new IOException("XML Read Cancelled");
		}
		finally {
			parser.dispose();
		}

        //printf(log.toString());
    }

	private static class CustomConflictHandler extends DataTypeConflictHandler
	{
		public DataTypeConflictHandler getSubsequentHandler() 
		{
			return this;
		}
		public DataTypeConflictHandler.ConflictResult resolveConflict(DataType addedDataType, DataType existingDataType) 
		{
			return DataTypeConflictHandler.ConflictResult.REPLACE_EXISTING;
		}
		public boolean shouldUpdate(DataType sourceDataType, DataType localDataType)
		{
			return true;
		}
	};

    private void parseXmlDatatypes(File file, MessageLog log) throws Exception
    {
        XmlPullParser parser = XmlPullParserFactory.create(file, new MyErrorHandler(log), false);
        final XmlElement programStart = parser.start("PROGRAM");
		try {
			while (parser.hasNext() && parser.peek().isStart() && !monitor.isCancelled()) {
				XmlElement element = parser.peek();
				String name = element.getName();

				if (name.equals("DATATYPES")) {
					monitor.setMessage("Processing DATA TYPES ...");

					this.dataManager = currentProgram.getDataTypeManager();
					this.log = log;
					readDataTypes(parser, monitor);
				}
				else {
					monitor.setMessage("Skipping over " + name + " ...");
					parser.discardSubTree(name);
				}
			}
			parser.end(programStart);
		}
		catch (CancelledException e) {
			throw new IOException("XML Read Cancelled");
		}
		finally {
			parser.dispose();
		}

        //printf(log.toString());
    }

	public void readDataTypes(XmlPullParser parser, TaskMonitor monitor)
			throws SAXParseException, CancelledException {
		ArrayList<XmlTreeNode> todo = new ArrayList<>();
		XmlElement element = parser.next();

		BuiltInDataTypeManager builtInMgr = BuiltInDataTypeManager.getDataTypeManager();
		try {
			dtParser = new DtParser(dataManager);
			while (true) {
				if (monitor.isCancelled()) {
					throw new CancelledException();
				}
				element = parser.peek();
				if (element.isEnd() && element.getName().equals("DATATYPES")) {
					parser.next();
					break;
				}
				XmlTreeNode root = new XmlTreeNode(parser);
				if (!processDataTypeNode(root, true)) {
					todo.add(root);
				}
			}

			while (true) {
				if (monitor.isCancelled()) {
					throw new CancelledException();
				}
				boolean processed = false;
				Iterator<XmlTreeNode> it = todo.iterator();
				while (it.hasNext()) {
					XmlTreeNode node = it.next();
					if (processDataTypeNode(node, false)) {
						it.remove();
						processed = true;
					}
				}
				if (!processed) {
					break;
				}
			}
		}
		finally {
			builtInMgr.close();
			dtParser = null;
		}

		Iterator<XmlTreeNode> it = todo.iterator();
		while (it.hasNext()) {
			if (monitor.isCancelled()) {
				throw new CancelledException();
			}
			logError(it.next());
		}
	}

    private void processFunctionAddresses(XmlPullParser parser, MessageLog log) throws CancelledException, SAXParseException, XmlAttributeException, InvalidInputException
    {
        XmlElement element = parser.next();
        while (true) {
            if (monitor.isCancelled()) {
                throw new CancelledException();
            }
            element = parser.peek();
            if (element.isEnd() && element.getName().equals("FUNCTION_ADDRESSES")) {
                parser.next();
                break;
            }
            XmlTreeNode root = new XmlTreeNode(parser);
            processFunctionAddress(root, log);
        }
    }

    private void processFunctionAddress(XmlTreeNode root, MessageLog log) throws InvalidInputException, XmlAttributeException {
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
        String addrStr = element.getAttribute("ADDRESS");

        printf("Adding function " + name + " at address " + addrStr);

        Address addr = XmlProgramUtilities.parseAddress(currentProgram.getAddressFactory(), addrStr);
        if (addr == null) {
            throw new XmlAttributeException("Incompatible Symbol Address: " + addrStr);
        }
        if (name == null) {
            throw new XmlAttributeException(
                "Missing required symbol name for address: " + addrStr);
        }

        String datatypeName = element.getAttribute("DATATYPE");
        CategoryPath datatypePath = getCategoryPath(element, "DATATYPE_NAMESPACE");
        FunctionDefinition fd = (FunctionDefinition) currentProgram.getDataTypeManager().getDataType(datatypePath, datatypeName);

        Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(addr);
        if (s == null) {
            // s = SymbolUtilities.createPreferredLabelOrFunctionSymbol(program, addr, scope, name,
            //     sourceType);
            printf("   Symbol is null");
        }
        else if (s.getSymbolType() == SymbolType.FUNCTION) {
            Function f = (Function) s.getObject();
            
            // ApplyFunctionSignatureCmd cmd = new ApplyFunctionSignatureCmd(f.getEntryPoint(), fd, SourceType.IMPORTED);
		    // cmd.applyTo(f.getProgram());
            setSignature(f, fd, false, name, SourceType.IMPORTED);
        }
        else {
            CreateFunctionCmd createCmd = new CreateFunctionCmd(addr);
		    if (!createCmd.applyTo(currentProgram))
            {
                throw new XmlAttributeException(
                "Symbol exists but is not a function for address: " + addrStr);
            }

            s = currentProgram.getSymbolTable().getPrimarySymbol(addr);
            Function f = (Function) s.getObject();
            setSignature(f, fd, false, name, SourceType.IMPORTED);
        }
    }

    // private void findFunctionDefs(XmlPullParser parser, MessageLog log) throws CancelledException, SAXParseException
    // {
    //     XmlElement element = parser.next();
    //     while (true) {
    //         if (monitor.isCancelled()) {
    //             throw new CancelledException();
    //         }
    //         element = parser.peek();
    //         if (element.isEnd() && element.getName().equals("DATATYPES")) {
    //             parser.next();
    //             break;
    //         }
    //         XmlTreeNode root = new XmlTreeNode(parser);
    //         processDatatypeNode(root, true, log);
    //     }
    // }

    // private boolean processDatatypeNode(XmlTreeNode root, boolean firstPass, MessageLog log) {
	// 	XmlElement element = root.getStartElement();
	// 	String elementName = element.getName();

	// 	try {
	// 		if (elementName.equals("FUNCTION_DEF")) {
                
    //             //printf("Processing function " + element.getAttribute("NAME") + "  [" + name + "]\n");
    //             String functionName = element.getAttribute("NAME");
	// 	        CategoryPath path = getCategoryPath(element);
    //             //printf(path + "\n");

    //             FunctionDefinition fd = (FunctionDefinition) currentProgram.getDataTypeManager().getDataType(path, functionName);
    //             if (fd == null) {
    //                 log.appendMsg("Skipping function " + path + "/" + functionName);
    //             }
    //             else {
    //                 String callingConvention = "unknown";
    //                 if (element.hasAttribute("CONVENTION")) {
    //                     callingConvention = element.getAttribute("CONVENTION");
    //                 }
    //                 GenericCallingConvention convention = getCallingConvention(callingConvention);
    //                 if (convention == null)
    //                 {
    //                     throw new Exception("Unknown calling convention '" + convention + "' in function " + path + "/" + functionName);
    //                 }
    //                 fd.setGenericCallingConvention​(convention);
    //             }
	// 		}
	// 	}
	// 	catch (Exception e) {
	// 		log.appendException(e);
	// 	}
	// 	return true;
	// }

    private static GenericCallingConvention getCallingConvention(String text) {
        switch (text)
        {
            case "cdecl": return GenericCallingConvention.cdecl;
            case "fastcall": return GenericCallingConvention.fastcall;
            case "stdcall": return GenericCallingConvention.stdcall;
            case "thiscall": return GenericCallingConvention.thiscall;
            case "vectorcall": return GenericCallingConvention.vectorcall;
            case "unknown": return GenericCallingConvention.unknown;
            default: return null;
        }
    }

    private CategoryPath getCategoryPath(XmlElement element) {
		return getCategoryPath(element, "NAMESPACE");
	}

    private CategoryPath getCategoryPath(XmlElement element, String attributeName) {
		String nameSpace = element.getAttribute(attributeName);
		CategoryPath cp = nameSpace == null ? CategoryPath.ROOT : new CategoryPath(nameSpace);
		return cp;
	}

    private boolean setSignature(Function func, FunctionSignature signature,
			boolean preserveCallingConvention, String customName, SourceType source)
			throws InvalidInputException {

		// take on the signatures name if this is not a user defined symbol
		setName(func, customName, source, true);

		CompilerSpec compilerSpec = currentProgram.getCompilerSpec();
		String conventionName = getCallingConvention(func, signature, compilerSpec);

        func.setCustomVariableStorage​(true);
        printf(func.hasCustomVariableStorage() + "\n");
		ParameterDefinition[] args = signature.getArguments();
		List<Parameter> params = createParameters(compilerSpec, conventionName, args);

		SymbolTable symbolTable = currentProgram.getSymbolTable();
		try {

			adjustParameterNamesToAvoidConflicts(symbolTable, func, params);

            int returnTypeSize = signature.getReturnType().getLength();
            VariableStorage returnStorage;
            if (returnTypeSize == 1) {
                returnStorage = new VariableStorage(currentProgram, currentProgram.getRegister("al"));
            }
            else if (returnTypeSize == 8) {
                returnStorage = new VariableStorage(currentProgram, currentProgram.getRegister("eax"), currentProgram.getRegister("edx"));
            }
            else if ("void".equals(signature.getReturnType().getName())) {
                returnStorage = VariableStorage.VOID_STORAGE;
            }
            else {
                returnStorage = new VariableStorage(currentProgram, currentProgram.getRegister("eax"));
            }

			ReturnParameterImpl returnParam =
				new ReturnParameterImpl(signature.getReturnType(), returnStorage, currentProgram);

			func.updateFunction(conventionName, returnParam, params,
				Function.FunctionUpdateType.CUSTOM_STORAGE, true, source);
			func.setVarArgs(signature.hasVarArgs());
		}
		catch (DuplicateNameException e) {
			// should not happen unless caused by a concurrent operation
			throw new InvalidInputException(
				"Parameter name conflict, likely due to concurrent operation");
		}

		updateStackPurgeSize(func, currentProgram);

		return true;
	}

    private static void updateStackPurgeSize(Function function, Program program) {
		// TODO: The following code could lock-in the wrong purge if the signature or calling
		// convention is incorrect.  (See SCR 9580)
		if (function.isStackPurgeSizeValid()) {
			return;
		}

		PrototypeModel convention = function.getCallingConvention();
		if (convention == null) {
			convention = program.getCompilerSpec().getDefaultCallingConvention();
		}

		int extraPop = convention.getExtrapop();
		if (extraPop != PrototypeModel.UNKNOWN_EXTRAPOP) {
			function.setStackPurgeSize(0);
			return;
		}

		int purgeSize = 0;
		Parameter[] parameters = function.getParameters();
		if (parameters.length > 0) {
			int align = convention.getStackParameterAlignment();
			long min = 0xfffffff0L; // Make sure this is a big POSITIVE value
			long max = 0;
			for (Parameter parameter : parameters) {
				Varnode vn = parameter.getFirstStorageVarnode();
				if (vn == null) {
					purgeSize = Function.UNKNOWN_STACK_DEPTH_CHANGE;
					break;
				}
				if (!vn.getAddress().isStackAddress()) {
					continue;
				}
				long val = vn.getOffset();
				if (val < min) {
					min = val;
				}
				val += vn.getSize();
				if (val > max) {
					max = val;
				}
			}

			if (max > min) {
				int diff = (int) (max - min);
				int rem = diff % align;
				if (rem != 0) {
					diff += (align - rem);
				}
				purgeSize += diff;
			}
		}

		if (purgeSize >= 0 && purgeSize != Function.UNKNOWN_STACK_DEPTH_CHANGE) {
			function.setStackPurgeSize(purgeSize);
		}
	}

    private void adjustParameterNamesToAvoidConflicts(SymbolTable symbolTable, Function function,
			List<Parameter> params) throws DuplicateNameException, InvalidInputException {

		for (int i = 0; i < params.size(); i++) {
			Parameter param = params.get(i);
			String name = param.getName();
			if (name == null || SymbolUtilities.isDefaultParameterName(name)) {
				continue;
			}

			String uniqueName = getUniqueParameterName(symbolTable, function, name);
			param.setName(uniqueName, param.getSource());
		}
	}

    private static String getUniqueParameterName(SymbolTable symbolTable, Function function,
			String name) {
		if (name == null || !SymbolUtilities.isDefaultParameterName(name)) {
			return name;
		}
		Symbol s = symbolTable.getParameterSymbol(name, function);
		if (s == null || s.getSymbolType() == SymbolType.PARAMETER) {
			return name;
		}
		return getUniqueName(symbolTable, function, name);
	}

    private static String getUniqueName(SymbolTable symbolTable, Namespace namespace,
			String baseName) {
		String name = baseName;
		if (name != null) {
			// establish unique name
			int cnt = 0;
			while (!symbolTable.getSymbols(name, namespace).isEmpty()) {
				name = baseName + (++cnt);
			}
		}
		return name;
	}

    private List<Parameter> createParameters(CompilerSpec compilerSpec, String conventionName,
			ParameterDefinition[] args) throws InvalidInputException {

		int firstParamIndex = getIndexOfFirstParameter(conventionName, args);
        boolean hasThisPointer = false;
        if (firstParamIndex == 1) {
            firstParamIndex = 0;
            hasThisPointer = true;
        }

        int stackOffset = 4;
		List<Parameter> params = new ArrayList<>();
		boolean settleCTypes = compilerSpec.doesCDataTypeConversions();
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		for (int i = firstParamIndex; i < args.length; i++) {
			String name = args[i].getName();
			if (Function.RETURN_PTR_PARAM_NAME.equals(name)) {
				continue; // discard what should be an auto-param
			}

            VariableStorage storage;
            if (hasThisPointer && i == 0) {
                storage = new VariableStorage(currentProgram, currentProgram.getRegister("ecx"));
            }
            else {
                storage = new VariableStorage(currentProgram, stackOffset, args[i].getLength());
                stackOffset += args[i].getLength();
                stackOffset = stackOffset + 3 & ~3;  // align to four
            }

			DataType type = args[i].getDataType().clone(dtm);
			if (settleCTypes) {
				type = settleCDataType(type, dtm);
			}
			Parameter param =
				new ParameterImpl(name, type, storage, currentProgram);
			param.setComment(args[i].getComment());
			params.add(param);
		}
		return params;
	}

    private static DataType settleCDataType(DataType dt, DataTypeManager dtm) {
		if (dt == null) {
			return null;
		}
		DataType baseType = dt;
		if (baseType instanceof TypedefDataType) {
			baseType = ((TypedefDataType) baseType).getBaseDataType();
		}
		if (!(baseType instanceof ArrayDataType)) {
			return dt;
		}
		baseType = ((ArrayDataType) baseType).getDataType();
		return dtm.getPointer(baseType);
	}

    private static int getIndexOfFirstParameter(String conventionName, ParameterDefinition[] args) {

		if (args.length == 0) {
			return 0;
		}

		if (!CompilerSpec.CALLING_CONVENTION_thiscall.equals(conventionName)) {
			return 0;
		}

		if (!Function.THIS_PARAM_NAME.equals(args[0].getName())) {
			return 0;
		}

		// Ignore this parameter since it should be established as an auto-parameter
		return 1; // 'this call' and the first param's name is 'this'
	}

    private void setName(Function function, String name, SourceType source,
			boolean forceName) throws InvalidInputException {

		if (name == null) {
			return;
		}

		Program currentProgram = function.getProgram();
		Address entryPoint = function.getEntryPoint();
		SymbolUtilities.validateName(name);

		SymbolTable symbolTable = currentProgram.getSymbolTable();
		Symbol sym = symbolTable.getPrimarySymbol(entryPoint);
		if (sym == null || sym.getName().equals(name)) {
			return;
		}

		if (!forceName && sym.getSource() != SourceType.DEFAULT) {
			// not default and we are not forcing the rename
			return;
		}

		try {
			removeCodeSymbol(symbolTable, entryPoint, name, function.getParentNamespace());
			sym.setName(name, source);
		}
		catch (DuplicateNameException e) {
			throw new InvalidInputException(
				"Function name conflict occurred when applying function signature.");
		}

	}

    private static void removeCodeSymbol(SymbolTable symbolTable, Address address, String name,
			Namespace namespace) {
		Symbol otherSym = symbolTable.getSymbol(name, address, namespace);
		if (otherSym != null) {
			if (otherSym.getSymbolType() == SymbolType.LABEL) {
				otherSym.delete(); // replace label if function name matches
			}
		}
	}

    private static String getCallingConvention(Function function, FunctionSignature signature, CompilerSpec compilerSpec) {
        boolean preserveCallingConvention = false;
		PrototypeModel preferredModel = null;
		if (signature.getGenericCallingConvention() != GenericCallingConvention.unknown) {
			preferredModel = compilerSpec.matchConvention(signature.getGenericCallingConvention());
		}

		PrototypeModel convention = function.getCallingConvention();
		if (convention == null || !preserveCallingConvention) {
			convention = preferredModel;
// NOTE: This has been disable since it can cause imported signature information to be
// ignored and overwritten by subsequent analysis
//			if (convention == null && compilerSpec.getCallingConventions().length > 1) {
//				// use default source for signature if convention is really unknown so that we
//				// know dynamic storage assignment is unreliable
//				source = SourceType.DEFAULT;
//			}
		}

		// Calling convention is permitted to change
		String conventionName = function.getCallingConventionName();
		if (!preserveCallingConvention && convention != null) {
			conventionName = convention.getName();
		}
		return conventionName;
	}


    class MyErrorHandler implements ErrorHandler {
        private MessageLog log;
    
        MyErrorHandler(MessageLog log) {
            this.log = log;
        }
    
        /**
         * @see org.xml.sax.ErrorHandler#error(org.xml.sax.SAXParseException)
         */
        @Override
        public void error(SAXParseException exception) throws SAXException {
            log.appendMsg(exception.getMessage());
        }
    
        /**
         * @see org.xml.sax.ErrorHandler#fatalError(org.xml.sax.SAXParseException)
         */
        @Override
        public void fatalError(SAXParseException exception) throws SAXException {
            log.appendMsg(exception.getMessage());
        }
    
        /**
         * @see org.xml.sax.ErrorHandler#warning(org.xml.sax.SAXParseException)
         */
        @Override
        public void warning(SAXParseException exception) throws SAXException {
            log.appendMsg(exception.getMessage());
        }
    }


	///// COPIED AND ADAPTED FROM DataTypesXmlMgr.java /////

	private final static int DEFAULT_SIZE = 1;

	private static HashMap<String, DataType> foreignTypedefs = new HashMap<>();
	static {
		foreignTypedefs.put("ascii", CharDataType.dataType);
		foreignTypedefs.put("string1", PascalString255DataType.dataType);
		foreignTypedefs.put("string2", PascalStringDataType.dataType);
		// string4 - pascal string with 4-byte length prefix
		foreignTypedefs.put("unicode2", PascalUnicodeDataType.dataType);
		// unicode4 - pascal unicode string with 4-byte length prefix
		foreignTypedefs.put("tbyte", LongDoubleDataType.dataType); // 10-byte float
		// oword - 16-byte value
		// packed real
		foreignTypedefs.put("3byte", UnsignedInteger3DataType.dataType);
	}

	private DataTypeManager dataManager;
	private DtParser dtParser;
	private MessageLog log;
	private int defaultEnumSize = IntegerDataType.dataType.getLength();


	private void logError(XmlTreeNode node) {
		XmlElement element = node.getStartElement();
		String tagName = element.getName();
		String name = element.getAttribute("NAME");
		if (name == null) {
			name = "";
		}
		logError(node, tagName + ": " + name);
	}

	private void logError(XmlTreeNode node, String parentName) {
		XmlElement element = node.getStartElement();
		String dataTypeName = element.getAttribute("DATATYPE");
		if (dataTypeName == null) {
			dataTypeName = element.getAttribute("DATATYPE_NAME");//support older versions of XML
		}
		log.appendMsg(element.getLineNumber(),
			"Couldn't create DataType: " + dataTypeName + " in " + parentName);
		Iterator<XmlTreeNode> it = node.getChildren();
		while (it.hasNext()) {
			logError(it.next(), parentName);
		}
	}

	private boolean processDataTypeNode(XmlTreeNode root, boolean firstPass) {
		XmlElement element = root.getStartElement();
		String name = element.getName();

		try {
			printf("Processing %s/%s\n", getCategoryPath(element).toString(), element.getAttribute("NAME"));

			if (name.equals("STRUCTURE")) {
				return processStructure(root, firstPass);
			}
			else if (name.equals("UNION")) {
				return processUnion(root, firstPass);
			}
			else if (name.equals("FUNCTION_DEF")) {
				return processFunctionDef(root, firstPass);
			}
			else if (name.equals("ENUM")) {
				return processEnum(root);
			}
			else if (name.equals("TYPE_DEF")) {
				return processTypeDef(root, firstPass);
			}
			log.appendMsg("Unrecognized datatype tag: " + name);
		}
		catch (Exception e) {
			log.appendException(e);
		}
		return true;
	}

	private boolean processFunctionDef(XmlTreeNode root, boolean firstPass) {
		boolean processedAll = true;
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
		CategoryPath path = getCategoryPath(element);
		FunctionDefinition fd = null;

		if (firstPass) {
			fd = new FunctionDefinitionDataType(path, name);
			fd = (FunctionDefinition) dataManager.addDataType(fd, DataTypeConflictHandler.REPLACE_HANDLER);
			if (!name.equals(fd.getName())) {
				element.setAttribute("NAME", fd.getName());
			}
		}
		else {
			fd = (FunctionDefinition) dataManager.getDataType(path, name);
		}

		String callingConvention = "unknown";
		if (element.hasAttribute("CONVENTION")) {
			callingConvention = element.getAttribute("CONVENTION");
		}
		GenericCallingConvention convention = getCallingConvention(callingConvention);
		if (convention == null)
		{
			throw new IllegalArgumentException("Unknown calling convention '" + convention + "' in function " + path + "/" + name);
		}
		fd.setGenericCallingConvention​(convention);

		XmlTreeNode node = root.getChild("RETURN_TYPE");
		if (node != null) {
			DataType returnType = findDataType(node.getStartElement());
			if (returnType != null) {
				fd.setReturnType(returnType);
				root.deleteChildNode(node);
			}
			else {
				processedAll = false;
			}
		}

		Iterator<XmlTreeNode> it = root.getChildren("PARAMETER");
		while (it.hasNext()) {
			node = it.next();
			String comment = getRegularComment(node);
			element = node.getStartElement();
			DataType dt = findDataType(element);
			if (dt != null) {
				int ordinal = XmlUtilities.parseInt(element.getAttribute("ORDINAL"));
				name = element.getAttribute("NAME");
				int size = dt.getLength();
				if (size == 0) {
					return false;
				}
				if (size < 0) {
					size = element.hasAttribute("SIZE")
							? XmlUtilities.parseInt(element.getAttribute("SIZE"))
							: 4;
				}
				fd.replaceArgument(ordinal, name, dt, comment, SourceType.USER_DEFINED);
				it.remove();
			}
			else {
				processedAll = false;
			}
		}
		return processedAll;
	}

	private boolean processEnum(XmlTreeNode root) {
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
		String comment = getRegularComment(root);
		CategoryPath cp = getCategoryPath(element);
		int size = XmlUtilities.parseInt(element.getAttribute("SIZE"), defaultEnumSize);

		EnumDataType enuum = new EnumDataType(cp, name, size);

		Iterator<XmlTreeNode> it = root.getChildren("ENUM_ENTRY");
		while (it.hasNext()) {
			XmlTreeNode node = it.next();
			XmlElement childElement = node.getStartElement();
			String entryName = childElement.getAttribute("NAME");
			long entryValue = XmlUtilities.parseLong(childElement.getAttribute("VALUE"));
			enuum.add(entryName, entryValue);
		}
		enuum.setDescription(comment);
		dataManager.addDataType(enuum, DataTypeConflictHandler.REPLACE_HANDLER);
		return true;
	}

	private boolean processTypeDef(XmlTreeNode root, boolean firstPass) {
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
		CategoryPath cp = getCategoryPath(element);

		DataType dt = findDataType(element);
		if (dt == null) {
			return false;		// typeDef'd datatype not resolved yet
		}

		int dtSize = dt.getLength();
		int size =
			element.hasAttribute("SIZE") ? XmlUtilities.parseInt(element.getAttribute("SIZE")) : -1;
		if (size != -1 && size != dtSize) {
			log.appendMsg("SIZE=" + element.getAttribute("SIZE") + " specified on type-def " +
				name + " does not agree with length of datatype " + dt.getDisplayName() + " (" +
				dtSize + ")");
		}

		TypeDef td = new TypedefDataType(cp, name, dt);
		try {
			td.setCategoryPath(cp);
		}
		catch (DuplicateNameException e) {
		}

		dataManager.addDataType(td, DataTypeConflictHandler.REPLACE_HANDLER);
		return true;
	}

	private boolean processStructure(XmlTreeNode root, boolean firstPass) {
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
		CategoryPath path = getCategoryPath(element);
		Structure struct = null;
		boolean isVariableLength = false;
		if (element.hasAttribute("VARIABLE_LENGTH")) {
			isVariableLength = XmlUtilities.parseBoolean(element.getAttribute("VARIABLE_LENGTH"));
		}
		if (firstPass) {
			int size = DEFAULT_SIZE;
			if (element.hasAttribute("SIZE")) {
				size = XmlUtilities.parseInt(element.getAttribute("SIZE"));
			}
			String comment = getRegularComment(root);
			struct = new StructureDataType(path, name, size);
			if (comment != null) {
				struct.setDescription(comment);
			}
			struct = (Structure) dataManager.addDataType(struct, DataTypeConflictHandler.REPLACE_HANDLER);
			if (!struct.getName().equals(name)) {
				element.setAttribute("NAME", struct.getName());
			}
		}
		else {
			struct = (Structure) dataManager.getDataType(path, name);
		}
		return processStructMembers(root, struct, firstPass, isVariableLength);
	}

	private boolean processUnion(XmlTreeNode root, boolean firstPass) {
		XmlElement element = root.getStartElement();
		String name = element.getAttribute("NAME");
		CategoryPath path = getCategoryPath(element);
		Union union = null;
		if (firstPass) {
			String comment = getRegularComment(root);
			union = new UnionDataType(path, name);
			if (comment != null) {
				union.setDescription(comment);
			}
			union = (Union) dataManager.addDataType(union, DataTypeConflictHandler.REPLACE_HANDLER);
			if (!union.getName().equals(name)) {
				element.setAttribute("NAME", union.getName());
			}
		}
		else {
			union = (Union) dataManager.getDataType(path, name);
		}
		return processUnionMembers(root, union, firstPass);
	}

	private String getRegularComment(XmlTreeNode root) {
		XmlTreeNode node = root.getChild("REGULAR_CMT");
		if (node != null) {
			return node.getEndElement().getText();
		}
		return null;
	}

	private boolean processStructMembers(XmlTreeNode root, Structure struct, boolean firstPass,
			boolean isVariableLength) {
		boolean processedAll = true;
		Iterator<XmlTreeNode> iter = root.getChildren("MEMBER");
		while (iter.hasNext()) {
			XmlTreeNode child = iter.next();
			XmlElement childElem = child.getStartElement();
			int offset = XmlUtilities.parseInt(childElem.getAttribute("OFFSET"));
			DataType memberDT = findDataType(childElem);
			if (memberDT != null) {
				if (memberDT instanceof TerminatedStringDataType) {
					// TerminatedCStringDataType no longer allowed in composites
					memberDT = new StringDataType();
				}
				else if (memberDT instanceof TerminatedUnicodeDataType) {
					// TerminatedUnicodeStringDataType no longer allowed in composites
					memberDT = new UnicodeDataType();
				}
				if (memberDT.getLength() == 0) {
					return false;
				}
				String memberName = childElem.getAttribute("NAME");
				String memberComment = getRegularComment(child);
				int dtSize = memberDT.getLength();
				int size = childElem.hasAttribute("SIZE")
						? XmlUtilities.parseInt(childElem.getAttribute("SIZE"))
						: -1;
				if (dtSize <= 0) {
					dtSize = size;
					if (dtSize < 0) {
						log.appendMsg("No SIZE specified for member at offset " + offset +
							" of structure " + struct.getDisplayName());
						dtSize = DEFAULT_SIZE;
					}
				}

				// NOTE: Size consistency checking was removed since some types are filled-out
				// lazily and may not have there ultimate size at this point.

				DataTypeComponent member = null;
				if (isVariableLength && offset >= struct.getLength()) {
					member = struct.add(memberDT, dtSize, memberName, memberComment);
				}
				else {
					member =
						struct.replaceAtOffset(offset, memberDT, dtSize, memberName, memberComment);
				}
				//processSettings(child, member.getDefaultSettings());

				iter.remove();
			}
			else {
				processedAll = false;
			}
		}
		return processedAll;
	}


	private boolean processUnionMembers(XmlTreeNode root, Union union, boolean firstPass) {
		boolean processedAll = true;
		Iterator<XmlTreeNode> iter = root.getChildren("MEMBER");
		while (iter.hasNext()) {
			XmlTreeNode child = iter.next();
			XmlElement childElem = child.getStartElement();
			DataType memberDT = findDataType(childElem);
			if (memberDT != null) {
				String memberName = childElem.getAttribute("NAME");
				String memberComment = getRegularComment(child);
				int dtSize = memberDT.getLength();
				int size = childElem.hasAttribute("SIZE")
						? XmlUtilities.parseInt(childElem.getAttribute("SIZE"))
						: -1;
				if (dtSize <= 0) {
					dtSize = size;
					if (dtSize < 0) {
						log.appendMsg("No SIZE specified for member datatype " +
							memberDT.getDisplayName() + " of union " + union.getDisplayName());
						dtSize = DEFAULT_SIZE;
					}
				}
				else if (size != -1 && size != dtSize) {
					log.appendMsg("SIZE=" + childElem.getAttribute("SIZE") +
						" specified for member datatype " + memberDT.getDisplayName() +
						" of union " + union.getDisplayName() +
						" does not agree with length of datatype (" + dtSize + ")");
				}
				union.add(memberDT, dtSize, memberName, memberComment);
				iter.remove();
			}
			else {
				processedAll = false;
			}
		}
		return processedAll;
	}

	private DataType findDataType(XmlElement element) {
		String dtName = element.getAttribute("DATATYPE");
		if (dtName == null) {
			dtName = element.getAttribute("DATATYPE_NAME");//support older versions of XML
		}
		CategoryPath cp = new CategoryPath(element.getAttribute("DATATYPE_NAMESPACE"));
		int size =
			element.hasAttribute("SIZE") ? XmlUtilities.parseInt(element.getAttribute("SIZE")) : -1;
		DataType dt = dtParser.parseDataType(dtName, cp, size);
		if (dt == null && addForeignTypedefIfNeeded(dtName)) {
			dt = dtParser.parseDataType(dtName, cp, size);
		}
		return dt;

	}

	private boolean addForeignTypedefIfNeeded(String dtName) {
		int ptrIndex = dtName.indexOf('*');
		int index = dtName.indexOf('[');
		String baseName = dtName.trim();
		if (index < 0 || index > ptrIndex) {
			index = ptrIndex;
		}
		if (index > 0) {
			baseName = dtName.substring(0, index).trim();
		}
		DataType ourType = foreignTypedefs.get(baseName);
		if (ourType != null && dataManager.getDataType("/" + baseName) == null) {
			TypedefDataType newTypedef = new TypedefDataType(baseName, ourType);
			dataManager.resolve(newTypedef, null);
			return true;
		}
		return false;
	}

	/**
	 * DtParser
	 */
	class DtParser {

		private DataTypeManager dtManager;
		private DataTypeParser parser;

		DtParser(DataTypeManager dtManager) {
			this.dtManager = dtManager;
			this.parser = new DataTypeParser(dtManager, dtManager, null, DataTypeParser.AllowedDataTypes.DYNAMIC);
		}

		/**
		 * Parse the specified dtName within the specified category.
		 * @param dtName
		 * @param category
		 * @param size optional data-type size, or -1 for unspecified
		 * @return data-type if found, or null if not found
		 */
		DataType parseDataType(String dtName, CategoryPath category, int size) {
			DataType dt;
			try {
				dt = parser.parse(dtName, category);
			}
			catch (InvalidDataTypeException | CancelledException e) {
				return null;
			}
			if (size > 0 && size != dt.getLength()) {
				dt = adjustPointerDataTypes(size, dt);
			}
			return dt;
		}

		/**
		 * Adjust pointer data-types based upon specified size which may not be 
		 * factored into pointer specification (e.g., void *32).
		 * @param size
		 * @param dt
		 * @return adjusted data-type
		 */
		private DataType adjustPointerDataTypes(int size, DataType dt) {
			if (dt instanceof Pointer) {
				Pointer p = (Pointer) dt;
				dt = new PointerDataType(p.getDataType(), size, dtManager);
			}
			else if (dt instanceof Array && ((Array) dt).getDataType() instanceof Pointer) {
	// TODO: does not handle multi-dimensional pointer arrays
				Array array = (Array) dt;
				DataType pointerDt = ((Pointer) array.getDataType()).getDataType();
				int pointerSize = size / array.getNumElements();
				DataType pointer = new PointerDataType(pointerDt, pointerSize, dtManager);
				dt = new ArrayDataType(pointer, array.getNumElements(), pointerSize, dtManager);
			}
			return dt;
		}
	}
}
