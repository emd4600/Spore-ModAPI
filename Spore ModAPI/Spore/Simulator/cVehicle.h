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

#include <Spore\Simulator\UnknownCreatureClass.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\CommonIDs.h>

#define cVehiclePtr intrusive_ptr<Simulator::cVehicle>

namespace Simulator
{
	class cCity;

	class cVehicle
		: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 508h */	, public cCombatant
		/* 5D0h */	, public cBehaviorAgent
		/* 638h */	, public cBehaviorList
		/* 650h */	, public UnknownCreatureClass
	{
	public:
		static const uint32_t TYPE = 0x137E8E0;
		static const uint32_t NOUN_ID = 0x18C6DE8;

		using Object::Cast;
		using Object::AddRef;
		using Object::Release;

		// check sub_CA2810 for locomotion

		//PLACEHOLDER sub_C9E6B0 get locomotion for ID
		// sub_C9E730 get purpose for ID

		void Load(VehicleLocomotion locomotion, VehiclePurpose purpose, struct ResourceKey name);

		VehicleLocomotion GetLocomotion() const;
		VehiclePurpose GetPurpose() const;

		cSpaceToolData* GetWeapon() const;

	public:
		/* AF0h */	int field_AF0;  // cBehaviorTreeData
		/* AF4h */	bool field_AF4;
		/* AF8h */	uint32_t mLocomotionHint;
		/* AFCh */	bool field_AFC;
		/* B00h */	int field_B00;
		/* B04h */	int field_B04;
		/* B08h */	int field_B08;
		/* B0Ch */	float field_B0C;
		/* B10h */	float field_B10;
		/* B14h */	float field_B14;
		/* B18h */	float field_B18;  // 10.0
		/* B1Ch */	VehicleLocomotion mLocomotion;
		/* B20h */	VehiclePurpose mPurpose;
		/* B24h */	uint32_t mStance;
		/* B28h */	uint32_t mCargoType;
		/* B2Ch */	UnknownBehaviorContainer mEvents;
		/* B58h */	float mCargoUnits;
		/* B5Ch */	intrusive_ptr<cCity> mpNearestCity;
		/* B60h */	intrusive_ptr<cSpaceToolData> mpWeapon;
		/* B64h */	int field_B64;  // also cSpaceToolData?
		/* B68h */	vector<int> mOrders;  //TODO PLACEHOLDER tVehicleOrders
		/* B7Ch */	intrusive_ptr<cSpatialObject> mpChaseTarget;
		/* B80h */	Vector3 mIdlePosition;
		/* B8Ch */	vector<intrusive_ptr<cCombatant>> mHostileUnits;
		/* BA0h */	cGonzagoTimer mParkingTimer;
		/* BC0h */	int field_BC0;
		/* BC4h */	int field_BC4;
		/* BC8h */	int field_BC8;
		/* BCCh */	bool field_BCC;
		/* BCDh */	bool mbDead;
		/* BCEh */	bool mbDrone;
		/* BCFh */	bool field_BCF;
		/* BD0h */	bool field_BD0;
		/* BD1h */	bool field_BD1;
		/* BD8h */	cGonzagoTimer field_BD8;
		/* BF8h */	cGonzagoTimer field_BF8;
		/* C18h */	cGonzagoTimer field_C18;
		/* C38h	*/	uint32_t mUIState;
		/* C3Ch */	Vector3 mAcceptableCenter;  // not initialized
		/* C48h */	float mAcceptableMinDist;
		/* C4Ch */	float mAcceptableMaxDist;
		/* C50h */	float mPowerStat;  // 0.33
		/* C54h */	float mDefenseStat;  // 0.33
		/* C58h */	float mSpeedStat;  // 0.33
		/* C5Ch */	float mDamageMultiplier;  // 1.0
		/* C60h */	float field_C60;  // 1.0
		/* C64h */	vector<int> mWeapons;  //TODO PLACEHOLDER tWeaponInfo
		/* C78h */	int mActiveWeaponIndex;
		/* C7Ch */	unsigned int mDefaultWeaponCycleTimeMS;
		/* C80h */	int mTimeToCycleWeaponMS;
		/* C84h */	unsigned int mTimeSinceLastWeaponFireMS;
		/* C88h */	cGonzagoTimer mCombatStatusTimer;
		/* CA8h */	cGonzagoTimer mCombatVoxTimer;
		/* CC8h */	string16 field_CC8;
		/* CD8h */	cGonzagoTimer field_CD8;
		/* CF8h */	int field_CF8;  // not initialized
		/* CFCh */	int mpHitSphere;  //TODO PLACEHOLDER cHitSphere
		/* D00h */	int field_D00;
		/* D04h */	int field_D04;
		/* D08h */	int field_D08;
		/* D0Ch */	int field_D0C;
		/* D10h */	bool field_D10;
		/* D14h */	string field_D14;
		/* D24h */	int field_D24;
		/* D28h */	int field_D28;  // not initialized
		/* D2Ch */	float field_D2C;
		/* D30h */	int field_D30;
		/* D34h */	Vector3 field_D34;
		/* D40h */	Vector3 field_D40;
		/* D4Ch */	Vector3 field_D4C;
		/* D58h */	Vector3 field_D58;
		/* D64h */	int field_D64;
		/* D68h */	float field_D68;  // 1.0
		/* D68h */	int field_D6C;
		/* D80h */	int field_D70;
		/* D84h */	int field_D74;
		/* D88h */	int field_D78;
		/* D88h */	int field_D7C;
		/* D80h */	int field_D80;
		/* D84h */	int field_D84;
		/* D88h */	int field_D88;
		/* D8Ch */	float field_D8C;
		/* D90h */	float field_D90;
		/* D94h */	int field_D94;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cVehicle) == 0xD98, "sizeof(cVehicle) != D98h");

	namespace Addresses(cVehicle)
	{
		DeclareAddress(Load);
	}

	inline VehicleLocomotion cVehicle::GetLocomotion() const {
		return mLocomotion;
	}
	inline VehiclePurpose cVehicle::GetPurpose() const {
		return mPurpose;
	}

	inline cSpaceToolData* cVehicle::GetWeapon() const {
		return mpWeapon.get();
	}
}