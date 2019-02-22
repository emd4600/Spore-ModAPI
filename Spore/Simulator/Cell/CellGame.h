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

#include <Spore\Internal.h>
#include <Spore\Simulator\GoalCard.h>

namespace Simulator
{
	namespace Cell
	{

		using namespace eastl;
		using namespace Swarm;
		using namespace Graphics;

		class CellGame
		{
		public:

		protected:
		};

		inline GoalCard* GetGoalCards()
		{
			return (GoalCard*)GetAddress(0x16B8068, 0x16B4DC8, 0x16B3DE8);
		}

		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		static_assert(sizeof(CellGFX) == 0x1625C, "sizeof(CellGFX) == 1625Ch");
	}
	
}

