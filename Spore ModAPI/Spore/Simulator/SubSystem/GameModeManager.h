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

#include <Spore\Object.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\PropertyList.h>
#include <Spore\CommonIDs.h>
#include <Spore\Editors\EditorRequest.h>

/// Access the active Simulator game mode manager. 
#define SimGameModeManager (*Simulator::cGameModeManager::Get())

namespace Simulator
{

	class cGameModeManager
		: public cStrategy
		, public App::IUnmanagedMessageListener
	{
	public:
		uint32_t GetActiveModeID();

		///
		/// Returns the difficulty tuning property list that configures the specified game mode ID. 
		/// If bUseCurrentDifficulty is false, it will return the medium difficulty; otherwise, it will use the 
		/// current player difficulty.
		/// @param gameModeID
		/// @param bUseCurrentDifficulty [Optional]
		App::PropertyList* GetDifficultyTuning(uint32_t gameModeID, bool bUseCurrentDifficulty=false);

		/// 
		/// Returns the dificulty tuning property list for the active game mode and difficulty. If there is no
		/// player dificulty set, it returns the medium difficulty.
		App::PropertyList* GetActiveDifficultyTuning();

		void SubmitEditorRequest(Editors::EditorRequest* pRequest);

	protected:
		struct DifficultyTuning {
			intrusive_ptr<App::PropertyList> values[3];
		};

		/* 20h */	uint32_t mActiveModeID;  // -1
		/* 24h */	int field_24;  // -1 previous mode?
		/* 28h */	bool field_28;
		/* 29h */	bool field_29;
		/* 2Ch */	int field_2C;
		/* 30h */	intrusive_ptr<Swarm::IEffectWorld> mpTransitionEffectWorld;
		/* 34h */	int field_34;
		/* 38h */	int mpTransitionBlockingWin;  // cTransitionBlockingWin PLACEHOLDER
		// Access with gameModeID - kGameModeBase
		/* 3Ch */	DifficultyTuning mDifficultyTuning[7];
		/* 90h */	intrusive_ptr<App::PropertyList> mScenarioTuning[3];  // one for each difficulty, related with Scenario

	public:
		/// Returns the active Simulator game mode manager. 
		static cGameModeManager* Get();
	};

	/// Returns the ID of the current game mode. You can compare it to the values in the GameModeIDs enum.
	uint32_t GetGameModeID();

	/// Returns true if the game is currently in the cell stage.
	inline bool IsCellGame() {
		return GetGameModeID() == kGameCell;
	}

	/// Returns true if the game is currently in the creature stage.
	inline bool IsCreatureGame() {
		return GetGameModeID() == kGameCreature;
	}

	/// Returns true if the game is currently in the tribe stage.
	inline bool IsTribeGame() {
		return GetGameModeID() == kGameTribe;
	}

	/// Returns true if the game is currently in the civilization stage.
	inline bool IsCivGame() {
		return GetGameModeID() == kGameCiv;
	}

	/// Returns true if the game is currently in the tribe stage.
	inline bool IsSpaceGame() {
		return GetGameModeID() == kGameSpace;
	}

	/// Returns true if the game is currently in the "game edit" mode, which is the level editor.
	inline bool IsGameEditMode() {
		return GetGameModeID() == kGameEditMode;
	}

	/// Returns true if the game is currently in adventure mode.
	inline bool IsScenarioMode() {
		return GetGameModeID() == kScenarioMode;
	}

	/// Returns true if the game is currently loading a stage.
	inline bool IsLoadingGameMode() {
		return GetGameModeID() == kLoadGameMode;
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameModeManager) == 0x9C, "sizeof(cGameModeManager) != 9Ch");

	namespace Addresses(cGameModeManager)
	{
		DeclareAddress(Get);

		DeclareAddress(GetActiveDifficultyTuning);
		DeclareAddress(GetDifficultyTuning);

		DeclareAddress(SubmitEditorRequest);

		//PLACEHOLDER 0xB1E2A0 transition to another game mode?
	}
}