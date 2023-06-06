#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cHerd.h>
#include <Spore\Simulator\cSpaceNames.h>
#include <Spore\Simulator\cBadgeManager.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\Simulator\cSimulatorUniverse.h>

namespace Simulator
{
	auto_METHOD(cHerd, cHerd*, Create,
		Args(const Vector3& position, cSpeciesProfile* pSpeciesProfile, int herdSize,
			bool isOwnedByAvatar, int creaturePersonality, bool createNest),
		Args(position, pSpeciesProfile, herdSize, isOwnedByAvatar, creaturePersonality, createNest));

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
}
#endif