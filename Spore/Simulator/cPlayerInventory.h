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

namespace Simulator
{
	class cPlayerInventory
		: public cSpaceInventory
	{
	public:
		static const uint32_t TYPE = 0x9073163B;
		static const uint32_t NOUN_ID = 0x2265FDC;

		cSpaceToolData* GetUnlockableTool(const ResourceKey& id);

	public:
		/* 4Ch */	vector<intrusive_ptr<cSpaceInventoryItem>> mUnlockableTools;
		/* 60h */	vector<int> field_60;
		/* 74h */	vector<ResourceKey> mUpgradedToolIds;
		/* 88h */	intrusive_ptr<cSpaceToolData> mpDropCargoTool;
		/* 8Ch */	intrusive_ptr<cSpaceToolData> mpActiveTool;
		/* 90h */	intrusive_ptr<cSpaceInventoryItem> mpActiveCargoItem;
		/* 94h */	bool mbHasAddedItem;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cPlayerInventory) == 0x98, "sizeof(cPlayerInventory) != 0x98");

	namespace InternalAddressList(cPlayerInventory)
	{
		DefineAddress(GetUnlockableTool, GetAddress(0xFF4640, 0xFF3BF0, 0xFF3BF0));
	}
}