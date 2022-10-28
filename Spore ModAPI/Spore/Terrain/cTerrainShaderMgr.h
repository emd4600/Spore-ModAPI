#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\RenderWare\IndexBuffer.h>

#define TerrainShaderMgr (*Terrain::cTerrainShaderMgr::Get())

namespace Terrain
{
	enum class TerrainMaterialIndex : int
	{
		/// Used when rendering land above water level
		TerrainAbove = 0,  // 92571B44, used in land rendering
		/// Used when rendering land below water level (so the seabed land)
		TerrainBelow = 1,  // AABC7278
		TerrainWater = 2,  // F6882F5A
		TerrainLava = 3,  // AF478CD9
		TerrainIce = 4,  // 6AFA56E2
		TerrainAtmosphere = 5,  // 18EDB1F3
		TerrainDecal = 6,  // 1C87A08
		TerrainWaterDecal = 7,  // 328F9A63
		TerrainAndWaterDecal = 8,  // EAFC74F4
		TerrainDecalEmissive = 9,  // 22A17AD9
		TerrainDebug = 10,  // 83376FD2
	};

	class cTerrainShaderMgr
	{
	public:
		static cTerrainShaderMgr* Get();

		virtual ~cTerrainShaderMgr();

		Graphics::Material* GetMaterial(TerrainMaterialIndex index);

	public:
		/* 04h */	bool mInitialized;
		/* 05h */	bool field_5;
		/* 08h */	int mDebugTextureIndex;
		/* 0Ch */	Graphics::Material* mpTerrainBrushTestVisualizerMaterial;  // 2D68CD23
		/* 10h */	Graphics::Material* mpTerrainBrushGaussianMaterial;  // B22C80BA
		/* 14h */	Graphics::Material* mpTerrainBrushGaussianGlobalMaterial;  // 6C2BEA87
		/* 18h */	Graphics::Material* mpTerrainBrushGaussianLevelMaterial;  // D9C40DEA
		/* 1Ch */	Graphics::Material* mpTerrainBrushGaussianLevelGlobalMaterial;  // 6C4953B7
		/* 20h */	Graphics::Material* mpTerrainBrushGaussianFilterMaterial;  // FEAD7D14
		/* 24h */	Graphics::Material* mpTerrainBrushGaussianFilterErosionMaterial;  // 329FDDD
		/* 28h */	Graphics::Material* mpTerrainBrushPassThruMaterial;  // 2970DF3
		/* 2Ch */	Graphics::Material* mpTerrainBrushTextureMaterial;  // 142925AE
		/* 30h */	Graphics::Material* mpTerrainBrushTextureLevelMaterial;  // 5EEA035E
		/* 34h */	Graphics::Material* mpTerrainBrushTextureAboveMaterial;  // E8078E3B
		/* 38h */	Graphics::Material* mpTerrainBrushTextureBeachMaterial;  // 100CB7AD
		/* 3Ch */	Graphics::Material* mpTerrainBrushTextureCliffMaterial;  // 19E45172
		/* 40h */	Graphics::Material* mpTerrainBrushTextureDecalMaterial;  // 635B24F7
		/* 44h */	Graphics::Material* mpTerrainBrushCubemapMaterial;  // D1A5769C
		/* 48h */	Graphics::Material* mpTerrainBrushCubemapLevelMaterial;  // 37F12E74
		/* 4Ch */	Graphics::Material* mpTerrainBrushConvertTo16BitPackedMaterial;  // C3B73A93
		/* 50h */	Graphics::Material* mpTerrainBrushCopyMaterial;  // D55F5F50
		/* 54h */	Graphics::Material* mpTerrainBrushTextureAbsoluteMaxMaterial;  // 97BD4863
		/* 58h */	Graphics::Material* mpTerrainBrushTextureAbsoluteMinMaterial;  // BBED46D5
		/// Indexed with TerrainMaterialIndices
		/* 5Ch */	Graphics::Material* mTerrainMaterials[11];
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;
	};
	ASSERT_SIZE(cTerrainShaderMgr, 0x9C);

	namespace Addresses(cTerrainShaderMgr) 
	{
		DeclareAddress(Get);  // 0xF48E20 0xF48A20
	}
}
