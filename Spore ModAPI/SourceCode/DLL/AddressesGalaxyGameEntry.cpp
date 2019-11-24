#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\GalaxyGameEntry\GlobalGGEUI.h>

namespace GalaxyGameEntry
{
	namespace Addresses(GlobalGGEUI)
	{
		DefineAddress(Initialize, SelectAddress(0xDE9290, 0xDEA200, 0xDEA1B0));
		DefineAddress(InitializeUI, SelectAddress(0xDE49E0, 0xDE5950, 0xDE5900));
	}
}
#endif
