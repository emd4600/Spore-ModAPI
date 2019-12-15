/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
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
#include "stdafx.h"
#include "AddressCheat.h"


AddressCheat::AddressCheat()
{
}


AddressCheat::~AddressCheat()
{
}

// The initialization function that adds the cheat to the game.
void AddressCheat::AddCheat(uintptr_t address, const char* pName)
{
	AddressCheat* pCheat = new AddressCheat();

	// Replace the vtable with the address
	*((long*)pCheat) = address;

	CheatManager.AddCheat(pName, pCheat);
}


void AddressCheat::ParseLine(const ArgScript::Line& line)
{
}

const char* AddressCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "";
}
