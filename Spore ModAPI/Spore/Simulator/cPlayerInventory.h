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

#include <Spore\Simulator\cSpaceInventory.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cSpaceToolData.h>

#define cPlayerInventoryPtr intrusive_ptr<Simulator::cPlayerInventory>

namespace Simulator
{
	class cPlayerInventory
		: public cSpaceInventory
	{
	public:
		static const uint32_t TYPE = 0x9073163B;
		static const uint32_t NOUN_ID = 0x2265FDC;

		/// Checks mInventoryItems and mUnlockableTools and returns the tool that has the specified id,
		/// or null otherwise
		/// @param id
		cSpaceToolData* GetUnlockableTool(const ResourceKey& id) const;

	public:
		/* 4Ch */	vector<cSpaceInventoryItemPtr> mUnlockableTools;
		/* 60h */	vector<int> field_60;
		/* 74h */	vector<ResourceKey> mUpgradedToolIds;
		/* 88h */	cSpaceToolDataPtr mpDropCargoTool;
		/* 8Ch */	cSpaceToolDataPtr mpActiveTool;
		/* 90h */	cSpaceInventoryItemPtr mpActiveCargoItem;
		/* 94h */	bool mbHasAddedItem;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cPlayerInventory) == 0x98, "sizeof(cPlayerInventory) != 0x98");

	namespace Addresses(cPlayerInventory)
	{
		DeclareAddress(GetUnlockableTool);
	}
}