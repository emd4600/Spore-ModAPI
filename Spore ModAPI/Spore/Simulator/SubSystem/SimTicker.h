#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <EASTL\list.h>

namespace Simulator
{
	class cSimTicker
		: public cStrategy
	{
	public:
		/* 50h */	virtual void AddSimulator(cGonzagoSimulator*) = 0;
		/* 54h */	virtual void RemoveSimulator(cGonzagoSimulator*) = 0;
		/* 58h */	virtual void ClearAllSimulators() = 0;
		// there are two methods more

	public:
		/* 1Ch */	eastl::list<cGonzagoSimulatorPtr> mSimulators;
		// If it was ticking when simulator was added, it gets added here
		/* 28h */	eastl::list<cGonzagoSimulatorPtr> mToAddSimulators;
		/* 34h */	eastl::list<int> field_34;
		/* 40h */	bool field_40;
		/* 41h */	bool mIsTicking;

	public:
		//GET B3D290
	};

	ASSERT_SIZE(cSimTicker, 0x44);
}