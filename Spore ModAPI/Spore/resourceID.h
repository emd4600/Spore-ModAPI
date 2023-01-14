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

#include <stdint.h>
#include <Spore\Internal.h>
#include <EASTL\functional.h>

///
/// Class similar to ResourceKey, but this one is only formed up by an instanceID and a groupID.
/// The groupID is used when hashing and comparing, allowing this class to be used in containers such as hash_map
/// or sorted vectors.
///
class ResourceID
{
public:
	ResourceID();
	ResourceID(uint32_t instanceID, uint32_t groupID);

	uint32_t groupID;
	uint32_t instanceID;
	
#ifndef SDK_TO_GHIDRA
	bool ResourceID::operator ==(const ResourceID &b) const;
#endif
};
ASSERT_SIZE(ResourceID, 0x8);

inline ResourceID::ResourceID(uint32_t _instanceID, uint32_t _groupID)
	: instanceID(_instanceID)
	, groupID(_groupID)
{
};

inline ResourceID::ResourceID()
	: instanceID(0)  // maybe use -1?
	, groupID(0)  // maybe use -1?
{
}

#ifndef SDK_TO_GHIDRA
inline bool ResourceID::operator ==(const ResourceID &b) const
{
	return groupID == b.groupID && instanceID == b.instanceID;
}

namespace eastl
{
	/// A necessary structure to be able to use ResourceID on containers such as hash_map.
	template <> struct hash<ResourceID>
	{
		size_t operator()(const ResourceID& val) const { return static_cast<size_t>(val.groupID); }
	};
}
#endif