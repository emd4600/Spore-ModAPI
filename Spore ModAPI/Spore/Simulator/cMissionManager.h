#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cMission.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\list.h>
#include <EASTL\deque.h>

#define MissionManager (*Simulator::cMissionManager::Get())

#define cMissionManagerPtr eastl::intrusive_ptr<Simulator::cMissionManager>

namespace Simulator
{
	struct UnkMissionManagerStruct
	{
		/* 00h */	int field_0;
		/* 04h */	int field_4;
		/* 08h */	vector<int> field_8;
		/* 1Ch */	vector<int> field_1C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
	};

	struct MissionManagerTimerEntry
	{
		/* 00h */	cGonzagoTimer timer;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	ResourceKey planetKey;
	};

	/// This class manages all the missions of a player in space stage.
	/// Each instance is unique for each saved game (i.e. different saved games use different instances of this class).
	/// The following fields are saved:
	/// - mbFirstCommunication
	/// - mbFlightSchoolFinished
	/// - mbMission201Finished
	/// - mTutorialTargetPlanetKeys
	/// - mTutorialSpeciesIDs
	/// - mTrackedMissions
	/// - mRecentNPCMissions
	/// - mRecentColonyMissions
	/// - mTutorialMissionStates
	class cMissionManager
		: public cGonzagoSimulator
		, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0xEE3F516E;

		static cMissionManager* Get();

		/// Creates a new mission object; the object will be a subclass of cMission,
		/// depending on the `missionType` parameter of that mission configuration property list.
		/// This method assigns the source planet, empire and planet mission to the generated mission object,
		/// and calls the `Initialize()` method.
		/// @param missionID ID of the mission to create, it must be the same ID as the mission configuration property list.
		/// @param pSourcePlanetRecord Planet where the mission is generated.
		/// @param pOwnerEmpire Empire that is assigning the mission.
		/// @param pParentMission Parent mission, this is generally null unless you want the new mission to be part of a larger, multi-step mission.
		/// @returns The created cMission subclass object, or nullptr.
		cMission* CreateMission(uint32_t missionID, cPlanetRecord* pSourcePlanetRecord, cEmpire* pOwnerEmpire, cMission* pParentMission);

		/// This function decides what mission needs to be done for the given empire.
		/// To be precise, if you communicate with empire `pEmpire` on planet `pPlanetRecord` 
		/// and ask for missions, this function is called and must return the mission to be done,
		/// or nullptr if no mission is offered.
		/// By default, this function returns null if `HasMissionsAvailable()` returns false.
		/// @param pEmpire The empire that is offering the mission.
		/// @param pPlanetRecord The planet where the mission is being offered from.
		/// @returns The offered mission object, or nullptr.
		cMission* ChooseMission(cEmpire* pEmpire, cPlanetRecord* pPlanetRecord);

		/// Decdies whether new missions can be offered by the given empire at the given planet.
		/// It returns false if:
		/// - You already have `mMaxNumMissions` active (event missions, such as pirate raids, do not count).
		/// - Another mission was requested recently on that planet (using fields `mRecentNPCMissions` and `mRecentColonyMissions`).
		/// - Based on the relationship you have with the empire on that planet.
		/// @param pEmpire
		/// @param pPlanetRecord
		/// @returns True if a new mission can be offered, false otherwise.
		bool HasMissionsAvailable(cEmpire* pEmpire, cPlanetRecord* pPlanetRecord);

		/// Returns the first existing mission object that has the given mission ID, or null if it does not exist.
		/// This can only looks for mission objects that have already been instantiated; to create a mission,
		/// use `CreateMission()`.
		/// @param missionID 
		/// @returns
		cMission* GetMissionByID(uint32_t missionID);

		/// Get the color used to track a certain mission. The mission must be currently tracked.
		/// The color will be stored in `dst` parameter.
		/// @returns True if a color was written to `dst`.
		bool GetMissionTrackColor(cMission* pMission, Color& dst);

		/// Returns true if there is an ongoing event in the given planet.
		/// @param pPlanetRecord
		/// @returns
		bool ThereIsEventInPlanet(cPlanetRecord* pPlanetRecord);

	public:
		/* 14h */	bool mbDebugDrawMissionLines;
		/* 15h */	bool field_15;
		/* 16h */	bool mbFirstCommunication;  // true
		/* 17h */	bool mbFlightSchoolFinished;
		/* 18h */	bool mbMission201Finished;
		/* 1Ch */	uint32_t mNextMissionType;
		/* 20h */	vector<UnkMissionManagerStruct> field_20;
		/* 34h */	vector<UnkMissionManagerStruct> field_34;
		/* 48h */	vector<UnkMissionManagerStruct> field_48;
		/* 5Ch */	map<uint32_t, MissionState> mTutorialMissionStates;
		/* 78h */	PropertyListPtr mpGeneratorConfigPropList;
		/* 7Ch */	PropertyListPtr mpConfigPropList;
		/* 80h */	vector<uint32_t> mTutorialTargetPlanetKeys;
		/* 94h */	vector<uint32_t> mTutorialSpeciesIDs;
		/* A8h */	vector<cMissionPtr> mTrackedMissions;
		/* BCh */	int field_BC;
		// Related with tracked missions?
		/* C0h */	cMissionPtr field_C0;
		/* C4h */	cMissionPtr field_C4;
		/* C8h */	list<MissionManagerTimerEntry> mRecentNPCMissions;
		/* D4h */	list<MissionManagerTimerEntry> mRecentColonyMissions;
		/* E0h */	int mMaxNumMissions;
		/// In milliseconds.
		/* E4h */	int mGapBetweenNPCMissions;
		/// In milliseconds.
		/* E8h */	int mGapBetweenColonyMissions;
		/* ECh */	int mMinEmpireSizeForArchetypeMissions;
		/* F0h */	ResourceKey mDefaultMissionIcon;
		/* FCh */	ResourceKey mDefaultDisasterIcon;
		/* 108h */	vector<uint32_t> mTeachingInteractMissions;
		/* 11Ch */	vector<uint32_t> mTeachingExpandMissions;
		/* 130h */	vector<uint32_t> mTeachingExploreMissions;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	ASSERT_SIZE(UnkMissionManagerStruct, 0x38);
	ASSERT_SIZE(cMissionManager, 0x144);

	namespace Addresses(cMissionManager) {
		DeclareAddress(Get);
		DeclareAddress(CreateMission);
		DeclareAddress(ChooseMission);
		DeclareAddress(HasMissionsAvailable);
		DeclareAddress(GetMissionByID);
		DeclareAddress(GetMissionTrackColor);
		DeclareAddress(ThereIsEventInPlanet);
	}
}