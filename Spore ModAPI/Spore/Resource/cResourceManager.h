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

#include <EASTL\vector.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\map.h>
#include <EASTL\hash_map.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>
#include <EASTL\string.h>

#include <Spore\ICoreAllocator.h>
#include <Spore\CoreAllocatorAdapter.h>

#include <Spore\Internal.h>
#include <Spore\ResourceKey.h>
#include <Spore\Mutex.h>

#include <Spore\IO\IStream.h>
#include <Spore\Resource\IResourceContainer.h>
#include <Spore\Resource\IResourceFactory.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Resource\IResourceMap.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\FixedPoolAllocator.h>

using namespace eastl;

namespace Resource
{

	class DatabasePackedFile;
	typedef DatabasePackedFile DBPF;

	///
	/// The implementation of IResourceManager; this should only be used for extending and detouring 
	///
	class cResourceManager : public IResourceManager
	{

	public:

		typedef list<DatabasePackedFile*, CoreAllocatorAdapter<ICoreAllocator>> DBPFList;


		virtual bool NeedsToRelease() override;
		virtual bool ReleaseResources() override;

		/* 0Ch */	virtual bool GetResource(
			const ResourceKey& name,
			ResourceObject** ppDst = nullptr, 
			int arg_8 = 0, 
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pCacheName = nullptr) override;

		/* 10h */	virtual bool func10h(
			const ResourceKey& name,
			ResourceObject** ppDst = nullptr, 
			void** arg_8 = nullptr, 
			void* arg_C = nullptr, 
			void* arg_10 = nullptr, 
			DBPF* pDBPF = nullptr, 
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pAlternativeName = nullptr) override;

		/* 14h */	virtual bool GetCachedResource(const ResourceKey& name, intrusive_ptr<ResourceObject>* pDst) override;
		/* 18h */	virtual bool func18h(int arg_0, int arg_4, int arg_8, int arg_C, int arg_10) override;
		/* 1Ch */	virtual bool ReadResource(
			const ResourceKey& name,
			ResourceObject** ppDst = nullptr,
			int arg_8 = 0,
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) override;

		/* 20h */	virtual bool WriteResource(
			const ResourceObject* pResource,
			int arg_4 = 0, 
			DBPF* pDBPF = nullptr, 
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pNameKey = nullptr) override;

		/* 24h */	virtual void SetTypeRemap(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount) override;
		/* 28h */	virtual size_t GetTypeRemap(vector<uint32_t>& dst, uint32_t nTypeID) const override;
		/* 2Ch */	virtual uint32_t GetGeneralTypeID(uint32_t nSubtypeID) const override;
		/* 30h */	virtual DBPF* GetRealFileKey(const ResourceKey& nameKey, ResourceKey* pDst=nullptr, DBPF* pDBPF=nullptr) const override;
		/* 34h */	virtual size_t func34h(vector<ResourceKey>& pDst, int arg_4) override;
		/* 38h */	virtual size_t GetFileKeys(vector<ResourceKey>& dst, IResourceFilter* request, vector<DBPF*>* pDstDBPFs=nullptr) const override;
		/* 3Ch */	virtual int func3Ch(int, int, int) override;
		/* 40h */	virtual bool func40h(int, int, int, int, int) override;
		/* 44h */	virtual bool SetResourceFactory(bool bRemove, IResourceFactory* pFactory, uint32_t arg_8) override;
		/* 48h */	virtual IResourceFactory* GetResourceFactory(uint32_t nTypeID, uint32_t nSubTypeID = ResourceKey::kWildcardID) const override;
		/* 4Ch */	virtual size_t GetResourceFactories(list<IResourceFactory*>& dst, uint32_t nTypeID = ResourceKey::kWildcardID) const override;
		/* 50h */	virtual bool AddDBPF(bool, DatabasePackedFile* pDBPF, int nPriority) override;
		/* 54h */	virtual bool GetPriority(DatabasePackedFile* pDBPF, int* pDst = nullptr) const override;
		/* 58h */	virtual DatabasePackedFile* GetDBPF(const ResourceKey& name) const override;
		/* 5Ch */	virtual size_t GetAllDBPFs(DBPFList& dst, const ResourceKey* pFileKey = nullptr) override;
		/* 60h */	virtual int func60h(int, int) override;
		/* 64h */	virtual bool func64h(int, int, int) override;
		/* 68h */	virtual IResourceMap* GetResourceCache(ResourceKey& name) const override;
		/* 6Ch */	virtual bool func6Ch(int, int) override;
		/* 70h */	virtual void func70h(IResourceMap*, SpecialResourceObject*) override;
		/* 74h */	virtual size_t GetResourceCaches(list<IResourceMap*>& dst) const override;
		/* 78h */	virtual bool AddFileName(const wchar_t* pFileName) override;
		/* 7Ch */	virtual void GetFileName(const ResourceKey& resourceKey, wstring& dst) const override;
		/* 80h */	virtual bool SetFileName(const ResourceKey& resourceKey, const wchar_t* pFileName) override;
		/* 84h */	virtual bool RemoveFileName(const ResourceKey& resourceKey) override;
		/* 88h */	virtual uint32_t GetTypeID(const wchar_t* pExtension) const override;
		/* 8Ch */	virtual wchar_t* GetExtension(uint32_t nTypeID) const override;
		/* 90h */	virtual bool AddExtensionMapping(uint32_t nTypeID, const wchar_t* pExtension) override;
		/* 94h */	virtual bool RemoveExtensionMapping(uint32_t nTypeID) override;


	protected:
		typedef hash_map<uint32_t, vector<pair<IResourceFactory::Pointer, uint32_t>>, ICoreAllocatorAdapter> FactoriesMap_t;
		typedef hash_map<uint32_t, vector<uint32_t>, ICoreAllocatorAdapter> TypesMap_t;
		typedef hash_map<uint32_t, uint32_t, ICoreAllocatorAdapter> SubtypesMap_t;
		typedef hash_map<uint32_t, wstring, ICoreAllocatorAdapter> ExtensionsMap_t;
		typedef hash_map<ResourceKey, wstring, FixedPoolAllocatorAdapter> FilenamesMap_t;
		typedef vector<pair<IResourceMap*, int>> CacheVector_t;

		/* 04h */	bool mbNeedsToRelease;
		/* 08h */	ICoreAllocator* mpAllocator;
		/* 0Ch */	map<int, int, less<ResourceKey>, ICoreAllocatorAdapter> field_0C;
		/* 2Ch */	void* field_2C;  // pointer to DBList
		/* 30h */	FactoriesMap_t		mResourceFactories;
		/* 54h */	TypesMap_t			mTypesRemapping;  // used to get multiple typeIDs from a single one
		/* 78h */	SubtypesMap_t		mSubtypesMap;  // subtype to typeID, inverse of mTypesRemapping
		/* 9Ch */	CacheVector_t		mCacheVector;
		/* B0h */	ExtensionsMap_t		mExtensionMappings;
		/* D4h */	FixedPoolAllocator	field_D4;
		/* F4h */	FilenamesMap_t		mFilenameMapping;
		/* 118h */	Mutex field_118;  // used for extension mapping
		/* 148h */	Mutex field_148;
	};


	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(cResourceManager) == 0x178, "sizeof(cResourceManager) != 178h");

	namespace Addresses(cResourceManager)
	{
		DeclareAddress(NeedsToRelease);
		DeclareAddress(ReleaseResources);
		DeclareAddress(GetResource);
		DeclareAddress(func10h);
		DeclareAddress(GetCachedResource);
		DeclareAddress(func18h);
		DeclareAddress(ReadResource);
		DeclareAddress(WriteResource);
		DeclareAddress(SetTypeRemap);
		DeclareAddress(GetTypeRemap);
		DeclareAddress(GetGeneralTypeID);
		DeclareAddress(GetRealFileKey);
		DeclareAddress(func34h);
		DeclareAddress(GetFileKeys);
		DeclareAddress(func3Ch);
		DeclareAddress(func40h);
		DeclareAddress(SetResourceFactory);
		DeclareAddress(GetResourceFactory);
		DeclareAddress(GetResourceFactories);
		DeclareAddress(AddDBPF);
		DeclareAddress(GetPriority);
		DeclareAddress(GetDBPF);
		DeclareAddress(GetAllDBPFs);
		DeclareAddress(func60h);
		DeclareAddress(func64h);
		DeclareAddress(GetResourceCache);
		DeclareAddress(func6Ch);
		DeclareAddress(func70h);
		DeclareAddress(GetResourceCaches);
		DeclareAddress(AddFileName);
		DeclareAddress(GetFileName);
		DeclareAddress(SetFileName);
		DeclareAddress(RemoveFileName);
		DeclareAddress(GetTypeID);
		DeclareAddress(GetExtension);
		DeclareAddress(AddExtensionMapping);
		DeclareAddress(RemoveExtensionMapping);

	}

}
