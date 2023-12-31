#pragma once

#include <Spore\Simulator\cDefaultToolProjectile.h>

#define cDeepSpaceProjectilePtr eastl::intrusive_ptr<Simulator::cDeepSpaceProjectile>

namespace Simulator
{
	class cDeepSpaceProjectile 
		: public cDefaultToolProjectile
	{
	public:
		static const uint32_t TYPE = 0x24270C6;
		static const uint32_t NOUN_ID = 0x24270C7;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
	};
	ASSERT_SIZE(cDeepSpaceProjectile, 0x5F0);
}