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

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\StarID.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCollectableItems.h>
#include <EASTL\hash_set.h>
#include <EASTL\vector_map.h>
#include <EASTL\map.h>
#include <EASTL\fixed_hash_set.h>
#include <EASTL\fixed_hash_map.h>

#define cPlayerPtr eastl::intrusive_ptr<Simulator::cPlayer>

namespace Simulator
{
	class cSpacePlayerWarData
	{
	public:
		/* 00h */	virtual ~cSpacePlayerWarData() = 0;
		/* 04h */	virtual bool Write(ISerializerStream* stream) = 0;
		/* 08h */	virtual bool Read(ISerializerStream* stream) = 0;

	public:
#ifdef SDK_TO_GHIDRA
		/* 04h */	int field_4;
#endif
		/* 08h */	uint32_t mEnemyEmpireID;
		/* 10h */	cGonzagoTimer mTimeSinceWarStart;
		/* 30h */	int mPlayerStartStarsCount;
		/* 34h */	int mEnemyStartStarsCount;
		/* 38h */	int mPlayerStarsCaptured;
		/* 3Ch */	int mEnemyStarsCaptured;
	};
	ASSERT_SIZE(cSpacePlayerWarData, 0x40);

	class PlayerPlanetData
	{
	public:
		/* 00h */	virtual bool Write(ISerializerStream* stream) = 0;
		/* 04h */	virtual bool Read(ISerializerStream* stream) = 0;
		/* 08h */	virtual ~PlayerPlanetData() = 0;

	public:
#ifdef SDK_TO_GHIDRA
		/* 04h */	int field_4;
#endif
		/* 08h */	eastl::vector_map<ResourceKey, bool> mSpeciesIsScanned;
		/* 20h */	eastl::vector_map<ResourceKey, bool> mBuildingIsScanned;
		/* 38h */	eastl::vector_map<ResourceKey, bool> mVehicleIsScanned;
		/* 50h */	eastl::vector_map<ResourceKey, bool> mUFOIsScanned;
		/* 68h */	eastl::vector_map<uint32_t, bool> mPoliticalIDsEncountered;
		/* 80h */	cGonzagoTimer mTimeSinceLastSpiceUpdate;
		/* A0h */	int8_t mMaxTScore;
		/* A1h */	int8_t mMaxFoodWebLines;
		/* A2h */	uint8_t mExplored;
		/* A4h */	int field_A4;
		/* A8h */	PlanetID field_A8;
		/* ACh */	int field_AC;
	};
	ASSERT_SIZE(PlayerPlanetData, 0xB0);

	class cPlayer
		/* 00h */	: public cGameData
		/* 34h */	, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x3C609F8;

		/// Determines whether the specified AI empire is aware of the player.
		/// An empire is considered "aware" if the player has contacted it at least once,
		/// or if the empire has ever sent a transmission to the player.
		/// @param empireID The ID of the empire to check.
		/// @returns True if the empire is aware of the player, false otherwise.
		bool EmpireIsAwareOfPlayer(uint32_t empireID);

	public:
		/* 38h */	eastl::sp_fixed_hash_set<ResourceKey, 64> mOneTimeEventFlags;
		/* 68Ch */	int field_68C;
		/* 690h */	int field_690;
		/* 694h */	int field_694;
		/* 698h */	eastl::sp_fixed_hash_map<int, int, 128> mFlags;
		/* 10E8h */	cCollectableItemsPtr mpCRGItems;
		/* 10ECh */	int field_10EC;  // not initialized
		/* 10F0h */	float mCurrentGoalProgress;
		/* 10F4h */	float mGoalProgressTotal;  // not initialized
		/* 10F8h */	uint32_t mUniqueGameID;
		/* 10FCh */	uint32_t mCellConsequenceTrait;
		/* 1100h */	uint32_t mCreatureConsequenceTrait;
		/* 1104h */	uint32_t mTribeConsequenceTrait;
		/* 1108h */	uint32_t mCivConsequenceTrait;
		/* 110Ch */	uint32_t mSpaceConsequenceTrait;
		/* 1110h */	char field_1110[0xC];
		/* 111Ch */	eastl::hash_set<uint32_t> mGameEventRecord;
		/* 113Ch */	eastl::vector<eastl::vector<cSpatialObjectPtr>> mSelectionGroups;
		/* 1150h */	ResourceKey mSelectedCityHallKey;
		/* 115Ch */	ResourceKey mSelectedVehicleKey;
		/* 1168h */	ResourceKey mSelectedUFOKey;
		/* 1174h */	int field_1174;  // not initialized
		/* 1178h */	Math::Vector3 mCapitalCityPos;  // not initialized
		/* 1184h */	eastl::vector<StarID> mStarsVisited;
		/* 1198h */	eastl::vector<StarID> mStarsKnown;
		/* 11ACh */	eastl::vector<StarID> mWormholesUsed;
		/* 11C0h */	eastl::vector<int> mPlanetData;
		/* 11D8h */	eastl::map<int, int> mPlayerSpecificEmpireData;
		/* 11F0h */	bool mHasCheated;
		/* 11F4h */	int field_11F4;
		/* 11F8h */	eastl::map<int, cSpacePlayerWarData> mSpacePlayerWarData;
		/* 1214h */	eastl::vector<eastl::pair<uint32_t, cGonzagoTimer>> mPlayerCaptureProgressStars;
		/* 1228h */	eastl::map<int, eastl::pair<int, int>> mEmbassies;
		/* 1244h */	uint32_t mThemeID;
		/* 1248h */	Difficulty mDifficultyLevel;
		/* 124Ch */	int mMaxPosseSize;
		/* 1250h */	int mTempPosseCount;
		/* 1254h */	int field_1254;
		/* 1258h */	cGonzagoTimer mSoothingSongTimer;
		/* 1278h */	float mSocialTraitProgress;
		/* 127Ch */	float mCombatTraitProgress;
		/* 1280h */	ResourceKey mPirateUFOModelKey;
		/* 128Ch */	unsigned int mTotalTimeInCVG;
		/* 1290h */	ResourceKey mInitCaptainKey;
		/* 129Ch */	eastl::fixed_vector<uint32_t, 9> mAdventuresCompleted;
	};
	ASSERT_SIZE(cPlayer, 0x12D8);

	namespace Addresses(cPlayer)
	{
		DeclareAddress(EmpireIsAwareOfPlayer); // 0xc79900   0xc7a910
	}
}