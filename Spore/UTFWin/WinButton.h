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

#error "Not implemented yet; use IButton"

#include "..\Internal.h"

#include "Window.h"
#include "OutlineFormat.h"
#include "IDrawable.h"

namespace UTFWin
{

	namespace ButtonFlags
	{
		typedef uint32_t Type;

		// Button considers itself clicked on mouse/key down rather than mouse/key up
		const Type kTriggerOnDown = 0x00000001;
		// Button is fixed width - this means that you can still resize the window area but the actual button width will remain fixed and and it will be positioned within a given window area. Most often used with radio and check box buttons with caption text positioned to the left or right of the button.
		const Type kFixedWidth = 0x00000002;
		// Button is fixed height - this means that you can still resize the window area but the actual button height will remain fixed and and it will be positioned within a given window area. Most often used with radio and check box buttons with caption text positioned to the left or right of the button
		const Type kFixedHeight = 0x00000004;
	};

	namespace ButtonStateFlags
	{
		typedef uint32_t Type;

		const Type Selected = 4;
	};


	class IButtonDrawable : public IDrawable
	{
		static const unsigned long Type = 0x2F02135C;
	};

	class IButton : public UTFWinObject
	{
	public:
		/* 10h */	virtual IWindow* ToWindow() = 0;

		/* 14h */	virtual void func5(int arg_0) = 0;

		/* 18h */	virtual ButtonTypes GetButtonType() = 0;
		/* 1Ch */	virtual void SetButtonType(ButtonTypes buttonType) = 0;
		/* 20h */	virtual ButtonStateFlags::Type GetButtonStateFlags() = 0;
		/* 24h */	virtual void SetButtonStateFlags(ButtonStateFlags::Type flags) = 0;
		/* 28h */	virtual void SetButtonStateFlag(ButtonStateFlags::Type flag, bool value) = 0;
		/* 2Ch */	virtual ButtonFlags::Type GetButtonFlags() = 0;
		/* 30h */	virtual void SetButtonFlags(ButtonFlags::Type flags) = 0;
		/* 34h */	virtual void SetButtonFlag(ButtonFlags::Type flag, bool value) = 0;
		// Get the horizontal alignment of the button within the window area whenever a fixed width flag is set. This is only the horizontal alignment, the button is always centered vertically. The caption text area always complements the alignment of the button.
		/* 38h */	virtual AlignmentH GetAlignment() = 0;
		// Set the horizontal alignment of the button within the window area whenever a fixed width flag is set. This is only the horizontal alignment, the button is always centered vertically. The caption text area always complements the alignment of the button.
		/* 3Ch */	virtual void SetAlignment(AlignmentH alignment) = 0;
		// Allows to group buttons together. Combined with radio button type this enables radio button group control.
		/* 40h */	virtual unsigned long GetButtonGroupID() = 0;
		// Allows to group buttons together. Combined with radio button type this enables radio button group control.
		/* 44h */	virtual void SetButtonGroupID(unsigned long groupID) = 0;
		// Get the caption color for the given state
		/* 48h */	virtual Color GetCaptionColor(StateIndices index) = 0;
		// Set the caption color for the given state
		/* 4Ch */	virtual void SetCaptionColor(StateIndices index, Color& color) = 0;
		// Get the caption borders
		/* 50h */	virtual void GetCaptionBorders(struct Borders& dst) = 0;
		// Set the caption borders
		/* 54h */	virtual void SetCaptionBorders(struct Borders& borders) = 0;
		// Get the caption offset to be used when the button is selected/depressed
		/* 58h */	virtual void GetCaptionOffset(struct Point& dst) = 0;
		// Set the caption offset to be used when the button is selected/depressed
		/* 5Ch */	virtual void SetCaptionOffset(struct Point& offset) = 0;
		// Set the object to render button appearance
		/* 60h */	virtual void SetButtonDrawable(IButtonDrawable* drawable) = 0;
		// Get the object to render button appearance
		/* 64h */	virtual IButtonDrawable* GetButtonDrawable() = 0;
		// Get the text outline format
		/* 68h */	virtual OutlineFormat& GetTextOutline() = 0;
		// Set the text outline format
		/* 6Ch */	virtual void SetTextOutline(OutlineFormat& format) = 0;
	};

	class WinButton : public Window, public IButton
	{
	private:
		bool field_210;
		/* 214h */	ButtonTypes buttonType;
		/* 218h */	ButtonFlags::Type buttonFlags;
		/* 21Ch */	AlignmentH alignment;
		/* 220h */	unsigned long buttonGroupID;

		char _padding_224[0x24];

		/* 248h */	Math::Rectangle captionBorders;
		/* 258h */	Point captionOffset;
		/* 260h */	Color captionColors[8];

		char _padding_280[0x5E0];

		/* 860h */	OutlineFormat textOutline;

	//private:
	//	// We can't use the default constructor and destructors because we don't know enough about WinButton. Do this in a future
	//	WinButton()
	//		: captionColors{}, textOutline(), field_210(true)
	//	{
	//		textOutline.SetStrength(2);
	//		this->SetFlag((WindowFlags) 8, true);

	//		if ((this->GetFlags() & WindowFlags::Enabled) == WindowFlags::Enabled)
	//		{
	//			field((Window*) this, 0xAC) |= 1;
	//		}

	//		VOID_THISCALL(SelectAddress(0x89DE50, 0), (void*) ((int)((Window*) this) + 0x280));
	//		VOID_THISCALL(SelectAddress(0x899610, 0), (void*)((int)((Window*) this) + 0x7B0));
	//	}

	//	~WinButton()
	//	{

	//	}

	public:
		static inline WinButton* New() {
			// __stdcall because it's cleanup by callee
			return (WinButton*)((IWindow*(__stdcall*)(void*, void*)) SelectAddress(0x967420, 0x9670A0, 0x9670A0))(nullptr, nullptr);
		}

		virtual METHOD_(SelectAddress(0x951FF0, 0x95F8F0, 0x963E30), ILayoutElement, int, AddRef);
		virtual METHOD_(SelectAddress(0x95FE40, 0x95F900, 0x963E40), ILayoutElement, int, Release);
		virtual METHOD(SelectAddress(0x9641E0, 0x963E50, 0x963E50), ILayoutElement, void*, Cast, Args(uint32_t typeID), Args(typeID));

	//	virtual METHOD_(SelectAddress(0x98F5C0, 0), ILayoutElement, int, AddRef);
	//	virtual METHOD_(SelectAddress(0x96B700, 0), ILayoutElement, int, Release);
	//	virtual METHOD(SelectAddress(0x9641E0, 0), ILayoutElement, void*, CastToType, Args(unsigned long typeID), Args(this, typeID));

	//	virtual METHOD_VOID(SelectAddress(0x964B00, 0), ILayoutElement, SetBlockDefinition, Args(void* dst), Args(this, dst));
	//	virtual METHOD_(SelectAddress(0x964860, 0), ILayoutElement, int, GetBlockType);

	//protected:
	//	virtual METHOD(SelectAddress(0x951030, 0), Window, bool, func20h, Args(Event* eventInfo), Args(this, eventInfo));  // warning, might not be an eventInfo!
	//	virtual METHOD(SelectAddress(0x964F30, 0), Window, bool, PaintWindow, Args(void* renderer), Args(this, renderer));

	//	virtual METHOD(SelectAddress(0x9516A0, 0), WinButton, bool, winbuttonFunc28h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x9516A0, 0), WinButton, bool, winbuttonFunc2Ch, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x964580, 0), WinButton, bool, winbuttonFunc30h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x9645E0, 0), WinButton, bool, winbuttonFunc34h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc38h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x964670, 0), WinButton, bool, winbuttonFunc3Ch, Args(int arg_0, int arg_4, int arg_8, int arg_C), Args(this, arg_0, arg_4, arg_8, arg_C));
	//	virtual METHOD(SelectAddress(0x964700, 0), WinButton, bool, winbuttonFunc40h, Args(int arg_0, int arg_4, int arg_8, int arg_C), Args(this, arg_0, arg_4, arg_8, arg_C));
	//	virtual METHOD(SelectAddress(0x9516A0, 0), WinButton, bool, winbuttonFunc44h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x886860, 0), WinButton, bool, winbuttonFunc48h, Args(int arg_0, int arg_4, int arg_8, int arg_C), Args(this, arg_0, arg_4, arg_8, arg_C));
	//	virtual METHOD(SelectAddress(0x964780, 0), WinButton, bool, winbuttonFunc4Ch, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x966F00, 0), WinButton, bool, winbuttonFunc50h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc54h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD_(SelectAddress(0x964850, 0), WinButton, bool, winbuttonFunc58h);
	//	virtual METHOD_VOID_(SelectAddress(0x7E66D0, 0), WinButton, winbuttonFunc5Ch);
	//	virtual METHOD_VOID_(SelectAddress(0x7E66D0, 0), WinButton, winbuttonFunc60h);
	//	virtual METHOD(SelectAddress(0x9516A0, 0), WinButton, bool, winbuttonFunc64h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD_VOID(SelectAddress(0xA36AD0, 0), WinButton, winbuttonFunc68h, Args(int arg_0), Args(this, arg_0));
	//	virtual METHOD_VOID(SelectAddress(0xA36AD0, 0), WinButton, winbuttonFunc6Ch, Args(int arg_0), Args(this, arg_0));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc70h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x9516A0, 0), WinButton, bool, winbuttonFunc74h, Args(int arg_0, int arg_4, int arg_8), Args(this, arg_0, arg_4, arg_8));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc78h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc7Ch, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc80h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD(SelectAddress(0x951320, 0), WinButton, bool, winbuttonFunc84h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD_VOID(SelectAddress(0x9654D0, 0), WinButton, winbuttonFunc88h, Args(int arg_0), Args(this, arg_0));
	//	virtual METHOD_(SelectAddress(0x9642B0, 0), WinButton, int, winbuttonFunc8Ch);
	//	virtual METHOD_VOID_(SelectAddress(0x964B30, 0), WinButton, winbuttonFunc90h);
	//	virtual METHOD_(SelectAddress(0x964440, 0), WinButton, bool, winbuttonFunc94h, Args(int arg_0), Args(this, arg_0));
	//	virtual METHOD_VOID(SelectAddress(0x966F10, 0), WinButton, winbuttonFunc98h, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));
	//	virtual METHOD_VOID_(SelectAddress(0x965690, 0), WinButton, winbuttonFunc9Ch);
	//	virtual METHOD_VOID_(SelectAddress(0x9642F0, 0), WinButton, winbuttonFuncA0h);

	//public:
	//	/* 7Ch */	virtual METHOD_VOID(SelectAddress(0x9648F0, 0), IWindow, SetFlag, Args(WindowFlags flag, bool value), Args(this, flag, value));
	//
	//	/* 94h */	virtual METHOD_(SelectAddress(0x9648C0, 0), IWindow, int, func37);
	//	
	//	/* BCh */	virtual METHOD(SelectAddress(0x964E70, 0), IWindow, int, func47, Args(float arg_0, float arg_4), Args(this, arg_0, arg_4));
	//	
	//	/* 118h */	virtual METHOD_(SelectAddress(0x1065680, 0), IWindow, char*, GetComponentName);
	};

	static_assert(sizeof(WinButton) == 0x888, "sizeof(WinButton) != 888h");
}