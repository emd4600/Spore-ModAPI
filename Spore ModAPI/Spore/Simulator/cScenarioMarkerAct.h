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
#include <Spore\Simulator\cScenarioAsset.h>
#include <Spore\Simulator\cScenarioClassAct.h>
#include <Spore\MathUtils.h>

using namespace Math;

namespace Simulator
{
	class cScenarioMarkerAct
	{
	public:
		/* 00h */	float mfWanderRadius;
		/* 04h */	Vector3 mPatrolPositionDEPRECATED;
		/* 10h */	Vector3 mTeleportPositionDEPRECATED;
		/* 14h */	eastl::vector<Vector3> mPatrolPath;
		/* 30h */	int mPatrolStyle;
	};
	ASSERT_SIZE(cScenarioMarkerAct, 0x34);
}