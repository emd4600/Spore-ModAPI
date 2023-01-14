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

#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\OutlineFormat.h>

#define IButtonPtr eastl::intrusive_ptr<UTFWin::IButton>

namespace UTFWin
{
	/// Flags that can be set to an UTFWin::IButton.
	enum ButtonFlags
	{
		/// Button considers itself clicked on mouse/key down rather than mouse/key up.
		kBtnFlagTriggerOnDown = 0x00000001,
		/// Button is fixed width - this means that you can still resize the window area but the actual button width will remain fixed and and it will be positioned within a given window area. Most often used with radio and check box buttons with caption text positioned to the left or right of the button.
		kBtnFlagFixedWidth = 0x00000002,
		/// Button is fixed height - this means that you can still resize the window area but the actual button height will remain fixed and and it will be positioned within a given window area. Most often used with radio and check box buttons with caption text positioned to the left or right of the button.
		kBtnFlagFixedHeight = 0x00000004
	};
	
	/// Flags relted to the state of a button that can be set to an UTFWin::IButton.
	enum ButtonStateFlags
	{
		kBtnStateSelected = 4
	};

	/// This class is a type of UTFWin::IDrawable capable of rendering an UTFWin::IButton.
	class IButtonDrawable : public IDrawable
	{
		static const uint32_t TYPE = 0x2F02135C;
	};

	/// An interface that declares all the functions needed by a button component. 
	class IButton : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0x8ED27E7A;

		static const uint32_t WinButton_ID = 0xEEEFE2C3;

		/// Returns the UTFWin::IWindow representation of this button.
		/* 10h */	virtual IWindow* ToWindow() = 0;

		/* 14h */	virtual void func5(int arg_0) = 0;

		/// Tells the type of this button (standard, toggle, radio).
		/// @returns A value in the enum UTFWin::ButtonTypes.
		/* 18h */	virtual ButtonTypes GetButtonType() = 0;

		/// Sets the type of this button (standard, toggle, radio).
		/// @param buttonType A value in the enum UTFWin::ButtonTypes.
		/* 1Ch */	virtual void SetButtonType(ButtonTypes buttonType) = 0;

		/// Returns the flags that define the state of this button; a combination of the values in 
		/// the UTFWin::ButtonStateFlags enum.
		/* 20h */	virtual int GetButtonStateFlags() = 0;

		/// Sets the flags that define the state of this button; a combination of the values in 
		/// the UTFWin::ButtonStateFlags enum.
		/// @param flags
		/* 24h */	virtual void SetButtonStateFlags(int flags) = 0;

		/// Sets the value of a specific flag that defines the state of this button.
		/// @param flag The flag that must be changed, which belongs to the enum UTFWin::ButtonStateFlags.
		/// @param bValue The new boolean value of the flag.
		/* 28h */	virtual void SetButtonStateFlag(int flag, bool bValue) = 0;

		/// Gets the flags of this button, which define certain properties about it; it's the combination
		/// of values in the UTFWin::ButtonFlags enum.
		/* 2Ch */	virtual int GetButtonFlags() = 0;

		/// Sets the flags of this button, which define certain properties about it; it's the combination
		/// of values in the UTFWin::ButtonFlags enum.
		/// @param flags
		/* 30h */	virtual void SetButtonFlags(int flags) = 0;

		/// Sets the value of a specific flag of this button, which defines certain properties about it;
		/// it's the combination of values in the UTFWin::ButtonFlags enum.
		/// @param flag The flag that must be changed, which belongs to the enum UTFWin::ButtonFlags.
		/// @param bValue The new boolean value of the flag.
		/* 34h */	virtual void SetButtonFlag(int flag, bool bValue) = 0;

		/// Gets the horizontal alignment of the button within the window area whenever a fixed width flag is set. 
		/// This is only the horizontal alignment, the button is always centered vertically. 
		/// The caption text area always complements the alignment of the button.
		/// @returns A value in the UTFWin::AlignmentH enum.
		/* 38h */	virtual AlignmentH GetAlignment() = 0;

		/// Set the horizontal alignment of the button within the window area whenever a fixed width flag is set. 
		/// This is only the horizontal alignment, the button is always centered vertically. 
		/// The caption text area always complements the alignment of the button.
		/// @param alignment A value in the UTFWin::AlignmentH enum.
		/* 3Ch */	virtual void SetAlignment(AlignmentH alignment) = 0;

		/// Allows to group buttons together. Combined with radio button type this
		/// enables radio button group control.
		/// @returns An ID that represents this button group.
		/* 40h */	virtual uint32_t GetButtonGroupID() = 0;

		/// Allows to group buttons together. Combined with radio button type this 
		/// enables radio button group control.
		/// @param groupID An ID that represents the button group.
		/* 44h */	virtual void SetButtonGroupID(uint32_t groupID) = 0;

		/// Gets the caption color for the given state. The return value can be casted to Math::Color
		/// @param index The state whose color must be returned, in the UTFWin::StateIndices enum.
		/* 48h */	virtual uint32_t GetCaptionColor(StateIndices index) = 0;

		/// Sets the caption color for the given state.
		/// @param index The state whose color must be changed, in the UTFWin::StateIndices enum.
		/// @param color The new color.
		/* 4Ch */	virtual void SetCaptionColor(StateIndices index, Color color) = 0;

		/// Gets the caption borders.
		/// @param[out] dst The Math::Rectangle where the borders will be written.
		/* 50h */	virtual void GetCaptionBorders(struct Math::Rectangle& dst) = 0;

		/// Sets the caption borders
		/// @param borders The Math::Rectangle that contains the new borders.
		/* 54h */	virtual void SetCaptionBorders(const struct Math::Rectangle& borders) = 0;

		/// Gets the caption offset to be used when the button is selected/depressed.
		/// @param[out] dst The Math::Point where the offset will be written.
		/* 58h */	virtual void GetCaptionOffset(struct Point& dst) = 0;

		/// Set the caption offset to be used when the button is selected/depressed.
		/// @param offset The Math::Point that contains the new offset.
		/* 5Ch */	virtual void SetCaptionOffset(const struct Point& offset) = 0;

		/// Sets the object to render button appearance, which must be an UTFWin::IButtonDrawable.
		/// @param pDrawable
		/* 60h */	virtual void SetButtonDrawable(IButtonDrawable* pDrawable) = 0;

		/// Gets the object to render button appearance, which must be an UTFWin::IButtonDrawable.
		/* 64h */	virtual IButtonDrawable* GetButtonDrawable() = 0;

		/// Gets the text outline format.
		/* 68h */	virtual OutlineFormat& GetTextOutline() = 0;

		/// Sets the text outline format.
		/// @param format
		/* 6Ch */	virtual void SetTextOutline(OutlineFormat& format) = 0;


		static IButton* Create();
	};

	namespace Addresses(IButton)
	{
		DeclareAddress(Create);
	}
}