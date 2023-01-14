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
#include <Spore\Simulator\cScenarioDialog.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <EASTL\fixed_vector.h>

namespace Simulator
{
	class cScenarioGoal
	{
	public:
		/* 00h */	ScenarioGoalType mType;
		/* 04h */	int mTargetClassIndex;
		/* 08h */	int mTargetClass2Index;
		/* 0Ch */	int mRequiredCount;
		/* 10h */	bool mbVisibility;
		/* 14h */	int mFlags;
		/* 18h */	eastl::fixed_vector<cScenarioDialog, 5> mDialogs;
		/* 184h */	int field_184;  // ?
	};
	ASSERT_SIZE(cScenarioGoal, 0x188);
}