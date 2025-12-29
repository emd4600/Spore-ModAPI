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

#include <Spore\ResourceKey.h>
#include <Spore\Simulator\cCreatureAbility.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\fixed_hash_map.h>

namespace Simulator
{
	class cSpeciesProfile
	{
	public:

		const ResourceKey& GetSpeciesKey();

		void GetSpeciesName(eastl::string16& dst);

	public:
		struct UnkStruct
		{
			int field_0;
			int field_4;
			int field_8;
			int field_C;
			int field_10;
		};
		ASSERT_SIZE(UnkStruct, 0x14);

		typedef eastl::sp_fixed_hash_map<int, UnkStruct, 32> UnkStructPool;
		ASSERT_SIZE(UnkStructPool, 0x4E0);

		/* 00h */	UnkStructPool field_0;
		/* 4E0h */	ResourceKey field_4E0[3];
		/* 504h */	ResourceKey mSpeciesKey;  //TODO this is the main key?
		/* 510h */	ResourceKey mBabyKey;
		/* 51Ch */	eastl::string16 mName;
		/* 52Ch */	eastl::string16 field_52C;
		/* 53Ch */	int field_53C;
		/* 540h */	int mCost;
		/* 544h */	int field_544;
		/* 548h */	float mCreatureAbilityJumping;
		/* 54Ch */	float mCreatureAbilityGliding;
		/* 550h */	float mCreatureAbilityFlapping;
		/* 554h */	Math::Vector3 mBoundingBoxUpper;
		/* 560h */	Math::Vector3 mBoundingBoxLower;
		/* 56Ch */	float mAdditionalHealth;  // 100.0
		/* 570h */	float field_570;  // 200.0
		/* 574h */	float field_574;	//CreatureSize?
		/* 578h */	bool mHasPlantRoot;
		/* 57Ch */	ModelTypes mModelType;
		/* 580h */	int field_580;  // not initialized
		/* 584h */	int field_584;  // not initialized
		/* 588h */	int field_588;  // 1
		/* 58Ch */	float mNumFoot;
		/* 590h */	float mNumGrasper;
		/* 594h */	float mNumMouth;
		/* 598h */	float mNumEar;
		/* 59Ch */	float mNumEye;
		/* 5A0h */	float mCuteness1;
		/* 5A4h */	float mCuteness2;
		/* 5A8h */	float field_5A8;
		/* 5ACh */	float mSocialSum;
		/* 5B0h */	float mAttackSum;
		/* 5B4h */	float mAttackMaxLevel;
		/* 5B8h */	float mSocialMaxLevel;
		/* 5BCh */	float mMeanness;
		/* 5C0h */	float field_5C0;	//itemUnlockLevel?
		/* 5C4h */	float field_5C4;	//itemUnlockLevel?
		/* 5C8h */	int mDuration;  // 5000
		/* 5CCh */	float mRefillAbilityBars;  // 1.0	cCreatureAbility->mDuration / cCreatureAbility->mRecharge
		/* 5D0h */	int mSprintBuff;  // 2
		/* 5D4h */	int mBiteLevel;
		/* 5D8h */	int mChargeLevel;
		/* 5DCh */	int mSpitLevel;
		/* 5E0h */	int mStrikeLevel;
		/* 5E4h */	int mSingLevel;
		/* 5E8h */	int mDanceLevel;
		/* 5ECh */	int mCharmLevel;
		/* 5F0h */	int mPoseLevel;
		/* 5F4h */	int mStealthLevel;
		/* 5F8h */	int field_5F8;
		/* 5FCh */	int mMatingCall;
		/* 600h */	int mCreatureSpeedLevel;
		/* 604h */	int mHealthLevel;
		/* 608h */	int mMouthCarnivorous;
		/* 60Ch */	int mMouthHerbivorous;
		/* 610h */	int mJumpLevel;
		/* 614h */	int mSprintLevel;
		/* 618h */	int mSight;	//Sense
		/* 61Ch */	int mGlideLevel;
		/* 620h */	int field_620;
		/* 624h */	int field_624;
		/* 628h */	int mTribeAttackLevel;
		/* 62Ch */	int mTribeSocialLevel;
		/* 630h */	int mTribeArmorLevel;
		/* 634h */	int mTribeGatherLevel;
		/* 638h */	int mTribeFishingLevel;
		/* 63Ch */	float mDamage;
		/* 640h */	float mEnergyRecoveryRate;
		/* 644h */	float mMaxEnergy;
		/* 648h */	int mShieldGenerator;
		/* 64Ch */	int mMissileLevel;
		/* 650h */	int mEnergyBladeLevel;
		/* 654h */	int mHoloCharmLevel;
		/* 658h */	int mLightningSwordLevel;
		/* 65Ch */	int mPulseGunLevel;
		/* 660h */	int mBattleArmor;
		/* 664h */	int mPoweredArmor;
		/* 668h */	int mAbsorptionShield;
		/* 66Ch */	float mHealthRecoveryRate;
		/* 670h */	int mBonusHealth;
		/* 674h */	int mSummonSwarm;
		/* 678h */	int mMindMeld;
		/* 67Ch */	int mPoisonBlade;
		/* 680h */	int mFreeze;
		/* 684h */	int mGracefulWaltz;
		/* 688h */	int mHarmoniousSong;
		/* 68Ch */	int mRoyalCharm;
		/* 690h */	int mRadiantPose;
		/* 694h */	int mSprintBurst;
		/* 698h */	int mHover;
		/* 69Ch */	int mStealthField;
		/* 6A0h */	int mJumpJet;
		/* 6A4h */	int mInspiringSongLevel;
		/* 6A8h */	int mStunningDanceLevel;
		/* 6ACh */	int mConfettiPoseLevel;
		/* 6B0h */	float mAdventurerEnergyCost;
		/* 6B4h */	int field_6B4;
		/* 6B8h */	eastl::vector<int> mFruits;	//unk type
		/* 6CCh */	bool mIsGameMode;	//true if cSpeciesProfile was called in gameMode, false otherwise
		/* 6D0h */	uint32_t mFootWeaponOrMouthType;
		/* 6D4h */	eastl::fixed_vector<cCreatureAbility*, 20> mActiveAbilities;  //TODO abilities
		/* 73Ch */	eastl::fixed_vector<cCreatureAbility*, 20> mPassiveAbilities;
		/* 7A4h */	eastl::fixed_vector<int, 20> field_7A4;
		/* 80Ch */	bool field_80C;
		/* 80Dh */	bool field_80D;
		/* 810h */	eastl::fixed_vector<int, 20> mFruitIndexes;
		/* 878h */	eastl::fixed_vector<int, 20> mMouthIndexes;
		/* 8E0h */	eastl::fixed_vector<int, 20> mGraspersIndexes;
		/* 948h */	eastl::fixed_vector<int, 20> mMouthsIndexes2;
		/* 9B0h */	eastl::fixed_vector<int, 20> mGraspersIndexes2;
	};
	ASSERT_SIZE(cSpeciesProfile, 0xA18);

	namespace Addresses(cSpeciesProfile) 
	{
		DeclareAddress(GetSpeciesName);  // 0x4DA1C0 0x4DA390
	}
}