#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Swarm\cEffectsManager.h>
#include <Spore\Swarm\IEffectsManager.h>

namespace Swarm
{
	namespace Addresses(cSwarmManager)
	{
		DefineAddress(GetDirectoryAndEffectIndex, SelectAddress(0xA6D920, 0xA6D730, 0xA6D750));
	}
	namespace Addresses(cEffectsManager)
	{
		DefineAddress(GetDirectoryAndEffectIndex, SelectAddress(0xA6D920, 0xA6D730, 0xA6D750));
	}

	namespace Addresses(ISwarmManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEF0, 0x67DD90, 0x67DD90));
	}
	namespace Addresses(IEffectsManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEF0, 0x67DD90, 0x67DD90));
	}
}
#endif
