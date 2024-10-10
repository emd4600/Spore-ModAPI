#pragma once

#include <Spore\Internal.h>
#include <EASTL\map.h>

namespace Simulator
{
	class cBaseSimulatorInputStrategy
	{
	public:
		/* 00h */	virtual ~cBaseSimulatorInputStrategy();
		/* 04h */	virtual void Initialize();
		/* 08h */	virtual void func08h(int, int);
		/* 0Ch */	virtual void func0Ch();
		/* 10h */	virtual void func10h();

	public:
		/* 04h */	eastl::map<int, int> field_4;
		/* 20h */	eastl::map<int, int> field_20;
	};
	ASSERT_SIZE(cBaseSimulatorInputStrategy, 0x3C);
}