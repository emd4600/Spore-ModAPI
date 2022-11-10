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
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetResource, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, int arg_8, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), Args(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetAsyncResource, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, AsyncResourcePtr* arg_8, void* arg_C, void* arg_10, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pAlternativeName), Args(name, ppDst, arg_8, arg_C, arg_10, pDBPF, pFactory, pAlternativeName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetCachedResource, Args(const ResourceKey& name, intrusive_ptr<ResourceObject>* pDst), Args(name, pDst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func18h, Args(int arg_0, int arg_4, int arg_8, int arg_C, int arg_10), Args(arg_0, arg_4, arg_8, arg_C, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, ReadResource, Args(const ResourceKey& name, ResourceObjectPtr* ppDst, int arg_8, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), Args(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, WriteResource, Args(const ResourceObject* pResource, int arg_4, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pNameKey), Args(pResource, arg_4, pDBPF, pFactory, pNameKey));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, SetTypeRemap, Args(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount), Args(nTypeID, pnTypes, nCount));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetTypeRemap, Args(vector<uint32_t>& dst, uint32_t nTypeID), Args(dst, nTypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, uint32_t, GetGeneralTypeID, Args(uint32_t nSubtypeID), Args(nSubtypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, DBPF*, GetRealFileKey, Args(const ResourceKey& nameKey, ResourceKey* pDst, DBPF* pDBPF), Args(nameKey, pDst, pDBPF));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, func34h, Args(vector<ResourceKey>& pDst, int arg_4), Args(pDst, arg_4));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetFileKeys, Args(vector<ResourceKey>& dst, IResourceFilter* request, vector<DBPF*>* pDstDBPFs), Args(dst, request, pDstDBPFs));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, int, func3Ch, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func40h, Args(int arg_0, int arg_4, int arg_8, int arg_c, int arg_10), Args(arg_0, arg_4, arg_8, arg_c, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetResourceFactory, Args(bool bRemove, IResourceFactory* pFactory, uint32_t arg_8), Args(bRemove, pFactory, arg_8));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, IResourceFactory*, GetResourceFactory, Args(uint32_t nTypeID, uint32_t nSubTypeID), Args(nTypeID, nSubTypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetResourceFactories, Args(list<IResourceFactory*>& dst, uint32_t nTypeID), Args(dst, nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddDBPF, Args(bool arg_0, DatabasePackedFile* pDBPF, int nPriority), Args(arg_0, pDBPF, nPriority));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, bool, GetPriority, Args(DatabasePackedFile* pDBPF, int* pDst), Args(pDBPF, pDst));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, DatabasePackedFile*, GetDBPF, Args(const ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetAllDBPFs, Args(DBPFList& dst, const ResourceKey* pFileKey), Args(dst, pFileKey));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, int, func60h, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func64h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, IResourceMap*, GetResourceCache, Args(ResourceKey& name), Args(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func6Ch, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, func70h, Args(IResourceMap* arg_0, CachedResourceObject* arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetResourceCaches, Args(list<IResourceMap*>& dst), Args(dst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddFileName, Args(const char16_t* pFileName), Args(pFileName));
	auto_METHOD_VIRTUAL_VOID_const(cResourceManager, cResourceManager, GetFileName, Args(const ResourceKey& resourceKey, string16& dst), Args(resourceKey, dst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetFileName, Args(const ResourceKey& resourceKey, const char16_t* pFileName), Args(resourceKey, pFileName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RemoveFileName, Args(const ResourceKey& resourceKey), Args(resourceKey));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, uint32_t, GetTypeID, Args(const char16_t* pExtension), Args(pExtension));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, char16_t*, GetExtension, Args(uint32_t nTypeID), Args(nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddExtensionMapping, Args(uint32_t nTypeID, const char16_t* pExtension), Args(nTypeID, pExtension));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RemoveExtensionMapping, Args(uint32_t nTypeID), Args(nTypeID));
#endif
}
