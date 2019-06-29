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

#include <Spore\IO\Allocator.h>
#include <Spore\IO\IStream.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\PFRecordRead.h>
#include <Spore\Resource\PFRecordWrite.h>
#include <Spore\Resource\PFIndexModifiable.h>

namespace IO
{
	using IO::IStream;

	/////////////////////
	//// Allocator.h ////
	/////////////////////

	auto_STATIC_METHOD_(IO, ICoreAllocator*, GetAllocator);

	/////////////////////

	//////////////////////////
	//// EAIOZoneObject.h ////
	//////////////////////////

	void* EAIOZoneObject::operator new(size_t n, ICoreAllocator* pAllocator, const char* pName)
	{
		return STATIC_CALL(GetAddress(0x9264E0, 0x926270, 0x926270), void*, PARAMS(size_t n, ICoreAllocator* pAllocator, const char* pName), PARAMS(n, pAllocator, pName));
	}

	void* EAIOZoneObject::operator new(size_t n)
	{
		return operator new(n, IO::GetAllocator(), nullptr);
	}

	void EAIOZoneObject::operator delete(void* p)
	{
		operator delete(p, IO::GetAllocator(), nullptr);
	}

	void EAIOZoneObject::operator delete(void* p, ICoreAllocator* pAllocator, const char* pName)
	{
		STATIC_CALL(GetAddress(0x926560, 0x9262F0, 0x9262F0), void, PARAMS(void* p), PARAMS(p));
	}

	//////////////////////////
}

namespace Resource
	{
	//////////////////////////////
	//// DatabasePackedFile.h ////
	//////////////////////////////

	DatabasePackedFile::DatabasePackedFile(const wchar_t* pPath, ICoreAllocator* pAllocator)
		: mnRefCount(0)
		, mbNeedsToRelease(false)
		, mpAllocator(pAllocator == nullptr ? IO::GetAllocator() : pAllocator)
		, mnFileAccess(0)
		, field_18(0)
		, field_1C(false)
		, field_1D(true)
		, mFilePath()
		, mFileStream()
		, mFileOffset(0)
		, mpCurrentStream(nullptr)
		, mpDataBuffer(nullptr)
		, mpBufferSize(0)
		, mnBufferOffset(0)

		, mIndexMutex(nullptr, true)
		, mReadWriteMutex(nullptr, true)

		, mpIndex(nullptr)
		, field_2D4(false)
		, field_2D8(0)
		, field_2DC(0)
		, field_2E0(true)
		, field_2E4(0.95f)
		, field_2E8()
		// , field_304(0)
		, field_308(0)
		, field_30C(0)
		, field_310(0)
		, field_314(0)
		, field_318(0)
		, field_31C(0)
		, field_320(0)
		, mnIndexOffset(0)
		, mnIndexCount(0)
		, mnIndexSize(0)
		, field_330(false)
		, field_334(0x13)
		, field_338(0.15f)

		, field_33C()
		, field_35C()

		, field_37C(0)
		, field_37D(0)
		, mpResourceMan(nullptr)
	{
		if (pPath != nullptr)
		{
			DatabasePackedFile::SetPath(pPath);
		}
	}

	DatabasePackedFile::~DatabasePackedFile()
	{
		DatabasePackedFile::ReleaseResources();
	}

	int DatabasePackedFile::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}

	int DatabasePackedFile::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			mnRefCount = 0;
			delete (EAIOZoneObject*) this;
		}
		return mnRefCount;
	}

	void* DatabasePackedFile::Cast(uint32_t type) const
	{
		if (type == DatabasePackedFile::TYPE)
		{
			return (DatabasePackedFile*) this;
		}
		else if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else
		{
			return nullptr;
		}
	}


	DatabasePackedFile::Unknown::Unknown()
		: field_0(-1)
		, field_4()
	{
	}

	bool DatabasePackedFile::NeedsToRelease()
	{
		if (!mbNeedsToRelease)
		{
			mbNeedsToRelease = true;
		}

		return true;
	}

	EAIOZoneObject_AMBIGOUS(DatabasePackedFile);

	bool DatabasePackedFile::ReleaseResources()
	{
		if (!mbNeedsToRelease)
		{
			if (mnFileAccess != 0)
			{
				Save();
			}

			ReleaseObject(mpIndex);
			mpIndex = nullptr;
			mpCurrentStream = nullptr;
		}

		return true;
	}


	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, uint32_t, GetType);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, int, GetReferenceCount);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, int, UseIndexMutex, PARAMS(bool bLock), PARAMS(bLock));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, Load, PARAMS(int nDesiredAccess, int nCreateDisposition, bool arg_8), PARAMS(nDesiredAccess, nCreateDisposition, arg_8));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Save);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, int, GetAccessFlags);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Write);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, wchar_t*, GetPath);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, SetPath, PARAMS(const wchar_t* path), PARAMS(path));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, size_t, GetFiles, PARAMS(PFIndexModifiable::KeysVector& dstVector, IResourceFilter* filter), PARAMS(dstVector, filter));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, GetFile, PARAMS(const ResourceKey& name, IPFRecord** pDst, int nDesiredAccess, int nCreateDisposition, bool arg_10, DBPFItem* pDstInfo), PARAMS(name, pDst, nDesiredAccess, nCreateDisposition, arg_10, pDstInfo));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, int, func38h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, func3Ch, PARAMS(IPFRecord* pRecord), PARAMS(pRecord));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, RemoveFile, PARAMS(ResourceKey& name), PARAMS(name));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, SetResourceManager, PARAMS(bool arg_0, cResourceManager* pResourceMan, bool arg_8), PARAMS(arg_0, pResourceMan, arg_8));
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, ICoreAllocator*, GetAllocator);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, IStream*, GetStream);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, SetStream, PARAMS(IStream* pStream), PARAMS(pStream));

	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordRead*, CreatePFRecordRead, PARAMS(int nDesiredAccess, DBPFItem* info, ResourceKey& key), PARAMS(nDesiredAccess, info, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordRead*, CreatePFRecordReadCopy, PARAMS(int nDesiredAccess, PFRecordRead* pOther, ResourceKey& key), PARAMS(nDesiredAccess, pOther, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordWrite*, CreatePFRecordWriteData, PARAMS(int nDesiredAccess, void* pData, size_t nSize, ResourceKey& key), PARAMS(nDesiredAccess, pData, nSize, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordWrite*, CreatePFRecordWrite, PARAMS(int nDesiredAccess, size_t nChunkOffset, size_t nSize, ResourceKey& key), PARAMS(nDesiredAccess, nChunkOffset, nSize, key));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Read);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, ReadHeader);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Reset);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, IsReadyForWrite);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, IsValidHeader, PARAMS(char* header), PARAMS(header));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, ReadIndex);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, WriteIndex);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, StreamCanContainFileData);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFIndexModifiable*, CreatePFIndexModifiable, PARAMS(int nDesiredAccess), PARAMS(nDesiredAccess));
	auto_METHOD_VIRTUAL_VOID(DatabasePackedFile, DatabasePackedFile, ReleaseObject, PARAMS(IO::EAIOZoneObject* pObject), PARAMS(pObject));
	auto_METHOD_VIRTUAL_VOID_(DatabasePackedFile, DatabasePackedFile, RenovateIndex);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, func90h);

	auto_METHOD(DatabasePackedFile, int, ReadBytes, PARAMS(void* pDst, size_t nSize), PARAMS(pDst, nSize));
	auto_METHOD(DatabasePackedFile, bool, ReadData, PARAMS(void* pDst, size_t nChunkOffset, size_t nSize), PARAMS(pDst, nChunkOffset, nSize));

	//////////////////////////////

	////////////////////////
	//// PFRecordRead.h ////
	////////////////////////

	PFRecordRead::PFRecordRead(DBPFItem& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: IPFRecord(PFRecordRead::kType, name, pParentDBPF, IO::kAccessFlagRead)
		, field_24(0)
		, field_28(-1)
		, mInternalBuffer("ResourceMan/PFRecordRead")
		, mDBPFItem(itemInfo)
		, mnOffset(0)
		, mnSize(0)
		, mnFlags(false)
		, mnStreamRefCount(1)
	{
		mInternalBuffer.AddRef();

		if (mDBPFItem.mFlags == 0)
		{
			mnSize = mDBPFItem.mnCompressedSize;
			if (mnSize <= 512) mnFlags = kPFRRDataFitsBuffer;
		}
		else
		{
			mnSize = mDBPFItem.mnMemorySize;
			mnFlags = kPFRRDataFitsBuffer;
		}
	}

	PFRecordRead::PFRecordRead(PFRecordRead* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: IPFRecord(PFRecordRead::kType, name, pParentDBPF, IO::kAccessFlagRead)
		, field_24(0)
		, field_28(-1)
		, mInternalBuffer("ResourceMan/PFRecordRead")
		, mDBPFItem(pOther->mDBPFItem)
		, mnOffset(0)
		, mnSize(pOther->mnSize)
		, mnFlags(pOther->mnFlags)
		, mnStreamRefCount(1)
	{
		mInternalBuffer.AddRef();

		if (mnFlags & kPFRRBufferReady)
		{
			mInternalBuffer.SetData(pOther->mInternalBuffer.GetSharedPointer(), pOther->mInternalBuffer.GetSize());
			mInternalBuffer.SetPosition(0);
		}
	}

	PFRecordRead::~PFRecordRead()
	{
		if (mnFileAccess != 0)
		{
			mpParentDBPF->func3Ch(this);
		}
	}

	int PFRecordRead::AddRef()
	{
		return ThreadedObject::AddRef();
	}

	int PFRecordRead::Release()
	{
		return ThreadedObject::Release();
	}

	auto_METHOD_(PFRecordRead, ResourceKey&, GetName);
	auto_METHOD_VOID(PFRecordRead, SetName, PARAMS(const ResourceKey& name), PARAMS(name));
	auto_METHOD_(PFRecordRead, IStream*, GetStream);
	auto_METHOD_const_(PFRecordRead, DatabasePackedFile*, GetParentDBPF);

	auto_METHOD_(PFRecordRead, bool, Open);
	auto_METHOD_(PFRecordRead, bool, Close);
	auto_METHOD_(PFRecordRead, int, func28h);


	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, uint32_t, GetType);
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, int, GetAccessFlags);
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, IO::FileError, GetState);
	// auto_METHOD_(		PFRecordRead, bool,	Close);  // Already overriden with IPFRecord

	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, IO::size_type, GetSize);
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, bool, SetSize, PARAMS(IO::size_type size), PARAMS(size));
	auto_METHOD_VIRTUAL_const(PFRecordRead, IStream, int, GetPosition, PARAMS(IO::PositionType positionType), PARAMS(positionType));
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, bool, SetPosition, PARAMS(int distance, IO::PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, int, GetAvailable);

	auto_METHOD_VIRTUAL(PFRecordRead, IStream, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_VIRTUAL_(PFRecordRead, IStream, bool, Flush);
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	////////////////////////

	/////////////////////////
	//// PFRecordWrite.h ////
	/////////////////////////

	PFRecordWrite::PFRecordWrite(void* pData, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: IPFRecord(kType, name, pParentDBPF, IO::kAccessFlagReadWrite)
		, field_24("ResourceMan/PFRecordWrite")
		, field_48((const char*)nullptr)
		, field_274(false)
		, mnStreamRefCount(0)
	{
		field_24.AddRef();
		field_48.AddRef();

		field_24.SetOption(IO::MemoryStream::kOptionResizeEnabled, 1.0f);

		field_24.SetDataRaw(pData, nSize, bUsePointer, true, mpParentDBPF->GetAllocator());

	}

	PFRecordWrite::PFRecordWrite(size_t nChunkOffset, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: IPFRecord(kType, name, pParentDBPF, IO::kAccessFlagReadWrite)
		, field_24("ResourceMan/PFRecordWrite")
		, field_48((const char*)nullptr)
		, field_274(false)
		, mnStreamRefCount(0)
	{
		field_24.AddRef();
		field_48.AddRef();

		field_24.SetOption(IO::MemoryStream::kOptionResizeEnabled, 1.0f);
		field_24.SetOption(IO::MemoryStream::kOptionResizeFactor, 1.5f);
		field_24.SetOption(IO::MemoryStream::kOptionResizeIncrement, 1024.0f);

		if (nSize > 0)
		{
			if (nSize > 2000000 && !field_274)
			{
				field_274 = true;

				//TODO
			}

			if (field_24.SetDataRaw(nullptr, nSize, false, true, mpParentDBPF->GetAllocator()))
			{
				mpParentDBPF->ReadBytes(field_24.GetData(), nSize);
			}
		}
	}

	PFRecordWrite::~PFRecordWrite()
	{
		mpParentDBPF->func3Ch(this);

		mpParentDBPF = nullptr;
		mnFileAccess = 0;
		field_274 = false;
		mnStreamRefCount = 0;

		if (field_48.GetAccessFlags() != 0)
		{
			field_48.Close();

			wchar_t fileName[IO::kMaxPathLength];
			field_48.GetPath((char16_t*)fileName, IO::kMaxPathLength);

			DeleteFileW(fileName);
		}
	}

	int PFRecordWrite::AddRef()
	{
		return ThreadedObject::AddRef();
	}

	int PFRecordWrite::Release()
	{
		return ThreadedObject::Release();
	}


	auto_METHOD_(PFRecordWrite, ResourceKey&, GetName);
	auto_METHOD_VOID(PFRecordWrite, SetName, PARAMS(const ResourceKey& name), PARAMS(name));
	auto_METHOD_(PFRecordWrite, IO::IStream*, GetStream);
	auto_METHOD_const_(PFRecordWrite, DatabasePackedFile*, GetParentDBPF);

	auto_METHOD_(PFRecordWrite, bool, Open);
	auto_METHOD_(PFRecordWrite, bool, Close);
	auto_METHOD_(PFRecordWrite, int, func28h);


	auto_METHOD_const_(PFRecordWrite, uint32_t, GetType);
	auto_METHOD_const_(PFRecordWrite, int, GetAccessFlags);
	auto_METHOD_const_(PFRecordWrite, IO::FileError, GetState);
	// auto_METHOD_(		PFRecordWrite, bool,	Close);  // Already overriden with IPFRecord

	auto_METHOD_const_(PFRecordWrite, IO::size_type, GetSize);
	auto_METHOD(PFRecordWrite, bool, SetSize, PARAMS(IO::size_type size), PARAMS(size));
	auto_METHOD_const(PFRecordWrite, int, GetPosition, PARAMS(IO::PositionType positionType), PARAMS(positionType));
	auto_METHOD(PFRecordWrite, bool, SetPosition, PARAMS(int distance, IO::PositionType positionType), PARAMS(distance, positionType));
	auto_METHOD_const_(PFRecordWrite, int, GetAvailable);

	auto_METHOD(PFRecordWrite, int, Read, PARAMS(void* pData, size_t nSize), PARAMS(pData, nSize));
	auto_METHOD_(PFRecordWrite, bool, Flush);
	auto_METHOD(PFRecordWrite, int, Write, PARAMS(const void* pData, size_t nSize), PARAMS(pData, nSize));

	/////////////////////////

	/////////////////////////////
	//// PFIndexModifiable.h ////
	/////////////////////////////

	PFIndexModifiable::PFIndexModifiable(ICoreAllocator* pAllocator)
		: mpParentAllocator(0)
		, mAllocator(pAllocator, sizeof(ItemsMap::value_type) * 4, sizeof(ItemsMap::value_type))
		, mItemsMap(ICoreAllocatorAdapter(nullptr, &mAllocator))
	{
	}


	auto_METHOD_(PFIndexModifiable, bool, func04h);
	auto_METHOD_(PFIndexModifiable, bool, IsEmpty);
	auto_METHOD_(PFIndexModifiable, size_t, GetFileCount);
	auto_METHOD_(PFIndexModifiable, bool, Reset);
	auto_METHOD_(PFIndexModifiable, size_t, GetTotalDiskSize);
	auto_METHOD_(PFIndexModifiable, size_t, GetDataEnd);
	auto_METHOD(PFIndexModifiable, size_t, GetFiles, PARAMS(KeysVector& dstVector, IResourceFilter* filter), PARAMS(dstVector, filter));
	auto_METHOD(PFIndexModifiable, size_t, GetAllFiles, PARAMS(KeysVector& dstVector), PARAMS(dstVector));
	auto_METHOD(PFIndexModifiable, bool, func24h, PARAMS(int arg_0, size_t fileDataBegin, size_t fileDataEnd), PARAMS(arg_0, fileDataBegin, fileDataEnd));

	auto_METHOD(PFIndexModifiable, DBPFItem*, GetFileInfo, PARAMS(const ResourceKey& fileName), PARAMS(fileName));
	auto_METHOD(PFIndexModifiable, DBPFItem&, PutFileInfo, PARAMS(const ResourceKey& fileName, DBPFItem& info), PARAMS(fileName, info));
	auto_METHOD(PFIndexModifiable, bool, RemoveFile, PARAMS(const ResourceKey& fileName, DBPFItem& dstInfo), PARAMS(fileName, dstInfo));

	auto_METHOD(PFIndexModifiable, bool, Read, PARAMS(void* pIndexData, size_t nIndexSize, size_t nIndexCount, bool arg_C), PARAMS(pIndexData, nIndexSize, nIndexCount, arg_C));
	auto_METHOD(PFIndexModifiable, bool, Write, PARAMS(void*& pDstIndexData, size_t& nDstIndexSize, size_t nIndexCount, bool arg_C), PARAMS(pDstIndexData, nDstIndexSize, nIndexCount, arg_C));

	auto_METHOD_VOID_(PFIndexModifiable, SetIsSaved);
	auto_METHOD(PFIndexModifiable, bool, CheckFilesInRange, PARAMS(size_t fileDataBegin, size_t fileDataEnd), PARAMS(fileDataBegin, fileDataEnd));
	auto_METHOD(PFIndexModifiable, bool, CheckFilesInSizeRange, PARAMS(size_t fileDataBegin, size_t size), PARAMS(fileDataBegin, size));

	/////////////////////////////


}
