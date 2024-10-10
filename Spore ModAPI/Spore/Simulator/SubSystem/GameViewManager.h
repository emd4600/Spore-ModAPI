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

#include <Spore\Anim\IAnimWorld.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\cViewer.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <EASTL\intrusive_list.h>
#include <EASTL\vector.h>
#include <EASTL\map.h>
#include <EASTL\hash_map.h>
#include <EASTL\fixed_vector.h>

/// Gets the active game view manager.
#define GameViewManager (*Simulator::cGameViewManager::Get())

namespace Addresses(Simulator)
{
	DeclareAddress(LightingWorld_ptr);
}

namespace Simulator
{
	using namespace Math;

	class cCombatant;

	class cGameViewManager
		: public Graphics::ILayer
		, public App::IMessageListener
		, public cStrategy
	{
	public:
		/// The ID used for the Simulator model world, effects world
		static const uint32_t GraphicsWorldID = 0xEB9968;
		/// The ID used for the Simulator lighting world, effects world
		static const uint32_t LightingWorldID = 0x4A4DEA0;

		//PLACEHOLDER initialize alll simulator systems? sub_B33270

		//TODO PLACEHOLDER
		/* 10h */	virtual void func10h_();
		/* 14h */	virtual void PrepareSimulator();
		/* 18h */	virtual void func18h_();
		/* 1Ch */	virtual void func1Ch_();
		/* 20h */	virtual void func20h_();
		/* 24h */	virtual void func24h_();
		/* 28h */	virtual void func28h_();
		/* 2Ch */	virtual void func2Ch_();
		/* 30h */	virtual cGameData* GetHoveredObject();
		/* 34h */	virtual int func34h_();  // get cRotationRing?
		/* 38h */	virtual Vector3 func38h_(int, struct Vector3);
		/* 3Ch */	virtual Vector3 func3Ch_(int);
		// if pPlayer is not null, it ignores it when checking the position
		// apparently only detects certain objects like airplanes, creatures, city walls, buildings but not planet ornaments
		/* 40h */	virtual Vector3 GetWorldMousePosition(int=0, cCombatant* pCombanant=nullptr);
		/* 44h */	virtual void func44h_();

		/// Finds all the cSpatialObject objects that intersect with the sphere with `center` and `radius`.
		/// The objects will be added to `dst`. `filter` is an optional filter function that receives a Model and `filterObject`,
		/// and returns whether the model is considered or not.
		///
		/// The collision is only checked with the bounding box, so it is not a precise model collision.
		/// If the `useModelCollisionMode` param is true, then the collision mode specified by each model will be used.
		///
		/// @param center The center of the sphere.
		/// @param radius The radius of the sphere.
		/// @param[out] dst The vector where all objects will be added.
		/// @param useModelCollisionMode If true, the collision mode specified by each model will be used.
		/// @param filter An optional filter function that decides which models are considered.
		/// @param filterObject An object that is passed to the filter function.
		/// @returns `true` if any object was found, `false` otherwise.
		/* 48h */	virtual bool IntersectSphere(const Vector3& center, float radius, eastl::vector<cSpatialObjectPtr>& dst, 
			bool useModelCollisionMode = false, Graphics::ModelPredicate_t filter = nullptr, void* filterObject = nullptr);

		/// Finds all the cSpatialObject objects that intersect with the segment between `point1` and `point2`.
		/// The objects will be added to `dst` in the order they have been found, so the ones closest to `point1` come first.
		///
		/// The collision is only checked with the bounding box, so it is not a precise model collision.
		/// If the `useModelCollisionMode` param is true, then the collision mode specified by each model will be used.
		///
		/// @param point1 The start point of the ray.
		/// @param point2 The end point of the ray.
		/// @param[out] dst The vector where all objects will be added.
		/// @param useModelCollisionMode If true, the collision mode specified by each model will be used.
		/// @returns `true` if any object was found, `false` otherwise.
		/* 4Ch */	virtual bool RaycastAll(const Vector3& point1, const Vector3& point2, 
			eastl::vector<cSpatialObjectPtr>& dst, bool useModelCollisionMode = false);

		/// Finds the first cGameData object that intersects with the segment between `point1` and `point2`.
		/// Only models that pass the filter function are considered.
		///
		/// The collision is only checked with the bounding box, so it is not a precise model collision.
		/// If the `useModelCollisionMode` param is true, then the collision mode specified by each model will be used.
		///
		/// @param point1 The start point of the ray.
		/// @param point2 The end point of the ray.
		/// @param filter A filter function that receives a Model and returns whether it is considered or not.
		/// @param[out] dst The object that is found, only valid if `true` was returned.
		/// @param[out] dstIntersection The point where the ray intersected with the model, only valid if `true` was returned.
		/// @param useModelCollisionMode If true, the collision mode specified by each model will be used.
		/// @returns `true` if an object was found, `false` otherwise.
		/* 50h */	virtual bool Raycast(const Vector3& point1, const Vector3& point2, Graphics::FilterSettings::FilterModel_t filter, 
			cGameDataPtr& dst, Vector3& dstIntersection, bool useModelCollisionMode = false);

		/* 54h */	virtual IGameDataView GetObjectView(cGameData* pObject);

	public:
		/* 24h */	eastl::intrusive_list<IGameDataView> mViews;
		/* 2Ch */	eastl::fixed_vector<ModelPtr, 16> mGrassTrampModels;
		/* 84h */	uint32_t mGameModeID;  // -1
		/* 88h */	cGameDataPtr mHoveredObject;
		/* 8Ch */	eastl::hash_map<int, int> field_8C;
		/* ACh */	eastl::vector<int> field_AC;
		/* C0h */	bool field_C0;
		/* C1h */	bool field_C1;  // visible?
		/* C4h */	eastl::intrusive_ptr<int> field_C4;  // release at 8
		/* C8h */	eastl::map<int, int> field_C8;  // actually might be a set, of object TYPEs that are not visible?
		/* E4h */	IModelWorldPtr field_E4;  // IModelWorld?
		/* E8h */	ObjectPtr field_E8;
		/* ECh */	App::cViewer* field_EC;  // with hologram render type
		/* F0h */	int field_F0;  // not initialized, ResourceKey?
		/* F4h */	int field_F4;  // not initialized
		/* F8h */	int field_F8;  // not initialized
		/* FCh */	int field_FC;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
		/* 108h */	IAnimWorldPtr mpCreatureFXAnimWorld;
		/* 10Ch */	bool mbSuperHighResVehicles;
		/* 10Dh */	bool mbSuperHighResIgnoreCount;
		/* 10Eh */	bool mbSuperHighResBuildings;
		/* 110h */	eastl::fixed_vector<int, 32> field_110;  // ?

	public:
		/// Gets the active game view manager.
		static cGameViewManager* Get();
	};
	ASSERT_SIZE(cGameViewManager, 0x1A8);

#ifndef SDK_TO_GHIDRA
	inline Graphics::ILightingWorld* GetLightingWorld() {
		return *(Graphics::ILightingWorld**)(GetAddress(Simulator, LightingWorld_ptr));
	}
#else
	Graphics::ILightingWorld* sLightingWorld;
#endif

	namespace Addresses(cGameViewManager)
	{
		DeclareAddress(Get);
	}
}