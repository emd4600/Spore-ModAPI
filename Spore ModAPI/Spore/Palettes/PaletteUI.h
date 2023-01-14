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
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\SporeAnimatedIconWin.h>
#include <Spore\Palettes\PaletteMain.h>
#include <Spore\Palettes\PaletteCategoryUI.h>
#include <Spore\Palettes\PaletteInfo.h>

#define PaletteUIPtr eastl::intrusive_ptr<Palettes::PaletteUI>

namespace Palettes
{
	///
	/// This class holds all information related to the user interface of a palette.
	/// It's the UI representation of a Palettes::PaletteMain.
	///
	class PaletteUI : public UTFWin::IWinProc, public DefaultRefCounted
	{
	public:
		enum ControlIDs
		{
			/// The ControlID and CommandID of the left arrow button that changes the categories displayed.
			kControlLeftArrowBtn = 0x5AEC4B8,
			/// The ControlID and CommandID of the right arrow button that changes the categories displayed.
			kControlRightArrowBtn = 0x05AEC4B9,
			/// The ControlID of the window that contains the category selection buttons.
			kControlCategoryButtons = 0x72DF4CEE,
			/// The ControlID of the window that is used to display the category content (e.g. its pages)
			kControlCategoryContent = 0x93019DBC,


			// #BA83C461 is the solid background shown behind the category buttons to the left of the active one
			// #90D4AADC is the solid background shown behind the category buttons to the right of the active one
		};

	public:
		PaletteUI();
		virtual ~PaletteUI() {};

		/// The UI is generated in the following steps:
		/// 1. The UILayout of the palette is loaded; it's parent is set to pWindow using the 
		/// UTFWin::UILayout::SetParentWindow() method.
		/// 2. The mpMainWindow is set to the window with ControlID 0xFFFFFFFF; if it exists, the method
		/// IWindow::FitParentArea() will be called.
		/// 3. The mAnimatedWindow is set to the window with ControlID 0x49AFE6A1, and it is set invisible.
		/// 4. This object is added as a IWinProc in the windows with ControlID: kControlLeftArrowBtn,
		/// kControlRightArrowBtn and 0x7BCE6E8
		void Load(PaletteMain* pPalette, UTFWin::IWindow* pWindow, bool, PaletteInfo* pInfo);

		void Unload();

		void Update(int msTime);

		void SetActiveCategory(int categoryIndex);


		//// OVERRIDES ////

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t) const override;

		int GetEventFlags() const override;
		bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

	public:
		/// The layout of the palette, loaded using the ID in Palettes::PaletteMain::mLayoutID.
		/* 0Ch */	UILayoutPtr mpLayout;
		/// The window that contains the category selection buttons.
		/* 10h */	UTFWin::IWindow* mpCategoryButtonsWindow;  // 0x72DF4CEE
		/* 14h */	UTFWin::IWindow* field_14;  // 0xBA83C461
		/* 18h */	UTFWin::IWindow* field_18;  // 0x90D4AADC
		/* 1Ch */	UTFWin::IWindow* field_1C;  // 0x05AEFF7F
		/* 20h */	UTFWin::SporeAnimatedIconWin* mpAnimatedWindow;
		/// The window that is used to display the category content (e.g. its pages)
		/* 24h */	UTFWin::IWindow* mpCategoryContent;  // 0x93019DBC
		/// The main window of the UILayout, with ControlID 0xFFFFFFFF.
		/* 28h */	UTFWin::IWindow* mpMainWindow;  // not initialized
		/// The Palettes::PaletteMain that this UI displays.
		/* 2Ch */	PaletteMainPtr mpPalette;
		/* 30h */	PaletteInfoPtr mpPaletteInfo;
		/// The UI objects for all categories contained in the palette. They are in the same order as the PaletteMain::mCategories field.
		/* 34h */	eastl::vector<PaletteCategoryUIPtr> mCategories;
		/* 48h */	eastl::vector<int> field_48;  // intrusive_ptrs too, but it's never used?
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	PaletteCategoryUIPtr mpActiveCategory;
		/* 68h */	bool field_68;
		/* 69h */	bool field_69;

	public:
		const static uint32_t TYPE = 0x52DEED23;
	};
	ASSERT_SIZE(PaletteUI, 0x6C);

	namespace Addresses(PaletteUI)
	{
		DeclareAddress(Load);
		DeclareAddress(Update);
		DeclareAddress(Unload);
		DeclareAddress(HandleUIMessage);
		DeclareAddress(SetActiveCategory);  // 0x5CAE20 0x5CB330
	}
}