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

#include <Spore\Object.h>

namespace Simulator
{
	//PLACEHOLDER also used by other classes
	struct UnknownBehaviorContainer
	{
		char field_0[0x2C];
	};

	// used by the cGameBehaviorManager
	class cBehaviorAgent
	{
	public:
		static const uint32_t TYPE = 0x11C0BA3;

		//TODO more
		virtual ~cBehaviorAgent();

	public:
		/* 04h */	bool field_4;
		/* 08h */	UnknownBehaviorContainer field_8;
		/* 34h */	UnknownBehaviorContainer field_34;
		/* 60h */	int field_60;  // not initialized
		/* 64h */	bool field_64;
		/* 65h */	bool field_65;  // true
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cBehaviorAgent) == 0x68, "sizeof(cBehaviorAgent) != 68h");
}