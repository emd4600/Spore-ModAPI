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
		: mbIsLoaded()
		, mbIsRollover()
		, mbIsMouseDown()
		, mbIsShowingPanel()
		, field_10()
		, mbIsCustomColor()
		, mbIsDefaultColor()
		, mfMouseRolloverTime()
		, field_18()
		, mfMouseDownTime()
		, mfMouseSelectTime()
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
		, mnClickTime()
		, mnPreviousClickTime()
		, mnColorIndex(-1)
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
		PARAMS(IWindow* pWindow, const Message& message), PARAMS(pWindow, message));

	auto_METHOD_VOID(ColorSwatchUI, Load, 
		PARAMS(const App::PropertyList* pConfigProp, struct Math::ColorRGB color, union Math::Rectangle area, IWindow* pContainerWindow, Object* pExpansionObject),
		PARAMS(pConfigProp, color, area, pContainerWindow, pExpansionObject));

	auto_METHOD_VOID(ColorSwatchUI, SetArea, PARAMS(union Math::Rectangle area, bool bUpdateSwatch), PARAMS(area, bUpdateSwatch));

	auto_METHOD_VOID(ColorSwatchUI, GenerateExpansionArea, PARAMS(bool bFitWindow), PARAMS(bFitWindow));

	auto_METHOD_VOID(ColorSwatchUI, AddTooltip, PARAMS(uint32_t instanceID), PARAMS(instanceID));

	auto_METHOD_VOID(ColorSwatchUI, Update, PARAMS(int arg_0, int arg_4, int arg_8), PARAMS(arg_0, arg_4, arg_8));



	ColorPickerUI::ColorPickerUI()
		: field_0C()
		, mpWindow(nullptr)
		, mfWidth()
		, mfHeight()
		, mSelectedColor(1.0f, 1.0f, 1.0f)
		, mnCustomColorIndex(-1)
		, mnDefaultColorIndex(-1)
		, mpColorUIs()
		, mnColorsCount(0)
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

	auto_METHOD_VOID(ColorPickerUI, Load, 
		PARAMS(IWindow* pWindow, uint32_t propID, uint32_t nRegionFilter, vector<ColorRGB>* pColors),
		PARAMS(pWindow, propID, nRegionFilter, pColors));

	auto_METHOD_VOID(ColorPickerUI, SetVisible, PARAMS(bool bVisible), PARAMS(bVisible));

	auto_METHOD(ColorPickerUI, Math::Rectangle, GetSwatchArea, PARAMS(int nIndex), PARAMS(nIndex));
}