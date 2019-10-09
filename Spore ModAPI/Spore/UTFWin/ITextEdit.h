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

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\UTFWinObject.h>

#include <EASTL\string.h>

namespace UTFWin
{
	enum class TextColors
	{
		Text = 0,
		Background = 1,
		DisabledText = 2,
		DisabledBackground = 3,
		SelectedText = 4,
		SelectedBackground = 5,
		Caret = 6,
		CaretBackground = 7
	};


	enum class TextEditWarpMode : uint32_t
	{
		/// All text in one line
		SingleLine = 0,
		/// Wrap on hard linebreaks only
		MultiLine = 1,
		/// Multiline with soft wordwrap
		MultiLineWordWrap = 2
	};

	enum class ScrollbarEnDis : uint32_t
	{
		Never = 0,
		AsNeeded = 1,
		Always = 2
	};

	class ITextEdit : public UTFWinObject
	{
	public:
		enum
		{
			/// If set to true, the text cannot be changed
			kFlagReadOnly = 0x0001,
			/// If set to true, allows return to insert a new line
			kFlagAcceptReturn = 0x0002,
			/// If set to true, allow using the insert key to toggle insert vs. overwrite mode
			kFlagAcceptInsertKey = 0x0004,
			/// If set to true, causes newly entered characters to overwrite existing characters
			kFlagOverwrite = 0x0008,
			/// If set to true, the selection will be hidden if we don't have focus
			kFlagHideInactiveSelection = 0x0010,
			/// If set to true, the flashing caret is hidden
			kFlagHideCaret = 0x0020,
			/// If set to true, allows copy and paste to and from clipboard
			kFlagEnableClipboard = 0x0040,
			/// If set to true, the displayed text is obscured, and won't copy to clipboard
			kFlagPasswordMode = 0x0080,
		};

		///
		/// Returns the IWindow that represents this text edit.
		///
		/* 10h */	virtual IWindow* ToWindow() = 0;
		/* 14h */	virtual uint32_t GetTextStyleID() const = 0;
		/* 18h */	virtual void SetTextStyleID(uint32_t styleID) = 0;

		///
		/// Gets the component color for the given text type.
		/// @param index The type of text affected by the color, in the TextColors enum.
		///
		/* 1Ch */	virtual Color GetColor(TextColors index) const = 0;

		///
		/// Specifies the component colors for the given text mode.
		/// @param index The type of text affected by this color, in the TextColors enum.
		/// @param color The new Color.
		///
		/* 20h */	virtual void SetColor(TextColors index, Color color) = 0;
		/* 24h */	virtual const Math::Rectangle& GetBorderWidth() const = 0;
		/* 28h */	virtual void SetBorderWidth(const Math::Rectangle& widths) = 0;

		///
		/// Get the caret blink period.
		///
		/* 2Ch */	virtual float GetCaretPeriod() const = 0;

		///
		/// Set the caret blink period.
		/// @param period
		///
		/* 30h */	virtual void SetCaretPeriod(float period) = 0;
		/* 34h */	virtual float GetField620h() const = 0;
		/* 38h */	virtual void SetField620h(float value) = 0;
		/* 3Ch */	virtual TextEditWarpMode GetWrapMode() const = 0;
		/* 40h */	virtual void SetWrapMode(TextEditWarpMode wrapMode) = 0;
		/* 44h */	virtual void SetTextEditFlag(int flag, bool value) = 0;
		/* 48h */	virtual bool GetTextEditFlag(int flag) const = 0;
		/* 4Ch */	virtual int GetTextEditFlags() const = 0;
		/* 50h */	virtual int GetTextLength() const = 0;
		/* 54h */	virtual const char16_t* GetText() const = 0;
		/* 58h */	virtual int GetTextFragment(string16& dst, int startIndex, int length) const = 0;
		/* 5Ch */	virtual int GetTextFragment(char16_t* dst, int startIndex, int length) const = 0;
		/* 60h */	virtual int SetText(const char16_t* pText, int arg_4) = 0;
		/* 64h */	virtual int GetMaxTextLength() const = 0;
		/* 68h */	virtual void SetMaxTextLength(int maxLength) = 0;
		/* 6Ch */	virtual bool InsertText(char16_t* text, int textLength, bool arg_8) = 0;
		/* 70h */	virtual bool InsertText(char16_t* text, bool arg_4) = 0;
		/* 74h */	virtual bool ReplaceSelectedText(char16_t* text, bool arg_4) = 0;
		/* 78h */	virtual bool TextChanged(int startIndex, int endIndex, char16_t* text, int textLength, bool arg_10) = 0;
		/* 7Ch */	virtual bool TextChanged(bool arg_10) = 0;
		/* 80h */	virtual void func80h() = 0;
		/* 84h */	virtual void func84h() = 0;
		/* 88h */	virtual int GetCursorIndex() const = 0;
		/* 8Ch */	virtual void SetCursorIndex(int cursorIndex, bool keepAnchor) = 0;
		/* 90h */	virtual int GetAnchorIndex() const = 0;
		/* 94h */	virtual void SetCursorAndAnchor(int cursorIndex, int anchorIndex) = 0;
		/* 98h */	virtual bool GetCursorAndAnchor(int& cursorIndex, int& anchorIndex) = 0;
		/* 9Ch */	virtual bool func9Ch(int, int, int) = 0;

		static const uint32_t TYPE = 0xCF428691;

		static ITextEdit* Create();
	};

	namespace Addresses(ITextEdit)
	{
		DeclareAddress(Create, SelectAddress(0x98CDC0, 0x98CAA0, 0x98CAA0));
	}
}