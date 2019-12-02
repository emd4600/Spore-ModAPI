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
	using namespace eastl;

	class cSpeciesManager
		: public App::IUnmanagedMessageListener
	{
	public:
		Simulator::cSpeciesProfile* GetSpeciesProfile(const ResourceKey& name);

	protected:
		/* 04h */	hash_map<ResourceKey, Simulator::cSpeciesProfile> field_4;
		/* 24h */	hash_map<int, int> field_24;
		/* 44h */	hash_map<int, int> field_44;
		/* 64h */	hash_map<int, int> field_64;
		/* 84h */	hash_map<int, int> field_84;
		/* A4h */	int field_A4[3];
		/* B0h */	hash_map<int, int> field_B0;
		/* D0h */	int field_D0[5];

	public:
		static cSpeciesManager* Get();
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpeciesManager) == 0xE4, "sizeof(cSpeciesManager) != E4h");

	namespace Addresses(cSpeciesManager) {
		DeclareAddress(Get);

		DeclareAddress(GetSpeciesProfile);
	}
}