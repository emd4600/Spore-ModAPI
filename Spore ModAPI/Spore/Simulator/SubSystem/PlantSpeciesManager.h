#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cPlantCargoInfo.h>
#include <Spore\Resource\IPFRecord.h>

/// Accesses the current instance of Simulator::cPlantSpeciesManager
#define PlantSpeciesManager (*Simulator::cPlantSpeciesManager::Get())

namespace Simulator
{
	class cPlantSpeciesManager
		: public cStrategy
	{
	public:
		static cPlantSpeciesManager* Get();

		cPlantCargoInfo* CreatePlantItem(const ResourceKey& speciesId);

	public:
		// some sort of cache?
		/* 1Ch */	map<ResourceKey, Resource::IPFRecord*, less<ResourceKey>, ICoreAllocatorAdapter> field_1C;
	};
	ASSERT_SIZE(cPlantSpeciesManager, 0x3C);

	namespace Addresses(cPlantSpeciesManager)
	{
		DeclareAddress(Get);  // B3D380, B3D520
		DeclareAddress(CreatePlantItem);  // B8FEF0, B90560
	}
}
