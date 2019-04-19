/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\App\DefaultGameMode.h>
#include <Spore\App\cGameModeManager.h>

#include <EASTL\internal\thread_support.h>

namespace App
{
	DefaultGameMode::DefaultGameMode()
		: mnRefCount(0)
	{
		
	}

	int DefaultGameMode::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}

	int DefaultGameMode::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	DefaultGameMode::~DefaultGameMode() {};
	bool DefaultGameMode::func0Ch() { return true; }
	bool DefaultGameMode::Initialize(IGameModeManager* pManager) { return true; }
	bool DefaultGameMode::Dispose() { return true; }
	bool DefaultGameMode::OnEnter() { return true; }
	void DefaultGameMode::OnExit() { return; }
	void* DefaultGameMode::func20h(int) { return nullptr; }
	bool DefaultGameMode::OnKeyDown(int virtualKey, int modifiers) { return false; }
	bool DefaultGameMode::OnKeyUp(int virtualKey, int modifiers) { return false; }
	bool DefaultGameMode::OnMouseDown(int mouseState, float mouseX, float mouseY, int flags) { return false; }
	bool DefaultGameMode::OnMouseUp(int mouseState, float mouseX, float mouseY, int flags) { return false; }
	bool DefaultGameMode::OnMouseMove(float mouseX, float mouseY, int state) { return false; }
	bool DefaultGameMode::OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state) { return false;  }
	void DefaultGameMode::Update(float fDelta1, float fDelta2) {}


	auto_STATIC_METHOD_(IGameModeManager, IGameModeManager*, Get);

	//// cGameModeManager ////

	cGameModeManager::cGameModeManager()
		: mEntries()
		, mnRefCount(0)
		, field_10(false)
		, mnActiveIndex(-1)
		, mpCameraMgr(nullptr)
		, mpViewer(nullptr)
	{
	}

	cGameModeManager::~cGameModeManager()
	{

	}

	auto_METHOD_VIRTUAL(cGameModeManager, IMessageListener, bool, HandleMessage, PARAMS(uint32_t messageID, void* pMessage), PARAMS(messageID, pMessage));

	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, int, AddRef);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, int, Release);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, bool, Initialize);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, bool, Dispose);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, bool, func14h);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, bool, InitializeModes);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, bool, ClearActiveMode);
	auto_METHOD_VIRTUAL_VOID(cGameModeManager, IGameModeManager, AddGameMode, PARAMS(IGameMode* pMode, uint32_t modeID, const char* pName), PARAMS(pMode, modeID, pName));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, bool, RemoveGameMode, PARAMS(uint32_t modeID), PARAMS(modeID));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, bool, SetActiveMode, PARAMS(uint32_t modeID), PARAMS(modeID));
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, IGameMode*, GetActiveMode);
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, IGameMode*, GetGameMode, PARAMS(uint32_t modeID), PARAMS(modeID));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, uint32_t, GetModeIDAt, PARAMS(size_t index), PARAMS(index));
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, uint32_t, GetActiveModeID);
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, size_t, GetModeCount);
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, bool, SetActiveModeAt, PARAMS(size_t index), PARAMS(index));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, IGameMode*, GetGameModeAt, PARAMS(size_t index), PARAMS(index));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, int, func48h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(cGameModeManager, IGameModeManager, bool, SetActiveModeByName, PARAMS(const char* pName), PARAMS(pName));
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, ICameraManager*, GetCameraManager);
	auto_METHOD_VIRTUAL_VOID(cGameModeManager, IGameModeManager, SetViewer, PARAMS(cViewer* scene), PARAMS(scene));
	auto_METHOD_VIRTUAL_(cGameModeManager, IGameModeManager, cViewer*, GetViewer);

}