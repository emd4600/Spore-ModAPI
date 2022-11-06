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

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cGameDataUFO.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>

#define SimulatorPlayerUFO (*Simulator::cSimulatorPlayerUFO::Get())

#define cSimulatorPlayerUFOPtr eastl::intrusive_ptr<Simulator::cSimulatorPlayerUFO>

namespace Simulator
{
	class cSimulatorPlayerUFO
		: public cGonzagoSimulator
		, public App::IUnmanagedMessageListener
	{
	public:
		inline cGameDataUFO* GetUFO() { return mpPlayerUFO.get(); };

	public:
		/* 14h */	bool field_14;
		/* 15h */	bool field_15;
		/* 16h */	bool field_16;
		/* 17h */	bool field_17;
		/* 18h */	bool field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	bool field_20;
		/* 24h */	int field_24;
		/* 28h */	bool field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	intrusive_ptr<cGameDataUFO> mpPlayerUFO;
		/* 44h */	int field_44;
		/* 48h */	float mMaxDistance;
		/* 4Ch */	float mMaxScanDistance;
		/* 50h */	float field_50;
		/* 54h */	bool field_54;
		/* 54h */	bool field_55;
		/* 54h */	bool field_56; // true
		/* 58h */	vector<int> field_58;
		/* 6Ch */	int field_6C;
		/* 70h */	list<uint32_t> mPosseUFOList;
		/* 80h */	cGonzagoTimer field_80;
		/* A0h */	int field_A0;
		/* A4h */	int field_A4;
		/* A8h */	int field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;
		/* B8h */	float field_B8;  // 1.0
		/* BCh */	float field_BC;  // 0.75
		/* C0h */	float field_C0;  // 50.0
		/* C4h */	float field_C4;  // 50.0
		/* C8h */	float field_C8;  // 50.0
		/* CCh */	int field_CC;
		/* D0h */	int field_D0;
		/* D4h */	int field_D4;
		/* D8h */	int field_D8;
		/* DCh */	int field_DC;

	public:
		static cSimulatorPlayerUFO* Get();
	};

	inline cGameDataUFO* GetPlayerUFO() {
		return cSimulatorPlayerUFO::Get()->GetUFO();
	}

	static_assert(sizeof(cSimulatorPlayerUFO) == 0xE0, "sizeof(cSimulatorPlayerUFO) != 0xE0");

	namespace Addresses(cSimulatorPlayerUFO)
	{
		DeclareAddress(Get);
	}
}