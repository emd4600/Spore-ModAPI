#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cCreatureBase.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\string.h>
#include <EASTL\map.h>

#define NpcTribeController (*Simulator::cNpcTribeController::Get())

namespace Simulator
{
	class cNpcTribeController
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0x11418FF;

		/// Returns the only cNpcTribeController instance; this function also creates
		/// that instance the first time it is called.
		static cNpcTribeController* Get();

	public:
		/* 10h */	cGonzagoTimer mPostTutorialDelayTimer_Mating;
		/* 30h */	cGonzagoTimer mPostTutorialDelayTimer_Food;
		/* 50h */	eastl::string16 field_50;
		/* 60h */	eastl::map<cCreatureBasePtr, cGonzagoTimer> mBabyGrowthTimers;
		/* 7Ch */	eastl::fixed_vector<ResourceKey, 5> mNPCTribeSpeciesKeys;
		/* D0h */	eastl::fixed_vector<cSpeciesProfile*, 5> mNPCTribeSpecies;
		/* FCh */	int mTribeAppearanceProperty;
	};
	ASSERT_SIZE(cNpcTribeController, 0x100);

	namespace Addresses(cNpcTribeController) {
		DeclareAddress(Get);  // 0xCC8330 0xCC8C90
	}
}