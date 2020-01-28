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
#include <Spore\Palettes\PalettePage.h>
#include <Spore\Palettes\StandardItemUI.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Object.h>

#define PalettePageUIPtr intrusive_ptr<Palettes::PalettePageUI>

namespace Palettes
{
	using namespace eastl;
	using namespace UTFWin;

	///
	/// This class holds all information related with the user interface of a palette page.
	/// It's the UI representation of a Palettes::PalettePage.
	///
	class PalettePageUI : public IWinProc, public DefaultRefCounted
	{
	public:
		enum DisplayType
		{
			kDisplayStandard = 0,
			kDisplayOutfitter = 0xB4E4F69B,
			kDisplaySelectable = 0xECCC3657,
		};


		enum ControlIDs
		{
			/// The ControlID of the panel that will contain the items.
			kControlItemsPanel = 0x12DF7465,
		};

	public:
		PalettePageUI();
		virtual ~PalettePageUI() {};

		void Load(PalettePage* pPage, IWindow* pWindow, void*, size_t nIndex, bool);

		///
		/// Returns the area the item in the given index should have, relative to the items panel.
		/// The layout properties of the page will be applied here. The index is the index to the item in
		/// the Palettes::PalettePage::mItems vector.
		Math::Rectangle GetItemArea(size_t nItemIndex);

		//// OVERRIDES ////

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t);

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	public:
		/// The layout of the palette page, loaded using the ID in Palettes::PalettePage::mLayoutID.
		/* 0Ch */	intrusive_ptr<UILayout> mpLayout;
		/// The panel that will contain the items.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlItemsPanel window.
		/* 10h */	IWindow* mpItemsPanel;
		/* 14h */	intrusive_ptr<PalettePage> mpPage;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	vector<intrusive_ptr<StandardItemUI>> mStandardItems;
		/* 34h */	vector<int> field_34;  // intrusive_ptr with vftable at 0C

	public:
		const static uint32_t TYPE = 0x72DEED2B;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PalettePageUI) == 0x48, "sizeof(PalettePageUI) != 48h");

	namespace Addresses(PalettePageUI)
	{
		DeclareAddress(Load);
		DeclareAddress(GetItemArea);
	}
}
