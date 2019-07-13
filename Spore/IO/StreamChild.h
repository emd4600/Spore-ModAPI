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
	///
	/// Implements a fixed-size read-only stream which is a 'child' of a parent
	/// stream. This is useful if you have a system whereby a single large file
	/// consists of smaller files or a single large database record consists of
	/// multiple sub-records and you want each sub-record to look like a standalone
	/// stream to the user.
	///
	/// This class is not inherently thread-safe. As a result, thread-safe usage 
	/// between multiple threads requires higher level coordination, such as a mutex.
	///
	class StreamChild : public IStream
	{
	public:
		StreamChild(IStream* pStreamParent = NULL, size_type nPosition = 0, size_type nSize = 0);

		bool Open(IStream* pStreamParent, size_type nPosition, size_type nSize);

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

		static const uint32_t kType = 0x3472233A;

	protected:
		/* 04h */	int         mnRefCount;
		/* 08h */	int         mnAccessFlags;
		/* 0Ch */	IStream*    mpStreamParent;
		/* 10h */	size_type   mnPositionParent;
		/* 14h */	size_type   mnPosition;
		/* 18h */	size_type   mnSize;
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(StreamChild) == 0x1C, "sizeof(StreamChild) != 1Ch");

	namespace Addresses(StreamChild)
	{
		DeclareAddress(AddRef, SelectAddress(0x93BB70, 0x93C350, 0x93C350));
		DeclareAddress(Release, SelectAddress(0x93BD60, 0x93C360, 0x93C360));
		DeclareAddress(GetType, SelectAddress(0x923C40, 0x93B780, 0x93B780));
		DeclareAddress(GetAccessFlags, SelectAddress(0x93BC20, 0x93B630, 0x93B630));
		DeclareAddress(GetState, SelectAddress(0x93BC00, 0x93B640, 0x93B640));
		DeclareAddress(Close, SelectAddress(0xFC8510, 0x93B610, 0x93B610));
		DeclareAddress(GetSize, SelectAddress(0x101B0F0, 0x6C0230, 0x6C0230));
		DeclareAddress(SetSize, SelectAddress(0x93BC40, 0xDDE980, 0xDDE930));
		DeclareAddress(GetPosition, SelectAddress(0x93BC50, 0x93B660, 0x93B660));
		DeclareAddress(SetPosition, SelectAddress(0x93BCB0, 0x93B670, 0x93B670));
		DeclareAddress(GetAvailable, SelectAddress(0x93BCC0, 0x93B6D0, 0x93B6D0));
		DeclareAddress(Read, SelectAddress(0xA37650, 0x93B6E0, 0x93B6E0));
		DeclareAddress(Flush, SelectAddress(0x951320, 0xB1FB00, 0xB1FB30));
		DeclareAddress(Write, SelectAddress(0x93BB90, 0x950E00, 0x950E00));

		DeclareAddress(Open, SelectAddress(0, 0x93B5A0, 0x93B5A0));
	}

}