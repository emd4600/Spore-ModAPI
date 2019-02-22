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

#include "Window.h"
#include "SliderDrawable.h"

namespace UTFWin
{
	class ISlider : public UTFWinObject
	{
	public:
		/* 10h */	virtual IWindow* ToWindow() = 0;
		// Set orientation of the slider
		/* 14h */	virtual void SetOrientation(Orientation value) = 0;
		// Get orientation of the slider
		/* 18h */	virtual Orientation GetOrientation() = 0;
		// Set current value
		/* 1Ch */	virtual void SetValue(int value, int arg_4) = 0;
		// Get current value
		/* 20h */	virtual int GetValue() = 0;
		// Set minimum value of the slider
		/* 24h */	virtual void SetMinValue(int value, int arg_4) = 0;
		// Get minimum value of the slider
		/* 28h */	virtual int GetMinValue() = 0;
		// Set maximum value of the slider
		/* 2Ch */	virtual void SetMaxValue(int value, int arg_4) = 0;
		// Get maximum value of the slider
		/* 30h */	virtual int GetMaxValue() = 0;
		// Set object to render slider appearance
		/* 34h */	virtual void SetSliderDrawable(ISliderDrawable* drawable) = 0;
		// Get object to render slider appearance
		/* 38h */	virtual ISliderDrawable* GetSliderDrawable() = 0;

		static const unsigned long Type = 0xF00A8A0;
	};

	class WinSlider : public Window, public ISlider
	{

	private:
		/* 210h */	int field_210;
		/* 214h */	int value;
		/* 218h */	int minValue;
		/* 21Ch */	int maxValue;
		/* 220h */	Orientation orientation;
		
		char _padding_224[0x34];

	public:

		static inline WinSlider* New() {
			// __stdcall because it's cleanup by callee
			return (WinSlider*)((IWindow*(__stdcall*)(void*, void*)) GetAddress(0x985D90, 0x985AC0, 0x985AC0))(nullptr, nullptr);
		}

		virtual METHOD_(GetAddress(0x98F5C0, 0x95F8F0, 0x95F8F0), ILayoutElement, int, AddRef);
		virtual METHOD_(GetAddress(0x96B700, 0x95F900, 0x95F900), ILayoutElement, int, Release);
		virtual METHOD(GetAddress(0x983DB0, 0x983A70, 0x983A70), ILayoutElement, void*, Cast, PARAMS(uint32_t typeID), PARAMS(typeID));
	};

	static_assert(sizeof(WinSlider) == 0x258, "sizeof(WinSlider) != 258h");
}