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

#define StreamChildPtr eastl::intrusive_ptr<IO::StreamChild>

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

		static const uint32_t kType = 0x3472233A;

	protected:
		/* 04h */	int         mnRefCount;
		/* 08h */	AccessFlags mnAccessFlags;
		/* 0Ch */	IStream*    mpStreamParent;
		/* 10h */	size_type   mnPositionParent;
		/* 14h */	size_type   mnPosition;
		/* 18h */	size_type   mnSize;
	};
	ASSERT_SIZE(StreamChild, 0x1C);

	namespace Addresses(StreamChild)
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

		DeclareAddress(Open);
	}

}