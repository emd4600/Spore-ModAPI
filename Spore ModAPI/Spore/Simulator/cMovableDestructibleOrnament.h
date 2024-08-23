#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cBehaviorAgent.h>

#define cMovableDestructibleOrnamentPtr eastl::intrusive_ptr<Simulator::cMovableDestructibleOrnament>

namespace Simulator
{
	class cMovableDestructibleOrnament
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 508h */	, public cCombatant
		/* 5D0h */	, public cBehaviorAgent
	{
	public:
		static const uint32_t TYPE = 0x283D961;
		static const uint32_t NOUN_ID = 0x283DDB1;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
	};
	ASSERT_SIZE(cMovableDestructibleOrnament, 0x638);
}