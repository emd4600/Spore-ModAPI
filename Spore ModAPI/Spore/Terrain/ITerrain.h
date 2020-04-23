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
		/* 24h */	virtual int func24h() = 0;
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual bool HasViewer() = 0;
		/* 30h */	virtual bool IsLoading() = 0;
		/* 34h */	virtual int GetLoadMode() = 0;

		/// Sets a function that will be executed when the planet finishes loading. If it has already finished,
		/// the function will be executed immediately. The `object` is passed as parameter to the function.
		/// @param f 
		/// @param object
		/* 38h */	virtual void SetOnLoadFinish(OnLoadFinish_t f, void* object) = 0;
		/* 3Ch */	virtual void ForceLoadEnd() = 0;
		/* 40h */	virtual int func40h() = 0;
		/* 44h */	virtual int func44h() = 0;
		/* 48h */	virtual int func48h() = 0;
		/* 4Ch */	virtual int func4Ch() = 0;
		/* 50h */	virtual int func50h() = 0;
		/* 54h */	virtual int func54h() = 0;
		/* 58h */	virtual int func58h() = 0;
		/* 5Ch */	virtual bool func5Ch(uint32_t modid) = 0;
		/* 60h */	virtual int func60h() = 0;
		// returns modid
		/* 64h */	virtual uint32_t AddPlayerModification(const Transform& transform, uint32_t effectID, uint32_t groupID = 0) = 0;
		/* 68h */	virtual bool RemovePlayerModification(uint32_t modid) = 0;
		/* 6Ch */	virtual bool HasPlayerModification(uint32_t modid) = 0;
		/* 70h */	virtual int func70h() = 0;
		/* 74h */	virtual int func74h() = 0;
		/* 78h */	virtual int func78h() = 0;
		/* 7Ch */	virtual int func7Ch() = 0;
		/* 80h */	virtual int func80h() = 0;
		/* 84h */	virtual int func84h() = 0;
		/* 88h */	virtual int func88h() = 0;
		/* 8Ch */	virtual bool AddToRender(Graphics::IRenderManager*) = 0;
		/* 90h */	virtual void RemoveFromRender(Graphics::IRenderManager*) = 0;
		/* 94h */	virtual bool IsAddedToRender(Graphics::IRenderManager*) = 0;
		/* 98h */	virtual void SetVisible(bool visible) = 0;
		/* 9Ch */	virtual void Update(App::cViewer* pViewer, int deltaTime) = 0;
		/* A0h */	virtual int funcA0h() = 0;  //PLACEHOLDER adds effect surfaces?
		/* A4h */	virtual int funcA4h() = 0;
		/* A8h */	virtual int funcA8h() = 0;
		/* ACh */	virtual int funcACh() = 0;
		/* B0h */	virtual int funcB0h() = 0;
		/* B4h */	virtual int funcB4h() = 0;
		/* B8h */	virtual int funcB8h() = 0;
		/* BCh */	virtual int funcBCh() = 0;
		/* C0h */	virtual int funcC0h() = 0;
		/* C4h */	virtual int funcC4h() = 0;
		/* C8h */	virtual int funcC8h() = 0;
		/* CCh */	virtual int funcCCh() = 0;
		/* D0h */	virtual int funcD0h() = 0;
		/* D4h */	virtual int funcD4h() = 0;
		/* D8h */	virtual int funcD8h() = 0;
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
		/* 110h */	virtual int func110h() = 0;
		/* 114h */	virtual void ParseProp(App::PropertyList* pPropList) = 0;
		/* 118h */	virtual const Vector3& GetCameraPos() = 0;
		/* 11Ch */	virtual const Vector3& GetCameraDir() = 0;
		/* 120h */	virtual const Vector3& GetSunDir() = 0;
		/* 124h */	virtual bool LoadInternal(bool weather) = 0;
		/* 128h */	virtual bool Load() = 0;
	};
}