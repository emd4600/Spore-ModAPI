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

#include <Spore\MathUtils.h>
#include <Spore\Input.h>
#include <Spore\LocalizedString.h>
#include <EASTL\string.h>

#include <Spore\UTFWin\UILayout.h>

namespace Simulator
{
	namespace Cell
	{
		using namespace eastl;

		class CellUI
		{
		public:

			/* 00h */	GameInput mGameInput;
			/* 48h */	char field_48[0x48];  // not initialized
			/* 90h */	UILayoutPtr field_90;
			/* 94h */	int field_94;
			/* 98h */	int field_98;
			/* 9Ch */	char field_9C[0x874];  // not initialized

			/* 910h */	string16 field_910;
			/* 920h */	LocalizedString field_920;
			/* 934h */	bool field_934[0x10];  // not initialized
		};


		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		static_assert(sizeof(CellUI) == 0x944, "sizeof(CellUI) == 944h");
	}
}