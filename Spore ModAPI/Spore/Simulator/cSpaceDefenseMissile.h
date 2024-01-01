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

		/// Creates a `cSpaceDefenseMissileLocomotion` to launch this projectile.
		/// @param target
		/// @param source
		void LaunchProjectile(const Math::Vector3& target, cCombatant* source);

	public:
		/* 5E0h */	int field_5E0;
		/* 5E4h */	cCombatantPtr mpSource;
		/* 5E8h */	cGonzagoTimer field_5E8;
		/* 608h */	int field_608;
	};
	ASSERT_SIZE(cSpaceDefenseMissile, 0x610);

	namespace Addresses(cSpaceDefenseMissile)
	{
		DeclareAddress(LaunchProjectile);  // 0xCB7FD0 0xCB88B0
	}
}