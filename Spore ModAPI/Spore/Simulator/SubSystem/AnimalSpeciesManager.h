#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cAnimalCargoInfo.h>

/// Accesses the current instance of Simulator::cAnimalSpeciesManager
#define AnimalSpeciesManager (*Simulator::cAnimalSpeciesManager::Get())

namespace Simulator
{
	class cAnimalSpeciesManager
		: public cStrategy
	{
	public:
		static cAnimalSpeciesManager* Get();

		/// Creates a cAnimalCargoInfo, which is a cargo item for an animal. This is also used to
		/// create sentient animals (that is, citizens) cargo items, with the last parameter to true.
		/// @param dst Pointer where the created object will be written.
		/// @param speciesId ID of the animal species (id to a .crt file)
		/// @param count How many units will the cargo item have, 1 by default.
		/// @param isSentient True if the creature is sentient (citizen), false otherwise.
		void CreateAnimalItem(cAnimalCargoInfoPtr& dst, const ResourceKey& speciesId, int count = 1, bool isSentient = false);
	};

	namespace Addresses(cAnimalSpeciesManager)
	{
		DeclareAddress(Get);  // 0xB3D3B0, 0xB3D550
		DeclareAddress(CreateAnimalItem);  // 0xAC0E90, 0xAC0C00
	}
}
