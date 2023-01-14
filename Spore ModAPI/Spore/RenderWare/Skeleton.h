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

namespace RenderWare
{
	enum BoneFlags
	{
		// Sets it's matrix as the previous matrix
		// Not only the first bone can use this
		kBoneRoot = 0,
		// Sets last branch matrix as previous; therefore, all leafs use the same previous matrix
		kBoneLeaf = 1,
		// Saves previous matrix in 'branch' matrix; used when the parent has multiple children, so it can go back
		kBoneBranch = 2,
		// Doesn't change 'previous' matrix; used in leafs whose parent is a root bone (i.e. not a branch)
		kBoneRootLeaf = 3
	};

	///
	/// This structure represents an Skeleton, that is, a hierarchy of bones. Each bone has a unique ID,
	/// a parent (except for the root bone) and flags.
	///
	struct Skeleton
	{
		Skeleton();
		Skeleton(size_t nBoneCount, uint32_t* pBoneIDs, int* pBoneFlags, int* pBoneParents);

		/// An array of flags for each bone.
		/* 00h */	int *mpBoneFlags;

		/// An array of the indices that tell the parent of each bone.
		/* 04h */	int *mpBoneParents;

		/// An array of the IDs of each bone.
		/* 08h */	uint32_t* mpBoneIDs;

		/// The amount of bones contained in this skeleton.
		/* 0Ch */	size_t mnBoneCount;

		/// The ID that identifies this skeleton.
		/* 10h */	uint32_t mSkeletonID;

		/// Usually same as bone count.
		/* 14h */	int field_14;  // boneCount again?

		static const uint32_t RW_TYPE = 0x70002;
	};
}
