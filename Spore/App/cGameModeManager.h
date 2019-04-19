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

using namespace eastl;

namespace App
{
	///
	/// The implementation of IGameModeManager; this should only be used for extending and detouring.
	///
	class cGameModeManager : public IGameModeManager, public IMessageListener, public IVirtual
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

	protected:
		struct ModeEntry
		{
			intrusive_ptr<IGameMode> mpMode;
			uint32_t mModeID;
			string mpName;
		};

	protected:
		/* 0Ch */	int mnRefCount;
		/* 10h */	bool field_10;
		/* 14h */	vector<ModeEntry> mEntries;
		/* 28h */	int mnActiveIndex;
		/* 2Ch */	intrusive_ptr<ICameraManager> mpCameraMgr;
		/* 30h */	cViewer* mpViewer;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameModeManager) == 0x34, "sizeof(cGameModeManager) != 34h");

	namespace InternalAddressList(cGameModeManager)
	{
		DefineAddress(HandleMessage, GetAddress(0x7D86A0, 0x7D81D0, 0x7D8240));

		DefineAddress(AddRef, GetAddress(0xCF91C0, 0x671F20, 0x671F20));
		DefineAddress(Release, GetAddress(0xD57BB0, 0xAE05F0, 0xAE0620));

		DefineAddress(Initialize, GetAddress(0x7D8580, 0x7D80B0, 0x7D8120));
		DefineAddress(Dispose, GetAddress(0x7D9640, 0x7D9170, 0x7D91E0));
		DefineAddress(func14h, GetAddress(0x7D8710, 0x7D8240, 0x7D82B0));
		DefineAddress(InitializeModes, GetAddress(0x7D8750, 0x7D8280, 0x7D82F0));
		DefineAddress(ClearActiveMode, GetAddress(0x7D8990, 0x7D84C0, 0x7D8530));
		DefineAddress(AddGameMode, GetAddress(0x7D9780, 0x7D92B0, 0x7D9320));
		DefineAddress(RemoveGameMode, GetAddress(0x7D9510, 0x7D9040, 0x7D90B0));
		DefineAddress(SetActiveMode, GetAddress(0x7D9150, 0x7D8C80, 0x7D8CF0));
		DefineAddress(GetActiveMode, GetAddress(0x7D87E0, 0x7D8310, 0x7D8380));
		DefineAddress(GetGameMode, GetAddress(0x7D8790, 0x7D82C0, 0x7D8330));
		DefineAddress(GetModeIDAt, GetAddress(0x7D8930, 0x7D8460, 0x7D84D0));
		DefineAddress(GetActiveModeID, GetAddress(0x7D8820, 0x7D8350, 0x7D83C0));
		DefineAddress(GetModeCount, GetAddress(0x7D8860, 0x7D8390, 0x7D8400));
		DefineAddress(SetActiveModeAt, GetAddress(0x7D91A0, 0x7D8CD0, 0x7D8D40));
		DefineAddress(GetGameModeAt, GetAddress(0x7D88F0, 0x7D8420, 0x7D8490));
		DefineAddress(func48h, GetAddress(0x108DD90, 0x111CD70, 0x111CD70));
		DefineAddress(SetActiveModeByName, GetAddress(0x7D8880, 0x7D83B0, 0x7D8420));
		DefineAddress(GetCameraManager, GetAddress(0xB18420, 0x967D90, 0x967D90));
		DefineAddress(SetViewer, GetAddress(0x7D8970, 0x7D84A0, 0x7D8510));
		DefineAddress(GetViewer, GetAddress(0x804E60, 0x5AADB0, 0x5AADB0));

	}
}