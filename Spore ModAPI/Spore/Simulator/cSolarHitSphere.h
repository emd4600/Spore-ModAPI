#pragma once

#include <Spore\Simulator\cHitSphere.h>

#define cSolarHitSpherePtr eastl::intrusive_ptr<Simulator::cSolarHitSphere>

namespace Simulator
{
	class cSolarHitSphere
		: public cHitSphere
	{
	public:
		static const uint32_t TYPE = 0x32F9777;
		static const uint32_t NOUN_ID = 0x32F9778;
	};
	ASSERT_SIZE(cSolarHitSphere, 0x250);
}