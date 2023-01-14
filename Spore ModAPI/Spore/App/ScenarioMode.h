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

#include <Spore\Simulator\cScenarioData.h>
#include <Spore\Simulator\cScenarioPlayMode.h>
#include <Spore\Simulator\cScenarioTerraformMode.h>
#include <Spore\App\IGameMode.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\Object.h>
#include <Spore\Input.h>

#define ScenarioMode (*App::cScenarioMode::Get())

#define ScenarioModePtr eastl::intrusive_ptr<App::ScenarioMode>

namespace App
{
	// kMsgEnterMode = 0x074BAF67
	// kMsgExitMode = 0x0462C656

	class cScenarioMode 
		: public App::IGameMode
		, public App::IUnmanagedMessageListener
		, public DefaultRefCounted
	{
	public:
		using DefaultRefCounted::AddRef;
		using DefaultRefCounted::Release;

		enum class Mode : int
		{
			UnkMode = 0,
			EditMode = 1,
			PlayMode = 2
		};

		Mode GetMode() const;

		inline Simulator::cScenarioData* GetData();

		inline Simulator::cScenarioTerraformMode* GetTerraformMode();

		inline Simulator::cScenarioPlayMode* GetPlayMode();

		inline Simulator::cScenarioResource* GetResource();

	public:
		/* 10h */	int mpEditModeInputStrategy;  // cScenarioEditModeInputStrategy
		/* 14h */	int mpEditModeDisplayStrategy;  // cScenarioEditModeDisplayStrategy
		/* 18h */	cScenarioTerraformModePtr mpTerraformMode;
		/* 1Ch */	int mpScenarioUI;  // Simulator::ScenarioModeUI ?
		/* 20h */	GameInput mInput;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;  // another UI?
		/* 70h */	int field_70;
		/* 74h */	cScenarioDataPtr mpData;
		/* 78h */	cScenarioPlayModePtr mpPlayMode;
		/* 7Ch */	int field_7C;  // token translator
		/* 80h */	App::MessageListenerData field_80;
		/* 94h */	App::MessageListenerData field_94;
		/* A8h */	bool field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;  // 2
		/* C8h */	int* field_C8;
		/* CCh */	Mode mMode;
		/// Only counts achivement if == 2
		/* D0h */	int field_D0;  // not initialized
		/* D4h */	int mpScenarioTutorials;  // cScenarioTutorials
		/* D8h */	int mpScenarioYoutube;  // cScenarioYoutube
		/* DCh */	bool field_DC;

	public:
		/// Returns the ScenarioMode instance.
		static cScenarioMode* Get();
	};
	ASSERT_SIZE(cScenarioMode, 0xE0);

	namespace Addresses(cScenarioMode) {
		DeclareAddress(ptr);
	}
	// We keed it for backwards compatibility
	namespace ScenarioMode_addresses {
		DeclareAddress(ptr);
	}

#ifdef SDK_TO_GHIDRA
	cScenarioMode* sScenarioMode;
#endif

	Simulator::cScenarioData* cScenarioMode::GetData()
	{
		return mpData.get();
	}

	Simulator::cScenarioResource* cScenarioMode::GetResource()
	{
		return mpData->mpResource.get();
	}

	Simulator::cScenarioTerraformMode* cScenarioMode::GetTerraformMode()
	{
		return mpTerraformMode.get();
	}

	Simulator::cScenarioPlayMode* cScenarioMode::GetPlayMode()
	{
		return mpPlayMode.get();
	}
}
