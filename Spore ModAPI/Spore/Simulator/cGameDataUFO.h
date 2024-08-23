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
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\list.h>

#define cGameDataUFOPtr eastl::intrusive_ptr<Simulator::cGameDataUFO>

namespace Simulator
{
	class cEmpire;

	class cGameDataUFO
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 508h */	, public cCombatant
		/* 5D0h */	, public cBehaviorList
		, public App::IUnmanagedMessageListener
	{
	public:
		static const uint32_t TYPE = 0xB033B403;
		static const uint32_t NOUN_ID = 0x18EBADC;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		float ChangeEnergy(float delta);

		void Initialize(UfoType type, cEmpire* empire);

	public:
		/* 5ECh */	float field_5EC;
		/* 5F0h */	float field_5F0;
		/* 5F4h */	Vector3 mLastTangentialVelocity;
		/* 600h */	float field_600;
		/* 604h */	float field_604;
		/* 608h */	bool field_608;
		/* 60Ch */	Vector3 mOffsetDueToDamage;
		/* 618h */	Vector3 field_618;
		/* 624h */	bool mbRotateTowardsDestination;
		/* 628h */	cGonzagoTimer field_628;
		/* 648h */	cGonzagoTimer field_648;
		/* 668h */	cGonzagoTimer field_668;
		/* 688h */	bool field_688;
		/* 689h */	bool field_689;
		/* 68Ch */	int mNPCFollowUFO;  //TODO
		/* 690h */	bool field_690;
		/* 691h */	bool field_691;
		/* 694h */	Vector3 mNPCFollowOffset;
		/* 6A0h */	Vector3 mNPCOrbitOffset;
		/* 6ACh */	float mNPCZoomOffset;
		/* 6B0h */	int mNPCFlockIndex;  // -1
		/* 6B4h */	float field_6B4;  // 1.0
		/* 6B8h */	float field_6B8;  // 1.0
		/* 6BCh */	Vector3 mStartEndPoint;
		/* 6C8h */	int field_6C8;
		/* 6D0h */	cGonzagoTimer field_6D0;
		/* 6F0h */	cGonzagoTimer field_6F0;
		/* 710h */	int field_710;
		/// 0 is player UFO
		/* 714h */	int mUFOType;  // -1
		/* 718h */	Vector3 mNextPosition;
		/* 724h */	Vector3 mNextVelocity;
		/* 730h	*/	Quaternion mNextOrientation;
		/* 740h */	Vector3 mOffsetFromPosition;
		/* 74Ch */	bool mbAtDestination;
		/* 750h */	Vector3 mDestination;
		/* 75Ch */	cPlanetPtr mDestinationPlanet;
		/* 760h */	cPlanetPtr mPreviousPlanet;
		/* 764h */	int field_764;
		/* 768h */	float mZoomAltitude;  // 1000.0
		/* 76Ch */	int field_76C;
		/* 770h */	eastl::list<int> field_770;
		/* 77Ch */	bool mbDesiredVisible;  // true
		/* 77Dh */	bool field_77D;
		/* 77Eh */	bool field_77E;
		/* 780h */	ResourceKey mDesiredModelKey;
		/* 78Ch */	bool field_78C;  // true
		/* 78Dh */	bool field_78D;
		/* 790h */	cSpaceToolDataPtr mpNPCWeapon;
		/* 794h */	cSpaceToolDataPtr mpNPCGroundWeapon;
		/* 798h */	cSpaceToolDataPtr mpNPCNearAirWeapon;
		/* 79Ch */	cSpaceToolDataPtr mpNPCMediumAirWeapon;
		/* 7A0h */	cSpaceToolDataPtr mpNPCFarAirWeapon;
		/* 7A4h */	cSpaceToolDataPtr mpNPCAbductWeapon;
		/* 7A8h */	int field_7A8;
		/* 7ACh */	int field_7AC;
		/* 7B0h */	int field_7B0;
		/* 7B8h */	cGonzagoTimer field_7B8;
		/* 7D8h */	int field_7D8;
		/* 7DCh */	int field_7DC;
		/* 7E0h */	eastl::string16 field_7E0;  // "UNINITIALIZED UFO NAME"
		/* 7F0h */	int field_7F0;
		/* 7F4h */	float mEnergy;
		/* 7F8h */	float mMaxEnergy;
		/* 7FCh */	int field_7FC;  // -1
		/* 800h */	int mOwnerMission;  //PLACEHOLDER
		/* 804h */	int field_804;
		/* 808h */	int field_808;
		/* 80Ch */	int field_80C;
		/* 810h */	int field_810;
		/* 814h */	int field_814;
	};
	ASSERT_SIZE(cGameDataUFO, 0x818);

	namespace Addresses(cGameDataUFO)
	{
		DeclareAddress(ChangeEnergy);
		DeclareAddress(Initialize);  // 0xC3D8D0 0xC3E210
	}

	/// Creates a new UFO instance of the given type and assigned to the specified empire.
	/// It will call cGameDataUFO::Initialize(), which sets up the necessary tools and AI.
	/// @param type
	/// @param empire
	/// @returns
	cGameDataUFO* CreateUFO(UfoType type, cEmpire* empire);
}

namespace Addresses(Simulator)
{
	DeclareAddress(CreateUFO);  // 0x102BB50 0x102AC60
}