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
#include <Spore\Simulator\cGonzagoTimer.h>

#define cDefaultAoEAreaPtr eastl::intrusive_ptr<Simulator::cDefaultAoEArea>

namespace Simulator
{
	class cSpaceToolData;

	class cDefaultAoEArea
		: public cGameData
		, public cSpatialObject
		, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x4167194;
		static const uint32_t NOUN_ID = 0x4167186;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 11Ch */	eastl::intrusive_ptr<cSpaceToolData> mpTool;
		/* 120h */	Vector3 mSourceOffset;  // 1, 1, 1
		/* 12Ch */	float mDamageRadius;
		/* 130h */	bool mbStopArea;
		/* 138h */	cGonzagoTimer mLifeTimer;
		/* 158h */	int64_t mAccumulatedTime;
		/* 160h */	int64_t mCulturalProjectileTime;
		/* 168h */	int64_t mLastUpdate;
	};
	ASSERT_SIZE(cDefaultAoEArea, 0x170);
}