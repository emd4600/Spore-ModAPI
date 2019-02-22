/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\LocalizedString.h>


LocalizedString::LocalizedString()
{
	CALL(GetAddress(0x6B5330, 0x6B4FF0, 0x6B4FF0), void,
		PARAMS(LocalizedString*),
		PARAMS(this));
}
LocalizedString::LocalizedString(uint32_t tableID, uint32_t instanceID, const char16_t* text)
{
	CALL(GetAddress(0x6B5A40, 0x6B5700, 0x6B5700), void,
		PARAMS(LocalizedString*, uint32_t tableID, uint32_t instanceID, const char16_t* text),
		PARAMS(this, tableID, instanceID, text));
}
LocalizedString::~LocalizedString()
{
	CALL(GetAddress(0x6B5510, 0x6B51D0, 0x6B51D0), void,
		PARAMS(LocalizedString*),
		PARAMS(this));
}

auto_METHOD_const_(LocalizedString, const char16_t*, GetText);
auto_METHOD(LocalizedString, bool, SetText, 
	PARAMS(uint32_t tableID, uint32_t instanceID, const char16_t* text),
	PARAMS(tableID, instanceID, text));
