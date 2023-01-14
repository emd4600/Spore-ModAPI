#pragma once

#include <Spore\Graphics\Texture.h>
#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\App\cViewer.h>
#include <Spore\Terrain\cTerrainShaderMgr.h>

namespace Terrain
{
	TerrainMaterialIndex GetActiveMaterialIndex();
	void SetActiveMaterialIndex(TerrainMaterialIndex material);

	int GetActiveQuadIndex();
	void SetActiveQuadIndex(int index);

	bool IsActiveQuadMaterial(TerrainMaterialIndex material, int quadIndex);
	void SetActiveQuadMaterial(TerrainMaterialIndex material, int quadIndex);


	RenderWare::IndexBuffer* GetAtmosphereIndexBuffer();  //TODO

	/// Creates the "TerrainRefractionBuffers", "TerrainRefractionBlur1" and "TerrainRefractionBlur2"
	/// render target textures, used for water refraction.
	/// Source code: @ref SourceCode-Terrain-Misc-CreateTerrainRefractionRTTs
	void CreateRefractionRTTs();  //TODO

	/// Disposes the terrain refraction render target textures.
	/// Source code: @ref SourceCode-Terrain-Misc-DisposeTerrainRefractionRTTs
	void DisposeRefractionRTTs();  //TODO

	Graphics::RenderTargetID* GetRefractionBuffersRenderTargetID();
	Graphics::Texture* GetRefractionBuffersRenderTargetTexture();
	RenderWare::Raster* GetRefractionBuffersRenderTarget();
	void SetRefractionBuffersRenderTargetTexture(Graphics::Texture* texture);

	Graphics::RenderTargetID* GetRefractionBlur1RenderTargetID();
	Graphics::RenderTargetID* GetRefractionBlur2RenderTargetID();

	/// Returns the camera configuration used to render the water refraction textures.
	/// @returns
	App::cViewer* GetRefractionViewer();

	/// Creates the render target texture used for water reflection.
	/// Source code: @ref SourceCode-Terrain-Misc-CreateReflectionRTTs
	void CreateReflectionRTTs();

	void DisposeReflectionRTTs();

	TexturePtr& GetReflectionTexture();
	App::cViewer* GetReflectionViewer();

	/// Creates render targets for scatter texture.
	/// Source code: @ref SourceCode-Terrain-Misc-CreateScatterRTTs
	void CreateScatterRTTs();

	TexturePtr& GetBakeInScatterTexture();
	TexturePtr& GetScatterTexture();
	App::cViewer* GetScatterViewer();

	/// Returns an array of 6 render target textures used for "SimData", which apparently controls planet
	/// color for each of the 6 terrain quads.
	/// @returns
	Graphics::Texture** GetSimDataRenderTargetTextures();

	/// Returns an array of 6 render target textures IDs used for "SimData".
	/// @returns
	Graphics::RenderTargetID* GetSimDataRenderTargetIDs();

	Graphics::RenderTargetID* GetColorMapID();
	RenderWare::Raster* GetColorMap();
	void SetColorMap(RenderWare::Raster* pRaster);
	App::cViewer* GetColorMapViewer();
}

namespace Addresses(Terrain)
{
	DeclareAddress(CurrentMaterialIndex_ptr);  // 0x15B5518 0x15B1538
	DeclareAddress(CurrentQuadIndex_ptr);  // 0x15B551C 0x15B153C
	DeclareAddress(TerrainRefractionBuffersRTT_ID_ptr);  // 0x15B51E0 0x15B1200
	DeclareAddress(TerrainRefractionBuffersRTTTexture_ptr);  // 0x16CE0E8 0x16C9E68
	DeclareAddress(TerrainRefractionBlur1RTT_ID_ptr);  // 0x15B51E8 0x15B1208
	DeclareAddress(TerrainRefractionBlur2RTT_ID_ptr);  // 0x15B51F0 0x15B1214
	DeclareAddress(TerrainRefractionViewer_ptr);  // 0x16CE358 0x16CA0D8
	DeclareAddress(CreateRefractionRTTs);  // 0xF97220 0xF96AE0
	DeclareAddress(DisposeRefractionRTTs);  // 0xF97340 0xF96C00
	DeclareAddress(CreateReflectionRTTs);  // 0xF9E8F0 0xF9E240
	DeclareAddress(DisposeReflectionRTTs);  // 0xF9E9C0 0xF9E310
	DeclareAddress(CreateScatterRTTs);  // 0xF9E790 0xF9E0E0
	DeclareAddress(TerrainBakeInScatterTexture_ptr);  // 0x16CE1D4 0x16C9F54
	DeclareAddress(TerrainScatterTexture_ptr);  // 0x16CE1D8 0x16C9F58
	DeclareAddress(TerrainScatterViewer_ptr);  // 0x16CE1E0 0x16C9F60
	DeclareAddress(TerrainSimDataTextures_ptr);  // 0x16CE0C4 0x16C9E44
	DeclareAddress(TerrainSimDataRTTs_ID_ptr);  // 0x16CE654 0x16CA3D4
	DeclareAddress(TerrainReflectionTexture_ptr);  // 0x16CE1DC 0x16C9F5C
	DeclareAddress(TerrainReflectionViewer_ptr);  // 0x16CE4E0 0x16CA260
	DeclareAddress(TerrainColorMapRTT_ID_ptr);  // 0x15B51F8 0x15B1218
	DeclareAddress(TerrainColorMapRTT_ptr);  // 0x16CE0C0 0x16C9E40
	DeclareAddress(TerrainColorMapViewer_ptr);  // 0x16CE690 0x16CA410
}

#ifdef SDK_TO_GHIDRA
namespace Terrain
{
	Terrain::TerrainMaterialIndex sCurrentMaterialIndex;
	int sCurrentQuadIndex;
	ResourceID sTerrainRefractionBuffersRTT_ID;
	Graphics::Texture* sTerrainRefractionBuffersRTTTexture;
	ResourceID sTerrainRefractionBlur1RTT_ID;
	ResourceID sTerrainRefractionBlur2RTT_ID;
	App::cViewer sTerrainRefractionViewer;
	eastl::intrusive_ptr<Graphics::Texture> sTerrainBakeInScatterTexture;
	eastl::intrusive_ptr<Graphics::Texture> sTerrainScatterTexture;
	App::cViewer sTerrainScatterViewer;
	eastl::intrusive_ptr<Graphics::Texture> sTerrainSimDataTextures[6];
	ResourceID sTerrainSimDataRTTs_ID[6];
	eastl::intrusive_ptr<Graphics::Texture> sTerrainReflectionTexture;
	App::cViewer sTerrainReflectionViewer;
	ResourceID sTerrainColorMapRTT_ID;
	RenderWare::Raster* sTerrainColorMapRTT;
	App::cViewer sTerrainColorMapViewer;
}
#endif
