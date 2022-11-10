/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>

/// Accesses the current instance of Simulator::cGameTimeManager
#define GameTimeManager (*Simulator::cGameTimeManager::Get())

namespace Simulator
{
	enum class TimeManagerPause
	{
		/// Pauses game and effects, not audio
		CinematicAll = 0x600C4AE,
		/// Pauses game, not effects nor audio
		Cinematic = 0x4BF38A5,
		/// Pauses game, not effects nor audio
		Tutorial = 0x64BEB65,
		/// Pauses game, not effects nor audio
		Editor = 0x4BF38A6,
		/// Pauses game and effects, not audio
		CommScreen = 0x4D02E35,
		/// Pauses game, not effects nor audio
		AdventureDialog = 0x7E9E4B7,
		/// Pauses game, effects and audio
		UserToggle = 0x4BF38A8,
		/// Pauses game and effects, not audio
		Gameplay = 0x4BF38A7,
		/// Pauses game and effects, not audio
		UIToggle = 0x4BF38A4,
		/// Pauses game and effects, not audio
		ModalDialog = 0x4BF38A9
	};

	/// This class controls game time speed and pauses. You can use it to pause/resume the game,
	/// and you can also use it to control the game speed.
	/// 
	/// This class is organized in different "pause types" that pause the game and optionally, effects and audio.
	/// Calls to Pause() and Resume() are "stacked", that is, if you call Pause() twice, then you have to call
	/// Resume() twice in order to actually resume the game.
	/// 
	/// Example usage:
	/// ```cpp
	/// if (!GameTimeManager.IsPaused()) {
	///     GameTimeManager.Pause(TimeManagerPause::UserToggle);
	/// }
	/// ```
	/// 
	/// This is a singleton class, so use GameTimeManager to access it.
	class cGameTimeManager
		: public cStrategy
	{
	public:
		static cGameTimeManager* Get();

		/// Tries to pause the game with the given pause type (which might also pause effects or audio).
		/// Internally, this increases the counter of how many times that type has been paused,
		/// so this does not necessarily pause the game (for example if Resume() has been called many times). 
		/// Returns 0 if game is still running, or greater than 0 if game is paused.
		/// @param pauseType
		/// @returns Current counter of `pauseType` pauses, 0 if still running, greather than 0 if paused
		int Pause(TimeManagerPause pauseType);

		/// Tries to resume the game by cancelling the given pause type.
		/// Internally, this decreases the counter of how many times that type has been paused,
		/// so this does not necessarily resume the game (for example if Pause() has been called many times). 
		/// Returns 0 if game was resumed.
		/// @param pauseType
		/// @returns Current counter of `pauseType` pauses, 0 if resumed, greather than 0 if still paused
		int Resume(TimeManagerPause pauseType);

		/// Pauses the given pause type if it is running, resumes it if it is paused.
		/// If the internal pause count is not 0 or 1 (for example, Pause() has been called many times) it does nothing.
		/// @param pauseType
		/// @returns True if game is paused, false otherwise
		bool Toggle(TimeManagerPause pauseType);

		/// Returns how many Pause() have been called on the given pause type; returns 0 if game
		/// is running, greather than 0 if it is paused.
		int GetPauseCount(TimeManagerPause pauseType);

		/// Returns the time that was registered at the start of the frame.
		/// @returns
		LARGE_INTEGER GetTimeAtStartOfFrame();

		/// Returns true if the game is paused, false if the game is running.
		/// @returns
		inline bool IsPaused();

		/// Returns true if effects are paused, false otherwise.
		/// @returns
		inline bool IsPausedEffects();

		/// Returns true if audio is paused, false otherwise.
		/// @returns
		inline bool IsPausedAudio();

		/// Called by the master Simulator system and Simulator game modes (creature, tribe, civ and space stage),
		/// to calculate the correct delta time. At the start of each frame there is an update method, with a 
		/// parameter that specifies the elapsed time since the last frame in milliseconds; that's the delta time.
		/// ConvertDeltaTime() returns 0 if the game is paused, otherwise it returns the given time multiplied by
		/// the current game time speed.
		/// @param deltaMilliseconds Real elapsed time since the last frame, in milliseconds
		/// @returns The simulated elapsed time
		int ConvertDeltaTime(int deltaMilliseconds);

		/// Sets the different possible game speeds (but does not change the current speed!).
		/// By default, these are 1.0, 2.0, 4.0, 8.0
		/// @param speed0
		/// @param speed1
		/// @param speed2
		/// @param speed3
		void SetSpeedFactors(float speed0, float speed1, float speed2, float speed3);

		/// Changes the game speed to one of 4 possible values, which are specified by SetSpeedFactors().
		/// By default, 0 sets the normal speed, 1 is 2.0x speed (so twice as fast), 2 is 4.0x speed, 3 is 8.0x speed.
		/// @param speedIndex A number from 0 to 3
		void SetSpeed(int speedIndex);

		/// Returns the current game speed, a factor that is multiplied by the elapsed time every frame.
		/// @returns
		float GetSpeed();

	public:
		enum PauseFlags
		{
			/// Pauses game time if enabled
			kPauseFlag = 0x1,
			/// Pauses effects if enabled
			kPauseFlagEffects = 0x2,
			/// Pauses audio if enabled
			kPauseFlagAudio = 0x4
		};

		struct PauseType
		{
			/// A counter of Pauses/Resumes, increases one when paused, decreases one when resumed;
			/// is considered paused if greater than 0
			int counter;
			/// A combination of PauseFlags
			int flags;
		};

		/// The possible speed factors, set with SetSpeedFactors()
		/* 1Ch */	float mSpeedFactors[4];  // 1.0, 2.0, 4.0, 8.0
		/* 30h */	LARGE_INTEGER mBaseTimeElapsed;
		/* 38h */	LARGE_INTEGER mTimeAtStartOfFrame;
		/* 40h */	float mCurrentSpeed;  // value from mSpeedFactors
		/* 44h */	int mCurrentSpeedIndex;  // index to mSpeedFactors
		/// A combination of current PauseFlags. If 0, game is unpaused; otherwise, use logical AND with PauseFlags
		/* 48h */	int mFlags;  // & 1 paused
		/// Maps each TimeManagerIdentifier to its index in `mPauseTypes`.
		/* 4Ch */	eastl::map<TimeManagerPause, int> mPauseMaps;
		/// Keeps track of the different pause types
		/* 68h */	eastl::vector<PauseType> mPauseTypes;
	};
	ASSERT_SIZE(cGameTimeManager, 0x80);

	namespace Addresses(cGameTimeManager)
	{
		DeclareAddress(Get);
		DeclareAddress(Pause);  // 0xB32140, 0x00b32330
		DeclareAddress(Resume);  // 0xB32170, 0x00b32360 
		DeclareAddress(Toggle);  // 0xB32170, 0x00b32390 
		DeclareAddress(GetPauseCount);  // 0xB31EE0, 0x00b321e0 
		DeclareAddress(ConvertDeltaTime);  // 0xB31AA0, 0xb31da0
		DeclareAddress(SetSpeed);  // 0xB32370, 0x00b32560
	}

	inline bool cGameTimeManager::IsPaused() {
		return mFlags & cGameTimeManager::kPauseFlag;
	}

	inline bool cGameTimeManager::IsPausedEffects() {
		return mFlags & cGameTimeManager::kPauseFlagEffects;
	}

	inline bool cGameTimeManager::IsPausedAudio() {
		return mFlags & cGameTimeManager::kPauseFlagAudio;
	}
}
