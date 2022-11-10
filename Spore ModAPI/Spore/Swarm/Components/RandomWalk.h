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

#include <EASTL\vector.h>

namespace Swarm
{
	namespace Components
	{
		struct RandomWalk
		{
			RandomWalk();

			/* 00h */	float time[2];
			/* 08h */	float strength[2];
			/* 10h */	float turnRange;
			/* 14h */	float turnOffset;
			/* 18h */	float mix;
			/* 1Ch */	eastl::vector<float> offsets;
			/* 30h */	char loopType;
		};
		ASSERT_SIZE(RandomWalk, 0x34);

		inline RandomWalk::RandomWalk()
			:
			time(), strength(), turnRange(0.25f), turnOffset(0), mix(0), offsets(), loopType(2)
		{
			time[0] = 5.0f;
			time[1] = 5.0f;
		}
	}
}