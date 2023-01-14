#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cNest.h>
#include <Spore\Simulator\cEgg.h>

#define cHerdPtr eastl::intrusive_ptr<Simulator::cHerd>

namespace Simulator
{
	//TODO
	/*enum class CreaturePersonality
	{
		None = 0,
		EpicPredator = 1,
		Migrator = 2,
		Decorator = 3,
		Monkey = 4,
		Stalker = 5,
		Guard = 6,
		Pet = 7,
		WaterPredator = 8,
		Carcass = 9
	};*/

	class cHerd
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x52AA6117;
		static const uint32_t NOUN_ID = 0x1BE418E;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		cHerd* Create(const Vector3& position, cSpeciesProfile* pSpeciesProfile, int herdSize, 
			bool isOwnedByAvatar, int creaturePersonality, bool createNest);

		void SetEnabled(bool enabled);

	public:
		/* 34h */	Vector3 mInitialPosition;
		/* 40h */	eastl::vector<cCreatureAnimalPtr> mHerd;
		/* 54h */	eastl::vector<cEggPtr> mEggs;
		/* 68h */	eastl::vector<Vector3> mFeedingGrounds;
		/* 7Ch */	bool mbCheckedForForests;
		/// Index to `mFeedingGrounds`, maybe? Default is -1
		/* 80h */	int mCurrentFeedingGrounds;  // -1
		/* 84h */	bool mOwnedByAvatar;
		/* 85h */	bool mbShouldEvolve;  // true
		/* 88h */	int mArchetype;  //TODO
		/* 8Ch */	int mArchetypeGroup;
		/* 90h */	int mScheduleIndex;
		/* 94h */	float mDNAEvolutionThreshold;
		/* 98h */	ResourceKey mOwnerSpeciesKey;
		/* A4h */	cSpeciesProfile* mpSpeciesProfile;
		/* A8h */	eastl::fixed_vector<ResourceKey, 4> mEvolvedSpeciesProfileKeys;
		/* F0h */	int mGeneration;
		/* F4h */	int mTargetHerdSize;
		/* F8h */	int mInitialShortfall;
		/* FCh */	bool mbEggStatusChanged;
		/* 100h */	int mNumGuards;
		/* 104h */	int field_104;
		/* 108h */	float mTerritoryRadius;
		/* 10Ch */	int mNumGuardLocations;
		/* 110h */	int mNumGuardsPerLocation;
		/* 114h */	Vector2 mGuardMinMaxRadius;
		/* 11Ch */	int mRespawnRate;
		/* 120h */	int mActivateBrainLevel;
		/* 124h */	int mDeactivateBrainLevel;
		/* 128h */	bool field_128;  // true
		/* 12Ch */	int mEggIndex;
		/* 130h */	cGonzagoTimer field_130;
		/* 150h */	float mScaleMultiplier;
		/* 154h */	float mHitpointOverride;
		/* 158h */	float mDamageMultiplier;
		/* 15Ch */	int mCreaturePersonality;  //TODO CreaturePersonality?
		/* 160h */	cNestPtr mpNest;
		/* 164h */	cCreatureAnimalPtr mpHerdMom;
		/* 168h */	int _padding_168[10];  // this is something related with cBehaviorTreeData and "Simulator/list"
		/* 190h */	bool mbExtinction;
		/* 191h */	bool mbBestFriends;
		/* 192h */	bool mbTransientHerd;
		/* 194h */	cCreatureAnimalPtr mpEggLayer;
		/* 198h */	bool mbEggsInNest;
		/* 1A0h */	cGonzagoTimer field_1A0;
		/* 1C0h */	cGonzagoTimer mChangeFeedingGroundsTimer;
		/* 1E0h */	eastl::vector<int> mValidLocations;
		/* 1F4h */	eastl::vector<int> field_1F4;
		/* 208h */	bool mbCheckedForWateringHole;
		/* 20Ch */	Vector3 mWateringHolePosition;
		/* 218h */	bool mbEnabled;
	};
	ASSERT_SIZE(cHerd, 0x220);

	namespace Addresses(cHerd)
	{
		DeclareAddress(Create);  // 0xB237C0
	}
}