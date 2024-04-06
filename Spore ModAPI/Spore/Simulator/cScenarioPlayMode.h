#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\Simulator\cScenarioGoal.h>
#include <Spore\Audio\AudioSystem.h>
#include <Spore\MathUtils.h>
#include <EASTL\string.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>

#define cScenarioPlayModePtr eastl::intrusive_ptr<Simulator::cScenarioPlayMode>

namespace Simulator
{
	class cScenarioPlayModeGoal
	{
	public:
		/* 00h */	bool mIsCompleted;
		/* 01h */	bool field_1;  // true if goal is collect, bring or allyWith
		/// How many of the tasks in this goal have been completed
		/* 04h */	int mCount;
		/// Maps cGameData ID to ??
		/* 08h */	eastl::map<uint32_t, int> field_8;
		/* 24h */	cScenarioGoal mGoal;
	};
	ASSERT_SIZE(cScenarioPlayModeGoal, 0x1AC);

	struct cScenarioPlaySummary
	{
		/* 00h */	int mNumCreaturesKilled;
		/* 04h */	int mNumBuildingsDestroyed;
		/* 08h */	int mNumVehiclesDestroyed;
		/* 0Ch */	int mNumCastMembersDefended;
		/* 10h */	int mNumCreaturesBefriended;
		/* 14h */	int mNumObjectsCollected;
		/* 18h */	int field_18;
		/* 1Ch */	int mNumGoalsCompleted;
		/* 20h */	int mNumDeaths;
		/* 24h */	int mNumPosseMembersLost;
		/* 28h */	int mAmountDamageDealt;
		/* 2Ch */	int mNumTimesUsedJetPack;
		/* 30h */	int mNumTimesUsedSprint;
		/* 34h */	int mNumBarrelsDestroyed;
		/* 38h */	int mNumCastMembersTalkedTo;
		/* 3Ch */	float mAmountHealthRegained;
		/* 40h */	float mAmountDamageReceived;
		/* 44h */	float mAmountEnergyUsed;
	};
	ASSERT_SIZE(cScenarioPlaySummary, 0x48);

	class cScenarioPlayMode
		: public App::IUnmanagedMessageListener
		, public DefaultRefCounted
	{
	public:
		//TODO check sub_F1EFC0
		
		void Initialize();
		void SetCurrentAct(int actIndex, bool = false);
		void JumpToAct(int actIndex);
		void SetState(ScenarioPlayModeState state);


	public:
		/* 0Ch */	cScenarioPlaySummary mSummary;
		/* 54h */	eastl::string16 mFailReason;
		/// Goals for the current act
		/* 64h */	eastl::vector<cScenarioPlayModeGoal> mCurrentGoals;
		/* 78h */	int field_78;  // not initialized
		/* 7Ch */	App::MessageListenerData mMessageListenerData;
		/// Current state of the adventure play mode.
		/// 0 is pre-init in editor play mode, 1 is intro, 2 seems to be pre-init in quick-play, 3 is gameplay, 5 is adventure completed and 6 is adventure failed (death or failed/invalid goals)
		/* 90h */	ScenarioPlayModeState mCurrentPlayModeState; // not initialized
		/// Controls what state the ending cinematic of the adventure is in. Set to 0 when ending procedure begins, 1 when cinematic activates, and 2 after player leaves the cinematic sequence.
		/* 94h */	int mCurrentEndCinematicState; // not initialized
		/// The clock activates when mCurrentEndCinematicState is set to 0. It counts up to around 2000 units (milliseconds),  after which the ending cinematic activates and mCurrentEndCinematicState is set to 1.
		/* 98h */	Clock mCinematicDelay;
		/* B0h */	int field_B0;  // not initialized
		/* B4h */	int field_B4;  // not initialized
		/// Index of the current act (0 is first act, 1 is second, etc)
		/* B8h */	int mCurrentActIndex;  // not initialized
		/// Time limit of the current act, in milliseconds (negative number if no time limit)
		/* BCh */	long mTimeLimitMS;
		/// The playtime of the current adventure in milliseconds. It pauses counting when the game is paused, and it records its count to display it at the results screen. 
		/// If the adventure is shared, it will also be sent to the adventure's high scores in the Spore servers if the player is logged in.
		/* C0h */	int mCurrentTimeMS;
		/// The amount of Spore points the captain is rewarded at the end of a successful adventure.
		/* C4h */	int mAdventurePoints; // not initialized
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	int field_CC;  // not initialized
		/* D0h */	int field_D0;  // not initialized
		/// Index of the dialog box being displayed during talk-to goal cinematic (-1 is the initial fade-in + creature greeting animation, 0 is first dialog box, 1 is second etc.)
		/* D4h */	int mCurrentDialogBoxIndex;  // not initialized
		/* D8h */	int field_D8;  // not initialized
		/// Used for move-to goals. Distance of the nearest target to the player.
		/* DCh */	float mDistanceToClosestMoveToTarget;
		/// Coordinates of the move-to goal target's location.
		/* E0h */	Math::Vector3 mMoveToGoalLocation;
		/* ECh */	bool field_EC;
		/* F0h */	Audio::AudioTrack mMusicTrack;
		/* F4h */	uint32_t mCurrentMusicId;
		/// The duration the captain fade-in effect is active during intro cutscene. Counts down to 0.
		/* F8h */	float mIntroFadeinTimer;
		/// Set to true when mIntroFadeinTimer begins counting. Set to false when mIntroBeamdownTimer is less than or equal to 0. 
		/* FCh */	bool mIsIntroFadeinActive;
		/// Initially set to false but set to true when adventure begins.
		/* FDh */	bool mIsAdventureActive;
		/* 100h */	int field_100;
	};
	ASSERT_SIZE(cScenarioPlayMode, 0x108);

	namespace Addresses(cScenarioPlayMode)
	{
		DeclareAddress(Initialize);		// 0xF1F450, 0xF1F060
		DeclareAddress(SetCurrentAct);  // 0xF1F260, 0xF1EE70
		DeclareAddress(JumpToAct);		// 0xF1F7B0, 0xF1F3C0
		DeclareAddress(SetState);		// 0xF1ADB0, 0xF1A9C0
	}
}