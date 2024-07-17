#pragma once

#include <Spore\Simulator\cMission.h>
#include <Spore\Simulator\cShipBackgroundData.h>

namespace Simulator
{
	/// The kind of mission for pirate raid events. Example usage, to raid the current planet:
	/// ```cpp
	/// using namespace Simulator;
	/// auto planet = GetActivePlanetRecord();
	/// auto empireID = planet->GetStarRecord()->mEmpireID;
	/// auto empire = StarManager.GetEmpire(empireID);
	/// auto mission = MissionManager.CreateMission(id("RaidPlunderEvent"), planet, empire);
	/// auto raidEvent = object_cast<cRaidPlunderEvent>(mission);
	/// raidEvent->mNumPirates = 20;
	/// raidEvent->mNumBombers = 10;
	/// raidEvent->mpTargetPlanet = GetActivePlanet();
	/// raidEvent->AcceptMission();
	/// auto eventID = UIEventLog.ShowEvent(0x31DF9AC0, GroupIDs::SpacePopups);
	/// raidEvent->mAssociatedEventLogIDs.push_back(eventID);
	/// ```
	class cRaidPlunderEvent
		: public cMission
	{
	public:
		static const uint32_t TYPE = 0x397BFF2;
		static const uint32_t NOUN_ID = 0x397BFF3;

	public:
		/* 1F0h */	ResourceKey mPendingUFOKey;
		/* 1FCh */	bool mCanStart;
		/* 200h */	int mNumPirates;
		/* 204h */	int mNumBombers;
		/* 208h */	int mNumFighters;
		/* 20Ch */	float mDamageRemainderUFO;
		/* 210h */	float mStolenSpiceFraction;
		/* 214h */	eastl::vector<cShipBackgroundData> mBackgroundShipsList;
	};
	ASSERT_SIZE(cRaidPlunderEvent, 0x228);
}