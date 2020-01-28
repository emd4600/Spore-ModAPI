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

#include <Spore\App\IGameMode.h>
#include <Spore\App\ICameraManager.h>
#include <Spore\App\StandardMessage.h>

#include <Spore\App\cViewer.h>

/// Access the active game mode manager.
#define GameModeManager (*App::IGameModeManager::Get())

// Access the active game camera manager.
#define CameraManager (*App::IGameModeManager::Get()->GetCameraManager())

#define IGameModeManagerPtr intrusive_ptr<App::IGameModeManager>

namespace App
{
	enum
	{
		kMsgAddRef = 1,
		kMsgRelease = 2,
		/// Called when the current mode is exited. The message data is the App::OnModeExitMessage class.
		kMsgOnModeExit = 0x212D3E7,
		/// Called after the current mode is entered. The message data is the App::OnModeEnterMessage class.
		kMsgOnModeEnter = 0x22D1ADC
	};

	// not public, so user can't access the fields
	class OnModeExitMessage : StandardMessage 
	{
	public:
		/// Returns the current mode ID after this change.
		inline uint32_t GetModeID() {
			return params[0].uint32;
		}

		/// Returns the pevious mode ID before this change.
		inline uint32_t GetPreviousModeID() {
			return params[1].uint32;
		}
	};

	typedef OnModeExitMessage OnModeEnterMessage;

	///
	/// A manager that takes care of game modes; check IGameMode for more information.
	/// The manager has a vector with all the modes and keeps track of the active mode.
	/// The active mode can be set by either ID or name.
	///
	/// The manager also controls the active ICameraManager and Viewer, which control all the calculations related with
	/// camera and view projections used for rendering.
	///
	class IGameModeManager
	{

	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IGameModeManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual bool func14h() = 0;

		///
		/// Calls the IGameMode::Initialize() method on all the modes in this manager.
		///
		/* 18h */	virtual bool InitializeModes() = 0;

		///
		/// Sets the active game mode to nullptr. The IGameMode::OnExit() method will be called on the active context,
		/// and the messages 0x212D3E7 and 0x22D1ADC will be generated. 
		/// @returns True if there was an active context, false otherwise.
		///
		/* 1Ch */	virtual bool ClearActiveMode() = 0;

		///
		/// Adds the given game mode to this manager under the modeID specified. 
		/// @param pMode The IGameMode to add.
		/// @param modeID The ID that uniquely identifies this game mode, and that can be used to access it.
		/// @param pName The name of this mode.
		///
		/* 20h */	virtual void AddGameMode(IGameMode* pMode, uint32_t modeID, const char* pName) = 0;

		///
		/// Removes the game mode with the ID specified from this manager. This will call the IGameMode::Dispose() method on the mode.
		/// @param modeID The ID of the mode to remove.
		/// @returns True if the game mode was removed, false if it was not in this manager.
		///
		/* 24h */	virtual bool RemoveGameMode(uint32_t modeID) = 0;

		///
		/// Sets the active game mode to be the one with the specified ID. If there's already an active mode, 
		/// the method IGameMode::OnExit(). The method IGameMode::OnEnter() will be called on
		/// the mode with the specified ID. A message with ID 0x22D1ADC will be generated.
		/// @param modeID The ID of the game mode to set as active.
		/// @returns True if the mode was found and set active, false otherwise.
		///
		/* 28h */	virtual bool SetActiveMode(uint32_t modeID) = 0;

		///
		/// Returns the game mode that is currently in action.
		///
		/* 2Ch */	virtual IGameMode* GetActiveMode() = 0;

		///
		/// Gets the game mode in this manager with the specified ID.
		/// @param modeID The ID of the mode.
		/// @returns The IGameMode with that ID, or nullptr if there is none.
		///
		/* 30h */	virtual IGameMode* GetGameMode(uint32_t modeID) = 0;

		///
		/// Gets the modeID at the specified index.
		/// @param index The index of the game modes array.
		/// @returns The ID of the game mode at that index, or 0 if the index is out of bounds.
		///
		/* 34h */	virtual uint32_t GetModeIDAt(size_t index) = 0;

		///
		/// Gets the modeID of the currently active IGameMode.
		/// @returns The ID of the active game mode, or 0 if no mode is active.
		///
		/* 38h */	virtual uint32_t GetActiveModeID() = 0;

		///
		/// Gets the number of game modes contained in this manager.
		///
		/* 3Ch */	virtual size_t GetModeCount() = 0;

		///
		/// Sets the active game mode to be the one at the specified index. If there's already an active mode, 
		/// the method IGameMode::OnExit() will be called on it. The method IGameMode::OnEnter() will be called on
		/// the mode at the specified index. A message with ID 0x22D1ADC will be generated.
		/// @param index The index of the game mode to set as active.
		/// @returns True if the mode was found and set active, false otherwise.
		///
		/* 40h */	virtual bool SetActiveModeAt(size_t index) = 0;

		///
		/// Gets the IGameMode at the specified index.
		/// @param index The index of the game modes array.
		/// @returns A pointer to the IGameMode at that index, or nullptr if the index is out of bounds.
		/// 
		/* 44h */	virtual IGameMode* GetGameModeAt(size_t index) = 0;

		/* 48h */	virtual int func48h(int) = 0;

		///
		/// Sets the active game mode to be the one with the specified name. If there's already an active mode, 
		/// the method IGameMode::OnExit() will be called on it. The method IGameMode::OnEnter() will be called on
		/// the moed at the specified index. A message with ID 0x22D1ADC will be generated.
		/// @param pName The name of the game mode to set as active.
		/// @returns True if the mode was found and set active, false otherwise.
		///
		/* 4Ch */	virtual bool SetActiveModeByName(const char* pName) = 0;

		///
		/// Gets the ICameraManager instance used in this mode manager, and that manages the active camera of the active game mode.
		///
		/* 50h */	virtual ICameraManager* GetCameraManager() = 0;

		///
		/// Sets the Viewer instance that is used for rendering the main game frame.
		/// @param pViewer The Viewer instance.
		///
		/* 54h */	virtual void SetViewer(cViewer* pViewer) = 0;

		///
		/// Returns the Viewer instance that is being used for rendering the main game frame.
		///
		/* 58h */	virtual cViewer* GetViewer() = 0;


		///
		/// Gets the active game mode manager.
		///
		static IGameModeManager* Get();
	};

	inline cViewer* GetViewer()
	{
		auto mgr = IGameModeManager::Get();
		return mgr ? mgr->GetViewer() : nullptr;
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IGameModeManager)
	{
		DeclareAddress(Get);
	}
}