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
#include <Spore\Palettes\IItemFrameUI.h>
#include <Spore\Palettes\PaletteInfo.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Object.h>

#define PalettePageUIPtr eastl::intrusive_ptr<Palettes::PalettePageUI>

namespace Palettes
{
	///
	/// This class holds all information related with the user interface of a palette page.
	/// It's the UI representation of a Palettes::PalettePage.
	///
	class PalettePageUI : public UTFWin::IWinProc, public DefaultRefCounted
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

		const static uint32_t TYPE = 0x72DEED2B;

		PalettePageUI();
		virtual ~PalettePageUI() {};

		void Load(PalettePage* pPage, UTFWin::IWindow* pWindow, PaletteInfo* pInfo, size_t nIndex, bool);

		///
		/// Returns the area the item in the given index should have, relative to the items panel.
		/// The layout properties of the page will be applied here. The index is the index to the item in
		/// the Palettes::PalettePage::mItems vector.
		Math::Rectangle GetItemArea(size_t nItemIndex);

		//// OVERRIDES ////

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t) const override;

		int GetEventFlags() const override;
		bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

	public:
		/// The layout of the palette page, loaded using the ID in Palettes::PalettePage::mLayoutID.
		/* 0Ch */	UILayoutPtr mpLayout;
		/// The panel that will contain the items.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlItemsPanel window.
		/* 10h */	UTFWin::IWindow* mpItemsPanel;
		/* 14h */	PalettePagePtr mpPage;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	eastl::vector<StandardItemUIPtr> mStandardItems;
		/* 34h */	eastl::vector<eastl::intrusive_ptr<IAdvancedItemUI>> mAdvancedItems;
	};
	ASSERT_SIZE(PalettePageUI, 0x48);

	namespace Addresses(PalettePageUI)
	{
		DeclareAddress(Load);
		DeclareAddress(GetItemArea);
	}
}
