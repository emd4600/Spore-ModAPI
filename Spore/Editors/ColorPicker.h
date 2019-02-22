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

#include <EASTL\vector.h>

#include <Spore\Object.h>
#include <Spore\Timer.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\App\PropertyList.h>

using namespace UTFWin;

namespace Editors
{
	class IColorChooser;

	class ColorSwatch : public IWinProc, public DefaultRefCounted
	{
	public:

		ColorSwatch()
		{
			VOID_THISCALL(GetAddress(0x5A4D30, 0x5A4FF0, 0x5A4FF0), this);
		}
		virtual ~ColorSwatch() {};

		// We must override the functions so we can create new objects

		virtual METHOD_(GetAddress(0x1065680, 0xE31100, 0xE310C0), IWinProc, int, func4);
		virtual METHOD_(GetAddress(0x05A4E20, 0xEA2D20, 0xEA2D20), IWinProc, int, func5);
		virtual METHOD(GetAddress(0x5A58B0, 0x5A5B60, 0x5A5B60), IWinProc, bool, HandleEvent, PARAMS(IWindow* window, const Message& eventInfo), PARAMS(window, eventInfo));

		virtual METHOD_(GetAddress(0x0AE9150, 0xC6AAD0, 0xC6AB00), Object, int, AddRef);
		virtual METHOD_(GetAddress(0x05BF860, 0x7B8750, 0x7B87B0), Object, int, Release);
		virtual METHOD(GetAddress(0x5A3EB0, 0x5A4170, 0x5A4170), Object, void*, CastToType, PARAMS(unsigned long typeID), PARAMS(typeID));


		METHOD_VOID(GetAddress(0x5A4230, 0x5A44F0, 0x5A44F0), ColorSwatch, SetBounds, PARAMS(union Math::Rectangle rect, bool arg_10), PARAMS(rect, arg_10));

		METHOD_VOID_(GetAddress(0x5A4360, 0x5A4620, 0x5A4620), ColorSwatch, sub_5A4360);

		METHOD_VOID_(GetAddress(0x5A5C40, 0x5A5DA0, 0x5A5DA0), ColorSwatch, sub_5A5C40);  // Dispose

		METHOD_VOID(GetAddress(0x5A46C0, 0x5A4980, 0x5A4980), ColorSwatch, sub_5A46C0, PARAMS(int arg_0), PARAMS(arg_0));  // Set expansion area

		METHOD_VOID(GetAddress(0x5A4F00, 0x5A51B0, 0x5A51B0), ColorSwatch, DefaultInitSwatch,
			PARAMS(App::PropertyList* propList, struct ColorRGB color, union Math::Rectangle rect, IWindow* parentWindow, int arg_24),
			PARAMS(propList, color, rect, parentWindow, arg_24));

		METHOD_VOID(GetAddress(0x5A43B0, 0x5A4670, 0x5A4670), ColorSwatch, AddDefaultTooltip, PARAMS(int arg_0), PARAMS(arg_0));

		static const unsigned long TYPE = 0x3B26CA5;


	public:
		/* 0Ch */	bool isInitialized;
		/* 0Dh */	bool isRollover;
		/* 0Eh */	bool isMouseDown;
		/* 0Fh */	bool isShowingPanel;
		/* 10h */	bool field_10;
		/* 11h */	bool isCustomColor;
		/* 12h */	bool isDefaultColor;
		/* 14h */	float mouseRolloverTime;
		/* 18h */	float field_18;
		/* 1Ch */	float mouseDownTime;
		/* 20h */	float mouseSelectTime;
		/* 24h */	ColorRGB originalColor;
		/* 30h */	ColorRGB currentColor;

		// doesn't get initialized!
		/* 3Ch */	Math::Rectangle bounds;

		/* 4Ch */	intrusive_ptr<IWindow> frameWindow;
		/* 50h */	intrusive_ptr<IWindow> frameGlowWindow;
		/* 54h */	intrusive_ptr<IWindow> frameShineWindow;
		/* 58h */	intrusive_ptr<IWindow> colorWindow;
		/* 5Ch */	intrusive_ptr<IWindow> mainWindow;
		/* 60h */	intrusive_ptr<IWindow> panelWindow;
		/* 64h */	intrusive_ptr<IColorChooser> colorChooser;
		/* 68h */	vector<intrusive_ptr<ColorSwatch>> field_68;  // ?

		/* 7Ch */	intrusive_ptr<App::PropertyList> propList;
		/* 80h */	Timer timer;
		/* 98h */	int clickTime;
		/* 9Ch */	int lastClickTime;
		/* A0h */	int colorIndex = -1;

		// these ones don't get initialized!
		/* A4h */	int field_A4;
	};

	static_assert(sizeof(ColorSwatch) == 0xA8, "sizeof(ColorSwatch) != A8h");

	// ?
	class IColorPicker : public Object
	{

	};

	class ColorPicker : public DefaultRefCounted, public IColorPicker
	{
	public:
		/* 0Ch */	intrusive_ptr<Object> field_0C;
		/* 10h */	intrusive_ptr<IWindow> parentWindow;
		/* 14h */	float width;
		/* 18h */	float height;
		/* 1Ch */	ColorRGB selectedColor;
		/* 28h */	int customColorIndex = -1;
		/* 2Ch */	int defaultColorIndex = -1;
		/* 30h */	vector<intrusive_ptr<ColorSwatch>> colors;
		/* 44h */	int colorCount;
		/* 48h */	intrusive_ptr<App::PropertyList> propList;
		/* 4Ch */	int field_4C;

		METHOD_VOID(GetAddress(0x5A4480, 0x5A4740, 0x5A4740), ColorPicker, GetSwatchBounds, PARAMS(Math::Rectangle& dst, int index, int arg_8), PARAMS(dst, index, arg_8));

		METHOD_VOID(GetAddress(0x5A4B50, 0x5A4E10, 0x5A4E10), ColorPicker, sub_5A4B50, PARAMS(ColorRGB& color), PARAMS( color));

		static const unsigned long Type = 0xD0D22119;
	};

	static_assert(sizeof(ColorPicker) == 0x50, "sizeof(ColorPicker) != 50h");
}
