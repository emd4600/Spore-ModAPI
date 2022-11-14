/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Graphics\IAmbientOccluder.h>
#include <Spore\ResourceID.h>
#include <EASTL\vector.h>

#include <Spore\Terrain\ITerrain.h>
#include <Spore\Terrain\cTerrainStateMgr.h>
#include <Spore\Terrain\TerrainShaderData.h>
#include <Spore\Terrain\cTerrainSphereQuad.h>

namespace Terrain
{
	struct cTerrainSphereRenderingChunk
	{
		/* 00h */	cTerrainSphereQuad* mpQuad;
		/* 04h */	float field_4;
		/* 08h */	int mFlags;  // 0x40: don't render
		/* 0Ch */	int field_C;  // always 0?
	};
	ASSERT_SIZE(cTerrainSphereRenderingChunk, 0x10);

	class cTerrainSphere
		: public ITerrain
		, public Graphics::ILayer
		, public App::IMessageListener
		, public Graphics::IAmbientOccluder
		, public Resource::ResourceObject
	{
	public:

		void Generate(int* unused0 = nullptr, int* unused1 = nullptr, bool = false, 
			bool generateSingleStep = false, float generateTimeLimit = 10.0f);

		/// Updates the fields in the class related with shader data, such as `mTerrainState`
		void PrepareShaderData();

		void RenderTerrainLand(Graphics::RenderStatistics& stats, int flags);
		void RenderTerrainSeabedAsLand(App::cViewer* pViewer, Graphics::RenderStatistics& stats);
		void RenderTerrainWater(Graphics::RenderStatistics& stats, int flags);
		void RenderTerrainDecals(Graphics::RenderStatistics& stats, int flags);
		void RenderTerrainRibbons(Graphics::RenderStatistics& stats, int flags);
		void RenderTerrainAtmosphere(Graphics::RenderStatistics& stats, int flags);

		/// Called on the Graphics::RenderLayers::Terrain layer, calls all the RenderTerrainLand() etc methods.
		/// @param ppViewer
		/// @param stats
		/// @param flags
		void MainRenderPass(App::cViewer** ppViewer, Graphics::RenderStatistics& stats, int flags);

		/// This is called on the Graphics::RenderLayers::TerrainRTT layer, before the planet itself is rendered;
		/// this function renders the water reflection and refraction textures that are later used in rendering water.
		/// This calls RenderWaterRefraction() and RenderWaterReflection()
		void RenderWaterReflectionAndRefraction();

		/// Renders the water refraction texture, called by RenderWaterReflectionAndRefraction()
		void RenderWaterRefraction();

		/// Renders the water reflection texture, called by RenderWaterReflectionAndRefraction()
		void RenderWaterReflection();

		RenderWare::Raster* GetQuadNormalMap(int quadIndex);
		RenderWare::Raster* GetQuadHeightMap(int quadIndex);
		RenderWare::Raster* GetQuadControlMap(int quadIndex);

		/// Returns the `SimDataRTT` texture for the specified terrain quad. This map
		/// is used to control the color of the planet at each point.
		/// @param quadIndex
		/// @returns
		RenderWare::Raster* GetSimDataRTT(int quadIndex);

		/// Creates some of the render target textures used by planets: the 'SimData' textures, 'ColorMap', scatter, and reflection.
		/// Source code: @ref SourceCode-Terrain-cTerrainSphere-CreateRTTs
		void CreateRTTs();


		class TextureContainer
		{
		public:
			virtual ~TextureContainer();   // there are 2 more functions

			/* 04h */	bool field_4;
			/* 08h */	int mLoadStep;
			/* 0Ch */	int field_C;
			/* 10h */	float field_10;
			/* 14h */	int field_14;
			/* 18h */	eastl::vector<TexturePtr> field_18;
			/* 2Ch */	eastl::vector<LARGE_INTEGER> mLoadTimes;
			/* 40h */	int field_40;
		};
		ASSERT_SIZE(TextureContainer, 0x44);

		struct TerrainModification
		{
			/* 00h */	Transform transform;
			/* 38h */	char field_38[0x60];  // floats
			/* 98h */	ResourceKey key;
			/* A4h */	int field_A4;
			/* A8h */	uint32_t modid;
		};
		ASSERT_SIZE(TerrainModification, 0xAC);

		/* 24h */	int field_24;
		/* 28h */	PropertyListPtr mpPropList;
		/* 2Ch */	cTerrainMapSetPtr mpTerrainMapSet;
		/* 30h */	TextureContainer field_30;
		/* 74h */	TextureContainer field_74;
		/* B8h */	TextureContainer field_B8;
		/* FCh */	TextureContainer* mpLoader;
		/* 100h */	ITerrain::OnLoadFinish_t mOnLoadFinish;
		/* 104h */	void* mOnLoadFinishObject;
		/* 108h */	bool mTerrainGenerateSingleStep;  // true
		/* 10Ch */	float mTerrainGenerateTimeLimit;  // 5.0
		/* 110h */	bool field_110;
		/* 111h */	bool field_111;
		/* 114h */	int field_114;
		/* 118h */	cTerrainSphereQuad* mFullResQuads[6];
		/* 130h */	cTerrainSphereQuad* mLowResQuads[6];
		/* 148h */	TexturePtr mTerrainNormalMaps[6];
		/* 160h */	TexturePtr mTerrainHeightMaps[6];
		/* 178h */	TexturePtr mTerrainControlMaps[6];
		/// The terrain land quads that have to be rendered
		/* 190h	*/	eastl::vector<cTerrainSphereRenderingChunk> mLandRenderingChunks;
		/* 1A4h */	eastl::vector<int> field_1A4;
		/* 1B8h */	eastl::vector<int> field_1B8;
		/* 1CCh */	uint32_t mSeed;
		/* 1D0h */	int field_1D0;  // 4
		/* 1D4h */	int mPlanetLODChunkRes;  // 16
		/* 1D8h */	float mPlanetUnderwaterCullRadius;  // 25.0
		/* 1DCh */	float mPlanetUnderwaterLargeCullRadius;  // 100.0
		/* 1E0h */	float mPlanetUnderwaterCullRadiusMultiplier;  // 1.0
		/* 1E4h */	float field_1E4;  // 1.0
		/* 1E8h */	bool field_1E8;  // true
		/* 1ECh */	float field_1EC;  // 1.0
		/* 1F0h */	float field_1F0;  // 1.0
		/* 1F4h */	float field_1F4;  // 1.0
		/* 1F8h */	float field_1F8;  // 1.0
		/* 1FCh */	float field_1FC;  // 1.0
		/* 200h */	float field_200;  // 1.0
		/* 204h */	float field_204;  // 1.0
		/* 208h */	float field_208;  // 1.0
		/* 20Ch */	cTerrainStateMgr* mpTerrainStateMgr;
		/* 210h */	cWeatherManagerPtr mpWeatherManager;
		/* 214h */	int field_214;
		/* 218h */	eastl::vector<int> field_218;
		/* 22Ch */	eastl::vector<int> field_22C;
		/* 240h */	eastl::vector<int> field_240;
		/* 254h */	eastl::vector<int> field_254;
		/* 268h */	eastl::vector<int> field_268;
		/* 27Ch */	eastl::vector<int> field_27C;
		/* 290h */	eastl::vector<int> field_290;
		/* 2A4h */	eastl::vector<int> field_2A4;
		/* 2B8h */	eastl::vector<int> field_2B8;
		/* 2CCh */	eastl::vector<int> field_2CC;
		/* 2E0h */	eastl::vector<int> field_2E0;
		/* 2F4h */	eastl::vector<int> field_2F4;
		/* 308h */	TexturePtr field_308;  // PLACEHOLDER 0xE5230445
		/* 30Ch */	Math::Vector4 mCameraPos;
		/* 31Ch */	Math::Vector4 mCameraDir;
		/* 32Ch */	Math::Vector4 mSunDir;
		/* 33Ch */	bool field_33C;
		/* 33Dh */	bool field_33D;
		/* 340h */	int field_340;
		/* 344h */	int field_344;
		/* 348h */	bool field_348;
		/* 34Ch */	float mMungeHeightMapScale;  // 1.0
		/* 350h */	float mMungeWindMapScale;  // 1.0
		/* 354h */	float mMungeTempMapScale;  // 1.0
		/* 358h */	float mMungeLatMapScale;  // 1.0
		/* 35Ch */	float mMungeAlphaNoiseStrength;  // 1.0
		/* 360h */	float field_360;  // -1.0
		/* 364h */	float field_364;  // -1.0
		/* 368h */	int8_t field_368[2];  // not initialized
		/* 36Ch */	int field_36C;
		/* 370h */	bool field_370;
		// something here is indexed by 36C
		/* 374h */	char padding_374[0x120];  // floats?
		/* 494h */	Math::Vector4 field_494[6];
		/* 4F4h */	bool field_4F4;  // ready to render?
		/* 4F5h */	bool field_4F5;  // true  visible?
		/* 4F8h */	TerrainState mTerrainState;
		/* 638h */	Math::Vector4 mTramp[8];
		/* 6B8h */	Math::Vector4 field_6B8;
		/* 6C8h */	Math::Vector4 field_6C8;
		///* 6D8h */	TerrainLighting mTerrainLighting;
		/* 6D8h */	Math::Vector4 field_6D8[8];  //PLACEHODER what is really this?
		/* 758h */	eastl::vector<int> field_758;
		/* 76Ch */	bool mAssetsLoaded;  // ambient effects and models
		/* 770h */	eastl::vector<TerrainModification> mModelFootprints;
		/* 784h */	eastl::vector<TerrainModification> mModelNeedRelevel;
		/* 798h */	eastl::vector<TerrainModification> mPlayerEffects;
		/* 7ACh */	int mNumModels;  // a count of something for 7B0
		/* 7B0h */	eastl::vector<ResourceKey> mModelKeys;
		/* 7C4h */	eastl::vector<Transform> mModelTransforms;
		/* 7D8h */	eastl::vector<ModelPtr> mModels;
		/* 7ECh */	eastl::vector<IVisualEffectPtr> mAmbientEffects;
		/* 800h */	eastl::vector<IVisualEffectPtr> mAmbientSoundEffects;
		/* 814h */	int mPlayerModCount;
		/* 818h */	int field_818;
		/* 81Ch */	int field_81C;
		/* 820h */	char padding_820[0x60];
		/* 880h */	bool field_880;
		/* 884h */	int field_884;
		/* 888h */	int field_888;
		/* 88Ch */	int field_88C;
		/* 890h */	int field_890;
		/* 894h */	int field_894;
		/* 898h */	int field_898;  // -1
		/* 89Ch */	int field_89C;  // -1
		/* 8A0h */  void* mpImpostorJob;  //PLACEHOLDER cTerrainSphereImpostorJob
		/* 8A4h */	int field_8A4;  // -1
		/* 8A8h */	int field_8A8;
		/* 8ACh */	bool mAllowUnderwaterObjects;
		// int are flags for renderable
		/* 8B0h */	eastl::vector<eastl::pair<IModelWorldPtr, int>> mUnderwaterModelWorlds;
		/* 8C4h */	eastl::vector<eastl::pair<IAnimWorldPtr, int>> mUnderwaterAnimWorlds;
		/* 8D8h */	IEffectsWorldPtr mpUnderWaterEffectWorld;
		/* 8DCh */	int field_8DC;
		/* 8E0h */	int field_8E0;
		/* 8E4h */	App::cViewer* mpTerrainViewer;
		/* 8E8h */	Transform field_8E8;
		/* 920h */	int field_920;  // -1
		/* 924h */	void* mpDecalManager;  //PLACEHOLDER DecalManager
		/* 928h */	void* mpTerrainDraw;  //PLACEHOLDER TerrainDraw
		/* 92Ch */	char padding_92C[0xF0];
		/* A1Ch */	float field_A1C;
		/* A20h */	float field_A20;
		/* A24h */	float field_A24;
		/* A28h */	float field_A28;
		/* A2Ch */	float field_A2C;
		/* A30h */	float field_A30;
		/* A34h */	float field_A34;
		/* A38h */	Math::ColorRGBA field_A38;
		/* A48h */	int field_A48;
		/* A4Ch */	void* mpQuadBuffersPool;  //PLACEHODLER cQuadBuffersPool

	public:
		static cTerrainSphere* Create();  //PLACEHOLDER method
	};
	ASSERT_SIZE(cTerrainSphere, 0xA50);

	namespace Addresses(cTerrainSphere)
	{
		DeclareAddress(Create);
		DeclareAddress(Generate);
		DeclareAddress(PrepareShaderData);  // 0xF99010 0xF98910
		DeclareAddress(RenderTerrainLand);  // 0xF985F0 0xF97EF0
		DeclareAddress(RenderTerrainSeabedAsLand);  // 0xF98BD0 0xF984D0
		DeclareAddress(RenderTerrainWater);  // 0xF986C0 0xF97FC0
		DeclareAddress(RenderTerrainDecals);  // 0xF98810 0xF98110
		DeclareAddress(RenderTerrainRibbons);  // 0xF9C2B0 0xF9BBE0
		DeclareAddress(RenderTerrainAtmosphere);  // 0xF98870 0xF98170
		DeclareAddress(GetSimDataRTT);  // 0xF96FF0 0xF968B0
		DeclareAddress(RenderWaterReflectionAndRefraction);  // 0xFA62D0 0xFA5C70
		DeclareAddress(RenderWaterRefraction);  // 0xFA3E70 0xFA3810
		DeclareAddress(RenderWaterReflection);  // 0xF9CAE0 0xF9C420
		DeclareAddress(MainRenderPass);  // 0xF9C370 0xF9BCA0
		DeclareAddress(CreateRTTs);  // 0xFA0A20 0xFA03C0
	}

	// For backwards compatibility
	namespace Sphere
	{
		namespace Addresses(cTerrainSphere)
		{
			DeclareAddress(Create);
			DeclareAddress(Generate);
		}
	}
}