#pragma once

#include <Spore\Simulator\cArtilleryProjectile.h>

#define cSpearPtr eastl::intrusive_ptr<Simulator::cSpear>

namespace Simulator
{
	class cSpear
		: public cArtilleryProjectile
	{
	public:
		static const uint32_t TYPE = 0x24270C8;
		static const uint32_t NOUN_ID = 0x24270C9;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 538h */	int field_538;  // not initialized
		/* 53Ch */	int field_53C;
	};
	ASSERT_SIZE(cSpear, 0x540);
}