#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\cCombatant.h>

#define cCulturalProjectilePtr eastl::intrusive_ptr<Simulator::cCulturalProjectile>

namespace Simulator
{
	class cCulturalProjectile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x4F76F08;
		static const uint32_t NOUN_ID = 0x4F76F0D;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 518h */	int field_518;
		/* 51Ch */	cVehiclePtr mpVehicle;
		/* 520h */	cCombatantPtr mpTarget;
		/* 524h */	cSpaceToolDataPtr mpTool;
		/* 528h */	int field_528;  // -1
		/* 52Ch */	Math::Vector3 mTargetPos;
		/* 538h */	bool field_538;
		/* 539h */	bool mbSpin;
		/* 540h */	cGonzagoTimer mLifeTimer;
		/* 560h */	uint32_t mOwner;  // -1
		/* 568h */	cGonzagoTimer field_568;
	};
	ASSERT_SIZE(cCulturalProjectile, 0x588);
}