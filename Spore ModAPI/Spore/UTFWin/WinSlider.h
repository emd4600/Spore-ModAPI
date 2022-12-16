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

#error "Not implemented yet; use ISlider"

namespace UTFWin
{

	//class WinSlider : public Window, public ISlider
	//{

	//private:
	//	/* 210h */	int field_210;
	//	/* 214h */	int value;
	//	/* 218h */	int minValue;
	//	/* 21Ch */	int maxValue;
	//	/* 220h */	Orientation orientation;
	//	
	//	char _padding_224[0x34];

	//public:

	//	static inline WinSlider* New() {
	//		// __stdcall because it's cleanup by callee
	//		return (WinSlider*)((IWindow*(__stdcall*)(void*, void*)) SelectAddress(0x985D90, 0x985AC0))(nullptr, nullptr);
	//	}

	//	virtual METHOD_(SelectAddress(0x98F5C0, 0x95F8F0), ILayoutElement, int, AddRef);
	//	virtual METHOD_(SelectAddress(0x96B700, 0x95F900), ILayoutElement, int, Release);
	//	virtual METHOD(SelectAddress(0x983DB0, 0x983A70), ILayoutElement, void*, Cast, Args(uint32_t typeID), Args(typeID));
	//};

	//static_assert(sizeof(WinSlider) == 0x258, "sizeof(WinSlider) != 258h");
}