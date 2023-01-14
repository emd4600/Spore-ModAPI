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

#include <Spore\Simulator\cScenarioString.h>
#include <Spore\Simulator\cScenarioAsset.h>
#include <Spore\Simulator\cScenarioClassAct.h>
#include <Spore\Simulator\SimulatorEnums.h>

namespace Simulator
{
	class cScenarioClass
	{
	public:

		static ScenarioObjectType GetObjectType(const ResourceKey& key);

		/// Returns true if this class is the kind of object that is consumed when the player 
		/// approaches it. By default, this returns true on teleporters, jumppads, spead/damage/armor boosts and med/energy kits.
		/// @returns
		bool IsConsumible();

	public:
		/* 00h */	cScenarioAsset mAsset;
		/* 20h */	bool mbIsDeepEditEnabled;
		/* 24h */	ScenarioGfxOverrideType mGfxOverrideType;
		/* 28h */	cScenarioAsset mGameplayObjectGfxOverrideAsset;
		/* 48h */	ScenarioGfxOverrideType mGfxOverideTypeSecondary;
		/* 50h */	cScenarioAsset mGameplayObjectGfxOverrideAsset_Secondary;
		/* 70h */	eastl::fixed_vector<cScenarioClassAct, 8> mActs;
		/* 2788h */	cScenarioString mCastName;
		/* 27C4h */	ResourceKey mAssetKeyDEPRECATED;
		/* 27D0h */	int field_27D0;
		/* 27D4h */	uint32_t mModelTypeDEPRECATED;  // not initialized
		/* 27D8h */	uint64_t mServerIDDEPRECATED;
	};
	ASSERT_SIZE(cScenarioClass, 0x27E0);

	namespace Addresses(cScenarioClass)
	{
		DeclareAddress(GetObjectType);  // 0xEED090
		DeclareAddress(IsConsumible);  // 0xF27A90
	}
}