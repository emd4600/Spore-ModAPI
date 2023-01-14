#pragma once

#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cCreatureCitizen.h>
#include <EASTL\fixed_vector.h>

#define cTribePlannerPtr eastl::intrusive_ptr<Simulator::cTribePlanner>

namespace Simulator
{
	class cTribe;

	/// Read from a `.prop` file in folder `TribePlans`
	struct cTribePlanProperties
	{
		/// Property `InitialDelay`
		/* 00h */	float mInitialDelay;
		/// Property `CheckTime`
		/* 04h */	float mCheckTime;
		/// Property `0xCD927E7C`
		/* 08h */	float field_08;
		/// Property `Frequency`
		/* 0Ch */	float mFrequency;
		/// Each bit represents a tool index. Property `RequiredTools`.
		/* 10h */	int mRequiredTools;
		/// Each bit represents a tool index. Property `DesiredTools`.
		/* 14h */	int mDesiredTools;
		/// Property `NumRequiredTribeMembers`
		/* 18h */	int mNumRequiredTribeMembers;
		/// Property `NumDesiredTribeMembers`
		/* 1Ch */	int mNumDesiredTribeMembers;
		/// Property `0xF90F8D19`
		/* 20h */	int field_20;
		/// Property `0x6CF6D7B7`
		/* 24h */	int field_24;
		/// Property `0x2B374411`
		/* 28h */	int field_28;
		/// Property `0xE32953B7`
		/* 2Ch */	int field_2C;
		/// Property `FoodRate`
		/* 30h */	float mFoodRate;
		/// Property `RequiredFood`
		/* 34h */	int mRequiredFood;
		/// Property `DesiredFood`
		/* 38h */	int mDesiredFood;
		/// Property `0x5D153EE8`
		/* 3Ch */	bool field_3C;
		/* 40h */	PropertyListPtr mpPropList;
	};
	ASSERT_SIZE(cTribePlanProperties, 0x44);

	struct cTribePlan
	{
		/* 00h */	uint32_t mID;
		/* 04h */	int mState;
		/* 08h */	int mFrequency;
		/* 0Ch */	float mCheckTime;
		/* 10h */	int mFoodRequired;
		/* 14h */	int mFoodAccumulated;
		/* 18h */	bool mbCheck;
		/* 1Ch */	eastl::fixed_vector<cCreatureCitizenPtr, 8> mWorkers;
		/* 54h */	cTribePlanProperties* mpProperties;
	};
	ASSERT_SIZE(cTribePlan, 0x58);

	class cTribePlanner
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0x9098AEB2;
		static const uint32_t NOUN_ID = 0x3098AF98;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 10h */	int mpBehaviorTreeData;  //TODO cBehaviorTreeData
		/// Plans from `TribePlans` folder decide the behavior of the tribe. The plans are selected in the Tribe Archetype file.
		/* 14h */	eastl::vector_map<TribePlanType, eastl::vector<cTribePlan>> mPlans;
		/* 2Ch */	eastl::fixed_vector<float, 48 / 4> mTimeBetweenPlanExecutionByType;
		/* 74h */	eastl::intrusive_ptr<cTribe> mpTribe;
		/* 78h */	float mAccumulatedDeltaTime;
	};
	ASSERT_SIZE(cTribePlanner, 0x7C);
}