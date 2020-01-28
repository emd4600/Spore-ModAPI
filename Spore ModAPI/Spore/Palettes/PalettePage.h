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

#include <EASTL\vector.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Object.h>
#include <Spore\MathUtils.h>

#define PalettePagePtr intrusive_ptr<Palettes::PalettePage>

namespace Palettes
{
	using namespace eastl;

	///
	/// A page in an Palettes palette that contains multiple items (Palettes::PaletteItem).
	/// Items are laid out in rows/columns of cells; each item has an icon that is displayed on its cell. 
	/// Pages belong to a specific category (Palettes::PaletteCategory). A page can belong to a DLC group.
	/// 
	class PalettePage : public DefaultRefCounted, public Object
	{
	public:
		PalettePage();
		virtual ~PalettePage() {}

		///
		/// Loads a page from the .prop file specified, as well as all its items. The items are loaded from different .prop files
		/// contained in a specific folder; the ID of that folder is calculated in the following expression:
		/// (groupID & 0x00FF00FF) | 0x40006D00, where 'groupID' is the group ID of the .prop file of the palette page being loaded.
		/// @param name The ResourceKey that points to the .prop file of the page.
		/// @param thumbnailGroupID The ID of the folder that contains the icons for the parts in the palette, such as 0x02231C8B ('CreaturePartIcons~').
		/// @param arg_8
		/// @param layoutID The instance ID of the layout file that the page will use. If this is specified, the property
		/// 'palettePageLayoutFile' will be ignored.
		/// @param arg_10
		/// @returns True if the .prop file existed and was read, false otherwise.
		///
		bool Load(const ResourceKey& name, uint32_t thumbnailGroupID, uint32_t arg_8 = 0, uint32_t layoutID = 0, uint32_t arg_10 = 0);

		///
		/// Loads the configuration .prop file of this page; this does not load the items contained on it.
		/// palettePageNumRows * palettePageNumColumns will be allocated in the vector field 'mItems' (all the values
		/// will be nullptr, however).
		///
		/// @param name The ResourceKey that points to the .prop file.
		/// @param layoutID The instance ID of the layout file that the page will use. If this is specified, the property
		/// 'palettePageLayoutFile' will be ignored.
		/// @returns True if the .prop file existed and was read, false otherwise.
		///
		bool ReadProp(const ResourceKey& name, uint32_t layoutID = 0);

		///
		/// Reads a .prop file that contains items contained in this page.
		/// @param pageName The ResourceKey of the .prop file of the page.
		/// @param moduleName The ResourceKey of the .prop file of the items module.
		/// @param thumbnailGroupID The group ID where the icons of the items are stored.
		///
		void ReadItemsModule(const ResourceKey& pageName, const ResourceKey& moduleName, uint32_t thumbnailGroupID);

		/// Returns the palette item at the given index. The behaviour is undefined if the index is out of bounds.
		/// @param nIndex
		PaletteItem* GetItemAt(size_t nIndex);

		//// OVERRIDES ////

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t);

	public:
		/// The instance ID of the layout file that will be used in this page. 
		/// By default it's 0xD8006607.
		/* 0Ch */	uint32_t mLayoutID;
		/// The UI class ID given by default to items that are not .prop files or they don't define the 
		/// 'paletteItemUIClassId' property.
		/* 10h */	uint32_t mDefaultUIClassID;
		/// The height of each item in the page, in pixels.
		/* 14h */	float mfItemHeight;
		/// The width of each item in the page, in pixels.
		/* 18h */	float mfItemWidth;
		/// The horizontal offset which item icons are moved relative to their respective cells, in pixels.
		/// For example, an offset of 2 means the item icon will be displayed at X + 2 from where it should be.
		/* 1Ch */	float mfHorizontalOffset;
		/// The vertical offset which item icons are moved relative to their respective cells, in pixels.
		/// For example, an offset of 2 means the item icon will be displayed at Y + 2 from where it should be.
		/* 20h */	float mfVerticalOffset;
		/// The horizontal spacing left between cells, in pixels.
		/* 24h */	float mfHorizontalSpacing;
		/// The vertical spacing left between cells, in pixels.
		/* 28h */	float mfVerticalSpacing;
		/* 2Ch */	bool mbIgnoreOverrideThumbnailGroup;
		/* 2Dh */	bool mbNoResolutionScale;
		/// Interior blank space in the page borders, in pixels.
		/* 30h */	Math::Rectangle mBorder;
		/// A value that scales items horizontally, relative to their cells' width.
		/* 40h */	float mfItemPercentageWidth;
		/* 44h */	float mfItemAspectRatio;
		/* 48h */	bool mbUseRelativeLayout;
		/* 49h */	bool mbUseAbsoluteItemSize;
		/// If true, the values in the mBorder field are measured in pixels, otherwise they are a fraction of the panel size.
		/* 4Ah */	bool mbUseAbsoluteBorderSizes;
		/// A value that scales items vertically, relative to their cells' height.
		/* 4Ch */	float mfItemMaxPercentageHeight;
		/// The number of rows of items can fit in the page; that is, how many items fit vertically. 
		/// Items in coordinates that exceed these limitations will not be displayed. The page space
		/// will be vertically divided in this number of cells.
		/* 50h */	int mnNumRows;
		/// The number of columns of items can fit in the page; that is, how many items fit horizontally. 
		/// Items in coordinates that exceed these limitations will not be displayed. The page space
		/// will be horizontally divided in this number of cells.
		/* 54h */	int mnNumColumns;
		/// An integer number that defines the order of this page inside the category. Pages with lower
		/// sequence number go first.
		/* 58h */	uint32_t mnSequenceNumber;
		/// The ID of the DLC group this page belongs to (0x00000001 is the base game).
		/* 5Ch */	uint32_t mSetID;
		/* 60h */	int field_60;
		/// The ResourceKey of the category this page belongs to.
		/* 64h */	ResourceKey mParentCategory;
		/// The items contained in this page, ordered by columns. The index of a certain cell is mnNumRows * column + row.
		/// If the item is nullptr, the corresponding cell is left blank.
		/* 70h */	vector<intrusive_ptr<PaletteItem>> mItems;

	public:
		static const uint32_t TYPE = 0x32C9B8C8;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PalettePage) == 0x84, "sizeof(PalettePage) != 84h");

	namespace Addresses(PalettePage)
	{
		DeclareAddress(ReadProp);
		DeclareAddress(Load);
		DeclareAddress(ReadItemsModule);
	}

	inline PaletteItem* PalettePage::GetItemAt(size_t nIndex)
	{
		return mItems[nIndex].get();
	}
}

