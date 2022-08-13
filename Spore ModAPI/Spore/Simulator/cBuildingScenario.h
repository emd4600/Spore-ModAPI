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

#include <Spore\Simulator\cBuilding.h>

#define cBuildingScenarioPtr eastl::intrusive_ptr<Simulator::cBuildingScenario>

namespace Simulator
{
	class cBuildingScenario
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0x70704DB;
		static const uint32_t NOUN_ID = 0x70703B3;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 340h */	int field_340;  // not initialized
		/* 344h */	vector<int> field_344;  // vector of some struct
		/* 358h */	char _padding_358[0x30];  // not initialized
		/* 388h */	Transform field_388;
		/* 3C0h */	int field_3C0;  // not initialized
		/* 3C4h */	int field_3C4;  // not initialized
	};
	ASSERT_SIZE(cBuildingScenario, 0x3C8);
}
