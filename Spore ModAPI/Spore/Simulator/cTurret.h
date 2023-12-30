#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cHitSphere.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cPlaceableStructure.h>

#define cTurretPtr eastl::intrusive_ptr<Simulator::cTurret>

namespace Simulator
{
	class cCity;

	class cTurret
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cBehaviorList
		/* 51Ch */	, public cBehaviorAgent
		/* 588h */	, public cCombatant
		/* 650h */	, public cPlaceableStructure
	{
	public:
		static const uint32_t TYPE = 0x436F315;
		static const uint32_t NOUN_ID = 0x436F342;
	
	public:
		/* 658h */	char padding_658[8];
		/* 660h */	cGonzagoTimer mDestroyTimer;
		/* 680h */	int field_680;
		/* 684h */	int mFreezeCount;
		/* 688h */	eastl::intrusive_ptr<cCity> mpCity;
		/* 68Ch */	cSpaceToolDataPtr mpWeapon;
		/* 690h */	cSpaceToolDataPtr mpCivTurretWeapon;
		/* 694h */	cSpaceToolDataPtr mpSpaceBeamWeapon;
		/* 698h */	cSpaceToolDataPtr mpSpaceDefenseMissileWeapon;
		/* 69Ch */	cSpaceToolDataPtr mpSpaceTurretFlak;
		/* 6A0h */	cHitSpherePtr mpHitSphere;
		/* 6A4h */	cCombatantPtr mpFacingTarget;
		/* 6A8h */	int field_6A8;  // -1
		/* 6B0h */	cGonzagoTimer field_6B0;
	};
	ASSERT_SIZE(cTurret, 0x6D0);
}