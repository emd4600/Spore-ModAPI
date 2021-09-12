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

#include <Spore\App\IPropManager.h>
#include <Spore\App\cPropManager.h>

namespace App
{
	auto_STATIC_METHOD_(IPropManager, IPropManager*, Get);

	cPropManager::cPropManager()
		: field_10()
		, mbIsInitialized(false)
		, field_15(false)
		, mpResourceMgr(nullptr)
		, field_1C(false)
		, field_20()
		, mPropertyDefinitions()
		, mPropertyLists()
		, mNamesToPropertyIDs()
		, mPropertyIDsToNames()
		, field_D4()
		, mPropertyGroupNames()
		, mPropertyGroupIDs()
		, field_128()
		, field_148()
		, mCurrentPropertyName()
		, field_178()
		, field_17C(nullptr)
		, field_180()
		, field_190()
		, field_1D4()
		, field_1D8()
		, mbAddToAppProperties(false)
	{
	}

	auto_METHOD_VIRTUAL(cPropManager, IMessageListener, bool, HandleMessage, Args(uint32_t messageID, void* pMessage), Args(messageID, pMessage));

	auto_METHOD_VIRTUAL_(cPropManager, IResourceFactory, uint32_t, GetType);
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, CreateResource, Args(Resource::IPFRecord* pRecord, ResourceObjectPtr& pDst, int arg_8, uint32_t nTypeID), Args(pRecord, pDst, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, AsyncAccess, Args(Resource::IPFRecord** arg_0, int arg_4, Resource::DBPF* arg_8, int arg_c, int arg_10, int arg_14), Args(arg_0, arg_4, arg_8, arg_c, arg_10, arg_14));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, Read, Args(Resource::IPFRecord* pRecord, Resource::ResourceObject* pResource, int arg_8, uint32_t nTypeID), Args(pRecord, pResource, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, Write, Args(Resource::ResourceObject* pResource, Resource::IPFRecord* pRecord, int arg_8, uint32_t nTypeID), Args(pResource, pRecord, arg_8, nTypeID));
	auto_METHOD_VIRTUAL_const(cPropManager, IResourceFactory, size_t, GetSupportedTypes, Args(uint32_t* pDstTypes, size_t nCount), Args(pDstTypes, nCount));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, IsValid, Args(uint32_t nTypeID, uint32_t nSubTypeID), Args(nTypeID, nSubTypeID));

	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, AddRef);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, Release);
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, func08h, Args(bool value), Args(value));
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Initialize);
	auto_METHOD_VIRTUAL_VOID_(cPropManager, IPropManager, PreloadPropertyLists);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Dispose);
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyID, Args(const char* pPropertyName, uint32_t& result), Args(pPropertyName, result));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const char*, GetPropertyName, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func20h, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const char*, GetPropertyGroupName, Args(uint32_t propertyGroupID), Args(propertyGroupID));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, HasPropertyList, Args(uint32_t instanceID, uint32_t groupID), Args(instanceID, groupID));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyList, Args(uint32_t instanceID, uint32_t groupID, PropertyListPtr& pDst), Args(instanceID, groupID, pDst));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetGlobalPropertyList, Args(uint32_t instanceID, PropertyListPtr& pDst), Args(instanceID, pDst));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, SetPropertyList, Args(PropertyList* pList, uint32_t instanceID, uint32_t groupID), Args(pList, instanceID, groupID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func38h, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func3Ch, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func40h, Args(int arg_0, int arg_4, const vector<uint32_t>& instanceIDs), Args(arg_0, arg_4, instanceIDs));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, func44h, Args(size_t nCount, const vector<ResourceKey>& names), Args(nCount, names));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetAllListIDs, Args(uint32_t groupID, vector<uint32_t>& result), Args(groupID, result));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func4Ch, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const Property*, GetPropertyDefinition, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VIRTUAL_const_(cPropManager, IPropManager, size_t, GetPropertyGroupsCount);
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyGroupIDAt, Args(size_t nIndex, uint32_t& dst), Args(nIndex, dst));

}
#endif
