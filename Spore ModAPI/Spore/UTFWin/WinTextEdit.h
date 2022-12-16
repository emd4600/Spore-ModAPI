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

#error "Not implemented yet; use ITextEdit"

#include "..\Internal.h"
#include "Window.h"
#include "OutlineFormat.h"
#include "ScrollbarDrawable.h"

namespace UTFWin
{
	

	//class WinTextEdit : public Window, public ITextEdit
	//{
	//private:
	//	int field_210;
	//	/* 214h */	TextEditFlags::Type textEditFlags;
	//	int field_218;
	//	/* 21Ch */	TextEditWarpMode wrapMode;
	//	/* 220h */	Math::Rectangle borderWidth;

	//	char _padding_230[0x14];

	//	/* 244h */	Color textColors[8];
	//	/* 264h */	int maxTextLength;
	//	/* 268h */	int cursorIndex;
	//	/* 26Ch */	int anchorIndex;

	//	char _padding_270[0x2B4];

	//	/* 524h */	int undoHistorySize;

	//	char _padding_528[0x5C];

	//	/* 584h */	IDrawablePtr hScrollbarDrawable;
	//	/* 588h */	ScrollbarEnDis hScrollbarEnabled;

	//	char _padding_58C[0xC];

	//	/* 598h */	IDrawablePtr vScrollbarDrawable;
	//	/* 59Ch */	ScrollbarEnDis vScrollbarEnabled;

	//	char _padding_5A0[0x30];

	//	/* 5D0h */	float caretPeriod;

	//	char _padding_5D4[0x50];

	//	/* 624h */	OutlineFormat textOutline;

	//	char _padding_64C[0xC];

	//public:


	//	static inline WinTextEdit* New() {
	//		// __stdcall because it's cleanup by callee
	//		return (WinTextEdit*)((IWindow*(__stdcall*)(void*, void*)) SelectAddress(0x98CDC0, 0x98CAA0))(nullptr, nullptr);
	//	}

	//	/*virtual METHOD_(SelectAddress(0x951FF0, 0), ILayoutElement, int, AddRef);
	//	virtual METHOD_(SelectAddress(0x95FE40, 0), ILayoutElement, int, Release);*/

	//	virtual METHOD_(SelectAddress(0x98F5C0, 0x95F8F0), ILayoutElement, int, AddRef);
	//	virtual METHOD_(SelectAddress(0x96B700, 0x95F900), ILayoutElement, int, Release);
	//	virtual METHOD(SelectAddress(0x9894F0, 0x989140), ILayoutElement, void*, CastToType, Args(unsigned long typeID), Args(typeID));
	//};

	//static_assert(sizeof(WinTextEdit) == 0x658, "sizeof(WinTextEdit) != 658h"); 
}