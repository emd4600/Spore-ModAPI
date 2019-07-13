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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGameBundleContainer.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\UnknownCreatureClass.h>
#include <Spore\resourceID.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>
#include <EASTL\bitset.h>

namespace Simulator
{
	

	class UnknownCreatureClass2
	{
		char field_0[0xA0];
	};

	// Maybe used in other places as well?
	class cAbilityState  // size 10h
	{
	public:
		/* 00h */	bool field_00;
		/* 01h */	bool field_01;
		/* 04h */	int field_04;
		/* 08h */	ResourceID field_08;
	};
	// Maybe used in other places as well?
	class cCreatureItem  // size 24h
	{
	public:
		/* 00h */	int field_00;
		/* 04h */	int field_04;
		/* 08h */	int field_08;
		/* 0Ch */	int field_0C;  // not written
		/* 10h */	int field_10;
		/* 14h */	int field_14;  // not written
		/* 18h */	bool field_18;
		/* 1Ch */	int field_1C;  // not written
		/* 20h */	intrusive_ptr<cSpatialObject> field_20;
	};

	class cCreatureBase
		: /* 00h */	public cGameData
		, /* 34h */	public cGameBundleContainer
		, /* 58h */	public cBehaviorAgent
		, /* C0h */	public cLocomotiveObject
		, /* 590h */	public cBehaviorList
		, /* 5A8h */	public cCombatant
		, /* 670h */	public UnknownCreatureClass
	{
	public:
		static const uint32_t TYPE = 0xCE9F6639;

		enum
		{
			kStandardSpeed = 2
		};

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		void* PlayAnimation(uint32_t animationID, int = 0xFFFFFFFF, bool = false);

		void* PlayAnimationTo(uint32_t animationID, cSpatialObject* otherObject, int = 0xFFFFFFFF, int = 0xFFFFFFFF);

		// sub_C0BEE0 decides the movement animation

		// sub_C0C730 get speed

		// sub_C1DCE0 related with playing ability

		// sub_C0E740 get target creature??

		// sub_C1BE40 WALK TO??
		// arg_8 is normalized vector
		void WalkTo(int speedState, const Vector3& dstPos, const Vector3& arg_8, float goalStopDistance=1.0f, float acceptableStopDistance=2.0f);

		//TODO loc_D315AE know how much distance advances with WASD

		// virtual B0h GetAbilityCount()
		// virtual B4h cCreatureAbility* GetAbility(int index)

		// sub_D48710 play ability

	public:
		/* B10h */	bool field_B10;
		/* B14h */	int field_B14;  // not initialized
		/* B18h */	bool field_B18;
		/* B1Ch */	int field_B1C;  // not initialized
		/* B20h */	cSpeciesProfile* field_B20;  // species profile?
		/* B24h */	uint32_t mProfileSeq;
		/* B28h */	ResourceKey mSpeciesKey;
		/* B34h */	int mAge;  // 1
		/* B38h */	string16 mCreatureName;
		/* B48h */	int field_B48;
		/* B4Ch */	int field_B4C;  // cBehaviorTreeData
		/* B50h */	intrusive_ptr<cCreatureBase> mpWhoIsInteractingWithMe;
		/* B54h */	int field_B54;  // anim container?
		/* B58h */	int mGeneralFlags;  // 0x200 IsPlayerAvatar
		/* B5Ch */	bool field_B5C;
		/* B5Dh */	bool mbTeleport;
		/* B5Eh */	bool mbDead;
		/* B5Fh */	bool mbHasBeenEaten;
		/* B60h */	bool mbUpdateInteractionEffect;
		/* B61h */	bool mbUpdateMotiveEffect;
		/* B62h */	bool mbIsDiseased;
		/* B63h */	bool field_B63;
		/* B64h */	bool field_B64;  // true
		/* B65h */	bool mbColorIsIdentity;
		/* B66h */	bool field_B66;
		/* B67h */	bool mbCasted;
		/* B68h */	bool field_B68;  // true
		/* B69h */	bool field_B69;
		/* B6Ch */	int field_B6C;
		/* B70h */	int field_B70;
		/* B74h */	int mIntentionTowardsTarget;
		/* B78h */	float mNoAttackTimer;  // not initialized
		/* B7Ch */	int field_B7C;  // not initialized
		/* B80h */	float mCurrentLoudness;  // not initialized
		/* B84h */	float mFoodValue;
		/* B88h */	int mStrengthRating;  // 5
		/* B90h */	cGonzagoTimer mHungerDelayTimer;
		/* BB0h */	bool field_BB0;
		/* BB1h */	bool mbStealthed;
		/* BB4h */	int field_BB4;
		/* BB8h */	float mHungerDelta;
		/* BBCh */	float mHunger;  // 100.0
		/* BC0h */	int field_BC0;
		/* BC4h */	int field_BC4;
		/* BC8h */	int field_BC8;
		/* BCCh */	int field_BCC;  // not initialized
		/* BD0h */	int field_BD0;  // not initialized
		/* BD4h */	int field_BD4;  // not initialized
		/* BD8h */	int field_BD8;  // not initialized
		/* BDCh */	int field_BDC;  // not initialized
		/* BE0h */	Vector3 field_BE0;
		/* BECh */	bitset<88> mInUseAbilityBits;
		/* BF8h */	bitset<88> mRechargingAbilityBits;
		/* C04h */	int field_C04;
		/* C08h */	int field_C08;
		/* C0Ch */	int field_C0C;
		/* C10h */	uint64_t DEPRECATED_mInUseAbilityBits;  // not initialized
		/* C18h */	uint64_t DEPRECATED_mRechargingAbilityBits;  // not initialized
		/* C20h */	int field_C20;  // not initialized
		/* C24h */	int field_C24;  // not initialized
		/* C28h */	fixed_vector<cAbilityState, 8> mAbilityStates;
		/* CC0h */	int mLastMotiveState;
		/* CC4h */	int mLastInteractionEffect;
		/* CC8h */	UnknownCreatureClass2 field_CC8;
		/* D68h */	UnknownCreatureClass2 field_D68;
		/* E08h */	map<int, int> field_E08;
		/* E24h */	vector<int> field_E24;
		/* E38h */	bool field_E38;
		/* E3Ch */	int field_E3C;  // -1
		/* E40h */	vector<cCreatureItem> mItemInventory;
		/* E54h */	int field_E54;
		/* E58h */	float field_E58;  // PLACEHOLDER adventurer energy??
		/* E5Ch */	float field_E5C;
		/* E60h */	bool field_E60;
		/* E61h */	bool field_E61;
		/* E62h */	bool field_E62;
		/* E63h */	bool field_E63;
		/* E64h */	int field_E64;
		/* E68h */	bool field_E68;
		/* E6Ch */	int field_E6C;
		/* E70h */	int field_E70;  // -1
		/* E74h */	int field_E74;  // -1
		/* E78h */	bool field_E78;
		/* E7Ch */	int field_E7C;  // cCombatant, the same instance?
		/* E80h */	int mArchetype;
		/* E84h */	void* field_E84;
		/* E88h */	int field_E88;
		/* E8Ch */	uint32_t mCurrentAttackIdx;  // -1
		/* E90h */	uint32_t mCurrentAttackAnimId;  // -1
		/* E94h */	float field_E94;
		/* E98h */	vector<int> field_E98;
		/* EACh */	int field_EAC;
		/* EB0h */	int field_EB0[10];  // not initialized, ?? (only EB4 initialized)
		/* ED8h */	int field_ED8;
		/* EDCh */	int field_EDC;
		/* EE0h */	int field_EE0;
		/* EE4h */	int field_EE4;  // not initialized
		/* EE8h */	int field_EE8;
		/* EECh */	int field_EEC[8];
		/* F0Ch	*/	int field_F0C;
		/* F10h	*/	int field_F10;
		/* F14h	*/	int field_F14;
		/* F18h	*/	int field_F18;  // not initialized
		/* F1Ch	*/	int field_F1C;
		/* F20h	*/	char padding_F20[0x20];
		/* F40h	*/	int field_F40;
		/* F44h	*/	int field_F44;
		/* F48h	*/	int field_F48;
		/* F4Ch	*/	int field_F4C;  // not initialized
		/* F50h */	int field_F50;
		/* F54h	*/	char padding_F54[0x20];
		/* F74h	*/	int field_F74;
		/* F78h	*/	int field_F78;
		/* F7Ch	*/	int field_F7C;
		/* F80h	*/	int field_F80;
		/* F84h */	list<int> field_F84;
		/* F90h */	bool field_F90;  // true
		/* F94h */	int field_F94;
		/* F98h */	int mSpeedState;
		/* F9Ch */	int field_F9C;
		/* FA0h */	int field_FA0;
		/* FA4h */	int field_FA4;
		/* FA8h */	float field_FA8;
		/* FACh */	float field_FAC;
		/* FB0h */	float field_FB0;  // speed ?
		/* FB4h */	float field_FB4;  // speed?
		/* FB8h */	char padding_FB8[8];
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(UnknownCreatureClass) == 0x4A0, "sizeof(UnknownCreatureClass) != 4A0h");
	static_assert(sizeof(cCreatureBase) == 0xFC0, "sizeof(cCreatureBase) != FC0h");

	namespace Addresses(cCreatureBase)
	{
		DeclareAddress(PlayAnimation, SelectAddress(0xC11CD0, NO_ADDRESS, 0xC12470));
		DeclareAddress(PlayAnimationTo, SelectAddress(0xC14380, NO_ADDRESS, 0xC14B20));
		DeclareAddress(WalkTo, SelectAddress(0xC1BE40, NO_ADDRESS, 0xC1C720));
	}
}