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
#include <Spore\Simulator\cBehaviorEntry.h>
#include <Spore\Simulator\cScenarioDialog.h>
#include <EASTL\vector.h>
#include <EASTL\fixed_vector.h>

namespace Simulator
{
	class cScenarioClassAct
	{
	public:
		/* 00h */	bool mbVisible;
		/* 01h */	bool mbInvulnerable;
		/* 02h */	bool mbIsDead;
		/* 04h */	eastl::fixed_vector<cScenarioDialog, 5> mDialogsChatter;
		/* 170h */	eastl::fixed_vector<cScenarioDialog, 5> mDialogsInspect;
		/* 2DCh */	eastl::fixed_vector<cScenarioDialog, 5> field_2DC;
		/* 448h */	cScenarioString mDescriptionDEPRECATED;
		/* 484h */	float mfAwareness;
		/* 488h */	float mfHealth_DEPRECATED;
		/* 48Ch */	float mfHealthMultiplier;
		/* 490h */	float mfSpeedMultiplier;
		/* 494h */	float mfDamageMultiplier;
		/// Property `powerupRadius`
		/* 498h */	float mfRadiusTuning;
		/// Property `powerupAmount`
		/* 49Ch */	float mfDamageTuning;
		/// Property `powerupAmount`
		/* 4A0h */	float mfJumpTuning;
		/// -1: class is not visible in this act; 0: no spawner
		/* 4A4h */	int mSpawnDelay;
		/* 4A8h */	int mTeamBehavior;
		/* 4ACh */	int mStanceBehavior;
		/* 4B0h */	int mPickupBehavior;
		/* 4B4h */	int mGiveBehavior;
		/* 4B8h */	int mMovementBehavior;
		/* 4BCh */	int mPickupTargetClassIndex;
		/* 4C0h */	int mGiveTargetClassIndex;
		/* 4C4h */	int mTrackTargetClassIndex;
		/* 4C8h */	bool mbCustomBehavior;
		/* 4CCh */	eastl::vector<cBehaviorEntry> mCustomBehaviorEntries;
	};
	ASSERT_SIZE(cScenarioClassAct, 0x4E0);
}