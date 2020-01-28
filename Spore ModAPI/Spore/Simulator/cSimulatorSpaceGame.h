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

#include <Spore\Simulator\cPlayerInventory.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\App\IMessageListener.h>

#include <EASTL\vector.h>

#define cSimulatorSpaceGamePtr intrusive_ptr<Simulator::cSimulatorSpaceGame>

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

		cPlayerInventory* GetPlayerInventory();

		// sub_10068B0 assigns archetype

	protected:
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;  // -1
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;  // not initialized
		/* 30h */	int field_30;  // a class
		/* 34h */	float field_34;
		/* 38h */	float field_38;
		/* 3Ch */	int field_3C;  // not initialized
		/* 40h */	intrusive_ptr<cPlayerInventory> mpPlayerInventory;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	bool field_4C;
		/* 4Dh */	bool field_4D;
		/* 4Eh */	bool field_4E;
		/* 4Fh */	bool field_4F;
		/* 50h */	int field_50;
		/* 54h */	int mpHighLODPlanetSim;  // TODO
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	bool field_6C;
		/* 70h */	int mpBadgeManager;  //TODO
		/* 74h */	bool field_74;
		/* 75h */	bool field_75;  // true
		/* 76h */	bool field_76;
		/* 77h */	bool field_77;
		/* 78h */	vector<int> mNPC_UFOs;  //TODO
		/* 90h */	cGonzagoTimer mTimeSinceStartedSpaceGame;
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;
		/* C8h */	vector<int> field_C8;
		/* DCh */	vector<int> mPlanetsToUplift;  // TODO

	public:
		static cSimulatorSpaceGame* Get();
	};

	inline cSimulatorSpaceGame* SimulatorSpaceGame() {
		return cSimulatorSpaceGame::Get();
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSimulatorSpaceGame) == 0xF0, "sizeof(cSimulatorSpaceGame) != 0xF0");

	namespace Addresses(cSimulatorSpaceGame)
	{
		DeclareAddress(Get);
	}
}