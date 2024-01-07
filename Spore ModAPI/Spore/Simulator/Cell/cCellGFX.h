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

#include <EASTL\vector.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\map.h>
#include <Spore\Anim\IAnimWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Swarm\IEffectsWorld.h>
#include <Spore\Audio\AudioSystem.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>

#define CellGFX (*Simulator::Cell::cCellGFX::Get())

namespace Simulator
{
	namespace Cell
	{
		class cCellGFX
		{
		public:
			enum WorldIDs
			{
				kCellLightingWorldID = 0x4A4D97F,
				kCellPreloadedModelWorldID = 0x1010050,
				kCellPreloadedEffectWorldID = 0x1010051,
				kCellSkyboxEffectWorldID = 0x1010000,
				kCellBackgroundEffectWorldID = 0x1010011,
				kCellBackgroundModelWorldID = 0x1010010,
				kCellBeachEffectWorldID = 0x1010016,
				kCellBeachModelWorldID = 0x1010015,
				kCellEffectWorldID = 0x1010021,
				kCellModelWorldID = 0x1010020,
				kCellForegroundEffectWorldID = 0x1010031,
				kCellAnimWorldID = 0x148A084,
			};

			typedef eastl::map<cCellDataReference_*, int> IsPreloadedMap_t;

			static cCellGFX* Get();

			static void PreloadResources();
			static void PreloadCellResource(IsPreloadedMap_t preloadedMap, cCellDataReference<cCellCellResource>* resource);
			static void PreloadPopulateResource(IsPreloadedMap_t preloadedMap, cCellDataReference<cCellPopulateResource>* resource);
			static void PreloadLootTableResource(IsPreloadedMap_t preloadedMap, cCellDataReference<cCellLootTableResource>* resource);
			static void PreloadCreature(uint32_t creatureID);

			static void AddPreloadedEffect(uint32_t instanceID, uint32_t groupID = 0);
			void AddPreloadedTexture(Graphics::Texture* texture);
			static void AddPreloadedModel(uint32_t instanceID, bool waitUntilLoaded);
			void AddPreloadedModel2(Graphics::Model* model);

			static void Initialize();

			/// Adds the renderer layers, sets as visible the effect and model worlds,
			/// sets as visible the UI, and starts playing the music.
			static void StartDisplay();

			/// Creates an instance of an effect; if the effect cannot be loaded, 'cell_bad_effect' is loaded instead.
			/// @param effectsWorld The effects world where the effect will be instantiated
			/// @param instanceID ID of the effect
			/// @param groupID Ignored
			/// @param dst 
			static void CreateEffect(Swarm::IEffectsWorld* effectsWorld, uint32_t instanceID, uint32_t groupID, IVisualEffectPtr& dst);

			static Swarm::IVisualEffect* InstanceEffectOnCell(cCellObjectData* cell, uint32_t effectID);

			/// Loads and places all the effects from the cCellGlobalsResource::effectMapEntry effect map.
			static void LoadEffectMap();

			/// Returns the bounding box for the currently visible background.
			static Math::BoundingBox& GetVisibleBackgroundBBox();
#ifdef SDK_TO_GHIDRA
			static Math::BoundingBox sVisibleBackgroundBBox;
#endif

			/// Returns the frustum cull for the currently visible main cell level.
			static Graphics::cFrustumCull& GetFrustumCull();
#ifdef SDK_TO_GHIDRA
			static Math::BoundingBox sFrustumCull;
#endif

		public:
			struct EffectInstance
			{
				/* 00h */	Transform localTransform;
				/* 38h */	Transform cellTransform;
				/* 74h */	IVisualEffectPtr effect;
			};
			ASSERT_SIZE(EffectInstance, 0x74);

			/// The graphical representation of a cell object: its model, animated creature, etc.
			struct CellGFXObjectData
				: public cObjectPoolClass
			{
				/* 04h */	int field_04;
				/* 08h */	int field_08;
				/// Index to the cell object in cCellGame::mCells that this object represents
				/* 0Ch */	cObjectPoolIndex mCellIndex;
				/* 10h */	int field_10;
				/* 14h */	cCellDataReference<cCellStructureResource>* mpStructure;
				/* 18h */	int field_18;
				/* 1Ch */	int field_1C;
				/* 20h */	int field_20;
				/* 24h */	Anim::AnimatedCreature* mpAnimatedCreature;
				/* 28h */	ModelPtr mpModel;
				// Either Swarm::IVisualEffect*, Graphics::Model*, Anim::AnimatedCreature*
				/* 2Ch */	void* mStructureGFXs[10];  //TODO how many?
				/* 54h */	int mNumStructureGFX;
				/* 58h */	float field_58;
				/* 5Ch */	bool field_5C;
				/* 60h */	ObjectPtr field_60;
				/* 64h */	int field_64;
				/* 68h */	int field_68;
				/* 6Ch */	int field_6C;
				/* 70h */	int field_70;
				/* 74h */	int field_74;
				/* 78h */	int field_78;
				/* 7Ch */	int field_7C;
				/* 80h */	int field_80;
				/* 84h */	int field_84;
				/* 88h */	int field_88;
				/* 8Ch */	ObjectPtr field_8C;
				/* 90h */	int field_90;
				/* 94h */	int field_94;
				/* 98h */	ObjectPtr field_98;
				/* 9Ch */	ObjectPtr field_9C;
				/* A0h */	ObjectPtr field_A0;
				/* A4h */	ObjectPtr field_A4;
				/* A8h */	ObjectPtr field_A8;
				/* ACh */	int field_AC;
				/* B0h */	int field_B0;
				/* B4h */	int field_B4;
				/* B8h */	int field_B8;
				/* BCh */	int field_BC;
				/* C0h */	int field_C0;
				/* C4h */	int field_C4;
			};
			ASSERT_SIZE(CellGFXObjectData, 0xC8);

			/* 00h */	eastl::vector<ModelPtr> mPreloadedModels;
			/* 14h */	eastl::vector<TexturePtr> mPreloadedTextures;
			/* 28h */	eastl::vector<Anim::AnimatedCreature*> mPreloadedCreatures;
			/* 3Ch */	int field_3C;
			/* 40h */	int field_40;
			/* 44h */	int field_44;
			/* 48h */	int field_48;
			/* 4Ch */	int field_4C;  // not initialized
			/* 50h */	IEffectsWorldPtr mpPreloadedEffectWorld;
			/* 54h */	IModelWorldPtr mpPreloadedModelWorld;
			/* 58h */	IAnimWorldPtr mpPreloadedAnimWorld;
			/* 5Ch */	IVisualEffectPtr field_5C[0x40];  // effect map entries
			/* 15Ch */	int field_15C;
			/* 160h */	IVisualEffectPtr mpDoFDistortEffect;
			/* 164h */	int field_164;
			/// 256 objects of size 0xC8
			/* 168h */	cObjectPool<CellGFXObjectData> mCellGFXObjects;
			/* 184h */	eastl::fixed_vector<int, 22528> field_184;
			/* 1619Ch */	int field_1619C;  // not initialized
			/* 161A0h */	ILightingWorldPtr mpLightingWorld;
			/* 161A4h */	int field_161A4;
			/* 161A8h */	IModelWorldPtr mpBeachModelWorld;
			/* 161ACh */	IEffectsWorldPtr mpBeachEffectWorld;
			/* 161B0h */	int field_161B0;
			/* 161B4h */	IEffectsWorldPtr mpSkyboxEffectWorld;
			/* 161B8h */	int field_161B8;
			/* 161BCh */	IEffectsWorldPtr mpBackgroundEffectWorld;
			/* 161C0h */	IModelWorldPtr mpBackgroundModelWorld;
			/* 161C4h */	IAnimWorldPtr mpBackgroundAnimWorld;
			/* 161C8h */	IEffectsWorldPtr mpEffectWorld;
			/* 161CCh */	IModelWorldPtr mpModelWorld;
			/* 161D0h */	IAnimWorldPtr mpAnimWorld;
			/* 161D4h */	IEffectsWorldPtr mpForegroundEffectWorld;
			/* 161D8h */	int field_161D8;
			/// Current effects
			/* 161DCh */	eastl::vector<EffectInstance> mEffectInstances;
			/* 161F0h */	char padding_161F0[0x16208 - 0x161F0];  // not initialized
			/* 16208h */	Audio::AudioTrack mCellMotionAudioTrack;  // not initialized
			/* 1620Ch */	Audio::AudioTrack mCellgameSeedMusicAudioTrack;  // not initialized
			/* 16210h */	Audio::AudioTrack mCellAmbAudioTrack;  // not initialized
			/* 16214h */	char padding_16214[0x1625C - 0x16214];  // not initialized
		};
		ASSERT_SIZE(cCellGFX, 0x1625C);

#ifdef SDK_TO_GHIDRA
		cCellGFX* sCellGFX;
#endif

		namespace Addresses(cCellGFX)
		{
			DeclareAddress(_ptr);  // 0x16B7E88 0x16B3C08
			DeclareAddress(PreloadResources);  // 0xE66C90 0xE666F0
			DeclareAddress(PreloadCellResource);  // 0xE66950 0xE663B0
			DeclareAddress(PreloadPopulateResource);  // 0xE66B60 0xE665C0
			DeclareAddress(PreloadLootTableResource);  // 0xE50290 0xE4FC00
			DeclareAddress(PreloadCreature);  // 0xE64F10 0xE64980
			DeclareAddress(AddPreloadedEffect);  // 0xE66820 0xE66280
			DeclareAddress(AddPreloadedTexture);  // 0xE65F10 0xE65970
			DeclareAddress(AddPreloadedModel);  // 0xE659B0 0xE65410
			DeclareAddress(AddPreloadedModel2);  // 0xE65940 0xE653A0
			DeclareAddress(Initialize);  // 0xE5E130 0xE5DBA0
			DeclareAddress(StartDisplay);  // 0xE55780 0xE55120
			DeclareAddress(CreateEffect);  // 0x628470 0x628480
			DeclareAddress(LoadEffectMap);  // 0xE63AF0 0xE63560
			DeclareAddress(InstanceEffectOnCell);  // 0xE66DE0 0xE66840
			DeclareAddress(sVisibleBackgroundBBox_ptr);  // 0x16B7F08 0x16B3C88
			DeclareAddress(sFrustumCull_ptr);  // 0x16B7F38 0x16B3CB8
		}
	}
}
