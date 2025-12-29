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
#include <Spore\LocalizedString.h>
#include <EASTL\vector.h>
#include <Spore\App\PropertyList.h>

#define cCreatureAbilityPtr eastl::intrusive_ptr<Simulator::cCreatureAbility>

namespace Simulator
{
	class cCreatureAbility
		: public RefCountTemplate
	{
	public:
		virtual ~cCreatureAbility() {}

		static bool Parse(cCreatureAbility* pAbility, App::PropertyList* pPropList);

		enum AbilityTypes
		{
			SocialHorn = 5,
			SocialMaraca = 6,
			SocialDidgeridoo = 7,
			AutoAttack = 8,
			Stealth = 13,
			Speed = 14,
			Block = 15,
			MatingCall = 16,
			Jump = 17,
			Glide = 18,
			Grasper = 19,
			Ration = 27,
			Scan = 29,
			Bite = 30,
			Charge = 31,
			Spit = 32,
			Strike = 33,
			Dance = 34,
			Pose = 35,
			Charm = 36,
			Sing = 37,
			Sprint = 39,
			Sight = 40,
			Stomp = 41,
			TribeAttackUnk = 42,
			TribeSpear = 43,
			TribeAttack = 44,
			TribeSocial = 45,
			TribeArmor = 46,
			TribeGathering = 47,
			TribeFishing = 48,
			CRG_SuperPower_Carnivore = 49,
			CRG_SuperPower_Herbivore = 50,
			CRG_SuperPower_Omnivore = 51,
			TRG_SuperPower_Carnivore = 52,
			TRG_SuperPower_Herbivore = 53,
			TRG_SuperPower_Omnivore = 54,
			TRG_SuperPower_Aggressive = 55,
			TRG_SuperPower_Social = 56,
			TRG_SuperPower_Versatile = 57,
			TribeTorch = 58,
			TribeAxe = 59,
			EnergyRegen = 60,
			Missile = 61,
			EnergyBlade = 62,
			ShieldGenerator = 63,
			HoloCharm = 64,
			LightningSword = 65,
			PulseGun = 66,
			BattleArmor = 67,
			PoweredArmor = 68,
			EnergyAbsorption = 69,
			HealthRegen = 70,
			SummonSwarm = 72,
			MindMeld = 73,
			PoisonBlade = 74,
			Freeze = 75,
			GracefulWaltz = 76,
			HarmoniousSong = 77,
			RoyalCharm = 78,
			RadiantPose = 79,
			SprintBurst = 80,
			Hover = 81,
			StealthField = 82,
			JumpJet = 83,
			InspiringSong = 84,
			StunningDance = 85,
			ConfettiPose = 86,
			EnergyStorage = 87,
		};

		//PLACEHOLDER loc_D1E9D0 uses ability type?

		/// Returns the animation ID at the given index, or 0x4330667 if there are no animation IDs in this ability or
		/// the given index is greater than the number of animations.
		/// @param
		uint32_t GetAnimationID(int index);

		/* 08h */	int mType;
		/* 0Ch */	int mCategory;
		/* 10h */	int mSocialCategory;
		/* 14h */	LocalizedString nName;
		/// The ID of the image in the layout
		/* 28h */	uint32_t mVerbIconImageID;
		/// Points to the layout file for a single verb icon
		/* 2Ch */	ResourceKey mVerbIconGameLayout;
		/// The ascii value of the key that triggers this ability. -1 means "use the tray index" and -2 means "no hot key"
		/* 38h */	int mVerbIconTriggerKey;
		/* 3Ch */	float mDamage;
		/* 40h */	float mRangedDamage;
		/* 44h */	float mRazeDamage;
		/* 48h */	eastl::vector<uint32_t> mAnimationIDs;
		/* 5Ch */	eastl::vector<uint32_t> mFollowerAnimationIDs;
		/// Animation ID a verb should play to show off the verb icon
		/* 70h */	uint32_t mVerbIconRepresentativeAnimation;
		/* 74h */	uint32_t mBabyGameAnimationID;
		/* 78h */	uint32_t mBuildingSpecificAnimationID;
		/* 7Ch */	int mEffectKind;
		/* 80h */	float mEffectDuration;
		/* 84h */	float mEffectDamage;
		/* 88h */	uint32_t mMuzzleEffectID;
		/* 8Ch */	uint32_t mTrailEffectID;
		/* 90h */	uint32_t mImpactEffectID;
		/* 94h */	float mConeDist;
		/* 98h */	float mConeRadius;
		/* 9Ch */	float mRefresh;  // 5.0
		/* A0h */	float mDuration;
		/* A4h */	float mRecharge;
		/* A8h */	float mRange;  // 10.0
		/* ACh */	float mEnergyCost;
		/* B0h */	float mSpeed;  // 5.0
		/* B4h */	unsigned int mSpeedGear;
		/* B8h */	eastl::vector<uint32_t> mCombatEffectTypes;
		/* CCh */	eastl::vector<float> mCombatEffectPercentages;
		/* E0h */	eastl::vector<uint32_t> mCombatEffectEffectIds;
		/* F4h */	float mRushingRange;
		/* F8h */	uint32_t mRushingAnimationID;  // -1
		/* FCh */	float mRushingSpeed;
		/* 100h */	bool mbRushingTargetedCharge;  // true
		/* 101h */	bool mbRushingDoDamage;
		/* 104h */	float mAdventurerEnergyCost;
		/* 108h */	int mSprintBuff;  // 2
		/* 10Ch */	float mDNAPoints;
		/* 110h */	float mLevelMultiplier;  // 1.0
		/* 114h */	bool mbIsSpecial;
		/* 115h */	bool mbUseForBabyGame;
		/* 118h */	uint32_t mHintName;
		/* 11Ch */	float mAreaOfEffect;
		/* 120h */	uint32_t mReactionAnimation;
		/* 124h */	uint32_t mReactionDeathAnimation;
		/* 128h */	uint32_t mReactionLiveAnimation;
		/* 12Ch */	float mReactionDuration;
		/* 130h */	PropertyListPtr mpPropList;
		/* 134h */	float mRangeMin;
		/* 138h */	float mAvatarRangeMin;
	};
	ASSERT_SIZE(cCreatureAbility, 0x13C);

	namespace Addresses(cCreatureAbility)
	{
		DeclareAddress(Parse);

		DeclareAddress(GetAnimationID);
	}
}
