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

#include <Spore\Simulator\cScenarioMarkerAct.h>
#include <Spore\Simulator\cScenarioClassAct.h>
#include <Spore\MathUtils.h>
#include <EASTL\fixed_vector.h>

using namespace Math;

namespace Simulator
{
	class cScenarioMarker
	{
	public:
		/* 00h */	int mClassIndex;  // -1
		/* 04h */	Vector3 mPosition;
		/* 10h */	Quaternion mOrientation;  // 0, 0, 0, 1.0
		/* 20h */	float mfScale;  // 0.5
		/* 24h */	float mfRelativeScaleToDefault;  // 1.0
		/* 28h */	fixed_vector<cScenarioMarkerAct, 8> mActs;
		/* 1E0h */	float mfPitch;
		/* 1E4h */	float mfGain;
		/* 1E8h */	Vector3 mTeleportPosition;
		/* 1F4h */	Quaternion mTeleportOrientation;
		/* 204h */	float mfTeleportScale;
		/* 208h */	bool field_208;
		/* 209h */	bool field_209;
		/* 20Ch */	vector<float> mOldDistances;
		/* 220h */	float mfElevation;
		/* 224h */	int mFlags;
		/* 228h */	int field_228;  // -1
		/* 22Ch */	int field_22C;  // -1
		/* 230h */	int field_230;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cScenarioMarker) == 0x234, "sizeof(cScenarioMarker) != 0x234");
}