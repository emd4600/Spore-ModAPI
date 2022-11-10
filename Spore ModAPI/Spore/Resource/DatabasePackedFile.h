/****************************************************************************
* Copyright (C) 2019 Eric Mor
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

#pragma once

#include <Spore\IO\FileStream.h>
#include <Spore\Object.h>
#include <Spore\Mutex.h>
#include <Spore\ICoreAllocator.h>
#include <Spore\Resource\Database.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\IO\EAIOZoneObject.h>
#include <Spore\Resource\PFIndexModifiable.h>

#include <EASTL\internal\thread_support.h>
#include <EASTL\string.h>
#include <EASTL\map.h>
#include <EASTL\set.h>

#define DatabasePackedFilePtr eastl::intrusive_ptr<Resource::DatabasePackedFile>

namespace Resource
{
	class cResourceManager;
	class PFRecordBase;
	class PFRecordRead;
	class PFRecordWrite;

	struct PFHoleTable
	{
		struct HoleRecord
		{
			int field_0;  // chunkOffset
			int field_4;
		};

		PFHoleTable();

		int field_0;  // -1
		eastl::set<HoleRecord> mRecords;
	};

	///
	/// A DatabasePackedFile is a type of file used in Spore to store and index multiple files inside a single container 
	/// (usually in the .package extension).
	/// This class contains all the necessary methods for accessing files and loading/saving DBPF files.
	/// 
	class DatabasePackedFile 
		: public Database
	{

	public:
		friend class PFRecordRead;
		friend class PFRecordWrite;

		static const uint32_t DATABASE_TYPE = 0x2A43BD44;  // returned by GetDatabaseType

		static const uint32_t TYPE = 0x226A25B;

		EAIOZoneObject_AMBIGOUS_DECLARATION;

		DatabasePackedFile(const char16_t* location, ICoreAllocator* allocator = nullptr);
		virtual ~DatabasePackedFile();

		virtual void* Cast(uint32_t type) const override;

		/* 04h */	virtual bool Initialize() override;
		/* 08h */	virtual bool Dispose() override;
		/* 0Ch */	virtual uint32_t GetDatabaseType() const override;
		/* 10h */	virtual int GetRefCount() const override;
		/* 14h */	virtual void Lock(bool lock) override;
		/* 18h */	virtual bool Open(IO::AccessFlags desiredAccess = IO::AccessFlags::Read, IO::CD createDisposition = IO::CD::Default, bool arg_8 = false) override;
		/* 1Ch */	virtual bool Close() override;
		/* 20h */	virtual IO::AccessFlags GetAccessFlags() const override;
		/* 24h */	virtual bool Flush() override;
		/* 28h */	virtual const char16_t* GetLocation() const override;
		/* 2Ch */	virtual bool SetLocation(const char16_t* path) override;
		/* 30h */	virtual size_t GetKeyList(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter=nullptr) override;
		/* 34h */	virtual bool OpenRecord(
			const ResourceKey& name,
			IRecord** ppDst,
			IO::AccessFlags desiredAccess = IO::AccessFlags::Read, 
			IO::CD createDisposition = IO::CD::Default,
			bool arg_10 = true,
			DBPFItem* pDstInfo = nullptr) override;
		/* 38h */	virtual int GetOpenCount(const ResourceKey& key) override;
		/* 3Ch */	virtual bool CloseRecord(IRecord* pRecord) override;
		/* 40h */	virtual bool DeleteRecord(const ResourceKey& name) override;
		/* 44h */	virtual bool Attach(bool, IResourceManager* pResourceMan, bool) override;
		/* 48h */	virtual ICoreAllocator* GetAllocator() const override;

		/* 4Ch */	virtual IO::IStream* GetStream();
		/* 50h */	virtual bool SetStream(IO::IStream* pStream);

	public:
		/* 54h */	virtual PFRecordRead* CreateRecordRead(IO::AccessFlags desiredAccess, DBPFItem* info, ResourceKey& key);
		/* 58h */	virtual PFRecordRead* CreateRecordReadCopy(IO::AccessFlags desiredAccess, PFRecordRead* pOther, ResourceKey& key);
		/* 5Ch */	virtual PFRecordWrite* CreateRecordWriteData(IO::AccessFlags desiredAccess, void* pData, size_t nSize, ResourceKey& key);
		/* 60h */	virtual PFRecordWrite* CreateRecordWrite(IO::AccessFlags desiredAccess, size_t nChunkOffset, size_t nSize, ResourceKey& key);
		/* 64h */	virtual bool ReadHeaders();
		/* 68h */	virtual bool ReadHeaderRecord();
		/* 6Ch */	virtual bool WriteEmptyHeaderRecord();
		/* 70h */	virtual bool WriteHeaderRecord();
		/* 74h */	virtual bool VerifyHeaderRecordIntegrity(char* header);
		/* 78h */	virtual bool ReadIndex();
		/* 7Ch */	virtual bool WriteIndex();
		/* 80h */	virtual bool VerifyIndexRecordIntegrity();
		/* 84h */	virtual PFIndexModifiable* CreateIndex(IO::AccessFlags desiredAccess = IO::AccessFlags::ReadWrite);
		/* 88h */	virtual void DestroyIndex(IO::EAIOZoneObject* pObject);
		/* 8Ch */	virtual void MakeIndexModifiable();
		/* 90h */	virtual bool InitializeHoleTable();

	public:
		int ReadBytes(void* pDst, size_t nSize);
		bool ReadData(void* pDst, size_t nChunkOffset, size_t nSize);

	public:
		/* 0Ch */	bool mIsInitialized;
		/* 10h */	ICoreAllocator* mpAllocator;
		/* 14h */	IO::AccessFlags mAccessFlags;
		/* 18h */	int field_18;
		/* 1Ch */	bool field_1C;
		/* 1Dh */	bool field_1D;  // true
		/* 20h */	eastl::string16 mFilePath;
		/* 30h */	IO::FileStream mFileStream;
		/* 25Ch */	size_t mFileOffset;
		/* 260h */	eastl::intrusive_ptr<IO::IStream> mpCurrentStream;
		// Set to nullptr if not using an internal buffer;
		/* 264h */	char* mpDataBuffer;
		/* 268h */	size_t mpBufferSize;
		/* 26Ch */	size_t mnBufferOffset;
		/* 270h */	Mutex mIndexMutex;
		/* 2A0h */	Mutex mReadWriteMutex;  // mutex used for reading and writing
		/* 2D0h */	PFIndexModifiable* mpIndex;
		/* 2D4h */	bool field_2D4;
		/* 2D8h */	int field_2D8;
		/* 2DCh */	int field_2DC;
		/* 2E0h */	bool field_2E0;
		/* 2E4h */	float field_2E4;
		/* 2E8h */	eastl::map<ResourceKey, IPFRecord*, eastl::less<ResourceKey>, ICoreAllocatorAdapter> field_2E8;
		/* 308h */	int field_308;
		/* 30Ch */	int field_30C;
		/* 310h */	int field_310;
		/* 314h */	int field_314;
		/* 318h */	int field_318;
		/* 31Ch */	int field_31C;
		/* 320h */	int field_320;
		/* 324h */	size_t mnIndexOffset;  // Absolute offset in package to the index header.
		/* 328h */	size_t mnIndexCount;  // Number of index entries in the package.
		/* 32Ch */	size_t mnIndexSize;  // The total size in bytes of index entries.
		/* 330h */	bool field_330;
		/* 334h */	int field_334;  // 0x13
		/* 338h */	float field_338;
		/* 33Ch */	PFHoleTable field_33C;
		/* 35Ch */	PFHoleTable field_35C;
		/* 37Ch */	bool field_37C;
		/* 37Dh */	bool field_37D;
		/* 380h */	cResourceManager* mpResourceMan;
		/* 384h */	int field_384;  // not initialized
	};
	ASSERT_SIZE(DatabasePackedFile, 0x388);

	/// A short name for DatabasePackedFile.
	typedef DatabasePackedFile DBPF;

	namespace Addresses(DatabasePackedFile)
	{
		DeclareAddress(GetType);
		DeclareAddress(GetReferenceCount);
		DeclareAddress(UseIndexMutex);
		DeclareAddress(Load);
		DeclareAddress(Save);
		DeclareAddress(GetAccessFlags);
		DeclareAddress(Write);
		DeclareAddress(GetPath);
		DeclareAddress(SetPath);
		DeclareAddress(GetFiles);
		DeclareAddress(GetFile);
		DeclareAddress(func38h);
		DeclareAddress(func3Ch);
		DeclareAddress(RemoveFile);
		DeclareAddress(SetResourceManager);
		DeclareAddress(GetAllocator);
		DeclareAddress(GetStream);
		DeclareAddress(SetStream);
		DeclareAddress(CreatePFRecordRead);
		DeclareAddress(CreatePFRecordReadCopy);
		DeclareAddress(CreatePFRecordWriteData);
		DeclareAddress(CreatePFRecordWrite);
		DeclareAddress(Read);
		DeclareAddress(ReadHeader);
		DeclareAddress(Reset);
		DeclareAddress(IsReadyForWrite);
		DeclareAddress(IsValidHeader);
		DeclareAddress(ReadIndex);
		DeclareAddress(WriteIndex);
		DeclareAddress(StreamCanContainFileData);
		DeclareAddress(CreatePFIndexModifiable);
		DeclareAddress(ReleaseObject);
		DeclareAddress(RenovateIndex);
		DeclareAddress(func90h);
		DeclareAddress(ReadBytes);
		DeclareAddress(ReadData);


		DeclareAddress(GetDatabaseType);
		DeclareAddress(GetRefCount);
		DeclareAddress(Lock);
		DeclareAddress(Open);
		DeclareAddress(Close);
		DeclareAddress(Flush);
		DeclareAddress(GetLocation);
		DeclareAddress(SetLocation);
		DeclareAddress(GetKeyList);
		DeclareAddress(OpenRecord);
		DeclareAddress(GetOpenCount);
		DeclareAddress(CloseRecord);
		DeclareAddress(DeleteRecord);
		DeclareAddress(Attach);
		DeclareAddress(CreateRecordRead);
		DeclareAddress(CreateRecordReadCopy);
		DeclareAddress(CreateRecordWriteData);
		DeclareAddress(CreateRecordWrite);
		DeclareAddress(ReadHeaders);
		DeclareAddress(ReadHeaderRecord);
		DeclareAddress(WriteEmptyHeaderRecord);
		DeclareAddress(WriteHeaderRecord);
		DeclareAddress(VerifyHeaderRecordIntegrity);
		DeclareAddress(ReadIndexRecord);
		DeclareAddress(WriteIndexRecord);
		DeclareAddress(VerifyIndexRecordIntegrity);
		DeclareAddress(CreateIndex);
		DeclareAddress(DestroyIndex);
		DeclareAddress(MakeIndexModifiable);
		DeclareAddress(InitializeHoleTable);
	}

}
