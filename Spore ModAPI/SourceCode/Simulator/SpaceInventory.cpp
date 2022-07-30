#ifndef MODAPI_DLL_EXPORT

#include <Spore\Simulator\SubSystem\AnimalSpeciesManager.h>
#include <Spore\Simulator\SubSystem\PlantSpeciesManager.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cAnimalSpeciesManager, cAnimalSpeciesManager*, Get);

	auto_METHOD_VOID(cAnimalSpeciesManager, CreateAnimalItem,
		Args(cAnimalCargoInfoPtr& dst, const ResourceKey& speciesId, int count, bool isSentient),
		Args(dst, speciesId, count, isSentient));

	auto_STATIC_METHOD_(cPlantSpeciesManager, cPlantSpeciesManager*, Get);

	auto_METHOD(cPlantSpeciesManager, cPlantCargoInfo*, CreatePlantItem,
		Args(const ResourceKey& speciesId),
		Args(speciesId));

	auto_STATIC_METHOD_VOID(cSpaceInventoryItem, CreateMultiDeliveryObject,
		Args(cSpaceInventoryItem& dst, const ResourceKey& itemID, uint32_t instanceID),
		Args(dst, itemID, instanceID));
}

#endif
