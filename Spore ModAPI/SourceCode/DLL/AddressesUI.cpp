#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\UI\LayerManager.h>
#include <Spore\UI\SpaceGameUI.h>
#include <Spore\UI\cHintManager.h>

namespace UI
{
	namespace Addresses(cLayerManager) 
	{
		DefineAddress(Get, SelectAddress(0x67CC20, , 0x67CA90));
	}

	namespace Addresses(SpaceGameUI)
	{
		DefineAddress(Load, SelectAddress(0x10743F0, 0x1073730, 0x1073730));
	}

	namespace Addresses(cHintManager)
	{
		DefineAddress(Get, SelectAddress(0x67CC10, , 0x67CA80));
		DefineAddress(ShowHint, SelectAddress(0x67C980, , 0x67C7F0));
	}
}
#endif
