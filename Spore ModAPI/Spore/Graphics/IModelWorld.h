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

#include <Spore\Swarm\IEffectsWorld.h>
#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\cMeshData.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\cFrustumCull.h>
#include <Spore\App\PropertyList.h>
#include <Spore\RenderWare\RWMath.h>

#define IModelWorldPtr eastl::intrusive_ptr<Graphics::IModelWorld>

namespace Graphics
{
	struct cMWHull
	{
		/* 00h */	int field_0;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	ObjectPtr field_18;
	};
	ASSERT_SIZE(cMWHull, 0x1C);

	struct cMWTransformedHull : cMWHull
	{
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
	};
	ASSERT_SIZE(cMWTransformedHull, 0x28);

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
	typedef void(*BoneCallback_t)(int, Matrix4&, Vector3&, void*);

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
	/// if the ILayer::Render() method is called directly from another renderer. For example:
	/// ~~~~~~~~~~~~~~{.cpp}
	/// Renderer.AddLayer(modelWorld->AsLayer(), 8);
	/// ~~~~~~~~~~~~~~
	/// You might use greater render layer indices, like Graphics::kRenderQueueMain + 1. An example of this would be 
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
		/* 0Ch */	virtual Model* CreateModel(uint32_t instanceID, uint32_t groupID, int arg_8 = 0) = 0;

		/// Return the number of models that are currently loading.
		/// @returns
		/* 10h */	virtual int GetNumModelsLoading() = 0;

		/// Calls the given function when the model finishes loading, calling it immediately
		/// if the model has already loaded.
		/// @param model
		/// @param callback
		/// @param data Argument that is passed to the callback function.
		/// @returns
		/* 14h */	virtual bool CallOnLoad(Model* model, ModelPredicate_t callback, void* data) = 0;

		/// Reads a list of models and sets them to load.
		/// @param propList
		/// @param preloadIndex
		/* 18h */	virtual void PreloadModels(App::PropertyList* propList, int preloadIndex) = 0;

		/// Returns whether a given model preload list has finished loading all models.
		/// @param preloadIndex
		/// @returns
		/* 1Ch */	virtual bool ModelsHavePreloaded(int preloadIndex) = 0;

		//TODO returns cMWGroupInternal*, second param is cMWObject*&
		/* 20h */	virtual void* CreateGroup(int, void*&) = 0;


		/// Gets the first model that is intersected with the segment between `point1` and `point2`.
		/// @returns The closest model that intersected, or nullptr if no model intersected the ray.
		/* 24h */	virtual Model* FindFirstModelAlongLine(const Vector3& point1, const Vector3& point2, float* factorDst = nullptr, Vector3* dstIntersectionPoint = nullptr, Vector3* = nullptr, FilterSettings& settings = FilterSettings(), int* = nullptr, int* = nullptr) = 0;

		/* 28h */	virtual Model* FindFirstModelAlongLine2(const Vector3& point1, const Vector3& point2, float* factorDst, FilterSettings& settings = FilterSettings()) = 0;

		/// Gets all the models that fit the filter. By default, the filter accepts all models.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 2Ch */	virtual bool FindModels(eastl::vector<Model*>& dst, FilterSettings& settings = FilterSettings()) = 0;

		/// Gets all the models that intersect with a segment. It adds them in the vector ordered by distance to `point1`;
		/// the vector will contains pairs of model and a float, the proportion between the two points where it intersected.
		/// @param point1 The start of the ray.
		/// @param point2 The end of the ray.
		/// @param result The vector where the { model, factor } pairs will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 30h */	virtual bool FindModelsAlongLineOrdered(const Vector3& point1, const Vector3& point2, eastl::vector<eastl::pair<Model*, float>>& result, FilterSettings& settings = FilterSettings(), float = 0.0) = 0;

		/// Gets all the models that intersect with a segment.
		/// @param point1 The start of the ray.
		/// @param point2 The end of the ray.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid.
		/// @returns True if any model intersected, false otherwise.
		/* 34h */	virtual bool FindModelsAlongLine(const Vector3& point1, const Vector3& point2, eastl::vector<Model*>& result, FilterSettings& settings = FilterSettings(), float = 0.0) = 0;

		/// Finds all the models that intersect with the sphere with `center` and `radius`.
		/// @param center The center point of the sphere.
		/// @param radius The radius of the sphere.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if any model intersected, false otherwise.
		/* 38h */	virtual bool FindModelsInSphere(const Vector3& center, float radius, eastl::vector<Model*> result, FilterSettings& settings = FilterSettings()) = 0;

		/// Finds all the models that intersect with the given bounding box.
		/// @param bbox The bounding box to check.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if any model intersected, false otherwise.
		/* 3Ch */	virtual bool FindModelsInBox(const BoundingBox& bbox, eastl::vector<Model*>& result, FilterSettings& settings = FilterSettings()) = 0;

		/// Finds all the models that intersect with the given frustum.
		/// @param frustum The frustum to check.
		/// @param result The vector where the models will be added.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if any model intersected, false otherwise.
		/* 40h */	virtual bool FindModelsInFrustum(const cFrustumCull& frustum, eastl::vector<Model*> result, FilterSettings& settings = FilterSettings()) = 0;

		/// Intersects a line segment with a model, and gives the point in the segment that intersected with the model.
		/// @param linePoint1 Start point of the segment
		/// @param linePoint2 End point of the segment
		/// @param model The model to check
		/// @param[out] dstFactor If the model intersected, this will be the factor of the segment where it intersected, where 0.0 is the start point and 1.0 the end point.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if the model intersected at some point in the segment, false otherwise.
		/* 44h */	virtual bool PickAgainstModel(const Vector3& linePoint1, const Vector3& linePoint2, Model* model, float& dstFactor, FilterSettings& settings = FilterSettings()) = 0;

		/// Returns true if the sphere with `center` and `radius` intersects with the model.
		/// @param center The center point of the sphere.
		/// @param radius The radius of the sphere.
		/// @param model The model to intersect with.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if the model intersects with the bbox, false otherwise.
		/* 48h */	virtual bool SphereIntersectsModel(const Vector3& center, float radius, Model* model, FilterSettings& settings = FilterSettings()) = 0;

		/// Returns true if the given bounding box intersects with the model.
		/// @param bbox The bounding box to check.
		/// @param model The model to intersect with.
		/// @param settings Settings that decide which models are valid and which collision mode is used.
		/// @returns True if the model intersects with the bbox, false otherwise.
		/* 4Ch */	virtual bool BoxIntersectsModel(const BoundingBox& bbox, Model* model, FilterSettings& settings = FilterSettings()) = 0;
		
		///
		/// Used to get the instance and group ID of the given model.
		/// @param model The model.
		/// @param pDstInstanceID [Optional] Reference to the destination variable for the instance ID.
		/// @param pDstGroupID [Optional] Reference to the destination variable for the group ID.
		/* 50h */	virtual void GetModelResourceIDs(Model* model, uint32_t* pDstInstanceID, uint32_t* pDstGroupID) = 0;

		/// Gets all the region codes present in this model; to be precise, it gets all the values of the
		/// 'region' shader data of the materials in the model.
		/// @param model
		/// @param dst
		/* 54h */	virtual void GetRegionList(Model* model, eastl::vector<uint32_t>& dst) = 0;

		/// Ensures the given model is loaded and all its parameters are updated.
		/// @param model
		/* 58h */	virtual void StallUntilLoaded(Model* model) = 0;

		///
		/// Returns the model bounding radius, calling StallUntilLoaded() if the model
		/// does not have the 'overrideBoundingRadius' property.
		/// @param model
		/// @returns The bounding radius.
		/* 5Ch */	virtual float GetBoundingRadius(Model* model) = 0;

		///
		/// Returns the model bounding box, calling StallUntilLoaded() if the model
		/// does not have the 'overrideBoundingBox' property.
		/// @param model
		/// @returns The bounding box.
		/* 60h */	virtual const BoundingBox& GetBoundingBox(Model* model) = 0;

		/// Returns the amount of animation groups.
		/// @return
		/* 64h */	virtual int GetNumAnimationGroups() = 0;

		/// Returns the amount of animations contained in the model.
		/// @param model
		/// @param animationGroup
		/// @returns
		/* 68h */	virtual int GetNumAnimations(Model* model, int animationGroup = 0) const = 0;

		/// Used to get the IDs of the animations contained in the model.
		/// `dst` must be an array of the size returned by GetAnimCount()
		/// @param model
		/// @param[out] dst
		/// @param animationGroup
		/// @returns
		/* 6Ch */	virtual int GetAnimationIDs(Model* model, uint32_t* dst, int animationGroup = 0) const = 0;

		/// Sets the current playing animation of a model.
		/// @param model
		/// @param animID
		/// @param arg3
		/// @param arg4
		/// @param animationGroup
		/* 70h */	virtual void AnimAction(Model* model, uint32_t animID, int arg3 = 3, float arg4 = 0.0, int animationGroup = 0) = 0;

		/// Changes the current time of an animation in the model. The time must be in the range returned by GetAnimationRange()
		/// @param model
		/// @param animID
		/// @param time
		/// @param animationGroup
		/* 74h */	virtual void MoveToTime(Model* model, uint32_t animID, float time, int animationGroup  = 0) = 0;

		/// Changes the blending weight of a model animation (that is, how much it combines/blends with other animations, default is 1.0)
		/// @param model
		/// @param animID
		/// @param weight
		/// @param animationGroup
		/* 78h */	virtual void SetWeight(Model* model, uint32_t animID, float weight, int animationGroup = 0) = 0;

		/// Changes the animation time scale of the model, 1.0 is the default.
		/// @param model
		/// @param timeScale
		/* 7Ch */	virtual void SetTimeScale(Model* model, float timeScale) const = 0;
		// last parameter is index (skeleton index or smth?), first float always gets written to 0

		/// Used to get the start and end time of an animation in the model, in seconds.
		/// The length of the animation can be calculated with `dstEnd - dstStart`.
		/// @param model
		/// @param animID
		/// @param[out] dstStart
		/// @param[out] dstEnd
		/// @returns
		/* 80h */	virtual bool GetAnimationRange(Model* model, uint32_t animID, float& dstStart, float& dstEnd, int = 0) const = 0;

		/// Returns the number of animation bones in the given model.
		/// @param model
		/// @returns 
		/* 84h */	virtual int GetNumBones(Model* model) const = 0;

		// Returns amount of bones
		/* 88h */	virtual int GetPoseTransforms(Model* model, RenderWare::cMDBoneTransform* dst, bool original = false) const = 0;

		/* 8Ch */	virtual int GetBoneTransforms(Model* model, RenderWare::cMDBoneTransform* dst) = 0;

		/// Used to obtain the IDs of the animation bones in the given model.
		/// @param model
		/// @param[out] dst Array of uint32_t of enough size (GetNumBones()), the IDs will be written here
		/// @returns The number of bones
		/* 90h */	virtual int GetBoneIDs(Model* model, uint32_t* dst) = 0;

		/// Used to obtain the index to the parent of each animation bone in a model (-1 means it is the root and has no parent).
		/// @param model
		/// @param[out] dst Array of int of enough size (GetNumBones()), the parent indices will be written here
		/// @returns The number of bones
		/* 94h */	virtual int GetBoneParents(Model* model, int* dst) = 0;

		/* 98h */	virtual void SetBoneTable(Model* model, int arg1, RenderWare::cMDBoneTransform* boneTable) = 0;

		/// Sets a function that is executed for a bone or all bones (when playing an animation?)
		/// @param model
		/// @param callback
		/// @param data
		/// @param boneIndex
		/// @param arg5
		/* 9Ch */	virtual int SetBoneCallback(Model* model, BoneCallback_t callback, void* data=nullptr, int boneIndex=-1, int arg5=0) = 0;

		/// Sets the transform of a model animation group.
		/// @param model
		/// @param animationGroup
		/// @param transform
		/* A0h */	virtual void SetAnimationGroupTransform(Model* model, int animationGroup, const Transform& transform) = 0;

		/* A4h */	virtual void SetMaterialInfo(Model* model, cMaterialInfo* pMaterialInfo, int region = -1) const = 0;
		/* A8h */	virtual cMaterialInfo* GetMaterialInfo(Model* model, int region = -1) const = 0;

		/* ACh */	virtual void SetDynamicDraw(Model* model, void* pDynamicDraw, bool arg3) = 0;

		/// Returns how many mesh versions this model has, which depend on the level of detail (LOD).
		/// @param model
		/* B0h */	virtual int GetNumLODs(Model* model) const = 0;

		/// Forces the model to use a certain lod level, or restores it to the default (which is changing lod level
		/// depending on distance).
		/// @param model The model to change.
		/// @param lod The level of detail t use, between 0 and 3. If -1 is used, the lod will be decided by distance.
		/* B4h */	virtual void SetLOD(Model* model, int lod) const = 0;

		/// Sets the effect range for the model. If the value is negative, effect range will be ignored,
		/// so effects in this model will be displayed at any distance. Otherwise, the value is ignored, and the
		/// effect range is loaded from the model `.prop` file.
		/// @param model
		/// @param effectRange
		/* B8h */	virtual void SetEffectRange(Model* model, double effectRange = -1.0f) const = 0;

		/* BCh */	virtual void SetLODScale(float scale) = 0;
		/* C0h */	virtual float GetLODScale() = 0;

		/// Enables or disables the effects in the model. An instance ID can be specified; in that case, only
		/// effects with that ID will be affected.
		/// @param model
		/// @param enable If true, effects will be enabled
		/// @param instanceID [Optional] If not 0, only effects with this ID will be changed.
		/* C4h */	virtual void SetEffectsRunning(Model* model, bool enable, uint32_t instanceID = 0) const = 0;

		/// Changes parameters of effects in a model.
		/// @param model
		/// @param param
		/// @param data
		/// @param count
		/// @param instanceID [Optional] If not 0, only effects with this ID will be changed.
		/// @returns 
		/* C8h */	virtual bool SetFloatParams(Model* model, Swarm::FloatParams param, const float* data, int count, uint32_t instanceID = 0) const = 0;

		/// Changes parameters of effects in a model.
		/// @param model
		/// @param param
		/// @param data
		/// @param count
		/// @param instanceID [Optional] If not 0, only effects with this ID will be changed.
		/// @returns 
		/* CCh */	virtual bool SetIntParams(Model* model, Swarm::IntParams param, const int* data, int count, uint32_t instanceID = 0) const = 0;

		/// Changes parameters of effects in a model.
		/// @param model
		/// @param param
		/// @param data
		/// @param count
		/// @param instanceID [Optional] If not 0, only effects with this ID will be changed.
		/// @returns 
		/* D0h */	virtual bool SetUnknownParams(Model* model, Swarm::ObjectParams param, Object* data, uint32_t instanceID = 0) const = 0;

		/* D4h */	virtual void SetExternalEffectsTransform(Model* model, const Transform* pTransform = nullptr, uint32_t instanceID = 0) = 0;

		/* D8h */	virtual void GetHull(Model* model, cMWHull& hull) = 0;

		/* DCh */	virtual void GetTransformedHull(Model* model, cMWTransformedHull*& hull) = 0;

		/* E0h */	virtual void ReleaseTransformedHull(Model* model, cMWTransformedHull*& hull) = 0;
		
		/// Gets the bounding box of the hull (collision) model.
		/// @param model
		/// @param dst
		/* E4h */	virtual void GetHullBoundingBox(Model* model, BoundingBox& dst) const = 0;

		// returns count
		/* E8h */	virtual int GetDeformationHandles(Model* model, MorphHandleInfo* dst, int count) = 0;

		/// Obtain the animation ID of all the deformation handles in the model.
		/// @param model
		/// @param[out] dst
		/// @param animationGroup
		/// @return The number of IDs written
		/* ECh */	virtual int GetDeformationAnimationIDs(Model* model, uint32_t* dst, int animationGroup = 0) = 0;

		/* F0h */	virtual bool GetBakedMeshes(Model* model, eastl::vector<cMeshDataPtr>& dst, const Transform& transform) = 0;

		/* F4h */	virtual bool GetBakedMeshes2(Model* model, eastl::vector<cMeshDataPtr>& dst) = 0;

		/* F8h */	virtual bool GetMeshes(Model* model, eastl::vector<cMeshDataPtr>& dst, const Transform& transform) = 0;

		/* FCh */	virtual bool GetBakedMeshesUnscaled(Model* model, eastl::vector<cMeshDataPtr>& dst, const Transform& transform) = 0;

		/* 100h */	virtual int GetRuntimeMeshes(Model* model, eastl::vector<cMeshDataPtr>& dst, RenderWare::RenderWareFile*, void*, void*) = 0;

		//TODO cGameModelResource
		/* 104h */	virtual int GetRuntimeModel(Model* model, void** dst, const ResourceKey& key) = 0;

		/// Returns default transform stored in the prop file of the model
		/// @param model
		/// @returns
		/* 108h */	virtual Transform* GetMeshTransform(Model* model) = 0;

		/* 10Ch */	virtual bool UpdatePickMesh(Model* model, BoundingBox* dstBbox = nullptr) = 0;

		/* 110h */	virtual bool UpdateHullPickMesh(Model* model, BoundingBox* dstBbox = nullptr) = 0;

		/* 114h */	virtual bool GetPickMeshTri(Model* model, int, void** dst, bool useHull) = 0;

		/* 118h */	virtual bool GetPickMeshTriPositions(Model* model, int, Vector3& dst1, Vector3& dst2, Vector3& dst3) = 0;

		/* 11Ch */	virtual void SetRenderGroups(const eastl::bitset<64>&, const eastl::bitset<64>&) = 0;

		/* 120h */	virtual void GetRenderGroups(eastl::bitset<64>& dst1, eastl::bitset<64>& dst2) = 0;

		/* 124h */	virtual void SetRenderSetInfo(int indexDrawSet, int info1, int info2) = 0;  // something related with PlanetModelDepthOffset ?

		/* 128h */	virtual void GetRenderSetInfo(int indexDrawSet, int* dst1, int* dst2) = 0;

		/* 12Ch */	virtual void SetWorldType(int worldType) = 0;

		/* 130h */	virtual int GetWorldType() = 0;

		///
		/// Toggles the visibility of all the world, including the lighting and all the models contained.
		/// @param visible Whether the world must be visible or not.
		///
		/* 134h */	virtual void SetActive(bool active) = 0;

		/* 138h */	virtual bool GetActive() = 0;

		///
		/// Returns the ILayer object that can be used to render this model world.
		///
		/* 13Ch */	virtual ILayer* AsLayer() = 0;

		// saves boolean at 1D0, world ad 1CC, bool is related with shadows
		/* 140h */	virtual int SetLightingWorld(ILightingWorld* pWorld, int indexDrawSet, bool drawShadows) = 0;

		/* 144h */	virtual ILightingWorld* GetLightingWorld(int indexDrawSet) = 0;

		/* 148h */	virtual int SetEffectsWorld(Swarm::IEffectsWorld*) = 0;

		/* 14Ch */	virtual Swarm::IEffectsWorld* GetEffectsWorld() = 0;

		/* 150h */	virtual void SetWorldBounds(const BoundingBox& bbox, float, float) = 0;

		/* 154h */	virtual void SetHorizonCullFactor(float factor) = 0;

		/* 158h */	virtual int AddOccluder(const Vector3& position, float radius) = 0;

		/* 15Ch */	virtual void UpdateOccluder(int index, const Vector3& position, float radius) = 0;

		/* 160h */	virtual void RemoveOccluder(int index) = 0;

		/* 164h */	virtual void func164h() = 0;  // ResetHighlightCurve, maybe?

		/* 168h */	virtual RenderWare::RenderWareFile* GetArenaResource(Model* model) = 0;

		/// Changes the visibility of a given model inside this world.
		/// @param model The model to set visible/invisible, which must be included inside this world.
		/// @param visible Whether the model must be visible or not.
		/// @returns
		/* 16Ch */	virtual bool SetInWorld(Model* model, bool visible) = 0;

		// model destructor calls this, and will crash if it was already removed
		/* 170h */	virtual void FinalRelease(Model* model, bool) = 0;

		/* 174h */	virtual bool Initialize() = 0;

		/* 178h */	virtual bool Dispose() = 0;

		/* 17Ch */	virtual void UpdateHull(Model* model, cMWTransformedHull* hull) = 0;  // related with collisions

	protected:
		void LoadModelProperties(const App::PropertyList* pPropList, cMWModelInternal* pAsset, int nFlags, int arg_C);

		// 18h modelmanager
		// /* 19Ch */	intrusive_list<cMWModelInternal> ??

		// 2ECh vector?
		// 300h vector
		// 5C8h		IEffectsWorldPtr

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IModelWorld)
	{
		DeclareAddress(LoadModelProperties);
	}

}
