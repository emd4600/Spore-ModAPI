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
#include <EASTL\intrusive_ptr.h>
#include <EASTL\intrusive_list.h>

#include <Spore\App\PropertyList.h>
#include <Spore\ResourceID.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>
#include <Spore\Swarm\IVisualEffect.h>
#include <Spore\Graphics\cMaterialInfo.h>
#include <Spore\Graphics\cModelInstance.h>
#include <Spore\Graphics\cModelInstanceAnimations.h>

#define ModelPtr eastl::intrusive_ptr<Graphics::Model>
#define cMWModelInternalPtr eastl::intrusive_ptr<Graphics::cMWModelInternal>

namespace Graphics
{
	enum class CollisionMode : uint8_t {
		/// Only use the bounding radius to intersect
		BoundingSphere = 0,
		/// Only use the bounding box to intersect
		BoundingBox = 1,
		/// Check intersection with the hull mesh
		HullTriangle = 2,
		/// Check intersection with the LOD0 mesh, in an optimized but more imprecise way
		MeshCluster = 3,
		/// Check intersection with the LOD0 mesh triangle geometry, the slowest but most precise
		MeshTriangle = 4
	};

	class IModelWorld;


	// loc_7536B2 uses scale, render?
	// loc_751BC9 uses scale too, render?
	//  sub_73FA40 -> create Matrix4 from transform
	//  sub_740AC0 -> possible draw function?

	enum ModelFlags
	{
		kModelFlagUseColor = 0x2,  // actually 4?

		kModelFlagObjectTypeColor = 0x8,

		kModelFlagOverrideRaycastMode = 0x100,

		kModelFlagHighRes = 0x2000,
		kModelFlagIsLoaded = 0x4000,
		kModelFlagVisible = 0x8000,

		kModelFlagOverrideBoundingBox = 0x10000,
		kModelFlagOverrideBoundingRadius = 0x20000,  // 1 << 17
		kModelFlagNeedsBake = 0x40000
	};

	// cMWModel
	class Model
	{
	public:
		int AddRef();
		int Release();

		Transform GetTransform() const;
		void SetTransform(const Transform& transform);

		IModelWorld* GetModelWorld() const;

		App::PropertyList* GetPropList() const;

		Math::ColorRGBA GetColor() const;
		void SetColor(const Math::ColorRGBA& color);

		bool IsVisible() const;

		///
		/// Assigns the required flags to this model depending on the groupID specified.
		/// @param groupID The ID of the model group, in the ModelGroups enum.
		///
		void AddGroup(uint32_t groupID);
		void RemoveGroup(uint32_t groupID);

		bool HasGroup(uint32_t groupID) const;

		Object* GetOwner() const;
		void SetOwner(Object* object);

	public:
		/* 00h */	IModelWorld* mpWorld;
		/* 04h */	int mFlags;
		/* 08h */	Transform mTransform;
		/* 40h */	int mnRefCount;
		/* 44h */	int mGroupFlags[2];
		/* 4Ch */	Math::ColorRGBA mColor;
		/* 5Ch */	bool field_5C;
		/* 5Dh */	CollisionMode mCollisionMode;
		/* 60h */	int field_60;  // PLACEHOLDER used to select objectTypeColor
		/* 64h */	ObjectPtr mpOwner;  // sometimes it gets casted to cGameData
		/* 68h */	int16_t field_68; 
		/* 6Ch */	float mDefaultBoundingRadius;  // 1.0f
		/* 70h */	Math::BoundingBox mDefaultBBox;
		/* 88h */	float field_88;  // FLOAT_MAX
		/* 8Ch */	float field_8C;  // FLOAT_MAX  // distance from camera?
		/* 90h */	PropertyListPtr mpPropList;
	};
	ASSERT_SIZE(Model, 0x94);

	class cMWModelInternal 
		: public eastl::intrusive_list_node
		, public Model
	{
	public:
		struct EffectInstance
		{
			/* 00h */	ResourceID mResourceID;
			/* 08h */	IVisualEffectPtr mpEffect;
			/* 0Ch */	Transform mTransform;
			/* 44h */	bool mEnabled;  // true
		};
		ASSERT_SIZE(EffectInstance, 0x48);
		// size depends on light count
		struct ModelLights {
			/* 00h */	int count;
			/* 04h */	float* lightStrength;
			/* 08h */	Math::ColorRGB* lightColor;
			/* 0Ch */	float* lightSize;
			/* 10h */	Math::Vector3 lightOffset;
		};

		/* 9Ch */	cModelInstancePtr mMeshLods[4];
		/* ACh */	cModelInstancePtr mMeshHull;
		/* B0h */	cModelInstancePtr mMeshLodHi;
		/* B4h */	cModelInstanceAnimationsPtr mAnimationLods[4];
		/* C4h */	cModelInstanceAnimationsPtr mAnimationHull;
		/* C8h */	cModelInstanceAnimationsPtr mAnimationLodHi;
		/* CCh */	int field_CC;  // -1
		/* D0h */	short field_D0;  // -1
		/* D4h */	float* mLodDistances;
		/* D8h */	cMaterialInfoPtr mMaterialInfo;
		/* DCh */	EffectInstance* mEffects;
		/* E0h */	ModelLights* mLights;
		/* E4h */	Transform mTransform;  // The transformation stored in the prop file
		/* 11Ch */	float mTimeScale;  // 1.0f
		/* 120h */	int field_120;
		/* 124h */	float mEffectRange;
		/* 128h */	int8_t mLodIndex;
		/* 129h */	int8_t mLodLevels;
		/* 12Ah */	short field_12A;
		/* 12Ch */	int field_12C;
		/* 130h */	int field_130;
		/* 134h */	int field_134;  // PLACEHOLDER sunDirAndCelStrength
		/* 138h */	int field_138;  // flags   0x10000000 fixed lod?  0x20000000 no effect range
	};
	ASSERT_SIZE(cMWModelInternal, 0x13C);

	inline int Model::AddRef()
	{
		return ++mnRefCount;
	}

	inline Transform Model::GetTransform() const
	{
		return mTransform;
	}
	inline void Model::SetTransform(const Transform& transform)
	{
		mTransform = transform;
	}

	inline App::PropertyList* Model::GetPropList() const {
		return mpPropList.get();
	}

	inline bool Model::IsVisible() const
	{
		return (mFlags & kModelFlagVisible) != 0;
	}

	inline Math::ColorRGBA Model::GetColor() const {
		return mColor;
	}

	inline void Model::SetColor(const Math::ColorRGBA& color) {
		mColor = color;
	}

	inline IModelWorld* Model::GetModelWorld() const {
		return mpWorld;
	}

	inline Object* Model::GetOwner() const
	{
		return mpOwner.get();
	}
	inline void Model::SetOwner(Object* object)
	{
		mpOwner = object;
	}

	namespace Addresses(Model)
	{
		DeclareAddress(Release);
	}
}