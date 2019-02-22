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

#include "IWinProc.h"
#include "ILayoutElement.h"
#include "LayoutStyle.h"
#include "UIMemory.h"

namespace UTFWin
{
	class ProportionalLayout : public ModifierWinProc, public DefaultLayoutElement, public LayoutStyle
	{
	private:
		// The relative origin of each edge, as a fraction of parent
		/* 10h */	float proportions[4];

	public:
		ProportionalLayout()
			: proportions{0, 0, 0, 0}
		{
		}
		virtual ~ProportionalLayout() {}

		static inline ProportionalLayout* New() {
			// __stdcall because it's cleanup by callee
			return ((ProportionalLayout*(__stdcall*)(void*, void*)) GetAddress(0x97EDE0, 0x97EB00, 0x97EB00))(nullptr, nullptr);
		}

		virtual METHOD_(GetAddress(0x967570, 0x9802A0, 0x9802D0), IWinProc, int, AddRef);
		virtual METHOD_(GetAddress(0x9841F0, 0x980060, 0x980090), IWinProc, int, Release);
		virtual METHOD(GetAddress(0x97EA40, 0x97E760, 0x97E760), IWinProc, void*, CastToType, PARAMS(unsigned long typeID), PARAMS(this, typeID));
		virtual METHOD_(GetAddress(0x1065680, 0xE31100, 0xE310C0), IWinProc, int, func4);
		virtual METHOD_(GetAddress(0x97EA70, 0x97E790, 0x97E790), IWinProc, int, func5);
		virtual METHOD(GetAddress(0x951370, 0x950E50, 0x950E50), IWinProc, bool, HandleEvent, PARAMS(IWindow* window, Event* eventInfo), PARAMS(this, window, eventInfo));

		virtual METHOD_VOID(GetAddress(0x97EDB0, 0x97EAD0, 0x97EAD0), ILayoutElement, SetBlockDefinition, PARAMS(void* dst), PARAMS(this, dst));
		virtual METHOD_(GetAddress(0x97EAB0, 0x97E7D0, 0x97E7D0), ILayoutElement, int, GetBlockType);

		virtual METHOD_(GetAddress(0x97E760, 0x96FEB0, 0x96FEB0), LayoutStyle, IWinProc*, ToWinProc);
		virtual METHOD_VOID(GetAddress(0x97ECC0, 0x97E9E0, 0x0x97E9E0), LayoutStyle, ApplyLayout, PARAMS(Math::Rectangle& dstBounds, Math::Rectangle& parentBounds), PARAMS(this, dstBounds, parentBounds));
		virtual METHOD(GetAddress(0x97ED30, 0x97EA50, 0x97EA50), LayoutStyle, bool, RevertLayout, PARAMS(Math::Rectangle& dstBounds, Math::Rectangle& parentBounds), PARAMS(this, dstBounds, parentBounds));

		// Get the relative origin of each edge, as a fraction of parent
		virtual METHOD_(GetAddress(0xAD2590, 0x97E7C0, 0x97E7C0), IWinProc, float*, GetProportions);
		// Set the relative origin of each edge, as a fraction of parent
		virtual METHOD_VOID(GetAddress(0x97ECA0, 0x97E9C0, 0x97E9C0), IWinProc, SetProportions, PARAMS(float* proportions), PARAMS(this, proportions));

		virtual METHOD_VOID(GetAddress(0x97EAF0, 0x97E810, 0x97E810), IWinProc, func58h, PARAMS(IWindow* window, Math::Rectangle& parentBounds), PARAMS(this, window, parentBounds));
	};

	static_assert(sizeof(ProportionalLayout) == 0x20, "sizeof(ProportionalLayout) != 20h");
}