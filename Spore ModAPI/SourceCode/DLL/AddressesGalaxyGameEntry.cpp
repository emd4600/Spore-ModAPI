#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\GalaxyGameEntry\GlobalGGEUI.h>

namespace GalaxyGameEntry
{
	namespace Addresses(GlobalGGEUI)
	{
		DefineAddress(Initialize, SelectAddress(0xDE9290, 0xDEA1B0));
		DefineAddress(InitializeUI, SelectAddress(0xDE49E0, 0xDE5900));

		DefineAddress(ptr, SelectAddress(0x16A55C4, 0x16A1344));
	}
}

#ifdef SDK_TO_GHIDRA
namespace Addresses(GalaxyGameEntry)
{
	DefineAddress(sGlobalGGEUI, SelectAddress(0x16A55C4, 0x16A1344));
}
#endif

#endif
