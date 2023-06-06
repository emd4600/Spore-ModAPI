#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Pollinator\cSPAchievementSerializer.h>
#include <EASTL\hash_map.h>
#include <EASTL\vector_map.h>

#define AchievementsManager (*Pollinator::cAchievementsManager::Get())

namespace Pollinator
{
	/// Manages the achievements of the game.
	/// This manager listens to the App::IMessageManager::kMsgCheatInvoked message,
	/// and will disable achievements when it receives the message, as you will be considered a cheater.
	/// Example code:
	/// ```cpp
	/// AchievementsManager.AddProgress(id("ADV-MyHero"), 20);
	/// ```
	class cAchievementsManager
		: public App::IUnmanagedMessageListener
	{
	public:
		enum Messages
		{
			kMsgSaveAchievements = 0x212D3E7
		};

		static cAchievementsManager* Get();

		cAchievementDefinition* GetAchievementDefinition(uint32_t achievementID);

		/// Evaluates whether the current achievement progress exceeds the trigger,
		/// which means the achievement should be earned.
		/// @param achievementID
		/// @returns
		bool EvaluateTriggerOp(uint32_t achievementID);

		/// Increases or decreases the progress of an achievement. If the achievement is automatic,
		/// this will call EvaluateTriggerOp() afterwards, and earn the achievement if it returns true.
		/// @param achievementID
		/// @param deltaProgress
		void AddProgress(uint32_t achievementID, int deltaProgress);

		/// Treats the progress as flags, and enables or disables some of them. If the achievement is automatic,
		/// this will call EvaluateTriggerOp() afterwards, and earn the achievement if it returns true.
		/// @param achievementID
		/// @param progressFlags
		/// @param value
		void SetProgressFlags(uint32_t achievementID, int progressFlags, bool value);

		/// Earns an achievement.
		/// @param achievementID
		/// @returns True if it was earned successfully
		bool EarnAchievement(uint32_t achievementID);

	public:
		/* 04h */	int mpAchievementNotifierUI;
		/* 08h */	cSPAchievementSerializerPtr mpSerializer;
		/* 0Ch */	eastl::vector_map<uint32_t, cAchievementDefinition> mAchievements;
		/// If true, achievements are disabled.
		/* 24h */	bool mIsCheater;
		/* 28h */	cSPAchievementSerializer::CrossGameData mCrossGameData;
	};
	ASSERT_SIZE(cAchievementsManager, 0xA8);
	
	namespace Addresses(cAchievementsManager)
	{
		DeclareAddress(Get);  // 0x6755E0 0x675210
		DeclareAddress(Init);  // 0x676D90 0x676C40
		DeclareAddress(GetAchievementDefinition);  // 0x676770 0x676620
		DeclareAddress(EvaluateTriggerOp);  // 0x676800 0x6766B0
		DeclareAddress(EarnAchievement);  // 0x676820 0x6766D0
		DeclareAddress(AddProgress);  // 0x676FA0 0x676E50
		DeclareAddress(SetProgressFlags);  // 0x676FE0 0x676E90
	}
}