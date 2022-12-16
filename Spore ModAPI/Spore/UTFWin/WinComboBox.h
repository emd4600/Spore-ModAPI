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

#error "Not implemented yet; use IComboBox"

#include "..\Internal.h"
#include "Window.h"
#include "ScrollbarDrawable.h"
#include "ComboBoxDrawable.h"
#include <EASTL\vector.h>

namespace UTFWin
{
	

	//class ComboBoxUnknown
	//{
	//	virtual void func0(int) = 0;
	//	virtual void func1(int, int) = 0;
	//	virtual ~ComboBoxUnknown() = 0;  // Release
	//};

	//class WinComboBox : public Window, public IComboBox, ComboBoxUnknown
	//{
	//private:

	//	char _padding_214[0x8];
	//	
	//	/* 21Ch */	int selectedIndex = 0;
	//	/* 220h */	Color colors[6];
	//	/* 238h */	unsigned int visibleValuesCount;
	//	/* 23Ch */	ComboBoxFlags::Type comboboxFlags;
	//	/* 240h */	AlignmentH alignment;

	//	int field_244;

	//	// WARNING: I think UTFWin classes actually use other memory functions, so 'spore_allocator' might be wrong
	//	/* 248h */	eastl::vector<eastl::string16> valueList;
	//	/* 25Ch */	intrusive_ptr<IScrollbarDrawable> scrollbarDrawable;

	//	char _padding_260[0x58];

	//public:
	//	static inline WinComboBox* New() {
	//		// __stdcall because it's cleanup by callee
	//		return (WinComboBox*)((IWindow*(__stdcall*)(void*, void*)) SelectAddress(0x969BB0, 0x9697E0))(nullptr, nullptr);
	//	}

	//	virtual METHOD_(SelectAddress(0x98F5C0, 0x95F8F0), ILayoutElement, int, AddRef);
	//	virtual METHOD_(SelectAddress(0x96B700, 0x95F900), ILayoutElement, int, Release);
	//	virtual METHOD(SelectAddress(0x967CD0, 0x967940), ILayoutElement, void*, Cast, Args(uint32_t typeID), Args(typeID));
	//};

	//static_assert(sizeof(WinComboBox) == 0x2B8, "sizeof(WinComboBox) != 2B8h");
}