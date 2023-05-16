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

#include "Internal.h"
#include <EASTL\functional.h>
#include <Spore\CommonIDs.h>
#include <Spore\Hash.h>

///
/// A structure used to point a resource in the game, made by three IDs: instance, group and type.
/// The groupID is used when hashing and comparing, allowing this class to be used in containers such as hash_map
/// or sorted vectors.
///
struct ResourceKey {

	static const uint32_t kWildcardID = 0xFFFFFFFF;

	ResourceKey();
	ResourceKey(uint32_t nInstanceID, uint32_t nTypeID, uint32_t nGroupID);

#ifndef SDK_TO_GHIDRA
	uint32_t instanceID;
	uint32_t typeID;
	uint32_t groupID;
#else
	uint32_t instanceID;
	TypeIDs::Names typeID;
	GroupIDs::Names groupID;
#endif

	///
	/// Creates a ResourceKey from the given text, which is in the format "groupID!instanceID.typeID". 
	/// The groupID and typeID can be ommited, however; if that happens, they will be replaced with the optional parameters
	/// nDefaultGroupID and nDefaultTypeID respectively.
	///
	/// The resulting uint32_ts will be the hashes of the eastl::strings separated by the '!' and '.' signs. The typeID can have a special treatment,
	/// however: before hashing it, it will check if there's a mapping for that extension in the ResourceManager class.
	///
	/// Examples:
	/// Parse(dstKey, "Properties.txt"); // this will be in the global (0x00000000) folder, with the appropiate mapping for the .txt extension)
	/// Parse(dstKey, "CreatureEditorBackground.rw4", 0, 0x40606000);  // this will search in the editor_rigblocks~ (0x40606000) folder.
	/// Parse(dstKey, "CreatureGame!DifficultyTunning.prop");
	///
	/// @param[out] dst The ResourceKey that will be filled with the parsed information.
	/// @param[in] pString The eastl::string to parse.
	/// @param[in] defaultTypeID [Optional] The typeID that will be used if no extension is specified in the text.
	/// @param[in] defaultGroupID [Optional] The groupID that will be used if no group is specified in the text.
	/// @returns True if the text was successfully parsed, false if the given eastl::string was nullptr.
	///
	static bool Parse(ResourceKey& dst, const char16_t* pString, uint32_t defaultTypeID = 0, uint32_t defaultGroupID = 0);

#ifndef SDK_TO_GHIDRA
	bool ResourceKey::operator ==(const ResourceKey &b) const;
	bool ResourceKey::operator !=(const ResourceKey &b) const;

	bool ResourceKey::operator <(const ResourceKey &b) const;
	bool ResourceKey::operator >(const ResourceKey &b) const;
#endif
};
ASSERT_SIZE(ResourceKey, 0xC);

#define instance_id(id) ResourceKey(id, 0, 0)
#define type_id(id) ResourceKey(0, id, 0)
#define group_id(id) ResourceKey(0, 0, id)

inline ResourceKey::ResourceKey()
	: instanceID(0)
	, typeID(0)
	, groupID(0)
{
}

inline ResourceKey::ResourceKey(uint32_t _instanceID, uint32_t _typeID, uint32_t _groupID)
#ifndef SDK_TO_GHIDRA
	: instanceID(_instanceID)
	, typeID(_typeID)
	, groupID(_groupID)
#else
	: instanceID(_instanceID)
	, typeID((TypeIDs::Names)_typeID)
	, groupID((GroupIDs::Names)_groupID)
#endif
{
}

#ifndef SDK_TO_GHIDRA
inline bool ResourceKey::operator ==(const ResourceKey &b) const
{
	return groupID == b.groupID && instanceID == b.instanceID && typeID == b.typeID;
}

inline bool ResourceKey::operator !=(const ResourceKey &b) const
{
	return groupID != b.groupID || instanceID != b.instanceID || typeID != b.typeID;
}

inline bool ResourceKey::operator >(const ResourceKey &b) const
{
	return groupID > b.groupID;
}

inline bool ResourceKey::operator <(const ResourceKey &b) const
{
	return groupID > b.groupID;
}

namespace eastl
{
	/// A necessary structure to be able to use ResourceKey on containers such as hash_map.
	template <> struct hash<ResourceKey>
	{
		size_t operator()(const ResourceKey& val) const { return static_cast<size_t>(val.groupID); }
	};
}
#endif

namespace Addresses(ResourceKey)
{
	DeclareAddress(Parse);
}
