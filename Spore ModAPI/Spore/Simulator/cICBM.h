#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cCombatant.h>

#define cICBMPtr eastl::intrusive_ptr<Simulator::cICBM>

namespace Simulator
{
	class cICBM
		/* 00h */ : public cGameData
		/* 34h */, public cLocomotiveObject
		/* 504h */, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x903C3EA3;
		static const uint32_t NOUN_ID = 0x49CEC61;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 518h */	int field_518;  // not initialized
		/* 51Ch */	int field_51C;  // not initialized
		/* 520h */	cCombatantPtr mpTarget;
	};
	ASSERT_SIZE(cICBM, 0x524);
}