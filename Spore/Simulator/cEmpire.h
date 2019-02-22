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

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\cCultureSet.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\ResourceKey.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>

namespace Simulator
{
	enum Archetypes
	{
		kArchetypeWarrior = 0,
		kArchetypeTrader = 1,
		kArchetypeScientist = 2,
		kArchetypeShaman = 3,
		kArchetypeBard = 4,
		kArchetypeZealot = 5,
		kArchetypeDiplomat = 6,
		kArchetypeEcologist = 7,
		kArchetypeGrob = 8,
		kArchetypePlayerWarrior = 9,
		kArchetypePlayerTrader = 10,
		kArchetypePlayerScientist = 11,
		kArchetypePlayerShaman = 12,
		kArchetypePlayerBard = 13,
		kArchetypePlayerZealot = 14,
		kArchetypePlayerDiplomat = 15,
		kArchetypePlayerEcologist = 16,
		kArchetypePlayerWanderer = 17,
		kArchetypePlayerKnight = 18,
	};

	class cEmpire
		: public ISimulatorSerializableRefCounted
		, public cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x1805E75;
		static const uint32_t NOUN_ID = 0x18EB9D2;

		using Object::AddRef;
		using Object::Release;

		cStarRecord* GetHomeStarRecord();

		void SetSpeciesProfile(cSpeciesProfile* pSpecies);

		inline bool IsAtWar(cEmpire* pOther) {
			return cRelationshipManager::Get()->IsAtWar(this, pOther);
		}

		inline void DeclareWar(cEmpire* pOther) {
			cRelationshipManager::Get()->DeclareWar(this, pOther);
		}

	public:
		/* 3Ch */	string16 mEmpireName;  // "unknown"
		/* 4Ch */	int mCurrentGameMode;  // not initialized  // uint32_t ?
		/* 50h */	int mFlags;  // 0x10 -> grox?
		/* 54h */	int mTrait;
		/* 58h */	Archetypes mArchetype;  // kArchetypePlayerWanderer
		/* 5Ch */	vector<intrusive_ptr<cEmpire>> mEnemies;
		/* 70h */	vector<intrusive_ptr<cEmpire>> mAllies;
		/* 84h */	int mPoliticalID;  // -1
		/* 88h */	vector<intrusive_ptr<cStarRecord>> mStars;
		/* 9Ch */	vector<intrusive_ptr<cStarRecord>> mNextStarTowardsHome;
		/* B0h */	uint32_t mHomeStar;  // -1
		/* B4h */	uint32_t mHomePlanet;  // -1
		/* B8h */	ResourceKey mUFOKey;
		/* C4h */	ResourceKey mCaptainKey;
		/* D0h */	int mEmpireMoney;
		/* D4h */	char mTravelDistance;  // 3
		/* D8h */	int field_D8;  // -1
		/* DCh */	float field_DC;
		/* E0h */	float field_E0;
		/* E4h */	float field_E4;
		/* E8h */	float field_E8;
		/* ECh */	float field_EC;
		/* F0h */	vector<int> field_F0;
		/* 104h */	intrusive_ptr<Object> mpCityMusic;
		/* 108h */	cCultureSet mCultureSet;
		/* 128h */	cGonzagoTimer field_128;
		/* 148h */	list<uint32_t> mAdventureList;
		///* 154h */	int field_154;  // not initialized
	};

	///
	/// Returns the instance ID of the property file that contains the relationship properties used by a certain 
	/// archetype in a certain difficulty (such as "spg_bard_easy", "spg_warrior_medium", etc)
	/// @param archetype The archetype, in the "kArchetype..." enum.
	/// @param difficulty The current difficulty, in the "kDifficulty..." enum.
	/// 
	uint32_t GetArchetypeRelationshipsID(int archetype, int difficulty);

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cEmpire) == 0x158, "sizeof(cEmpire) != 158h");

	namespace InternalAddressList(cEmpire)
	{
		DefineAddress(SetSpeciesProfile, GetAddress(0xC32FB0, 0xC337D0, 0xC337F0));
		DefineAddress(sub_C32EA0, GetAddress(0xC32EA0, 0xC336C0, 0xC336E0));
	}

}

namespace InternalAddressList(Simulator)
{
	DefineAddress(GetArchetypeRelationshipsID, GetAddress(0xC30530, NO_ADDRESS, 0xC30E20));
}