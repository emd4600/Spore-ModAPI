#pragma once

#include <Spore\Simulator\cBuilding.h>

#define cBuildingIndustryPtr eastl::intrusive_ptr<Simulator::cBuildingIndustry>

namespace Simulator
{
	class cBuildingIndustry
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0xECADE42;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
	};
	ASSERT_SIZE(cBuildingIndustry, 0x340);
}