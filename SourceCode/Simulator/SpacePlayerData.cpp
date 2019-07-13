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
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>

namespace Simulator
{
	SpacePlayerData* SpacePlayerData::Get()
	{
		return *(SpacePlayerData**)(GetAddress(SpacePlayerData, ptr));
	}

	cPlanet* GetActivePlanet()
	{
		return SpacePlayerData::Get()->mpActivePlanet.get();
	}

	cPlanetRecord* GetActivePlanetRecord()
	{
		auto planet = SpacePlayerData::Get()->mpActivePlanet.get();
		return planet ? planet->mpPlanetRecord.get() : nullptr;
	}

	auto_STATIC_METHOD_(Simulator, cStar*, GetActiveStar);
	auto_STATIC_METHOD_(Simulator, cStarRecord*, GetActiveStarRecord);

	auto_STATIC_METHOD_(Simulator, cEmpire*, GetPlayerEmpire);
	auto_STATIC_METHOD_(Simulator, uint32_t, GetPlayerEmpireID);

	auto_STATIC_METHOD_(Simulator, SpaceContext, GetCurrentContext);
}