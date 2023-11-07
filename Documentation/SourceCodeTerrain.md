@page SourceCode-Terrain Source Code: Terrain
@brief Some reconstructed Spore source code for the Terrain namespace

@tableofcontents

@section SourceCode-Terrain-cTerrainSphereQuad Terrain::cTerrainSphereQuad

@subsection SourceCode-Terrain-cTerrainSphereQuad-RenderLand cTerrainSphereQuad::RenderLand()

Code for Terrain::cTerrainSphereQuad::RenderLand()

```cpp
void cTerrainSphereQuad::RenderLand(App::cViewer* pViewer, Graphics::RenderStatistics& stats)
{
	UpdateBuffers();
	if (mIndicesCount > 0)
	{
		LoadTerrainTransform(pViewer);
		RenderWare::TextureSlot slots[4];
		if (!IsActiveQuadMaterial(TerrainMaterialIndex::TerrainAbove, mIndex))
		{
			SetActiveQuadMaterial(TerrainMaterialIndex::TerrainAbove, mIndex);
			auto materialState = TerrainShaderMgr.GetMaterial(TerrainMaterialIndex::TerrainAbove)->GetState();
			slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
			slots[1].SetTexture(materialState, 1, mpSphere->GetTerrainStateManager()->mTextures.mpTextureAboveDetail2->GetRaster());
			slots[2].SetTexture(materialState, 2, mpSphere->GetSimDataRTT(mIndex));
			slots[3].SetTexture(materialState, 3, GetScatterTexture()->GetRaster());
		}
		Draw(mpMesh->vertexBuffer, mpMesh->indexBuffer, 0, mIndicesCount);
		stats.numVerticesRendered += mpMesh->vertexBuffer->vertexCount;
		stats.numIndicesRendered += mIndicesCount;
		stats.numDrawCalls++;
	}
}
```

@subsection SourceCode-Terrain-cTerrainSphereQuad-RenderSeabedAsLand cTerrainSphereQuad::RenderSeabedAsLand()

Code for Terrain::cTerrainSphereQuad::RenderSeabedAsLand()

```cpp
void cTerrainSphereQuad::RenderSeabedAsLand(App::cViewer* pViewer, Graphics::RenderStatistics& stats)
{
	UpdateBuffers();
	if (mIndicesCount > 0)
	{
		LoadTerrainTransform(pViewer);
		RenderWare::TextureSlot slots[3];
		if (!IsActiveQuadMaterial(TerrainMaterialIndex::TerrainBelow, mIndex))
		{
			SetActiveQuadMaterial(TerrainMaterialIndex::TerrainBelow, mIndex);
			auto materialState = TerrainShaderMgr.GetMaterial(TerrainMaterialIndex::TerrainBelow)->GetState();
			slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
			slots[1].SetTexture(materialState, 1, mpSphere->GetQuadHeightMap(mIndex));
			slots[2].SetTexture(materialState, 2, mpSphere->GetSimDataRTT(mIndex));
		}
		Draw(mpMesh->vertexBuffer, mpMesh->indexBuffer, 0, mIndicesCount);
		stats.numVerticesRendered += mpMesh->vertexBuffer->vertexCount;
		stats.numIndicesRendered += mIndicesCount;
		stats.numDrawCalls++;
	}
}
```

@subsection SourceCode-Terrain-cTerrainSphereQuad-RenderWater cTerrainSphereQuad::RenderWater()

Code for Terrain::cTerrainSphereQuad::RenderWater()

```cpp
void cTerrainSphereQuad::RenderWater(App::cViewer* pViewer, Graphics::RenderStatistics& stats, TerrainMaterialIndex material, int flags)
{
	UpdateBuffers();
	if (mWaterIndicesCount > 0)
	{
		LoadTerrainTransform(pViewer);
		RenderWare::TextureSlot slots[8];
		if (!IsActiveQuadMaterial(material, mIndex))
		{
			SetActiveQuadMaterial(material, mIndex);
			auto materialState = TerrainShaderMgr.GetMaterial(TerrainMaterialIndex::TerrainBelow)->GetState();
			auto& terrainTextures = mpSphere->GetTerrainStateManager()->mTextures;
			switch (material)
			{
			case TerrainMaterialIndex::TerrainAbove:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
				slots[1].SetTexture(materialState, 1, mpSphere->GetTerrainStateManager()->mTextures.mpTextureAboveDetail2->GetRaster());
				slots[2].SetTexture(materialState, 2, mpSphere->GetSimDataRTT(mIndex));
				slots[3].SetTexture(materialState, 3, GetScatterTexture()->GetRaster());
				break;
			case TerrainMaterialIndex::TerrainWater:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadHeightMap(mIndex));
				slots[1].SetTexture(materialState, 1, terrainTextures.mpWaterPCAComponent0->GetRaster());
				slots[2].SetTexture(materialState, 2, terrainTextures.mpWaterFoamCutMap->GetRaster());
				slots[3].SetTexture(materialState, 3, terrainTextures.mpWaterPCAComponent1->GetRaster());
				slots[4].SetTexture(materialState, 4, GetScatterTexture()->GetRaster());
				slots[5].SetTexture(materialState, 5, GetRefractionBuffersRenderTarget());
				break;
			case TerrainMaterialIndex::TerrainIce:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
				slots[1].SetTexture(materialState, 1, mpSphere->GetQuadHeightMap(mIndex));
				slots[2].SetTexture(materialState, 2, terrainTextures.mpTextureBelow->GetRaster());
				slots[3].SetTexture(materialState, 3, terrainTextures.mpIceDetailNear->GetRaster());
				slots[4].SetTexture(materialState, 4, terrainTextures.mpIceRamp->GetRaster());
				slots[5].SetTexture(materialState, 5, terrainTextures.mpIceDetailMid->GetRaster());
				slots[6].SetTexture(materialState, 6, GetScatterTexture()->GetRaster());
				break;
			case TerrainMaterialIndex::TerrainLava:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
				slots[1].SetTexture(materialState, 1, mpSphere->GetQuadHeightMap(mIndex));
				slots[2].SetTexture(materialState, 2, terrainTextures.mpLavaRamp->GetRaster());
				slots[3].SetTexture(materialState, 3, terrainTextures.mpTextureBelow->GetRaster());
				slots[4].SetTexture(materialState, 4, terrainTextures.mpWaterPCAComponent0->GetRaster());
				slots[5].SetTexture(materialState, 5, terrainTextures.mpLavaDetail->GetRaster());
				slots[6].SetTexture(materialState, 6, terrainTextures.mpWaterPCAComponent1->GetRaster());
				slots[7].SetTexture(materialState, 7, GetScatterTexture()->GetRaster());
				break;
			case TerrainMaterialIndex::TerrainBelow:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
				slots[1].SetTexture(materialState, 1, mpSphere->GetTerrainStateManager()->mTextures.mpTextureAboveDetail2->GetRaster());
				slots[2].SetTexture(materialState, 2, mpSphere->GetSimDataRTT(mIndex));
				break;
			case TerrainMaterialIndex::TerrainAtmosphere:
				slots[0].SetTexture(materialState, 0, GetScatterTexture()->GetRaster());
				slots[1].SetTexture(materialState, 1, terrainTextures.mpAtmospherePackedCurves->GetRaster());
				break;
			case TerrainMaterialIndex::TerrainDecal:
			case TerrainMaterialIndex::TerrainWaterDecal:
			case TerrainMaterialIndex::TerrainAndWaterDecal:
			case TerrainMaterialIndex::TerrainDecalEmissive:
				slots[0].SetTexture(materialState, 0, mpSphere->GetQuadNormalMap(mIndex));
				slots[1].SetTexture(materialState, 1, nullptr);
				slots[2].SetTexture(materialState, 2, GetScatterTexture()->GetRasterSafe());
				break;
			case TerrainMaterialIndex::TerrainDebug:
				RenderWare::Raster* rasters[4];
				rasters[0] = mpSphere->GetQuadHeightMap(mIndex);
				rasters[1] = mpSphere->GetQuadNormalMap(mIndex);
				rasters[2] = mpSphere->GetQuadControlMap(mIndex);
				rasters[3] = mpSphere->GetSimDataRTT(mIndex);
				slots[0].SetTexture(materialState, 0, rasters[TerrainShaderMgr.mDebugTextureIndex]);
				break;
			}
			materialState->Load();
		}
		Draw(mpMesh->vertexBuffer, mpMesh->indexBuffer, mWaterIndicesStart, mWaterIndicesCount);
		stats.numVerticesRendered += mpMesh->vertexBuffer->vertexCount;
		stats.numIndicesRendered += mWaterIndicesCount;
		stats.numDrawCalls++;
	}
}
```

@subsection SourceCode-Terrain-cTerrainSphereQuad-RenderAtmosphere cTerrainSphereQuad::RenderAtmosphere()

Code for Terrain::cTerrainSphereQuad::RenderAtmosphere()

```cpp
void cTerrainSphereQuad::RenderAtmosphere(App::cViewer* pViewer, Graphics::RenderStatistics& stats)
{
	UpdateBuffers();
	if (mIndicesCount > 0)
	{
		LoadTerrainTransform(pViewer);
		RenderWare::TextureSlot slots[2];
		if (!IsActiveQuadMaterial(TerrainMaterialIndex::TerrainAtmosphere, mIndex))
		{
			SetActiveQuadMaterial(TerrainMaterialIndex::TerrainAtmosphere, mIndex);
			auto materialState = TerrainShaderMgr.GetMaterial(TerrainMaterialIndex::TerrainAtmosphere)->GetState();
			slots[0].SetTexture(materialState, 0, GetScatterTexture()->GetRaster());
			slots[1].SetTexture(materialState, 1, mpSphere->GetTerrainStateManager()->mTextures.mpAtmospherePackedCurves->GetRaster());
		}
		Draw(mpMesh->vertexBuffer, GetAtmosphereIndexBuffer(), 0, mIndicesCount);
		stats.numVerticesRendered += mpMesh->vertexBuffer->vertexCount;
		stats.numIndicesRendered += GetAtmosphereIndexBuffer()->indicesCount;
		stats.numDrawCalls++;
	}
}
```

@section SourceCode-Terrain-cTerrainSphere Terrain::cTerrainSphere

@subsection SourceCode-Terrain-cTerrainSphere-CreateRTTs cTerrainSphere::CreateRTTs()

Code for cTerrainSphere::CreateRTTs()

```cpp
void cTerrainSphere::CreateRTTs()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = RenderTargetManager.CreateRenderTarget(256, 256, D3DFMT_A8R8G8B8);
		RenderTargetManager.SetRenderTargetName(index, "TerrainRTTs");
		GetSimDataRenderTargetIDs()[i] = index;
		GetSimDataRenderTargetTextures()[i] = RenderTargetManager.GetTexture(index);
	}

	CreateScatterRTTs();

	// renderTerrainWaterReflection
	if (AppProperties.GetDirectBool(0xF1A9135A)) 
	{
		CreateReflectionRTTs();
	}

	auto index = RenderTargetManager.CreateRenderTarget(256, 256, D3DFMT_A8R8G8B8, 0, 0x956A72C0);
	RenderTargetManager.SetRenderTargetName(index, "TerrainColorMap");
	SetColorMap(RenderTargetManager.GetRaster(index));

	auto viewer = GetColorMapViewer();
	viewer->Initialize();
	viewer->SetTargetZBuffer(nullptr);
	viewer->SetTargetRaster(GetReflectionTexture()->GetRaster());
	viewer->SetViewport({ 0, 0, 256, 256 });
}
```

@section SourceCode-Terrain-Misc Terrain

@subsection SourceCode-Terrain-Misc-CreateTerrainRefractionRTTs CreateTerrainRefractionRTTs()

Code for Terrain::CreateTerrainRefractionRTTs()

```cpp
void Terrain::CreateTerrainRefractionRTTs()
{
	auto index = RenderTargetManager.CreateRenderTarget(256, 256, D3DFMT_A8R8G8B8, 0, 0x5A6F2FEE);
	RenderTargetManager.SetRenderTargetName(index, "TerrainRefractionBuffers");
	*GetRefractionBuffersRenderTargetID() = index;
	SetRefractionBuffersRenderTargetTexture(RenderTargetManager.GetTexture(index));

	auto index = RenderTargetManager.CreateRenderTarget(256, 256, D3DFMT_A8R8G8B8, 0, 0x43EC615B);
	RenderTargetManager.SetRenderTargetName(index, "TerrainRefractionBlur1");
	*GetRefractionBlur1RenderTargetID() = index;

	auto index = RenderTargetManager.CreateRenderTarget(256, 256, D3DFMT_A8R8G8B8, 0, 0x43EC6158);
	RenderTargetManager.SetRenderTargetName(index, "TerrainRefractionBlur2");
	*GetRefractionBlur2RenderTargetID() = index;

	GetRefractionViewer()->Initialize();
}
```

@subsection SourceCode-Terrain-Misc-DisposeTerrainRefractionRTTs DisposeTerrainRefractionRTTs()

Code for Terrain::DisposeTerrainRefractionRTTs()

```cpp
void Terrain::DisposeTerrainRefractionRTTs()
{
	GetRefractionViewer()->Dispose();
	RenderTargetManager.ReleaseRenderTarget(*GetRefractionBuffersRenderTargetID());
	RenderTargetManager.ReleaseRenderTarget(*GetRefractionBlur1RenderTargetID());
	RenderTargetManager.ReleaseRenderTarget(*GetRefractionBlur2RenderTargetID());
	SetRefractionBuffersRenderTargetTexture(nullptr);
}
```

@subsection SourceCode-Terrain-Misc-CreateScatterRTTs CreateScatterRTTs()

Code for Terrain::CreateScatterRTTs()

```cpp
void Terrain::CreateScatterRTTs()
{
	auto texture = TextureManager.CreateTexture(0x7DF39217, GroupIDs::terrainSystem_gameAsset, 
		32, 32, 1, RenderWare::Raster::kFlagCubeTexture | RenderWare::Raster::kTypeRenderTarget,
		D3DFMT_A8R8G8B8);
	GetBakeInScatterTexture() = texture;

	auto texture = TextureManager.CreateTexture(0x3090FF70, GroupIDs::terrainSystem_gameAsset,
		32, 32, 1, RenderWare::Raster::kFlagCubeTexture | RenderWare::Raster::kTypeRenderTarget,
		D3DFMT_A8R8G8B8);
	GetScatterTexture() = texture;

	auto viewer = GetScatterViewer();
	viewer->Initialize();
	viewer->SetTargetZBuffer(nullptr);
	viewer->SetTargetRaster(GetScatterTexture()->GetRaster());
	viewer->SetViewport({ 0, 0, 32, 32 });
}
```

@subsection SourceCode-Terrain-Misc-CreateReflectionRTTs CreateReflectionRTTs()

Code for Terrain::CreateReflectionRTTs()

```cpp
void Terrain::CreateReflectionRTTs()
{
	auto texture = TextureManager.CreateTexture(0x7EF570CC, GroupIDs::terrainSystem_gameAsset,
		256, 256, 1, RenderWare::Raster::kFlagCubeTexture | RenderWare::Raster::kTypeRenderTarget,
		D3DFMT_A8R8G8B8);
	GetReflectionTexture() = texture;

	auto viewer = GetReflectionViewer();
	viewer->Initialize();
	viewer->SetBackgroundColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	viewer->SetTargetRaster(GetReflectionTexture()->GetRaster());
	viewer->SetPerspectiveProjection(90.0f);
	viewer->SetViewport({ 0, 0, 256, 256 });
}
```

