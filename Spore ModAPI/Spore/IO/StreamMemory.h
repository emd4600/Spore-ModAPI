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

#include <Spore\ICoreAllocator.h>
#include <Spore\Object.h>
#include <Spore\IO\EAIOZoneObject.h>
#include <Spore\IO\IStream.h>

#define MemoryStreamPtr eastl::intrusive_ptr<IO::MemoryStream>

namespace IO
{
	///
	/// Implements a basic ref-counted pointer.
	///
	/// This class is meant to be used like a COM object. When this object's 
	/// reference count goes to zero, the memory it holds is deleted and then
	/// this object calls 'delete this'. This class is similar to but doesn't
	/// work exactly the same as Boost's shared_ptr template.
	/// A typical usage pattern is like so:
	///     SharedPointer* pSP = new SharedPointer(1000);
	///     pSP->AddRef();
	///     pSP->Release();
	///
	class SharedPointer : public IVirtual, public EAIOZoneObject
	{
	public:
		typedef ICoreAllocator Allocator;

		SharedPointer(void* pData, bool bFreeData, Allocator* pAllocator)
			: mpAllocator(pAllocator ? pAllocator : IO::GetAllocator())
			, mpData((uint8_t*)pData)
			, mnRefCount(0)
			, mbFreeData(bFreeData)
		{
		}


		SharedPointer(size_type nSize, const char* pName)
			: mpAllocator(IO::GetAllocator())
			, mpData((uint8_t*)mpAllocator->Alloc((size_t)nSize, pName ? pName : "EAStreamMemory/data", 0))
			, mnRefCount(0)
			, mbFreeData(true)
		{
		}


		SharedPointer(size_type nSize, Allocator* pAllocator, const char* pName)
			: mpAllocator(pAllocator ? pAllocator : IO::GetAllocator())
			, mpData((uint8_t*)mpAllocator->Alloc((size_t)nSize, pName ? pName : "EAStreamMemory/data", 0))
			, mnRefCount(0)
			, mbFreeData(true)
		{
		}

		virtual ~SharedPointer();


		void*      GetPointer();
		int        AddRef();
		int        Release();
		Allocator* GetAllocator() const;

	protected:
		/* 08h */	int         mnRefCount;
		/* 0Ch */	Allocator*  mpAllocator;
		/* 10h */	uint8_t*    mpData;
		/* 14h */	bool        mbFreeData; // If true, we free the data when done.
	};

	static_assert(sizeof(SharedPointer) == 0x18, "sizeof(SharedPointer) != 18h");

	///
	/// Implements an memory-based stream that supports the IStream interface.
	///
	/// This class is not inherently thread-safe. As a result, thread-safe usage 
	/// between multiple threads requires higher level coordination, such as a mutex.
	///
	class MemoryStream : public IStream
	{
	public:
		typedef ICoreAllocator Allocator;

		/// enum Options
		/// Specifies policies regarding the internal operation of this class.
		enum Options
		{
			kOptionNone = 0,    /// No options
			kOptionResizeEnabled = 1,    /// 0 or 1. Default is disabled.  If set, then the buffer is automatically resized on beyond-bounds position sets, beyond-bounds writes, and beyond-bounds SetSize calls.
			kOptionResizeFactor = 2,    /// 1.0+    Default is 1.5.       Specifies how much a resize multiplies in size; is applied before kOptionResizeIncrement. Can be 1.0 if kOptionResizeIncrement > 0.
			kOptionResizeIncrement = 3,    /// 0.0+    Default is 0.0.       Specifies how much a resize increments; is applied after kOptionResizeFactor. Can be set to zero if kOptionResizeFactor is > 1.
			kOptionClearNewMemory  = 4     /// 0 or 1. Default is 0.         If set, then newly allocated space is cleared to zero. Otherwise the space is left as it comes from the memory allocator.
		};

		static const uint32_t kType = 0x347223d2;

	public:
		MemoryStream(const char* pName = NULL);
		MemoryStream(SharedPointer* pSharedPointer = NULL, size_type nSize = 0, const char* pName = NULL);
		MemoryStream(void* pData, size_type nSize, bool bUsePointer, bool bFreePointer = true, Allocator* pAllocator = NULL, const char* pName = NULL); // If bUsePointer is true, then we take over ownership of pData instead of copying from it.

		~MemoryStream();

		float   GetOption(Options option) const;
		void    SetOption(Options option, float fValue);

		SharedPointer* GetSharedPointer();

		void*   GetData() const;
		bool    SetData(SharedPointer* pSharedPointer, size_type nSize);
		bool    SetDataRaw(void* pData, size_type nSize, bool bUsePointer, bool bFreePointer = true, Allocator *pAllocator = NULL);

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


	protected:
		/* 04h */	SharedPointer* mpSharedPointer;     /// Pointer to memory block.
		/* 08h */	int            mnRefCount;          /// Reference count. May or may not be in use.
		/* 0Ch */	size_type      mnSize;              /// The size of the stream, in bytes.
		/* 10h */	size_type      mnCapacity;          /// The size of the memory buffer, in bytes.
		/* 14h */	size_type      mnPosition;          /// Current position within memory block.
		/* 18h */	bool           mbResizeEnabled;     /// True if resizing is enabled.
		/* 19h */	bool           mbClearNewMemory;    /// True if clearing of newly allocated memory is enabled.
		/* 1Ch */	float          mfResizeFactor;      /// Specifies how capacity is increased.
		/* 20h */	int            mnResizeIncrement;   /// Specifies how capacity is increased.
	};


	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(MemoryStream) == 0x24, "sizeof(MemoryStream) != 24h");

	namespace Addresses(MemoryStream)
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

		DeclareAddress(SetData);
		DeclareAddress(SetDataRaw);
		DeclareAddress(GetOption);
		DeclareAddress(SetOption);
	}

	///////////////////////////////////////////////////////////////////////////////
	// SharedPointer
	///////////////////////////////////////////////////////////////////////////////


	inline SharedPointer* MemoryStream::GetSharedPointer()
	{
		return mpSharedPointer;
	}


	inline int SharedPointer::AddRef()
	{
		return ++mnRefCount;
	}


	inline SharedPointer::Allocator* SharedPointer::GetAllocator() const
	{
		return mpAllocator;
	}

	inline int SharedPointer::Release()
	{
		if (mnRefCount > 1)
			return --mnRefCount;
		delete this;
		return 0;
	}



	///////////////////////////////////////////////////////////////////////////////
	// MemoryStream
	///////////////////////////////////////////////////////////////////////////////

	inline void* MemoryStream::GetData() const
	{
		if (mpSharedPointer)
			return mpSharedPointer->GetPointer();
		return 0;
	}

	inline void* SharedPointer::GetPointer()
	{
		return mpData;
	}
}