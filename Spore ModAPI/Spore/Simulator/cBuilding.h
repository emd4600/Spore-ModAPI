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
#include <Spore\Simulator\cSpaceInventory.h>

#include <EASTL\initializer_list.h>

#define cBuildingPtr intrusive_ptr<Simulator::cBuilding>

namespace Simulator
{
	class cCity;

	/// Base class for all buildings in Simulator game modes. This class cannot be instantiated;
	/// instead, you have to create instances of specific building types:
	/// - Simulator::cBuildingCityHall
	/// - Simulator::cBuildingIndustry
	/// - Simulator::cBuildingHouse
	/// - Simulator::cBuildingEntertainment
	/// - Simulator::cBuildingScenario
	class cBuilding
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
		/* 120h */	, public cCombatant
		/* 1E8h */	, public cPlaceableStructure
	{
	public:
		struct _Unknown1
		{
			int field_0[11];
		};

		static const uint32_t TYPE = 0xE9CB8BA;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/* 54h */	virtual void SetOwnerCity1(cCity* pCity);
		/* 58h */	virtual void SetOwnerCity2(cCity* pCity);
		/* 5Ch */	virtual float GetCost();
		/* 60h */	virtual float func60h();

		/// Returns the `mbIsOn` variable
		/// @returns
		/* 64h */	virtual bool IsOn();
		
		/// Sets the `mbIsOn` variable
		/// @param isOn
		/* 68h */	virtual void SetIsOn(bool isOn);

		/* 6Ch */	virtual bool func6Ch();  // gets field_288
		/* 70h */	virtual void func70h(bool value);  // sets field_288
		/* 74h */	virtual const char16_t* func74h(); // returns field_278
		/* 78h */	virtual bool func78h();  // does nothing
		/* 7Ch */	virtual bool func7Ch(const Math::Vector3&);
		/* 80h */	virtual float func80h();  // returns 1.0
		/* 84h */	virtual cCity* GetOwnerCity();
		/* 88h */	virtual bool func88h();  // returns true
		/* 8Ch */	virtual Math::Vector3& func8Ch();

	public:
		/// Used by scenario buildings?
		/* 1ECh */	cSpaceInventoryPtr mpSpaceInventory;
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