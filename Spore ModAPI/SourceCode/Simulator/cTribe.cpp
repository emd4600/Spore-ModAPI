#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cTribeArchetype.h>

namespace Simulator
{
	auto_STATIC_METHOD(cTribeArchetype, cTribeArchetype*, GetTribeArchetype,
		Args(uint32_t archetype), Args(archetype));
}
#endif