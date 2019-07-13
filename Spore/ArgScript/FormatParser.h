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

using namespace eastl;

namespace ArgScript
{
	class FormatParser;

	typedef function<void(const Line&, FormatParser*)> ParseLine_t;
	typedef function<const char*(DescriptionMode)> GetDescription_t;
	typedef function<void(FormatParser*, void*)> SetData_t;

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
		/// Converts the given string into a ArgScript::Line and it process it using the correct IParser,
		/// determined by the keyword (the first word in the line). If the keyword is not mapped to any parser,
		/// an exception will be thrown.
		/// @param pString The input line string.
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
		/// @param pInputStream The input IStream with the data to process.
		/// @returns True if there were no exceptions, false otherwise.
		///
		/* 4Ch */	virtual bool ProcessStreamSafe(IO::IStream* pStream);

		///
		/// Converts the given string into a ArgScript::Line and it process it using the correct IParser,
		/// determined by the keyword (the first word in the line), without throwing any exceptions.
		/// This calls ProcessLine(const char*) inside a try-catch block.
		/// @param pString The input line string.
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
		/// Sets the value of a variable. The value is always a string, which can contain other variables, referencing them with
		/// $ (and usually {} too; for example, to get the value of variable 'version', one would use '${version}' or '$version').
		/// This variable will be added to the current scope.
		/// @param pName The name of the variable.
		/// @param pValue The c-string value of the variable.
		///
		/* 6Ch */	virtual void SetVariable(const char* pName, const char* pValue);

		///
		/// Returns the string value of the specified variable, or nullptr if the variable is not mapped.
		/// The variable is searched within the current scope and its parent scopes, unless another scope is specified (for example, Intel:card1 would
		/// search 'card1' inside the 'Intel' scope).
		/// If the name is prefixed with ':', the variable will be searched as a global variable first.
		/// @param pVariableName The name of the variable.
		///
		/* 70h */	virtual const char* GetVariable(const char* pVariableName);

		///
		/// Sets the value of a global variable. The value is always a string, which can contain other variables, referencing them with
		/// $ (and usually {} too; for example, to get the value of variable 'version', one would use '${version}' or '$version').
		/// To access global variables, their name must be prefixed with ':'. For example, to get the global variable 'build', 
		/// one would use '$:build'.
		/// @param pName The name of the variable.
		/// @param pValue The c-string value of the variable.
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
		/// @param pName The name of the variable.
		/// @throws ArgScriptException If the name of the scope is not valid.
		///
		/* 84h */	virtual void PurgeScope(const char* pScope);

		///
		/// Returns the string used by the current scope, for example, 'App:'. The string is made by 
		/// appending ':' after all the scope parents and the scope name. Variable names are the result of
		/// appending this string with the variable name.
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
		/// Converts the specified string representation of a logical expression to its bool equivalent.
		/// Values 'true', 'on' and '1' are evaluated as true, and 'false', 'off' and '0' are evaluated as false.
		/// Logical operators 'or', 'and', 'not' are allowed, as well as the use of boolean functions.
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the boolean expression is not valid.
		///
		/* 94h */	virtual bool ParseBool(const char* pString) const;

		///
		/// Converts the specified string representation of a real number expression to its float equivalent.
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
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the real expression is not valid.
		///
		/* 98h */	virtual float ParseFloat(const char* pString) const;

		///
		/// Converts the specified string representation of an integer number expression to its int equivalent.
		/// The integer operator + - * / % ^ can be used, as well as some functions from ParseFloat(const char*):
		/// 'abs', 'floor', 'ceil', 'sqr' and any function mapped in the lexer. The function 'round(x)' which rounds 
		/// the real number x to the closest integer is also supported.
		/// All the supported functions can take real expressions (the ones used in ParseFloat(const char*)).
		/// Hexadecimal numbers, prefixed by 0x, are also supported.
		/// 'true' and 'on' are interpreted as 1, 'false' and 'off' are interpreted as 0.
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the integer expression is not valid.
		/// 
		/* 9Ch */	virtual int	ParseInt(const char* pString) const;

		///
		/// Same as ParseInt(const char*).
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the integer expression is not valid.
		///
		/* A0h */	virtual unsigned int ParseUInt(const char* pString) const;

		///
		/// Parses two real numbers separated with commas and puts them into a Vector2. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - string '3.4, sqr(4)' will return Vector2(3.4, 16).
		/// - string '8' will return Vector2(8.0, 8.0).
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the real expression is not valid.
		///
		/* A4h */	virtual Math::Vector2 ParseVector2(const char* pString) const;

		///
		/// Parses three real numbers separated with commas and puts them into a Vector3. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - string '3.4, sqr(4), 1.0 + 2' will return Vector3(3.4, 16.0, 3.0).
		/// - string '8' will return Vector3(8.0, 8.0, 8.0).
		/// @param pString The string to parse.
		/// @throws ArgScriptException If the real expression is not valid or only two numbers are specified.
		///
		/* A8h */	virtual Math::Vector3 ParseVector3(const char* pString) const;

		///
		/// Parses four real numbers separated with commas and puts them into a Vector4. 
		/// The numbers are parsed using the ParseFloat(const char*) function.
		/// If only one number is specified, the vector will be filled with that number.
		///
		/// Examples:
		/// - string '3.4, sqr(4), 1.0 + 2, 0' will return Vector4(3.4, 16.0, 3.0, 0.0).
		/// - string '8' will return Vector4(8.0, 8.0, 8.0, 8.0).
		/// @param pString The string to parse.
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
		/// - string '0.4, sqr(0.5), 0.5 * 2' will return ColorRGB(0.4, 0.25, 1.0).
		/// - string '0.2' will return ColorRGB(0.2, 0.2, 0.2).
		/// @param pString The string to parse.
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
		/// - string '0.4, sqr(0.5), 0.5 * 2' will return ColorRGB(0.4, 0.25, 1.0, 1.0).
		/// @param pString The string to parse.
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
		/* 14h */	intrusive_ptr<ITraceStream> mpTraceStream;
		/* 18h */	int field_18;
		/* 1Ch */	int mnMinVersion;  // -1
		/* 20h */	int mnMaxVersion;  // -1
		/* 24h */	int mnVersion;  // -1
		/* 28h */	void* mpData;
		/* 2Ch */	hash_map<string, intrusive_ptr<IParser>> mParsers;
		/* 4Ch */	Lexer mLexer;
		/* 6Ch */	hash_map<string, int> mDefinitions;
		/* 8Ch */	hash_map<string, string> mVariables;
		/* ACh */	hash_map<string, string> mGlobalVariables;
		/* CCh */	int field_CC;
		/* D0h */	string field_D0;
		/* E0h */	string field_E0;
		/* F0h */	int field_F0;
		/* F4h */	string field_F4;
		/* 104h */	int field_104;
		/* 108h */	vector<IBlock*> mBlocks;
		/* 11Ch */	vector<pair<ISpecialBlock*, const char*>> mSpecialBlocks;
		/* 130h */	string mCurrentScope;  // the string of the current scope, for example, 'App:'
		/* 140h */	vector<size_t> mScopeLenghts;  // the length each scope uses in the mCurrentScope string
		/* 154h */	string field_154;
		/* 164h */	bool field_164;
		/* 168h */	int field_168;
		/* 16Ch */	ArgScript::Line mTempLine;
		/* 1B0h */	string mTempString;  // used when adding parsers
	};

	typedef void* (*PrintF_ptr)(FormatParser* object, const char* str, ...);

	// this will be defined in ModAPI\MainUtilities.cpp
	///
	/// A function that prints a formatted text into an ArgScript stream. This uses the same format as the C printf function.
	///
	extern PrintF_ptr PrintF;

	///
	/// Creates a new ArgScript stream, which is an instance of FormatParser. 
	///
	extern FormatParser* CreateStream();


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(FormatParser) == 0x1C0, "sizeof(FormatParser) != 1C0h");

	namespace Addresses(ArgScript)
	{
		DeclareAddress(CreateStream, SelectAddress(0x841190, 0x840920, 0x8409A0));
	}

	namespace Addresses(FormatParser)
	{
		// DeclareAddress(ReplaceVariables, SelectAddress(0x843F10, , ));

		DeclareAddress(AddRef, SelectAddress(0x83D030, 0x83F620, 0x83F6A0));
		DeclareAddress(Release, SelectAddress(0x841A80, 0x841210, 0x841290));
		DeclareAddress(Initialize, SelectAddress(0x845FB0, 0x845710, 0x845790));
		DeclareAddress(Dispose, SelectAddress(0x847680, 0x846DE0, 0x846E60));
		DeclareAddress(SetData, SelectAddress(0x841AC0, 0xA6FE50, 0xA6FE70));
		DeclareAddress(AddParser, SelectAddress(0x8468D0, 0x846030, 0x8460B0));
		DeclareAddress(RemoveParser, SelectAddress(0x8469C0, 0x846120, 0x8461A0));
		DeclareAddress(RemoveParserByObject, SelectAddress(0x846940, 0x8460A0, 0x846120));
		DeclareAddress(GetParser, SelectAddress(0x8434D0, 0x842C40, 0x842CC0));
		DeclareAddress(SetFlag, SelectAddress(0x841D50, 0x8414C0, 0x841540));
		DeclareAddress(SetVersionRange, SelectAddress(0x841AD0, 0x841250, 0x8412D0));
		DeclareAddress(GetVersion, SelectAddress(0x804E30, 0xFF3480, 0xFF3480));
		DeclareAddress(func30h, SelectAddress(0x8477E0, 0x846F40, 0x846FC0));
		DeclareAddress(Close, SelectAddress(0x845780, 0x844EF0, 0x844F70));
		DeclareAddress(ProcessFile, SelectAddress(0x843520, 0x842C90, 0x842D10));
		DeclareAddress(ProcessStream, SelectAddress(0x843810, 0x842F80, 0x843000));
		DeclareAddress(ProcessLine, SelectAddress(0x844990, 0x844100, 0x844180));
		DeclareAddress(CreateDefinition, SelectAddress(0x845870, 0x844FE0, 0x845060));
		DeclareAddress(ProcessFileSafe, SelectAddress(0x841AF0, 0x841270, 0x8412F0));
		DeclareAddress(ProcessStreamSafe, SelectAddress(0x841B60, 0x8412E0, 0x841360));
		DeclareAddress(ProcessLineSafe, SelectAddress(0x841BD0, 0x841350, 0x8413D0));
		DeclareAddress(CreateDefinitionSafe, SelectAddress(0x841C40, 0x8413C0, 0x841440));
		DeclareAddress(func58h, SelectAddress(0xC6FF70, 0x8414F0, 0x841570));
		DeclareAddress(func5Ch, SelectAddress(0x841D80, 0x841500, 0x841580));
		DeclareAddress(func60h, SelectAddress(0x843B00, 0x843270, 0x8432F0));
		DeclareAddress(HasParser, SelectAddress(0x843B40, 0x8432B0, 0x843330));
		DeclareAddress(HasDefinition, SelectAddress(0x843B90, 0x843300, 0x843380));
		DeclareAddress(SetVariable, SelectAddress(0x8473D0, 0x846B30, 0x846BB0));
		DeclareAddress(GetVariable, SelectAddress(0x843BE0, 0x843350, 0x8433D0));
		DeclareAddress(SetGlobalVariable, SelectAddress(0x846B50, 0x8462B0, 0x846330));
		DeclareAddress(func78h, SelectAddress(0x841DB0, 0x841530, 0x8415B0));
		DeclareAddress(StartScope, SelectAddress(0x845B20, 0x845290, 0x845310));
		DeclareAddress(EndScope, SelectAddress(0x842550, 0x841CC0, 0x841D40));
		DeclareAddress(PurgeScope, SelectAddress(0x846CF0, 0x846450, 0x8464D0));
		DeclareAddress(GetCurrentScope, SelectAddress(0x841DF0, 0xD1DCD0, 0xD1DCD0));
		DeclareAddress(AddBlock, SelectAddress(0x845BA0, 0x845310, 0x845390));
		DeclareAddress(AddSpecialBlock, SelectAddress(0x845BE0, 0x845350, 0x8453D0));
		DeclareAddress(ParseBool, SelectAddress(0x841CB0, 0x841430, 0x8414B0));
		DeclareAddress(ParseFloat, SelectAddress(0x841CC0, 0x841440, 0x8414C0));
		DeclareAddress(ParseInt, SelectAddress(0x841CD0, 0x841450, 0x8414D0));
		DeclareAddress(ParseUInt, SelectAddress(0x841CD0, 0x841450, 0x8414D0));
		DeclareAddress(ParseVector2, SelectAddress(0x841E00, 0x841570, 0x8415F0));
		DeclareAddress(ParseVector3, SelectAddress(0x841E50, 0x8415C0, 0x841640));
		DeclareAddress(ParseVector4, SelectAddress(0x841ED0, 0x841640, 0x8416C0));
		DeclareAddress(ParseColorRGB, SelectAddress(0x841E50, 0x8415C0, 0x841640));
		DeclareAddress(ParseColorRGBA, SelectAddress(0x841F70, 0x8416E0, 0x841760));
		DeclareAddress(GetLexer, SelectAddress(0x94EBD0, 0xFF3A50, 0xFF3A50));
		DeclareAddress(SetTraceStream, SelectAddress(0x842000, 0x841770, 0x8417F0));
		DeclareAddress(funcC0h, SelectAddress(0x842040, 0x8417B0, 0x841830));
		DeclareAddress(GetTraceStream, SelectAddress(0x8D88F0, 0xFF02D0, 0xFF02D0));
		DeclareAddress(funcC8h, SelectAddress(0xFC8510, 0x6C0230, 0x6C0230));

	}
}

