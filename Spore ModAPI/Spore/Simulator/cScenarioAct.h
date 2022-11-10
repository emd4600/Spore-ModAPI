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

#include <Spore\Simulator\cScenarioString.h>
#include <Spore\Simulator\cScenarioGoal.h>

namespace Simulator
{
	class cScenarioAct
	{
	public:
		/* 00h */	cScenarioString mName;
		/* 3Ch */	cScenarioString mDescription;
		/* 78h */	int mTimeLimitSecs;
		/* 7Ch */	bool mbTimeVisible;
		/* 80h */	uint32_t mActMusicID;
		/* 84h */	eastl::fixed_vector<cScenarioGoal, 3> mGoals;
	};
	ASSERT_SIZE(cScenarioAct, 0x534);
}