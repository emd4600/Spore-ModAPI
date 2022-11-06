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
#include <Spore\Object.h>
#include <Spore\Internal.h>

#define PaletteItemPtr eastl::intrusive_ptr<Palettes::PaletteItem>

namespace Palettes
{
	using namespace eastl;

	///
	/// Represents an item inside a palette page. The functionality of the item is not defined here;
	/// this class only has metadata related to the display of the item itself. Each item has one
	/// thumbnail image, the icon.
	class PaletteItem : public DefaultRefCounted, public Object
	{
	public:
		/// The supported types of palette items, which are selected depending on the file extension or
		/// the value of the 'paletteItemType' property.
		/// There might be more that are undocumented.
		enum ItemType
		{
			/// The item used when the item is a .png image file.
			kItemBlock = 0xA2E50993,
			/// The item used when the item is a creation (that is .vcl, .crt, .cll, etc files).
			kItemCreation = 0x674AB27,
			/// The item used in paints (not themes) for block creations (building, vehicle and ufo).
			kItemBlockPaint = 0xBD110A25,
			/// The item used in paint themes for skin creations (building, vehicle and ufo).
			kItemBlockPaintTheme = 0x17D37D90,
			/// The item used in paints (not themes) for skin creations (creature, cell and flora).
			kItemSkinPaint = 0x2B61CC2D,
			/// The item used in paint themes for skin creations (creature, cell and flora).
			kItemSkinPaintTheme = 0xDEE3D8A8,
			/// The 'Paint Like This' item in paint mode.
			kItemPaintLikeThis = 0x800B7988,
			kItemTribeTool = 0x0FCAFD26,
			kItemOutfitter = 0x42BF8C1D,
			kItemCityStyle = 0x2B885DF4,
			/// The item used to select vehicles in cities/colonies.
			kItemCityVehicle = 0x8BFAC054,
			/// The item used to select buildings in cities/colonies.
			kItemCityBuilding = 0x81C74DBC
			//TODO there are missing ones
		};

		PaletteItem();
		virtual ~PaletteItem() {}

		/// 
		/// Loads the configuration of a specific palette item. This only sets fields related to the
		/// item configuration, and not specific to the item type itself. The item type will be set
		/// according to the file extension in the 'name' parameter:
		/// - If typeID == 'png', the type will be Palettes::PaletteItem::ItemType::kItemBlock.
		/// - If typeID == 'crt', 'cll', 'flr', 'vcl', 'bld' or 'ufo', the type will be 
		/// Palettes::PaletteItem::ItemType::kItemCreation.
		/// - If typeID == 'prop', the type will be set according to the 'paletteItemType' property.
		/// @param name The ResourceKey of the item. If no typeID is specified, it will be assumed to be 'prop'.
		/// @param nPagePartPriority The priority of the items module.
		/// @param thumbnailGroupID The group ID of the folder where the icon images are stored.
		/// @returns True if the item is of a recognised type, false otherwise.
		///
		bool Load(const ResourceKey& name, int nPagePartPriority, uint32_t thumbnailGroupID);

		//// OVERRIDES ////

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t) const override;

	public:
		/// The ResourceKey of the object that represents this item.
		/* 0Ch */	ResourceKey mName;
		/// The ResourceKey of the image that will be used as the thumbnail of the item.
		/* 18h */	ResourceKey mThumbnailName;
		/// An ID that determines the type of this block. Common IDs are in the Palettes::PaletteItem::ItemType enum.
		/* 24h */	uint32_t mTypeID;
		/// The instance ID of the icon image used when the item is unlockable (but has not been unlocked yet).
		/* 28h */	uint32_t mUnlockableIconID;
		/// The name of the UI layout used when the item is unlockable (but has not been unlocked yet).
		/* 2Ch */	ResourceKey mUnlockableLayoutName;
		/// The instance ID of the icon image used when the item is locked and not unlockable.
		/* 38h */	uint32_t mNotUnlockableIconID;
		/// The name of the UI layout used when the item is locked and not unlockable.
		/* 3Ch */	ResourceKey mNotUnlockableLayoutName;
		/* 48h */	int mnPartPriority;
		/* 4Ch */	bool mbEnabledLockedRollover;
		/* 50h */	intrusive_ptr<Object> field_50;

	public:
		static const uint32_t TYPE = 0x72D44E3A;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PaletteItem) == 0x54, "sizeof(PaletteItem) != 54h");

	namespace Addresses(PaletteItem)
	{
		DeclareAddress(Load);
	}

}
