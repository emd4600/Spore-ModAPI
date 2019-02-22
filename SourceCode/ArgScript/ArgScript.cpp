/****************************************************************************
* Copyright (C) 2018 Eric Mor
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


#include <Spore\ArgScript\IParser.h>
#include <Spore\ArgScript\ICommand.h>
#include <Spore\ArgScript\IBlock.h>
#include <Spore\ArgScript\ISpecialBlock.h>
#include <Spore\ArgScript\LambdaParser.h>
#include <Spore\ArgScript\Lexer.h>
#include <Spore\ArgScript\Line.h>
#include <Spore\ArgScript\FormatParser.h>

namespace ArgScript
{
	Line::Line()
		: mnFirstArgIndex(0)
		, mnArgumentCount(0)
		, mOptions()
		, mStrings()
		, mArguments()
	{

	}

	Line::Line(const char* pText)
		: Line()
	{
		FromString(pText);
	}

	void Line::RemoveKeyword()
	{
		if (mnArgumentCount > 0)
		{
			mnFirstArgIndex++;
			mnArgumentCount--;
		}
	}

	auto_METHOD_VOID(Line, FromString, PARAMS(const char* pText), PARAMS(pText));

	auto_METHOD_const(Line, Arguments, GetArguments, PARAMS(size_t nCount), PARAMS(nCount));
	auto_METHOD_const(Line, Arguments, GetArgumentsRange, PARAMS(size_t* dstCount, size_t nMin, size_t nMax), PARAMS(dstCount, nMin, nMax));
	auto_METHOD_const_(Line, size_t, GetArgumentsCount);
	auto_METHOD_const(Line, const char*, GetArgumentAt, PARAMS(size_t nIndex), PARAMS(nIndex));
	auto_METHOD_const(Line, Arguments, GetOption, PARAMS(const char* pOptionName, size_t nCount), PARAMS(pOptionName, nCount));
	auto_METHOD_const(Line, Arguments, GetOptionRange, PARAMS(const char* pOptionName, size_t* dstCount, size_t nMin, size_t nMax), PARAMS(pOptionName, dstCount, nMin, nMax));
	auto_METHOD_const(Line, bool, HasFlag, PARAMS(const char* pFlagName), PARAMS(pFlagName));

	auto_STATIC_METHOD(Line, int, GetEnum, PARAMS(const char* pValueString, const EnumValue* pEnum), PARAMS(pValueString, pEnum));
	auto_STATIC_METHOD(Line, bool, GetOptionalEnum, PARAMS(const char* pValueString, const EnumValue* pEnum, int& dst), PARAMS(pValueString, pEnum, dst));

	auto_METHOD_VOID(IBlock, AddParser, PARAMS(const char* pKeyword, IParser* pParser), PARAMS(pKeyword, pParser));
	auto_METHOD(IBlock, IParser*, GetParser, PARAMS(const char* pKeyword), PARAMS(pKeyword));

	IParser::IParser()
		: mnRefCount(0)
		, mpFormatParser(nullptr)
		, mpData(nullptr)
	{

	}

	const char* IParser::GetDescription(DescriptionMode mode) const
	{
		return nullptr;
	}

	int IParser::AddRef()
	{
		return ++mnRefCount;
	}

	int IParser::Release()
	{
		if (--mnRefCount == 0)
		{
			delete this;
		}
		return mnRefCount;
	}


	void ICommand::SetData(FormatParser* formatParser, void* data)
	{
		this->mpData = data;
		this->mpFormatParser = formatParser;
	}

	IBlock::IBlock()
		: mParsers()
	{

	}


	auto_METHOD_VOID(Lexer, AddFunction, PARAMS(const char* pFunctionName, IFunction* pFunction), PARAMS(pFunctionName, pFunction));
	auto_METHOD_VOID(Lexer, ExpectChar, PARAMS(LexerString& lexerString, char c), PARAMS(lexerString, c));
	auto_METHOD(Lexer, bool, OptionalExpectChar, PARAMS(LexerString& lexerString, char c), PARAMS(lexerString, c));
	auto_METHOD_VOID(Lexer, NextParameter, PARAMS(LexerString& lexerString, string& dst), PARAMS(lexerString, dst));

	auto_STATIC_METHOD_(ArgScript, FormatParser*, CreateStream);

	void ISpecialBlock::SetData(FormatParser* pFormatParser, void* pData)
	{
		this->mpData = pData;
		this->mpFormatParser = pFormatParser;
	}


	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, AddRef);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, Release);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, bool, Initialize);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, bool, Dispose);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetData, PARAMS(void* pData), PARAMS(pData));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, AddParser, PARAMS(const char* pKeyword, IParser* pParser), PARAMS(pKeyword, pParser));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, RemoveParser, PARAMS(const char* pKeyword), PARAMS(pKeyword));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, RemoveParserByObject, PARAMS(IParser* pParser), PARAMS(pParser));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, IParser*, GetParser, PARAMS(const char* pKeyword), PARAMS(pKeyword));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetFlag, PARAMS(int flag, bool bValue), PARAMS(flag, bValue));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetVersionRange, PARAMS(int nMinVersion, int nMaxVerison), PARAMS(nMinVersion, nMaxVerison));
	auto_METHOD_VIRTUAL_const_(FormatParser, FormatParser, int, GetVersion);
	auto_METHOD_VIRTUAL_VOID_(FormatParser, FormatParser, func30h);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, Close, PARAMS(bool arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessFile, PARAMS(const char* pPath), PARAMS(pPath));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessStream, PARAMS(IO::IStream* pInputStream), PARAMS(pInputStream));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessLine, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, CreateDefinition, PARAMS(const char* pName, const Line& argumentsLine), PARAMS(pName, argumentsLine));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessFileSafe, PARAMS(const char* pFilePath), PARAMS(pFilePath));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessStreamSafe, PARAMS(IO::IStream* pStream), PARAMS(pStream));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessLineSafe, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, CreateDefinitionSafe, PARAMS(const char* pName, const Line& argumentsLine), PARAMS(pName, argumentsLine));
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, func58h);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, func5Ch);
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, int, func60h, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, int, HasParser, PARAMS(const char* pName), PARAMS(pName));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, bool, HasDefinition, PARAMS(const char* pName), PARAMS(pName));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetVariable, PARAMS(const char* pName, const char* pValue), PARAMS(pName, pValue));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, const char*, GetVariable, PARAMS(const char* pVariableName), PARAMS(pVariableName));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetGlobalVariable, PARAMS(const char* pName, const char* pValue), PARAMS(pName, pValue));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, func78h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, StartScope, PARAMS(const char* pName), PARAMS(pName));
	auto_METHOD_VIRTUAL_VOID_(FormatParser, FormatParser, EndScope);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, PurgeScope, PARAMS(const char* pScope), PARAMS(pScope));
	auto_METHOD_VIRTUAL_const_(FormatParser, FormatParser, const char*, GetCurrentScope);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, AddBlock, PARAMS(IBlock* pBlock), PARAMS(pBlock));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, int, AddSpecialBlock, PARAMS(ISpecialBlock* pSpecialBlock, const char* pEndKeyword), PARAMS(pSpecialBlock, pEndKeyword));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, bool, ParseBool, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, float, ParseFloat, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, int, ParseInt, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, unsigned int, ParseUInt, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector2, ParseVector2, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector3, ParseVector3, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector4, ParseVector4, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::ColorRGB, ParseColorRGB, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::ColorRGBA, ParseColorRGBA, PARAMS(const char* pString), PARAMS(pString));
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, Lexer&, GetLexer);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetTraceStream, PARAMS(ITraceStream* pTraceStream), PARAMS(pTraceStream));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, funcC0h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, ITraceStream*, GetTraceStream);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, funcC8h);



	LambdaParser::LambdaParser(ParseLine_t pParseLine)
		: mpParseLine(pParseLine)
		, mpGetDescription(nullptr)
		, mpSetData(nullptr)
	{}
	LambdaParser::LambdaParser(ParseLine_t pParseLine, GetDescription_t pGetDescription)
		: mpParseLine(pParseLine)
		, mpGetDescription(pGetDescription)
		, mpSetData(nullptr)
	{}
	LambdaParser::LambdaParser(ParseLine_t pParseLine, SetData_t pSetData)
		: mpParseLine(pParseLine)
		, mpGetDescription(nullptr)
		, mpSetData(pSetData)
	{}

	void LambdaParser::ParseLine(const Line& line)
	{
		if (mpParseLine)
		{
			mpParseLine(line, mpFormatParser);
		}
	}
	const char* LambdaParser::GetDescription(DescriptionMode mode) const
	{
		return mpGetDescription ? mpGetDescription(mode) : nullptr;
	}
	void LambdaParser::SetData(FormatParser* pFormatParser, void* pData)
	{
		this->mpFormatParser = pFormatParser;
		this->mpData = pData;
		if (mpSetData)
		{
			mpSetData(pFormatParser, pData);
		}
	}


	void FormatParser::AddParser(const char* pKeyword, ParseLine_t pParseLine)
	{
		AddParser(pKeyword, new LambdaParser(pParseLine));
	}
	void FormatParser::AddParser(const char* pKeyword, ParseLine_t pParseLine, GetDescription_t pGetDescription)
	{
		AddParser(pKeyword, new LambdaParser(pParseLine, pGetDescription));
	}
	void FormatParser::AddParser(const char* pKeyword, ParseLine_t pParseLine, SetData_t pSetData)
	{
		AddParser(pKeyword, new LambdaParser(pParseLine, pSetData));
	}
}