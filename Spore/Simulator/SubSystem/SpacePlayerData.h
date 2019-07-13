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

namespace Simulator
{
	enum SpaceContext
	{
		kSpaceContextNone = -1,
		kSpaceContextPlanet = 0,
		kSpaceContextSolarSystem = 1,
		kSpaceContextGalaxy = 2
	};

	cStar* GetActiveStar();
	cStarRecord* GetActiveStarRecord();

	cPlanet* GetActivePlanet();
	cPlanetRecord* GetActivePlanetRecord();

	cEmpire* GetPlayerEmpire();
	uint32_t GetPlayerEmpireID();

	SpaceContext GetCurrentContext();

	class SpacePlayerData
	{
	public:
		/* 00h */	int mMillisecondsSinceLastUpdate;  // not initialized
		/* 04h */	intrusive_ptr<cPlanet> mpActivePlanet;
		/* 08h */	intrusive_ptr<cStar> mpActiveStar;
		/* 0Ch */	intrusive_ptr<cRelationshipManager> mpTribeCivRelationships;
		/* 10h */	SpaceContext mCurrentContext;  // -1
		/* 14h */	float mfRotationRateFactor;  // 1.0
		/* 18h */	uint32_t mPlayerEmpireID;  // -1
		/* 1Ch */	intrusive_ptr<cEmpire> mpPlayerEmpire;
		/* 20h */	vector<intrusive_ptr<cPlanet>> mPlayerColonies;

		static SpacePlayerData* Get();
	};

	namespace Addresses(SpacePlayerData)
	{
		DeclareAddress(ptr, SelectAddress(0x16E1D0C, 0x16DEA6C, 0x16DDA8C));
	}
}

namespace Addresses(Simulator)
{
	DeclareAddress(GetActiveStar, SelectAddress(0x10222B0, 0x10210E0, 0x10210E0));
	DeclareAddress(GetActiveStarRecord, SelectAddress(0x10222C0, 0x10210F0, 0x10210F0));

	DeclareAddress(GetPlayerEmpire, SelectAddress(0x1022380, 0x10211B0, 0x10211B0));
	DeclareAddress(GetPlayerEmpireID, SelectAddress(0x10220F0, 0x1020F40, 0x1020F40));

	DeclareAddress(GetCurrentContext, SelectAddress(0x10220E0, 0x1020F30, 0x1020F30));

}