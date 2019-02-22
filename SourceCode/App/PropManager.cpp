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

	auto_METHOD_VIRTUAL(cPropManager, IMessageListener, bool, HandleMessage, PARAMS(uint32_t messageID, void* pMessage), PARAMS(messageID, pMessage));

	auto_METHOD_VIRTUAL_(cPropManager, IResourceFactory, uint32_t, GetType);
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, CreateResource, PARAMS(IPFRecord* pRecord, ResourceObject*& pDst, int arg_8, uint32_t nTypeID), PARAMS(pRecord, pDst, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, AsyncAccess, PARAMS(IPFRecord** arg_0, int arg_4, DBPF* arg_8, int arg_c, int arg_10, int arg_14), PARAMS(arg_0, arg_4, arg_8, arg_c, arg_10, arg_14));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, Read, PARAMS(IPFRecord* pRecord, ResourceObject* pResource, int arg_8, uint32_t nTypeID), PARAMS(pRecord, pResource, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, Write, PARAMS(ResourceObject* pResource, IPFRecord* pRecord, int arg_8, uint32_t nTypeID), PARAMS(pResource, pRecord, arg_8, nTypeID));
	auto_METHOD_VIRTUAL_const(cPropManager, IResourceFactory, size_t, GetSupportedTypes, PARAMS(uint32_t* pDstTypes, size_t nCount), PARAMS(pDstTypes, nCount));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, IsValid, PARAMS(uint32_t nTypeID, uint32_t nSubTypeID), PARAMS(nTypeID, nSubTypeID));

	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, AddRef);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, Release);
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, func08h, PARAMS(bool value), PARAMS(value));
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Initialize);
	auto_METHOD_VIRTUAL_VOID_(cPropManager, IPropManager, PreloadPropertyLists);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Dispose);
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyID, PARAMS(const char* pPropertyName, uint32_t& result), PARAMS(pPropertyName, result));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const char*, GetPropertyName, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func20h, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const char*, GetPropertyGroupName, PARAMS(uint32_t propertyGroupID), PARAMS(propertyGroupID));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, HasPropertyList, PARAMS(uint32_t instanceID, uint32_t groupID), PARAMS(instanceID, groupID));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyList, PARAMS(uint32_t instanceID, uint32_t groupID, PropertyList::Pointer& pDst), PARAMS(instanceID, groupID, pDst));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetGlobalPropertyList, PARAMS(uint32_t instanceID, PropertyList::Pointer& pDst), PARAMS(instanceID, pDst));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, SetPropertyList, PARAMS(PropertyList* pList, uint32_t instanceID, uint32_t groupID), PARAMS(pList, instanceID, groupID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func38h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func3Ch, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func40h, PARAMS(int arg_0, int arg_4, const vector<uint32_t>& instanceIDs), PARAMS(arg_0, arg_4, instanceIDs));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, func44h, PARAMS(size_t nCount, const vector<ResourceKey>& names), PARAMS(nCount, names));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetAllListIDs, PARAMS(uint32_t groupID, vector<uint32_t>& result), PARAMS(groupID, result));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func4Ch, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, const Property*, GetPropertyDefinition, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_VIRTUAL_const_(cPropManager, IPropManager, size_t, GetPropertyGroupsCount);
	auto_METHOD_VIRTUAL_const(cPropManager, IPropManager, bool, GetPropertyGroupIDAt, PARAMS(size_t nIndex, uint32_t& dst), PARAMS(nIndex, dst));

}