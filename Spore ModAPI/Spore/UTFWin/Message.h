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

#include <Spore\UTFWin\UIRenderer.h>
#include <Spore\UTFWin\Constants.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\MathUtils.h>

#include <EASTL\string.h>

namespace UTFWin
{

	///
	/// This struct is used in kMsgTextChanged messages to represent the text in a ITextEdit.
	///
	struct TextChange
	{
		char16_t* string;
		size_t length;

		inline eastl::string16 ToString() const
		{
			return eastl::string16(string, length);
		}
	};

	class Message
	{
	public:
		/* 00h */	IWindow* source;
		/* 04h */	int field_04;  // ??
		/* 08h */	int eventType;  // ??

		///
		/// Tells whether the message is of the given type, in the enum MessageType.
		/// @param type The expected message type.
		///
		inline bool IsType(int type) const
		{
			return eventType == type;
		}

		///
		/// Tells whether this window is the source window that
		/// generated the message.
		/// @param pWindow The expected source window.
		///
		inline bool IsSource(const IWindow* pWindow) const
		{
			return source == pWindow;
		}

		///
		/// Tells whether this control ID is the one used by the source window that
		/// generated the message.
		/// @param controlID The expected control ID of the source.
		///
		inline bool IsSource(uint32_t controlID) const
		{
			return source->GetControlID() == controlID;
		}

		union
		{
			///
			/// The event arguments for the message types: UTFWin::kMsgKeyDown | UTFWin::kMsgKeyUp | UTFWin::kMsgKeyDown2
			/// | UTFWin::kMsgKeyUp2.
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/// The virtual key that was pressed/released. Example usage: vkey == VK_A (means the user pressed/released A).
				/* 10h */	int vkey;
				/// The modifiers that were applying in the key event, from the KeyModifiers enum.
				/* 14h */	int modifiers;
			} Key;

			///
			/// The event arguments for the message type: UTFWin::kMsgKeyPress
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/// The virtual key that was pressed/released. Example usage: vkey == VK_A (means the user pressed/released A).
				/* 10h */	int16_t vkey;
			} KeyPress;

			///
			/// The event arguments for the message types: UTFWin::kMsgMouseDown | UTFWin::kMsgMouseUp | UTFWin::kMsgMouseMove
			/// | UTFWin::kMsgMouseWheel.
			/// Note that the mnWheelDelta member should only be considered on UTFWin::kMsgMouseWheel messages.
			///
			struct
			{
				/// The X coordinate of the mouse, relative to the window that raised the event.
				/* 0Ch */	float mouseX;
				/// The Y coordinate of the mouse, relative to the window that raised the event.
				/* 10h */	float mouseY;
				/// A combination of values from the MouseStateFlags enum.
				/* 14h */	int mouseState;
				/// How much the mouse wheel changed, it is usually a multiple of 120.
				/* 18h */	int wheelDelta;

				inline bool IsLeftButton() const {
					return (mouseState & kMouseLeftButtonDown) == kMouseLeftButtonDown;
				}
				inline bool IsMiddleButton() const {
					return (mouseState & kMouseMiddleButtonDown) == kMouseMiddleButtonDown;
				}
				inline bool IsRightButton() const {
					return (mouseState & kMouseRightButtonDown) == kMouseRightButtonDown;
				}
			} Mouse;

			///
			/// The event arguments for the message types: UTFWin::kMsgMouseLeave | UTFWin::kMsgMouseEnter
			/// The 'window' member is the window that lost focus for UTFWin::kMsgMouseLeave, and
			/// the window that is getting focus for UTFWin::kMsgMouseEnter.
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/// For kMsgMouseLeave, the windows that lost focus; for kMsgMouseEnter, the window that gained focus.
				/* 18h */	IWindow* window;
			} MouseEnter, MouseLeave;

			///
			/// The event arguments for the message type: UTFWin::kMsgPaint
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/// The object that can be used to paint to the UI.
				/* 18h */	UIRenderer* renderer;
			} Paint;

			///
			/// The event arguments for the message type: UTFWin::kMsgRefresh
			///
			struct
			{
				/* 0Ch */	RefreshType refreshType;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/* 18h */	IWindow* window;
			} Refresh;

			///
			/// The event arguments for the message type: UTFWin::kMsgLayout
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/// Pointer to the new layout area.
				/* 18h */	Math::Rectangle* area;
			} Layout;

			///
			/// The event arguments for the message type: UTFWin::kMsgStateChanged
			///
			struct
			{
				/// The previous state flags of the window.
				/* 0Ch */	int oldState;
				/// The new state flags of the window.
				/* 10h */	int newState;
			} StateChanged;

			///
			/// The event arguments for the message type: UTFWin::kMsgCollisionDetect
			/// This message has a member called mpbIsColliding, which is a pointer to the result.
			/// For example, if you decide that the mouse position is colliding the window, use *mpbIsColliding = true;
			///
			struct
			{				
				/// The X coordinate where the collision check must be done.
				/* 0Ch */	float x;
				/// The Y coordinate where the collision check must be done.
				/* 10h */	float y;
				/// A combination of values from the UTFWin::MouseState enum.
				/* 14h */	int mouseState;
				/// This bool* holds the result, whether a collision was detected or not.
				/* 18h */	bool* isColliding;
			} CollisionDetect;

			///
			/// The event arguments for the message type: UTFWin::kMsgTransformed
			///
			struct
			{
				/* 0Ch */	int field_0C;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/// The transformation matrix applied.
				/* 18h */	Math::Matrix4* transformation;
			} Transformed;

			///
			/// The event arguments for the message type: UTFWin::kMsgButtonClick
			///
			struct
			{
				/// The command ID of the clicked button.
				/* 0Ch */	uint32_t commandID;
			} ButtonClick;

			///
			/// The event arguments for the message type: UTFWin::kMsgButtonSelect
			///
			struct
			{
				/// The command ID of the clicked button.
				/* 0Ch */	uint32_t commandID;
				/* 10h */	int field_10;
				/// Whether the button is now selected.
				/* 14h */	bool isSelected;
			} ButtonSelect;

			///
			/// The event arguments for the message type: UTFWin::kMsgTextChanged
			///
			struct
			{

				/* 0Ch */	int field_0C;
				/* 10h */	int field_10;
				/* 14h */	int field_14;
				/// The change of the text.
				/* 18h */	TextChange* change;
			} TextChanged;
		};
	};

	static_assert(sizeof(Message) == 0x1C, "sizeof(Message) == 0x1C)");  // 7 32bit ints
}
