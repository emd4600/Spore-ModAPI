#ifndef MODAPI_DLL_EXPORT
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
	CALL(GetAddress(LocalizedString, ctor_0), void,
		Args(LocalizedString*),
		Args(this));
}
LocalizedString::LocalizedString(uint32_t tableID, uint32_t instanceID, const char16_t* text)
{
	CALL(GetAddress(LocalizedString, ctor_1), void,
		Args(LocalizedString*, uint32_t tableID, uint32_t instanceID, const char16_t* text),
		Args(this, tableID, instanceID, text));
}
LocalizedString::~LocalizedString()
{
	CALL(GetAddress(LocalizedString, dtor), void,
		Args(LocalizedString*),
		Args(this));
}

auto_METHOD_const_(LocalizedString, const char16_t*, GetText);
auto_METHOD(LocalizedString, bool, SetText, 
	Args(uint32_t tableID, uint32_t instanceID, const char16_t* text),
	Args(tableID, instanceID, text));

#endif
