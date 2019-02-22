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

enum KeyModifiers
{
	kModifierShiftDown = 1,
	kModifierCtrlDown = 2,
	kModifierAltDown = 4,
};

enum MouseFlags
{
	kMouseShiftDown = 1,
	kMouseCtrlDown = 2,
	kMouseAltDown = 4,
	kMouseLeftButtonDown = 8,
	kMouseMiddleButtonDown = 16,
	kMouseRightButtonDown = 32
};

enum MouseButtons
{
	kMouseButtonLeft = 1000,
	kMouseButtonWheel = 1001,
	kMouseButtonRight = 1002
};

/// This structure keeps track of all the input in the game, such as 
/// keys pressed/released, the mouse position, etc.
struct GameInput
{
	GameInput();

	void OnKeyUp(int vkCode, int modifiers);
	void OnKeyDown(int vkCode, int modifiers);
	void OnMouseDown(int mouseButton, float mouseX, float mouseY, int flags);
	void OnMouseUp(int mouseButton, float mouseX, float mouseY, int flags);
	void OnMouseMove(float mouseX, float mouseY, int state);
	void OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state);

	static bool IsMouseButtonDown(MouseButtons button);

	/// The keys that are pressed.
	/* 00h */	int mKeys[8];
	/// The modifiers of the last key that was pressed.
	/* 20h */	int mKeyModifiers;
	/// The mouse buttons that are pressed.
	/* 24h */	bool mMouseButtons[8];
	/// The last coordinates of the mouse pointer.
	/* 2Ch */	Math::Point mMousePosition;
	/// The last mouse button that was pressed, in the enum MouseButtons or 0 if no button is pressed.
	/* 34h */	int mMouseButton;
	/// The position of the last mouse click.
	/* 38h */	Math::Point mClickPosition;
	/// The mouse flags (Ctrl down, Alt down, etc) of the last time a mouse button was pressed.
	/* 40h */	int mMouseFlags;
	/// The amount of positions the mouse wheel is.
	/* 44h */	int mnMouseWheel;
};


/////////////////////////////////
//// INTERNAL IMPLEMENTATION ////
/////////////////////////////////

static_assert(sizeof(GameInput) == 0x48, "sizeof(GameInput) == 48h");

inline GameInput::GameInput()
	: mKeys()
	, mKeyModifiers()
	, mMouseButtons()
	, mMousePosition()
	, mMouseButton()
	, mClickPosition()
	, mMouseFlags()
	, mnMouseWheel()
{
}

inline void GameInput::OnMouseDown(int mouseButton, float mouseX, float mouseY, int flags)
{
	mMousePosition.x = mouseX;
	mMousePosition.y = mouseY;

	mMouseButtons[mouseButton - 1000] = true;

	if (mMouseButton == 0)
	{
		mMouseButton = mouseButton;
		mMouseFlags = flags;
		mClickPosition.x = mouseX;
		mClickPosition.y = mouseY;
	}
}

inline void GameInput::OnMouseUp(int mouseButton, float mouseX, float mouseY, int flags)
{
	mMousePosition.x = mouseX;
	mMousePosition.y = mouseY;

	mMouseButtons[mouseButton - 1000] = false;

	if (mMouseButton == mouseButton)
	{
		mMouseButton = 0;
	}
}

inline void GameInput::OnMouseMove(float mouseX, float mouseY, int state)
{
	mMousePosition.x = mouseX;
	mMousePosition.y = mouseY;
}

inline void GameInput::OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state)
{
	mnMouseWheel += nWheelDelta;
}

namespace InternalAddressList(GameInput)
{
	DefineAddress(OnKeyDown, GetAddress(0x697CA0, 0x697A50, 0x697A50));
	DefineAddress(OnKeyUp, GetAddress(0x697CD0, 0x697A80, 0x697A80));

	DefineAddress(IsMouseButtonDown, GetAddress(0x8D3650, 0x8D3300, 0x8D3340));
}

inline auto_METHOD_VOID(GameInput, OnKeyDown, PARAMS(int vkCode, int modifiers), PARAMS(vkCode, modifiers));
inline auto_METHOD_VOID(GameInput, OnKeyUp, PARAMS(int vkCode, int modifiers), PARAMS(vkCode, modifiers));

inline auto_STATIC_METHOD(GameInput, bool, IsMouseButtonDown, PARAMS(MouseButtons button), PARAMS(button));