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

#include <Spore\RenderWare\Skeleton.h>
#include <Spore\RenderWare\SkinsInK.h>
#include <Spore\RenderWare\AnimationSkin.h>
#include <Spore\RenderWare\SkinMatrixBuffer.h>

namespace RenderWare
{
	Skeleton::Skeleton()
		: mpBoneIDs(nullptr)
		, mpBoneFlags(nullptr)
		, mpBoneParents(nullptr)
		, mnBoneCount(0)
		, mSkeletonID(0)
		, field_14(0)
	{

	}

	Skeleton::Skeleton(size_t nBoneCount, uint32_t* pBoneIDs, int* pBoneFlags, int* pBoneParents)
		: mpBoneIDs(pBoneIDs)
		, mpBoneFlags(pBoneFlags)
		, mpBoneParents(pBoneParents)
		, mnBoneCount(nBoneCount)
		, mSkeletonID(0)
		, field_14(nBoneCount)
	{

	}

	SkinsInK::SkinsInK()
		: mpAnimationSkin(nullptr)
		, mpSkinMatrixBuffer(nullptr)
		, mpSkeleton(nullptr)
		, field_0(nullptr)
		, field_4(nullptr)
	{

	}

	AnimationSkin::AnimationSkin()
		: mpData(nullptr)
		, mnCount(0)
		, field_08()
		, field_0C()
	{

	}

	SkinMatrixBuffer::SkinMatrixBuffer()
		: mpData(nullptr)
		, mnCount(0)
		, field_08()
		, field_0C()
	{

	}
}
