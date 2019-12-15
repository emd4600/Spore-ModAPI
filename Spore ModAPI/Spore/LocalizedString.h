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

#include <Spore\Internal.h>
#include <stdint.h>
#include <EASTL\string.h>

using namespace eastl;

///
/// This class is used to store a string16 that is localized; that is, it depends on the current language of the game.
/// LocalizedStrings store a tableID and instanceID which are used to get the appropiate text depending on the current language.
/// The texts are searched inside the locale~ folder. The tableID is the name of the file, and the instanceID is the ID of that
/// text inside that file.
///
class LocalizedString
{
public:
	LocalizedString();
	LocalizedString(uint32_t tableID, uint32_t instanceID, const char16_t* pText = nullptr);
	~LocalizedString();

	///
	/// Gets the text that corresponds to this object according to the current locale.
	///
	const char16_t* GetText() const;

	///
	/// Sets the tableID and instanceID that are used to get the text depending on the current language.
	/// @param tableID The ID of the .locale file that contains the text.
	/// @param instanceID The ID that identifies this particular string inside the locale table.
	/// @param pPlaceholderText [Optional] A placeholder text, ignored.
	///
	bool SetText(uint32_t tableID, uint32_t instanceID, const char16_t* pPlaceholderText = nullptr);

protected:
	int field_0;
	string16* field_4;
	char16_t* pText;
	int field_C;
	bool field_10;
	bool field_11;  // if true, returns field_4
};

/////////////////////////////////
//// INTERNAL IMPLEMENTATION ////
/////////////////////////////////

static_assert(sizeof(LocalizedString) == 0x14, "sizeof(LocalizedString) != 14h");

namespace Addresses(LocalizedString)
{
	DeclareAddress(GetText);
	DeclareAddress(SetText);

	DeclareAddress(ctor_0);
	DeclareAddress(ctor_1);
	DeclareAddress(dtor);
}