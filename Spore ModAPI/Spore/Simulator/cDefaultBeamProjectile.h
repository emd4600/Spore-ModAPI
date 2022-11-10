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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cGonzagoTimer.h>

#define cDefaultBeamProjectilePtr eastl::intrusive_ptr<Simulator::cDefaultBeamProjectile>

namespace Simulator
{
	class cCombatant;
	class cSpaceToolData;

	class cDefaultBeamProjectile
		: public cGameData
		, public cSpatialObject
		, public cProjectile
		, public cBehaviorList
	{
	public:
		static const uint32_t TYPE = 0x24630CE;
		static const uint32_t NOUN_ID = 0x24630D7;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 134h */	eastl::intrusive_ptr<cSpaceToolData> mpTool;
		/* 138h */	eastl::intrusive_ptr<cCombatant> mpSource;
		/* 13Ch */	Vector3 mTargetPosition;
		/* 148h */	Vector3 mHitPosition;
		/* 154h */	bool field_154;
		/* 155h */	bool mbStopBeam;
		/* 158h */	float mMaxBeamLength;
		/* 15Ch */	float field_15C;  // 1.0
		/* 160h */	Vector3 mBeamDirection;
		/* 16Ch */	bool mbHittingGround;
		/* 16Dh */	bool mbHittingWater;
		/* 16Eh */	bool mbOrientsToTerrain;
		/* 16Fh */	bool mbPassesThroughToTerrain;
		/* 170h */	float mDamageRadius;  // 1.0
		/* 174h */	float mBeamTurnRate;
		/* 178h */	int64_t mMsPerDamagePoint;
		/* 180h */	int64_t mAccumulatedTime;
		/* 188h */	int64_t mLastUpdate;
		/* 190h */	int64_t mNextAimTime;
		/* 198h */	Vector3 mTargetAimOffset;
		/* 1A4h */	Vector3 mCurrentOffset;
		/* 1B0h */	Vector4 mGroundHitOrientation;
		/* 1C0h */	cGonzagoTimer mLifeTimer;
		/* 1E0h */	cGameDataPtr mpTargetedCombatant;
		/* 1E4h */	eastl::vector<Vector3> mPath;
	};
	ASSERT_SIZE(cDefaultBeamProjectile, 0x1F8);
}