#ifndef MODAPI_DLL_EXPORT
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

RedirectStaticMethod_noargs(ArgScript, CreateStream, ArgScript::FormatParser*);

namespace ArgScript
{
	Line::Line()
		: mFirstArgIndex(0)
		, mArgumentCount(0)
		, mOptions()
		, mBuffer()
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
		if (mArgumentCount > 0)
		{
			mFirstArgIndex++;
			mArgumentCount--;
		}
	}

	auto_METHOD_VOID(Line, FromString, Args(const char* pText), Args(pText));

	auto_METHOD_const(Line, Arguments, GetArguments, Args(size_t nCount), Args(nCount));
	auto_METHOD_const(Line, Arguments, GetArgumentsRange, Args(size_t* dstCount, size_t nMin, size_t nMax), Args(dstCount, nMin, nMax));
	auto_METHOD_const_(Line, size_t, GetArgumentsCount);
	auto_METHOD_const(Line, const char*, GetArgumentAt, Args(size_t nIndex), Args(nIndex));
	auto_METHOD_const(Line, Arguments, GetOption, Args(const char* pOptionName, size_t nCount), Args(pOptionName, nCount));
	auto_METHOD_const(Line, Arguments, GetOptionRange, Args(const char* pOptionName, size_t* dstCount, size_t nMin, size_t nMax), Args(pOptionName, dstCount, nMin, nMax));
	auto_METHOD_const(Line, bool, HasFlag, Args(const char* pFlagName), Args(pFlagName));

	auto_STATIC_METHOD(Line, int, GetEnum, Args(const char* pValueString, const EnumValue* pEnum), Args(pValueString, pEnum));
	auto_STATIC_METHOD(Line, bool, GetOptionalEnum, Args(const char* pValueString, const EnumValue* pEnum, int& dst), Args(pValueString, pEnum, dst));

	auto_METHOD_VOID(IBlock, AddParser, Args(const char* pKeyword, IParser* pParser), Args(pKeyword, pParser));
	auto_METHOD(IBlock, IParser*, GetParser, Args(const char* pKeyword), Args(pKeyword));

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


	auto_METHOD_VOID(Lexer, AddFunction, Args(const char* pFunctionName, IFunction* pFunction), Args(pFunctionName, pFunction));
	auto_METHOD_VOID(Lexer, ExpectChar, Args(LexerString& lexerString, char c), Args(lexerString, c));
	auto_METHOD(Lexer, bool, OptionalExpectChar, Args(LexerString& lexerString, char c), Args(lexerString, c));
	auto_METHOD_VOID(Lexer, NextParameter, Args(LexerString& lexerString, string& dst), Args(lexerString, dst));

	void ISpecialBlock::SetData(FormatParser* pFormatParser, void* pData)
	{
		this->mpData = pData;
		this->mpFormatParser = pFormatParser;
	}


	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, AddRef);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, Release);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, bool, Initialize);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, bool, Dispose);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetData, Args(void* pData), Args(pData));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, AddParser, Args(const char* pKeyword, IParser* pParser), Args(pKeyword, pParser));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, RemoveParser, Args(const char* pKeyword), Args(pKeyword));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, RemoveParserByObject, Args(IParser* pParser), Args(pParser));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, IParser*, GetParser, Args(const char* pKeyword), Args(pKeyword));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetFlag, Args(int flag, bool bValue), Args(flag, bValue));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetVersionRange, Args(int nMinVersion, int nMaxVerison), Args(nMinVersion, nMaxVerison));
	auto_METHOD_VIRTUAL_const_(FormatParser, FormatParser, int, GetVersion);
	auto_METHOD_VIRTUAL_VOID_(FormatParser, FormatParser, func30h);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, Close, Args(bool arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessFile, Args(const char* pPath), Args(pPath));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessStream, Args(IO::IStream* pInputStream), Args(pInputStream));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, ProcessLine, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, CreateDefinition, Args(const char* pName, const Line& argumentsLine), Args(pName, argumentsLine));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessFileSafe, Args(const char* pFilePath), Args(pFilePath));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessStreamSafe, Args(IO::IStream* pStream), Args(pStream));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, ProcessLineSafe, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, bool, CreateDefinitionSafe, Args(const char* pName, const Line& argumentsLine), Args(pName, argumentsLine));
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, func58h);
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, int, func5Ch);
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, int, func60h, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, int, HasParser, Args(const char* pName), Args(pName));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, bool, HasDefinition, Args(const char* pName), Args(pName));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetVariable, Args(const char* pName, const char* pValue), Args(pName, pValue));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, const char*, GetVariable, Args(const char* pVariableName), Args(pVariableName));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetGlobalVariable, Args(const char* pName, const char* pValue), Args(pName, pValue));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, func78h, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, StartScope, Args(const char* pName), Args(pName));
	auto_METHOD_VIRTUAL_VOID_(FormatParser, FormatParser, EndScope);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, PurgeScope, Args(const char* pScope), Args(pScope));
	auto_METHOD_VIRTUAL_const_(FormatParser, FormatParser, const char*, GetCurrentScope);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, AddBlock, Args(IBlock* pBlock), Args(pBlock));
	auto_METHOD_VIRTUAL(FormatParser, FormatParser, int, AddSpecialBlock, Args(ISpecialBlock* pSpecialBlock, const char* pEndKeyword), Args(pSpecialBlock, pEndKeyword));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, bool, ParseBool, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, float, ParseFloat, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, int, ParseInt, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, unsigned int, ParseUInt, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector2, ParseVector2, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector3, ParseVector3, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::Vector4, ParseVector4, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::ColorRGB, ParseColorRGB, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_const(FormatParser, FormatParser, Math::ColorRGBA, ParseColorRGBA, Args(const char* pString), Args(pString));
	auto_METHOD_VIRTUAL_(FormatParser, FormatParser, Lexer&, GetLexer);
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, SetTraceStream, Args(ITraceStream* pTraceStream), Args(pTraceStream));
	auto_METHOD_VIRTUAL_VOID(FormatParser, FormatParser, funcC0h, Args(int arg_0), Args(arg_0));
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
#endif
