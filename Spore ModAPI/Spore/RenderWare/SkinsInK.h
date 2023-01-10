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

#include <Spore\RenderWare\AnimationSkin.h>
#include <Spore\RenderWare\SkinMatrixBuffer.h>
#include <Spore\RenderWare\Skeleton.h>

namespace RenderWare
{

	///
	/// A structure needed to get animations working. It contains a SkinMatrixBuffer, where the animation result will be written,
	/// a AnimationSkin, that has the base transformations for all bones, and a Skeleton, which contains the hierarchy information.
	///
	struct SkinsInK
	{
		SkinsInK();

		/* 00h */	void* field_0;  // sectionIndex, usually 0x400000 (therefore, 0)
		/* 04h */	void* field_4;  // pointer to a function, this doesn't matter as Spore always sets it
		/* 08h */	SkinMatrixBuffer* mpSkinMatrixBuffer;
		/* 0Ch */	Skeleton* mpSkeleton;
		/* 10h */	AnimationSkin* mpAnimationSkin;

		static const uint32_t RW_TYPE = 0x7000C;
	};
}