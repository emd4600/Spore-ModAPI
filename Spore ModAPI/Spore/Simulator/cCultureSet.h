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

#include <Spore\ResourceKey.h>
#include <Spore\CommonIDs.h>
#include <EASTL\map.h>

namespace Simulator
{
	/// Contains the IDs of all the creation types of a specific "culture" or civilization/empire. This maps
	/// each member of the ModelTypes enum to a creation ID.
	/// Note: Does not store creature data.
	class cCultureSet
	{
	public:
		cCultureSet();
		~cCultureSet() {};

		///
		/// Assigns a creation to a certain type. The available types can be found in the ModelTypes enum, such
		/// as "BuildingCityHall". The ResourceKey points directly to the creation model (the .bld, .crt,... files)
		/// @param creationType
		/// @param modelKey
		///
		const ResourceKey& SetCreation(ModelTypes creationType, const ResourceKey& modelKey);

		const ResourceKey* GetCreation(ModelTypes creationType);

		/// Returns the creation assigned to the specific type, or picks one randomly if there is no creation assigned yet.
		/// @param creationType
		const ResourceKey& PickCreation(ModelTypes creationType);

		//TODO other methods such as sub_BF89F0, sub_BF8DF0

	public:
		eastl::map<uint32_t, ResourceKey> mModelTypeToKeyMap;
	};
	ASSERT_SIZE(cCultureSet, 0x1C);

	namespace Addresses(cCultureSet) 
	{
		DeclareAddress(PickCreation);  // 0xBF8DF0 0xBF9840
	}
}