@page SourceCode-Skinner Source Code: Skinner
@brief Some reconstructed Spore source code for the Skinner namespace

@tableofcontents

@section SourceCode-Skinner-cSkinPainterJobBumpToNormal Skinner::cSkinPainterJobBumpToNormal

```cpp
bool cSkinPainterJobBumpToNormal::Execute()
{
	float skinpaintBumpHeight = 0.0f;
	App::Property::GetFloat(App::GetAppProperties(), 0xC19DB33, skinpaintBumpHeight);
	if (skinpaintBumpHeight == 0.0f) skinpaintBumpHeight = 5.0f;

	auto dstTexture = PaintSystem.GetPainter()->GetTexture2();
	dstTexture->StartRender();
	dstTexture->SetMaterial(0x9E74D163);  // uses shader skpBumpToNormal
	dstTexture->AddRaster(0, PaintSystem.GetPainter()->GetTexture0()->GetRaster());

	ColorRGBA params;
	params.r = 1.0f / dstTexture->mWidth;
	params.g = 1.0f / dstTexture->mHeight;
	params.b = skinpaintBumpHeight / 3.0f;
	params.a = 0.0f;
	dstTexture->AddCustomParams(0, params);

	dstTexture->PaintRegion({ 0.0f, 0.0f }, { 1.0f, 1.0f });
	dstTexture->EndRender();
	return true;
}
```

@section SourceCode-Skinner-cSkinPainterJobCopyTex1AlphaToTex0 Skinner::cSkinPainterJobCopyTex1AlphaToTex0

```cpp
bool cSkinPainterJobCopyTex1AlphaToTex0::Execute()
{
	auto dstTexture = PaintSystem.GetPainter()->GetTexture0();
	dstTexture->StartRender();
	// Only edit alpha channel
	dstTexture->SetColorWriteEnable(false, false, false, true);
	dstTexture->SetMaterial(0x58653EAC);  // skpCopyIdentity
	dstTexture->AddRaster(0, PaintSystem.GetPainter()->GetTexture1()->GetRaster());

	dstTexture->PaintRegion({ 0.0f, 0.0f }, { 1.0f, 1.0f });
	dstTexture->SetColorWriteEnable(true, true, true, true);
	dstTexture->EndRender();
	return true;
}
```

@section SourceCode-Skinner-cSkinPainterJobPaintParts Skinner::cSkinPainterJobPaintParts

```cpp
bool cSkinPainterJobPaintParts::Execute()
{
	auto texture0 = PaintSystem.GetPainter()->mpTexture0;
	auto texture1 = PaintSystem.GetPainter()->mpTexture1;
	auto skinMesh = PaintSystem.GetSkinMesh();

	int count = skinMesh->mpCreatureData->field_98.size();

	if (mStage == 1) mStage = 2;

	if (mStage >= 4)
	{
		return mStage == 4;
	}
	
	if (mStage >= 2) {
		texture1->StartRender();
	}
	else {
		texture0->StartRender();
	}

	Math::ColorRGBA baseColor{ 1.0f, 1.0f, 1.0f, 0.0f };
	Math::ColorRGBA coatColor{ 1.0f, 1.0f, 1.0f, 0.0f };
	Math::ColorRGBA detailColor{ 1.0f, 1.0f, 1.0f, 0.0f };

	float skinpaintPartBumpScale;
	App::Property::GetFloat(App::GetAppProperties(), 0x1C76D9B5, skinpaintPartBumpScale);
	if (skinpaintPartBumpScale == 0.0f) skinpaintPartBumpScale = 1.0f;

	int rigblockLimitCount = 0;
	while (mRigblockIndex < count && rigblockLimitCount < 10)
	{
		if (skinMesh->mpCreatureData->field_98[mRigblockIndex].field_8 & 1)
		{
			mRigblockIndex++;
			continue;
		}

		baseColor.r = Math::randf();
		baseColor.g = Math::randf();
		baseColor.b = Math::randf();

		rigblockLimitCount++;
		auto& uvs = skinMesh->mUVs[mRigblockIndex];
		Vector2 uv1{ uvs.x1, uvs.y1 };
		Vector2 uv2{ uvs.x2, uvs.y2 };
		auto propList = skinMesh->mRigblockPropLists[mRigblockIndex].get();

		Graphics::Texture* skinpaintDiffuseTexture = nullptr;
		Graphics::Texture* skinpaintTintMaskTexture = nullptr;
		Graphics::Texture* skinpaintSpecBumpTexture = nullptr;

		if (mStage == 0)
		{
			// skinpaintDiffuseTexture
			if (propList->HasProperty(0x2424655)) 
			{
				ResourceKey key{};
				App::Property::GetKey(propList, 0x2424655, key);
				if (TextureManager.HasTexture(key))
				{
					skinpaintDiffuseTexture = TextureManager.GetTexture(key, 
						Graphics::kTextureFlagForceLoad | Graphics::kTextureFlagSetLOD);
				}
			}
		}
		if (mStage == 0 || mStage == 1)
		{
			// skinpaintTintMaskTexture
			if (propList->HasProperty(0x2424657))
			{
				ResourceKey key{};
				App::Property::GetKey(propList, 0x2424657, key);
				if (TextureManager.HasTexture(key))
				{
					skinpaintTintMaskTexture = TextureManager.GetTexture(key,
						Graphics::kTextureFlagForceLoad | Graphics::kTextureFlagSetLOD);
				}
			}
		}
		if (mStage == 2 || mStage == 3)
		{
			// skinpaintSpecBumpTexture
			if (propList->HasProperty(0x2424657))
			{
				ResourceKey key{};
				App::Property::GetKey(propList, 0x2424657, key);
				if (TextureManager.HasTexture(key))
				{
					skinpaintSpecBumpTexture = TextureManager.GetTexture(key,
						Graphics::kTextureFlagForceLoad | Graphics::kTextureFlagSetLOD);
				}
			}
		}

		if (mStage == 0 && skinpaintDiffuseTexture && skinpaintTintMaskTexture)
		{
			texture0->SetColorWriteEnable(true, true, true, false);
			// Uses 0x700000ad(skpSplatTintShader).shader
			texture0->mMaterialID = 0xD9EC39BC;
			texture0->AddCustomParams(0, baseColor);
			texture0->AddCustomParams(1, coatColor);
			texture0->AddCustomParams(2, detailColor);
			texture0->AddRaster(0, skinpaintDiffuseTexture->GetLoadedRaster());
			texture0->AddRaster(1, skinpaintTintMaskTexture->GetLoadedRaster());
			texture0->PaintRegion(uv1, uv2);
		}
		if (mStage == 1 && skinpaintTintMaskTexture)
		{
			texture0->SetColorWriteEnable(false, false, false, true);
			// Uses skpSplatCopyTexShader
			texture0->mMaterialID = 0xA91B6551;
			texture0->AddCustomParams(0, { 1.0f, 1.0f , 1.0f, 1.0f });
			texture0->AddRaster(0, skinpaintTintMaskTexture->GetLoadedRaster());
			texture0->AddRaster(1, nullptr);
			texture0->PaintRegion(uv1, uv2);
		}
		if (mStage == 2 && skinpaintSpecBumpTexture)
		{
			float scale = PaintSystem.GetPainter()->mPartSpecScale;  // ?
			texture1->SetColorWriteEnable(true, false, false, false);
			// Uses skpBumpBrushShader
			texture1->mMaterialID = 0x3815422;
			texture1->AddCustomParams(0, { scale, scale, scale, 1.0f });
			texture1->AddRaster(0, skinpaintSpecBumpTexture->GetLoadedRaster());
			texture1->PaintRegion(uv1, uv2);
		}
		if (mStage == 3 && skinpaintSpecBumpTexture)
		{
			float scale = PaintSystem.GetPainter()->mPartBumpScale;  // ?
			texture1->SetColorWriteEnable(false, false, true, false);
			// Uses skpSplatCopyTexShader
			texture1->mMaterialID = 0x968E3FFF;
			texture1->AddCustomParams(0, { scale, scale, scale, 1.0f });
			texture1->AddRaster(0, skinpaintSpecBumpTexture->GetLoadedRaster());
			texture1->PaintRegion(uv1, uv2);
		}

		mRigblockIndex++;
	}

	if (mStage >= 2) {
		texture1->EndRender();
	}
	else {
		texture0->EndRender();
	}

	if (mRigblockIndex >= count) {
		mRigblockIndex = 0;
		mStage++;
	}
	
	return mStage == 4;
}
```