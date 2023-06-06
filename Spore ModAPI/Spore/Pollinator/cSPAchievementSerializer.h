#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <EASTL\vector.h>
#include <EASTL\vector_map.h>
#include <EASTL\hash_set.h>

#define cSPAchievementSerializerPtr eastl::intrusive_ptr<Pollinator::cSPAchievementSerializer>

namespace Pollinator
{
	struct cAchievementDefinition
	{
		enum Flags
		{
			/// If present, the achievement will be granted automatically upon adding progress if it exceeds the trigger
			kFlagAutomatic = 1,
			kFlagGameScope = 2,

			kTriggerOpGreaterEqual = 0x000,
			kTriggerOpGreater = 0x100,
			kTriggerOpEqual = 0x200,
			kTriggerOpLess = 0x300,
			kTriggerOpLessEqual = 0x400,
			kTriggerOpNotEqual = 0x500,
			kTriggerOpMask = 0x700,
		};

		/// Flags
		/* 00h */	int mFlags;
		/* 04h */	int mProgress;
		/* 08h */	int mTriggerValue;
	};
	ASSERT_SIZE(cAchievementDefinition, 0xC);

	class cSPAchievementSerializer
		: public Simulator::ISimulatorSerializable
		, public RefCountTemplate
	{
	public:
		struct CrossGameData
		{
			/* 00h */	eastl::hash_set<uint32_t> mCellGameIDs;
			/* 20h */	eastl::hash_set<uint32_t> mEncounteredCreatures;
			/* 40h */	eastl::hash_set<uint32_t> mEatenCreatures;
			/* 60h */	eastl::hash_set<uint32_t> mTribeGamesCompleted;
		};
		ASSERT_SIZE(CrossGameData, 0x80);

		/* 0Ch */	eastl::vector_map<uint32_t, cAchievementDefinition> mAchievements;
		/* 24h */	eastl::vector<int> mAchievementSet;
		/* 38h */	int field_38;  // not initialized
		/* 3Ch */	CrossGameData mCrossGameData;
	};
	ASSERT_SIZE(cSPAchievementSerializer, 0xBC);
}