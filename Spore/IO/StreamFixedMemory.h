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

#include "IStream.h"

namespace IO
{
	/// Implements an memory-based stream that supports the IStream interface.
	///
	/// This class is not inherently thread-safe. As a result, thread-safe usage 
	/// between multiple threads requires higher level coordination, such as a mutex.
	///
	class FixedMemoryStream : public IStream
	{
	public:
		FixedMemoryStream( void *pBuffer = NULL, size_type nSize = 0 );

		void*       GetData() const;
		bool        SetData(void* pData, size_type nSize);

		size_type   GetCapacity() const;

		/* 04h */	virtual int	AddRef() override;
		/* 08h */	virtual int	Release() override;

		/* 0Ch */	virtual uint32_t	GetType() const override;
		/* 10h */	virtual int			GetAccessFlags() const override;
		/* 14h */	virtual FileError	GetState() const override;
		/* 18h */	virtual bool		Close() override;

		/* 1Ch */	virtual size_type	GetSize() const override;
		/* 20h */	virtual bool		SetSize(size_type size) override;
		/* 24h */	virtual int			GetPosition(PositionType positionType = kPositionTypeBegin) const override;
		/* 28h */	virtual bool		SetPosition(int distance, PositionType positionType = kPositionTypeBegin) override;
		/* 2Ch */	virtual int			GetAvailable() const override;

		/* 30h */	virtual int		Read(void* pData, size_t nSize) override;
		/* 34h */	virtual bool	Flush() override;
		/* 38h */	virtual int		Write(const void* pData, size_t nSize) override;

		static const uint32_t kType = 0x02F2F470;

	protected:
		/* 04h */	void         * mpData;
		/* 08h */	int            mnRefCount;          /// Reference count. May or may not be in use.
		/* 0Ch */	size_type      mnSize;              /// The size of the stream, in bytes.
		/* 10h */	size_type      mnCapacity;          /// The size of the memory buffer, in bytes.
		/* 14h */	size_type      mnPosition;          /// Current position within memory block.
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(FixedMemoryStream) == 0x18, "sizeof(FixedMemoryStream) != 18h");

	namespace InternalAddressList(FixedMemoryStream)
	{
		DefineAddress(AddRef, GetAddress(0x83D030, 0x83F620, 0x83F6A0));
		DefineAddress(Release, GetAddress(0x93BF70, 0x93B820, 0x93B820));
		DefineAddress(GetType, GetAddress(0x93BE00, 0x93B840, 0x93B840));
		DefineAddress(GetAccessFlags, GetAddress(0x5D6800, 0x10E87E0, 0x10E87E0));
		DefineAddress(GetState, GetAddress(0x1065680, 0xE31100, 0xE310C0));
		DefineAddress(Close, GetAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(GetSize, GetAddress(0x80E390, 0xFC7E10, 0xFC7E10));
		DefineAddress(SetSize, GetAddress(0x93BE30, 0x93B870, 0x93B870));
		DefineAddress(GetPosition, GetAddress(0x93C110, 0x93B890, 0x93B890));
		DefineAddress(SetPosition, GetAddress(0x93BE50, 0x93B8C0, 0x93B8C0));
		DefineAddress(GetAvailable, GetAddress(0x93BFC0, 0x93BA10, 0x93BA10));
		DefineAddress(Read, GetAddress(0x93BEA0, 0x93B910, 0x93B910));
		DefineAddress(Flush, GetAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(Write, GetAddress(0x93BEE0, 0x93B950, 0x93B950));

		DefineAddress(SetData, GetAddress(0x93BE10, 0x93B850, 0x93B850));
	}

	inline void* FixedMemoryStream::GetData() const
	{
		return mpData;
	}


	inline size_type FixedMemoryStream::GetCapacity() const
	{
		return mnCapacity;
	}

}