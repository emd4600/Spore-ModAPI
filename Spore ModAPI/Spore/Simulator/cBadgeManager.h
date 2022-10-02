#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\App\PropertyList.h>
#include <Spore\LocalizedString.h>

//TODO #define BadgeManager ?

#define cBadgeManagerPtr eastl::intrusive_ptr<Simulator::cBadgeManager>

namespace Simulator
{
	class cBadgeManager
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0x2CB0EDE;

	public:
		/// Maps the file ID to the PropertyList, for each badge in space_badges~ (0x2CB089D)
		/* 10h */	map<uint32_t, PropertyListPtr> mBadges;
		/// Tracks the state of each badge (wether its unlocked, in progress, etc)
		/* 2Ch */	map<uint32_t, int> mBadgeMap;
		/* 48h */	map<int, int> mStageMap;
		/// Counts how many events of a certain kind have happened, used to know when to give a badge
		/* 64h */	map<BadgeManagerEvent, int> mEventCounts;
		/* 80h */	hash_map<int, int> field_80;
		/* A0h */	bool field_A0;
		/* A4h */	uint32_t mCurrentBadgeCard;
		/* A8h */	int field_A8;
		/* ACh */	LocalizedString field_AC;
	};
	ASSERT_SIZE(cBadgeManager, 0xC0);
}