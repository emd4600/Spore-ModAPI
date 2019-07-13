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
	auto_METHOD(XmlWriter, bool, BeginElement, Args(const char16_t* pElementName), Args(pElementName));
	auto_METHOD(XmlWriter, bool, EndElement, Args(const char16_t* pElementName), Args(pElementName));
	auto_METHOD(XmlWriter, bool, BeginProcessingInstruction, Args(const char16_t* pInstructionName), Args(pInstructionName));
	auto_METHOD_(XmlWriter, bool, EndProcessingInstruction);
	auto_METHOD(XmlWriter, bool, AppendAttribute, Args(const char16_t* pAttrName, const char16_t* pAttrValue), Args(pAttrName, pAttrValue));
	
	bool XmlWriter::AppendAttributeF(const char16_t* pAttrName, const char16_t* pAttrValueFmt, ...)
	{
		va_list args;
		va_start(args, pAttrValueFmt);
		bool result = ((bool(__thiscall*)(const char16_t*, const char16_t*, va_list))(GetAddress(XmlWriter, AppendAttributeF)))
			(pAttrName, pAttrValueFmt, args);
		va_end(args);

		return result;
	}

	auto_METHOD(XmlWriter, bool, WriteCharData, Args(const char16_t* pCharData), Args(pCharData));
	auto_METHOD(XmlWriter, bool, WriteCDATA, Args(const char16_t* pCharData), Args(pCharData));
	auto_METHOD(XmlWriter, bool, WriteComment, Args(const char16_t* pCommentText, bool bNewlineBefore), Args(pCommentText, bNewlineBefore));
	auto_METHOD(XmlWriter, bool, WriteName, Args(const char16_t* pString), Args(pString));
	auto_METHOD(XmlWriter, bool, WriteText, Args(const char16_t* pString, size_t nLength), Args(pString, nLength));
}


