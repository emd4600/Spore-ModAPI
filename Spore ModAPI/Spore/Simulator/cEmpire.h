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

#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\cCultureSet.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\ICityMusic.h>
#include <Spore\ResourceKey.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>

#define cEmpirePtr eastl::intrusive_ptr<Simulator::cEmpire>

namespace Simulator
{
	enum EmpireFlags
	{
		kEmpireFlagNeedsEmpireLines = 0x10,
	};

	/// An empire in Space Stage.
	class cEmpire
		: public ISimulatorSerializableRefCounted
		, public cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x1805E75;
		static const uint32_t NOUN_ID = 0x18EB9D2;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Returns the political ID of this empire.
		uint32_t GetEmpireID() const;

		cStarRecord* GetHomeStarRecord();

		cSpeciesProfile* GetSpeciesProfile();

		void SetSpeciesProfile(cSpeciesProfile* pSpecies);

		/// Calculates and returns the identity color of the empire, based on the `mIDColorID` field.
		/// ColorIDs equal or greater than `0x53DBCF1` are cached, and `colorID - 0x53DBCF1` is an index to
		/// the real color stored in `animations~!ui.prop` in `IdentityColors` property.
		/// `0x53DBCF1` is special and uses the empire species identity color, instead of the color on the list.
		/// If the ID less than `0x53DBCF1`, the color will be recalculated, cached, and the ID will be updated.
		Math::ColorRGB UpdateAndGetColor();

		/// Makes this empire the owner of the given star. It will emit a kMsgStarOwnershipChanged message.
		void AddStarOwnership(cStarRecord* star);

		/// Captures a star system for a specific empire. This can only be used when the star belongs to another empire.
		/// For any kind of star, use cEmpire::AddStarOwnership
		/// @param pStarRecord The star system to capture.
		/// @param empireID Political ID of the empire that will become the owner.
		static void CaptureSystem(cStarRecord* pStarRecord, uint32_t empireID);

	public:
		/* 3Ch */	eastl::string16 mEmpireName;  // "unknown"
		/* 4Ch */	int mCurrentGameMode;  // not initialized  // uint32_t ?
		/// EmpireFlags
		/* 50h */	int mFlags;  // 0x10 -> grox?
		/// A member of EmpireTrait enum, EmpireTrait::kEmpireTraitNone
		/* 54h */	EmpireTrait mTrait;
		/// A member of Archetypes enum, Archetypes::kArchetypePlayerWanderer by default
		/* 58h */	Archetypes mArchetype;  // kArchetypePlayerWanderer
		/* 5Ch */	eastl::vector<cEmpirePtr> mEnemies;
		/* 70h */	eastl::vector<cEmpirePtr> mAllies;
		/* 84h */	int mPoliticalID;  // -1
		/* 88h */	eastl::vector<cStarRecordPtr> mStars;
		/* 9Ch */	eastl::vector<cStarRecordPtr> mNextStarTowardsHome;
		/* B0h */	StarID mHomeStar;  // -1
		/* B4h */	PlanetID mHomePlanet;  // -1
		/* B8h */	ResourceKey mUFOKey;
		/* C4h */	ResourceKey mCaptainKey;
		/* D0h */	int mEmpireMoney;
		/* D4h */	char mTravelDistance;  // 3
		//TODO sub_C31000 GetEmpireTier ?
		/* D8h */	int field_D8;  // -1  //TODO empire size? Related with combat tuning, check loc_C31039
		/* DCh */	float field_DC;
		/* E0h */	float field_E0;
		/* E4h */	float field_E4;
		/* E8h */	float field_E8;
		/* ECh */	float field_EC;
		/* F0h */	eastl::vector<int> field_F0;
		/* 104h */	ICityMusicPtr mpCityMusic;
		/* 108h */	cCultureSet mCultureSet;
		/* 128h */	cGonzagoTimer field_128;
		/* 148h */	eastl::list<uint32_t> mAdventureList;
		///* 154h */	int field_154;  // not initialized
	};
	ASSERT_SIZE(cEmpire, 0x158);

	///
	/// Returns the instance ID of the property file that contains the relationship properties used by a certain 
	/// archetype in a certain difficulty (such as "spg_bard_easy", "spg_warrior_medium", etc)
	/// @param archetype The archetype, in the "kArchetype..." enum.
	/// @param difficulty The current difficulty, in the "kDifficulty..." enum.
	/// 
	uint32_t GetArchetypeRelationshipsID(int archetype, int difficulty);

	inline uint32_t cEmpire::GetEmpireID() const
	{
		return mPoliticalID;
	}

	namespace Addresses(cEmpire)
	{
		DeclareAddress(GetSpeciesProfile);
		DeclareAddress(SetSpeciesProfile);
		DeclareAddress(sub_C32EA0);
		DeclareAddress(CaptureSystem);
		DeclareAddress(UpdateAndGetColor);  // 0xC325F0 0xC32E30
		DeclareAddress(AddStarOwnership);  // 0xC33AB0 0xC34300
		//TODO sub_C30F90 RequireHomePlanet
	}

}

namespace Addresses(Simulator)
{
	DeclareAddress(GetArchetypeRelationshipsID);
}