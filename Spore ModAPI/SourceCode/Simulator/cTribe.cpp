#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cTribeArchetype.h>
#include <Spore\Simulator\cTribe.h>

namespace Simulator
{
	auto_STATIC_METHOD(cTribeArchetype, cTribeArchetype*, GetTribeArchetype,
		Args(uint32_t archetype), Args(archetype));
	

	auto_STATIC_METHOD(Simulator, cTribe*, SpawnNpcTribe,
		Args(const Math::Vector3& position, int tribeArchetype, int numMembers, int arg0, bool arg1, cSpeciesProfile* species),
		Args(position, tribeArchetype, numMembers, arg0, arg1, species));
}
#endif