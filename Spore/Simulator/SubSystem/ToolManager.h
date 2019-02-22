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
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cToolStrategy.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\MathUtils.h>
#include <Spore\LocalizedString.h>

#include <EASTL\hash_map.h>
#include <EASTL\map.h>

namespace Simulator
{
	class cToolManager
		: public cStrategy
		, public App::IUnmanagedMessageListener
	{
	public:
		enum ToolFailText
		{
			kCantUseInThisSystem = 0,
			kMustUseOnPlanet = 1,
			kRanOutOfAmmo = 2,
			kRecharging = 3,
			kMustBeUsedOnEmpirePlanet = 4,
			kMustBeUsedOnAlienColony = 5,
			kMustBeUsedOnYourColony = 6,
			kCanOnlyHaveOnePerPlanet = 7,
			kNoRoomInFleet = 8,
			kAlreadyHaveMiniU = 9,
			kSystemMustHaveTradeRoute = 0x0A,
			kMustBeOnHighestTech = 0x0B,
			kAnimalMustBePresentOnPlanet = 0x0C,
			kCannotUseMonolith = 0x0D,
			kCantUseOnEmpireSystems = 0x0E,
			kCantUseOnWildlifeSanctuary = 0x0F,
			kMustBeOnWildPlanets = 0x10,
			kNeedHigherTerrascore = 0x11,
			kCantUseOnHomeworld = 0x12,
			kEnergyIsFull = 0x13,
			kHealthIsFull = 0x14,
			kCantUseOverWater = 0x15,
			kCantUseAboveACity = 0x16,
			kYouAreTooHighUp = 0x17,
			kStarSystemAlreadyHasSentient = 0x18,
			kCantPlaceMoreColoniesWithCurrentTScore = 0x19
		};

		enum Messages
		{
			kMsgToolActivated = 0x61DAE5C,
			kMsgToolDeactivated = 0x61DAE65
		};

		bool LoadTool(const ResourceKey& id, intrusive_ptr<cSpaceToolData>& dst);

		cToolStrategy* GetStrategy(uint32_t strategyID);
		void AddStrategy(cToolStrategy* pStrategy, uint32_t id);

		const char16_t* GetToolFailText(ToolFailText index);

		// Does not generate message
		bool ActivateTool(cSpaceToolData* pTool);
		bool DeactivateTool(cSpaceToolData* pTool);

		bool OnMouseUp(cSpaceToolData* pTool);

		// sub_10505F0 deselect? PLACEHOLDER

	protected:
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	Math::Vector3 field_2C;
		/* 38h */	hash_map<uint32_t, intrusive_ptr<cToolStrategy>> mStrategies;
		/* 58h */	map<int, int> field_58;
		/* 74h */	LocalizedString mToolFailTexts[26];
		/* 27Ch */	int field_27C;
		/* 280h */	int field_280;
		/* 284h */	int field_284;
		/* 288h */	int field_288;
		/* 28Ch */	int field_28C;
		/* 290h */	Math::Vector3 field_290;

	public:
		///
		/// Returns the active Simulator tool manager. Same as ToolManager().
		///
		static cToolManager* Get();
	};

	///
	/// Returns the active Simulator tool manager. Same as cToolManager::Get().
	///
	inline cToolManager* ToolManager()
	{
		return cToolManager::Get();
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cToolManager) == 0x29C, "sizeof(cToolManager) != 29Ch");

	namespace InternalAddressList(cToolManager)
	{
		DefineAddress(Get, GetAddress(0xB3D2F0, 0xB3D460, 0xB3D490));

		DefineAddress(LoadTool, GetAddress(0x104EEA0, 0x104E350, 0x104E350));
		DefineAddress(GetStrategy, GetAddress(0x10503B0, NO_ADDRESS, 0x104F860));

		DefineAddress(ActivateTool, GetAddress(0x1050710, NO_ADDRESS, 0x104FBC0));
		DefineAddress(DeactivateTool, GetAddress(0x1050770, NO_ADDRESS, 0x104FC20));
		DefineAddress(OnMouseUp, GetAddress(0x10505F0, NO_ADDRESS, 0x104FAA0));
	}
}
