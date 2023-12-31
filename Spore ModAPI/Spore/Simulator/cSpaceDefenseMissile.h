#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cCombatant.h>

#define cSpaceDefenseMissilePtr eastl::intrusive_ptr<Simulator::cSpaceDefenseMissile>

namespace Simulator
{
	class cSpaceDefenseMissile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
		/* 518h */	, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0x244D3C0;
		static const uint32_t NOUN_ID = 0x244D3C8;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 5E0h */	int field_5E0;
		/* 5E4h */	int field_5E4;
		/* 5E8h */	cGonzagoTimer field_5E8;
		/* 608h */	int field_608;
	};
	ASSERT_SIZE(cSpaceDefenseMissile, 0x610);
}