#pragma once

#include <Spore\Simulator\cMission.h>
#include <Spore\Simulator\cGameDataUFO.h>
#include <Spore\Simulator\cShipBackgroundData.h>

namespace Simulator
{
	/// The kind of mission for raid events. Example usage, to raid the current planet:
	/// ```cpp
	/// using namespace Simulator;
	/// auto planet = GetActivePlanetRecord();
	/// auto empireID = planet->GetStarRecord()->mEmpireID;
	/// auto empire = StarManager.GetEmpire(empireID);
	/// auto mission = MissionManager.CreateMission(id("RaidEvent"), planet, empire);
	/// auto raidEvent = object_cast<cRaidEvent>(mission);
	/// raidEvent->mpTargetPlanet = GetActivePlanet();
	/// raidEvent->mNumBombers = 10;
	/// raidEvent->AcceptMission();
	/// ```
	class cRaidEvent
		: public cMission
	{
	public:
		static const uint32_t TYPE = 0x3960C0E;
		static const uint32_t NOUN_ID = 0x3960C0A;

	public:
		/* 1F0h */	cGameDataUFOPtr mGalaxyBomber;
		/* 1F4h */	int mOriginStarRecordID;
		/* 1F8h */	int mNumBombers;
		/* 1FCh */	int mNumFighters;
		/* 200h */	ResourceKey mPendingUFOKey;
		/* 20Ch */	float mDamageRemainder;
		/* 210h */	float mDamageRemainderUFO;
		/* 214h */	bool mShouldDestroyColonyObject;
		/* 215h */	bool mWaitingForRaid;  // true
		/* 218h */	int field_218;
		/* 21Ch */	bool mUFOsLeaveOnArrival;
		/* 21Dh */	bool mInitialized;
		/* 21Eh */	bool mShowDefaultEventLog;  // true
		/* 220h */	uint32_t mTimeOfArrivalMS;
		/* 224h */	Math::Vector3 mUFOSpawnLocation;
		/* 230h */	uint32_t mAttackerEmpire;  // -1
		/* 234h */	bool mIsPlayerSummoned;
		/* 238h */	eastl::vector<int> mBackgroundShipsList;
	};
	ASSERT_SIZE(cRaidEvent, 0x250);
}