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

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cPlanetRecord.h>
#include <Spore\Simulator\cCommodityNode.h>
#include <EASTL\hash_map.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>

#define TerraformingManager (*Simulator::cTerraformingManager::Get())

namespace Simulator
{
	class cTerraformingManager
		: public cStrategy
	{
	public:
		
		/// Returns the TScore of the current planet, or the planet specified in the parameter.
		/// The TScore is calculated using the planet atmosphere and temperature scores.
		int GetTScore(const cPlanetRecord* pPlanet = nullptr);

		int CalculateTScore(float atmosphereScore, float temperatureScore);

	public:
		/* 1Ch */	eastl::hash_map<int, int> field_1C;
		/* 3Ch */	bool field_3C;  // true
		/* 40h */	int field_40;  // -1
		/* 44h */	bool field_44;
		/* 48h */	eastl::map<int, int> field_48;
		/* 64h */	int field_64;
		/* 68h */	eastl::vector<cCommodityNodePtr> mCommodityNodes;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;

	public:
		static cTerraformingManager* Get();
	};
	ASSERT_SIZE(cTerraformingManager, 0x94);

	namespace Addresses(cTerraformingManager)
	{
		DeclareAddress(Get);

		DeclareAddress(GetTScore);
		DeclareAddress(CalculateTScore);
	}
}