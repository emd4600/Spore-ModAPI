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
#include <EASTL\hash_map.h>
#include <EASTL\string.h>
#include <EASTL\intrusive_ptr.h>


#include <Spore\App\IPropManager.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\IResourceFactory.h>
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\Line.h>

namespace App
{
	///
	/// The implementation of IPropManager; this should only be used for extending and detouring.
	///
	class cPropManager : public IPropManager, public IResourceFactory, public IMessageListener
	{
	public:
		cPropManager();
		virtual ~cPropManager() {};

		// Overrides

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		virtual uint32_t GetType() override;
		virtual bool CreateResource(IPFRecord* pRecord, ResourceObject*& pDst, int, uint32_t nTypeID) override;
		virtual bool AsyncAccess(IPFRecord** ppDst, int, DBPF* pDBPF, int, int, int) override;
		virtual bool Read(IPFRecord* pRecord, ResourceObject* pResource, int, uint32_t nTypeID) override;
		virtual bool Write(ResourceObject* pResource, IPFRecord* pRecord, int, uint32_t nTypeID) override;
		virtual size_t GetSupportedTypes(uint32_t* pDstTypes, size_t nCount) const override;
		virtual bool IsValid(uint32_t nTypeID, uint32_t nSubTypeID) override;

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void func08h(bool value) override;
		virtual bool Initialize() override;
		virtual void PreloadPropertyLists() override;
		virtual bool Dispose() override;
		virtual bool GetPropertyID(const char* pPropertyName, uint32_t& result) const override;
		virtual const char* GetPropertyName(uint32_t propertyID) const override;
		virtual void* func20h(int arg_0, int arg_4) override;
		virtual const char* GetPropertyGroupName(uint32_t propertyGroupID) const override;
		virtual bool HasPropertyList(uint32_t instanceID, uint32_t groupID) const override;
		virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList::Pointer& pDst) const override;
		virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyList::Pointer& pDst) override;
		virtual void SetPropertyList(PropertyList* pList, uint32_t instanceID, uint32_t groupID) override;
		virtual void* func38h(int arg_0) override;
		virtual void* func3Ch(int arg_0, int arg_4) override;
		virtual void* func40h(int arg_0, int arg_4, const vector<uint32_t>& instanceIDs) override;
		virtual bool func44h(size_t nCount, const vector<ResourceKey>& names) override;
		virtual bool GetAllListIDs(uint32_t groupID, vector<uint32_t>& result) const override;
		virtual void* func4Ch(int arg_0, int arg_4) override;
		virtual const Property* GetPropertyDefinition(uint32_t propertyID) const override;
		virtual size_t GetPropertyGroupsCount() const override;
		virtual bool GetPropertyGroupIDAt(size_t nIndex, uint32_t& dst) const override;


	protected:
		/* 10h */	int field_10;
		/* 14h */	bool mbIsInitialized;
		/* 15h */	bool field_15;
		/* 18h */	IResourceManager* mpResourceMgr;
		/* 1Ch */	bool field_1C;
		/* 20h */	map<uint32_t, Property> field_20;
		// only contains appproperties?
		/* 3Ch */	PropertyList mPropertyDefinitions;  // if !field_1C, used to store default values of properties.trigger?
		/* 74h */	hash_map<ResourceID, PropertyList::Pointer> mPropertyLists;
		/* 94h */	hash_map<string, uint32_t> mNamesToPropertyIDs;
		/* B4h */	hash_map<uint32_t, string> mPropertyIDsToNames;
		/* D4h */	hash_map<string, int> field_D4;
		/* F4h */	hash_map<uint32_t, string> mPropertyGroupNames;
		/* 114h */	vector<uint32_t> mPropertyGroupIDs;
		/* 128h */	hash_map<int, int> field_128;
		/* 148h */	hash_map<int, int> field_148;
		/* 168h */	string mCurrentPropertyName;  // in lower case, used as temporary
		/* 178h */	int field_178;
		/* 17Ch */	intrusive_ptr<ArgScript::FormatParser> field_17C;
		/* 180h */	string field_180;
		/* 190h */	ArgScript::Line field_190;
		/* 1D4h */	int field_1D4;
		/* 1D8h */	string field_1D8;
		/* 1E8h */	bool mbAddToAppProperties;  // add property to direct property list
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(cPropManager) == 0x1EC, "sizeof(PropManager) must be 1ECh");

	namespace Addresses(cPropManager)
	{
		DeclareAddress(HandleMessage);

		DeclareAddress(GetType);
		DeclareAddress(CreateResource);
		DeclareAddress(AsyncAccess);
		DeclareAddress(Read);
		DeclareAddress(Write);
		DeclareAddress(GetSupportedTypes);
		DeclareAddress(IsValid);

		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(func08h);
		DeclareAddress(Initialize);
		DeclareAddress(PreloadPropertyLists);
		DeclareAddress(Dispose);
		DeclareAddress(GetPropertyID);
		DeclareAddress(GetPropertyName);
		DeclareAddress(func20h);
		DeclareAddress(GetPropertyGroupName);
		DeclareAddress(HasPropertyList);
		DeclareAddress(GetPropertyList);
		DeclareAddress(GetGlobalPropertyList);
		DeclareAddress(SetPropertyList);
		DeclareAddress(func38h);
		DeclareAddress(func3Ch);
		DeclareAddress(func40h);
		DeclareAddress(func44h);
		DeclareAddress(GetAllListIDs);
		DeclareAddress(func4Ch);
		DeclareAddress(GetPropertyDefinition);
		DeclareAddress(GetPropertyGroupsCount);
		DeclareAddress(GetPropertyGroupIDAt);


	}
}