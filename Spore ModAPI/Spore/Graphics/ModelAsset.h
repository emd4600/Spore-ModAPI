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
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>

using namespace eastl;

namespace Graphics
{
	class IModelWorld;


	// loc_7536B2 uses scale, render?
	// loc_751BC9 uses scale too, render?
	//  sub_73FA40 -> create Matrix4 from transform
	//  sub_740AC0 -> possible draw function?

	enum
	{
		kModelFlagUseColor = 0x2,

		kModelFlagVisible = 0x8000,

		kModelFlagOverrideBoundingBox = 0x10000,
		kModelFlagOverrideBoundingRadius = 0x20000,  // 1 << 17
		kModelFlagNeedsBake = 0x40000
	};

	class Model
	{
	public:
		int AddRef();
		int Release();

		Transform GetTransform() const;
		void SetTransform(const Transform& transform);

		IModelWorld* GetModelWorld() const;

		App::PropertyList* GetPropList() const;

		ColorRGBA GetColor() const;
		void SetColor(const ColorRGBA& color);

		///
		/// Assigns the required flags to this model depending on the groupID specified.
		/// @param groupID The ID of the model group, in the ModelGroups enum.
		///
		void AddGroup(uint32_t groupID);
		void RemoveGroup(uint32_t groupID);

		bool HasGroup(uint32_t groupID) const;

	public:
		/* 00h */	IModelWorld* mpWorld;
		/* 04h */	int mFlags;
		/* 08h */	Transform mTransform;
		/* 40h */	int mnRefCount;
		/* 44h */	int mGroupFlags[2];
		/* 4Ch */	Math::ColorRGBA mColor;
		/* 5Ch */	bool field_5C;
		/* 5Dh */	bool field_5D;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;  // not initialized
		/* 6Ch */	float mDefaultBoundingRadius;  // 1.0f
		/* 70h */	Math::BoundingBox mDefaultBBox;
		/* 88h */	float field_88;  // FLOAT_MAX
		/* 8Ch */	float field_8C;  // FLOAT_MAX  // distance from camera?
		/* 90h */	intrusive_ptr<App::PropertyList> mpPropList;
	};

	class ModelAsset : public intrusive_list_node, public Model
	{
	public:

	protected:
		// The object, at 30h, has vector<Material*>
		/* 9Ch */	vector<intrusive_ptr<void*>> field_9C;
		/* B0h */	int field_B0;  // not initialized
		/* B4h */	vector<intrusive_ptr<void*>> field_B4;  // PLACEHOLDER not really a vector! related with animations
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	int field_CC;  // -1
		/* D0h */	short field_D0;
		/* D4h */	float mnLodDistances[4];
		/* E4h */	Transform mTransform;
		/* 11Ch */	float field_11C;  // 1.0f
		/* 120h */	int field_120;
		/* 124h */	float mfEffectRange;
		/* 128h */	bool field_128;
		/* 129h */	bool mbUseLodDistances;
		/* 12Ah */	short field_12A;
		/* 12Ch */	int field_12C;
		/* 130h */	int field_130;
		/* 134h */	int field_134;
		/* 138h */	int field_138;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ModelAsset) == 0x13C, "sizeof(ModelAsset) != 13Ch");
	static_assert(sizeof(Model) == 0x94, "sizeof(Model) != 94h");

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

	inline ColorRGBA Model::GetColor() const {
		return mColor;
	}

	inline void Model::SetColor(const ColorRGBA& color) {
		mColor = color;
	}

	inline IModelWorld* Model::GetModelWorld() const {
		return mpWorld;
	}

	namespace Addresses(Model)
	{
		DeclareAddress(Release);
	}
}