#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Terrain\Sphere\cTerrainSphere.h>

namespace Terrain
{
	namespace Sphere
	{
		namespace Addresses(cTerrainSphere)
		{
			DefineAddress(Create, SelectAddress(0xFA29A0, NO_ADDRESS, 0xFA2350));
		}
	}
}
#endif
