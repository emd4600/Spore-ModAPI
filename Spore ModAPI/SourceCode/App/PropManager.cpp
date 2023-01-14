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
		, mIsDevMode(false)
		, mpResourceMgr(nullptr)
		, field_1C(false)
		, field_20()
		, mPropertyDefinitions()
		, mPropertyLists()
		, mNamesToPropertyIDs()
		, mPropertyIDsToNames()
		, mPropertyGroupNamesToIDs()
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

	auto_METHOD_VIRTUAL_(cPropManager, IResourceFactory, uint32_t, GetFactoryType);
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, CreateResource, Args(Resource::IRecord* pRecord, ResourceObjectPtr& pDst, void* arg_8, uint32_t nTypeID), Args(pRecord, pDst, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, CreateResourceAsync, Args(IAsyncRequestPtr* arg_0, int16_t arg_4, Resource::IRecord* arg_8, void* arg_c, uint32_t arg_10, int arg_14), Args(arg_0, arg_4, arg_8, arg_c, arg_10, arg_14));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, ReadResource, Args(Resource::IRecord* pRecord, Resource::ResourceObject* pResource, void* arg_8, uint32_t nTypeID), Args(pRecord, pResource, arg_8, nTypeID));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, WriteResource, Args(Resource::ResourceObject* pResource, Resource::IRecord* pRecord, void* arg_8, uint32_t nTypeID), Args(pResource, pRecord, arg_8, nTypeID));
	auto_METHOD_VIRTUAL_const(cPropManager, IResourceFactory, size_t, GetSupportedTypes, Args(uint32_t* pDstTypes, size_t nCount), Args(pDstTypes, nCount));
	auto_METHOD_VIRTUAL(cPropManager, IResourceFactory, bool, CanConvert, Args(uint32_t nTypeID, uint32_t nSubTypeID), Args(nTypeID, nSubTypeID));

	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, AddRef);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, int, Release);
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, SetDevMode, Args(bool value), Args(value));
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Initialize);
	auto_METHOD_VIRTUAL_VOID_(cPropManager, IPropManager, PreloadPropertyLists);
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, bool, Dispose);
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetIDFromName, Args(const char* pPropertyName, uint32_t& result), Args(pPropertyName, result));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, const char*, GetNameFromID, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetPropertyGroupIDFromName, Args(const char* arg_0, uint32_t& arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, const char*, GetNameFromPropertyGroupID, Args(uint32_t propertyGroupID), Args(propertyGroupID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, HasPropertyList, Args(uint32_t instanceID, uint32_t groupID), Args(instanceID, groupID));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetPropertyList, Args(uint32_t instanceID, uint32_t groupID, PropertyListPtr& pDst), Args(instanceID, groupID, pDst));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetGlobalPropertyList, Args(uint32_t instanceID, PropertyListPtr& pDst), Args(instanceID, pDst));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, AddPropertyList, Args(PropertyList* pList, uint32_t instanceID, uint32_t groupID), Args(pList, instanceID, groupID));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, RemovePropertyList, Args(PropertyList* arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, RemovePropertyLists, Args(int arg_0, const ResourceKey* arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_VOID(cPropManager, IPropManager, RemovePropertyLists2, Args(uint32_t arg_0, int arg_4, uint32_t* instanceIDs), Args(arg_0, arg_4, instanceIDs));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, AreAnyPropertyListsReferenced, Args(int nCount, const ResourceKey* names), Args(nCount, names));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetPropertyListIDs, Args(uint32_t groupID, eastl::vector<uint32_t>& result), Args(groupID, result));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, void*, func4Ch, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, const Property*, GetPropertyDefinition, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VIRTUAL_(cPropManager, IPropManager, size_t, GetPropertyGroupsCount);
	auto_METHOD_VIRTUAL(cPropManager, IPropManager, bool, GetPropertyGroupIDAt, Args(size_t nIndex, uint32_t& dst), Args(nIndex, dst));

}
#endif
