#pragma once

#include <Spore\Simulator\cGonzagoTimer.h>
#include <EASTL\list.h>

namespace Simulator
{
	class cBaseDisplayStrategy
	{
	public:
		virtual ~cBaseDisplayStrategy();
		virtual void func04h(int) {};

	public:
		/* 04h */	int field_4;  // not initialized
		/* 08h */	eastl::list<int> field_8;
		/* 18h */	cGonzagoTimer field_18;
	};
	ASSERT_SIZE(cBaseDisplayStrategy, 0x38);
}