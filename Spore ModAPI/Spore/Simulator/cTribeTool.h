#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>

#define cTribeToolPtr eastl::intrusive_ptr<Simulator::cTribeTool>

namespace Simulator
{
	class cTribeTool
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
		/* 120h */	, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0x116D858;
		static const uint32_t NOUN_ID = 0x18C8F0C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 1ECh */	uint32_t field_1EC; // value always seems to be 0x1984618, at least in player villages
		/* 1F0h */	int field_1F0;
		/* 1F4h */	int field_1F4;
		/* 1F8h */	int field_1F8;
		/* 1FCh */	uint32_t mToolType; // value seems usually to be 0x1b5e3868, at least in player villages
		/* 200h */	cGonzagoTimer mCreationTimer;
		/* 220h */	cGonzagoTimer mDestroyedTimer;
		/* 240h */	int field_240;
		/* 244h */	int field_244;
		/* 248h */	int mhFootprint;
	};
	ASSERT_SIZE(cTribeTool, 0x250);
}