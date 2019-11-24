// The IO namespace has been copied (mostly only the headers) from the open source EA WebKit
// I've only used the function documentation here

/*
Copyright (C) 2009-2010 Electronic Arts, Inc.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1.  Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3.  Neither the name of Electronic Arts, Inc. ("EA") nor the names of
its contributors may be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY ELECTRONIC ARTS AND ITS CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ELECTRONIC ARTS OR ITS CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/////////////////////////////////////////////////////////////////////////////
// EAStreamMemory.h
//
// Copyright (c) 2007, Electronic Arts Inc. All rights reserved.
// Written by Paul Pedriana
//
// Implements a IO stream that reads and writes to a block of memory.
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Spore\IO\IStream.h>
#include <Spore\ResourceID.h>
#include <EASTL\string.h>

namespace IO
{
	// Warning: There's no difference between Int and UInt methods; there's no difference between ReadInt32 and ReadFloat

	///
	/// Reads a single boolean value from the stream. Note that the to be 
	/// portable, the stream implments booleans as int8_t and not bool.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	///
	bool ReadBool8(IStream* pIS, bool& value);

	///
	/// Reads a single int8_t value or an array of int8_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1.
	///
	bool ReadInt8(IStream* pIS, int8_t* value, size_type count = 1);

	///
	/// Reads a single uint8_t value or an array of uint8_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1.
	///
	bool ReadUInt8(IStream* pIS, uint8_t* value, size_type count = 1);

	///
	/// Reads a single int16_t value or an array of int16_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadInt16(IStream* pIS, int16_t* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a single uint16_t value or an array of uint16_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadUInt16(IStream* pIS, uint16_t* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a single int32_t value or an array of int32_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadInt32(IStream* pIS, int32_t* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a single uint32_t value or an array of uint32_t from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadUInt32(IStream* pIS, uint32_t* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a single float value or an array of float from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadFloat(IStream* pIS, float* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a single ResourceID value or an array of ResourceID from the stream.
	/// Input 'endianSource' refers to the endian-ness of the values in the stream.
	/// Upon return the output value will be in local (a.k.a. native) endian-ness.
	/// The return value is true if the value could be entirely read. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool ReadResourceID(IStream* pIS, ResourceID* value, size_type count = 1, Endian endianSource = kEndianBig);

	///
	/// Reads a null-terminated string from the source IStream
	/// This will read bytes until a \x00 byte is found.
	///
	IStream* ReadCString(IStream* pIS, eastl::string8& str);

	///
	/// Reads a line of text from the source IStream.
	///
	/// A line is defined as a sequence ending with "\n" or "\r\n".
	/// A line may be empty, as would be the case with a "\n\n" sequence.
	/// The returned line does not end with line terminator characters.
	/// The returned line -does- end with a terminating zero.
	///
	/// The return value is the strlen (string length) of the expected line or 
	/// kSizeTypeError upon error. A return value of kSizeTypeDone means there 
	/// were no more lines to read. This is different from the return value of 
	/// the IStream::Read function because of the possibility of empty lines.
	/// Note that the return value is the *expected* strlen, which may be >=
	/// the nLineCapacity. In any case, the returned line will always be 
	/// nul-terminated if it has any capacity.
	///
	/// Upon return, the stream will be positioned at the beginning of the 
	/// next line, even if input nLineCapacity was not enough to hold the entire line.
	/// The input nLineCapacity is max number of characters to write, including 
	/// the terminating zero. The input pLine can be NULL, in which case it 
	/// will not be written to and the return value will merely indicate its 
	/// required size.
	///
	/// Example usage:
	///     char      buffer[256];
	///     size_type size;
	///     while((size = EA::IO::ReadLine(&fileStream, buffer, 256)) < kSizeTypeDone) // While there there were more lines...
	///         ; // do something
	///
	size_type ReadLine(IStream* pIS, char* pLine, size_type nLineCapacity);



	///
	/// Writes a boolean value to the output stream.
	/// Since type 'bool' is not portable, this function converts the input to 
	/// an int8_t and write that as 0 or 1.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	///
	bool WriteBool8(IStream* pOS, const bool* value);

	///
	/// Writes a single int8_t value or an array of int8_t numerical values to the output stream.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1.
	///
	bool WriteInt8(IStream* pOS, const int8_t* value, size_type count = 1);

	///
	/// Writes a single uint8_t value or an array of uint8_t numerical values to the output stream.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1.
	///
	bool WriteUInt8(IStream* pOS, const uint8_t* value, size_type count = 1);

	///
	/// Writes a single int16_t value or an array of int16_t numerical values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteInt16(IStream* pOS, const int16_t* value, size_type count = 1, Endian endianDestination = kEndianBig);

	///
	/// Writes a single uint16_t value or an array of uint16_t numerical values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteUInt16(IStream* pOS, const uint16_t* value, size_type count = 1, Endian endianDestination = kEndianBig);

	/// WriteInt32
	///
	/// Writes a single int32_t value or an array of int32_t numerical values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteInt32(IStream* pOS, const int32_t* src, size_type count = 1, Endian endianDestination = kEndianBig);

	///
	/// Writes a single uint32_t value or an array of uint32_t numerical values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteUInt32(IStream* pOS, const uint32_t* value, size_type count = 1, Endian endianDestination = kEndianBig);

	///
	/// Writes a single float value or an array of float numerical values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteFloat(IStream* pOS, const float* value, size_type count = 1, Endian endianDestination = kEndianBig);

	///
	/// Writes a single ResourceID value or an array of ResourceID values to the output stream with the given destination endian-ness.
	/// The return value is true if the value could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error.
	/// The default number of values is 1, and the default endian-ness is kEndianBig.
	///
	bool WriteResourceID(IStream* pOS, const ResourceID* value, size_type count = 1, Endian endianDestination = kEndianBig);

	///
	/// Reads a null-terminated string from the source IStream
	/// This will read bytes until a \x00 byte is found.
	///
	void WriteCString(IStream* pOS, eastl::string8& str);

	///
	/// Writes a line of text to a destination IStream.
	///
	/// The source line is not expected to end in a line delimiter (e.g. '\n'); 
	/// a appropriate line delimiter (defined by the lineEndToUse parameter) will be 
	/// written to the stream by this function. The source line is not expected to end 
	/// with a nul-terminator; if it has such a terminator, the nSourceLineLength value 
	/// should not include that terminator.
	///
	/// If input nLineLength is kLengthNull, then the line is expected to be 
	/// nul-terminated and the length written is the strlen of pSourceLine.
	/// The pLineSource value must be non-NULL unless nLineLength is zero.
	///
	/// The return value is true if the line could be successfully completely written. 
	/// If false, you can use IStream::GetState to determine the error, as this function
	/// generates no errors beyond those related to IStream errors.
	///
	bool WriteLine(IStream* pOS, const char8_t* pLineSource, size_type nLineLength, LineEnd lineEndToUse = kLineEndAuto);


	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	inline bool IO::WriteBool8(IStream* pOS, const bool* value)
	{
		int8_t src = value ? 1 : 0;
		return IO::WriteInt8(pOS, &src);
	}

	inline void IO::WriteCString(IStream* pOS, eastl::string8& str)
	{
		char terminator = 0;
		pOS->Write(str.c_str(), str.length());
		pOS->Write(&terminator, 1);
	}

}

namespace Addresses(IO)
{
	DeclareAddress(ReadBool8);

	DeclareAddress(ReadInt8);
	DeclareAddress(ReadUInt8);

	DeclareAddress(ReadInt16);
	DeclareAddress(ReadUInt16);

	DeclareAddress(ReadInt32);
	DeclareAddress(ReadUInt32);

	DeclareAddress(ReadFloat);

	DeclareAddress(ReadResourceID);

	DeclareAddress(ReadCString);

	DeclareAddress(ReadLine);


	DeclareAddress(WriteInt8);
	DeclareAddress(WriteUInt8);

	DeclareAddress(WriteInt16);
	DeclareAddress(WriteUInt16);

	DeclareAddress(WriteInt32);
	DeclareAddress(WriteUInt32);

	DeclareAddress(WriteFloat);

	DeclareAddress(WriteResourceID);

	DeclareAddress(WriteLine);
}

