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
#include <Spore\ResourceID.h>
#include <EASTL\vector.h>

using namespace eastl;

namespace Swarm
{
	namespace Components
	{
		class Surface
		{
		public:
			Surface();

			/* 00h */	int flags;  // & 0x3FFF
			/* 04h */	int field_4;
			/* 08h */	ResourceID surfaceMapID;
			/* 10h */	float bounce;
			/* 14h */	float slide;
			/* 18h */	float collisionRadius;
			/* 1Ch */	float deathProbabilty;
			/* 20h */	float pinOffset;
			/* 24h */	float field_24;
			/* 28h */	float field_28;
			/* 2Ch */	float field_2C;
			/* 30h */	float field_30;
			/* 34h */	float field_34;
			/* 38h */	int collideEffectIndex;
			/* 3Ch */	int deathEffectIndex;
			/* 40h */	vector<Math::Vector3> surfacePoints;
			/* 54h */	int field_54;

			enum
			{
				kFlagPin = 2,
				kFlagPinMove = 4,
				kFlagPinEmit = 8,
				kFlagAlign = 0x20,
				kFlagSourceSpace = 0x40,
				kFlagWorldSpace = 0x80
			};
		};

		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		static_assert(sizeof(Surface) == 0x58, "sizeof(Surface) != 58h");

		inline Surface::Surface()
			:
			flags(0), collideEffectIndex(-1), deathEffectIndex(-1), surfaceMapID(-1, -1),
			collisionRadius(0), deathProbabilty(0), pinOffset(0), field_28(0), field_2C(0), field_30(0),
			bounce(1.0f), slide(1.0f), field_24(-1.0E9), field_34(-1.0E9)
		{
		}
	}
}