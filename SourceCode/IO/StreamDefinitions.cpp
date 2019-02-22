/****************************************************************************
* Copyright (C) 2018 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include <Spore\IO\FileStream.h>
#include <Spore\IO\StreamAdapter.h>
#include <Spore\IO\StreamBuffer.h>
#include <Spore\IO\StreamChild.h>
#include <Spore\IO\StreamFixedMemory.h>
#include <Spore\IO\StreamMemory.h>
#include <Spore\IO\StreamNull.h>

namespace IO
{
	//////////////////////
	//// FileStream.h ////
	//////////////////////

	FileStream::FileStream(const char* pPath8)
		: mhFile(reinterpret_cast<void*>(-1)),
		mnRefCount(0),
		mnAccessFlags(0),
		mnCD(0),
		mnSharing(0),
		mnUsageHints(kUsageHintNone),
		mnLastError(0),
		mnSize(static_cast<size_type>(-1))
	{
		mpPath16[0] = 0;
		FileStream::SetPathCString(pPath8); // Note that in a constructor, the virtual function mechanism is inoperable.
	}


	FileStream::FileStream(const char16_t* pPath16)
		: mhFile(reinterpret_cast<void*>(-1)),
		mnRefCount(0),
		mnAccessFlags(0),
		mnCD(0),
		mnSharing(0),
		mnUsageHints(kUsageHintNone),
		mnLastError(0),
		mnSize(static_cast<size_type>(-1))
	{
		mpPath16[0] = 0;
		FileStream::SetPath(pPath16); // Note that in a constructor, the virtual function mechanism is inoperable.
	}

	FileStream::~FileStream()
	{
		FileStream::Close(); // Note that in a destructor, the virtual function mechanism is inoperable.
	}

	auto_METHOD_(FileStream, int, AddRef);
	auto_METHOD_(FileStream, int, Release);

	auto_METHOD_const_(FileStream, uint32_t, GetType);
	auto_METHOD_const_(FileStream, int, GetAccessFlags);
	auto_METHOD_const_(FileStream, FileError, GetState);
	auto_METHOD_(FileStream, bool, Close);

	auto_METHOD_const_(FileStream, size_type, GetSize);
	auto_METHOD(FileStream, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(FileStream, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(FileStream, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(FileStream, int, GetAvailable);

	auto_METHOD(FileStream, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(FileStream, bool, Flush);
	auto_METHOD(FileStream, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	auto_METHOD_VOID(FileStream, SetPath, PARAMS(const char16_t* pPath16), PARAMS(pPath16));
	auto_METHOD_VOID(FileStream, SetPathCString, PARAMS(const char* pPath8), PARAMS(pPath8));
	auto_METHOD(FileStream, size_t, GetPath, PARAMS(char16_t* pPath16, size_t nPathLength), PARAMS(pPath16, nPathLength));
	auto_METHOD(FileStream, size_t, GetPathCString, PARAMS(char* pPath8, size_t nPathLength), PARAMS(pPath8, nPathLength));
	auto_METHOD(FileStream, bool, Open, PARAMS(int nAccessFlags, int nCreationDisposition, int nSharing, int nUsageHints), PARAMS(nAccessFlags, nCreationDisposition, nSharing, nUsageHints));


	//////////////////////


	/////////////////////////
	//// StreamAdapter.h ////
	/////////////////////////


	auto_STATIC_METHOD(IO, bool, ReadBool8, PARAMS(IStream* pIS, bool& value), PARAMS(pIS, value));
	auto_STATIC_METHOD(IO, bool, ReadInt8, PARAMS(IStream* pIS, int8_t* value, size_type count), PARAMS(pIS, value, count));
	auto_STATIC_METHOD(IO, bool, ReadUInt8, PARAMS(IStream* pIS, uint8_t* value, size_type count), PARAMS(pIS, value, count));
	auto_STATIC_METHOD(IO, bool, ReadInt16, PARAMS(IStream* pIS, int16_t* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));
	auto_STATIC_METHOD(IO, bool, ReadUInt16, PARAMS(IStream* pIS, uint16_t* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));
	auto_STATIC_METHOD(IO, bool, ReadInt32, PARAMS(IStream* pIS, int32_t* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));
	auto_STATIC_METHOD(IO, bool, ReadUInt32, PARAMS(IStream* pIS, uint32_t* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));
	auto_STATIC_METHOD(IO, bool, ReadFloat, PARAMS(IStream* pIS, float* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));

	auto_STATIC_METHOD(IO, bool, ReadResourceID, PARAMS(IStream* pIS, ResourceID* value, size_type count, Endian endianSource), PARAMS(pIS, value, count, endianSource));
	auto_STATIC_METHOD(IO, IStream*, ReadCString, PARAMS(IStream* pIS, eastl::string8& str), PARAMS(pIS, str));
	auto_STATIC_METHOD(IO, size_type, ReadLine, PARAMS(IStream* pIS, char* pLine, size_type nLineCapacity), PARAMS(pIS, pLine, nLineCapacity));


	auto_STATIC_METHOD(IO, bool, WriteInt8, PARAMS(IStream* pOS, const int8_t* value, size_type count), PARAMS(pOS, value, count));
	auto_STATIC_METHOD(IO, bool, WriteUInt8, PARAMS(IStream* pOS, const uint8_t* value, size_type count), PARAMS(pOS, value, count));
	auto_STATIC_METHOD(IO, bool, WriteInt16, PARAMS(IStream* pOS, const int16_t* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));
	auto_STATIC_METHOD(IO, bool, WriteUInt16, PARAMS(IStream* pOS, const uint16_t* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));
	auto_STATIC_METHOD(IO, bool, WriteInt32, PARAMS(IStream* pOS, const int32_t* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));
	auto_STATIC_METHOD(IO, bool, WriteUInt32, PARAMS(IStream* pOS, const uint32_t* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));

	auto_STATIC_METHOD(IO, bool, WriteFloat, PARAMS(IStream* pOS, const float* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));
	auto_STATIC_METHOD(IO, bool, WriteResourceID, PARAMS(IStream* pOS, const ResourceID* value, size_type count, Endian endianDestination), PARAMS(pOS, value, count, endianDestination));
	auto_STATIC_METHOD(IO, bool, WriteLine, PARAMS(IStream* pOS, const char8_t* pLineSource, size_type nLineLength, LineEnd lineEndToUse), PARAMS(pOS, pLineSource, nLineLength, lineEndToUse));

	/////////////////////////


	////////////////////////
	//// StreamBuffer.h ////
	////////////////////////


	auto_METHOD(StreamBuffer, bool, SetBufferSizes, PARAMS(size_type nReadBufferSize, size_type nWriteBufferSize), PARAMS(nReadBufferSize, nWriteBufferSize));
	auto_METHOD(StreamBuffer, bool, SetStream, PARAMS(IStream* pStream), PARAMS(pStream));
	auto_METHOD(StreamBuffer, bool, FillWriteBuffer, PARAMS(const char* pData, size_type nSize), PARAMS(pData, nSize));
	auto_METHOD_(StreamBuffer, bool, FlushWriteBuffer);

	auto_METHOD_(StreamBuffer, int, AddRef);
	auto_METHOD_(StreamBuffer, int, Release);

	auto_METHOD_const_(StreamBuffer, uint32_t, GetType);
	auto_METHOD_const_(StreamBuffer, int, GetAccessFlags);
	auto_METHOD_const_(StreamBuffer, FileError, GetState);
	auto_METHOD_(StreamBuffer, bool, Close);

	auto_METHOD_const_(StreamBuffer, size_type, GetSize);
	auto_METHOD(StreamBuffer, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(StreamBuffer, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(StreamBuffer, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(StreamBuffer, int, GetAvailable);

	auto_METHOD(StreamBuffer, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(StreamBuffer, bool, Flush);
	auto_METHOD(StreamBuffer, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));


	StreamBuffer::StreamBuffer(size_type nReadBufferSize, size_type nWriteBufferSize, IStream* pStream)
		: mpStream(NULL),
		mnRefCount(0),

		mnPositionExternal(0),
		mnPositionInternal(0),

		mpReadBuffer(NULL),
		mnReadBufferSize(0),
		mnReadBufferStartPosition(0),
		mnReadBufferUsed(0),

		mpWriteBuffer(NULL),
		mnWriteBufferSize(0),
		mnWriteBufferStartPosition(0),
		mnWriteBufferUsed(0)
	{
		SetBufferSizes(nReadBufferSize, nWriteBufferSize);
		SetStream(pStream);
	}


	StreamBuffer::~StreamBuffer()
	{
		SetStream(NULL); // This will flush the write buffer.
		if (mpReadBuffer)
		{
			IO::GetAllocator()->Free(mpReadBuffer);
			mpReadBuffer = nullptr;
		}
		if (mpWriteBuffer)
		{
			IO::GetAllocator()->Free(mpWriteBuffer);
			mpWriteBuffer = nullptr;
		}
	}

	void StreamBuffer::GetBufferSizes(size_type& nReadBufferSize, size_type& nWriteBufferSize) const
	{
		nReadBufferSize = mnReadBufferSize;
		nWriteBufferSize = mnWriteBufferSize;
	}

	////////////////////////


	///////////////////////
	//// StreamChild.h ////
	///////////////////////



	StreamChild::StreamChild(IStream* pStreamParent, size_type nPosition, size_type nSize) :
		mnRefCount(0),
		mnAccessFlags(0),
		mpStreamParent(0),
		mnPositionParent(0),
		mnPosition(0),
		mnSize(0)
	{
		if (pStreamParent) {
			Open(pStreamParent, nPosition, nSize);
		}
	}

	auto_METHOD(StreamChild, bool, Open, PARAMS(IStream* pStreamParent, size_type nPosition, size_type nSize), PARAMS(pStreamParent, nPosition, nSize));

	auto_METHOD_(StreamChild, int, AddRef);
	auto_METHOD_(StreamChild, int, Release);

	auto_METHOD_const_(StreamChild, uint32_t, GetType);
	auto_METHOD_const_(StreamChild, int, GetAccessFlags);
	auto_METHOD_const_(StreamChild, FileError, GetState);
	auto_METHOD_(StreamChild, bool, Close);

	auto_METHOD_const_(StreamChild, size_type, GetSize);
	auto_METHOD(StreamChild, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(StreamChild, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(StreamChild, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(StreamChild, int, GetAvailable);

	auto_METHOD(StreamChild, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(StreamChild, bool, Flush);
	auto_METHOD(StreamChild, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	///////////////////////


	/////////////////////////////
	//// StreamFixedMemory.h ////
	/////////////////////////////


	auto_METHOD(FixedMemoryStream, bool, SetData, PARAMS(void* pData, size_type nSize), PARAMS(pData, nSize));

	auto_METHOD_(FixedMemoryStream, int, AddRef);
	auto_METHOD_(FixedMemoryStream, int, Release);

	auto_METHOD_const_(FixedMemoryStream, uint32_t, GetType);
	auto_METHOD_const_(FixedMemoryStream, int, GetAccessFlags);
	auto_METHOD_const_(FixedMemoryStream, FileError, GetState);
	auto_METHOD_(FixedMemoryStream, bool, Close);

	auto_METHOD_const_(FixedMemoryStream, size_type, GetSize);
	auto_METHOD(FixedMemoryStream, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(FixedMemoryStream, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(FixedMemoryStream, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(FixedMemoryStream, int, GetAvailable);

	auto_METHOD(FixedMemoryStream, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(FixedMemoryStream, bool, Flush);
	auto_METHOD(FixedMemoryStream, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	FixedMemoryStream::FixedMemoryStream(void* pData, size_type nSize)
		: mpData(pData)
		, mnRefCount(0)
		, mnSize(nSize)
		, mnCapacity(nSize)
		, mnPosition(0)
	{
	}

	/////////////////////////////


	////////////////////////
	//// StreamMemory.h ////
	////////////////////////

	SharedPointer::~SharedPointer()
	{
		if (mbFreeData)
			mpAllocator->Free(mpData);
	}

	MemoryStream::MemoryStream(const char* pName) :
		mpSharedPointer(NULL),
		mnRefCount(0),
		mnSize(0),
		mnCapacity(0),
		mnPosition(0),
		//mbClearNewMemory(false),
		mbResizeEnabled(false),
		mfResizeFactor(1.5f),
		mnResizeIncrement(0)
	{
	}

	MemoryStream::MemoryStream(SharedPointer* pSharedPointer, size_type nSize, const char* pName)
		: mpSharedPointer(NULL),
		mnRefCount(0),
		mnSize(0),
		mnCapacity(0),
		mnPosition(0),
		//mbClearNewMemory(false),
		mbResizeEnabled(false),
		mfResizeFactor(1.5f),
		mnResizeIncrement(0)
	{
		if (pSharedPointer && nSize)
			SetData(pSharedPointer, nSize);
	}


	MemoryStream::MemoryStream(void* pData, size_type nSize, bool bUsePointer, bool bFreePointer, Allocator *pAllocator, const char* pName)
		: mpSharedPointer(NULL),
		mnRefCount(0),
		mnSize(0),
		mnCapacity(0),
		mnPosition(0),
		//mbClearNewMemory(false),
		mbResizeEnabled(false),
		mfResizeFactor(1.5f),
		mnResizeIncrement(0)
	{
		if (pData || nSize)
			SetDataRaw(pData, nSize, bUsePointer, bFreePointer, pAllocator);
	}

	MemoryStream::~MemoryStream()
	{
		if (mpSharedPointer) mpSharedPointer->Release();
	}

	auto_METHOD_(MemoryStream, int, AddRef);
	auto_METHOD_(MemoryStream, int, Release);

	auto_METHOD_const_(MemoryStream, uint32_t, GetType);
	auto_METHOD_const_(MemoryStream, int, GetAccessFlags);
	auto_METHOD_const_(MemoryStream, FileError, GetState);
	auto_METHOD_(MemoryStream, bool, Close);

	auto_METHOD_const_(MemoryStream, size_type, GetSize);
	auto_METHOD(MemoryStream, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(MemoryStream, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(MemoryStream, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(MemoryStream, int, GetAvailable);

	auto_METHOD(MemoryStream, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(MemoryStream, bool, Flush);
	auto_METHOD(MemoryStream, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	auto_METHOD(MemoryStream, bool, SetData, PARAMS(SharedPointer* pSharedPointer, size_type nSize), PARAMS(pSharedPointer, nSize));
	auto_METHOD(MemoryStream, bool, SetDataRaw, PARAMS(void* pData, size_type nSize, bool bUsePointer, bool bFreePointer, Allocator *pAllocator), PARAMS(pData, nSize, bUsePointer, bFreePointer, pAllocator));
	auto_METHOD_const(MemoryStream, float, GetOption, PARAMS(Options option), PARAMS(option));
	auto_METHOD_VOID(MemoryStream, SetOption, PARAMS(Options option, float fValue), PARAMS(option, fValue));

	////////////////////////


	//////////////////////
	//// StreamNull.h ////
	//////////////////////

	StreamNull::StreamNull()
		: mnRefCount(0)
	{}

	auto_METHOD_(StreamNull, int, AddRef);
	auto_METHOD_(StreamNull, int, Release);

	auto_METHOD_const_(StreamNull, uint32_t, GetType);
	auto_METHOD_const_(StreamNull, int, GetAccessFlags);
	auto_METHOD_const_(StreamNull, FileError, GetState);
	auto_METHOD_(StreamNull, bool, Close);

	auto_METHOD_const_(StreamNull, size_type, GetSize);
	auto_METHOD(StreamNull, bool, SetSize, PARAMS(size_type size), PARAMS(size));
	auto_METHOD_const(StreamNull, int, GetPosition, PARAMS(PositionType positionType), PARAMS(positionType));
	auto_METHOD(StreamNull, bool, SetPosition, PARAMS(int distance, PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(StreamNull, int, GetAvailable);

	auto_METHOD(StreamNull, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(StreamNull, bool, Flush);
	auto_METHOD(StreamNull, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	//////////////////////
}