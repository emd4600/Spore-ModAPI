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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\Message.h>
#include <Spore\UTFWin\Serialization.h>

namespace UTFWin
{
	class InteractiveWinProc : public IWinProc, public ILayoutElement
	{
	public:

		InteractiveWinProc();

		virtual int AddRef() override;
		virtual int Release() override;

		virtual void* Cast(uint32_t typeID) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		///
		/// An event listener called every time a key is pressed on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 1Ch */	virtual bool OnKeyDown2(IWindow* pWindow, int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is released on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 20h */	virtual bool OnKeyUp2(IWindow* pWindow, int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is pressed on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 24h */	virtual bool OnKeyDown(IWindow* pWindow, int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a key is released on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 28h */	virtual bool OnKeyUp(IWindow* pWindow, int, int virtualKey, int modifiers);

		///
		/// An event listener called every time a character, space or backspace key is released on a window this procedure is
		/// listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param virtualKey The VK code of the key.
		/// @returns Whether the event was handled or not.
		///
		/* 2Ch */	virtual bool OnKeyPress(IWindow* pWindow, int, int16_t virtualKey);

		///
		/// An event listener called every time a mouse key is pressed on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 30h */	virtual bool OnMouseDown(IWindow* pWindow, float fMouseX, float fMouseY, int, int state);

		///
		/// An event listener called every time a mouse key is released on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 34h */	virtual bool OnMouseUp(IWindow* pWindow, float fMouseX, float fMouseY, int, int state);

		///
		/// An event listener called every time the mouse is moved within a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 38h */	virtual bool OnMouseMove(IWindow* pWindow, float fMouseX, float fMouseY, int state);

		///
		/// An event listener called every time the mouse wheel is moved within a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 3Ch */	virtual bool OnMouseWheel(IWindow* pWindow, float fMouseX, float fMouseY, int state, int nWheelDelta);

		///
		/// An event listener called every time the mouse pointer enters or leaves a window this procedure is listening,
		/// or the keyboard focus is gained or lost.
		/// @param pWindow The IWindow where this event was received.
		/// @param type The type of refresh that happened, in the RefreshType enum.
		/// @returns Whether the event was handled or not.
		///
		/* 40h */	virtual bool OnRefresh(IWindow* pWindow, RefreshType type, IWindow*);

		/* 44h */	virtual bool func44h(IWindow* pWindow, int arg_4, int arg_8);

		///
		/// An event listener called every game loop if the window this procedure is listening is registered to
		/// receive update events.
		/// @param pWindow The IWindow where this event was received.
		/// @returns Whether the event was handled or not.
		///
		/* 48h */	virtual bool OnUpdate(IWindow* pWindow);

		///
		/// An event listener called to check if the window contains the mouse pointer.
		/// @param pWindow The IWindow where this event was received.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param pbResult The bool* where the result of the detection must go. Set it to true if it collisions with this window.
		/// @returns Whether the event was handled or not.
		///
		/* 4Ch */	virtual bool OnCollisionDetect(IWindow* pWindow, float fMouseX, float fMouseY, bool* pbResult);

		///
		/// An event listener called every time a window or procedure is added to a component this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @returns Whether the event was handled or not.
		///
		/* 50h */	virtual bool OnElementAdd(IWindow* pWindow);

		///
		/// An event listener called every time a window is removed from a component this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @returns Whether the event was handled or not.
		///
		/* 54h */	virtual bool OnElementRemove(IWindow* pWindow);

		///
		/// An event listener called every time the window layout is recalculated on a window this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param parentBounds
		///
		/* 58h */	virtual void OnLayout(IWindow* window, Math::Rectangle& parentBounds);

		///
		/// An event listener called every time a transformation is applied on a window.
		/// @param pWindow The IWindow where this event was received.
		/// @param pTransformation
		///
		/* 5Ch */	virtual void OnTransform(IWindow* pWindow, Math::Matrix4* pTransformation);

		///
		/// An event listener called when this procedure is added into an IWindow.
		/// @param pWindow The IWindow where this event was received.
		///
		/* 60h */	virtual void OnWinProcAdd(IWindow* pWindow);

		///
		/// An event listener called when this procedure is removed from an IWindow.
		/// @param pWindow The IWindow where this event was received.
		///
		/* 64h */	virtual void OnWinProcRemove(IWindow* pWindow);

		///
		/// An event listener called when the window is clicked, if it's a standard button.
		/// @param pWindow The IWindow where this event was received.
		/// @param pSourceWindow The button IWindow that was clicked.
		/// @param commandID The command ID of the button.
		/// @returns Whether the event was handled or not.
		///
		/* 68h */	virtual bool OnButtonClick(IWindow* pWindow, IWindow* pSourceWindow, uint32_t commandID);

		///
		/// An event listener called when the window is selected, if it's a toggle or radio button.
		/// @param pWindow The IWindow where this event was received.
		/// @param pSourceWindow The button IWindow that was clicked.
		/// @param commandID The command ID of the button.
		/// @param message
		/// @returns Whether the event was handled or not.
		///
		/* 6Ch */	virtual bool OnButtonSelect(IWindow* pWindow, IWindow* pSourceWindow, uint32_t commandID, Message& message);

		/* 70h */	virtual bool func70h(IWindow* pWindow, int arg_4, int arg_8);
		/* 74h */	virtual bool func74h(IWindow* pWindow, int arg_4, int arg_8);

		///
		/// An event listener called every time the pointer enters a component this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param pLostFocusWindow The window that gained focus.
		/// @returns Whether the event was handled or not.
		///
		/* 78h */	virtual bool OnMouseEnter(IWindow* pWindow, int, IWindow* pFocusWindow);

		///
		/// An event listener called every time the pointer leaves a component this procedure is listening.
		/// @param pWindow The IWindow where this event was received.
		/// @param pLostFocusWindow The window that lost focus.
		/// @returns Whether the event was handled or not.
		///
		/* 7Ch */	virtual bool OnMouseLeave(IWindow* pWindow, int, IWindow* pLostFocusWindow);


	protected:
		int mnRefCount;

	private:
		static const ComponentSerialization SerializationData;
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(InteractiveWinProc)
	{
		DeclareAddress(HandleUIMessage, SelectAddress(0x951370, 0x950E50, 0x950E50));
	}
}