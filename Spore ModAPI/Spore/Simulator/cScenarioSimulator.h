#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>

namespace Simulator
{
	class cScenarioSimulator
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0x75E1008;
		static const uint32_t NOUN_ID = 0x75E1005;

		static cScenarioSimulator* Get();

		// sub_F30830 struct copy, sub_F30240 constructor?

	public:
		/* 10h */	eastl::vector<int> field_10;
	};

	namespace Addresses(cScenarioSimulator)
	{
		DeclareAddress(Get);  // 0xC02AE0, 0xC033C0
	}
}