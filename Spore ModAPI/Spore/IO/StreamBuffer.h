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

#include <Spore\IO\IStream.h>
#include <EASTL\intrusive_ptr.h>

#define StreamBufferPtr eastl::intrusive_ptr<IO::StreamBuffer>

namespace IO
{
	///
	/// Implements a smart buffer around a random-access stream.
	/// This buffering is significantly smarter than the file buffering 
	/// you get with the C or C++ standard libaries, and it gives the 
	/// user some configurability options as well.
	///
	class StreamBuffer : public IStream
	{
	public:

		static const uint32_t kType = 0x12ea45bc;

		static const size_type kBufferSizeReadDefault = (size_type)2000;   /// This is the default write buffer size.
		static const size_type kBufferSizeWriteDefault = (size_type)2000;   /// This is the default write buffer size.
		static const size_type kBufferSizeUseDefault = (size_type)-1;   /// This means that the buffer is used with the default size.
		static const size_type kBufferSizeUnspecified = (size_type)-2;   /// This means that the user means to leave the given buffer as-is.

	public:
		StreamBuffer(
			size_type nReadBufferSize = kBufferSizeUnspecified,
			size_type nWriteBufferSize = kBufferSizeUnspecified,
			IStream* pStream = NULL
			);

		~StreamBuffer();

		IStream* GetStream() const;
		bool     SetStream(IStream* pStream);

		void GetBufferSizes(size_type& nReadBufferSize, size_type& nWriteBufferSize) const;
		bool SetBufferSizes(size_type  nReadBufferSize, size_type  nWriteBufferSize);

		/* 04h */	virtual int	AddRef() override;
		/* 08h */	virtual int	Release() override;

		/* 0Ch */	virtual uint32_t	GetType() const override;
		/* 10h */	virtual AccessFlags	GetAccessFlags() const override;
		/* 14h */	virtual FileError	GetState() const override;
		/* 18h */	virtual bool		Close() override;

		/* 1Ch */	virtual size_type	GetSize() const override;
		/* 20h */	virtual bool		SetSize(size_type size) override;
		/* 24h */	virtual int			GetPosition(PositionType positionType = PositionType::Begin) const override;
		/* 28h */	virtual bool		SetPosition(int distance, PositionType positionType = PositionType::Begin) override;
		/* 2Ch */	virtual int			GetAvailable() const override;

		/* 30h */	virtual int		Read(void* pData, size_t nSize) override;
		/* 34h */	virtual bool	Flush() override;
		/* 38h */	virtual int		Write(const void* pData, size_t nSize) override;

	protected:
		bool        FillWriteBuffer(const char* pData, size_type nSize);
		bool        FlushWriteBuffer();

	protected:
		/* 04h */	IStreamPtr          mpStream;                      /// The stream that we are buffering.
		/* 08h */	int                 mnRefCount;                    /// The reference count, which may or may not be used.
		/* 0Ch */	size_type           mnPositionExternal;            /// This is the position of the the file pointer as the the user sees it. It is where the next byte read or write will come from or go to.
		/* 10h */	size_type           mnPositionInternal;            /// This is the position of the the file pointer as the owned stream sees it.

		/* 14h */	char*               mpReadBuffer;                  /// Pointer to buffer data.
		/* 18h */	size_type           mnReadBufferSize;              /// This is the size of the read buffer available for our usage.
		/* 1Ch */	size_type           mnReadBufferStartPosition;     /// This is where in the file the beginning the read buffer corresponds to. 
		/* 20h */	size_type           mnReadBufferUsed;              /// This is the count of bytes in the read buffer that are valid.

		/* 24h */	char*               mpWriteBuffer;                 /// Pointer to buffer data.
		/* 28h */	size_type           mnWriteBufferSize;             /// This is the size of the write buffer available for our usage.
		/* 2Ch */	size_type           mnWriteBufferStartPosition;    /// This is where in the file the beginning the write buffer corresponds to.
		/* 30h */	size_type           mnWriteBufferUsed;             /// This is the count of bytes in the write buffer that are valid.
	};
	ASSERT_SIZE(StreamBuffer, 0x34);

	namespace Addresses(StreamBuffer)
	{
		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(GetType);
		DeclareAddress(GetAccessFlags);
		DeclareAddress(GetState);
		DeclareAddress(Close);
		DeclareAddress(GetSize);
		DeclareAddress(SetSize);
		DeclareAddress(GetPosition);
		DeclareAddress(SetPosition);
		DeclareAddress(GetAvailable);
		DeclareAddress(Read);
		DeclareAddress(Flush);
		DeclareAddress(Write);

		DeclareAddress(SetBufferSizes);
		DeclareAddress(SetStream);
		DeclareAddress(FillWriteBuffer);
		DeclareAddress(FlushWriteBuffer);
	}

	inline IStream* StreamBuffer::GetStream() const
	{
		return mpStream.get();
	}

}