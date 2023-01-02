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

#include <Spore\Palettes\ColorPickerUI.h>
#include <Spore\Palettes\ColorSwatchUI.h>

namespace Palettes
{
	ColorSwatchUI::ColorSwatchUI()
		: mIsLoaded()
		, mIsRollover()
		, mIsMouseDown()
		, mIsShowingPanel()
		, field_10()
		, mIsCustomColor()
		, mIsDefaultColor()
		, mMouseRolloverTime()
		, field_18()
		, mMouseDownTime()
		, mMouseSelectTime()
		, mOriginalColor(1.0f, 1.0f, 1.0f)
		, mColor(1.0f, 1.0f, 1.0f)
		, mpFrameWindow(nullptr)
		, mpFrameGlowWindow(nullptr)
		, mpFrameShineWindow(nullptr)
		, mpColorWindow(nullptr)
		, mpMainWindow(nullptr)
		, mpExpansionWindow(nullptr)
		, mpExpansionObject(nullptr)
		, mExpansionSwatches()
		, mpConfigProp(nullptr)
		, mClock(Clock::Mode::Milliseconds)
		, mClickTime()
		, mPreviousClickTime()
		, mColorIndex(-1)
	{
	}

	int ColorSwatchUI::AddRef()
	{
		return mnRefCount++;
	}

	int ColorSwatchUI::Release()
	{
		int refCount = --mnRefCount;
		if (refCount <= 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	void* ColorSwatchUI::Cast(uint32_t type) const {
		if (type == IWinProc::TYPE)
		{
			return (IWinProc*)this;
		}
		else if (type == Object::TYPE)
		{
			return (Object*)this;
		}
		else if (type == ColorSwatchUI::TYPE)
		{
			return (ColorSwatchUI*)this;
		}
		else 
		{
			return nullptr;
		}
	}

	int ColorSwatchUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagBasicInput | UTFWin::kEventRefresh;
	}

	auto_METHOD_VIRTUAL(ColorSwatchUI, IWinProc, bool, HandleUIMessage, 
		Args(UTFWin::IWindow* pWindow, const UTFWin::Message& message), Args(pWindow, message));

	auto_METHOD_VOID(ColorSwatchUI, Load, 
		Args(App::PropertyList* pConfigProp, struct Math::ColorRGB color, union Math::Rectangle area, UTFWin::IWindow* pContainerWindow, Object* pExpansionObject),
		Args(pConfigProp, color, area, pContainerWindow, pExpansionObject));

	auto_METHOD_VOID(ColorSwatchUI, SetArea, Args(union Math::Rectangle area, bool bUpdateSwatch), Args(area, bUpdateSwatch));

	auto_METHOD_VOID(ColorSwatchUI, GenerateExpansionArea, Args(bool bFitWindow), Args(bFitWindow));

	auto_METHOD_VOID(ColorSwatchUI, AddTooltip, Args(uint32_t instanceID), Args(instanceID));

	auto_METHOD_VOID(ColorSwatchUI, Update, Args(int msTime, bool arg_4), Args(msTime, arg_4));

	auto_METHOD_VOID_(ColorSwatchUI, Destroy);



	ColorPickerUI::ColorPickerUI()
		: field_0C()
		, mpWindow(nullptr)
		, mWidth()
		, mHeight()
		, mSelectedColor(1.0f, 1.0f, 1.0f)
		, mCustomColorIndex(-1)
		, mDefaultColorIndex(-1)
		, mpColorUIs()
		, mColorsCount(0)
		, mpPropList(nullptr)
	{
	}

	int ColorPickerUI::AddRef()
	{
		return mnRefCount++;
	}

	int ColorPickerUI::Release()
	{
		int refCount = --mnRefCount;
		if (refCount <= 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	void* ColorPickerUI::Cast(uint32_t type) const {
		if (type == Object::TYPE)
		{
			return (Object*)this;
		}
		else if (type == ColorPickerUI::TYPE)
		{
			return (ColorPickerUI*)this;
		}
		else
		{
			return nullptr;
		}
	}

	auto_METHOD(ColorPickerUI, bool, Load, 
		Args(UTFWin::IWindow* pWindow, uint32_t propID, uint32_t nRegionFilter, eastl::vector<Math::ColorRGB>* pColors),
		Args(pWindow, propID, nRegionFilter, pColors));

	auto_METHOD_VOID(ColorPickerUI, SetVisible, Args(bool bVisible), Args(bVisible));

	Math::Rectangle ColorPickerUI::GetSwatchArea(int nIndex, bool arg_4) const {
		Math::Rectangle rect;
		CALL(GetAddress(ColorPickerUI, GetSwatchArea), void, 
			Args(const ColorPickerUI*, Math::Rectangle&, int, bool), Args(this, rect, nIndex, arg_4));
		return rect;
	}

	auto_METHOD_VOID(ColorPickerUI, SetColor, Args(const Math::ColorRGB& color), Args(color));
}
#endif
