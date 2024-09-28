#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cHerd.h>
#include <Spore\Simulator\cSpaceNames.h>
#include <Spore\Simulator\cBadgeManager.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\Simulator\cSimulatorUniverse.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\SubSystem\GamePersistenceManager.h>
#include <Spore\Simulator\SubSystem\CinematicManager.h>
#include <Spore\Simulator\cDefaultToolProjectile.h>
#include <Spore\Simulator\cArtilleryProjectile.h>
#include <Spore\Simulator\cCulturalProjectile.h>
#include <Spore\Simulator\cFlakProjectile.h>
#include <Spore\Simulator\cResourceProjectile.h>
#include <Spore\Simulator\cSpaceDefenseMissile.h>
#include <Spore\Simulator\cCollectableItems.h>
#include <Spore\Simulator\cPlanetaryArtifact.h>

namespace Simulator
{
	void cHerd::SetEnabled(bool enabled)
	{
		mbEnabled = enabled;
		if (mpNest) mpNest->mbEnabled = enabled;
		for (auto egg : mEggs) {
			egg->mEnabled = enabled;
		}
	}


	auto_STATIC_METHOD_(cSpaceNames, cSpaceNames*, Get);

	eastl::string16 cSpaceNames::GenerateRandomName(SpaceNamesType arg)
	{
		eastl::string16 dst;
		CALL(GetAddress(cSpaceNames, GenerateRandomName), void, 
			Args(cSpaceNames*, eastl::string16&, SpaceNamesType), Args(this, dst, arg));
		return dst;
	}


	auto_METHOD_VOID(cBadgeManager, AddToBadgeProgress,
		Args(BadgeManagerEvent badge, int addedValue), Args(badge, addedValue));


	//// cObjectPool ////

	cObjectPool_::cObjectPool_()
		: mpData(nullptr)
	{}

	cObjectPool_::~cObjectPool_()
	{
		CALL(GetAddress(cObjectPool_, _dtor), void, Args(cObjectPool_*), Args(this));
	}

	auto_METHOD_VOID(cObjectPool_, Initialize, Args(int objectSize, int numObjects), Args(objectSize, numObjects));

	auto_METHOD_VOID_(cObjectPool_, Clear);

	auto_METHOD(cObjectPool_, cObjectPoolClass*, Get, Args(cObjectPoolIndex arg), Args(arg));

	auto_METHOD(cObjectPool_, cObjectPoolClass*, GetIfNotDeleted, Args(cObjectPoolIndex arg), Args(arg));

	auto_METHOD_(cObjectPool_, cObjectPoolIndex, CreateObject);

	auto_METHOD_VOID(cObjectPool_, DeleteObject, Args(cObjectPoolIndex arg), Args(arg));

	auto_METHOD_const(cObjectPool_, cObjectPoolClass*, Iterate, Args(Iterator& arg), Args(arg));


	//// cSimulatorUniverse ////

	cSimulatorUniverse* cSimulatorUniverse::Get()
	{
		return *(cSimulatorUniverse**)GetAddress(cSimulatorUniverse, _ptr);
	}

	//// GamePersistenceManager ////

	auto_STATIC_METHOD_(cGamePersistenceManager, cGamePersistenceManager*, Get);


	//// cSpeciesProfile ////

	auto_METHOD_VOID(cSpeciesProfile, GetSpeciesName, Args(eastl::string16& dst), Args(dst));


	//// cIdentityColorable ////

	auto_METHOD_VOID(cIdentityColorable, AssignNames, Args(const eastl::string16& speciesName), Args(speciesName));

	//// cDefaultToolProjectile ////

	auto_STATIC_METHOD_VOID(Simulator, LaunchDefaultToolProjectile,
		Args(cSpaceToolData* tool, cDefaultToolProjectile* projectile, const Math::Vector3& origin, const Math::Vector3& target),
		Args(tool, projectile, origin, target));


	//// cArtilleryProjectile ////

	auto_METHOD_VOID(cArtilleryProjectile, LaunchProjectile, Args(const Math::Vector3& target), Args(target));


	//// cCulturalProjectile ////

	auto_METHOD_VOID(cCulturalProjectile, LaunchProjectile, 
		Args(cGameData* owner, cVehicle* vehicle, cSpaceToolData* tool, cCombatant* target, const Math::Vector3& unk0, float unk1, bool unk2, bool spin),
		Args(owner, vehicle, tool, target, unk0, unk1, unk2, spin));


	//// cFlakProjectile ////

	auto_METHOD_VOID(cFlakProjectile, LaunchProjectile, Args(const Math::Vector3& target, float arg), Args(target, arg));


	//// cResourceProjectile ////

	auto_METHOD_VOID(cResourceProjectile, LaunchProjectile,
		Args(cCivilization* civilization, cCommodityNode* commodityNode, const Math::Vector3& arg0, float speed, bool arg1),
		Args(civilization, commodityNode, arg0, speed, arg1));

	//// cSpaceDefenseMissile ////

	auto_METHOD_VOID(cSpaceDefenseMissile, LaunchProjectile, Args(const Math::Vector3& target, cCombatant* arg), Args(target, arg));


	//// cCollectableItems ////

	auto_METHOD_VOID(cCollectableItems, LoadConfig, 
		Args(uint32_t configGroupID, uint32_t configInstanceID, uint32_t itemsGroupID),
		Args(configGroupID, configInstanceID, itemsGroupID));

	auto_METHOD_VOID(cCollectableItems, AddUnlockableItem,
		Args(uint32_t instanceID, uint32_t groupID, int itemUnlockLevel, uint32_t categoryID, int row, int column, int pageIndex, float itemUnlockFindPercentage, uint32_t itemUnlockEffect),
		Args(instanceID, groupID, itemUnlockLevel, categoryID, row, column, pageIndex, itemUnlockFindPercentage, itemUnlockEffect));

	auto_METHOD(cCollectableItems, bool, AddUnlockableItemFromProp,
		Args(struct ResourceKey key, uint32_t categoryID, int row, int column, int pageIndex),
		Args(key, categoryID, row, column, pageIndex));

	auto_METHOD_VOID(cCollectableItems, sub_597390,
		Args(eastl::vector<int>& dst, struct cCollectableItemID itemID, int unk),
		Args(dst, itemID, unk));


	eastl::fixed_vector<eastl::pair<uint32_t, int>, 16>& GetCreatureGameUnlockCategoriesCount() {
		return *(eastl::fixed_vector<eastl::pair<uint32_t, int>, 16>*)(GetAddress(Simulator, sCreatureGameUnlockCategoriesCount));
	}


	//// cPlanetaryArtifact ////

	auto_METHOD_VOID_(cPlanetaryArtifact, SetLocomotion);

	auto_METHOD_VOID(cPlanetaryArtifact, LoadFromItem, 
		Args(SpaceInventoryItemType itemType, const ResourceKey& itemKey, int count, bool arg),
		Args(itemType, itemKey, count, arg));

	//// CinematicManager ////

	auto_STATIC_METHOD_(cCinematicManager, cCinematicManager*, Get);

	auto_METHOD_VOID(cCinematicManager, PlayCinematic,
		Args(const char* cinematicName, int arg0, int arg1, int arg2, int arg3, int arg4),
		Args(cinematicName, arg0, arg1, arg2, arg3, arg4));

	CinematicActionFunction_t CinematicAction::GetStartVignetteFunction() {
		return (CinematicActionFunction_t)(GetAddress(CinematicAction, StartVignetteFunction_ptr));
	}
}
#endif