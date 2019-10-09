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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <EASTL\vector.h>

namespace Simulator
{
	class cSpaceInventory
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0xB075DEC5;
		static const uint32_t NOUN_ID = 0x21FFA3F;

		/* 54h */	virtual void func54h();
		/* 58h */	virtual void SetMaxCargoAmount(int amount);
		/* 5Ch */	virtual size_t GetItemCount();
		/* 60h */	virtual cSpaceInventoryItem* GetItem(size_t index);
		/* 64h */	virtual int IndexOf(int type, const ResourceKey& id);
		/* 68h */	virtual cSpaceInventoryItem* GetTool(const ResourceKey& id);  // calls IndexOf with type 2
		/* 6Ch */	virtual int func6Ch(int type, size_t);
		/* 70h */	virtual bool HasItem(int itemType, uint32_t id) = 0;
		// apparently only the instanceid matters, gets it with item type 2
		/* 74h */	virtual bool HasTool(const ResourceKey& id) = 0;
		/* 78h */	virtual bool RemoveItem(cSpaceInventoryItem* pItem);  // also sets pItem->mpCargoSlot = nullptr
																		  // Transfer ammo? If it's a tool substracts count from items[index] and sets dst.count = count
		/* 7Ch */	virtual bool func7Ch(size_t index, intrusive_ptr<cSpaceInventoryItem>& dst, int count);

		///
		/// Adds the given item to the inventory. If it already exists, it returns false. If it does not exist
		/// but there is another item with the same ID (and the item is not unique), it will increase the amount
		/// (or ammo) of items with that ID. 
		/* 80h */	virtual void AddItem(cSpaceInventoryItem* pItem, int = 0, bool = true);
		/* 84h */	virtual cSpaceInventoryItem* GetItemByCargSlot(cSpaceInventoryItem* pCargoSlot);  // ?
		/* 88h */	virtual size_t func88h();
		/* 8Ch */	virtual size_t func8Ch();
		/* 90h */	virtual bool func90h(cSpaceInventoryItem*&);
		/* 94h */	virtual void GenerateItems(size_t count);
		/* 98h */	virtual bool func98h(cSpaceInventoryItem* pCargoSlot);

	public:

		/* 34h */	vector<intrusive_ptr<cSpaceInventoryItem>> mInventoryItems;
		/* 48h */	int mMaxItemCountPerItem;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpaceInventory) == 0x4C, "sizeof(cSpaceInventory) != 0x4C");
}