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

#include <Spore\App\IMessageListener.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>

#include <Spore\Palettes\PaletteCategory.h>
#include <Spore\Palettes\ColorPickerUI.h>
#include <Spore\Palettes\PalettePageUI.h>
#include <Spore\Palettes\PaletteSubcategoriesUI.h>
#include <Spore\Palettes\PaletteInfo.h>

#define PaletteCategoryUIPtr eastl::intrusive_ptr<Palettes::PaletteCategoryUI>

namespace Palettes
{
	class PageArrowsUI;
	/// Deprecated, only for internal implementation.
	class UnkPageArrowsUI;

	class PaletteSubcategoriesUI;


	///
	/// This class holds all information related with the user interface of a palette category.
	/// It's the UI representation of a Palettes::PaletteCategory.
	///
	class PaletteCategoryUI 
		: public App::IMessageListener
		, public UTFWin::IWinProc
		, public DefaultRefCounted
	{
	public:
		enum ControlIDs
		{
			/// The ControlID of the panel that will contain the buttons for the DLC groups.
			kControlDLCPanel = 0x05D122C0,
			/// The ControlID of the panel that will contain the page number and the arrow buttons to switch pages.
			kControlArrowsPanel = 0x92DF6FD8,
			/// The ControlID of the panel that will contain the current page itself.
			kControlPagePanel = 0x05D1754B,
			/// The ControlID of the window that contains all panels related with pages.
			kControlPageFrame = 0x5D17546,
			/// The ControlID of the window that contains most important windows.
			kControlMainFrame = 0x52DF67AF,
			/// The ControlID of the window that will contain the color picker buttons.
			kControlColorPicker = 0x3304221B, 
			/// The ControlID of the window that will contain the secondary color picker buttons (like in the building editor).
			kControlColorPicker2 = 0x3304221C,
			/// The ControlID of the window that contains the panels that will contain the color picker UI(s).
			kControlColorPickersPanel = 0x5D3F56B,
		};

		const static uint32_t TYPE = 0x72DEED41;

		struct PageUIContainer {
			PalettePageUIPtr page;
			bool isEnabled;
			bool field_5;
			bool dontUpdate;
		};

		PaletteCategoryUI();
		virtual ~PaletteCategoryUI() {};

		void Load(PaletteCategory* pCategory, UTFWin::IWindow* pWindow, PaletteInfo* pInfo);

		void LoadPages(PaletteCategory* pCategory, void*);

		/// Changes the current page, moving it the specified number of pages. If the number is negative, it will move
		/// to a previous page.
		/// @param nDeltaPage The number of pages to move (negative to move backwards).
		void FlipPage(int nDeltaPage);

		void LayoutPagePanel();

		void Update(int msTime);

		//// OVERRIDES ////

		bool HandleMessage(uint32_t messageID, void* pMessage) override;

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t) const override;

		int GetEventFlags() const override;
		bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

	public:
		/// The layout of the palette category, loaded using the ID in Palettes::PaletteCategory::mLayoutID.
		/* 10h */	UILayoutPtr mpLayout;
		/* 14h */	int field_14;
		/// The window that contains most important windows.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlMainFrame window.
		/* 18h */	IWindowPtr mpMainFrame;
		/// The panel that will contain the page number and the arrow buttons to switch pages.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlArrowsPanel window.
		/* 1Ch */	IWindowPtr mpArrowsPanel;
		/// The panel that will contain the buttons for the DLC groups. 
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlDLCPanel window.
		/* 20h */	IWindowPtr mpDLCPanel;
		/// The window that contains the panels that will contain the color picker UI(s).
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlColorPickersPanel window.
		/* 24h */	IWindowPtr mpColorPickersPanel;
		/// The panel that will contain the current page itself.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlPagePanel window.
		/* 28h */	IWindowPtr mpPagePanel;
		/// The window that contains all panels related with pages.
		/// This window contains the mpArrowsPanel, mpDLCPanel and mpPagePanel windows.
		/// It corresponds to the Palettes::PaletteCategoryUI::ControlIDs::kControlPageFrame window.
		/* 2Ch */	IWindowPtr mpPageFrame;
		/// The UI of the color picker buttons.
		/// It is generated and added to the Palettes::PaletteCategoryUI::ControlIDs::kControlColorPicker window.
		/* 30h */	ColorPickerUIPtr mpColorPickerUI;
		/// The UI of the secondary color picker buttons (like in the building editor).
		/// It is generated and added to the Palettes::PaletteCategoryUI::ControlIDs::kControlColorPicker2 window.
		/* 34h */	ColorPickerUIPtr mpColorPickerUI2;
		/// The area occupied by the color picker UI.
		/* 38h */	Math::Rectangle mColorPickerArea;
		/// The area occupied by the secondary color picker UI. If it doesn't exist, it's the same as the primary one.
		/* 48h */	Math::Rectangle mColorPickerArea2;
		/// The area occupied by both color picker UIs. They are expected to be one on top of the other and to have the
		/// same width.
		/* 58h */	Math::Rectangle mTotalColorPickerArea;
		/* 68h */	int field_68;
		/// The Palettes::PaletteCategory that this UI displays.
		/* 6Ch */	PaletteCategoryPtr mpCategory;
		/// The class that manages the piece of UI that displays the page number and the turn page buttons.
		/* 70h */	eastl::intrusive_ptr<PageArrowsUI> mpPageArrowsUI;
		/* 74h */	eastl::vector<int> field_74;
		/* 88h */	eastl::vector<PageUIContainer> mPageUIs;
		/* 9Ch */	PaletteSubcategoriesUIPtr mpSubcategoriesUI;
		/* A0h */	int field_A0;  // current page index?
		/* A4h */	int field_A4;
		/* A8h */	int field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;  // 6
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;
		/* C8h */	uint32_t mPaintID;
		/* CCh */	Math::ColorRGB mPrimaryColor;
		/* D8h */	Math::ColorRGB mSecondaryColor;
		/* E4h */	bool mPrimaryIsDefault;  // true
		/* E5h */	bool mSecondaryIsDefault;  // true
		/* E8h */	eastl::vector<int> field_E8;
	};
	ASSERT_SIZE(PaletteCategoryUI, 0xFC);


	class UnkPageArrowsUI
	{
	public:
		virtual ~UnkPageArrowsUI() {}
		virtual bool func04h(int, int) = 0;
	};


	///
	/// The class that represents the fragment of user interface of the page numbers and arrow buttons in an Editors::PaletteCategory.
	///
	class PageArrowsUI
		: public UTFWin::IWinProc
		, public UnkPageArrowsUI
		, public DefaultRefCounted
	{
	public:
		enum ControlIDs
		{
			/// The ControlID of the main window in the layout.
			kControlMainWindow = 0xFFFFFFFF,
			/// The ControlID of the window (that displays text) that shows the current page number.
			kControlNumbersText = 0x05D122C0,
			/// The ControlID of the button used to turn one page backwards.
			kControlTurnBackBtn = 0x92DF6FD7,
			/// The ControlID of the button used to turn one page forward.
			kControlTurnForwardBtn = 0x92DF6FD6,
		};

		static const uint32_t TYPE = 0xF345E898;

		PageArrowsUI();
		virtual ~PageArrowsUI() {};

		/// Loads the UI for this panel and adds it to the window and given category UI. This method loads the
		/// UI with instance ID 0xB0039D21. This class, which inherits from UTFWin::IWinProc, adds itself as a 
		/// window procedure to the main window of the UI layout loaded, in order to receive events.
		/// @param pWindow
		/// @param pCategoryUI
		void Load(UTFWin::IWindow* pWindow, PaletteCategoryUI* pCategoryUI);

		/// Toggles the visibility of this panel.
		/// @param bVisible Whether the panel must be visible or not.
		void SetVisible(bool bVisible);

		void Update(int);

		//// OVERRIDES ////

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t);

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

		virtual bool func04h(int, int) override {
			return true;
		};
		
	public:
		/// The UI layout of this panel.
		/* 10h */	UILayoutPtr mpLayout;
		/// The UI of the palette category whose page numbers are being displayed by this class.
		/* 14h */	PaletteCategoryUIPtr mpCategoryUI;
		/// The window (something meant to display text) that shows the page number.
		/// It corresponds to the Editors::PaletteCategoryUI::ControlIDs::PageArrowsUI::TODO window.
		/* 18h */	IWindowPtr mpPageNumberPanel;  // a WinText, the page number?
		/// The window that contains all the page number/arrows stuff.
		/// It corresponds to the Editors::PaletteCategoryUI::ControlIDs::PageArrowsUI::TODO window.
		/* 1Ch */	IWindowPtr mpMainWindow;
		/* 20h */	int field_20;  // -1
		/* 24h */	int field_24;  // -1
	};
	ASSERT_SIZE(PageArrowsUI, 0x28);

	class SubcategoryChangedMessage
		: public App::StandardMessage
	{
	public:
		static const uint32_t ID = 0x7956D8A;

		SubcategoryChangedMessage(uint32_t categoryID);

		uint32_t GetCategoryID() const;
	};

	namespace Addresses(PaletteCategoryUI)
	{
		DeclareAddress(Load);
		DeclareAddress(LoadPages);
		DeclareAddress(FlipPage);
		DeclareAddress(HandleMessage);
		DeclareAddress(HandleUIMessage);
		DeclareAddress(Update);
		DeclareAddress(LayoutPagePanel);
	}

	namespace Addresses(PageArrowsUI)
	{
		DeclareAddress(HandleUIMessage);
		DeclareAddress(Load);
		DeclareAddress(Update);
	}

	inline void PageArrowsUI::SetVisible(bool bVisible)
	{
		if (mpMainWindow) mpMainWindow->SetFlag(UTFWin::kWinFlagVisible, bVisible);
	}


	inline SubcategoryChangedMessage::SubcategoryChangedMessage(uint32_t categoryID)
	{
		this->params[0].uint32 = categoryID;
	}

	inline uint32_t SubcategoryChangedMessage::GetCategoryID() const {
		return this->params[0].uint32;
	}
}
