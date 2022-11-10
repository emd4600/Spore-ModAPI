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

#include <Spore\App\IGameModeManager.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Object.h>

#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace App
{
	///
	/// The implementation of IGameModeManager; this should only be used for extending and detouring.
	///
	class cGameModeManager 
		: public IGameModeManager
		, public IMessageListener
		, public IVirtual
	{
	public:

		cGameModeManager();
		virtual ~cGameModeManager();

		// Overrides

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		virtual int AddRef() override;
		virtual int Release() override;

		virtual bool Initialize() override;
		virtual bool Dispose() override;
		virtual bool func14h() override;
		virtual bool InitializeModes() override;
		virtual bool ClearActiveMode() override;
		virtual void AddGameMode(IGameMode* pMode, uint32_t modeID, const char* pName) override;
		virtual bool RemoveGameMode(uint32_t modeID) override;
		virtual bool SetActiveMode(uint32_t modeID) override;
		virtual IGameMode* GetActiveMode() override;
		virtual IGameMode* GetGameMode(uint32_t modeID) override;
		virtual uint32_t GetModeIDAt(size_t index) override;
		virtual uint32_t GetActiveModeID() override;
		virtual size_t GetModeCount() override;
		virtual bool SetActiveModeAt(size_t index) override;
		virtual IGameMode* GetGameModeAt(size_t index) override;
		virtual int func48h(int) override;
		virtual bool SetActiveModeByName(const char* pName) override;
		virtual ICameraManager* GetCameraManager() override;
		virtual void SetViewer(cViewer* scene) override;
		virtual cViewer* GetViewer() override;

	public:
		struct ModeEntry
		{
			IGameModePtr mpMode;
			uint32_t mModeID;
			eastl::string mpName;
		};

		/* 0Ch */	int mnRefCount;
		/* 10h */	bool field_10;
		/* 14h */	eastl::vector<ModeEntry> mEntries;
		/* 28h */	int mnActiveIndex;
		/* 2Ch */	ICameraManagerPtr mpCameraMgr;
		/* 30h */	cViewer* mpViewer;
	};
	ASSERT_SIZE(cGameModeManager, 0x34);

	namespace Addresses(cGameModeManager)
	{
		DeclareAddress(HandleMessage);

		DeclareAddress(AddRef);
		DeclareAddress(Release);

		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(func14h);
		DeclareAddress(InitializeModes);
		DeclareAddress(ClearActiveMode);
		DeclareAddress(AddGameMode);
		DeclareAddress(RemoveGameMode);
		DeclareAddress(SetActiveMode);
		DeclareAddress(GetActiveMode);
		DeclareAddress(GetGameMode);
		DeclareAddress(GetModeIDAt);
		DeclareAddress(GetActiveModeID);
		DeclareAddress(GetModeCount);
		DeclareAddress(SetActiveModeAt);
		DeclareAddress(GetGameModeAt);
		DeclareAddress(func48h);
		DeclareAddress(SetActiveModeByName);
		DeclareAddress(GetCameraManager);
		DeclareAddress(SetViewer);
		DeclareAddress(GetViewer);

	}
}