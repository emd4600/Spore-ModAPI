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
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\ResourceID.h>
#include <EASTL\vector.h>

#include <Spore\Terrain\ITerrain.h>
#include <Spore\Terrain\cTerrainStateMgr.h>
#include <Spore\Terrain\TerrainShaderData.h>
#include <Spore\Terrain\Sphere\cTerrainSphereQuad.h>

using namespace eastl;
using namespace Math;

namespace Terrain
{
	// related with ambient occlusion??
	class unk_class_0x13F3628 {
		virtual void unk() = 0;
	};

	namespace Sphere
	{
		class cTerrainSphere
			: public ITerrain
			, public Graphics::IRenderable
			, public App::IMessageListener
			, public unk_class_0x13F3628
			, public Resource::ResourceObject
		{
		public:

			void Generate(int* unused0 = nullptr, int* unused1 = nullptr, bool = false, 
				bool generateSingleStep = false, float generateTimeLimit = 10.0f);


			class TextureContainer
			{
			public:
				virtual ~TextureContainer();   // there are 2 more functions

				/* 04h */	bool field_4;
				/* 08h */	int mLoadStep;
				/* 0Ch */	int field_C;
				/* 10h */	float field_10;
				/* 14h */	int field_14;
				/* 18h */	vector<TexturePtr> field_18;
				/* 2Ch */	vector<LARGE_INTEGER> mLoadTimes;
				/* 40h */	int field_40;
			};
			ASSERT_SIZE(TextureContainer, 0x44);

			struct TerrainModification
			{
				/* 00h */	Transform transform;
				/* 38h */	char field_38[0x60];  // floats
				/* 98h */	ResourceKey key;
				/* A4h */	int field_A4;
				/* A8h */	uint32_t field_A8;
			};
			ASSERT_SIZE(TerrainModification, 0xAC);

			/* 24h */	int field_24;
			/* 28h */	PropertyListPtr mpPropList;
			/* 2Ch */	intrusive_ptr<cTerrainMapSet> mpTerrainMapSet;
			/* 30h */	TextureContainer field_30;
			/* 74h */	TextureContainer field_74;
			/* B8h */	TextureContainer field_B8;
			/* FCh */	TextureContainer* mpLoader;
			/* 100h */	OnLoadFinish_t mOnLoadFinish;
			/* 104h */	void* mOnLoadFinishObject;
			/* 108h */	bool mTerrainGenerateSingleStep;  // true
			/* 10Ch */	float mTerrainGenerateTimeLimit;  // 5.0
			/* 110h */	bool field_110;
			/* 111h */	bool field_111;
			/* 114h */	int field_114;
			/* 118h */	cTerrainSphereQuad* field_118[6];
			/* 130h */	cTerrainSphereQuad* field_130[6];
			/* 148h */	TexturePtr field_148[6];
			/* 160h */	TexturePtr field_160[6];
			/* 178h */	TexturePtr field_178[6];
			// The item has a size of 16, used in rendering
			/* 190h	*/	vector<void*> field_190;
			/* 1A4h */	vector<int> field_1A4;
			/* 1B8h */	vector<int> field_1B8;
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
			/* 218h */	vector<int> field_218;
			/* 22Ch */	vector<int> field_22C;
			/* 240h */	vector<int> field_240;
			/* 254h */	vector<int> field_254;
			/* 268h */	vector<int> field_268;
			/* 27Ch */	vector<int> field_27C;
			/* 290h */	vector<int> field_290;
			/* 2A4h */	vector<int> field_2A4;
			/* 2B8h */	vector<int> field_2B8;
			/* 2CCh */	vector<int> field_2CC;
			/* 2E0h */	vector<int> field_2E0;
			/* 2F4h */	vector<int> field_2F4;
			/* 308h */	TexturePtr field_308;  // PLACEHOLDER 0xE5230445
			/* 30Ch */	Vector4 mCameraPos;
			/* 31Ch */	Vector4 mCameraDir;
			/* 32Ch */	Vector4 mSunDir;
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
			/* 494h */	Vector4 field_494[6];
			/* 4F4h */	bool field_4F4;  // ready to render?
			/* 4F5h */	bool field_4F5;  // true  visible?
			/* 4F8h */	TerrainState mTerrainState;
			/* 638h */	Vector4 mTramp[8];
			/* 6B8h */	Vector4 field_6B8;
			/* 6C8h */	Vector4 field_6C8;
			/* 6D8h */	TerrainLighting mTerrainLighting;
			/* 758h */	vector<int> field_758;
			/* 76Ch */	bool mAmbientEffectsLoaded;
			/* 770h */	vector<TerrainModification> mModelFootprints;
			/* 784h */	vector<TerrainModification> mModelNeedRelevel;
			/* 798h */	vector<TerrainModification> mPlayerEffects;
			/* 7ACh */	int mNumModels;  // a count of something for 7B0
			/* 7B0h */	vector<ResourceKey> mModelKeys;
			/* 7C4h */	vector<Transform> mModelTransforms;
			/* 7D8h */	vector<ModelPtr> mModels;
			/* 7ECh */	vector<IEffectPtr> mAmbientEffects;
			/* 800h */	vector<IEffectPtr> mAmbientSoundEffects;
			/* 814h */	int mPlayerModCount;

			/* 8A0h */  //PLACEHOLDER cTerrainSphereImpostorJob

			/* 8ACh */	bool mAllowUnderwaterObjects;
			// int are flags for renderable
			/* 8B0h */	vector<pair<IModelWorldPtr, int>> mUnderwaterModelWorlds;
			/* 8C4h */	vector<pair<IAnimWorldPtr, int>> mUnderwaterAnimWorlds;

			/* 8E4h */	App::cViewer* mpTerrainViewer;

			/* 924h */	//PLACEHOLDER DecalManager
			/* 928h */	//PLACEHOLDER TerrainDraw

			/* A4Ch */	//PLACEHODLER cQuadBuffersPool

		public:
			static cTerrainSphere* Create();  //PLACEHOLDER method
		};

		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		//PLACEHOLDER static_assert(sizeof(cTerrainSphere) == 0xA50, "sizeof(cTerrainSphere) != A50h");

		namespace Addresses(cTerrainSphere)
		{
			DeclareAddress(Create);
			DeclareAddress(Generate);
		}
	}
}