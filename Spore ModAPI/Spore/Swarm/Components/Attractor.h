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
		struct Attractor
		{
			Attractor();

			/* 00h */	eastl::vector<float> strength;
			/* 14h */	float range;
			/* 18h */	float killRange;
		};
		ASSERT_SIZE(Attractor, 0x1C);

		inline Attractor::Attractor()
			:
			strength(), range(1.0f), killRange(0)
		{
		}
	}
}