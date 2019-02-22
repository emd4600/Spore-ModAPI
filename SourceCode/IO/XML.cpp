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

#include <Spore\IO\XmlWriter.h>
#include <Spore\Internal.h>

namespace IO
{
	XmlWriter::XmlWriter(bool bFormatPretty, WriteEncoding writeEncoding)
		: mWriteEncoding(writeEncoding)
		, mbFormatPretty(bFormatPretty)
		, mbSimpleElement(false)
		, mnState(kStateChars)
		, mnIndentLevel(0)
		, mnIndentSpaces(kIndentSpacesDefault)
		, mLineEnd(kLineEndDefault)
	{

	}

	void XmlWriter::SetOutputStream(IO::IStream *pStream, bool bFormatPretty)
	{
		this->mpStream = pStream;
		this->mbFormatPretty = bFormatPretty;
	}

	auto_METHOD_(XmlWriter, bool, WriteXmlHeader);
	auto_METHOD(XmlWriter, bool, BeginElement, PARAMS(const char16_t* pElementName), PARAMS(pElementName));
	auto_METHOD(XmlWriter, bool, EndElement, PARAMS(const char16_t* pElementName), PARAMS(pElementName));
	auto_METHOD(XmlWriter, bool, BeginProcessingInstruction, PARAMS(const char16_t* pInstructionName), PARAMS(pInstructionName));
	auto_METHOD_(XmlWriter, bool, EndProcessingInstruction);
	auto_METHOD(XmlWriter, bool, AppendAttribute, PARAMS(const char16_t* pAttrName, const char16_t* pAttrValue), PARAMS(pAttrName, pAttrValue));
	
	bool XmlWriter::AppendAttributeF(const char16_t* pAttrName, const char16_t* pAttrValueFmt, ...)
	{
		va_list args;
		va_start(args, pAttrValueFmt);
		bool result = ((bool(__thiscall*)(const char16_t*, const char16_t*, va_list))(GetMethodAddress(XmlWriter, AppendAttributeF)))
			(pAttrName, pAttrValueFmt, args);
		va_end(args);

		return result;
	}

	auto_METHOD(XmlWriter, bool, WriteCharData, PARAMS(const char16_t* pCharData), PARAMS(pCharData));
	auto_METHOD(XmlWriter, bool, WriteCDATA, PARAMS(const char16_t* pCharData), PARAMS(pCharData));
	auto_METHOD(XmlWriter, bool, WriteComment, PARAMS(const char16_t* pCommentText, bool bNewlineBefore), PARAMS(pCommentText, bNewlineBefore));
	auto_METHOD(XmlWriter, bool, WriteName, PARAMS(const char16_t* pString), PARAMS(pString));
	auto_METHOD(XmlWriter, bool, WriteText, PARAMS(const char16_t* pString, size_t nLength), PARAMS(pString, nLength));
}


