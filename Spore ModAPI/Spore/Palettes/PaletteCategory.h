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
#include <Spore\LocalizedString.h>
#include <Spore\Object.h>
#include <Spore\Palettes\PalettePage.h>

namespace Palettes {

	using namespace eastl;

	///
	/// A category in an editor palette contains pages. Pages can be grouped in subcategories (like in the paint region
	/// category: base, coat, detail) and in DLC groups.
	///
	class PaletteCategory : public DefaultRefCounted, public Object
	{
	public:
		PaletteCategory();
		virtual ~PaletteCategory() {};

		///
		/// Loads the configuration .prop file of this category; this does not load the pages nor the subcategories 
		/// contained on it. If the groupID of the ResourceKey given is 0, 0x406B0100 will be used as folder instead.
		///
		/// @param name The ResourceKey that points to the .prop file.
		/// @param defaultLayoutID The default instance ID of the layout file that the category will use, if no layout is specified in the .prop file.
		/// @returns True if the .prop file existed and was read, false otherwise.
		///
		bool ReadProp(const ResourceKey& name, uint32_t defaultLayoutID);

		///
		/// Returns the subcategory in this palette that has the specified instance ID. This method will check 
		/// recursively on all the subcategories and their children categories (if any). If no category has the given ID, 
		/// nullptr will be returned.
		/// @param categoryID The instance ID of the category to return.
		/// @returns The Palettes::PaletteCategory which has that ID, or nullptr if no category has it.
		///
		PaletteCategory* GetCategory(uint32_t categoryID);

		///
		/// Returns the palette page at the specified index. The behaviour is undefined if the index is out of bounds.
		/// @param nIndex
		///
		PalettePage* GetPageAt(size_t nIndex);

		/// 
		/// Tells whether the given  subcategory is a children of this subcategory.
		/// @param pCategory
		bool HasCategory(PaletteCategory* pCategory);

		//// OVERRIDES ////

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t);

	public:
		/// The pages contained in this category.
		/* 0Ch */	vector<intrusive_ptr<PalettePage>> mPages;
		/// The IDs of the DLC groups that divide the pages in the category.
		/* 20h */	vector<uint32_t> mDLCGroups;
		/// Subcategories contained in this category. Subcategories are, for example, the different regions that can
		/// be painted inside the Paint Region category.
		/* 34h */	vector<intrusive_ptr<PaletteCategory>> mChildren;

		/// The instance ID of the user interface layout file used by the category. The layout is expected to have:
		/// - A window that can contain the DLC group buttons (i.e. creepy & Cute, base game, GA)
		/// - A window with ControlID 0x0AF12396 or 0x811C9DC5 (it's not clear which) that will contain the page.
		/// - A window with ControlID 0x92DF6FD8 that will contain the page numbers and arrows.
		/// By default it's 0x89845152.
		/* 48h */	uint32_t mLayoutID;
		/// An integer number that defines the order of this category inside the palette. Categories with lower
		/// sequence number go first.
		/* 4Ch */	uint32_t mnSequenceNumber;
		/* 50h */	bool mbPaintByNumber;
		/// For paint categories: the instance ID of a file that defines which region is painted in partial styles.
		/// This is only for block-paint editors, such as the building editor. The file is assumed to be in the folder with group ID 0x406A6F00.
		/* 54h */	uint32_t mRegionFilterID;
		/* 58h */	uint32_t mnSkinPaintIndex;
		/// The text that is displayed when the category icon is hovered.
		/* 5Ch */	LocalizedString mCategoryName;
		/* 70h */	bool mbForceHasPages;
		/// The ID that identifies this category.
		/* 74h */	uint32_t mCategoryID;
		/// The ID of the parent category, if any.
		/* 78h */	uint32_t mParentCategoryID;
		/// The ResourceKey of the icon used, only if this is a subcategory.
		/* 7Ch */	ResourceKey mCategoryIcon;
		/// A list of 9 ResourceKey objects that point to the icons used in the category button.
		/// The images are in this order:
		/// 1. Normal
		/// 2. Disabled
		/// 3. Highlighted (when the mouse is hovered)
		/// 4. Action (when the mouse is clicked)
		/// 5. On & Normal (when it's selected)
		/// 6. On & Disabled (when it's selected and disabled)
		/// 7. On & Highlighted (when it's selected and the mouse is hovered)
		/// 8. On & Action (when it's selected and the mouse is clicked)
		/// 9. Normal again ?
		/* 88h */	ResourceKey* mCategoryIconList;
		/* 8Ch */	bool field_8C;

	public:
		static const uint32_t TYPE = 0x32C9B8C8;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PaletteCategory) == 0x90, "sizeof(PaletteCategory) != 90h");

	namespace Addresses(PaletteCategory)
	{
		DeclareAddress(ReadProp);
		DeclareAddress(GetCategory);
		DeclareAddress(HasCategory);
	}

	inline PalettePage* PaletteCategory::GetPageAt(size_t nIndex)
	{
		return mPages[nIndex].get();
	}
}
