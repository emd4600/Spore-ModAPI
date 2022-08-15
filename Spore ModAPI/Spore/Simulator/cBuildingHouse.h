#pragma once

#include <Spore\Simulator\cBuilding.h>

#define cBuildingHousePtr eastl::intrusive_ptr<Simulator::cBuildingHouse>

namespace Simulator
{
	class cBuildingHouse
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0xFF10521;
		static const uint32_t NOUN_ID = 0x18EB106;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
	};
	ASSERT_SIZE(cBuildingHouse, 0x340);
}