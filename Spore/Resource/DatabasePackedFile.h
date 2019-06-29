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

#include <Spore\Object.h>
#include <Spore\Mutex.h>
#include <Spore\ICoreAllocator.h>
#include <Spore\Resource\IResourceContainer.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\IO\FileStream.h>
#include <Spore\IO\EAIOZoneObject.h>
#include <Spore\Resource\PFIndexModifiable.h>

#include <EASTL\internal\thread_support.h>
#include <EASTL\string.h>
#include <EASTL\map.h>

using namespace eastl;

namespace Resource
{
	class cResourceManager;
	class IPFRecord;
	class PFRecordRead;
	class PFRecordWrite;

	///
	/// A DatabasePackedFile is a type of file used in Spore to store and index multiple files inside a single container 
	/// (usually in the .package extension).
	/// This class contains all the necessary methods for accessing files and loading/saving DBPF files.
	/// 
	class DatabasePackedFile : public IResourceContainer, public Object
	{

	public:
		friend class PFRecordRead;
		friend class PFRecordWrite;

		static const uint32_t kDefaultType = 0x2A43BD44;  // returned by GetType

		static const uint32_t TYPE = 0x226A25B;

		EAIOZoneObject_AMBIGOUS_DECLARATION;

		DatabasePackedFile(const wchar_t* pPath, ICoreAllocator* pAllocator);
		virtual ~DatabasePackedFile();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual bool NeedsToRelease();  // sets to true if not already
		virtual bool ReleaseResources();  // release resources or something like that?

		/* 0Ch */	virtual uint32_t GetType() const;
		/* 10h */	virtual int GetReferenceCount() const;
		/* 14h */	virtual int UseIndexMutex(bool bLock);
		/* 18h */	virtual bool Load(int nDesiredAccess = IO::kAccessFlagRead, int nCreateDisposition = IO::kCDDefault, bool arg_8 = false);
		/* 1Ch */	virtual bool Save();
		/* 20h */	virtual int GetAccessFlags() const;
		/* 24h */	virtual bool Write();
		/* 28h */	virtual wchar_t* GetPath() const;
		/* 2Ch */	virtual bool SetPath(const wchar_t* path);
		/* 30h */	virtual size_t GetFiles(PFIndexModifiable::KeysVector& dstVector, IResourceFilter* filter=nullptr);
		/* 34h */	virtual bool GetFile(
			const ResourceKey& name,
			IPFRecord** ppDst,
			int nDesiredAccess = IO::kAccessFlagRead,
			int nCreateDisposition = IO::kCDDefault,
			bool arg_10 = true,
			DBPFItem* pDstInfo = nullptr);
		/* 38h */	virtual int func38h(int);
		/* 3Ch */	virtual bool func3Ch(IPFRecord* pRecord);
		/* 40h */	virtual bool RemoveFile(ResourceKey& name);  // not sure
		/* 44h */	virtual bool SetResourceManager(bool, cResourceManager* pResourceMan, bool);
		/* 48h */	virtual ICoreAllocator* GetAllocator() const;
		/* 4Ch */	virtual IO::IStream* GetStream();
		/* 50h */	virtual bool SetStream(IO::IStream* pStream);

	protected:
		/* 54h */	virtual PFRecordRead* CreatePFRecordRead(int nDesiredAccess, DBPFItem* info, ResourceKey& key);
		/* 58h */	virtual PFRecordRead* CreatePFRecordReadCopy(int nDesiredAccess, PFRecordRead* pOther, ResourceKey& key);
		/* 5Ch */	virtual PFRecordWrite* CreatePFRecordWriteData(int nDesiredAccess, void* pData, size_t nSize, ResourceKey& key);
		/* 60h */	virtual PFRecordWrite* CreatePFRecordWrite(int nDesiredAccess, size_t nChunkOffset, size_t nSize, ResourceKey& key);
		/* 64h */	virtual bool Read();
		/* 68h */	virtual bool ReadHeader();
		/* 6Ch */	virtual bool Reset();
		/* 70h */	virtual bool IsReadyForWrite();
		/* 74h */	virtual bool IsValidHeader(char* header);
		/* 78h */	virtual bool ReadIndex();
		/* 7Ch */	virtual bool WriteIndex();
		///
		/// Tells whether the file stream has enough space to fit the data of the index files.
		///
		/* 80h */	virtual bool StreamCanContainFileData();
		/* 84h */	virtual PFIndexModifiable* CreatePFIndexModifiable(int nDesiredAccess = IO::kAccessFlagReadWrite);
		/* 88h */	virtual void ReleaseObject(IO::EAIOZoneObject* pObject);

		///
		/// Creates a new index that has the same information as the current one, which will be deleted.
		///
		/* 8Ch */	virtual void RenovateIndex();
		/* 90h */	virtual bool func90h();

	protected:
		int ReadBytes(void* pDst, size_t nSize);
		bool ReadData(void* pDst, size_t nChunkOffset, size_t nSize);

	protected:

		struct Unknown
		{
			Unknown();

			int field_0;  // -1
			map<size_t, int> field_4;  // maps chunkOffset to something
		};

		/* 08h */	int mnRefCount;
		/* 0Ch */	bool mbNeedsToRelease;
		/* 10h */	ICoreAllocator* mpAllocator;
		/* 14h */	int mnFileAccess;
		/* 18h */	int field_18;
		/* 1Ch */	bool field_1C;
		/* 1Dh */	bool field_1D;  // true

		/* 20h */	wstring mFilePath;
		/* 30h */	IO::FileStream mFileStream;
		/* 25Ch */	size_t mFileOffset;
		/* 260h */	intrusive_ptr<IO::IStream> mpCurrentStream;
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
		/* 2E8h */	map<ResourceKey, IPFRecord*, less<ResourceKey>, ICoreAllocatorAdapter> field_2E8;
		// /* 304h */	int field_304;
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

		/* 33Ch */	Unknown field_33C;
		/* 35Ch */	Unknown field_35C;

		/* 37Ch */	bool field_37C;
		/* 37Dh */	bool field_37D;
		/* 380h */	cResourceManager* mpResourceMan;
		/* 384h */	int field_384;  // not initialized

	};

	/// A short name for DatabasePackedFile.
	typedef DatabasePackedFile DBPF;

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(DatabasePackedFile) == 0x388, "sizeof(DatabasePackedFile) != 388h");


	namespace InternalAddressList(DatabasePackedFile)
	{
		DefineAddress(GetType, GetAddress(0x8D9B60, 0x8D9790, 0x8D97A0));
		DefineAddress(GetReferenceCount, GetAddress(0x69D630, 0x69D3F0, 0x69D3F0));
		DefineAddress(UseIndexMutex, GetAddress(0x8D88C0, 0x8D84E0, 0x8D84F0));
		DefineAddress(Load, GetAddress(0x8D90A0, 0x8D8C90, 0x8D8CA0));
		DefineAddress(Save, GetAddress(0x8D9FF0, 0x8D9CC0, 0x8D9CD0));
		DefineAddress(GetAccessFlags, GetAddress(0x8D88F0, 0xFF02D0, 0xFF02D0));
		DefineAddress(Write, GetAddress(0x8DB150, 0x8DAEB0, 0x8DAEC0));
		DefineAddress(GetPath, GetAddress(0xAE92B0, 0xA426C0, 0xA42700));
		DefineAddress(SetPath, GetAddress(0x8DA000, 0x8D9CD0, 0x8D9CE0));
		DefineAddress(GetFiles, GetAddress(0x8D8DF0, 0x8D8A20, 0x8D8A30));
		DefineAddress(GetFile, GetAddress(0x8DA980, 0x8DA6E0, 0x8DA6F0));
		DefineAddress(func38h, GetAddress(0x8D9C40, 0x8D9870, 0x8D9880));
		DefineAddress(func3Ch, GetAddress(0x8DA050, 0x8D9D20, 0x8D9D30));
		DefineAddress(RemoveFile, GetAddress(0x8D9290, 0x8D8E80, 0x8D8E90));
		DefineAddress(SetResourceManager, GetAddress(0x8D8C80, 0x8D88B0, 0x8D88C0));
		DefineAddress(GetAllocator, GetAddress(0x6BD860, 0x7F5550, 0x7F55C0));
		DefineAddress(GetStream, GetAddress(0x8D8D90, 0x8D89C0, 0x8D89D0));
		DefineAddress(SetStream, GetAddress(0x8D8DA0, 0x8D89D0, 0x8D89E0));

		DefineAddress(CreatePFRecordRead, GetAddress(0x8D89E0, 0x8D85F0, 0x8D8600));
		DefineAddress(CreatePFRecordReadCopy, GetAddress(0x8D89A0, 0x8D85B0, 0x8D85C0));
		DefineAddress(CreatePFRecordWriteData, GetAddress(0x8D8950, 0x8D8560, 0x8D8570));
		DefineAddress(CreatePFRecordWrite, GetAddress(0x8D8900, 0x8D8510, 0x8D8520));
		DefineAddress(Read, GetAddress(0x8D8A20, 0x8D8630, 0x8D8640));
		DefineAddress(ReadHeader, GetAddress(0x8D9370, 0x8D8F60, 0x8D8F70));
		DefineAddress(Reset, GetAddress(0x8D9540, 0x8D9130, 0x8D9140));
		DefineAddress(IsReadyForWrite, GetAddress(0x8D9600, 0x8D91F0, 0x8D9200));
		DefineAddress(IsValidHeader, GetAddress(0x8D94B0, 0x8D90A0, 0x8D90B0));
		DefineAddress(ReadIndex, GetAddress(0x8DAD00, 0x8DAA60, 0x8DAA70));
		DefineAddress(WriteIndex, GetAddress(0x8D9CD0, 0x8D9900, 0x8D9910));
		DefineAddress(StreamCanContainFileData, GetAddress(0x8D9720, 0x8D9310, 0x8D9320));
		DefineAddress(CreatePFIndexModifiable, GetAddress(0x8D8A60, 0x8D8670, 0x8D8680));
		DefineAddress(ReleaseObject, GetAddress(0x6BC5B0, 0x8D86A0, 0x8D86B0));
		DefineAddress(RenovateIndex, GetAddress(0x8D8A90, 0x8D86C0, 0x8D86D0));
		DefineAddress(func90h, GetAddress(0x8D9E50, 0x8D9A80, 0x8D9A90));


		DefineAddress(ReadBytes, GetAddress(0x8D8FB0, 0x8D8BE0, 0x8D8BF0));
		DefineAddress(ReadData, GetAddress(0x8D9770, 0x6BCA80, 0x6BCA80));

	}

}
