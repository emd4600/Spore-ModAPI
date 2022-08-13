#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cBehaviorAgent.h>

#define cGamePlantPtr eastl::intrusive_ptr<Simulator::cGamePlant>

namespace Simulator
{
	class cGamePlant
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cBehaviorList
		/* 520h */	, public cCombatant
		/* 5E8h */	, public cBehaviorAgent
	{
	public:
		static const uint32_t TYPE = 0xAEB336B4;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 650h */	ResourceKey mSpecies;
		/* 65Ch */	ResourceKey field_65C;
		/* 668h */	int field_668;
		/* 66Ch */	float field_66C;  // 1.0
		/* 670h */	int field_670;
		/* 674h */	float field_674;  // -1.0
		/* 678h */	float field_678;  // 1.0
	};
	ASSERT_SIZE(cGamePlant, 0x680);
}