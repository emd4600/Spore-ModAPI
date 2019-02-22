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
		PARAMS(const ResourceKey& name, uint32_t creationTypeID, uint32_t arg_8, uint32_t defaultLayoutID, uint32_t arg_10, uint32_t arg_14, uint32_t arg_18),
		PARAMS(name, creationTypeID, arg_8, defaultLayoutID, arg_10, arg_14, arg_18));

	auto_METHOD_VOID(PaletteMain, ReadModuleProp, PARAMS(const ResourceKey& name), PARAMS(name));

	auto_METHOD(PaletteMain, PaletteCategory*, GetCategory, PARAMS(uint32_t ID), PARAMS(ID));


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
		PARAMS(const ResourceKey& name, uint32_t defaultLayoutID),
		PARAMS(name, defaultLayoutID));

	auto_METHOD(PaletteCategory, bool, HasCategory, PARAMS(PaletteCategory* pCategory), PARAMS(pCategory));

	auto_METHOD(PaletteCategory, PaletteCategory*, GetCategory, PARAMS(uint32_t ID), PARAMS(ID));


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
		PARAMS(const ResourceKey& name, uint32_t thumbnailGroupID, uint32_t arg_8, uint32_t layoutID, uint32_t arg_10),
		PARAMS(name, thumbnailGroupID, arg_8, layoutID, arg_10));

	auto_METHOD(PalettePage, bool, ReadProp,
		PARAMS(const ResourceKey& name, uint32_t layoutID),
		PARAMS(name, layoutID));

	auto_METHOD_VOID(PalettePage, ReadItemsModule,
		PARAMS(const ResourceKey& pageName, const ResourceKey& moduleName, uint32_t thumbnailGroupID),
		PARAMS(pageName, moduleName, thumbnailGroupID));


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
		PARAMS(const ResourceKey& name, int nPagePartPriority, uint32_t thumbnailGroupID),
		PARAMS(name, nPagePartPriority, thumbnailGroupID));


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

	auto_METHOD_VOID(PaletteUI, Load, PARAMS(PaletteMain* pPalette, IWindow* pWindow, bool arg_8, void* arg_C),
		PARAMS(pPalette, pWindow, arg_8, arg_C));

	auto_METHOD_VIRTUAL(PaletteUI, IWinProc, bool, HandleUIMessage, PARAMS(IWindow* pWindow, const Message& message),
		PARAMS(pWindow, message));

	auto_METHOD_VOID(PaletteUI, Update, PARAMS(int arg_0), PARAMS(arg_0));


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

	auto_METHOD_VIRTUAL(PageArrowsUI, IWinProc, bool, HandleUIMessage, PARAMS(IWindow* pWindow, const Message& message),
		PARAMS(pWindow, message));

	auto_METHOD_VOID(PageArrowsUI, Load, PARAMS(IWindow* pWindow, PaletteCategoryUI* pCategoryUI),
		PARAMS(pWindow, pCategoryUI));

	auto_METHOD_VOID(PageArrowsUI, Update, PARAMS(int arg_0), PARAMS(arg_0));


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
		, field_88()
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

	auto_METHOD_VIRTUAL(PaletteCategoryUI, App::IMessageListener, bool, HandleMessage, PARAMS(uint32_t messageID, void* message),
		PARAMS(messageID, message));

	auto_METHOD_VOID(PaletteCategoryUI, Load, PARAMS(PaletteCategory* pCategory, IWindow* pWindow, void* arg_8),
		PARAMS(pCategory, pWindow, arg_8));

	auto_METHOD_VOID(PaletteCategoryUI, FlipPage, PARAMS(int nDelta),
		PARAMS(nDelta));

	auto_METHOD_VOID(PaletteCategoryUI, Update, PARAMS(int arg_0), PARAMS(arg_0));
	
	auto_METHOD_VIRTUAL(PaletteCategoryUI, IWinProc, bool, HandleUIMessage, PARAMS(IWindow* pWindow, const Message& message), PARAMS(pWindow, message));

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

	auto_METHOD(PalettePageUI, Math::Rectangle, GetItemArea, PARAMS(size_t nIndex), PARAMS(nIndex));

	auto_METHOD_VOID(PalettePageUI, Load, PARAMS(PalettePage* pPage, IWindow* pWindow, void* arg_8, size_t nIndex, bool arg_10),
		PARAMS(pPage, pWindow, arg_8, nIndex, arg_10));

	bool PalettePageUI::HandleUIMessage(IWindow* pWindow, const Message& message)
	{
		return true;
	}
}