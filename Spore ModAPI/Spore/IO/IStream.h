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
#include <Spore\IO\Allocator.h>
#include <stdint.h>

#define IStreamPtr eastl::intrusive_ptr<IO::IStream>

namespace IO
{
	typedef size_t size_type;

	/// Used to designate an error condition for many functions that return size_type.
	const size_type kSizeTypeError = (size_type)-1;


	/// Used to designate the condition whereby a requested operation is complete
	/// and no more processing can be done. Only applicable to functions that 
	/// document the use of kSizeTypeDone.
	const size_type kSizeTypeDone = (size_type)-2;


	/// Defines a value to be used for string conversion functions which means
	/// that the string length is specified by a wherever the terminating null
	/// character is. For the copying or converting of strings, the terminating
	/// null character is also copied to the destination.
	const size_t kLengthNull = (size_t)-1;

	enum class FileError : uint32_t
	{
		Success = 0,
		InvalidHandle = 0xFFFFFFFE,
		OutOfMemory = 0xCFDE0002,  // both OutOfMemory and NotEnoughMemory
		FileNotFound = 0xCFDE0004,
		PathNotFound = 0xCFDE0005,  // also INVALID_DRIVE
		AccessDenied = 0xCFDE0006,
		CurrentDirectory = 0xCFDE0008,
		WriteProtect = 0xCFDE0007,
		NotReady = 0xCFDE000B,
		CRC = 0xCFDE000C,
		Other = 0xCFDE000D
	};

	/// Defines stream access flags, much like file access flags.
	enum AccessFlags
	{
		kAccessFlagNone = 0x00,  /// No specified flags. Also used to indicate that a given IO stream is closed.
		kAccessFlagRead = 0x01,  /// Used for identifying read access to an entity.
		kAccessFlagWrite = 0x02,  /// Used for identifying write access to an entity.
		kAccessFlagReadWrite = 0x03   /// Used for identifying both read and write access to an entity.
	};

	/// Creation disposition. Specifies aspects of how to create or not create a file during opening of it.
	enum CD
	{
		kCDCreateNew = 1,      /// Fails if file already exists.
		kCDCreateAlways = 2,      /// Never fails, always opens or creates and truncates to 0.
		kCDOpenExisting = 3,      /// Fails if file doesn't exist, keeps contents.
		kCDOpenAlways = 4,      /// Never fails, creates if doesn't exist, keeps contents.
		kCDTruncateExisting = 5,      /// Fails if file doesn't exist, but truncates to 0 if it does.
		kCDDefault = 6       /// Default (implementation-specific) disposition
	};

	/// Defines the positional basis for a user GetPosition or SetPosition action.
	enum PositionType
	{
		kPositionTypeBegin = 0,    /// For GetPosition refers to absolute index of next byte to read; always positive. For SetPosition, refers to absolute index of next byte to be written; always positive.
		kPositionTypeCurrent = 1,    /// For GetPosition always returns zero. For SetPosition, refers to position relative to current position; can be positive or negative.
		kPositionTypeEnd = 2     /// For GetPosition returns to position relative to end (i.e. the negative of bytes left to read); always negative. For SetPosition, refers to position relative to end; can be positive or negative.
	};

	/// Defines textual line ending property types.
	enum LineEnd
	{
		kLineEndNone = 0,     /// Refers to no line termination. When writing, it means to append nothing.
		kLineEndAuto = 1,     /// Refers to automatic line termination. When writing, it means to append kLineTerminationNewline if there isn't one already.
		kLineEndNewline = 2,     /// Refers to "\n" line termination. When writing, it means to append a newline always.
		kLineEndUnix = 2,     /// Same as kLineEndNewline.
		kLineEndWindows = 3      /// Refers to "\r\n" line termination. When writing, it means to append a newline always.
	};

	enum Share
	{
		kShareNone = 0x00,     /// No sharing.
		kShareRead = 0x01,     /// Allow sharing for reading.
		kShareWrite = 0x02,     /// Allow sharing for writing.
		kShareDelete = 0x04      /// Allow sharing for deletion.
	};

	enum UsageHints
	{
		kUsageHintNone = 0x00,
		kUsageHintSequential = 0x01,
		kUsageHintRandom = 0x02
	};

	/// Defines state values or function return values. Zero means success and non-zero means failure in general.
	/// Note that various stream types may define their own errors in addition to these generic errors.
	enum State
	{
		kStateSuccess = 0,
		kStateError = -1,
		kStateNotOpen = -2
	};

	/// Defines endian-ness. This is appropriate for working with binary numerical data. 
	enum Endian
	{

		kEndianBig = 0,            /// Big endian.
		kEndianLittle = 1,            /// Little endian.
#ifdef EA_SYSTEM_BIG_ENDIAN
		kEndianLocal = kEndianBig    /// Whatever endian is native to the machine.
#else 
		kEndianLocal = kEndianLittle /// Whatever endian is native to the machine.
#endif
	};

	class IStream
	{
	public:

		// off_143AC04 -> vtable

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
		/* 10h */	virtual int GetAccessFlags() const = 0;

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
		/* 24h */	virtual int GetPosition(PositionType positionType = kPositionTypeBegin) const = 0;

		/// Sets the read/write position of the stream. If the specified position is 
		/// beyond the size of a fixed stream, the position is set to the end of the stream.
		/// A writable stream subclass may provide a policy whereby setting the position
		/// beyond the end of the stream results in an increase in the stream size.
		/// @param distance
		/// @param positionType
		/* 28h */	virtual bool SetPosition(int distance, PositionType positionType = kPositionTypeBegin) = 0;

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