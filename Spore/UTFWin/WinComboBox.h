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

#include "..\Internal.h"
#include "Window.h"
#include "ScrollbarDrawable.h"
#include "ComboBoxDrawable.h"
#include <EASTL\vector.h>

namespace UTFWin
{
	namespace ComboBoxFlags
	{
		typedef uint32_t Type;

		// An outline is drawn around the control when highlighted
		const Type kOutline = 0x00000001;
	};

	enum class ComboBoxColors
	{
		Foreground = 0,
		Background = 1,
		HighlightedForeground = 2,
		HighlightedBackground = 3,
		SelectedForeground = 4,
		SelectedBackground = 5
	};

	class IComboBox : public UTFWinObject
	{
	public:
		/* 10h */	virtual IWindow* ToWindow() = 0;
		/* 14h */	virtual ComboBoxFlags::Type GetComboBoxFlags() = 0;
		/* 18h */	virtual void SetComboBoxFlags(ComboBoxFlags::Type flags) = 0;
		/* 1Ch */	virtual void SetComboBoxFlag(ComboBoxFlags::Type flag, bool value) = 0;
		/* 24h */	virtual void AddValue(const char16_t* value) = 0;
		/* 24h */	virtual bool InsertValue(int index, const char16_t* value) = 0;
		/* 28h */	virtual void ReserveValues(int count) = 0;
		/* 2Ch */	virtual void ClearValues() = 0;
		/* 30h */	virtual bool SetValue(int index, const char16_t* value) = 0;
		/* 34h */	virtual eastl::string16 GetValue(int index) = 0;
		/* 38h */	virtual int GetIndexOf(const char16_t* value) = 0;
		/* 3Ch */	virtual int GetValueCount() = 0;
		/* 40h */	virtual int GetSelectedValue() = 0;
		/* 44h */	virtual void SetSelectedValue(int index, bool value) = 0;
		// Set the text foreground and background colors.
		/* 48h */	virtual void SetColor(ComboBoxColors index, Color color) = 0;
		// Get the text foreground and background colors.
		/* 4Ch */	virtual Color GetColor(ComboBoxColors index) = 0;
		// Set how many values should be shown at once in the pull-down list.
		/* 50h */	virtual void SetVisibleValuesCount(unsigned int count) = 0;
		// Get how many values should be shown at once in the pull-down list.
		/* 54h */	virtual unsigned int GetVisibleValuesCount() = 0;
		// Set the horizontal alignment of the pull-down button within the window area.
		/* 58h */	virtual void SetAlignment(AlignmentH alignment) = 0;
		// Get the horizontal alignment of the pull-down button within the window area.
		/* 5Ch */	virtual AlignmentH GetAlignment() = 0;
		// Set custom scrollbar drawable for pull down menu.
		/* 60h */	virtual void SetScrollbarDrawable(IScrollbarDrawable* drawable) = 0;
		// Get custom scrollbar drawable for pull down menu.
		/* 64h */	virtual IScrollbarDrawable* GetScrollbarDrawable() = 0;
		// Set the object to render combo box appearance.
		/* 68h */	virtual void SetComboBoxDrawable(IComboBoxDrawable* drawable) = 0;
		// Get the object to render combo box appearance.
		/* 6Ch */	virtual IComboBoxDrawable* GetComboBoxDrawable() = 0;
	};

	class ComboBoxUnknown
	{
		virtual void func0(int) = 0;
		virtual void func1(int, int) = 0;
		virtual ~ComboBoxUnknown() = 0;  // Release
	};

	class WinComboBox : public Window, public IComboBox, ComboBoxUnknown
	{
	private:

		char _padding_214[0x8];
		
		/* 21Ch */	int selectedIndex = 0;
		/* 220h */	Color colors[6];
		/* 238h */	unsigned int visibleValuesCount;
		/* 23Ch */	ComboBoxFlags::Type comboboxFlags;
		/* 240h */	AlignmentH alignment;

		int field_244;

		// WARNING: I think UTFWin classes actually use other memory functions, so 'spore_allocator' might be wrong
		/* 248h */	vector<string16> valueList;
		/* 25Ch */	intrusive_ptr<IScrollbarDrawable> scrollbarDrawable;

		char _padding_260[0x58];

	public:
		static inline WinComboBox* New() {
			// __stdcall because it's cleanup by callee
			return (WinComboBox*)((IWindow*(__stdcall*)(void*, void*)) GetAddress(0x969BB0, 0x9697E0, 0x9697E0))(nullptr, nullptr);
		}

		virtual METHOD_(GetAddress(0x98F5C0, 0x95F8F0, 0x95F8F0), ILayoutElement, int, AddRef);
		virtual METHOD_(GetAddress(0x96B700, 0x95F900, 0x95F900), ILayoutElement, int, Release);
		virtual METHOD(GetAddress(0x967CD0, 0x967940, 0x967940), ILayoutElement, void*, Cast, PARAMS(uint32_t typeID), PARAMS(typeID));
	};

	static_assert(sizeof(WinComboBox) == 0x2B8, "sizeof(WinComboBox) != 2B8h");
}