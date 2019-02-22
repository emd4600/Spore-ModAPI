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

	auto_METHOD_VIRTUAL_(cResourceManager, cResourceManager, bool, NeedsToRelease);
	auto_METHOD_VIRTUAL_(cResourceManager, cResourceManager, bool, ReleaseResources);
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetResource, PARAMS(const ResourceKey& name, ResourceObject** ppDst, int arg_8, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), PARAMS(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func10h, PARAMS(const ResourceKey& name, ResourceObject** ppDst, void** arg_8, void* arg_C, void* arg_10, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pAlternativeName), PARAMS(name, ppDst, arg_8, arg_C, arg_10, pDBPF, pFactory, pAlternativeName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, GetCachedResource, PARAMS(const ResourceKey& name, intrusive_ptr<ResourceObject>* pDst), PARAMS(name, pDst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func18h, PARAMS(int arg_0, int arg_4, int arg_8, int arg_C, int arg_10), PARAMS(arg_0, arg_4, arg_8, arg_C, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, ReadResource, PARAMS(const ResourceKey& name, ResourceObject** ppDst, int arg_8, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pCacheName), PARAMS(name, ppDst, arg_8, pDBPF, pFactory, pCacheName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, WriteResource, PARAMS(const ResourceObject* pResource, int arg_4, DBPF* pDBPF, IResourceFactory* pFactory, const ResourceKey* pNameKey), PARAMS(pResource, arg_4, pDBPF, pFactory, pNameKey));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, SetTypeRemap, PARAMS(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount), PARAMS(nTypeID, pnTypes, nCount));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetTypeRemap, PARAMS(vector<uint32_t>& dst, uint32_t nTypeID), PARAMS(dst, nTypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, uint32_t, GetGeneralTypeID, PARAMS(uint32_t nSubtypeID), PARAMS(nSubtypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, DBPF*, GetRealFileKey, PARAMS(const ResourceKey& nameKey, ResourceKey* pDst, DBPF* pDBPF), PARAMS(nameKey, pDst, pDBPF));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, func34h, PARAMS(vector<ResourceKey>& pDst, int arg_4), PARAMS(pDst, arg_4));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetFileKeys, PARAMS(vector<ResourceKey>& dst, IResourceFilter* request, vector<DBPF*>* pDstDBPFs), PARAMS(dst, request, pDstDBPFs));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, int, func3Ch, PARAMS(int arg_0, int arg_4, int arg_8), PARAMS(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func40h, PARAMS(int arg_0, int arg_4, int arg_8, int arg_c, int arg_10), PARAMS(arg_0, arg_4, arg_8, arg_c, arg_10));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetResourceFactory, PARAMS(bool bRemove, IResourceFactory* pFactory, uint32_t arg_8), PARAMS(bRemove, pFactory, arg_8));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, IResourceFactory*, GetResourceFactory, PARAMS(uint32_t nTypeID, uint32_t nSubTypeID), PARAMS(nTypeID, nSubTypeID));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetResourceFactories, PARAMS(list<IResourceFactory*>& dst, uint32_t nTypeID), PARAMS(dst, nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddDBPF, PARAMS(bool arg_0, DatabasePackedFile* pDBPF, int nPriority), PARAMS(arg_0, pDBPF, nPriority));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, bool, GetPriority, PARAMS(DatabasePackedFile* pDBPF, int* pDst), PARAMS(pDBPF, pDst));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, DatabasePackedFile*, GetDBPF, PARAMS(const ResourceKey& name), PARAMS(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, size_t, GetAllDBPFs, PARAMS(DBPFList& dst, const ResourceKey* pFileKey), PARAMS(dst, pFileKey));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, int, func60h, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func64h, PARAMS(int arg_0, int arg_4, int arg_8), PARAMS(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, IResourceMap*, GetResourceCache, PARAMS(ResourceKey& name), PARAMS(name));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, func6Ch, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL_VOID(cResourceManager, cResourceManager, func70h, PARAMS(IResourceMap* arg_0, SpecialResourceObject* arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, size_t, GetResourceCaches, PARAMS(list<IResourceMap*>& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddFileName, PARAMS(const wchar_t* pFileName), PARAMS(pFileName));
	auto_METHOD_VIRTUAL_VOID_const(cResourceManager, cResourceManager, GetFileName, PARAMS(const ResourceKey& resourceKey, wstring& dst), PARAMS(resourceKey, dst));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, SetFileName, PARAMS(const ResourceKey& resourceKey, const wchar_t* pFileName), PARAMS(resourceKey, pFileName));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RemoveFileName, PARAMS(const ResourceKey& resourceKey), PARAMS(resourceKey));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, uint32_t, GetTypeID, PARAMS(const wchar_t* pExtension), PARAMS(pExtension));
	auto_METHOD_VIRTUAL_const(cResourceManager, cResourceManager, wchar_t*, GetExtension, PARAMS(uint32_t nTypeID), PARAMS(nTypeID));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, AddExtensionMapping, PARAMS(uint32_t nTypeID, const wchar_t* pExtension), PARAMS(nTypeID, pExtension));
	auto_METHOD_VIRTUAL(cResourceManager, cResourceManager, bool, RemoveExtensionMapping, PARAMS(uint32_t nTypeID), PARAMS(nTypeID));
}