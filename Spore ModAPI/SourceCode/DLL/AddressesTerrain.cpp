#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Terrain\cTerrainSphere.h>
#include <Spore\Terrain\cTerrainSphereQuad.h>
#include <Spore\Terrain\cTerrainStateMgr.h>
#include <Spore\Terrain\ITerrainResourceManager.h>
#include <Spore\Terrain\TerrainRendering.h>

namespace Terrain
{
	namespace Addresses(ITerrainResourceManager)
	{
		DefineAddress(Get, SelectAddress(0xF48E40, 0xF48A40));
	}

	namespace Addresses(cTerrainMapSet) {
		DefineAddress(GetHeight, SelectAddress(0xF92C50, 0xF92760));
	}

	namespace Sphere
	{
		namespace Addresses(cTerrainSphere)
		{
			DefineAddress(Create, SelectAddress(0xFA29A0, 0xFA2350));
			DefineAddress(Generate, SelectAddress(0xF9BF30, 0xF9B860));
		}
	}
	namespace Addresses(cTerrainSphere)
	{
		DefineAddress(Create, SelectAddress(0xFA29A0, 0xFA2350));
		DefineAddress(Generate, SelectAddress(0xF9BF30, 0xF9B860));
		DefineAddress(PrepareShaderData, SelectAddress(0xF99010, 0xF98910));
		DefineAddress(RenderTerrainLand, SelectAddress(0xF985F0, 0xF97EF0));
		DefineAddress(RenderTerrainSeabedAsLand, SelectAddress(0xF98BD0, 0xF984D0));
		DefineAddress(RenderTerrainWater, SelectAddress(0xF986C0, 0xF97FC0));
		DefineAddress(RenderTerrainDecals, SelectAddress(0xF98810, 0xF98110));
		DefineAddress(RenderTerrainRibbons, SelectAddress(0xF9C2B0, 0xF9BBE0));
		DefineAddress(RenderTerrainAtmosphere, SelectAddress(0xF98870, 0xF98170));
		DefineAddress(GetSimDataRTT, SelectAddress(0xF96FF0, 0xF968B0));
		DefineAddress(RenderWaterReflectionAndRefraction, SelectAddress(0xFA62D0, 0xFA5C70));
		DefineAddress(RenderWaterRefraction, SelectAddress(0xFA3E70, 0xFA3810));
		DefineAddress(RenderWaterReflection, SelectAddress(0xF9CAE0, 0xF9C420));
		DefineAddress(MainRenderPass, SelectAddress(0xF9C370, 0xF9BCA0));
		DefineAddress(CreateRTTs, SelectAddress(0xFA0A20, 0xFA03C0));
	}

	namespace Addresses(cTerrainSphereQuad)
	{
		DefineAddress(Initialize, SelectAddress(0xFB5540, 0xFB4DE0));
		DefineAddress(LoadTerrainTransform, SelectAddress(0xFB73F3, 0xFB1750));
		DefineAddress(Draw, SelectAddress(0xFAF550, 0xFAEEC0));
		DefineAddress(RenderLand, SelectAddress(0xFB6DC0, 0xFB66A0));
		DefineAddress(RenderSeabedAsLand, SelectAddress(0xFB74F0, 0xFB6DD0));
		DefineAddress(RenderWater, SelectAddress(0xFB6F40, 0xFB6820));
		DefineAddress(RenderAtmosphere, SelectAddress(0xFB73C0, 0xFB6CA0));
		DefineAddress(RenderDecals, SelectAddress(0xFB36C0, 0xFB3010));
		DefineAddress(UpdateVertexBuffer, SelectAddress(0xFB6D20, 0xFB6600));
		DefineAddress(UpdateIndexBuffer, SelectAddress(0xFB4AE0, 0xFB4380));
	}

	namespace Addresses(cTerrainStateMgr) {
		DefineAddress(Initialize, SelectAddress(0xFC0BA0, 0xFC0480));
		DefineAddress(InitTextures, SelectAddress(0xFBE200, 0xFBDAE0));
		DefineAddress(ParseProp, SelectAddress(0xFBC820, 0xFBC100));
		DefineAddress(SetUserColorEnabled, SelectAddress(0xFBDDA0, 0xFBD680));
		DefineAddress(ApplyTerrainUserElevationColor, SelectAddress(0xFBF8B0, 0xFBF190));
		DefineAddress(ApplyTerrainUserWaterColor, SelectAddress(0xFB9930, 0xFB9210));
		DefineAddress(ApplyTerrainUserCliffColor, SelectAddress(0xFBDEA0, 0xFBD780));
		DefineAddress(ApplyTerrainUserBeachColor, SelectAddress(0xFBDDD0, 0xFBD6B0));
		DefineAddress(ApplyTerrainUserAtmosphereColor, SelectAddress(0xFB98C0, 0xFB91A0));
	}
}
namespace Addresses(Terrain)
{
#ifndef SDK_TO_GHIDRA
	DefineAddress(CurrentMaterialIndex_ptr, SelectAddress(0x15B5518, 0x15B1538));
	DefineAddress(CurrentQuadIndex_ptr, SelectAddress(0x15B551C, 0x15B153C));
	DefineAddress(TerrainRefractionBuffersRTT_ID_ptr, SelectAddress(0x15B51E0, 0x15B1200));
	DefineAddress(TerrainRefractionBuffersRTTTexture_ptr, SelectAddress(0x16CE0E8, 0x16C9E68));
	DefineAddress(TerrainRefractionBlur1RTT_ID_ptr, SelectAddress(0x15B51E8, 0x15B1208));
	DefineAddress(TerrainRefractionBlur2RTT_ID_ptr, SelectAddress(0x15B51F0, 0x15B1214));
	DefineAddress(TerrainRefractionViewer_ptr, SelectAddress(0x16CE358, 0x16CA0D8));
	DefineAddress(CreateRefractionRTTs, SelectAddress(0xF97220, 0xF96AE0));
	DefineAddress(DisposeRefractionRTTs, SelectAddress(0xF97340, 0xF96C00));
	DefineAddress(CreateReflectionRTTs, SelectAddress(0xF9E8F0, 0xF9E240));
	DefineAddress(DisposeReflectionRTTs, SelectAddress(0xF9E9C0, 0xF9E310));
	DefineAddress(CreateScatterRTTs, SelectAddress(0xF9E790, 0xF9E0E0));
	DefineAddress(TerrainBakeInScatterTexture_ptr, SelectAddress(0x16CE1D4, 0x16C9F54));	
	DefineAddress(TerrainScatterTexture_ptr, SelectAddress(0x16CE1D8, 0x16C9F58));
	DefineAddress(TerrainScatterViewer_ptr, SelectAddress(0x16CE1E0, 0x16C9F60));
	DefineAddress(TerrainSimDataTextures_ptr, SelectAddress(0x16CE0C4, 0x16C9E44));
	DefineAddress(TerrainSimDataRTTs_ID_ptr, SelectAddress(0x16CE654, 0x16CA3D4));
	DefineAddress(TerrainReflectionTexture_ptr, SelectAddress(0x16CE1DC, 0x16C9F5C));
	DefineAddress(TerrainReflectionViewer_ptr, SelectAddress(0x16CE4E0, 0x16CA260));
	DefineAddress(TerrainColorMapRTT_ID_ptr, SelectAddress(0x15B51F8, 0x15B1218));
	DefineAddress(TerrainColorMapRTT_ptr, SelectAddress(0x16CE0C0, 0x16C9E40));
	DefineAddress(TerrainColorMapViewer_ptr, SelectAddress(0x16CE690, 0x16CA410));
#else
	DefineAddress(sCurrentMaterialIndex, SelectAddress(0x15B5518, 0x15B1538));
	DefineAddress(sCurrentQuadIndex, SelectAddress(0x15B551C, 0x15B153C));
	DefineAddress(sTerrainRefractionBuffersRTT_ID, SelectAddress(0x15B51E0, 0x15B1200));
	DefineAddress(sTerrainRefractionBuffersRTTTexture, SelectAddress(0x16CE0E8, 0x16C9E68));
	DefineAddress(sTerrainRefractionBlur1RTT_ID, SelectAddress(0x15B51E8, 0x15B1208));
	DefineAddress(sTerrainRefractionBlur2RTT_ID, SelectAddress(0x15B51F0, 0x15B1214));
	DefineAddress(sTerrainRefractionViewer, SelectAddress(0x16CE358, 0x16CA0D8));
	DefineAddress(CreateRefractionRTTs, SelectAddress(0xF97220, 0xF96AE0));
	DefineAddress(DisposeRefractionRTTs, SelectAddress(0xF97340, 0xF96C00));
	DefineAddress(CreateReflectionRTTs, SelectAddress(0xF9E8F0, 0xF9E240));
	DefineAddress(DisposeReflectionRTTs, SelectAddress(0xF9E9C0, 0xF9E310));
	DefineAddress(CreateScatterRTTs, SelectAddress(0xF9E790, 0xF9E0E0));
	DefineAddress(sTerrainBakeInScatterTexture, SelectAddress(0x16CE1D4, 0x16C9F54));
	DefineAddress(sTerrainScatterTexture, SelectAddress(0x16CE1D8, 0x16C9F58));
	DefineAddress(sTerrainScatterViewer, SelectAddress(0x16CE1E0, 0x16C9F60));
	DefineAddress(sTerrainSimDataTextures, SelectAddress(0x16CE0C4, 0x16C9E44));
	DefineAddress(sTerrainSimDataRTTs_ID, SelectAddress(0x16CE654, 0x16CA3D4));
	DefineAddress(sTerrainReflectionTexture, SelectAddress(0x16CE1DC, 0x16C9F5C));
	DefineAddress(sTerrainReflectionViewer, SelectAddress(0x16CE4E0, 0x16CA260));
	DefineAddress(sTerrainColorMapRTT_ID, SelectAddress(0x15B51F8, 0x15B1218));
	DefineAddress(sTerrainColorMapRTT, SelectAddress(0x16CE0C0, 0x16C9E40));
	DefineAddress(sTerrainColorMapViewer, SelectAddress(0x16CE690, 0x16CA410));
#endif
}
#endif
