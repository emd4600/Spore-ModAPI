#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Anim\IAnimManager.h>

namespace Anim
{
	namespace Addresses(IAnimManager)
	{
		DefineAddress(Get, SelectAddress(0x67CC70, , 0x67CAE0));
	}
}

#endif