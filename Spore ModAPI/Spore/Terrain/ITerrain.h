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

#include <Spore\Terrain\cTerrainMapSet.h>
#include <Spore\Terrain\cTerrainStateMgr.h>
#include <Spore\Terrain\cWeatherManager.h>
#include <Spore\Terrain\TerrainShaderData.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Graphics\IRenderManager.h>
#include <Spore\Anim\IAnimWorld.h>
#include <Spore\Graphics\IModelWorld.h>

#define ITerrainPtr intrusive_ptr<Terrain::ITerrain>

namespace Terrain
{
	class ITerrain
	{
	public:
		enum class DisplayType {
			Creature = 0,
			Tribe = 1,
			Civ = 2,
			Space = 3,
			Default = 4
		};

		typedef void(*OnLoadFinish_t)(ITerrain*, void*);

		static const uint32_t WORLD_ID = 0x3FBAE24;

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		/// Returns the property list used to generate this planet.
		/* 08h */	virtual App::PropertyList* GetPropertyList() = 0;
		/* 0Ch */	virtual cTerrainMapSet* GetTerrainMapSet() = 0;
		/* 10h */	virtual cTerrainStateMgr* GetTerrainStateManager() = 0;
		/* 14h */	virtual cWeatherManager* GetWeatherManager() = 0;

		/// Returns the seed that was used to create this planet.
		/// The seed is determined by the `modelEffectSeed` property; if
		/// the property isn't specified, the planet instance ID is used as seed.
		/* 18h */	virtual uint32_t GetSeed() = 0;
		/* 1Ch */	virtual void SetDisplayType(DisplayType pathType) = 0;
		/* 20h */	virtual DisplayType GetDisplayType() = 0;
		/* 24h */	virtual void func24h(Object*) = 0;
		/* 28h */	virtual Object* func28h() = 0;
		/* 2Ch */	virtual bool HasViewer() = 0;
		/* 30h */	virtual bool IsLoading() = 0;
		/* 34h */	virtual int GetLoadMode() = 0;

		/// Sets a function that will be executed when the planet finishes loading. If it has already finished,
		/// the function will be executed immediately. The `object` is passed as parameter to the function.
		/// @param f 
		/// @param object
		/* 38h */	virtual void SetOnLoadFinish(OnLoadFinish_t f, void* object) = 0;
		/* 3Ch */	virtual void ForceLoadEnd() = 0;
		/* 40h */	virtual void func40h() = 0;
		/* 44h */	virtual void func44h(bool) = 0;
		/* 48h */	virtual uint8_t func48h(uint8_t) = 0;
		/* 4Ch */	virtual bool func4Ch(bool) = 0;
		/* 50h */	virtual bool func50h() = 0;
		/* 54h */	virtual uint32_t AddModelModification(const Transform& transform, App::PropertyList* propList) = 0;
		/* 58h */	virtual bool RemoveModelModification(uint32_t modid, bool) = 0;
		/* 5Ch */	virtual bool HasModelModification(uint32_t modid) = 0;
		/* 60h */	virtual int ResetModelModifications() = 0;
		// returns modid
		/* 64h */	virtual uint32_t AddPlayerModification(const Transform& transform, uint32_t effectID, uint32_t groupID = 0) = 0;
		/* 68h */	virtual bool RemovePlayerModification(uint32_t modid) = 0;
		/* 6Ch */	virtual bool HasPlayerModification(uint32_t modid) = 0;
		/* 70h */	virtual void ResetPlayerModifications() = 0;  // also removes certain properties
		// ranges [0, 63], [0,13], [0,13]
		/* 74h */	virtual void SetPlanetInfo(int terrainType, int atmosphereType, int waterType) = 0;
		/* 78h */	virtual void GetPlanetInfo(int* dstTerrainType, int* dstAtmosphereType, int* dstWaterType) = 0;
		/* 7Ch */	virtual void func7Ch(int terrainType, int atmosphereType, int waterType, Vector3*, Vector3*, Vector3*) = 0;  // related with colors or maps
		/* 80h */	virtual void func80h() = 0;  // related with player effects
		/* 84h */	virtual void func84h() = 0;
		/* 88h */	virtual void func88h() = 0;
		/* 8Ch */	virtual bool AddToRender(Graphics::IRenderManager*) = 0;
		/* 90h */	virtual void RemoveFromRender(Graphics::IRenderManager*) = 0;
		/* 94h */	virtual bool IsAddedToRender(Graphics::IRenderManager*) = 0;
		/* 98h */	virtual void SetVisible(bool visible) = 0;
		/* 9Ch */	virtual void Update(App::cViewer* pViewer, int deltaTime) = 0;
		/* A0h */	virtual void funcA0h() = 0;  //PLACEHOLDER adds effect surfaces?
		/* A4h */	virtual void funcA4h() = 0;  // Unloads effect surfaces?

		/// Loads the ambient effects and terrain models, only if they are not loaded already.
		/// You can force a reload by calling UnloadAssets() first.
		/* A8h */	virtual void LoadAssets() = 0;
		/// Unloads the ambient effects and terrain models
		/* ACh */	virtual void UnloadAssets() = 0;
		/// Used to get the loaded planet asset models. Returns the number of models.
		/* B0h */	virtual size_t GetModels(ModelPtr*& dst) = 0;
		/* B4h */	virtual size_t GetModelsInfo(ResourceKey** dstKeys, Transform** dstTransforms) = 0;
		/* B8h */	virtual int funcB8h(int) = 0;
		/* BCh */	virtual int funcBCh(int) = 0;
		/* C0h */	virtual int funcC0h(int) = 0;
		/* C4h */	virtual int funcC4h(int) = 0;
		/* C8h */	virtual size_t funcC8h() = 0;
		/* CCh */	virtual int funcCCh() = 0;
		/* D0h */	virtual int funcD0h() = 0;
		/* D4h */	virtual void funcD4h(float) = 0;
		/* D8h */	virtual bool funcD8h() = 0;
		/* DCh */	virtual bool GetAllowUnderwaterObjects() = 0;
		/* E0h */	virtual void SetAllowUnderwaterObjects(bool) = 0;
		/* E4h */	virtual void AddUnderwaterModelWorld(Graphics::IModelWorld* world, int flags = 0) = 0;
		/* E8h */	virtual void RemoveUnderwaterModelWorld(Graphics::IModelWorld*) = 0;
		/* ECh */	virtual void ClearUnderwaterModelWorlds() = 0;
		/* F0h */	virtual void AddUnderwaterAnimWorld(Anim::IAnimWorld* world, int flags) = 0;
		/* F4h */	virtual void RemoveUnderwaterAnimWorld(Anim::IAnimWorld*) = 0;
		/* F8h */	virtual void ClearUnderwaterAnimWorlds() = 0;
		/* FCh */	virtual Vector4* GetGrassTrampling() = 0;
		/* 100h */	virtual int GetMaxGrassTrampling() = 0;  // returns 8
		/* 104h */	virtual void ResetGrassTrampling() = 0;

		/// Finds the first point in the terrain surface that intersects with a ray in position `pos`
		/// towards direction `dir`. This only takes the terrain into acount, so it ignores models and water.
		/// @param pos The start position of the ray.
		/// @param dir The direction of the ray.
		/// @returns The position of the terrain where the ray hit, or (0,0,0) if there was no intersection with the planet.
		/* 108h */	virtual Vector3 Raycast(const Vector3& pos, const Vector3& dir) = 0;
		/* 10Ch */	virtual Quaternion GetOrientation(const Vector3& upAxis) = 0;
		/* 110h */	virtual void Dispose() = 0;
		/* 114h */	virtual void ParseProp(App::PropertyList* pPropList) = 0;
		/* 118h */	virtual const Vector3& GetCameraPos() = 0;
		/* 11Ch */	virtual const Vector3& GetCameraDir() = 0;
		/* 120h */	virtual const Vector3& GetSunDir() = 0;
		/* 124h */	virtual bool LoadInternal(bool weather) = 0;
		/* 128h */	virtual bool Load() = 0;
	};
}