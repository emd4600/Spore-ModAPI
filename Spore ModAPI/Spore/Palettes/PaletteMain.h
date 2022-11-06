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

#include <Spore\Object.h>
#include <Spore\Palettes\PaletteCategory.h>

#define PaletteMainPtr eastl::intrusive_ptr<Palettes::PaletteMain>

namespace Palettes
{
	// sub_5CB180 generates the category icons

	using namespace eastl;

	///
	/// This object represents the palette of an editor. An editor can have two palettes, one for build mode and the other
	/// for paint mode. Palettes contain categories (Palettes::PaletteCategory), which in turn contain pages (Palettes::PalettePage).
	/// 
	class PaletteMain : public DefaultRefCounted, public Object
	{
	public:
		PaletteMain();
		virtual ~PaletteMain() {} //TODO something else?

		///
		/// Loads the configuration .prop file of this palette, as well as all the page palettes that use it.
		/// All the modules (i.e. prop files that contain a list with all the pages used by the palette) will be loaded;
		/// modules are expected to be inside a folder with ID 0x406B6BXX, where XX are the last two digits of the
		/// instance ID of the palette .prop file.
		///
		/// @param name The ResourceKey that points to the .prop file.
		/// @param creationTypeID The ID that represents the type of creation of the editor, such as 'creature'.
		/// @param arg_8 Sets the field_34 value; it's a folder ID used for icons, but only on very specific occasions.
		/// @param layoutID The default instance ID of the layout file that the palette must use. If this is specified, the
		/// 'palettePaletteLayoutID' property willbe ignored.
		/// @param categoryLayoutID An instance ID that points to the layout categories must use. If this is specified, the 
		/// 'paletteCategoryLayoutFile' property on each category will be ignored.
		/// @param pageLayoutID An instance ID that points to the layout pages must use. If this is specified, the 
		/// 'palettePageLayoutFile' property on each page will be ignored.
		/// @param arg_18 A value that will be set in field_2C.
		/// @returns True if the .prop file existed and was read, false otherwise.
		///
		bool ReadProp(const ResourceKey& name, uint32_t creationTypeID = -1, uint32_t arg_8 = 0, 
			uint32_t layoutID = 0, uint32_t categoryLayoutID = 0, uint32_t pageLayoutID = 0, uint32_t arg_18 = 0);

		///
		/// Loads the configuration .prop of a module that makes up this palette. A certain palette can have infinite modules
		/// that can belong to different mods; each module .prop just contains a list of pages that belong to the palette.
		/// This method will load all those pages as well, using the Palettes::PalettePage::Load() method. All the 
		/// categories used by the pages will be loaded as well, using the Palettes::PaletteCategory::ReadProp() method.
		///
		/// @param name The ResourceKey that points to the .prop file.
		///
		void ReadModuleProp(const ResourceKey& name);

		///
		/// Returns the category or subcategory in this palette that has the specified instance ID. This method will check 
		/// recursively on all the categories and their children categories (if any). If no category has the given ID, 
		/// nullptr will be returned.
		/// @param categoryID The instance ID of the category to return.
		/// @returns The Palettes::PaletteCategory which has that ID, or nullptr if no category has it.
		///
		PaletteCategory* GetCategory(uint32_t categoryID);

		/// 
		/// Returns the category that is at the specified index. Categories are generally ordered by the
		/// Palettes::PaletteCategory::mnSequenceNumber field, with the ones that have the lowest value being first.
		/// @param nIndex The index the category is at in the vector.
		/// @returns The Palettes::PaletteCategory at that index. If the index is out of bounds, the behaviour is undefined.
		///
		PaletteCategory* GetCategoryAt(size_t nIndex);

		void Unload();

		//// OVERRIDES ////

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t) const override;

	public:
		/// A vector with all the categories used in this palette.
		/* 0Ch */	vector<intrusive_ptr<PaletteCategory>> mCategories;
		/// The instance ID of the user interface layout file used by the palette. This layout is the bar at
		/// the top that displays the category buttons. It must also have a window with ControlID 0x93019DBC that will 
		/// contain the category page. 
		/// By default it's 0x8511B8A.
		/* 20h */	uint32_t mLayoutID;

		/// An instance ID that points to the layout categories must use. If this is specified, the 'paletteCategoryLayoutFile'
		/// property on each category will be ignored.
		/* 24h */	uint32_t mCategoryLayoutID;
		/// An instance ID that points to the layout pages must use. If this is specified, the 'palettePageLayoutFile'
		/// property on each page will be ignored.
		/* 28h */	uint32_t mPageLayoutID;
		/* 2Ch */	uint32_t field_2C;  // -> arg_18

		/// The ID of the folder that contains the icons for the parts in the palette, such as 0x02231C8B ('CreaturePartIcons~').
		/* 30h */	uint32_t mThumbnailGroupID;
		/// Related to mThumbnailGroupID. It's only used in the Captain Outfitter palette (not the one from the Create Menu, but
		/// the one you unlock in the game).
		/* 34h */	uint32_t field_34;
		/// The index of the category that will be selected when the editor is first opened. For instance, if the value is
		/// 0, the first category will be selected.
		/* 38h */	uint32_t mnStartupCategory;
		/// The type of creature, as an ID, that the editor of this palette is editing (for example, 'creature').
		/* 3Ch */	uint32_t mCreationTypeID;

	public:
		static const uint32_t TYPE = 0x12DCA0EA;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PaletteMain) == 0x40, "sizeof(PaletteMain) != 40h");

	namespace Addresses(PaletteMain)
	{
		DeclareAddress(GetCategory);
		DeclareAddress(ReadProp);
		DeclareAddress(ReadModuleProp);
		DeclareAddress(Unload);
	}

	inline PaletteCategory* PaletteMain::GetCategoryAt(size_t nIndex)
	{
		return mCategories[nIndex].get();
	}
}

