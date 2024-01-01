#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cProjectile.h>

#define cFlakProjectilePtr eastl::intrusive_ptr<Simulator::cFlakProjectile>

namespace Simulator
{
	class cFlakProjectile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x240E3B7;
		static const uint32_t NOUN_ID = 0x240E3BF;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		void LaunchProjectile(const Math::Vector3&, float);

	public:
		/* 518h */	int field_518;
		/* 51Ch */	float field_51C;
	};
	ASSERT_SIZE(cFlakProjectile, 0x520);

	namespace Addresses(cFlakProjectile)
	{
		DeclareAddress(LaunchProjectile);  // 0xCB7400 0xCB7CF0
	}
}