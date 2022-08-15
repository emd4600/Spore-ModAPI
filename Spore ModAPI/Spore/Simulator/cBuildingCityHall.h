#pragma once

#include <Spore\Simulator\cBuilding.h>
#include <Spore\Simulator\cHitSphere.h>

#define cBuildingCityHallPtr eastl::intrusive_ptr<Simulator::cBuildingCityHall>

namespace Simulator
{
	class cBuildingCityHall
		: public cBuilding
	{
	public:
		static const uint32_t TYPE = 0x1007AE63;
		static const uint32_t NOUN_ID = 0x18EA1EB;

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
	ASSERT_SIZE(cBuildingCityHall, 0x378);
}