#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cCreatureBase.h>

#define cEggPtr eastl::intrusive_ptr<Simulator::cEgg>

namespace Simulator
{
	class cHerd;

	/// Default model is `0x00000000!0xA76CD528`, default `mMaterialType` is 5.
	class cEgg
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
		/* 120h */	, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0x2A0349A;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 1E8h */	int mState;
		/* 1ECh */	bool field_1EC;  // true
		/* 1F0h */	int mTimeToHatch;  // 10000
		/* 1F4h */	intrusive_ptr<cHerd> mpHerd;
		/* 1F8h */	cGonzagoTimer mBrokenTimer;
		/* 218h */	cCreatureBasePtr mpToHatch;
		/* 21Ch */	ObjectPtr field_21C;
		/* 220h */	float mEffectScale;  // 1.0
	};
	ASSERT_SIZE(cEgg, 0x228);
}