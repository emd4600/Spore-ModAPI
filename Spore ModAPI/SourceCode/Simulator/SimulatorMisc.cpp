#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cHerd.h>
#include <Spore\Simulator\cSpaceNames.h>

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

	string16 cSpaceNames::GenerateRandomName(SpaceNamesType arg)
	{
		string16 dst;
		CALL(GetAddress(cSpaceNames, GenerateRandomName), void, 
			Args(cSpaceNames*, string16&, SpaceNamesType), Args(this, dst, arg));
		return dst;
	}
}
#endif