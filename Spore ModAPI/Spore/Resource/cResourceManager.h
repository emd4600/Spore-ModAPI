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
#include <Spore\Resource\IResourceFactory.h>
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\Resource\ICache.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\Database.h>
#include <Spore\FixedPoolAllocator.h>

namespace Resource
{
	///
	/// The implementation of IResourceManager; this should only be used for extending and detouring 
	///
	class cResourceManager : public IResourceManager
	{

	public:

		typedef eastl::list<Database*, CoreAllocatorAdapter<ICoreAllocator>> DatabaseList;


		virtual bool Initialize() override;
		virtual bool Dispose() override;

		/* 0Ch */	virtual bool GetResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr, 
			void* arg_8 = 0, 
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pCacheName = nullptr) override;

		/* 10h */	virtual bool GetResourceAsync(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			IAsyncRequestPtr* arg_8 = nullptr, 
			void* arg_C = nullptr, 
			void* arg_10 = nullptr, 
			Database* pDatabase = nullptr, 
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pAlternativeName = nullptr) override;

		/* 14h */	virtual bool GetLoadedResource(const ResourceKey& name, ResourceObjectPtr* pDst) override;
		/* 18h */	virtual bool ReloadResource(const ResourceKey& name,
			ResourceObject* pResource,
			void* pFactoryData = nullptr,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr) override;
		/* 1Ch */	virtual bool GetPrivateResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			void* arg_8 = 0,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) override;

		/* 20h */	virtual bool WriteResource(
			const ResourceObject* pResource,
			void* arg_4 = 0,
			Database* pDatabase = nullptr, 
			IResourceFactory* pFactory = nullptr, 
			const ResourceKey* pNameKey = nullptr) override;

		/* 24h */	virtual void SetTypeMapping(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount) override;
		/* 28h */	virtual size_t GetRecordTypesFromResourceType(eastl::vector<uint32_t>& dst, uint32_t nTypeID) override;
		/* 2Ch */	virtual uint32_t GetTypeMapping(uint32_t nSubtypeID) override;
		/* 30h */	virtual Database* FindRecord(const ResourceKey& nameKey, ResourceKey* pDst=nullptr, Database* pDatabase=nullptr) override;
		/* 34h */	virtual size_t GetResourceKeyList(eastl::vector<ResourceKey>& pDst, IKeyFilter* filter) override;
		/* 38h */	virtual size_t GetRecordKeyList(eastl::vector<ResourceKey>& dst, IKeyFilter* request, eastl::vector<Database*>* pDstDatabases=nullptr) override;
		/* 3Ch */	virtual size_t GetRecordKeyList2(eastl::vector<ResourceKey>& dst, IKeyFilter* filter, bool cached) override;
		/* 40h */	virtual bool RegisterChangeNotification(bool, ChangeNotificationCallback_t callback, void* data, IKeyFilter* filter, int) override;
		/* 44h */	virtual bool RegisterFactory(bool bRemove, IResourceFactory* pFactory, uint32_t arg_8) override;
		/* 48h */	virtual IResourceFactory* FindFactory(uint32_t nTypeID, uint32_t nSubTypeID = ResourceKey::kWildcardID) override;
		/* 4Ch */	virtual size_t GetFactoryList(eastl::list<IResourceFactory*>& dst, uint32_t nTypeID = ResourceKey::kWildcardID) override;
		/* 50h */	virtual bool RegisterDatabase(bool, Database* pDatabase, int nPriority) override;
		/* 54h */	virtual bool IsDatabaseRegistered(Database* pDatabase, int* pDst = nullptr) override;
		/* 58h */	virtual Database* FindDatabase(const ResourceKey& name) override;
		/* 5Ch */	virtual size_t GetDatabaseList(DatabaseList& dst, const ResourceKey* pFileKey = nullptr) override;
		/* 60h */	virtual void DoDatabaseChanged(Database* pDatabase, eastl::vector<ResourceKey>& keys) override;
		/* 64h */	virtual bool RegisterCache(bool add, ICache* pCache, int) override;
		/* 68h */	virtual ICache* FindCache(const ResourceKey& name) override;
		/* 6Ch */	virtual bool CacheResource(ResourceObject* pResource, bool) override;
		/* 70h */	virtual void FlushCache(ICache*, IKeyFilter*) override;
		/* 74h */	virtual size_t GetCacheList(eastl::list<ICache*>& dst) override;
		/* 78h */	virtual ResourceKey GetKeyFromName(const char16_t* pFileName, uint32_t defaultTypeID = 0, uint32_t defaultGroupID = 0) override;
		/* 7Ch */	virtual void GetNameFromKey(const ResourceKey& resourceKey, eastl::string16& dst) override;
		/* 80h */	virtual bool SetKeyName(const ResourceKey& resourceKey, const char16_t* pFileName) override;
		/* 84h */	virtual bool ForgetKeyName(const ResourceKey& resourceKey) override;
		/* 88h */	virtual uint32_t GetTypeFromTypename(const char16_t* pExtension) override;
		/* 8Ch */	virtual const char16_t* GetTypenameFromType(uint32_t nTypeID) override;
		/* 90h */	virtual bool SetTypename(uint32_t nTypeID, const char16_t* pExtension) override;
		/* 94h */	virtual bool ResetTypename(uint32_t nTypeID) override;


	protected:
		typedef eastl::hash_map<uint32_t, eastl::vector<eastl::pair<IResourceFactoryPtr, uint32_t>>, ICoreAllocatorAdapter> FactoriesMap_t;
		typedef eastl::hash_map<uint32_t, eastl::vector<uint32_t>, ICoreAllocatorAdapter> ResourceTypeToRecordTypeMap_t;
		typedef eastl::hash_map<uint32_t, uint32_t, ICoreAllocatorAdapter> RecordTypeToResourceTypeMap_t;
		typedef eastl::hash_map<uint32_t, eastl::string16, ICoreAllocatorAdapter> ExtensionsMap_t;
		typedef eastl::hash_map<ResourceKey, eastl::string16, FixedPoolAllocatorAdapter> FilenamesMap_t;
		typedef eastl::vector<eastl::pair<ICache*, int>> CacheVector_t;

		/* 04h */	bool mbNeedsToRelease;
		/* 08h */	ICoreAllocator* mpAllocator;
		/* 0Ch */	eastl::map<int, int, eastl::less<ResourceKey>, ICoreAllocatorAdapter> mChangeNotifications;
		/* 2Ch */	void* field_2C;  // pointer to DBList
		/* 30h */	FactoriesMap_t		mResourceFactories;
		/* 54h */	ResourceTypeToRecordTypeMap_t mResourceTypeToRecordType;  // used to get multiple typeIDs from a single one
		/* 78h */	RecordTypeToResourceTypeMap_t mRecordTypeToResourceType;  // subtype to typeID, inverse of mTypesRemapping
		/* 9Ch */	CacheVector_t		mCacheVector;
		/* B0h */	ExtensionsMap_t		mExtensionMappings;
		/* D4h */	FixedPoolAllocator	field_D4;
		/* F4h */	FilenamesMap_t		mFilenameMapping;
		/* 118h */	Mutex field_118;  // used for extension mapping
		/* 148h */	Mutex field_148;
	};
	ASSERT_SIZE(cResourceManager, 0x178);

	namespace Addresses(cResourceManager)
	{
		DeclareAddress(NeedsToRelease);
		DeclareAddress(ReleaseResources);
		DeclareAddress(GetResource);
		DeclareAddress(GetAsyncResource);
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
		DeclareAddress(AddDatabase);
		DeclareAddress(GetPriority);
		DeclareAddress(GetDatabase);
		DeclareAddress(GetAllDatabases);
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

		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		//DeclareAddress(GetResource);
		DeclareAddress(GetResourceAsync);
		DeclareAddress(GetLoadedResource);
		DeclareAddress(ReloadResource);
		DeclareAddress(GetPrivateResource);
		//DeclareAddress(WriteResource);
		DeclareAddress(SetTypeMapping);
		DeclareAddress(GetRecordTypesFromResourceType);
		DeclareAddress(GetTypeMapping);
		DeclareAddress(FindRecord);
		DeclareAddress(GetResourceKeyList);
		DeclareAddress(GetRecordKeyList);
		DeclareAddress(GetRecordKeyList2);
		DeclareAddress(RegisterChangeNotification);
		DeclareAddress(RegisterFactory);
		DeclareAddress(FindFactory);
		DeclareAddress(GetFactoryList);
		DeclareAddress(RegisterDatabase);
		DeclareAddress(IsDatabaseRegistered);
		DeclareAddress(FindDatabase);
		DeclareAddress(GetDatabaseList);
		DeclareAddress(DoDatabaseChanged);
		DeclareAddress(RegisterCache);
		DeclareAddress(FindCache);
		DeclareAddress(CacheResource);
		DeclareAddress(FlushCache);
		DeclareAddress(GetCacheList);
		DeclareAddress(GetKeyFromName);
		DeclareAddress(GetNameFromKey);
		DeclareAddress(SetKeyName);
		DeclareAddress(ForgetKeyName);
		DeclareAddress(GetTypeFromTypename);
		DeclareAddress(GetTypenameFromType);
		DeclareAddress(SetTypename);
		DeclareAddress(ResetTypename);
	}

}
