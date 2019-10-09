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

#include <Spore\LocalizedString.h>
#include <EASTL\string.h>

using namespace eastl;

namespace Simulator
{
	class cScenarioString
	{
	public:
		/* 00h */	LocalizedString mString;
		/* 14h */	string16 mNonLocalizedString;
		/* 24h */	uint32_t mLocalizedStringTableID;
		/* 28h */	uint32_t mLocalizedStringInstanceID;
		/* 2Ch */	string16 mComments;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cScenarioString) == 0x3C, "sizeof(cScenarioString) != 0x3C");
}