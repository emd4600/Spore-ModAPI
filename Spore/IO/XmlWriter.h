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

#include <Spore\IO\IStream.h>

#include <EASTL\intrusive_ptr.h>

using namespace eastl;

namespace IO
{
	///
	/// A simple class that can be used to easily write XML files.
	///
	class XmlWriter
	{
	public:
		/// Character encodings for XmlWriter
		enum WriteEncoding
		{
			kWriteEncodingUnknown,
			kWriteEncodingUTF16 = 1,
			kWriteEncodingLatin1 = 2,
			kWriteEncodingASCII = 3,
			kWriteEncodingUTF8 = 4,
		};

		/// Defines 
		enum LineEnd
		{
			kLineEndUnix,       // \n
			kLineEndWindows,    // \r\n
			kLineEndDefault = kLineEndWindows
		};

		/// Default number of space chars per indent.
		static const size_t kIndentSpacesDefault = 2;


		XmlWriter(bool bFormatPretty = true, WriteEncoding writeEncoding = kWriteEncodingUnknown);

		///
		/// Set the destination stream for the XML - output will fail if this is unset.
		/// @param pStream The output IStream.
		/// @param bFormatPretty True if we format the output to have automatic indentation.
		///
		void SetOutputStream(IO::IStream *pStream, bool bFormatPretty = true);

		///
		/// Write the header at the beginning of the XML file. 
		/// The header is also known as a "prologue".
		///
		/* 04h */	virtual bool WriteXmlHeader();

		///
		/// Begin a new element.
		/// @param pElementName The name of the element.
		///
		/* 08h */	virtual bool BeginElement(const char16_t* pElementName);

		///
		/// End the current element.
		/// @param pElementName The name of the element.
		///
		/* 0Ch */	virtual bool EndElement(const char16_t* pElementName);

		///
		/// Begin a new processing intruction.
		/// @param pInstructionName The name of the instruction.
		///
		/* 10h */	virtual bool BeginProcessingInstruction(const char16_t* pInstructionName);

		///
		/// End the current processing instruction.
		///
		/* 14h */	virtual bool EndProcessingInstruction();

		///
		/// Append a string attribute to the most recently written element or processing instruction,
		/// assuming that it has not been closed.
		/// This should be called before any character data or child elements are written.
		/// XML special characters in the attribute value will be escaped as entities.
		/// @param pAttrName The name of the attribute.
		/// @param pAttrValue The value of the attribute.
		///
		/* 18h */	virtual bool AppendAttribute(const char16_t* pAttrName, const char16_t* pAttrValue);

		///
		/// VPrintF version of AppendAttribute().
		/// @param pAttrName The name of the attribute.
		/// @param pAttrValueFmt The format used by the value.
		///
		/* 1Ch */	virtual bool AppendAttributeF(const char16_t* pAttrName, const char16_t* pAttrValueFmt, ...);

		///
		/// Write a string of character data. XML special characters will be escaped as entities.
		/// @param pCharData The string of characters.
		///
		/* 20h */	virtual bool WriteCharData(const char16_t* pCharData);

		///
		/// Write a string of unencoded character data. Consecutive calls to WriteCDATA will be
		/// merged into a single CDATA block.
		/// It is an error to include the string "]]>" in the character data.
		/// @param pCharData The string of characters.
		///
		/* 24h */	virtual bool WriteCDATA(const char16_t* pCharData);

		///
		/// Write a comment tag, including the enclosing <!-- -->. 
		/// For compatibility with the XML standard, a run of dashes (----) will
		/// be converted into a single dash. No other encoding is performed.
		/// @param pCommentText The comment text.
		/// @param bNewlineBefore If true, then a newline will be written before the comment is written.
		///
		/* 28h */	virtual bool WriteComment(const char16_t* pCommentText, bool bNewlineBefore = true);

		///
		/// Writes a C-string as a piece of raw text.
		/// @param pString The null-terminated string to write.
		/// 
		/* 2Ch */	virtual bool WriteName(const char16_t* pString);

		///
		/// Write a piece of raw text.
		/// @param pString The string to write.
		/// @param nLength The length of the string.
		///
		/* 30h */	virtual bool WriteText(const char16_t* pString, size_t nLength);

	protected:
		enum EState {
			kStateChars,
			kStateElement,
			kStateProcessingInstruction,
			kStateCDATA,
		};

	protected:
		/* 04h */	WriteEncoding     mWriteEncoding;   /// The text encoding (e.g. UTF8) that we write.
		/* 08h */	bool              mbFormatPretty;   /// True if we format the output to have automatic indentation.
		/* 09h */	bool              mbSimpleElement;  /// True if the current element has no child elements. 
		/* 0Ch */	EState            mnState;          /// Used to tell what we are currently writing.
		/* 10h */	size_t            mnIndentLevel;    /// Level of indentation. Starts at zero, increases by one for each indentation.
		/* 14h */	size_t            mnIndentSpaces;   /// Number of space chars per indent. Total indent at any time = mnIndentLevel * mnIndentSpaces.
		/* 18h */	LineEnd           mLineEnd;         /// Defines whether we use Windows or standard indentation.
		/* 1Ch */	intrusive_ptr<IStream> mpStream;
	};

	static_assert(sizeof(XmlWriter) == 0x20, "sizeof(XmlWriter) != 20h");

	namespace Addresses(XmlWriter)
	{
		DeclareAddress(WriteXmlHeader, SelectAddress(0x902040, 0x901C00, 0x901C00));
		DeclareAddress(BeginElement, SelectAddress(0x902210, 0x901DD0, 0x901DD0));
		DeclareAddress(EndElement, SelectAddress(0x902270, 0x901E30, 0x901E30));
		DeclareAddress(BeginProcessingInstruction, SelectAddress(0x901D70, 0x901930, 0x901930));
		DeclareAddress(EndProcessingInstruction, SelectAddress(0x901DE0, 0x9019A0, 0x9019A0));
		DeclareAddress(AppendAttribute, SelectAddress(0x901E20, 0x9019E0, 0x9019E0));
		DeclareAddress(AppendAttributeF, SelectAddress(0x901EB0, 0x901A70, 0x901A70));
		DeclareAddress(WriteCharData, SelectAddress(0x901F80, 0x901B40, 0x901B40));
		DeclareAddress(WriteCDATA, SelectAddress(0x901FB0, 0x901B70, 0x901B70));
		DeclareAddress(WriteComment, SelectAddress(0x902340, 0x901F00, 0x901F00));
		DeclareAddress(WriteName, SelectAddress(0x902010, 0x901BD0, 0x901BD0));
		DeclareAddress(WriteText, SelectAddress(0x902470, 0x902030, 0x902030));

	}
}