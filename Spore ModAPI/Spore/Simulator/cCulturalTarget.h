#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cHitSphere.h>
#include <Spore\Simulator\cVehicle.h>

#define cCulturalTargetPtr eastl::intrusive_ptr<Simulator::cCulturalTarget>

namespace Simulator
{
	class cCulturalTarget
		/* 00h */	: public cGameData
		/* 34h */	, public cCombatant
		/* 100h */	, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x3D5C477;
		static const uint32_t NOUN_ID = 0x3D5C325;

	public:
		/* 1D4h */	int8_t mGateIndex;  // -1
		/* 1D8h */	int mAttackState;
		/* 1DCh */	uint32_t mAttackerPoliticalID;  // -1
		/* 1E0h */	eastl::vector<int> field_1E0;
		/* 1F4h */	eastl::vector<cVehiclePtr> mAttackers;
		/* 208h */	cHitSpherePtr mpHitSphere;
		/* 20Ch */	float field_20C;
		/* 210h */	float field_210;
		/* 214h */	int field_214;
	};
	ASSERT_SIZE(cCulturalTarget, 0x218);
}