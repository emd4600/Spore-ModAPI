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
		/* 0 */	kMissionFlagIsEvent = 1,
		/* 1 */	kMissionFlagHideStarName = 2,
		/* 2 */	kMissionFlagHidePlanetName = 4,
		/* 3 */	kMissionFlagIsTutorial = 8,
		/* 4 */	kMissionFlagCannotAbort = 0x10,
		/* 5 */	kMissionFlagTimerStartsOnFirstEntry = 0x20,
		/* 7 */	kMissionFlagIsAdventure = 0x80,
	};

	enum class MissionState 
	{
		/// When the mission hasn't been accepted yet, and player is in the initial conversation
		Unaccepted = 0,
		/// The mission has been finished (not necessarily completed). After this, the mission is destroyed.
		Finished = 1,
		/// The player just accepted the mission, but it hasn't started yet.
		/// It calls cMission::OnMissionAccept() and immediately transitions to MissionState::Active
		Accepted = 2,
		/// The mission is currently active. While the mission is in this state, it receives calls to Update()
		Active = 3,
		/// The player has successfully completed the mission. It calls cMission::OnMissionCompleted() and immediately 
		/// transitions to MissionState::Finished, or to MissionState::StepCompleted if this is a sub-mission of a bigger mission.
		Completed = 5,
		/// The player has failed the mission.
		/// It calls cMission::OnMissionFailed() and immediately transitions to MissionState::Finished
		Failed = 6,
		/// The mission has been aborted. 
		/// It calls cMission::OnMissionAbort() and immediately transitions to MissionState::Finished
		Aborted = 7,
		/// The mission has been rejected. 
		/// It calls cMission::OnMissionReject() and immediately transitions to MissionState::Finished
		Rejected = 8,
		/// When this mission is only a step of a bigger mission, and the step gets completed
		StepCompleted = 9
	};

	enum class LandmarkStarType
	{
		Here = 0,
		Star = 1,
		Wormhole = 2,
		BigStar = 3,
		RedStar = 4,
		ProtoPlanetaryStar = 5,
		GalacticCore = 6
	};

	enum class LandmarkPlanetType
	{
		AsteroidBelt = 0,
		GasGiant = 1,
		T0 = 2,
		T1 = 3,
		T2 = 4,
		T3 = 5
	};

	struct cStarClue
	{
		/// -1 is disabled, 0 is for landmarks that are closer than 2 units, 1 for farther than 2 units, there might be other types
		/* 00h */	int mType;  // -1
		/* 04h */	float mDistance;
		/* 08h */	vector<LandmarkStarType> mLandmarkTypes;
		/* 0Ch */	vector<cStarRecordPtr> mLandmarkStars;
	};

	struct cPlanetClue
	{
		/* 00h */	int mType;
		/* 04h */	LandmarkPlanetType mPlanetType;
		/* 08h */	int mOrbitOrder;
	};

	/// Base class for all missions, this class cannot be instantiated.
	class cMission
		: public cGameData
		, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x2AA5ADA;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Changes the state of the mission. Sets `mTitle` and `field_15C` to an empty string.
		/// If the new state is MissionState::Active, emits a SimulatorMessages::kMsgMissionUpdate message.
		/// @param state
		void SetState(MissionState state);

		/// Returns the empire that created this mission. This will return `mpOwnerEmpire`, or
		/// set it to the empire of `mpOwnerEmpireID` if not set.
		/// @returns
		cEmpire* GetOwnerEmpire();

		/// Returns the target empire of this mission. This will return `mpTargetEmpire`, or
		/// set it to the empire of `mpTargetEmpireID` if not set.
		/// @returns
		cEmpire* GetTargetEmpire();

		/// Sets the target empire of this mission.
		/// @param pEmpire
		void SetTargetEmpire(cEmpire* pEmpire);

		/* 60h */	virtual int GetState();
		/* 64h */	virtual bool func64h();  // field_38.IsRunning()
		// Called by sub_E13A70
		/* 68h */	virtual bool func68h();  // field_58.IsRunning()
		/* 6Ch */	virtual void func6Ch();  //TODO start?
		/* 70h */	virtual void func70h();  // field_58.Start()
		/* 74h */	virtual uint32_t GetCardWindowControlID();  // returns a window controlID
		/* 78h */	virtual void Initialize();  // related with parsing prop, called when mission is created

		/// Only called when state is Active, called every frame. Default behaviour:
		/// 1. Updates `mElapsedTimeMS`, and if it is greater than the mission max duration, fails the mission.
		/// 2. Calls func168h()
		/// 3. Updates clocks `field_38` and `field_58`, and sends message `0x38CF2FD` sometimes
		/// 4. If `field_18C` and player is in galaxy context, calls func1A0h()
		/// @param deltaTime
		/// @returns New state of the mission.
		/* 7Ch */	virtual MissionState Update(int deltaTime);

		/// Loads prop file
		/* 80h */	virtual void Load();

		/// Calling when destroying the mission, if `mSystemsShutdown` is false.
		/* 84h */	virtual void ShutdownSystems();

		/// Called when the player accepts the mission.
		/* 88h */	virtual void OnMissionAccept();

		/// Called when the mission is rejected.
		/* 8Ch */	virtual void OnMissionReject();

		/// Called when the mission is aborted.
		/* 90h */	virtual void OnMissionAbort();

		/// Called when the mission is completed. Default behaviour:
		/// 1. If mission is a tutorial, it changes MissionManager.mTutorialMissionStates
		/// 2. If mission is an adventure, advances some variable on player empire
		/// 3. Unlocks (or gives?) the tools in `mUnlockToolIDList`
		/// 4. Unlocks (or gives?) the tool in `mRewardToolID`
		/// 5. Adds `mRewardMoney` to player empire money
		/// 6. Applies empire relationships
		/// ... more things ...
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
		/* B4h */	virtual void GetTargetAnimalSpeciesNameText(string16& dst);
		/* B8h */	virtual void GetTitleText(string16& dst);
		/* BCh */	virtual void GetUIMediumDescText(string16& dst);
		/* C0h */	virtual void GetUILongDescText(string16& dst);
		/* C4h */	virtual void funcC4h(string16& dst);  // calls GetUILongDescText
		/// "Mission" or "Alert" 
		/* C8h */	virtual void GetAlertTitleText(string16& dst);
		/* CCh */	virtual void GetStarClueText(int index, string16& dst);
		/* D0h */	virtual void GetStarClueDistanceText(string16& dst);
		/* D4h */	virtual void GetStarClueRangeMinText(string16& dst);
		/* D8h */	virtual void GetStarClueRangeMaxText(string16& dst);
		/* DCh */	virtual void GetPlanetClueOrbitOrderText(string16& dst);
		/* E0h */	virtual void GetPlanetClueText(string16& dst);
		/* E4h */	virtual uint32_t GetStarMapEffectGroup();
		/* E8h */	virtual uint32_t GetStarMapEffect();

		/// Returns how much money it costs to travel from the source planet to the target planet and back.
		/* ECh */	virtual int GetTravelCost();

		/// Returns how much distance to travel from the source planet to the target planet and back.
		/* F0h */	virtual float GetTravelDistance();

		/// Returns true if the given planet is the target planet of the mission, or false otherwise.
		/// @param pPlanetRecord
		/* F4h */	virtual bool IsTargetPlanet(cPlanetRecord* pPlanetRecord);

		/* F8h */	virtual bool HasBeenFulfilled();  // returns false
		/* FCh */	virtual bool HasFailed();  // returns false
		/* 100h */	virtual bool func100h();  // returns false
		/* 104h */	virtual bool func104h();  // is timed mission? //elapsed time is running?
		/* 108h */	virtual int func108h();
		// returns mission_complete, mission_failed or mission_incomplete
		/* 10Ch */	virtual uint32_t func10Ch();
		// by default parameters are ignored, dynamic_response_to_source is returned if not event
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

		/// Creates the star and planet clues for finding landmarks, only if they are not disabled with the
		/// `kMissionFlagHideStarName` and `kMissionFlagHidePlanetName` flags.
		/// @returns
		/* 128h */	virtual bool CreateClues();

		/// Chooses one nearby star where a landmark must be found, and enables the `mStarClue` accordingly.
		/// The maximum star distance is determined by the property `missionLandmarkSearchRadius`
		/// @returns
		/* 12Ch */	virtual bool CreateStarClue();  // HideStarName?

		/* 130h */	virtual bool CreatePlanetClue();  // similar to ChooseLandmarkStar but with planets? HidePlanetName?

		/// Returns true if the mission is Active or Complete, and the given empire and planet are
		/// the empire and planet where the mission originated.
		/// @param empireId
		/// @param planetId
		/// @returns
		/* 134h */	virtual bool IsSourcePlanetAndEmpire(uint32_t empireId, PlanetID planetId);

		/// Checks if the player has enough available cargo slots in the inventory to give the
		/// animals and plants of the mission (`mGiveOnAcceptAnimalIDs` and `mGiveOnAcceptPlantIDs`).
		/// @returns True if it has enough cargo slots, false otherwise.
		/* 138h */	virtual bool HasEnoughAvailableCargoSlots();

		/* 13Ch */	virtual bool func13Ch();  // true
		/* 140h */	virtual bool func140h(int, int);  // false

		/// Adds this mission as listener to some game messages.
		/// By default, it listens to `0x35EC3DE`, `0x248975F`, `0x2489760`, `0x4249453`
		/* 144h */	virtual void AddMessageListeners();
		/* 144h */	virtual void RemoveMessageListeners();

		/* 14Ch */	virtual void AddMessageListener(uint32_t messageId);
		/* 150h */	virtual void RemoveMessageListener(uint32_t messageId);

		/// Returns true if the mission is a listener to the given game internal message.
		/// @param messageId
		/// @returns
		/* 154h */	virtual bool ListensToMessage(uint32_t messageId);

		/* 158h */	virtual bool func158h();  // false
		/* 15Ch */	virtual bool func15Ch();  // nothing
		/* 160h */  virtual int func160h();
		/* 164h */  virtual int func164h();
		/* 168h */  virtual bool func168h();
		/* 16Ch */  virtual void func16Ch();  // nothing

		/// Reads properties `missionExportTargetPlanetTo` and `missionExportTargetSpeciesTo`. If set,
		/// it sets the mission target planet and species id as the tutorial ones in MissionManager.
		/* 170h */	virtual void ExportTargetPlanetAndSpecies();

		/* 174h */  virtual void func174h(int);  // nothing
		/* 178h */  virtual uint32_t func178h();  // returns property 5D6796FD
		/* 17Ch */	virtual uint32_t GetCreatureGoalCardLayoutId();
		/* 180h */	virtual bool func180h();  // false
		/* 184h */	virtual float func184h(int, int);

		/* 188h */	virtual int CalculateMissionDuration();
		
		/// Sets `mTargetAnimalSpecies` and `mTargetAnimalSpeciesKey`. By default, it
		/// just picks a random creature from the planet.
		/// @return 
		/* 18Ch */	virtual bool PickTargetAnimalSpecies();

		/* 190h */	virtual void func190h(const ResourceKey& speciesId);  // calls PickTargetAnimalSpecies
		/* 194h */	virtual void func194h();
		/* 198h */	virtual bool func198h(bool);
		/* 19Ch */	virtual void func19Ch();
		/* 1A0h */	virtual void func1A0h(bool);

	public:
		/* 38h */	cGonzagoTimer field_38;
		/* 58h */	cGonzagoTimer field_58;
		/* 78h */	uint32_t mMissionID;
		/* 7Ch */	unsigned int mElapsedTimeMS;
		/* 80h */	int mDuration;
		/* 84h */	MissionState mState;
		/* 88h */	bool mSystemsShutdown;
		/* 8Ch */	uint32_t mOwnerEmpireID;  // -1
		/// Owner empire. Use GetOwnerEmpire()
		/* 90h */	cEmpirePtr mpOwnerEmpire;
		/* 94h */	uint32_t mTargetEmpireID;  // -1
		/// Owner empire. Use GetTargetEmpire() and SetTargetEmpire()
		/* 98h */	cEmpirePtr mpTargetEmpire;
		/* 9Ch */	cPlanetPtr mpSourcePlanet;
		/* A0h */	float mRewardMoney;
		/* A4h */	ResourceKey mRewardToolID;
		/* B0h */	LocalizedString field_B0;
		/* C4h */	cStarClue mStarClue;
		/* F4h */	cPlanetClue mPlanetClue;
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
		/* 1D0h */	vector<uint32_t> field_1D0;
		/* 1E4h */	cCommEventPtr mpGalaxyCommEvent;
		/* 1E8h */	cPlanetPtr mpTargetPlanet;
	};
	ASSERT_SIZE(cMission, 0x1F0);

	namespace Addresses(cMission)
	{
		DeclareAddress(SetState);  // 0xC47C40
		DeclareAddress(GetOwnerEmpire);  // 0xC44930
		DeclareAddress(GetTargetEmpire);  // 0xC449F0
		DeclareAddress(SetTargetEmpire);  // 0xC449A0
	}
}
