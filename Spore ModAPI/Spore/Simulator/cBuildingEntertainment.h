#pragma once

#include <Spore\Simulator\cBuilding.h>

#define cBuildingEntertainmentPtr eastl::intrusive_ptr<Simulator::cBuildingEntertainment>

namespace Simulator
{
	class cBuildingEntertainment
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0x1A55E4D;
		static const uint32_t NOUN_ID = 0x1A56ABA;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
	};
	ASSERT_SIZE(cBuildingEntertainment, 0x340);
}