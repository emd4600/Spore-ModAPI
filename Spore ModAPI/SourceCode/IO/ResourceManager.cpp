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

#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\cResourceManager.h>

namespace Resource
{

	auto_STATIC_METHOD_(IResourceManager, IResourceManager*, Get);

#ifndef MODAPI_DLL_EXPORT
	auto_METHOD_VIRTUAL_(cResourceManager, cResourceManager, bool, Initialize);
	auto_METHOD_VIRTUAL_(cResourceManager, cResourceManager, bool, Dispose);
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetResource, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, void* arg_8, Database* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), Args(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetResourceAsync, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, IAsyncRequestPtr* arg_8, void* arg_C, void* arg_10, Database* pDBPF, IResourceFactory* pFactory, const ResourceKey* pAlternativeName), Args(name, ppDst, arg_8, arg_C, arg_10, pDBPF, pFactory, pAlternativeName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetLoadedResource, Args(const ResourceKey& name, ResourceObjectPtr* pDst), Args(name, pDst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, ReloadResource, Args(const ResourceKey& arg_0, ResourceObject* arg_4, void* arg_8, Database* arg_C, IResourceFactory* arg_10), Args(arg_0, arg_4, arg_8, arg_C, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetPrivateResource, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, void* arg_8, Database* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), Args(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, WriteResource, Args(const ResourceObject* pResource, void* arg_4, Database* pDBPF, IResourceFactory* pFactory, const ResourceKey* pNameKey), Args(pResource, arg_4, pDBPF, pFactory, pNameKey));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, SetTypeMapping, Args(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount), Args(nTypeID, pnTypes, nCount));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetRecordTypesFromResourceType, Args(eastl::vector<uint32_t>& dst, uint32_t nTypeID), Args(dst, nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, uint32_t, GetTypeMapping, Args(uint32_t nSubtypeID), Args(nSubtypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, Database*, FindRecord, Args(const ResourceKey& nameKey, ResourceKey* pDst, Database* pDBPF), Args(nameKey, pDst, pDBPF));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetResourceKeyList, Args(eastl::vector<ResourceKey>& pDst, IKeyFilter* arg_4), Args(pDst, arg_4));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetRecordKeyList, Args(eastl::vector<ResourceKey>& dst, IKeyFilter* request, eastl::vector<Database*>* pDstDBPFs), Args(dst, request, pDstDBPFs));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetRecordKeyList2, Args(eastl::vector<ResourceKey>& arg_0, IKeyFilter* arg_4, bool arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RegisterChangeNotification, Args(bool arg_0, ChangeNotificationCallback_t arg_4, void* arg_8, IKeyFilter* arg_c, int arg_10), Args(arg_0, arg_4, arg_8, arg_c, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RegisterFactory, Args(bool bRemove, IResourceFactory* pFactory, uint32_t arg_8), Args(bRemove, pFactory, arg_8));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, IResourceFactory*, FindFactory, Args(uint32_t nTypeID, uint32_t nSubTypeID), Args(nTypeID, nSubTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetFactoryList, Args(eastl::list<IResourceFactory*>& dst, uint32_t nTypeID), Args(dst, nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RegisterDatabase, Args(bool arg_0, Database* pDBPF, int nPriority), Args(arg_0, pDBPF, nPriority));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, IsDatabaseRegistered, Args(Database* pDBPF, int* pDst), Args(pDBPF, pDst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, Database*, FindDatabase, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetDatabaseList, Args(DatabaseList& dst, const ResourceKey* pFileKey), Args(dst, pFileKey));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, DoDatabaseChanged, Args(Database* pDatabase, eastl::vector<ResourceKey>& keys), Args(pDatabase, keys));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RegisterCache, Args(bool arg_0, ICache* arg_4, int arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, ICache*, FindCache, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, CacheResource, Args(ResourceObject* pResource, bool arg_4), Args(pResource, arg_4));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, FlushCache, Args(ICache* arg_0, IKeyFilter* arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetCacheList, Args(eastl::list<ICache*>& dst), Args(dst));
	//auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, ResourceKey, GetKeyFromName, Args(const char16_t* pFileName), Args(pFileName));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, GetNameFromKey, Args(const ResourceKey& resourceKey, eastl::string16& dst), Args(resourceKey, dst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetKeyName, Args(const ResourceKey& resourceKey, const char16_t* pFileName), Args(resourceKey, pFileName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, ForgetKeyName, Args(const ResourceKey& resourceKey), Args(resourceKey));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, uint32_t, GetTypeFromTypename, Args(const char16_t* pExtension), Args(pExtension));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, const char16_t*, GetTypenameFromType, Args(uint32_t nTypeID), Args(nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetTypename, Args(uint32_t nTypeID, const char16_t* pExtension), Args(nTypeID, pExtension));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, ResetTypename, Args(uint32_t nTypeID), Args(nTypeID));
#endif
}
