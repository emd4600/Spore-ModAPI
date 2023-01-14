// The IO namespace has been copied (mostly only the headers) from the open source EA WebKit

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

#include <Spore\Internal.h>
#include <Spore\ICoreAllocator.h>
#include <Spore\IO\Constants.h>
#include <Spore\IO\Allocator.h>
#include <stdint.h>

#define IStreamPtr eastl::intrusive_ptr<IO::IStream>

namespace IO
{
	class IStream
	{
	public:
		/* 00h */	virtual ~IStream() {};
		/* 04h */	virtual int AddRef() = 0;
		/* 08h */	virtual int Release() = 0;

		/// Returns the type of the stream, which is different for each Stream subclass.
		/// This function can be used for run-time type identification. A type of zero means
		/// the type is unknown or invalid.
		/* 0Ch */	virtual uint32_t GetType() const = 0;  // ?

		/// Returns one of enum AccessFlags.
		/// This function also tells you if the stream is open, as a return value 
		/// of zero means the stream is not open. It is not allowed that a stream  
		/// be open with no type of access.
		/* 10h */	virtual AccessFlags GetAccessFlags() const = 0;

		/// Returns the error state of the stream.
		/// Returns FileError::Success if OK, else an error code.
		/// This function is similar to 'errno' or a 'get last error' facility.
		/* 14h */	virtual FileError GetState() const = 0;

		/// Closes the stream and releases resouces associated with it.
		/// Returns true upon success, else false.
		/// If the return value is false, GetState will give the error code.
		/// If an IStream encounters an error during operations on an open
		/// stream, it is guaranteed that you can safely call the Close function 
		/// on the stream.
		/* 18h */	virtual bool Close() = 0;

		/// Returns the size of the stream, which is not the same as the size
		/// of bytes remaining to be read from the stream. Returns (size_type)-2 
		/// if the stream is of indeterminate size. Returns (size_type)-1 
		/// (a.k.a. kSizeTypeError) upon error.
		/* 1Ch */	virtual size_type GetSize() const = 0;

		/// Sets the size of the stream, if possible. It is debatable whether this
		/// function should be present in IStream or only in suclasses of 
		/// StreamBase which are writable. For consistency with GetSize, we put 
		/// the function here. But also consider that a SetSize function is not 
		/// necessarily a data writing function, depending on the stream implementation.
		/// @param size
		/* 20h */	virtual bool SetSize(size_type size) = 0;

		/// Gets the current read/write position within the stream. The read and 
		/// write positions of a stream must be the same value; you cannot have a
		/// read position that is different from a write position. However, a 
		/// Stream subclass can provide such functionality if needed. 
		/// Returns -1 upon error.
		/// @param positionType
		/* 24h */	virtual int GetPosition(PositionType positionType = PositionType::Begin) const = 0;

		/// Sets the read/write position of the stream. If the specified position is 
		/// beyond the size of a fixed stream, the position is set to the end of the stream.
		/// A writable stream subclass may provide a policy whereby setting the position
		/// beyond the end of the stream results in an increase in the stream size.
		/// @param distance
		/// @param positionType
		/* 28h */	virtual bool SetPosition(int distance, PositionType positionType = PositionType::Begin) = 0;

		/// Returns the number of bytes available for reading.
		/// Returns (size_type)-1 (a.k.a. kSizeTypeError) upon error.
		/// This function is non-blocking; it should return immediately.
		/* 2Ch */	virtual int GetAvailable() const = 0;

		/// Reads bytes from the stream given by the input count 'nSize'.
		/// If less then nSize bytes are available, then those bytes will be read.
		/// Returns the number of bytes read. A return value of zero means that there
		/// were no bytes to be read or no bytes were requested to be read. 
		/// A return value of zero means the end of file was reached.
		/// A return value > 0 but < 'nSize' is possible, and it does not
		/// necessarily mean that the end of the file was reached.
		/// Returns (size_type)-1 (a.k.a. kSizeTypeError) if there was an error. 
		/// You can use this return value or IStream::GetState to determine the error.
		/// Input size values equal to (size_type)-1 (a.k.a. kSizeTypeError) are not valid input.
		/// Upon error, the stream pointer is at the position it was upon the error occurrence.
		/// @param pData
		/// @param nSize
		/* 30h */	virtual int Read(void* pData, size_t nSize) = 0;

		/// Flush any non-empty stream write buffers. 
		/// If the return value is false, GetState will give the error code.
		/// This function implements the flushing as per the underlying file system.
		/// The behavior of the Flush function varies with the underlying platform.
		///
		/// A common use of Flush is write a file to disk immediately in order to prevent
		/// the file from being corrupted if the application crashes before the file
		/// is closed. However, on desktop platforms such as Windows this strategy is
		/// unnecesary, as the Windows OS file flush doesn't write the file to disk as 
		/// might be expected. This actually is not a problem, because the Windows OS
		/// manages files outside the process and if your process crashes the OS will 
		/// take care of safely closing the files. Only if the machine power is lost or
		/// if certain kinds of kernel-level crashes occur may you lose file data.    
		/* 34h */	virtual bool Flush() = 0;

		/// Writes bytes to the stream. 
		/// If false is returned, you can use IStream::GetState to determine the error.
		/// Upon error, the stream pointer is at the position it was upon the error occurrence.
		/// @param pData
		/// @param nSize
		/* 38h */	virtual int Write(const void* pData, size_t nSize) = 0;
	};

}