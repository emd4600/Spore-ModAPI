#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cCommEvent.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\MathUtils.h>
#include <Spore\LocalizedString.h>

#define cMissionPtr eastl::intrusive_ptr<Simulator::cMission>

namespace Simulator
{
	enum MissionFlags
	{
		kMissionFlagIsEvent = 1,
		kMissionFlagHideStarName = 2,
		kMissionFlagHidePlanetName = 4,
		kMissionFlagIsTutorial = 8,
		kMissionFlagCannotAbort = 0x10,
		kMissionFlagTimerStartsOnFirstEntry = 0x20,
		kMissionFlagIsAdventure = 0x80,
	};

	enum class MissionState 
	{
		/// When the mission hasn't been accepted yet, and player is in the initial conversation
		Unaccepted = 0,
		/// The mission has been finished (not necessarily completed). After this, the mission is destroyed.
		Finished = 1,
		/// The player just accepted the mission, but it hasn't started yet.
		/// It immediately transitions to MissionState::Active
		Accepted = 2,
		/// The mission is currently active. While the mission is in this state, it receives calls to Update()
		Active = 3,
		/// The player has successfully completed the mission. It immediately transitions to MissionState::Finished,
		/// or to MissionState::StepCompleted if this is a sub-mission of a bigger mission.
		Completed = 5,
		/// The player has failed the mission. It immediately transitions to MissionState::Finished
		Failed = 6,
		/// The mission has been aborted. It immediately transitions to MissionState::Finished
		Aborted = 7,
		/// The mission has been aborted. It immediately transitions to MissionState::Finished
		Rejected = 8,
		/// When this mission is only a step of a bigger mission, and the step gets completed
		StepCompleted = 9
	};

	class cMission
		: public cGameData
		, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x2AA5ADA;

		//TODO GetOwnerEmpire, GetTargetEmpire C44930
		//TODO SetState

		/* 60h */	virtual int GetState();
		/* 64h */	virtual bool func64h();  // field_38.IsRunning()
		/* 68h */	virtual bool func68h();  // field_58.IsRunning()
		/* 6Ch */	virtual void func6Ch();  //TODO start?
		/* 70h */	virtual void func70h();  // field_58.Start()
		/* 74h */	virtual uint32_t GetCardWindowControlID();  // returns a window controlID
		/* 78h */	virtual void Initialize();  // related with parsing prop, called when mission is created
		/// Only called when state is 3, called every frame.
		/* 7Ch */	virtual MissionState Update(int deltaTime);
		/// Loads prop file
		/* 80h */	virtual void Load();
		/* 84h */	virtual void func84h();

		/// Called when the player accepts the mission.
		/* 88h */	virtual void OnMissionAccept();

		/// Called when the mission is rejected.
		/* 8Ch */	virtual void OnMissionReject();

		/// Called when the mission is aborted.
		/* 90h */	virtual void OnMissionAbort();

		/// Called when the mission is completed.
		/* 94h */	virtual void OnMissionCompleted();

		/// Called when the mission is failed.
		/* 98h */	virtual void OnMissionFailed();

		/// Causes this mission to fail. 
		/* 9Ch */	virtual void FailMission();

		/// Returns a description for this mission, usually the `description` property in the prop list.
		/// @param dst The string where the description will be stored
		/* A0h */	virtual string16* GetDescription(string16* dst);

		/// Returns the ID of a `.cnv` conversation file used for the mission.
		/// If the mission has a parent, it will return the conversation of the parent.
		/* A4h */	virtual uint32_t GetConversationID();

		/// Returns how much time the mission can last, in milliseconds. 0 if there is no time limit.
		/* A8h */	virtual int GetDuration();

		/// For missions with a time limit, returns how much time is left (duration - elapsedTime). Otherwise, returns 0.
		/* ACh */	virtual int GetRemainingTime();

		/* B0h */	virtual cSpeciesProfile* GetTargetAnimalSpecies();

		/* E4h */	virtual uint32_t GetStarMapEffectGroup();
		/* E8h */	virtual uint32_t GetStarMapEffect();
		/// Returns how much money it costs to travel from the source planet to the target planet and back.
		/* ECh */	virtual int GetTravelCost();
		/// Returns how much distance to travel from the source planet to the target planet and back.
		/* F0h */	virtual float GetTravelDistance();
		/// Returns true if the given planet is the target planet of the mission, or false otherwise.
		/* F4h */	virtual bool IsTargetPlanet(cPlanetRecord* pPlanetRecord);
		/* F8h */	virtual bool funcF8h();  // returns false
		/* FCh */	virtual bool funcFCh();  // returns false
		/* 100h */	virtual bool func100h();  // returns false
		/* 104h */	virtual bool func104h();
		/* 108h */	virtual int func108h();
		/* 10Ch */	virtual uint32_t func10Ch();
		/* 110h */	virtual uint32_t func110h(int, int);
		/* 114h */	virtual void func114h();  // nothing

		/// Called by the space token translator, used to replace special tokens in localized texts.
		/// For example, it is used to provide the target planet name, target species, etc
		/// @param tokenID id of the token (the token is a text, this is the FNV hash)
		/// @param dst Where the token text must be written.
		/// @returns True if the token was processed, false otherwise.
		/* 118h */	virtual bool TranslateToken(uint32_t tokenID, string16& dst);
		/// By default, `event_log_return_for_rewards`
		/* 11Ch */	virtual uint32_t GetCompletedEventLogID();
		/* 120h */	virtual bool func120h();  // returns false
		/* 124h */	virtual void func120h(int);  // nothing
		/* 128h */	virtual bool func128h();

	public:
		/* 38h */	cGonzagoTimer field_38;
		/* 58h */	cGonzagoTimer field_58;
		/* 78h */	uint32_t mMissionID;
		/* 7Ch */	unsigned int mElapsedTimeMS;
		/* 80h */	int mDuration;
		/* 84h */	int mState;
		/* 88h */	bool mSystemsShutdown;
		/* 8Ch */	uint32_t mOwnerEmpireID;  // -1
		/// Owner empire. Use GetOwnerEmpire
		/* 90h */	cEmpirePtr mpOwnerEmpire;
		/* 94h */	uint32_t mTargetEmpireID;  // -1
		/// Owner empire. Use GetTargetEmpire
		/* 98h */	cEmpirePtr mpTargetEmpire;
		/* 9Ch */	cPlanetPtr mpSourcePlanet;
		/* A0h */	float mRewardMoney;
		/* A4h */	ResourceKey mRewardToolID;
		/* B0h */	LocalizedString field_B0;
		/* C4h */	int mStarClue;  // -1  //TODO cStarClue
		/* C8h */	int field_C4;
		/* CCh */	vector<int> field_CC;
		/* E0h */	vector<ObjectPtr> field_E0;
		/* F4h */	int mPlanetClue;  //TODO cPlanetClue
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	uint32_t mStarMapIconEffectID;
		/* 104h */	int field_104;
		/* 108h */	vector<int> field_108;
		/* 11Ch */	vector<ResourceKey> mUnlockToolIDList;
		/* 130h */	int mFlags;
		/* 134h */	vector<int> field_134;
		/* 148h */	uint32_t mProgressEventID;  // -1
		/* 14Ch	*/	string16 mTitle;
		/* 15Ch	*/	string16 field_15C;
		/* 16Ch */	cSpeciesProfile* mTargetAnimalSpecies;
		/* 170h */	ResourceKey mTargetAnimalSpeciesKey;
		/* 17Ch */	cMissionPtr mpParentMission;
		/* 180h */	PropertyListPtr mpPropList;
		/* 184h */	int mAcceptCost;
		/* 188h */	int mToolCost;
		/* 18Ch */	bool field_18C;
		/* 190h */	int mGiveOnAcceptMoney;
		/* 194h */	vector<ResourceKey> mGiveOnAcceptToolIDs;
		/* 1A8h */	vector<ResourceKey> mGiveOnAcceptAnimalIDs;
		/* 1BCh */	vector<ResourceKey> mGiveOnAcceptPlantIDs;
		/* 1D0h */	vector<int> field_1D0;
		/* 1E4h */	cCommEventPtr mpGalaxyCommEvent;
		/* 1E8h */	cPlanetPtr mpTargetPlanet;
	};
	ASSERT_SIZE(cMission, 0x1F0);
}