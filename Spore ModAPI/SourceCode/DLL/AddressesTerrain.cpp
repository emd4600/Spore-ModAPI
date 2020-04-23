#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Terrain\Sphere\cTerrainSphere.h>
#include <Spore\Terrain\ITerrainResourceManager.h>

namespace Terrain
{
	namespace Addresses(ITerrainResourceManager)
	{
		DefineAddress(Get, SelectAddress(0xF48E40, , 0xF48A40));
	}

	namespace Addresses(cTerrainMapSet) {
		DefineAddress(GetHeight, SelectAddress(0xF92C50, , 0xF92760));
	}

	namespace Sphere
	{
		namespace Addresses(cTerrainSphere)
		{
			DefineAddress(Create, SelectAddress(0xFA29A0, , 0xFA2350));
			DefineAddress(Generate, SelectAddress(0xF9BF30, , 0xF9B860));
		}
	}
}
#endif
