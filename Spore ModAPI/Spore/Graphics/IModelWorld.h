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

#include <cstdint>

#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\Graphics\ModelAsset.h>
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\App\PropertyList.h>
#include <Spore\RenderWare\RWMath.h>

#define IModelWorldPtr intrusive_ptr<Graphics::IModelWorld>

namespace Graphics
{
	struct MorphHandleInfo
	{
		/* 00h */	int field_0;
		/* 04h */	Transform transform;
		/* 3Ch */	uint32_t id;
		/* 40h */	Vector3 startPos;
		/* 4Ch */	Vector3 endPos;
		/* 58h */	float defaultProgress;
	};
	ASSERT_SIZE(MorphHandleInfo, 0x5C);

	typedef bool(*ModelPredicate_t)(Model*, void*);

	struct FilterSettings {
		typedef bool(*FilterModel_t)(Model*);

		enum Flags {
			kUseModelCollisionMode = 1,
			kIgnoreModelScale = 2
		};

		FilterSettings();

		/* 00h */	uint64_t requiredGroupFlags;
		/* 08h */	uint64_t bannedGroupFlags;
		/* 10h */	FilterModel_t filterFunction;
		/* 14h */	CollisionMode collisionMode;
		/* 15h */	uint8_t flags;
	};

	inline FilterSettings::FilterSettings()
		: requiredGroupFlags()
		, bannedGroupFlags()
		, filterFunction(nullptr)
		, collisionMode(CollisionMode::Lod0KDTree)
		, flags(kUseModelCollisionMode)
	{
	}

	///
	/// A model world is a space where models can be rendered in the game. Model worlds keep track of all the models
	/// loaded in order to render them when the model world itself is rendered. A world can also contain multiple
	/// lighting worlds; for more information, check the ILightingWorld interface. When no lighting worlds are added
	/// a default lighting is used.
	///
	/// In order for the model world to render, you must add it to the render queue. This step is not necessary
	/// if the IRenderable::Render() method is called directly from another renderer. For example:
	/// ~~~~~~~~~~~~~~{.cpp}
	/// RenderManager.AddRenderable(pModelWorld->ToRenderable(), Graphics::kRenderQueueMain);
	/// ~~~~~~~~~~~~~~
	/// You might use greater render queue indices, like Graphics::kRenderQueueMain + 1. An example of this would be 
	/// having a model world for translucid objects, which need to be rendered last. 
	///
	class IModelWorld
	{
	public:
		enum ModelWorldFlags {
			kBuildDrawLists = 0x00000100,
			kUpdateLOD = 0x00000200,
			kUseOccluders = 0x00000400,
			kSetState = 0x00000800,
			kDrawOpaque = 0x00001000,
			kDrawAlpha = 0x00002000,
			kDrawDebug = 0x00004000,
			kNoSort = 0x00008000,
			kForceOpaque = 0x00010000,

			kRenderAll = 0x00007f00,
			kRenderAllNoLOD = 0x00007d00,
		};

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		virtual ~IModelWorld() {};

		///
		/// Loads a model from the resources system with the given instance and group ID.
		/// Keep in mind that a model refers to the configuration file (i.e. the .prop file) which includes the 
		/// model files for each level of detail, the effects that must be used, etc.
		/// If the model configuration does not exist, a builtin model might be used.
		/// @param instanceID
		/// @param groupID
		///
		/* 0Ch */	virtual Model* LoadModel(uint32_t instanceID, uint32_t groupID, int arg_8 = 0) = 0;

		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual int func14h() = 0;
		/* 18h */	virtual int func18h() = 0;
		/* 1Ch */	virtual int func1Ch() = 0;
		/* 20h */	virtual int func20h() = 0;


		/// Gets the first model that is intersected with the segment between `point1` and `point2`.
		/// @returns The closest model that intersected, or nullptr if no model intersected the ray.
		/* 24h */	virtual Model* Raycast(const Vector3& point1, const Vector3& point2, float* factorDst = nullptr, Vector3* dstIntersectionPoint = nullptr, Vector3* = nullptr, FilterSettings& settings = FilterSettings(), int* = nullptr, int* = nullptr) = 0;

		/* 28h */	virtual Model* func28h(const Vector3& point1, const Vector3& point2, float* factorDst, FilterSettings& settings = FilterSettings()) = 0;

		/// Gets all the models that fit the filter. By default, the filter accepts all models.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 2Ch */	virtual bool GetModels(vector<Model*>& dst, FilterSettings& settings = FilterSettings()) = 0;

		/// Gets all the models that intersect with a segment. It adds them in the vector ordered by distance to `point1`;
		/// the vector will contains pairs of model and a float, the proportion between the two points where it intersected.
		/// @param point1 The start of the ray.
		/// @param point2 The end of the ray.
		/// @param result The vector where the { model, factor } pairs will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 30h */	virtual bool RaycastAllOrdered(const Vector3& point1, const Vector3& point2, vector<pair<Model*, float>>& result, FilterSettings& settings = FilterSettings(), float = 0.0) = 0;

		/// Gets all the models that intersect with a segment.
		/// @param point1 The start of the ray.
		/// @param point2 The end of the ray.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 34h */	virtual bool RaycastAll(const Vector3& point1, const Vector3& point2, vector<Model*>& result, FilterSettings& settings = FilterSettings(), float = 0.0) = 0;

		/// Finds all the models that intersect with the sphere with `center` and `radius`.
		/// @param center The center point of the sphere.
		/// @param radius The radius of the sphere.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if any model intersected, false otherwise.
		/* 38h */	virtual bool IntersectSphere(const Vector3& center, float radius, vector<Model*> result, FilterSettings& settings = FilterSettings()) = 0;

		/// Finds all the models that intersect with the given bounding box.
		/// @param bbox The bounding box to check.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if any model intersected, false otherwise.
		/* 3Ch */	virtual bool IntersectBBox(const BoundingBox& bbox, vector<Model*>& result, FilterSettings& settings = FilterSettings()) = 0;

		/* 40h */	virtual int func40h() = 0;  // intersect with frustum
		/* 44h */	virtual bool func44h(const Vector3& p1, const Vector3& p2, const Model* model, const Vector3& p3, FilterSettings& settings = FilterSettings()) = 0;

		/// Returns true if the sphere with `center` and `radius` intersects with the model.
		/// @param center The center point of the sphere.
		/// @param radius The radius of the sphere.
		/// @param model The model to intersect with.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if the model intersects with the bbox, false otherwise.
		/* 48h */	virtual bool ModelIntersectSphere(const Vector3& center, float radius, const Model* model, FilterSettings& settings = FilterSettings()) = 0;

		/// Returns true if the given bounding box intersects with the model.
		/// @param bbox The bounding box to check.
		/// @param model The model to intersect with.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if the model intersects with the bbox, false otherwise.
		/* 4Ch */	virtual bool ModelIntersectBBox(const BoundingBox& bbox, const Model* model, FilterSettings& settings = FilterSettings()) = 0;
		
		///
		/// Used to get the instance and group ID of the given model.
		/// @param pModel The model.
		/// @param pDstInstanceID [Optional] Reference to the destination variable for the instance ID.
		/// @param pDstGroupID [Optional] Reference to the destination variable for the group ID.
		/* 50h */	virtual void GetResourceID(const Model* pModel, uint32_t* pDstInstanceID, uint32_t* pDstGroupID) = 0;

		/* 54h */	virtual void GetRegions(const Model* pModel, vector<uint32_t>& dst) = 0;

		///
		/// Ensures the given model is loaded and all its parameters are updated.
		/// @param pModel
		///
		/* 58h */	virtual void UpdateModel(const Model* pModel) = 0;

		///
		/// Returns the model bounding radius, calling UpdateModel() if the model
		/// does not have the 'overrideBoundingRadius' property.
		/// @param pModel
		/// @returns The bounding radius.
		/* 5Ch */	virtual float GetBoundingRadius(const Model* pModel) = 0;

		///
		/// Returns the model bounding box, calling UpdateModel() if the model
		/// does not have the 'overrideBoundingBox' property.
		/// @param pModel
		/// @returns The bounding box.
		/* 60h */	virtual const BoundingBox& GetBoundingBox(const Model* pModel) = 0;

		/* 64h */	virtual int func64h() = 0;  // returns amount of skeletonSink?

		/// Returns the amount of animations contained in the model.
		/// @param pModel
		/* 68h */	virtual int GetAnimCount(const Model* pModel, int skeletonSinkIndex = 0) const = 0;

		/// Used to get the IDs of the animations contained in the model.
		/// `dst` must be an array of the size returned by GetAnimCount()
		/// @param pModel
		/// @param[out] dst
		/* 6Ch */	virtual int GetAnimIDs(const Model* pModel, uint32_t* dst, int skeletonSinkIndex = 0) const = 0;
		/* 70h */	virtual void func70h(Model* pModel, uint32_t animID, int = 3, float = 0.0, int skeletonSinkIndex = 0) = 0;

		/// Changes the current time of an animation in the model. The time must be in the range returned by GetAnimRange()
		/// @param pModel
		/// @param animID
		/// @param time
		/* 74h */	virtual void SetAnimTime(Model* pModel, uint32_t animID, float time, int = 0) = 0;
		/* 78h */	virtual int func78h(Model* pModel, uint32_t animID, float, int) = 0;
		/* 7Ch */	virtual int func7Ch(Model* pModel) const = 0;   // sets field_11C of model
		// last parameter is index (skeleton index or smth?), first float always gets written to 0

		/// Used to get the start and end time of an animation in the model, in seconds.
		/// The length of the animation can be calculated with `dstEnd - dstStart`.
		/// @param pModel
		/// @param animID
		/// @param[out] dstStart
		/// @param[out] dstEnd
		/* 80h */	virtual bool GetAnimRange(const Model* pModel, uint32_t animID, float& dstStart, float& dstEnd, int = 0) const = 0;
		/* 84h */	virtual int func84h(const Model* pModel) const = 0;
		// Returns amount of bones
		/* 88h */	virtual int GetAnimationSkin(const Model* pModel, RenderWare::Matrix3x4* dst, bool original = false) const = 0;
		/* 8Ch */	virtual int func8Ch(const Model* pModel, void* dst) = 0;
		/* 90h */	virtual int func90h() = 0;  
		/* 94h */	virtual int func94h() = 0;
		/* 98h */	virtual int func98h() = 0;
		/* 9Ch */	virtual int func9Ch() = 0;
		/* A0h */	virtual int funcA0h() = 0;

		/* A4h */	virtual void SetMaterialInfo(Model* pModel, cMaterialInfo* pMaterialInfo, int region = -1) const = 0;
		/* A8h */	virtual cMaterialInfo* GetMaterialInfo(const Model* pModel, int region = -1) const = 0;

		/* ACh */	virtual int funcACh() = 0;

		/// Returns how many mesh versions this model has, which depend on the level of detail (LOD).
		/// @param pModel
		/* B0h */	virtual int GetLodMeshCount(const Model* pModel) const = 0;

		/// Forces the model to use a certain lod level, or restores it to the default (which is changing lod level
		/// depending on distance).
		/// @param pModel The model to change.
		/// @param lod The level of detail t use, between 0 and 3. If -1 is used, the lod will be decided by distance.
		/* B4h */	virtual void SetFixedLod(Model* pModel, int lod) const = 0;

		/// Sets the effect range for the model. If the value is negative, effect range will be ignored,
		/// so effects in this model will be displayed at any distance. Otherwise, the value is ignored, and the
		/// effect range is loaded from the model `.prop` file.
		/* B8h */	virtual void SetEffectRange(Model* pModel, double effectRange = -1.0f) const = 0;
		/* BCh */	virtual int funcBCh() = 0;
		/* C0h */	virtual int funcC0h() = 0;

		/// Enables or disables the effects in the model. An instance ID can be specified; in that case, only
		/// effects with that ID will be affected.
		/// @param pModel
		/// @param enable If true, effects will be enabled
		/// @param instanceID [Optional] If not 0, only effects with this ID will be changed.
		/* C4h */	virtual void SetEffectEnable(Model* pModel, bool enable, uint32_t instanceID = 0) const = 0;
		/* C8h */	virtual bool SetEffectFloatParams(Model* pModel, Swarm::IEffect::FloatParams param, const float* data, int count, uint32_t instanceID = 0) const = 0;
		/* CCh */	virtual bool SetEffectIntParams(Model* pModel, Swarm::IEffect::IntParams param, const int* data, int count, uint32_t instanceID = 0) const = 0;
		/* D0h */	virtual bool SetEffectObjectParam(Model* pModel, Swarm::IEffect::IntParams param, Object* data, uint32_t instanceID = 0) const = 0;
		/* D4h */	virtual int funcD4h(Model* pModel, const Transform* pTransform = nullptr, uint32_t instanceID = 0) = 0;
		/* D8h */	virtual int funcD8h() = 0;
		/* DCh */	virtual int funcDCh() = 0;
		/* E0h */	virtual int funcE0h() = 0;
		// Uses ModelAsset mTransform
		/* E4h */	virtual void GetHullBoundingBox(const Model* pModel, BoundingBox& dst) const = 0;
		// returns count
		/* E8h */	virtual int GetMorphHandles(const Model* pModel, MorphHandleInfo* dst, int count) = 0;
		/* ECh */	virtual int funcECh() = 0;
		/* F0h */	virtual int funcF0h() = 0;
		/* F4h */	virtual int funcF4h() = 0;
		/* F8h */	virtual int funcF8h() = 0;
		/* FCh */	virtual int funcFCh() = 0;
		/* 100h */	virtual int func100h() = 0;
		/* 104h */	virtual int func104h() = 0;
		/* 108h */	virtual int func108h() = 0;
		/* 10Ch */	virtual int func10Ch() = 0;
		/* 110h */	virtual int func110h() = 0;
		/* 114h */	virtual int func114h() = 0;
		/* 118h */	virtual int func118h() = 0;
		/* 11Ch */	virtual int func11Ch() = 0;
		/* 120h */	virtual int func120h() = 0;
		/* 124h */	virtual int func124h() = 0;  // something related with PlanetModelDepthOffset ?
		/* 128h */	virtual int func128h() = 0;
		/* 12Ch */	virtual int func12Ch() = 0;
		/* 130h */	virtual int func130h() = 0;

		///
		/// Toggles the visibility of all the world, including the lighting and all the models contained.
		/// @param visible Whether the world must be visible or not.
		///
		/* 134h */	virtual void SetVisible(bool visible) = 0;

		/* 138h */	virtual int func138h() = 0;

		///
		/// Returns the IRenderable object that can be used to render this model world.
		///
		/* 13Ch */	virtual IRenderable* ToRenderable() = 0;

		// saves boolean at 1D0, world ad 1CC, bool is related with shadows
		/* 140h */	virtual int AddLightingWorld(ILightingWorld* pWorld, int slotIndex, bool) = 0;


		/* 144h */	virtual ILightingWorld* GetLightingWorld(int slotIndex) = 0;
		/* 148h */	virtual int func148h(Swarm::IEffectWorld*) = 0;
		/* 14Ch */	virtual Swarm::IEffectWorld* func14Ch() = 0;
		/* 150h */	virtual int func150h() = 0;
		/* 154h */	virtual int func154h() = 0;
		/* 158h */	virtual int func158h() = 0;
		/* 15Ch */	virtual int func15Ch() = 0;
		/* 160h */	virtual int func160h() = 0;
		/* 164h */	virtual int func164h() = 0;
		/* 168h */	virtual int func168h() = 0;

		///
		/// Changes the visibility of a given model inside this world.
		/// @param pModel The model to set visible/invisible, which must be included inside this world.
		/// @param visible Whether the model must be visible or not.
		///
		/* 16Ch */	virtual bool SetModelVisibile(Model* pModel, bool visible) = 0;

		// model destructor calls this, and will crash if it was already removed
		/* 170h */	virtual void DestroyModel(Model* pModel, bool) = 0;  // ?

		/* 174h */	virtual bool Initialize() = 0;
		/* 178h */	virtual bool Dispose() = 0;
		/* 17Ch */	virtual void func17Ch() = 0;  // related with collisions

	protected:
		void LoadModelProperties(const App::PropertyList* pPropList, ModelAsset* pAsset, int nFlags, int arg_C);

		// 18h modelmanager
		// /* 19Ch */	intrusive_list<ModelAsset> ??

		// 2ECh vector?
		// 300h vector
		// 5C8h		IEffectWorldPtr

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IModelWorld)
	{
		DeclareAddress(LoadModelProperties);
	}

}
