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

#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\ResourceKey.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Internal.h>
#include <EASTL\hash_map.h>

/// Access the active species manager.
#define SpeciesManager (*Editors::cSpeciesManager::Get())

namespace Editors
{
	class cSpeciesManager
		: public App::IUnmanagedMessageListener
	{
	public:
		Simulator::cSpeciesProfile* GetSpeciesProfile(const ResourceKey& name);

		//TODO 4DF2D0 used to get plants?

	public:
		/* 04h */	eastl::hash_map<ResourceKey, Simulator::cSpeciesProfile> mSpeciesProfiles;
		/* 24h */	eastl::hash_map<int, int> field_24;
		/* 44h */	eastl::hash_map<int, int> field_44;
		/* 64h */	eastl::hash_map<int, int> field_64;
		/* 84h */	eastl::hash_map<int, int> field_84;
		/* A4h */	ResourceKey mDefaultKey;
		/* B0h */	eastl::hash_map<int, int> field_B0;
		/* D0h */	int field_D0[5];

	public:
		static cSpeciesManager* Get();
	};
	ASSERT_SIZE(cSpeciesManager, 0xE4);

	namespace Addresses(cSpeciesManager) {
		DeclareAddress(Get);

		DeclareAddress(GetSpeciesProfile);
	}
}