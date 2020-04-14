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

#include <Spore\ResourceID.h>
#include <Spore\App\PropertyList.h>

using namespace eastl;
using namespace Resource;

/// Access the active property manager.
#define PropManager (*App::IPropManager::Get())

#define IPropManagerPtr intrusive_ptr<App::IPropManager>

namespace App
{
	///
	/// A manager that stores all the property lists in the game, used for most configurations. Property lists (.prop files) are
	/// simple instances of the class PropertyList that contains properties. This is used for configuring most objects and things
	/// in the game.
	///
	/// A property manager can also contain definitions for properties, which are stored in the Properties.txt and AppProperties.txt
	/// files.
	///
	class IPropManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual void func08h(bool value) = 0;
		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual void PreloadPropertyLists() = 0;
		/* 14h */	virtual bool Dispose() = 0;

		///
		/// Gets the ID that corresponds to the given property name. This function will only work for those names
		/// that are mapped in this manager.
		/// @param propertyName The name of the property.
		/// @param[out] result The uint32_t that will receive the ID.
		/// @returns Whether the name was found or not.
		///
		/* 18h */	virtual bool GetPropertyID(const char* propertyName, uint32_t& result) const = 0;

		///
		/// Gets the name that is mapped to the given propertyID. This function will only work for those names
		/// that are mapped in this manager.
		/// @param propertyID The ID of the property.
		/// @returns The name of the property, or nullptr if it is not mapped.
		///
		/* 1Ch */	virtual const char* GetPropertyName(uint32_t propertyID) const = 0;

		/* 20h */	virtual void* func20h(int arg_0, int arg_4) = 0;

		///
		/// Gets the name assigned to the given property group ID. This function will only work if that group
		/// is mapped in this manager.
		/// @param propertyGroupID The ID of the property group.
		/// @returns The name of the group, or nullptr if it is not mapped.
		///
		/* 24h */	virtual const char* GetPropertyGroupName(uint32_t propertyGroupID) const = 0;

		///
		/// Tells whether a PropertyList with the given instanceID and groupID is contained in this manager.
		/// @param instanceID The instance ID of the list.
		/// @param groupID The group ID of the list.
		/// @returns True if the list exists, false otherwise.
		///
		/* 28h */	virtual bool HasPropertyList(uint32_t instanceID, uint32_t groupID) const = 0;

		///
		/// Gets the PropertyList stored in the given group and with the given instanceID.
		/// @param instanceID The instance ID of the list.
		/// @param groupID The group ID of the list.
		/// @param pDst A PropertyListPtr that will receive the list. It must not be initialized or contain nullptr; the previous pointer
		/// won't be released.
		/// @returns Whether the list was found or not.
		///
		/* 2Ch */	virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr &pDst) const = 0;

		///
		/// Gets the PropertyList stored in the global (0x00000000) folder and with the given instanceID.
		/// @param instanceID The instance ID of the list.
		/// @param pDst An PropertyListPtr that will receive the list. It must not be initialized or contain nullptr; the previous pointer
		/// won't be released.
		/// @returns Whether the list was found or not.
		///
		/* 30h */	virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyListPtr &pDst) = 0;

		///
		/// Adds this property list with the given instance and group ID, or replaces the existing one.
		/// @param pList The new PropertyList.
		/// @param instanceID The instance ID of the property list.
		/// @param groupID The group ID of the property list.
		///
		/* 34h */	virtual void SetPropertyList(PropertyList* pList, uint32_t instanceID, uint32_t groupID) = 0;

		/* 38h */	virtual void* func38h(int arg_0) = 0;
		/* 3Ch */	virtual void* func3Ch(int arg_0, int arg_4) = 0;
		/* 40h */	virtual void* func40h(int arg_0, int arg_4, const vector<uint32_t>& instanceIDs) = 0;

		// Get used lists?
		/* 44h */	virtual bool func44h(size_t nCount, const vector<ResourceKey>& names) = 0;

		///
		/// Gets the instance IDs of all the PropertyList objects contained in the specified group.
		/// @param groupID The ID of the group where the lists are (i.e. the folder)
		/// @param[out] result A uint32_t vector that will receive the instance IDs.
		/// @param 
		///
		/* 48h */	virtual bool GetAllListIDs(uint32_t groupID, vector<uint32_t>& result) const = 0;

		/* 4Ch */	virtual void* func4Ch(int arg_0, int arg_4) = 0;

		///
		/// Gets the property definition of the property with the given ID. The definition is a Property object that 
		/// contains the type and default value of the property. Definitions are stored in the Properties.txt,
		/// AppProperties.txt, etc files.
		/// @param propertyID The ID of the property.
		/// @returns The Property that contains the type and default value, or nullptr if there is no definition for that property.
		///
		/* 50h */	virtual const Property* GetPropertyDefinition(uint32_t propertyID) const = 0;

		///
		/// Gets the number of property groups contained in this manager.
		///
		/* 54h */	virtual size_t GetPropertyGroupsCount() const = 0;

		///
		/// Gets the ID of the property group at the given index.
		/// @param index The index of the group inside this manager.
		/// @param[out] dst The uint32_t that will receive the ID.
		/// @returns Whether the index was valid or not.
		///
		/* 58h */	virtual bool GetPropertyGroupIDAt(size_t index, uint32_t& dst) const = 0;

	public:

		/// Returns the object that is the currently active property manager.
		static IPropManager* Get();
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IPropManager)
	{
		DeclareAddress(Get);
	}
}
