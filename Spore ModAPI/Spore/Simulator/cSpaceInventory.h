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

#define cSpaceInventoryPtr intrusive_ptr<Simulator::cSpaceInventory>

namespace Simulator
{
	class cSpaceInventory
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0xB075DEC5;
		static const uint32_t NOUN_ID = 0x21FFA3F;

		/// Creates 10 cargo slots.
		/* 54h */	virtual void func54h();
		/* 58h */	virtual void SetMaxCargoAmount(int amount);
		/* 5Ch */	virtual size_t GetItemCount();
		/* 60h */	virtual cSpaceInventoryItem* GetItem(size_t index);
		/* 64h */	virtual int IndexOf(SpaceInventoryItemType type, const ResourceKey& id);

		/// Returns the inventory item for the given tool ID, if it is present in the current inventory.
		/// @param id
		/// @returns The tool inventory item (probably a cSpaceToolData), or nullptr if not in the inventory.
		/* 68h */	virtual cSpaceInventoryItem* GetTool(const ResourceKey& id);

		/// Returns the index to the nth item of the given type in this inventory.
		/// For example, nth=3 means it returns the fourth (index starts in 0!) item of the specificed type.
		/// @param type
		/// @param nth
		/// @returns The index of the item (that can be used in GetItem()), or -1 if not present in the inventory.
		/* 6Ch */	virtual int IndexOfNthItem(SpaceInventoryItemType type, size_t nth);

		/// Returns true if the inventory has an item of the given type and item instance id.
		/// @param type
		/// @param id
		/// @returns
		/* 70h */	virtual bool HasItem(SpaceInventoryItemType type, uint32_t id) = 0;

		// apparently only the instanceid matters, gets it with item type 2
		/// Returns true if the inventory has the tool with the given ID (only instance id matters).
		/// Equivalent to `HasItem(SpaceInventoryItemType::Tool, id.instanceID)`.
		/// @param id
		/// @returns
		/* 74h */	virtual bool HasTool(const ResourceKey& id) = 0;

		/* 78h */	virtual bool RemoveItem(cSpaceInventoryItem* pItem);  // also sets pItem->mpCargoSlot = nullptr
																		  // Transfer ammo? If it's a tool substracts count from items[index] and sets dst.count = count
		/* 7Ch */	virtual bool func7Ch(size_t index, intrusive_ptr<cSpaceInventoryItem>& dst, int count);

		///
		/// Adds the given item to the inventory. If it already exists, it returns false. If it does not exist
		/// but there is another item with the same ID (and the item is not unique), it will increase the amount
		/// (or ammo) of items with that ID. 
		/* 80h */	virtual void AddItem(cSpaceInventoryItem* pItem, int = 0, bool = true);

		/// Returns the inventory item that uses the given cargo slot.
		/// @param pCargoSlot
		/// @returns
		/* 84h */	virtual cSpaceInventoryItem* GetItemByCargoSlot(cSpaceInventoryItem* pCargoSlot);

		/// Returns the total amount of cargo slots in the inventory, either used or available.
		/// @returns
		/* 88h */	virtual size_t GetCargoSlotsCount();
		
		/// Returns how many cargo slots are free and available to use.
		/// @returns
		/* 8Ch */	virtual size_t GetAvailableCargoSlotsCount();

		/// Gets the first available cargo slot item. Returns true if an item was written to `pDst`, false
		/// if there are no available cargo slots.
		/// @param pDst
		/// @returns True if `pDst` was written, false if there are no available cargo slots.
		/* 90h */	virtual bool GetFreeCargoSlot(cSpaceInventoryItem*& pDst);

		/// Creates new empty cargo slots and adds them to the inventory.
		/// @param count
		/* 94h */	virtual void AddCargoSlots(size_t count);

		/// Returns true if none of the inventory items use the given item as cargo slot.
		/// @param pCargSlot
		/// @returns
		/* 98h */	virtual bool CargoSlotIsFree(cSpaceInventoryItem* pCargoSlot);

	public:

		/* 34h */	vector<cSpaceInventoryItemPtr> mInventoryItems;
		/* 48h */	int mMaxItemCountPerItem;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpaceInventory) == 0x4C, "sizeof(cSpaceInventory) != 0x4C");
}