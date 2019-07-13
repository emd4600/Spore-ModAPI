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
#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\Object.h>
#include <Spore\Input.h>

namespace App
{
	// kMsgEnterMode = 0x074BAF67
	// kMsgExitMode = 0x0462C656

	class ScenarioMode 
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

	public:
		/* 10h */	int mpEditModeInputStrategy;  // cScenarioEditModeInputStrategy
		/* 14h */	int mpEditModeDisplayStrategy;  // cScenarioEditModeDisplayStrategy
		/* 18h */	int field_18;
		/* 1Ch */	int mpScenarioUI;  // Simulator::ScenarioModeUI ?
		/* 20h */	GameInput mInput;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	int field_70;
		/* 74h */	int field_74;  // 10h is cScenarioResource!
		/* 78h */	int field_78;
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
		/* D0h */	int field_D0;  // not initialized
		/* D4h */	int mpScenarioTutorials;  // cScenarioTutorials
		/* D8h */	int mpScenarioYoutube;  // cScenarioYoutube
		/* DCh */	bool field_DC;

	public:
		/// Returns the ScenarioMode instance.
		static ScenarioMode* Get();
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ScenarioMode) == 0xE0, "sizeof(ScenarioMode) != E0h");

	namespace Addresses(ScenarioMode) {
		DeclareAddress(ptr, SelectAddress(0x16CBD24,, 0x16C7AA4));
	}
}
