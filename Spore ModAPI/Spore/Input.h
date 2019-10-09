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

#include <EASTL\bitset.h>
#include <Spore\Internal.h>
#include <Spore\MathUtils.h>

enum KeyModifierFlags
{
	kModifierShiftDown = 1,
	kModifierCtrlDown = 2,
	kModifierAltDown = 4,
};
union KeyModifiers
{
	uint32_t value;
	struct {
		int IsShiftDown : 1;
		int IsCtrlDown : 1;
		int IsAltDown : 1;
	};
};
static_assert(sizeof(KeyModifiers) == 4, "Invalid flags");


enum MouseStateFlags
{
	kMouseShiftDown = 1,
	kMouseCtrlDown = 2,
	kMouseAltDown = 4,
	kMouseLeftButtonDown = 8,
	kMouseMiddleButtonDown = 16,
	kMouseRightButtonDown = 32
};
union MouseState
{
	uint32_t value;
	struct {
		int IsShiftDown : 1;
		int IsCtrlDown : 1;
		int IsAltDown : 1;
		int IsLeftButtonDown : 1;
		int IsMiddleButtonDown : 1;
		int IsRightButtonDown : 1;
	};
};
static_assert(sizeof(MouseState) == 4, "Invalid flags");

enum MouseButton
{
	kMouseButtonNone = 0,
	kMouseButtonLeft = 1000,
	kMouseButtonWheel = 1001,
	kMouseButtonRight = 1002,
	kMouseButton3 = 1003,
	kMouseButton4 = 1004,
	kMouseButton5 = 1005,
	kMouseButton6 = 1006,
	kMouseButton7 = 1007,
};

/// This structure keeps track of all the input in the game, such as 
/// keys pressed/released, the mouse position, etc.
///
/// The recommended usage is having a member of this type in your camera/game mode. On event-like methods,
/// like <tt>OnMouseUp</tt>, <tt>OnKeyDown</tt>, etc you just call the corresponding GameInput method. 
/// Then, in the <tt>Update</tt> method you can access the information like this:
/// \code{.cpp}
/// if (mInput.IsKeyDown(VK_Z)) ...
/// if (mInput.IsMouseDown(kMouseButtonRight)) ...
/// \endcode
struct GameInput
{
	GameInput();

	void OnKeyUp(int vkCode, KeyModifiers modifiers);
	void OnKeyDown(int vkCode, KeyModifiers modifiers);
	void OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
	void OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
	void OnMouseMove(float mouseX, float mouseY, MouseState state);
	void OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState);

	inline bool IsKeyDown(int vkey) const {
		return keys[vkey];
	}

	inline bool IsMouseDown(MouseButton button) const {
		return mouseButtons[static_cast<int>(button) - 1000];
	}

	static bool IsMouseButtonDown(MouseButton button);

	/// The keys that are pressed.
	/* 00h */	int keys[8];
	/// The modifiers of the last key that was pressed.
	/* 20h */	KeyModifiers keyModifiers;
	/// The mouse buttons that are pressed.
	/* 24h */	bool mouseButtons[8];
	/// The last coordinates of the mouse pointer.
	/* 2Ch */	Math::Point mousePosition;
	/// The last mouse button that was pressed, in the enum MouseButton; kMouseButtonNone if no button is pressed.
	/* 34h */	MouseButton mouseButton;
	/// The position of the last mouse click.
	/* 38h */	Math::Point clickPosition;
	/// The mouse state (Ctrl down, Alt down, etc) of the last time a mouse button was pressed; values in the MouseState enum.
	/* 40h */	MouseState mouseState;
	/// The amount of positions the mouse wheel is.
	/* 44h */	int mouseWheel;
};


/////////////////////////////////
//// INTERNAL IMPLEMENTATION ////
/////////////////////////////////

static_assert(sizeof(GameInput) == 0x48, "sizeof(GameInput) == 48h");

inline GameInput::GameInput()
	: keys()
	, keyModifiers()
	, mouseButtons()
	, mousePosition()
	, mouseButton()
	, clickPosition()
	, mouseState()
	, mouseWheel()
{
}

inline void GameInput::OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState state)
{
	mousePosition.x = mouseX;
	mousePosition.y = mouseY;

	mouseButtons[mouseButton - 1000] = true;

	if (this->mouseButton == kMouseButtonNone)
	{
		this->mouseButton = mouseButton;
		mouseState = state;
		clickPosition.x = mouseX;
		clickPosition.y = mouseY;
	}
}

inline void GameInput::OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState state)
{
	mousePosition.x = mouseX;
	mousePosition.y = mouseY;

	mouseButtons[mouseButton - 1000] = false;

	if (this->mouseButton == mouseButton)
	{
		this->mouseButton = kMouseButtonNone;
	}
}

inline void GameInput::OnMouseMove(float mouseX, float mouseY, MouseState state)
{
	mousePosition.x = mouseX;
	mousePosition.y = mouseY;
}

inline void GameInput::OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, MouseState state)
{
	mouseWheel += nWheelDelta;
}

namespace Addresses(GameInput)
{
	DeclareAddress(OnKeyDown, SelectAddress(0x697CA0, 0x697A50, 0x697A50));
	DeclareAddress(OnKeyUp, SelectAddress(0x697CD0, 0x697A80, 0x697A80));

	DeclareAddress(IsMouseButtonDown, SelectAddress(0x8D3650, 0x8D3300, 0x8D3340));
}

inline auto_METHOD_VOID(GameInput, OnKeyDown, Args(int vkCode, KeyModifiers modifiers), Args(vkCode, modifiers));
inline auto_METHOD_VOID(GameInput, OnKeyUp, Args(int vkCode, KeyModifiers modifiers), Args(vkCode, modifiers));

inline auto_STATIC_METHOD(GameInput, bool, IsMouseButtonDown, Args(MouseButton button), Args(button));