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
	const int kMaxPathLength = 260;      // NTFS allows at least 32767 characters, but most of  the Windows API limits the value to 260.

	class FileStream : public IStream
	{
	public:
		FileStream(const char* pPath8 = NULL);
		FileStream(const char16_t* pPath16);

		~FileStream();

		/* 04h */	virtual int AddRef();
		/* 08h */	virtual int Release();

		/* 0Ch */	virtual uint32_t	GetType() const;  // ?
		/* 10h */	virtual int			GetAccessFlags() const;
		/* 14h */	virtual FileError	GetState() const;
		/* 18h */	virtual bool		Close();

		/* 1Ch */	virtual size_type GetSize() const;
		/* 20h */	virtual bool	SetSize(size_type size);
		/* 24h */	virtual int		GetPosition(PositionType positionType = kPositionTypeBegin) const;
		/* 28h */	virtual bool	SetPosition(int distance, PositionType positionType = kPositionTypeBegin);
		/* 2Ch */	virtual int		GetAvailable() const;

		/* 30h */	virtual int		Read(void* pData, size_t nSize);
		/* 34h */	virtual bool	Flush();
		/* 38h */	virtual int		Write(const void* pData, size_t nSize);

		/* 3Ch */	virtual void    SetPath(const char16_t* pPath16);
		/* 40h */	virtual void    SetPathCString(const char* pPath8);
		/* 44h */	virtual size_t  GetPath(char16_t* pPath16, size_t nPathLength);
		/* 48h */	virtual size_t  GetPathCString(char* pPath8, size_t nPathLength);

		/* 4Ch */	virtual bool	Open(int nAccessFlags = kAccessFlagRead, int nCreationDisposition = kCDDefault, int nSharing = kShareRead, int nUsageHints = kUsageHintNone);

		static const uint32_t kType = 0x34722300;

	protected:
		/* 04h */	void*             mhFile;                     /// We defined as void* instead of HANDLE in order to simplify header includes. HANDLE is typedef'd to (void *) on all Windows platforms.
		/* 08h */	char16_t          mpPath16[kMaxPathLength];   /// Path for the file.
		/* 210h */	int               mnRefCount;                 /// Reference count, which may or may not be in use.
		/* 214h */	int               mnAccessFlags;              /// See enum AccessFlags.
		/* 218h */	int               mnCD;                       /// See enum CD (creation disposition).
		/* 21Ch */	int               mnSharing;                  /// See enum Share.
		/* 220h */	int               mnUsageHints;               /// See enum UsageHints.
		/* 224h */	mutable int       mnLastError;                /// Used for error reporting.
		/* 228h */	mutable size_type mnSize;                     /// Used for caching the file size, which is sometimes useful. 
	};


	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(FileStream) == 0x22C, "sizeof(FileStream) != 22Ch");

	namespace Addresses(FileStream)
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
		DeclareAddress(SetPath);
		DeclareAddress(SetPathCString);
		DeclareAddress(GetPath);
		DeclareAddress(GetPathCString);
		DeclareAddress(Open);
	}

}