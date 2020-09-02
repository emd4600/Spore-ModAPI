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

#include <Spore\Input.h>

namespace UTFWin
{
	enum EventFlags
	{
		/// A flag to listen to message types 0x01 -- 0x09 and 0x17 -- 0x1A, that is, 
		/// all the ones related to keyboard and mouse input.
		kEventFlagBasicInput = 0x01,

		/// A flag to listen to the message type kMsgUpdate.
		kEventFlagUpdate = 0x02,

		/// A flag to listen to the message type kMsgPaint.
		kEventFlagPaint = 0x04,

		/// A flag to listen to the message type kMsgWindowChanged and 0x0F.
		kEventWindowChanged = 0x08,

		/// A flag to listen to the message type kMsgStateChanged.
		kEventStateChanged = 0x10,


		/// A flag to listen to the message types kMsgRefresh, kMsgMouseEnter and kMsgMouseLeave.
		kEventRefresh = 0x40,

		/// A flag to listen to the rest of message types, all the ones above 0x1C.
		/// This does not include the kMsgWinProcAdded and kMsgWinProcRemoved, which are ALWAYS listened.
		kEventFlagAdvanced = 0x80,

		/// Some flags to listen to the message type kMsgLayout. This is composed of multiple flags.
		kEventFlagLayout = 0x108,


		/// A flag to listen to the message types kMsgElementAdded and kMsgElementRemoved.
		kEventFlagElement = 0x400,
	};

	enum MessageType
	{
		/// Occurs when a key is pressed while the component has focus.
		kMsgKeyDown = 0x01,
		/// Occurs when a key is released while the component has focus.
		kMsgKeyUp = 0x02,
		/// Occurs when a key is pressed while the component has focus.
		kMsgKeyDown2 = 0x03,
		/// Occurs when a key is released while the component has focus.
		kMsgKeyUp2 = 0x04,
		/// Occurs when a character, space or backspace key is pressed while the control has focus.
		kMsgKeyPress = 0x05,

		/// Occurs when the mouse pointer is over the component and a mouse button is pressed.
		kMsgMouseDown = 0x06,
		/// Occurs when the mouse pointer is over the component and a mouse button is released.
		kMsgMouseUp = 0x07,
		/// Occurs when the mouse pointer is moved over the component.
		kMsgMouseMove = 0x08,
		/// Occurs when the mouse wheel moves while the component has focus.
		kMsgMouseWheel = 0x09,

		/// Occurs when the mouse pointer leaves or enters the component.
		kMsgRefresh = 0x0A,


		/// Occurs every game loop, not all components receive this message.
		kMsgUpdate = 0x0C,
		/// Occurs when the component is redrawn.
		kMsgPaint = 0x0D,
		/// Occurs when something in the window (caption, flags or drawable) changes.
		kMsgWindowChanged = 0x0E,


		/// Occurs every time the window area is changed, when IWindow::Revalidate() is called.
		kMsgLayout = 0x10,
		/// Occurs every time a window or procedure is added.
		kMsgElementAdded = 0x11,
		/// Occurs every time a window is removed.
		kMsgElementRemoved = 0x12,
		/// Occurs when the state of a window changes.
		kMsgStateChanged = 0x13,
		/// Occurs when a window is checked to see if it contains the mouse pointer.
		kMsgCollisionDetect = 0x14,
		/// Occurs when a transformation is applied to a window.
		kMsgTransformed = 0x15,

		/// Occurs when a standard button is clicked.
		kMsgButtonClick = 0x17,
		/// Occurs when a toggle or radio button is selected.
		kMsgButtonSelect = 0x18,

		/// Occurs when the mouse pointer enters the component.
		kMsgMouseEnter = 0x1B,
		/// Occurs when the mouse pointer leaves the component.
		kMsgMouseLeave = 0x1C,

		// This is the limit of common events; the rest require the message flag 0x80

		/// Occurs inmediately after a IWinProc is added to a component. This is called directly on the
		/// IWinProc.
		kMsgWinProcAdded = 0x1000,
		/// Occurs inmediately after a IWinProc is removed from a component. This is called directly on the
		/// IWinProc.
		kMsgWinProcRemoved = 0x1001,

		kMsgComponentActivated = 0x287259F6,

		/// Occurs when the text inside a ITextEdit is changed.
		kMsgTextChanged = 0x9B1552DA
	};

	EventFlags GetEventFlags(MessageType type);

	enum RefreshType
	{
		kRefreshMouse = 1,
		kRefreshKeyboard = 0
	};
}