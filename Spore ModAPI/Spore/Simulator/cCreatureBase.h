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

#include <Spore\Audio\AudioSystem.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGameBundleContainer.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\UnknownCreatureClass.h>
#include <Spore\Anim\AnimatedCreature.h>
#include <Spore\Swarm\IVisualEffect.h>
#include <Spore\ResourceID.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>
#include <EASTL\hash_map.h>
#include <EASTL\fixed_hash_map.h>
#include <EASTL\bitset.h>
#include <EASTL\queue.h>

#define cCreatureBasePtr eastl::intrusive_ptr<Simulator::cCreatureBase>

namespace Simulator
{
	typedef eastl::sp_fixed_hash_map<uint32_t, IVisualEffectPtr, 4> CreatureEffectPool;
	ASSERT_SIZE(CreatureEffectPool, 0xA0);

	static_assert(sizeof(eastl::pair<uint32_t, IVisualEffectPtr>) + 4 == 0xC, "Incorrect size");

	// Maybe used in other places as well?
	class cAbilityState  // size 10h
	{
	public:
		/* 00h */	bool field_00;
		/* 01h */	bool field_01;
		/* 04h */	int field_04;
		/* 08h */	ResourceID field_08;
	};
	ASSERT_SIZE(cAbilityState, 0x10);
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
		/* 20h */	cSpatialObjectPtr mpObject;
	};

	class cCreatureAnimal;

	enum CreatureFlags
	{
		kCreatureFlagIsAlpha = 0x1,

		kCreatureFlagIsHungry = 0x100,
		kCreatureFlagIsPlayerAvatar = 0x200,
	};

	/// The base class for all creatures in the Simulator.
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

		enum SpeedType
		{
			kStandardSpeed = 2
		};

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		Anim::AnimIndex PlayAnimation(uint32_t animationID, int blockIndex = 0xFFFFFFFF, bool disableBlendInTime = false);

		Anim::AnimIndex PlayAnimationTo(uint32_t animationID, cSpatialObject* otherObject, int = 0xFFFFFFFF, int blockIndex = 0xFFFFFFFF);

		// sub_C0BEE0 decides the movement animation

		// sub_C0C730 get speed

		// sub_C1DCE0 related with playing ability

		// sub_C1BE40 WALK TO??
		// arg_8 is normalized vector
		void WalkTo(int speedState, const Vector3& dstPos, const Vector3& arg_8, float goalStopDistance=1.0f, float acceptableStopDistance=2.0f);

		//TODO loc_D315AE know how much distance advances with WASD

		// sub_C19000 get anim index for slot?

		// sub_D48710 play ability

		/// Makes the creature play an ability, the index can be obtained with GetAbilityIndexByType().
		/// If dstAnimIndex is specified, the index of the ability animation played will be written there.
		/// Does not work with skill abilties (glide, jump, mating call, sprint and sneak)
		/// @param abilityIndex
		/// @param[out] dstAnimIndex [Optional]
		void PlayAbility(int abilityIndex, Anim::AnimIndex* dstAnimIndex = nullptr);

		/// If possible, causes the creature to jump, even if the creature is already in the air.
		/// @param energyConsumed [Optional] For captains, how much energy will be consumed
		/// @returns Whether the jump was carried out
		bool DoJump(int energyConsumed = 0);

		/// For scenario captains, consumes a certain amount of energy. 
		/// If it's the player, it sends a kMsgScenarioEnergyConsumed message.
		/// @param amount
		void ConsumeEnergy(float amount);

		/// Returns the index to the first ability of the craeture that has the specified ability type.
		/// @param abilityType
		/// @returns Index to ability, or -1 if not found
		int GetAbilityIndexByType(int abilityType);

		/// Returns the target of this creature ONLY if it is a Simulator::cCreatureAnimal.
		/// @returns
		cCreatureAnimal* GetAnimalTarget();

		/// Creates an effect on the creature effect pool 1, storing it with a different ID than the effect ID.
		/// The effect will be returned in its default state, positioned in the creature, without having started.
		/// @param effectId ID of the effect to create
		/// @param poolId ID used to identify this new effect within the pool, must be used to access it in related methods.
		/// @returns The created effect, or null if the effect id is not valid.
		Swarm::IVisualEffect* CreateEffectForPool1Renamed(uint32_t effectId, uint32_t poolId);

		/// Creates an effect on the creature effect pool 1.
		/// The effect will be returned in its default state, positioned in the creature, without having started.
		/// @param effectId ID of the effect to create
		/// @returns The created effect, or null if the effect id is not valid.
		Swarm::IVisualEffect* CreateEffectForPool1(uint32_t effectId);

		/// Creates and starts an effect on the creature effect pool 1, storing it with a different ID than the effect ID.
		/// The effect will be returned in its default state, positioned in the creature, but starting it with `hardStart=0`.
		/// @param effectId ID of the effect to create
		/// @param poolId ID used to identify this new effect within the pool, must be used to access it in related methods.
		/// @returns The created effect, or null if the effect id is not valid.
		Swarm::IVisualEffect* CreateAndStartEffectForPool1Renamed(uint32_t effectId, uint32_t poolId);

		/// Creates and starts an effect on the creature effect pool 1.
		/// The effect will be returned in its default state, positioned in the creature, but starting it with `hardStart=0`.
		/// @param effectId ID of the effect to create
		/// @returns The created effect, or null if the effect id is not valid.
		Swarm::IVisualEffect* CreateAndStartEffectForPool1(uint32_t effectId);

		/// Creates an effect on the creature effect pool 2, storing it with a different ID than the effect ID.
		/// The effect will be returned in its default state, positioned in the creature, without having started.
		/// @param effectId ID of the effect to create
		/// @param poolId ID used to identify this new effect within the pool, must be used to access it in related methods.
		/// @returns The created effect, or null if the effect id is not valid.
		Swarm::IVisualEffect* CreateEffectForPool2Renamed(uint32_t effectId, uint32_t poolId);


		Swarm::IVisualEffect* StartOrStopEffectFromPool1(bool create, uint32_t effectId, uint32_t poolId);

		Swarm::IVisualEffect* StartOrStopEffectFromPool2(bool create, uint32_t effectId, uint32_t poolId);

		/// Gets an active effect from one of the effect pools of the creature. The effect is referenced with the ID
		/// that was given at its creation, which usually is the effect ID.
		/// @param poolId
		/// @returns
		Swarm::IVisualEffect* GetEffectFromPools(uint32_t poolId);

		/// Stops an effect from one of the effect pools of the creature. The effect is referenced with the ID
		/// that was given at its creation, which usually is the effect ID.
		/// @param poolId
		/// @param hardStop
		/// @returns
		Swarm::IVisualEffect* StopEffectFromPools(uint32_t poolId, int hardStop = 0);

		/// Plays a voice file on the creature (only sound, creature does not animate accordingly).
		/// Example usage: `PlayVoice("vcode_baby_born_cry", 2, 0)`
		/// @param pName
		/// @param param2
		/// @param param3
		/// @returns
		int PlayVoice(const char* pName, int param2, int param3);

		/// Returns true if the creature's diet can eat plants, that is, for herbivores and omnivores
		bool CanEatPlants();


		/* 54h */	virtual void CreateLocomotionStrategy();

		/// Called when the creature touches land after jumping/hovering in the air.
		/* 58h */	virtual void OnJumpLand();
		/// Called when the creature enters water deep enough to swim.
		/* 5Ch */	virtual void OnStartSwimming();

		/// Called every frame, parameter is the ellapsed time in milliseconds.
		/// @param deltaTime
		/* 60h */	virtual void Update(int deltaTime);

		/* 64h */	virtual void func64h(float);  // called by Update
		/* 68h */	virtual void func68h(float);  // called by Update
		/* 6Ch */	virtual void func6Ch(int deltaTime);  // called by Update
		/* 70h */	virtual void func70h(float deltaTimeSeconds);  // called by Update
		/* 74h */	virtual void func74h(void*);  // related to babies growing up
		/// Make the creature grow up and play the baby grow up effect. Will run even if the creature is already an adult.
		/* 78h */	virtual void GrowUp();
		/* 7Ch */	virtual float GetBaseMaxHitPoints() = 0;
		/* 80h */	virtual float CalculateScale(bool isBaby);
		/* 84h */	virtual void SetCreatureTarget(cCombatant* pTarget, bool, int intentionTowardsTarget);  //TODO check loc_D3242E
		/* 88h */	virtual void UpdateHunger(float deltaTimeSeconds);
		/* 8Ch */	virtual void func8Ch();  // sets dead
		/* 90h */	virtual void func90h();  // sets not dead
		/* 94h */	virtual void func94h(float);
		/* 98h */	virtual uint32_t GetLastInteractionEffect();
		/* 9Ch */	virtual void SetLastInteractionEffect(uint32_t effect);
		/* A0h */	virtual bool ForgetUpdateInteractionEffect();
		/* A4h */	virtual CreatureMotive UpdateMotiveState();  // returns new motive state
		/* A8h */	virtual bool HasUpdateMotiveEffect();
		/* ACh */	virtual bool funcACh(bool);
		/* B0h */	virtual int GetAbilitiesCount();
		/* B4h */	virtual cCreatureAbility* GetAbility(int index);
		/* B8h */	virtual bool funcB8h(cCombatant* target, int abilityIndex, Math::Vector3* hitPosition = nullptr);
		/* BCh */	virtual int funcBCh();
		/* C0h */	virtual bool funcC0h(cCreatureBase* pOtherCreature, float, float);
		/* C4h */	virtual void funcC4h();
		/* C8h */	virtual void funcC8h(bool) = 0;
		/* CCh */	virtual void funcCCh(bool);
		/* D0h */	virtual bool IsDefaultSpecies();
		/* D4h */	virtual int funcD4h();
		/* D8h */	virtual int GetCurrentBrainLevel();
		/* DCh */	virtual void SetCurrentBrainLevel(int level);
		/* E0h */	virtual const ColorRGB& GetIdentityColor() const;
		/* E4h */	virtual void SetIdentityColor(const ColorRGB& color);	

	public:
		/* B10h */	bool mHasDamageBoost;
		/* B14h */	float mDamageBoostAmount;  // not initialized
		/* B18h */	bool mHasArmorBoost;
		/* B1Ch */	float mArmorBoostAmount;  // not initialized
		/* B20h */	cSpeciesProfile* mpSpeciesProfile;
		/* B24h */	uint32_t mProfileSeq;
		/* B28h */	ResourceKey mSpeciesKey;
		/* B34h */	int mAge;  // 1
		/* B38h */	eastl::string16 mCreatureName;
		/* B48h */	int field_B48;
		/* B4Ch */	int field_B4C;  //TODO cBehaviorTreeData
		/* B50h */	cCreatureBasePtr mpWhoIsInteractingWithMe;
		/* B54h */	AnimatedCreaturePtr mpAnimatedCreature;
		/// CreatureFlags
		/* B58h */	int mGeneralFlags;
		/* B5Ch */	bool field_B5C;
		/* B5Dh */	bool mbTeleport;
		/* B5Eh */	bool mbDead;
		/* B5Fh */	bool mbHasBeenEaten;
		/* B60h */	bool mbUpdateInteractionEffect;
		/* B61h */	bool mbUpdateMotiveEffect;
		/* B62h */	bool mbIsDiseased;
		/// Setting this to true deletes the creature
		/* B63h */	bool mbMarkedForDeletion;
		/* B64h */	bool field_B64;  // true
		/* B65h */	bool mbColorIsIdentity; // if applied at runtime, requires age-up or other model reload to take effect
		/* B66h */	bool field_B66;
		/* B67h */	bool mbCasted;
		/* B68h */	bool field_B68;  // true
		/* B69h */	bool field_B69;
		/* B6Ch */	Audio::AudioTrack field_B6C;
		/* B70h */	int field_B70;
		/* B74h */	int mIntentionTowardsTarget;
		/* B78h */	float mNoAttackTimer;  // not initialized
		/// When creature is in stealth, opacity for the creature
		/* B7Ch */	float mStealthOpacity;  // not initialized
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
		/* BECh */	eastl::bitset<88> mInUseAbilityBits;
		/* BF8h */	eastl::bitset<88> mRechargingAbilityBits;
		/* C04h */	int field_C04;
		/* C08h */	int field_C08;
		/* C0Ch */	int field_C0C;
		/* C10h */	uint64_t DEPRECATED_mInUseAbilityBits;  // not initialized
		/* C18h */	uint64_t DEPRECATED_mRechargingAbilityBits;  // not initialized
		/* C20h */	int field_C20;  // not initialized
		/* C24h */	int field_C24;  // not initialized
		/* C28h */	eastl::fixed_vector<cAbilityState, 8> mAbilityStates;
		/* CC0h */	CreatureMotive mLastMotiveState;
		/* CC4h */	uint32_t mLastInteractionEffect;
		/* CC8h */	CreatureEffectPool mEffectPool1;
		/* D68h */	CreatureEffectPool mEffectPool2;
		/* E08h */	eastl::map<int, int> field_E08;  // related with audio
		/* E24h */	eastl::vector<int> field_E24;
		/* E38h */	bool field_E38;
		/* E3Ch */	int field_E3C;  // -1
		/* E40h */	eastl::vector<cCreatureItem> mItemInventory;
		/* E54h */	int field_E54;
		/// For adventurer creatures, their current energy.
		/* E58h */	float mEnergy;
		/* E5Ch */	float mMaxEnergy;
		/* E60h */	bool field_E60;
		/* E61h */	bool field_E61;
		/* E62h */	bool field_E62;
		/* E63h */	bool field_E63;
		/* E64h */	int field_E64;
		/// If true, green sparkles and smiles will emanate from the creature
		/* E68h */	bool mbMindMelded;
		/* E6Ch */	int field_E6C;
		/// Index to default attack ability, which is generally bite or its improvements (energy or poison blade)
		/* E70h */	int mDefaultAttackAbilityIndex;  // -1
		/// Index to default socialize ability, which is generally vocalize or its improvements (inspiring or harmonious song)
		/* E74h */	int mDefaultSocializeAbilityIndex;  // -1
		/* E78h */	bool field_E78;
		/* E7Ch */	cCombatant* mpCombatantTarget;  // cCombatant
		/* E80h */	int mArchetype;
		/* E84h */	void* field_E84;  // related with hunger
		/* E88h */	int field_E88;
		/// Index of current attack ability
		/* E8Ch */	uint32_t mCurrentAttackIdx;  // -1
		/* E90h */	uint32_t mCurrentAttackAnimId;  // -1
		/* E94h */	float field_E94;
		/* E98h */	eastl::vector<int> field_E98;
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
		/* F84h */	eastl::list<int> field_F84;
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
	ASSERT_SIZE(UnknownCreatureClass, 0x4A0);
	ASSERT_SIZE(cCreatureBase, 0xFC0);

	namespace Addresses(cCreatureBase)
	{
		DeclareAddress(PlayAnimation);
		DeclareAddress(PlayAnimationTo);
		DeclareAddress(WalkTo);
		DeclareAddress(GetAbilityIndexByType);  // C0B930
		DeclareAddress(GetAnimalTarget);  // C0E740
		DeclareAddress(CreateEffectForPool1Renamed);  // C1C9A0
		DeclareAddress(CreateEffectForPool1);  // C1CB10
		DeclareAddress(CreateAndStartEffectForPool1Renamed);  // C1CC80
		DeclareAddress(CreateAndStartEffectForPool1);  // C1CCB0
		DeclareAddress(CreateEffectForPool2Renamed);  // C1CCE0
		DeclareAddress(StartOrStopEffectFromPool1);  // C1FA20
		DeclareAddress(StartOrStopEffectFromPool2);  // C1CE60
		DeclareAddress(GetEffectFromPools);
		DeclareAddress(StopEffectFromPools);
		DeclareAddress(PlayVoice);  // C1CEC0
		DeclareAddress(PlayAbility);  // 0xC1DCE0 0xC1E5C0
		DeclareAddress(DoJump);  // 0xC184A0 0xC18CA0
		DeclareAddress(ConsumeEnergy);  // 0xC15780 0xC15F20
		DeclareAddress(OnJumpLand);  // 0xC14670 0xC14E10
		DeclareAddress(OnStartSwimming);  // 0xC147D0 0xC14F70
		DeclareAddress(Update);  // 0xC20C50 0xC21530
		DeclareAddress(TakeDamage);
		DeclareAddress(IsHervibore);  // 0xC0B040 0xC0B8E0
		DeclareAddress(CanEatPlants);  // 0xC0B040 0xC0B8E0
	}
}