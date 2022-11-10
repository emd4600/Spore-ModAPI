/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once


#include <Spore\MathUtils.h>
#include <Spore\ArgScript\Line.h>
#include <Spore\ArgScript\Lexer.h>
#include <Spore\ArgScript\ASDeclarations.h>
#include <Spore\IO\IStream.h>

#include <EASTL\hash_map.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\string.h>

#define FormatParserPtr eastl::intrusive_ptr<ArgScript::FormatParser>

namespace ArgScript
{
	class FormatParser;

	typedef eastl::function<void(const Line&, FormatParser*)> ParseLine_t;
	typedef eastl::function<const char*(DescriptionMode)> GetDescription_t;
	typedef eastl::function<void(FormatParser*, void*)> SetData_t;

	class ITraceStream
	{
	public:
		virtual ~ITraceStream() = 0;
		virtual int AddRef() = 0;
		virtual int Release() = 0;
		//TODO: ?
	};

	/// 
	/// This class contains all the parsers necessary to process a certain ArgScript format. Check ArgScript for more information.
	///
	class FormatParser
	{
	public:
		/* 00h */	virtual int AddRef();
		/* 04h */	virtual int Release();

		/* 08h */	virtual bool Initialize();
		/* 0Ch */	virtual bool Dispose();

		///
		/// Sets the object that is being parsed in this format parser. Commands and blocks can use this data object
		/// to set all the information parsed somewhere. The data can be of any type, since it won't be used directly by any
		/// default implementation.
		/// @param pData A pointer to the object.
		///
		/* 10h */	virtual void SetData(void* pData);

		///
		/// Adds the given IParser to this format; it will be used when a line with the specified keyword is found.
		/// The IParser::SetData() method will be called, passing the current data object of the format parser as a parameter.
		/// @param pKeyword The keyword that is used to call this parser. It is not case sensitive.
		/// @param pParser
		///
		/* 14h */	virtual void AddParser(const char* pKeyword, IParser* pParser);

		void AddParser(const char* pKeyword, ParseLine_t pParseLine);
		void AddParser(const char* pKeyword, ParseLine_t pParseLine, GetDescription_t pGetDescription);
		void AddParser(const char* pKeyword, ParseLine_t pParseLine, SetData_t pSetData);

		///
		/// Removes the IParser mapped to the specified keyword.
		/// @param pKeyword The keyword that is used to call the parser. It is not case sensitive.
		/// @returns True if the parser was removed, false if no parser was mapped to that keyword.
		///
		/* 18h */	virtual bool RemoveParser(const char* pKeyword);

		///
		/// Removes the specified IParser from this format.
		/// @param pParser The IParser to remove.
		/// @returns True if the parser was removed, false if no parser was mapped.
		///
		/* 1Ch */	virtual bool RemoveParserByObject(IParser* pParser);

		///
		/// Returns the IParser mapped to the given keyword, or nullptr if no parser is mapped to that keyword.
		/// @param pKeyword The keyword used to call the parser.
		///
		/* 20h */	virtual IParser* GetParser(const char* pKeyword) const;

		/* 24h */	virtual void SetFlag(int flag, bool bValue);

		///
		/// Sets the minimum and maximum version that the script can have. The script version is specified using
		/// the 'version' command; if the version is out of range, an exception will be thrown when parsing that command.
		///
		/* 28h */	virtual void SetVersionRange(int nMinVersion, int nMaxVerison);

		///
		/// Gets the version of the current script.
		///
		/* 2Ch */	virtual int GetVersion() const;

		/* 30h */	virtual void func30h();
		///
		/// Closes all blocks and special blocks and exits the current scope. This will call IBlock::OnBlockEnd() on all
		/// blocks and ISpecialBlock::OnEnd() on all special blocks.
		///
		/* 34h */	virtual void Close(bool = false);

		///
		/// Reads an ArgScript file in the specified physical path (that is, in the disk).
		/// @param pPath The file path to the file to process.
		/// @throws ArgScriptException If there is a problem while reading or the format is incorrect.
		///
		/* 38h */	virtual void ProcessFile(const char* pPath);

		///
		/// Reads an ArgScript file from the IStream given.
		/// @param pInputStream The input IStream with the data to process.
		/// @throws ArgScriptException If there is a problem while reading or the format is incorrect.
		///
		/* 3Ch */	virtual void ProcessStream(IO::IStream* pInputStream);

		///
		/// Converts the given eastl::string into a ArgScript::Line and it process it using the correct IParser,
		/// determined by the keyword (the first word in the line). If the keyword is not mapped to any parser,
		/// an exception will be thrown.
		/// @param pString The input line eastl::string.
		/// @throws ArgScriptException If the keyword is not mapped.
		/// @throws ArgScriptException If the format is not correct.
		///
		/* 40h */	virtual void ProcessLine(const char* pString);

		///
		/// Creates an instance of a definition of the given name using the specified parameters. Definitions are pieces of text
		/// with parameters that can be replaced; definitions can be created using the 'define' keyword.
		/// @param pName The name of the definition.
		/// @param argumentsLine The line that contains the arguments (separated by spaces, not commas)
		/// @throws ArgScriptException If no definition with that name exists.
		/// @throws ArgScriptException If the number of arguments is not correct.
		/// @throws ArgScriptException If a keyword of the code in the definition is not mapped.
		/// @throws ArgScriptException If the format is not correct.
		///
		/* 44h */	virtual void CreateDefinition(const char* pName, const Line& argumentsLine);

		///
		/// Reads an ArgScript file from the file path given, without throwing any exceptions. 
		/// This calls ProcessFile(const char*) inside a try-catch block.
		/// @param pFilePath The file path to the file to process.
		/// @returns True if there were no exceptions, false otherwise.
		///
		/* 48h */	virtual bool ProcessFileSafe(const char* pFilePath);

		///
		/// Reads an ArgScript file from the IStream given, without throwing any exceptions. 
		/// This calls ProcessStream(IO::IStream*) inside a try-catch block.
		/// @param pStream The input IStream with the data to process.
		/// @returns True if there were no exceptions, false otherwise.
		///
		/* 4Ch */	virtual bool ProcessStreamSafe(IO::IStream* pStream);

		///
		/// Converts the given eastl::string into a ArgScript::Line and it process it using the correct IParser,
		/// determined by the keyword (the first word in the line), without throwing any exceptions.
		/// This calls ProcessLine(const char*) inside a try-catch block.
		/// @param pString The input line eastl::string.
		/// @returns True if no exceptions were thrown, false otherwise.
		///
		/* 50h */	virtual bool ProcessLineSafe(const char* pString);

		///
		/// Creates an instance of a definition of the given name using the specified parameters. Definitions are pieces of text
		/// with parameters that can be replaced; definitions can be created using the 'define' keyword.
		/// This calls ProcessDefinition() inside a try-catch block, so that no exceptions are thrown.
		/// @param pName The name of the definition.
		/// @param argumentsLine The line that contains the arguments (separated by spaces, not commas)
		/// @returns True if no exceptions were thrown, false otherwise.
		///
		/* 54h */	virtual bool CreateDefinitionSafe(const char* pName, const Line& argumentsLine);

		/* 58h */	virtual int func58h(); 
		/* 5Ch */	virtual int func5Ch();
		/* 60h */	virtual int func60h(int, int);

		///
		/// Tells whether this format parser has a parser assigned to the given keyword.
		/// @param pName The keyword mapped to the parser (not case sensitive).
		/// @returns True if there is an IParser with this name.
		///
		/* 64h */	virtual int HasParser(const char* pName) const;

		///
		/// Tells whether this format parser has a definition with the given name.
		/// @param pName The name of the definition (not case sensitive).
		/// @returns True if there is a definition with this name.
		///
		/* 68h */	virtual bool HasDefinition(const char* pName) const;

		///
		/// Sets the value of a variable. The value is always a eastl::string, which can contain other variables, referencing them with
		/// $ (and usually {} too; for example, to get the value of variable 'version', one would use '${version}' or '$version').
		/// This variable will be added to the current scope.
		/// @param pName The name of the variable.
		/// @param pValue The c-eastl::string value of the variable.
		///
		/* 6Ch */	virtual void SetVariable(const char* pName, const char* pValue);

		///
		/// Returns the eastl::string value of the specified variable, or nullptr if the variable is not mapped.
		/// The variable is searched within the current scope and its parent scopes, unless another scope is specified (for example, Intel:card1 would
		/// search 'card1' inside the 'Intel' scope).
		/// If the name is prefixed with ':', the variable will be searched as a global variable first.
		/// @param pVariableName The name of the variable.
		///
		/* 70h */	virtual const char* GetVariable(const char* pVariableName);

		///
		/// Sets the value of a global variable. The value is always a eastl::string, which can contain other variables, referencing them with
		/// $ (and usually {} too; for example, to get the value of variable 'version', one would use '${version}' or '$version').
		/// To access global variables, their name must be prefixed with ':'. For example, to get the global variable 'build', 
		/// one would use '$:build'.
		/// @param pName The name of the variable.
		/// @param pValue The c-eastl::string value of the variable.
		///
		/* 74h */	virtual void SetGlobalVariable(const char* pName, const char* pValue);

		/* 78h */	virtual void func78h(int);

		///
		/// Starts a scope with the given name. The scope will be inside the current scope. All the variables inside a scope
		/// can only be used within that scope; to use them from outside, they must be referenced using ':'. For example,
		/// to get the variable 'card1' inside the scope 'Intel', use 'Intel:card1'.
		/// @param pName The name of the scope.
		///
		/* 7Ch */	virtual void StartScope(const char* pName);

		///
		/// Ends the current scope.
		///
		/* 80h */	virtual void EndScope();

		///
		/// Removes all the variables definitions from the given namespace scope. The scope name must finish with ':' to be valid.
		/// @param pScope The name of the scope.
		/// @throws ArgScriptException If the name of the scope is not valid.
		///
		/* 84h */	virtual void PurgeScope(const char* pScope);

		///
		/// Returns the eastl::string used by the current scope, for example, 'App:'. The eastl::string is made by 
		/// appending ':' after all the scope parents and the scope name. Variable names are the result of
		/// appending this eastl::string with the variable name.
		///
		/* 88h */	virtual const char* GetCurrentScope() const;

		///
		/// Adds the given block to this parser. This will allow the block to be notified when the 'end' keyword is reached.
		/// Blocks must do this on the IBlock::ParseLine() method in order to work properly. This does not start a new scope.
		/// @param pBlock The block that is currently being parsed.
		///
		/* 8Ch */	virtual void AddBlock(IBlock* pBlock);

		///
		/// Adds the given special block to this parser; the block will end when the specified keyword is found.
		/// Special blocks can process each line inside the block individually; for more information, check ISpecialBlock.
		/// @param pSpecialBlock The special block.
		/// @param pEndKeyword The keyword that ends the block.
		///
		/* 90h */	virtual int AddSpecialBlock(ISpecialBlock* pSpecialBlock, const char* pEndKeyword);

		///
		/// Converts the specified eastl::string representation of a logical expression to its bool equivalent.
		/// Values 'true', 'on' and '1' are evaluated as true, and 'false', 'off' and '0' are evaluated as false.
		/// Logical operators 'or', 'and', 'not' are allowed, as well as the use of boolean functions.
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the boolean expression is not valid.
		///
		/* 94h */	virtual bool ParseBool(const char* pString) const;

		///
		/// Converts the specified eastl::string representation of a real number expression to its float equivalent.
		/// Numerical expressions like + - * /, % (modulus), ^ (power) can be used, as well as the 'pi' constant.
		/// These functions are also supported:
		/// - sqrt(x): Returns the square root of the x.
		/// - exp(x): Returns e^x, where e is Euler's number.
		/// - log(x): Returns the natural logarithm (base e) of x.
		/// - abs(x): Returns the absolute value of x, that is, the value if no sign.
		/// - sin(x), cos(x), tan(x), asin(x), acos(x), atan(x): Trigonometical functions that work in radians.
		/// - sind(x), cosd(x), tand(x), dasin(x), dacos(x), datan(x): Trigonometical functions that work in degrees.
		/// - floor(x): Returns the largest integer less than or equal to x.
		/// - ceil(x): Returns the smallest integer greater than or equal to x.
		/// - sqr(x): Returns x^2.
		/// - pow(x, y): Returns x to the power of y, x^y.
		/// - atan2(x, y): Returns the arctangent of the quotient of its arguments, in radians.
		/// - datan2(x, y): Returns the arctangent of the quotient of its arguments, in degrees.
		/// - Any other function mapped in the lexer.
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid.
		///
		/* 98h */	virtual float ParseFloat(const char* pString) const;

		///
		/// Converts the specified eastl::string representation of an integer number expression to its int equivalent.
		/// The integer operator + - * / % ^ can be used, as well as some functions from ParseFloat(const char*):
		/// 'abs', 'floor', 'ceil', 'sqr' and any function mapped in the lexer. The function 'round(x)' which rounds 
		/// the real number x to the closest integer is also supported.
		/// All the supported functions can take real expressions (the ones used in ParseFloat(const char*)).
		/// Hexadecimal numbers, prefixed by 0x, are also supported.
		/// 'true' and 'on' are interpreted as 1, 'false' and 'off' are interpreted as 0.
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the integer expression is not valid.
		/// 
		/* 9Ch */	virtual int	ParseInt(const char* pString) const;

		///
		/// Same as ParseInt(const char*).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the integer expression is not valid.
		///
		/* A0h */	virtual unsigned int ParseUInt(const char* pString) const;

		///
		/// Parses two real numbers separated with commas and puts them into a Vector2. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - eastl::string '3.4, sqr(4)' will return Vector2(3.4, 16).
		/// - eastl::string '8' will return Vector2(8.0, 8.0).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid.
		///
		/* A4h */	virtual Math::Vector2 ParseVector2(const char* pString) const;

		///
		/// Parses three real numbers separated with commas and puts them into a Vector3. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - eastl::string '3.4, sqr(4), 1.0 + 2' will return Vector3(3.4, 16.0, 3.0).
		/// - eastl::string '8' will return Vector3(8.0, 8.0, 8.0).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid or only two numbers are specified.
		///
		/* A8h */	virtual Math::Vector3 ParseVector3(const char* pString) const;

		///
		/// Parses four real numbers separated with commas and puts them into a Vector4. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - eastl::string '3.4, sqr(4), 1.0 + 2, 0' will return Vector4(3.4, 16.0, 3.0, 0.0).
		/// - eastl::string '8' will return Vector4(8.0, 8.0, 8.0, 8.0).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid or only two or three numbers are specified.
		///
		/* ACh */	virtual Math::Vector4 ParseVector4(const char* pString) const;

		///
		/// Parses three real numbers separated with commas and puts them into a ColorRGB. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the color values will be filled with that number.
		/// This is equivalent to ParseVector3(const char*).
		/// Color numbers are usually in the range [0.0, 1.0].
		///
		/// Examples:
		/// - eastl::string '0.4, sqr(0.5), 0.5 * 2' will return ColorRGB(0.4, 0.25, 1.0).
		/// - eastl::string '0.2' will return ColorRGB(0.2, 0.2, 0.2).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid or only two numbers are specified.
		///
		/* B0h */	virtual Math::ColorRGB ParseColorRGB(const char* pString) const;

		///
		/// Parses three or four real numbers separated with commas and puts them into a ColorRGBA. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only three numbers are specified, the alpha value will be assigned to 1.0.
		/// Color numbers are usually in the range [0.0, 1.0].
		///
		/// Examples:
		/// - eastl::string '0.4, sqr(0.5), 0.5 * 2' will return ColorRGB(0.4, 0.25, 1.0, 1.0).
		/// @param pString The eastl::string to parse.
		/// @throws ArgScriptException If the real expression is not valid or only one or two numbers are specified.
		///
		/* B4h */	virtual Math::ColorRGBA ParseColorRGBA(const char* pString) const;

		///
		/// Returns the Lexer instance of this format parser.
		///
		/* B8h */	virtual Lexer& GetLexer();
		
		///
		/// Sets the ITraceStream where the text can be output from this ArgScript instance.
		/// @param pTraceStream
		///
		/* BCh */	virtual void SetTraceStream(ITraceStream* pTraceStream);

		/* C0h */	virtual void funcC0h(int);

		///
		/// Gets the ITraceStream where the text can be output from this ArgScript instance.
		///
		/* C4h */	virtual ITraceStream* GetTraceStream();

		/* C8h */	virtual int funcC8h();

		/* CCh */	virtual ~FormatParser();


	protected:
		/* 04h */	uint32_t field_04;  // 8BA83ACB
		/* 08h */	int mnRefCount;
		/* 0Ch */	bool field_0C;
		/* 10h */	int mnFlags;
		/* 14h */	eastl::intrusive_ptr<ITraceStream> mpTraceStream;
		/* 18h */	int field_18;
		/* 1Ch */	int mnMinVersion;  // -1
		/* 20h */	int mnMaxVersion;  // -1
		/* 24h */	int mnVersion;  // -1
		/* 28h */	void* mpData;
		/* 2Ch */	eastl::hash_map<eastl::string, eastl::intrusive_ptr<IParser>> mParsers;
		/* 4Ch */	Lexer mLexer;
		/* 6Ch */	eastl::hash_map<eastl::string, int> mDefinitions;
		/* 8Ch */	eastl::hash_map<eastl::string, eastl::string> mVariables;
		/* ACh */	eastl::hash_map<eastl::string, eastl::string> mGlobalVariables;
		/* CCh */	int field_CC;
		/* D0h */	eastl::string field_D0;
		/* E0h */	eastl::string field_E0;
		/* F0h */	int field_F0;
		/* F4h */	eastl::string field_F4;
		/* 104h */	int field_104;
		/* 108h */	eastl::vector<IBlock*> mBlocks;
		/* 11Ch */	eastl::vector<eastl::pair<ISpecialBlock*, const char*>> mSpecialBlocks;
		/* 130h */	eastl::string mCurrentScope;  // the eastl::string of the current scope, for example, 'App:'
		/* 140h */	eastl::vector<size_t> mScopeLenghts;  // the length each scope uses in the mCurrentScope eastl::string
		/* 154h */	eastl::string field_154;
		/* 164h */	bool field_164;
		/* 168h */	int field_168;
		/* 16Ch */	ArgScript::Line mTempLine;
		/* 1B0h */	eastl::string mTempString;  // used when adding parsers
	};
	ASSERT_SIZE(FormatParser, 0x1C0);

	typedef void* (*PrintF_ptr)(FormatParser* object, const char* str, ...);

	///
	/// A function that prints a formatted text into an ArgScript stream. This uses the same format as the C printf function.
	///
	extern MODAPI PrintF_ptr PrintF;

	///
	/// Creates a new ArgScript stream, which is an instance of FormatParser. 
	///
	extern FormatParser* CreateStream();


	namespace Addresses(FormatParser)
	{
		// DeclareAddress(ReplaceVariables);

		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(SetData);
		DeclareAddress(AddParser);
		DeclareAddress(RemoveParser);
		DeclareAddress(RemoveParserByObject);
		DeclareAddress(GetParser);
		DeclareAddress(SetFlag);
		DeclareAddress(SetVersionRange);
		DeclareAddress(GetVersion);
		DeclareAddress(func30h);
		DeclareAddress(Close);
		DeclareAddress(ProcessFile);
		DeclareAddress(ProcessStream);
		DeclareAddress(ProcessLine);
		DeclareAddress(CreateDefinition);
		DeclareAddress(ProcessFileSafe);
		DeclareAddress(ProcessStreamSafe);
		DeclareAddress(ProcessLineSafe);
		DeclareAddress(CreateDefinitionSafe);
		DeclareAddress(func58h);
		DeclareAddress(func5Ch);
		DeclareAddress(func60h);
		DeclareAddress(HasParser);
		DeclareAddress(HasDefinition);
		DeclareAddress(SetVariable);
		DeclareAddress(GetVariable);
		DeclareAddress(SetGlobalVariable);
		DeclareAddress(func78h);
		DeclareAddress(StartScope);
		DeclareAddress(EndScope);
		DeclareAddress(PurgeScope);
		DeclareAddress(GetCurrentScope);
		DeclareAddress(AddBlock);
		DeclareAddress(AddSpecialBlock);
		DeclareAddress(ParseBool);
		DeclareAddress(ParseFloat);
		DeclareAddress(ParseInt);
		DeclareAddress(ParseUInt);
		DeclareAddress(ParseVector2);
		DeclareAddress(ParseVector3);
		DeclareAddress(ParseVector4);
		DeclareAddress(ParseColorRGB);
		DeclareAddress(ParseColorRGBA);
		DeclareAddress(GetLexer);
		DeclareAddress(SetTraceStream);
		DeclareAddress(funcC0h);
		DeclareAddress(GetTraceStream);
		DeclareAddress(funcC8h);
	}
}

namespace Addresses(ArgScript)
{
	DeclareAddress(CreateStream);
}

