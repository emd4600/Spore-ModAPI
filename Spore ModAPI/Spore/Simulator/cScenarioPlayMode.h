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
		/* 08h */	map<uint32_t, int> field_8;
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
		
		void SetCurrentAct(int actIndex, bool = false);

	public:
		/* 0Ch */	cScenarioPlaySummary mSummary;
		/* 54h */	string16 mFailReason;
		/// Goals for the current act
		/* 64h */	vector<cScenarioPlayModeGoal> mCurrentGoals;
		/* 78h */	int field_78;  // not initialized
		/* 7Ch */	App::MessageListenerData mMessageListenerData;
		/* 90h */	int field_90;  // not initialized, current state? fail reason?
		/* 94h */	int field_94;  // not initialized
		/* 98h */	Clock field_98;
		/* B0h */	int field_B0;  // not initialized
		/* B4h */	int field_B4;  // not initialized
		/// Index of the current act (0 is first act, 1 is second, etc)
		/* B8h */	int mCurrentActIndex;  // not initialized
		/// Time limit of the current act, in milliseconds (negative number if no time limit)
		/* BCh */	long mTimeLimitMS;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;  // not initialized
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	int field_CC;  // not initialized
		/* D0h */	int field_D0;  // not initialized
		/* D4h */	int field_D4;  // not initialized
		/* D8h */	int field_D8;  // not initialized
		/* DCh */	float field_DC;
		/* E0h */	Math::Vector3 field_E0;
		/* ECh */	bool field_EC;
		/* F0h */	Audio::AudioTrack mMusicTrack;
		/* F4h */	uint32_t mCurrentMusicId;
		/* F8h */	float field_F8;
		/* FCh */	bool field_FC;
		/* FDh */	bool field_FD;
		/* 100h */	int field_100;
	};
	ASSERT_SIZE(cScenarioPlayMode, 0x108);

	namespace Addresses(cScenarioPlayMode)
	{
		DeclareAddress(SetCurrentAct);  // 0xF1F260, 0xF1EE70
	}
}