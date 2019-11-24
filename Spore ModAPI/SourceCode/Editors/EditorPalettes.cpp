#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Palettes\PaletteMain.h>
#include <Spore\Palettes\PaletteCategory.h>
#include <Spore\Palettes\PalettePage.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Palettes\PaletteUI.h>
#include <Spore\Palettes\PaletteCategoryUI.h>
#include <Spore\Palettes\PalettePageUI.h>
#include <Spore\Palettes\ItemViewer.h>

namespace Palettes
{
	PaletteMain::PaletteMain()
		: mLayoutID(0x8511B8A)
		, mCategories()
		, mCategoryLayoutID()
		, mPageLayoutID()
		, field_2C()
		, mThumbnailGroupID()
		, field_34()
		, mnStartupCategory(-1)
		, mCreationTypeID(-1)
	{
	}

	int PaletteMain::AddRef() { return DefaultRefCounted::AddRef(); }
	int PaletteMain::Release() { return DefaultRefCounted::Release(); }

	void* PaletteMain::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PaletteMain::TYPE)
		{
			return (PaletteMain*) this;
		}
		else {
			return nullptr;
		}
	}

	auto_METHOD(PaletteMain, bool, ReadProp,
		Args(const ResourceKey& name, uint32_t creationTypeID, uint32_t arg_8, uint32_t defaultLayoutID, uint32_t arg_10, uint32_t arg_14, uint32_t arg_18),
		Args(name, creationTypeID, arg_8, defaultLayoutID, arg_10, arg_14, arg_18));

	auto_METHOD_VOID(PaletteMain, ReadModuleProp, Args(const ResourceKey& name), Args(name));

	auto_METHOD(PaletteMain, PaletteCategory*, GetCategory, Args(uint32_t ID), Args(ID));


	//// PALETTE CATEGORY ////

	PaletteCategory::PaletteCategory()
		: mPages()
		, mDLCGroups()
		, mChildren()
		, mLayoutID(0x89845152)
		, mnSequenceNumber()
		, mbPaintByNumber()
		, mRegionFilterID(0xFFFFFFFF)
		, mnSkinPaintIndex(0xFFFFFFFF)
		, mCategoryName()
		, mbForceHasPages()
		, mCategoryID()
		, mCategoryIcon()
		, mCategoryIconList(nullptr)
		, field_8C()
	{
	}

	int PaletteCategory::AddRef() { return DefaultRefCounted::AddRef(); }
	int PaletteCategory::Release() { return DefaultRefCounted::Release(); }

	void* PaletteCategory::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PaletteCategory::TYPE)
		{
			return (PaletteCategory*) this;
		}
		else {
			return nullptr;
		}
	}

	auto_METHOD(PaletteCategory, bool, ReadProp,
		Args(const ResourceKey& name, uint32_t defaultLayoutID),
		Args(name, defaultLayoutID));

	auto_METHOD(PaletteCategory, bool, HasCategory, Args(PaletteCategory* pCategory), Args(pCategory));

	auto_METHOD(PaletteCategory, PaletteCategory*, GetCategory, Args(uint32_t ID), Args(ID));


	//// PALETTE PAGE ////

	PalettePage::PalettePage()
		: mLayoutID(0xD8006607)
		, mDefaultUIClassID()
		, mfItemHeight()
		, mfItemWidth()
		, mfHorizontalOffset()
		, mfVerticalOffset()
		, mfHorizontalSpacing()
		, mfVerticalSpacing()
		, mbIgnoreOverrideThumbnailGroup()
		, mbNoResolutionScale()
		, mBorder()
		, mfItemPercentageWidth()
		, mfItemAspectRatio()
		, mbUseRelativeLayout()
		, mbUseAbsoluteItemSize()
		, mbUseAbsoluteBorderSizes()
		, mfItemMaxPercentageHeight(1.0f)
		, mnNumRows()
		, mnNumColumns()
		, mnSequenceNumber()
		, mSetID()
		, field_60(0xFFFFFFFF)
		, mParentCategory()
		, mItems()
	{
	}

	int PalettePage::AddRef() { return DefaultRefCounted::AddRef(); }
	int PalettePage::Release() { return DefaultRefCounted::Release(); }

	void* PalettePage::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PalettePage::TYPE)
		{
			return (PalettePage*) this;
		}
		else {
			return nullptr;
		}
	}

	auto_METHOD(PalettePage, bool, Load,
		Args(const ResourceKey& name, uint32_t thumbnailGroupID, uint32_t arg_8, uint32_t layoutID, uint32_t arg_10),
		Args(name, thumbnailGroupID, arg_8, layoutID, arg_10));

	auto_METHOD(PalettePage, bool, ReadProp,
		Args(const ResourceKey& name, uint32_t layoutID),
		Args(name, layoutID));

	auto_METHOD_VOID(PalettePage, ReadItemsModule,
		Args(const ResourceKey& pageName, const ResourceKey& moduleName, uint32_t thumbnailGroupID),
		Args(pageName, moduleName, thumbnailGroupID));


	//// PALETTE ITEM ////

	PaletteItem::PaletteItem()
		: mName()
		, mThumbnailName()
		, mTypeID(0xFFFFFFFF)
		, mUnlockableIconID()
		, mUnlockableLayoutName()
		, mNotUnlockableIconID()
		, mNotUnlockableLayoutName()
		, mnPartPriority()
		, mbEnabledLockedRollover()
		, field_50()
	{
	}

	int PaletteItem::AddRef() { return DefaultRefCounted::AddRef(); }
	int PaletteItem::Release() { return DefaultRefCounted::Release(); }

	void* PaletteItem::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PaletteItem::TYPE)
		{
			return (PaletteItem*) this;
		}
		else {
			return nullptr;
		}
	}

	auto_METHOD(PaletteItem, bool, Load,
		Args(const ResourceKey& name, int nPagePartPriority, uint32_t thumbnailGroupID),
		Args(name, nPagePartPriority, thumbnailGroupID));


	//// PALETTE UI ////

	PaletteUI::PaletteUI()
		: mpLayout(nullptr)
		, mpCategoryButtonsWindow()
		, field_14()
		, field_18()
		, field_1C()
		, mpAnimatedWindow(nullptr)
		, mpCategoryContent()
		, mpPalette(nullptr)
		, mCategories()
		, field_48()
		, field_5C()
		, field_60()
		, field_64()
		, field_68()
		, field_69()
	{
	}

	int PaletteUI::AddRef() { return DefaultRefCounted::AddRef(); }
	int PaletteUI::Release() { return DefaultRefCounted::Release(); }

	void* PaletteUI::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PaletteUI::TYPE)
		{
			return (PaletteUI*) this;
		}
		else if (type == IWinProc::TYPE)
		{
			return (IWinProc*) this;
		}
		else {
			return nullptr;
		}
	}

	int PaletteUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagAdvanced | UTFWin::kEventFlagBasicInput;
	}

	auto_METHOD_VOID(PaletteUI, Load, Args(PaletteMain* pPalette, IWindow* pWindow, bool arg_8, void* arg_C),
		Args(pPalette, pWindow, arg_8, arg_C));

	auto_METHOD_VIRTUAL(PaletteUI, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message),
		Args(pWindow, message));

	auto_METHOD_VOID(PaletteUI, Update, Args(int arg_0), Args(arg_0));


	//// PAGE ARROWS UI ////

	PageArrowsUI::PageArrowsUI()
		: mpLayout(nullptr)
		, mpCategoryUI(nullptr)
		, mpPageNumberPanel(nullptr)
		, mpMainWindow(nullptr)
		, field_20(0xFFFFFFFF)
		, field_24(0xFFFFFFFF)
	{
	}

	int PageArrowsUI::AddRef() { return DefaultRefCounted::AddRef(); }
	int PageArrowsUI::Release() { return DefaultRefCounted::Release(); }

	void* PageArrowsUI::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PageArrowsUI::TYPE)
		{
			return (PageArrowsUI*) this;
		}
		else if (type == IWinProc::TYPE)
		{
			return (IWinProc*) this;
		}
		else {
			return nullptr;
		}
	}

	int PageArrowsUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagAdvanced | UTFWin::kEventFlagBasicInput;
	}

	auto_METHOD_VIRTUAL(PageArrowsUI, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message),
		Args(pWindow, message));

	auto_METHOD_VOID(PageArrowsUI, Load, Args(IWindow* pWindow, PaletteCategoryUI* pCategoryUI),
		Args(pWindow, pCategoryUI));

	auto_METHOD_VOID(PageArrowsUI, Update, Args(int arg_0), Args(arg_0));


	//// PALETTE CATEGORY UI ////

	PaletteCategoryUI::PaletteCategoryUI()
		: mpLayout(nullptr)
		, field_14()
		, mpMainFrame(nullptr)
		, mpArrowsPanel(nullptr)
		, mpDLCPanel(nullptr)
		, mpColorPickersPanel(nullptr)
		, mpPagePanel(nullptr)
		, mpPageFrame(nullptr)
		, mpColorPickerUI(nullptr)
		, mpColorPickerUI2(nullptr)
		, field_68()
		, mpCategory(nullptr)
		, mpPageArrowsUI(nullptr)
		, field_74()
		, mPageUIs()
		, field_9C()
		, field_A0()
		, field_A4()
		, field_A8()
		, field_AC()
		, field_B0(6)
		, field_B4()
		, field_B8()
		, field_BC()
		, field_C0()
		, field_C4()
		, field_C8()
		, field_CC(1.0f, 1.0f, 1.0f)
		, field_D8(1.0f, 1.0f, 1.0f)
		, field_E4(true)
		, field_E5(true)
		, field_E8()
	{
	}

	int PaletteCategoryUI::AddRef() { return DefaultRefCounted::AddRef(); }
	int PaletteCategoryUI::Release() { return DefaultRefCounted::Release(); }

	void* PaletteCategoryUI::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PaletteCategoryUI::TYPE)
		{
			return (PaletteCategoryUI*) this;
		}
		else if (type == IWinProc::TYPE)
		{
			return (IWinProc*) this;
		}
		else {
			return nullptr;
		}
	}

	int PaletteCategoryUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagAdvanced | UTFWin::kEventFlagBasicInput;
	}

	auto_METHOD_VIRTUAL(PaletteCategoryUI, App::IMessageListener, bool, HandleMessage, Args(uint32_t messageID, void* message),
		Args(messageID, message));

	auto_METHOD_VOID(PaletteCategoryUI, Load, Args(PaletteCategory* pCategory, IWindow* pWindow, void* arg_8),
		Args(pCategory, pWindow, arg_8));

	auto_METHOD_VOID(PaletteCategoryUI, FlipPage, Args(int nDelta),
		Args(nDelta));

	auto_METHOD_VOID(PaletteCategoryUI, Update, Args(int arg_0), Args(arg_0));
	
	auto_METHOD_VIRTUAL(PaletteCategoryUI, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	//// PALETTE PAGE UI ////

	PalettePageUI::PalettePageUI()
		: mpLayout(nullptr)
		, mpItemsPanel(nullptr)
		, mpPage(nullptr)
		, field_18()
		, field_1C()
		, mStandardItems()
		, field_34()
	{
	}

	int PalettePageUI::AddRef() { return DefaultRefCounted::AddRef(); }
	int PalettePageUI::Release() { return DefaultRefCounted::Release(); }

	void* PalettePageUI::Cast(uint32_t type)
	{
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == PalettePageUI::TYPE)
		{
			return (PalettePageUI*) this;
		}
		else if (type == IWinProc::TYPE)
		{
			return (IWinProc*) this;
		}
		else {
			return nullptr;
		}
	}

	int PalettePageUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagAdvanced | UTFWin::kEventFlagBasicInput;
	}

	auto_METHOD(PalettePageUI, Math::Rectangle, GetItemArea, Args(size_t nIndex), Args(nIndex));

	auto_METHOD_VOID(PalettePageUI, Load, Args(PalettePage* pPage, IWindow* pWindow, void* arg_8, size_t nIndex, bool arg_10),
		Args(pPage, pWindow, arg_8, nIndex, arg_10));

	bool PalettePageUI::HandleUIMessage(IWindow* pWindow, const Message& message)
	{
		return true;
	}



	auto_METHOD_VOID_(ItemViewer, InitializeViewerCamera);
}
#endif
