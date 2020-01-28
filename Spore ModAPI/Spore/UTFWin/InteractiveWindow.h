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

#include <Spore\UTFWin\Window.h>

#define InteractiveWindowPtr intrusive_ptr<UTFWin::InteractiveWindow>

namespace UTFWin
{
	class InteractiveWindow : public Window
	{
	protected:
		///
		/// An event listener called every time a key is pressed on this window.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 28h */	virtual bool OnKeyDown2(int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is released on this window.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 2Ch */	virtual bool OnKeyUp2(int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is pressed on this window.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 30h */	virtual bool OnKeyDown(int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is released on this window.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 34h */	virtual bool OnKeyUp(int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a character, space or backspace key is released on this window.
		/// @param virtualKey The VK code of the key.
		/// @returns Whether the event was handled or not.
		///
		/* 38h */	virtual bool OnKeyPress(int, int16_t virtualKey);

		///
		/// An event listener called every time a mouse key is pressed on this window.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 3Ch */	virtual bool OnMouseDown(float fMouseX, float fMouseY, int, int state);

		///
		/// An event listener called every time a mouse key is released on this window.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 40h */	virtual bool OnMouseUp(float fMouseX, float fMouseY, int, int state);

		///
		/// An event listener called every time the mouse is moved within this window.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 44h */	virtual bool OnMouseMove(float fMouseX, float fMouseY, int state);

		///
		/// An event listener called every time the mouse wheel is moved within this window.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 48h */	virtual bool OnMouseWheel(float fMouseX, float fMouseY, int state, int nWheelDelta);

		///
		/// An event listener called every time the mouse pointer enters or leaves this window, or the keyboard focus is gained or lost.
		/// @param type The type of refresh that happened, in the RefreshType enum.
		/// @returns Whether the event was handled or not.
		///
		/* 4Ch */	virtual bool OnRefresh(RefreshType type, IWindow*);

		/* 50h */	virtual bool func50h(int, IWindow*);
		/* 54h */	virtual bool func54h(int, IWindow*);

		///
		/// An event listener called every game loop. The return value might not be relevant.
		/// @returns Whether the event was handled or not.
		///
		/* 58h */	virtual void OnUpdate();

		///
		/// An event listener called every time a window or procedure is added to the component.
		/// @returns Whether the event was handled or not.
		///
		/* 5Ch */	virtual void OnElementAdd();

		///
		/// An event listener called every time a window is removed from the component.
		/// @returns Whether the event was handled or not.
		///
		/* 60h */	virtual void OnElementRemove();

		///
		/// An event listener called to check if the window contains the mouse pointer.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param pbResult The bool* where the result of the detection must go. Set it to true if it collisions with this window.
		/// @returns Whether the event was handled or not.
		///
		/* 64h */	virtual bool OnCollisionDetect(float fMouseX, float fMouseY, bool* pbResult);

		///
		/// An event listener called every time the window layout is recalculated.
		/// @param pArea
		///
		/* 68h */	virtual void OnLayout(Math::Rectangle* pArea);

		///
		/// An event listener called every time a transformation is applied on the window.
		/// @param pTransformation
		///
		/* 6Ch */	virtual void OnTransform(Math::Matrix4* pTransformation);


		///
		/// An event listener called when the window is clicked, if it's a standard button.
		/// @param pSourceWindow The button IWindow that was clicked.
		/// @param commandID The command ID of the button.
		/// @returns Whether the event was handled or not.
		///
		/* 70h */	virtual bool OnButtonClick(IWindow* pSourceWindow, uint32_t commandID);

		///
		/// An event listener called when the window is selected, if it's a toggle or radio button.
		/// @param pSourceWindow The button IWindow that was clicked.
		/// @param commandID The command ID of the button.
		/// @param msg
		/// @returns Whether the event was handled or not.
		///
		/* 74h */	virtual bool OnButtonSelect(IWindow* pSourceWindow, uint32_t commandID, Message& msg);


		/* 78h */	virtual bool func78h(int, int);
		/* 7Ch */	virtual bool func7Ch(int, int);


		///
		/// An event listener called every time the pointer enters the component.
		/// @param pLostFocusWindow The window that gained focus.
		/// @returns Whether the event was handled or not.
		///
		/* 80h */	virtual bool OnMouseEnter(int, IWindow* pFocusWindow);

		///
		/// An event listener called every time the pointer leaves the component.
		/// @param pLostFocusWindow The window that lost focus.
		/// @returns Whether the event was handled or not.
		///
		/* 84h */	virtual bool OnMouseLeave(int, IWindow* pLostFocusWindow);
	};
}