#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\IO\Constants.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\DatabaseDirectoryFiles.h>
#include <Spore\Resource\PFRecordRead.h>
#include <Spore\Resource\PFRecordWrite.h>
#include <Spore\Resource\PFIndexModifiable.h>
#include <Spore\Resource\Paths.h>

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
		return STATIC_CALL(GetAddress(EAIOZoneObject, new_), void*,
			Args(size_t n, ICoreAllocator* pAllocator, const char* pName), Args(n, pAllocator, pName));
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
		STATIC_CALL(GetAddress(EAIOZoneObject, delete_), void, Args(void* p), Args(p));
	}

	//////////////////////////


	auto_STATIC_METHOD(Directory, bool, Exists, Args(const char16_t* path), Args(path));
	auto_STATIC_METHOD(Directory, bool, Create, Args(const char16_t* path), Args(path));
	auto_STATIC_METHOD(Directory, bool, Remove, Args(const char16_t* path, bool recursive), Args(path, recursive));

	auto_STATIC_METHOD(File, bool, Exists, Args(const char16_t* path), Args(path));
	auto_STATIC_METHOD(File, bool, Remove, Args(const char16_t* path), Args(path));
	auto_STATIC_METHOD(File, unsigned int, GetSize, Args(const char16_t* path), Args(path));
}

namespace Resource
{
	//////////////////////////////
	//// DatabasePackedFile.h ////
	//////////////////////////////

	DatabasePackedFile::DatabasePackedFile(const char16_t* pPath, ICoreAllocator* pAllocator)
		: mIsInitialized(false)
		, mpAllocator(pAllocator == nullptr ? IO::GetAllocator() : pAllocator)
		, mAccessFlags(IO::AccessFlags::None)
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
		mFileStream.AddRef();

		if (pPath)
		{
			DatabasePackedFile::SetLocation(pPath);
		}

		/*CALL(Address(0x8DA560), void,
			Args(DatabasePackedFile*, const char16_t*, ICoreAllocator *),
			Args(this, pPath, pAllocator));*/
	}

	DatabasePackedFile::~DatabasePackedFile()
	{
		DatabasePackedFile::Dispose();
	}

	int Database::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}

	int Database::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			mnRefCount = 0;
			delete (EAIOZoneObject*) this;
			return 0;
		}
		else {
			return mnRefCount;
		}
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


	PFHoleTable::PFHoleTable()
		: field_0(-1)
		, mRecords()
	{
	}

	bool DatabasePackedFile::Initialize()
	{
		if (!mIsInitialized)
		{
			mIsInitialized = true;
		}

		return true;
	}

	EAIOZoneObject_AMBIGOUS(DatabasePackedFile);

	bool DatabasePackedFile::Dispose()
	{
		if (!mIsInitialized)
		{
			if (mAccessFlags != IO::AccessFlags::None)
			{
				Close();
			}

			DestroyIndex(mpIndex);
			mpIndex = nullptr;
			mpCurrentStream = nullptr;
		}

		return true;
	}


	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, uint32_t, GetDatabaseType);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, int, GetRefCount);
	auto_METHOD_VIRTUAL_VOID(DatabasePackedFile, DatabasePackedFile, Lock, Args(bool bLock), Args(bLock));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, Open, Args(IO::AccessFlags nDesiredAccess, IO::CD nCreateDisposition, bool arg_8), Args(nDesiredAccess, nCreateDisposition, arg_8));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Close);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, IO::AccessFlags, GetAccessFlags);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, Flush);
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, const char16_t*, GetLocation);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, SetLocation, Args(const char16_t* path), Args(path));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, size_t, GetKeyList, Args(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter), Args(dstVector, filter));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, OpenRecord, Args(const ResourceKey& name, IRecord** pDst, IO::AccessFlags nDesiredAccess, IO::CD nCreateDisposition, bool arg_10, DBPFItem* pDstInfo), Args(name, pDst, nDesiredAccess, nCreateDisposition, arg_10, pDstInfo));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, int, GetOpenCount, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, CloseRecord, Args(IRecord* pRecord), Args(pRecord));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, DeleteRecord, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, Attach, Args(bool arg_0, IResourceManager* pResourceMan, bool arg_8), Args(arg_0, pResourceMan, arg_8));
	auto_METHOD_VIRTUAL_const_(DatabasePackedFile, DatabasePackedFile, ICoreAllocator*, GetAllocator);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, IO::IStream*, GetStream);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, SetStream, Args(IO::IStream* pStream), Args(pStream));

	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordRead*, CreateRecordRead, Args(IO::AccessFlags nDesiredAccess, DBPFItem* info, ResourceKey& key), Args(nDesiredAccess, info, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordRead*, CreateRecordReadCopy, Args(IO::AccessFlags nDesiredAccess, PFRecordRead* pOther, ResourceKey& key), Args(nDesiredAccess, pOther, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordWrite*, CreateRecordWriteData, Args(IO::AccessFlags nDesiredAccess, void* pData, size_t nSize, ResourceKey& key), Args(nDesiredAccess, pData, nSize, key));
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFRecordWrite*, CreateRecordWrite, Args(IO::AccessFlags nDesiredAccess, size_t nChunkOffset, size_t nSize, ResourceKey& key), Args(nDesiredAccess, nChunkOffset, nSize, key));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, ReadHeaders);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, ReadHeaderRecord);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, WriteEmptyHeaderRecord);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, WriteHeaderRecord);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, bool, VerifyHeaderRecordIntegrity, Args(char* header), Args(header));
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, ReadIndex);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, WriteIndex);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, VerifyIndexRecordIntegrity);
	auto_METHOD_VIRTUAL(DatabasePackedFile, DatabasePackedFile, PFIndexModifiable*, CreateIndex, Args(IO::AccessFlags nDesiredAccess), Args(nDesiredAccess));
	auto_METHOD_VIRTUAL_VOID(DatabasePackedFile, DatabasePackedFile, DestroyIndex, Args(IO::EAIOZoneObject* pObject), Args(pObject));
	auto_METHOD_VIRTUAL_VOID_(DatabasePackedFile, DatabasePackedFile, MakeIndexModifiable);
	auto_METHOD_VIRTUAL_(DatabasePackedFile, DatabasePackedFile, bool, InitializeHoleTable);

	auto_METHOD(DatabasePackedFile, int, ReadBytes, Args(void* pDst, size_t nSize), Args(pDst, nSize));
	auto_METHOD(DatabasePackedFile, bool, ReadData, Args(void* pDst, size_t nChunkOffset, size_t nSize), Args(pDst, nChunkOffset, nSize));

	//////////////////////////////

	////////////////////////
	//// PFRecordRead.h ////
	////////////////////////

	PFRecordRead::PFRecordRead(DBPFItem& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: PFRecordBase(PFRecordRead::kType, name, pParentDBPF, IO::AccessFlags::Read)
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
		: PFRecordBase(PFRecordRead::kType, name, pParentDBPF, IO::AccessFlags::Read)
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
		if (mFileAccess != IO::AccessFlags::None)
		{
			mpParentDBPF->CloseRecord(this);
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

	auto_METHOD_(PFRecordRead, const ResourceKey&, GetKey);
	auto_METHOD_VOID(PFRecordRead, SetKey, Args(const ResourceKey& name), Args(name));
	auto_METHOD_(PFRecordRead, IO::IStream*, GetStream);
	auto_METHOD_(PFRecordRead, Database*, GetDatabase);

	auto_METHOD_(PFRecordRead, bool, RecordOpen);
	auto_METHOD_(PFRecordRead, bool, RecordClose);
	auto_METHOD_(PFRecordRead, int, DoPostClose);


	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, uint32_t, GetType);
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, IO::AccessFlags, GetAccessFlags);
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, IO::FileError, GetState);
	// auto_METHOD_(		PFRecordRead, bool,	Close);  // Already overriden with IPFRecord

	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, IO::size_type, GetSize);
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, bool, SetSize, Args(IO::size_type size), Args(size));
	auto_METHOD_VIRTUAL_const(PFRecordRead, IStream, int, GetPosition, Args(IO::PositionType positionType), Args(positionType));
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, bool, SetPosition, Args(int distance, IO::PositionType positionType), Args(distance, positionType));
	auto_METHOD_VIRTUAL_const_(PFRecordRead, IStream, int, GetAvailable);

	auto_METHOD_VIRTUAL(PFRecordRead, IStream, int, Read, Args(void* pData, size_t nSize), Args(pData, nSize));
	auto_METHOD_VIRTUAL_(PFRecordRead, IStream, bool, Flush);
	auto_METHOD_VIRTUAL(PFRecordRead, IStream, int, Write, Args(const void* pData, size_t nSize), Args(pData, nSize));

	////////////////////////

	/////////////////////////
	//// PFRecordWrite.h ////
	/////////////////////////

	PFRecordWrite::PFRecordWrite(void* pData, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF)
		: PFRecordBase(kType, name, pParentDBPF, IO::AccessFlags::ReadWrite)
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
		: PFRecordBase(kType, name, pParentDBPF, IO::AccessFlags::ReadWrite)
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
		mpParentDBPF->CloseRecord(this);

		mpParentDBPF = nullptr;
		mFileAccess = IO::AccessFlags::None;
		field_274 = false;
		mnStreamRefCount = 0;

		if (field_48.GetAccessFlags() != IO::AccessFlags::None)
		{
			field_48.Close();

			char16_t fileName[IO::kMaxPathLength];
			field_48.GetPath((char16_t*)fileName, IO::kMaxPathLength);

			DeleteFileW((wchar_t*)fileName);
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


	auto_METHOD_(PFRecordWrite, const ResourceKey&, GetKey);
	auto_METHOD_VOID(PFRecordWrite, SetKey, Args(const ResourceKey& name), Args(name));
	auto_METHOD_(PFRecordWrite, IO::IStream*, GetStream);
	auto_METHOD_(PFRecordWrite, Database*, GetDatabase);

	auto_METHOD_(PFRecordWrite, bool, RecordOpen);
	auto_METHOD_(PFRecordWrite, bool, RecordClose);
	auto_METHOD_(PFRecordWrite, int, DoPostClose);


	auto_METHOD_const_(PFRecordWrite, uint32_t, GetType);
	auto_METHOD_const_(PFRecordWrite, IO::AccessFlags, GetAccessFlags);
	auto_METHOD_const_(PFRecordWrite, IO::FileError, GetState);
	// auto_METHOD_(		PFRecordWrite, bool,	Close);  // Already overriden with IPFRecord

	auto_METHOD_const_(PFRecordWrite, IO::size_type, GetSize);
	auto_METHOD(PFRecordWrite, bool, SetSize, Args(IO::size_type size), Args(size));
	auto_METHOD_const(PFRecordWrite, int, GetPosition, Args(IO::PositionType positionType), Args(positionType));
	auto_METHOD(PFRecordWrite, bool, SetPosition, Args(int distance, IO::PositionType positionType), Args(distance, positionType));
	auto_METHOD_const_(PFRecordWrite, int, GetAvailable);

	auto_METHOD(PFRecordWrite, int, Read, Args(void* pData, size_t nSize), Args(pData, nSize));
	auto_METHOD_(PFRecordWrite, bool, Flush);
	auto_METHOD(PFRecordWrite, int, Write, Args(const void* pData, size_t nSize), Args(pData, nSize));

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
	auto_METHOD(PFIndexModifiable, size_t, GetFiles, Args(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter), Args(dstVector, filter));
	auto_METHOD(PFIndexModifiable, size_t, GetAllFiles, Args(eastl::vector<ResourceKey>& dstVector), Args(dstVector));
	auto_METHOD(PFIndexModifiable, bool, func24h, Args(int arg_0, size_t fileDataBegin, size_t fileDataEnd), Args(arg_0, fileDataBegin, fileDataEnd));

	auto_METHOD(PFIndexModifiable, DBPFItem*, GetFileInfo, Args(const ResourceKey& fileName), Args(fileName));
	auto_METHOD(PFIndexModifiable, DBPFItem&, PutFileInfo, Args(const ResourceKey& fileName, DBPFItem& info), Args(fileName, info));
	auto_METHOD(PFIndexModifiable, bool, RemoveFile, Args(const ResourceKey& fileName, DBPFItem& dstInfo), Args(fileName, dstInfo));

	auto_METHOD(PFIndexModifiable, bool, Read, Args(void* pIndexData, size_t nIndexSize, size_t nIndexCount, bool arg_C), Args(pIndexData, nIndexSize, nIndexCount, arg_C));
	auto_METHOD(PFIndexModifiable, bool, Write, Args(void*& pDstIndexData, size_t& nDstIndexSize, size_t nIndexCount, bool arg_C), Args(pDstIndexData, nDstIndexSize, nIndexCount, arg_C));

	auto_METHOD_VOID_(PFIndexModifiable, SetIsSaved);
	auto_METHOD(PFIndexModifiable, bool, CheckFilesInRange, Args(size_t fileDataBegin, size_t fileDataEnd), Args(fileDataBegin, fileDataEnd));
	auto_METHOD(PFIndexModifiable, bool, CheckFilesInSizeRange, Args(size_t fileDataBegin, size_t size), Args(fileDataBegin, size));

	/////////////////////////////



	auto_STATIC_METHOD(Paths, const char16_t*, GetDirFromID, Args(PathID dirID), Args(dirID));
	auto_STATIC_METHOD(Paths, bool, GetDirectory, Args(PathID dirID, eastl::string16& dst), Args(dirID, dst));
	auto_STATIC_METHOD_VOID(Paths, RegisterDirectory, Args(PathID dirID, const char16_t* path), Args(dirID, path));

	auto_STATIC_METHOD(Paths, Database*, GetSaveArea,
		Args(SaveAreaID areaID),
		Args(areaID));

	auto_STATIC_METHOD_VOID(Paths, RegisterSaveArea, 
		Args(SaveAreaID areaID, Resource::Database* pDatabase, void* arg), 
		Args(areaID, pDatabase, arg));

	const char16_t* Paths::GetDataDir() {
		return GetDirFromID(PathID::Data);
	}
	const char16_t* Paths::GetAppDir() {
		return GetDirFromID(PathID::App);
	}
	const char16_t* Paths::GetDebugDir() {
		return GetDirFromID(PathID::Debug);
	}

	//////////////////////

	EAIOZoneObject_AMBIGOUS(DatabaseDirectoryFiles);

	//auto_METHOD_VIRTUAL_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Initialize);
	auto_METHOD_VIRTUAL_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Dispose);
	//auto_METHOD_VIRTUAL_const_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, uint32_t, GetDatabaseType);
	auto_METHOD_VIRTUAL_const_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, int, GetRefCount);
	auto_METHOD_VIRTUAL_VOID(DatabaseDirectoryFiles, DatabaseDirectoryFiles, Lock, Args(bool bLock), Args(bLock));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Open, Args(IO::AccessFlags nDesiredAccess, IO::CD nCreateDisposition, bool arg_8), Args(nDesiredAccess, nCreateDisposition, arg_8));
	auto_METHOD_VIRTUAL_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Close);
	//auto_METHOD_VIRTUAL_const_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, int, GetAccessFlags);
	auto_METHOD_VIRTUAL_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Flush);
	//auto_METHOD_VIRTUAL_const_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, char16_t*, GetLocation);
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, SetLocation, Args(const char16_t* path), Args(path));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, size_t, GetKeyList, Args(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter), Args(dstVector, filter));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, OpenRecord, Args(const ResourceKey& name, IRecord** pDst, IO::AccessFlags nDesiredAccess, IO::CD nCreateDisposition, bool arg_10, DBPFItem* pDstInfo), Args(name, pDst, nDesiredAccess, nCreateDisposition, arg_10, pDstInfo));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, int, GetOpenCount, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, CloseRecord, Args(IRecord* pRecord), Args(pRecord));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, DeleteRecord, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, Attach, Args(bool arg_0, IResourceManager* pResourceMan, bool arg_8), Args(arg_0, pResourceMan, arg_8));
	//auto_METHOD_VIRTUAL_const_(DatabaseDirectoryFiles, DatabaseDirectoryFiles, ICoreAllocator*, GetAllocator);

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, AddExtensionMapping,
		Args(const char16_t* extension, uint32_t typeID), Args(extension, typeID));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, int, UpdateRecordData,
		Args(const char16_t* arg0, eastl::vector<ResourceKey>& keys, int arg2), Args(arg0, keys, arg2));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, int, UpdateRecordData2,
		Args(eastl::vector<ResourceKey>& keys), Args(keys));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, uint32_t, GetTypeFromTypename,
		Args(const char16_t* typeName), Args(typeName));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, const char16_t*, GetTypenameFromType,
		Args(uint32_t typeID), Args(typeID));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, GetFileNameFromKey,
		Args(const ResourceKey& key, char16_t* dst), Args(key, dst));

	auto_METHOD_VIRTUAL(DatabaseDirectoryFiles, DatabaseDirectoryFiles, bool, GetKeyFromFileName,
		Args(const char16_t* fileName, ResourceKey& dst), Args(fileName, dst));


	bool DatabaseDirectoryFiles::Initialize()
	{
		if (!mIsInitialized)
		{
			mIsInitialized = true;
		}

		return true;
	}

	ICoreAllocator* DatabaseDirectoryFiles::GetAllocator() const {
		return mpAllocator;
	}

	uint32_t DatabaseDirectoryFiles::GetDatabaseType() const {
		return DATABASE_TYPE;
	}

	IO::AccessFlags DatabaseDirectoryFiles::GetAccessFlags() const {
		return mAccessFlags;
	}

	const char16_t* DatabaseDirectoryFiles::GetLocation() const {
		return mLocation.c_str();
	}

	void DatabaseDirectoryFiles::SetFileNameToKeyConverter(FileNameToKeyConverter_t callback)
	{
		mFileNameToKeyConverter = callback;
	}

	uint32_t DatabaseDirectoryFiles::GetDefaultGroupId() {
		return mDefaultGroupID;
	}
	void DatabaseDirectoryFiles::SetDefaultGroupId(uint32_t groupID) {
		mDefaultGroupID = groupID;
	}

	void* DatabaseDirectoryFiles::Cast(uint32_t type) const
	{
		if (type == DatabaseDirectoryFiles::TYPE)
		{
			return (DatabaseDirectoryFiles*)this;
		}
		else if (type == Object::TYPE)
		{
			return (Object*)this;
		}
		else
		{
			return nullptr;
		}
	}

	DatabaseDirectoryFiles::DatabaseDirectoryFiles(const char16_t* location, ICoreAllocator* allocator)
		: mIsInitialized(false)
		, mpAllocator(allocator == nullptr ? IO::GetAllocator() : allocator)
		, field_14()
		, field_15()
		, mAccessFlags()
		, mLocation()
		, mExtensionMapAllocator(mpAllocator, 0x20, 0x24)
		, mRecordListDataMapAllocator(mpAllocator, 0x80, 0x48)
		, mExtensionMap(CoreAllocatorAdapter<FixedPoolAllocator>(nullptr, &mExtensionMapAllocator))
		, mRecordListDataMap(CoreAllocatorAdapter<FixedPoolAllocator>(nullptr, &mRecordListDataMapAllocator))
		, mDefaultGroupID(0)
		, mpResourceManager()
		, mFileNameToKeyConverter()
		, mMutex(nullptr, true)
		, field_B8{}
	{
		mLocation = location;
		IO::EnsureTrailingPathSeparator(mLocation);
	}

	DatabaseDirectoryFiles::~DatabaseDirectoryFiles()
	{
		if (mAccessFlags != IO::AccessFlags::None) {
			Close();
		}
	}
}

auto_STATIC_METHOD(IO, bool, EnsureTrailingPathSeparator, Args(eastl::string16& path), Args(path));

auto_STATIC_METHOD_VOID(Resource, ReadExtensionMappingsFromPropFile,
	Args(uint32_t instanceID, DatabaseDirectoryFiles* database), Args(instanceID, database));




#endif
