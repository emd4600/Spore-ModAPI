#ifndef MODAPI_DLL_EXPORT
#include <Spore\Internal.h>
#include <Spore\Terrain\ITerrainResourceManager.h>
#include <Spore\Terrain\cTerrainMapSet.h>
#include <Spore\Terrain\Sphere\cTerrainSphere.h>

namespace Terrain
{
	auto_STATIC_METHOD_(ITerrainResourceManager, ITerrainResourceManager*, Get);

	auto_METHOD_const(cTerrainMapSet, float, GetHeight, Args(const Vector3& v), Args(v));

	namespace Sphere
	{
		auto_METHOD_VOID(cTerrainSphere, Generate, 
			Args(int* unused0, int* unused1, bool arg_8, bool generateSingleStep, float generateTimeLimit), 
			Args(unused0, unused1, arg_8, generateSingleStep, generateTimeLimit));
	}
}

#endif