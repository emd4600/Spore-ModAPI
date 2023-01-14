/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\cMaterialInfo.h>
#include <EASTL\internal\thread_support.h>

namespace Graphics
{
	void FilterSettings::SetRequiredGroup(uint32_t group)
	{
		int flags = ModelManager.GetGroupFlag(group);
		requiredGroupFlags |= 1i64 << flags;
	}
	void FilterSettings::SetExcludedGroup(uint32_t group)
	{
		int flags = ModelManager.GetGroupFlag(group);
		excludedGroupFlags &= ~(1i64 << flags);
	}

	void Model::AddGroup(uint32_t groupID)
	{
		int flags = ModelManager.GetGroupFlag(groupID);
		if (flags < 64)
		{
			mGroupFlags[flags/32] |= 1 << (flags & 31);
		}
	}

	void Model::RemoveGroup(uint32_t groupID)
	{
		int flags = ModelManager.GetGroupFlag(groupID);
		if (flags < 64)
		{
			mGroupFlags[flags / 32] &= ~(1 << (flags & 31));
		}
	}

	bool Model::HasGroup(uint32_t groupID) const
	{
		int flags = ModelManager.GetGroupFlag(groupID);
		if (flags < 64) return (mGroupFlags[flags / 32] & (1 << (flags & 31))) != 0;
		return false;
	}

	auto_STATIC_METHOD_(IModelManager, IModelManager*, Get);


	auto_METHOD_(Model, int, Release);


	cMaterialInfo::~cMaterialInfo() {
		for (auto t : mData) {
			if (t) delete t;
		}
	}

	cModelInstance::cModelInstance()
		: mMeshes()
		, mBoneRanges()
		, mMaterials()
		, mMaterialInfos()
		, mRegionMaterialInfos()
		, mModelToWorldTransform()
		, mBoundingBox()
		, mBoundingRadius(1.0f)
		, mpRenderWare()
		, field_C8()
		, field_CC()
		, field_D0()
		, field_D4({ FLT_MIN, FLT_MIN, FLT_MIN }, { FLT_MAX, FLT_MAX, FLT_MAX })
		, field_EC()
		, mpAnimations()
		, field_F8(-1)
		, field_FC(-1)
	{
	}

	cModelInstance::~cModelInstance() {
		if (field_D0) {
			if (*field_D0) {
				delete *field_D0;
			}
			delete field_D0;
		}
		field_D0 = nullptr;
	}
}