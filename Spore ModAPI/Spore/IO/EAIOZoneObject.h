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

namespace IO
{
	///////////////////////////////////////////////////////////////////////////////
	///
	/// A class derived from EAIOZoneObject is able to be allocated from different 
	/// heaps without the owner of the object needing to know or care which heap
	/// the object came from or even what kind of allocator the object is using.
	/// The owner of the object can use 'delete' or the object can call 'delete'
	/// on itself (useful for reference counting systems) and the object will be 
	/// freed via the correct allocator.
	///
	/// Zone object uses the ICoreAllocator interface to allocate 
	/// and free.
	///
	/// Zone objects have a virtual destructor and thus a vtable. However, the user
	/// doesn't need to use any virtual functions in derived classes.
	///
	/// EAIOZoneObject-deriving classes can be created via EA_NEW, but don't have 
	/// to be created by it. They can be created by regular new as well.
	///
	/// Example usage:
	///     class Widget : public EAIOZoneObject
	///     {
	///         uint32_t mRefCount;
	///
	///         Widget()
	///            : mRefCount(0) { }
	///
	///         void AddRef()
	///             { ++mRefCount; }
	///
	///         void Release()
	///         {
	///             if(mRefCount > 1) 
	///                 --mRefCount;
	///             else
	///                 delete this; // Will use ICoreAllocator to free self.
	///         }
	///     };
	///
	///     Widget* pWidget = new(pCoreAllocator) Widget;
	///     pWidget->AddRef();
	///     pWidget->Release();
	///////////////////////////////////////////////////////////////////////////////
	class EAIOZoneObject
	{
	public:
		virtual ~EAIOZoneObject() {};

		static void operator delete(void* p);

		static void operator delete(void* p, ICoreAllocator* pAllocator, const char* pName);

		/// Example usage:
		///    Widget* pWidget = new(pCoreAllocator, "Widget") Widget;
		static void* operator new(size_t n, ICoreAllocator* pAllocator, const char* pName);

		static void* operator new(size_t n);
	};

}

// we must avoid ambigous call

#define EAIOZoneObject_AMBIGOUS_DECLARATION static void* operator new(size_t n, ICoreAllocator* pAllocator, const char* pName); \
static void* operator new(size_t n); \
static void operator delete(void* p, ICoreAllocator* pAllocator, const char* pName); \
static void operator delete(void* p);

#define EAIOZoneObject_AMBIGOUS(className) void* className::operator new(size_t n, ICoreAllocator* pAllocator, const char* pName) {return EAIOZoneObject::operator new(n, pAllocator, pName);} \
void* className::operator new(size_t n) { return EAIOZoneObject::operator new(n); } \
void className::operator delete(void* p, ICoreAllocator* pAllocator, const char* pName) { return EAIOZoneObject::operator delete(p, pAllocator, pName); }\
void className::operator delete(void* p) { return EAIOZoneObject::operator delete(p); }