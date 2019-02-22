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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cPlaceableStructure.h>

#include <EASTL\initializer_list.h>

namespace Simulator
{
	class cCity;

	class cBuilding
		: public cGameData
		, public cSpatialObject
		, public cBehaviorList
		, public cCombatant
		, public cPlaceableStructure
	{
	public:
		struct _Unknown1
		{
			int field_0[11];
		};

	protected:

		/* 1ECh */	int field_1EC;
		/* 1F0h */	intrusive_ptr<cCity> mpOwnerCity;
		/* 1F4h */	bool mbIsOn;  // true
		/* 1F8h */	_Unknown1 mEvents;
		/* 224h */	ResourceKey mNormalModelKey;
		/* 230h */	bool mbIrradiated;
		/* 238h */	cGonzagoTimer mAttackTimer;
		/* 258h */	cGonzagoTimer mDestroyTimer;
		/* 278h */	string16 field_278;
		/* 288h */	bool field_288;  // true
		/* 289h */	bool mbConnected;  // true
		/* 28Ch */	int mEffectiveness;
		/* 290h */	int mFreezeCount;
		/* 294h */	int mMoneyCount;
		/* 298h */	int mHappyCount;
		/* 29Ch */	int mUnhappyCount;
		/* 2A0h */	vector<int> field_2A0;
		/* 2B4h */	vector<int> field_2B4;
		/* 2C8h */	vector<int> field_2C8;
		/* 2DCh */	vector<int> field_2DC;
		/* 2F0h */	bool field_2F0;
		/* 2F4h */	vector<int> field_2F4;
		/* 308h */	vector<int> field_308;
		/* 320h */	cGonzagoTimer field_320;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cBuilding) == 0x340, "sizeof(cBuilding) != 340h");
}