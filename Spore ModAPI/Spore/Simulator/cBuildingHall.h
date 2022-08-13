#pragma once

#include <Spore\Simulator\cBuilding.h>
#include <Spore\Simulator\cHitSphere.h>

#define cBuildingHallPtr eastl::intrusive_ptr<Simulator::cBuildingHall>

namespace Simulator
{
	class cBuildingHall
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0x1007AE63;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 340h */	bool mbMoneyAddedThisTick;
		/* 341h */	bool field_341;  // true
		/* 344h */	cHitSpherePtr mpHitSphere;
		/* 348h */	int _padding_348[4];  // not initialized
		/* 358h */	cGonzagoTimer field_358;
	};
	ASSERT_SIZE(cBuildingHall, 0x378);
}