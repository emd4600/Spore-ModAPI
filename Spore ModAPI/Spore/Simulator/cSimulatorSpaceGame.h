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

#include <Spore\Simulator\cBadgeManager.h>
#include <Spore\Simulator\cPlayerInventory.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSimPlanetHighLOD.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include <Spore\Simulator\cMissionManager.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\UI\SpaceGameUI.h>

#include <EASTL\vector.h>

/// Easy access to Simulator::cSimulatorSpaceGame
#define SimulatorSpaceGame (*Simulator::cSimulatorSpaceGame::Get())

/// Easy access to Simulator::cBadgeManager
#define BadgeManager (*SimulatorSpaceGame.mpBadgeManager.get())

#define cSimulatorSpaceGamePtr eastl::intrusive_ptr<Simulator::cSimulatorSpaceGame>

namespace Simulator
{
	class cSimulatorSpaceGame
		: public cGonzagoSimulator
		, public App::IMessageListener
	{
	public:
		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		UI::SpaceGameUI* GetUI();

		cPlayerInventory* GetPlayerInventory();

		cSimPlanetHighLOD* GetPlanetHighLOD();

		// sub_10068B0 assigns archetype

	public:
		/* 14h */	SpaceGameUIPtr mpUI;
		/* 18h */	int field_18;  //TODO space trading UI
		/* 1Ch */	int field_1C;  // -1
		/* 20h */	int mpCommunityEditor;  //TODO cCommunityEditor
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;  // not initialized
		/* 30h */	int field_30;  // a class
		/* 34h */	float mSpacePhiOffsetGalaxy;
		/* 38h */	float mSpacePhiOffsetSolar;
		/* 3Ch */	float mPlanetCameraMouseRotationSpeed;  // not initialized
		/* 40h */	cPlayerInventoryPtr mpPlayerInventory;
		/* 44h */	int field_44;  // a resource factory
		/* 48h */	int field_48;
		/* 4Ch */	bool field_4C;
		/* 4Dh */	bool field_4D;
		/* 4Eh */	bool field_4E;
		/* 4Fh */	bool field_4F;
		/* 50h */	int field_50;
		/* 54h */	cSimPlanetHighLODPtr mpHighLODPlanetSim;
		/* 58h */	App::MessageListenerData mMessageListenerData;
		/* 6Ch */	bool field_6C;
		/* 70h */	cBadgeManagerPtr mpBadgeManager;
		/* 74h */	bool field_74;
		/* 75h */	bool field_75;  // true
		/* 76h */	bool field_76;
		/* 77h */	bool field_77;
		/* 78h */	eastl::vector<cGameDataUFOPtr> mNPC_UFOs;
		/* 90h */	cGonzagoTimer mTimeSinceStartedSpaceGame;
		/// Current star ID??
		/* B0h */	StarID field_B0;
		/* B4h */	cSimulatorPlayerUFOPtr mpPlayerUFO;
		/* B8h */	cMissionManagerPtr mpMissionManager;
		/* BCh */	int mpSimulatorWalkAround;  //TODO cSimulatorWalkAround
		/* C0h */	int mpSimulatorUniverse;  //TODO cSimulatorUniverse
		/* C4h */	int field_C4;
		/* C8h */	eastl::vector<int> field_C8;
		/* DCh */	eastl::vector<int> mPlanetsToUplift;  // TODO

	public:
		static cSimulatorSpaceGame* Get();
	};
	ASSERT_SIZE(cSimulatorSpaceGame, 0xF0);

	inline cSimPlanetHighLOD* cSimulatorSpaceGame::GetPlanetHighLOD() {
		return mpHighLODPlanetSim.get();
	}

	inline UI::SpaceGameUI* cSimulatorSpaceGame::GetUI() {
		return mpUI.get();
	}

	namespace Addresses(cSimulatorSpaceGame)
	{
		DeclareAddress(Get);
	}
}