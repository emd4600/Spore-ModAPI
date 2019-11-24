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

using namespace eastl;

namespace Simulator
{
	class cCreatureAbility
	{
	public:
		virtual ~cCreatureAbility();

		static bool Parse(cCreatureAbility* pAbility, App::PropertyList* pPropList);

		//PLACEHOLDER loc_D1E9D0 uses ability type?

		/// Returns the animation ID at the given index, or 0x4330667 if there are no animation IDs in this ability or
		/// the given index is greater than the number of animations.
		/// @param
		uint32_t GetAnimationID(int index);

		/* 04h */	int field_04;
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
		/* 3Ch */	float mfDamage;
		/* 40h */	float mfRangedDamage;
		/* 44h */	float mfRazeDamage;
		/* 48h */	vector<uint32_t> mAnimationIDs;
		/* 5Ch */	vector<uint32_t> mFollowerAnimationIDs;
		/// Animation ID a verb should play to show off the verb icon
		/* 70h */	uint32_t mVerbIconRepresentativeAnimation;
		/* 74h */	uint32_t mBabyGameAnimationID;
		/* 78h */	uint32_t mBuildingSpecificAnimationID;
		/* 7Ch */	int mEffectKind;
		/* 80h */	float mfEffectDuration;
		/* 84h */	float mfEffectDamage;
		/* 88h */	uint32_t mMuzzleEffectID;
		/* 8Ch */	uint32_t mTrailEffectID;
		/* 90h */	uint32_t mImpactEffectID;
		/* 94h */	float mfConeDist;
		/* 98h */	float mfConeRadius;
		/* 9Ch */	float mfRefresh;  // 5.0
		/* A0h */	float mfDuration;
		/* A4h */	float mfRecharge;
		/* A8h */	float mfRange;  // 10.0
		/* ACh */	float mfEnergyCost;
		/* B0h */	float mfSpeed;  // 5.0
		/* B4h */	unsigned int mSpeedGear;
		/* B8h */	vector<uint32_t> mCombatEffectTypes;
		/* CCh */	vector<float> mCombatEffectPercentages;
		/* E0h */	vector<uint32_t> mCombatEffectEffectIds;
		/* F4h */	float mfRushingRange;
		/* F8h */	uint32_t mRushingAnimationID;  // -1
		/* FCh */	float mfRushingSpeed;
		/* 100h */	bool mbRushingTargetedCharge;  // true
		/* 101h */	bool mbRushingDoDamage;
		/* 104h */	float mfAdventurerEnergyCost;
		/* 108h */	int mSprintBuff;  // 2
		/* 10Ch */	float mfDNAPoints;
		/* 110h */	float mfLevelMultiplier;  // 1.0
		/* 114h */	bool mbIsSpecial;
		/* 115h */	bool mbUseForBabyGame;
		/* 118h */	uint32_t mHintName;
		/* 11Ch */	float mfAreaOfEffect;
		/* 120h */	uint32_t mReactionAnimation;
		/* 124h */	uint32_t mReactionDeathAnimation;
		/* 128h */	uint32_t mReactionLiveAnimation;
		/* 12Ch */	float mfReactionDuration;
		/* 130h */	intrusive_ptr<App::PropertyList> mpPropList;
		/* 134h */	float mfRangeMin;
		/* 138h */	float mfAvatarRangeMin;
	};

	static_assert(sizeof(cCreatureAbility) == 0x13C, "sizeof(cCreatureAbility) != 13Ch");

	namespace Addresses(cCreatureAbility)
	{
		DeclareAddress(Parse);

		DeclareAddress(GetAnimationID);
	}
}
