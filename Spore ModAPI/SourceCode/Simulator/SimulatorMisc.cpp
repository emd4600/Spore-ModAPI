#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cHerd.h>

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
}
#endif