#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cSpaceToolData.h>

#define cArtilleryProjectilePtr eastl::intrusive_ptr<Simulator::cArtilleryProjectile>

namespace Simulator
{
	class cArtilleryProjectile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x1428A48;
		static const uint32_t NOUN_ID = 0x18C9380;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Creates a `cBallisticLocomotion` locomotion strategy to start launching this projectile.
		/// @param target
		void LaunchProjectile(const Math::Vector3& target);

	public:
		/* 518h */	Math::Vector3 mLastPosition;
		/* 524h */	cCombatantPtr mpOwner;
		/* 528h */	int mMinDamage;
		/* 52Ch */	int mMaxDamage;
		/* 530h */	int mDamageType;
		/* 534h */	cSpaceToolDataPtr mTool;
	};
	ASSERT_SIZE(cArtilleryProjectile, 0x538);

	namespace Addresses(cArtilleryProjectile)
	{
		DeclareAddress(LaunchProjectile);  // 0xCB68C0 0xCB71C0
	}
}