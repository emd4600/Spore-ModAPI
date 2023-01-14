#pragma once

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IButton.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\StandardMessage.h>

#define PaletteSubcategoriesUIPtr eastl::intrusive_ptr<Palettes::PaletteSubcategoriesUI>

namespace Palettes
{
	class PaletteCategoryUI;

	class PaletteSubcategoriesUI
		: public UTFWin::IWinProc
		, public App::IUnmanagedMessageListener
		, public DefaultRefCounted
	{
	public:
		using Object::AddRef;
		using Object::Release;

		/* 10h */	IWindowPtr mpContainerWindow;
		/* 14h */	int mActiveCategory;
		/* 18h */	float mButtonHeight;
		/* 1Ch */	float mPageHeight;  // how much of the area is not filled with the category buttons
		/* 20h */	Math::Rectangle mContainerArea;
		/* 30h */	eastl::vector<UTFWin::IButton*> mTitleButtons;
		/* 44h */	eastl::vector<UTFWin::IWindow*> field_44;
		/* 58h */	eastl::vector<UTFWin::IWindow*> mTitleContainers;
		/* 6Ch */	eastl::vector<eastl::intrusive_ptr<PaletteCategoryUI>> mCategoryUIs;
		/* 80h */	eastl::vector<float> mScaleFactors;  // 1 if opened, 0 if not
	};
	ASSERT_SIZE(PaletteSubcategoriesUI, 0x94);
}