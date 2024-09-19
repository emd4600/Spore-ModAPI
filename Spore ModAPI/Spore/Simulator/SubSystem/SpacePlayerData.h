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

#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\cStar.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\SimulatorEnums.h>

namespace Simulator
{
	cStar* GetActiveStar();
	cStarRecord* GetActiveStarRecord();

	cPlanet* GetActivePlanet();
	cPlanetRecord* GetActivePlanetRecord();

	cEmpire* GetPlayerEmpire();
	uint32_t GetPlayerEmpireID();

	SpaceContext GetCurrentContext();

	cPlanetRecord* GetPlayerHomePlanet();

	class SpacePlayerData
	{
	public:
		/* 00h */	int mMillisecondsSinceLastUpdate;  // not initialized
		/* 04h */	cPlanetPtr mpActivePlanet;
		/* 08h */	cStarPtr mpActiveStar;
		/* 0Ch */	eastl::intrusive_ptr<cRelationshipManager> mpTribeCivRelationships;
		/* 10h */	SpaceContext mCurrentContext;  // -1
		/* 14h */	float mfRotationRateFactor;  // 1.0
		/* 18h */	uint32_t mPlayerEmpireID;  // -1
		/* 1Ch */	cEmpirePtr mpPlayerEmpire;
		/* 20h */	eastl::vector<cPlanetPtr> mPlayerColonies;

		static SpacePlayerData* Get();
	};

	namespace Addresses(SpacePlayerData)
	{
		DeclareAddress(ptr);
	}

#ifdef SDK_TO_GHIDRA
	SpacePlayerData* sSpacePlayerData;
#endif
}

namespace Addresses(Simulator)
{
	DeclareAddress(GetActiveStar);
	DeclareAddress(GetActiveStarRecord);

	DeclareAddress(GetPlayerEmpire);
	DeclareAddress(GetPlayerEmpireID);

	DeclareAddress(GetCurrentContext);

	DeclareAddress(GetPlayerHomePlanet);  // 0x10223F0 0x1021220
}