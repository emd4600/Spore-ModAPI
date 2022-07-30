#pragma once

#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cSpeciesProfile.h>

#define cAnimalCargoInfoPtr eastl::intrusive_ptr<Simulator::cAnimalCargoInfo>

namespace Simulator
{
	// created with AnimalSpeciesManager_CreateAnimalItem
	class cAnimalCargoInfo
		: public cSpaceInventoryItem
	{
	public:
		static const uint32_t TYPE = 0x30FC270B;

	public:
		/* 7Ch */	cSpeciesProfile* mpSpeciesProfile;
	};
	ASSERT_SIZE(cAnimalCargoInfo, 0x80);
}