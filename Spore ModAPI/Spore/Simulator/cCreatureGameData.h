#pragma once

#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\MathUtils.h>

namespace Simulator
{
	class cCreatureGameData
	{
	public:
		enum class AbilityMode : int
		{
			Attack = 0,
			Social = 1
		};

		static cCreatureGameData* Get();

		/// Increases the amount of evolution points, updating the UI and 
		static void AddEvolutionPoints(float points);

		/// Returns the current amount of evolution points.
		/// @returns
		static float GetEvolutionPoints();

		/// Sets the `mEvolutionPoints` variable, but has no other effect on the game.
		static void SetEvolutionPoints(float points);

		/// Returns the amount of evolution points required to achieve the next brain level.
		/// If the parameter is -1, it will use the avatar current brain level.
		/// @param currentLevel
		/// @returns
		static float GetEvoPointsToNextBrainLevel(int currentLevel = -1);

		/// Changes the current ability mode (Attack or Social), optionally playing a sound.
		/// This does not change the user interface.
		static void SetAbilityMode(AbilityMode mode, bool playSound);

		/// Called after a creature touches the ground after gliding. This method resets
		/// the `mGlideStartPosition` and `mNumFlapsAllowed` values, and gives out the flying achievement
		/// if necessary.
		static void AfterGlideFinish();

		static void CalculateAvatarNormalizingScale();

		static float GetAvatarNormalizingScale(cCreatureBase* creature = nullptr);

	public:
		/* 00h */	int mCurrentBrainLevel;
		/* 04h */	float mAvatarNormalizingScale;
		/* 08h */	int mNumFlapsAllowed;
		/* 0Ch */	bool field_C;
		/* 0Dh */	bool field_D;
		/* 0Eh */	bool field_E;
		/* 0Fh */	bool field_F;
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;
		/* 14h */	int field_14;
		/* 18h */	Math::Vector3 field_18;
		/* 24h */	AbilityMode mAbilityMode;
		/* 28h */	float mEvolutionPoints;
		/* 30h */	uint64_t DEPRECATED_mLearnedAbilities;
		/* 38h */	int mLearnedAbilities[3];
		/// The position on land on the last jump, is 0 if creature is on land.
		/* 44h */	Math::Vector3 mGlideStartPosition;
	};
	ASSERT_SIZE(cCreatureGameData, 0x50);

	namespace Addresses(cCreatureGameData)
	{
		DeclareAddress(Get);  // 0xD2D640 0xD2E340
		DeclareAddress(GetEvoPointsToNextBrainLevel);  // 0xD2D680 0xD2E380
		DeclareAddress(GetAbilityMode);  // 0xD2D790 0xD2E490
		DeclareAddress(SetAbilityMode);  // 0xD2D7A0 0xD2E4A0
		DeclareAddress(AfterGlideFinish);  // 0xD2D880 0xD2E580
		DeclareAddress(CalculateAvatarNormalizingScale);  // 0xD2DA20 0xD2E720
		DeclareAddress(GetAvatarNormalizingScale);  // 0xD2DB00 0xD2E800
		DeclareAddress(GetEvolutionPoints);  // 0xD2D650 0xD2E350
		DeclareAddress(SetEvolutionPoints);  // 0xD2D780 0xD2E480
		DeclareAddress(AddEvolutionPoints);  // 0xD2DBA0 0xD2E8A0
	}

#ifdef SDK_TO_GHIDRA
	cCreatureGameData* sCreatureGameData;
#endif
}
