#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Audio\AudioSystem.h>

namespace Audio
{
	namespace Addresses(AudioSystem)
	{
		DefineAddress(Get, SelectAddress(0xA20620, NO_ADDRESS, 0xA20670));
		DefineAddress(PlayAudio, SelectAddress(0x436040, NO_ADDRESS, 0x436390));
	}
}
#endif
