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
namespace Addresses(Audio)
{
	DefineAddress(PlayAudio, SelectAddress(0x436040, , 0x436390));
	DefineAddress(StopAudio, SelectAddress(0x571F40, , 0x572020));
	DefineAddress(PlayProceduralAudio, SelectAddress(0x571EA0, , 0x571F80));
	DefineAddress(SetProperty, SelectAddress(0x4360B0, , 0x436400));
	DefineAddress(SetPropertyString, SelectAddress(0x571F90, , 0x572070));
}
#endif
