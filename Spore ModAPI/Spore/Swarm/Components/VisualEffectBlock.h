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

#include <Spore\Transform.h>

#include <EASTL\vector.h>

namespace Swarm
{
	namespace Components
	{

		class VisualEffectBlock
		{
		public:
			struct LODScale
			{
				float emit;
				float size;
				float alpha;
			};

			VisualEffectBlock();

			/* 00h */	char blockType;
			/* 04h */	int flags;
			/* 08h */	Transform transform;
			/* 40h */	char lodBegin;
			/* 41h */	char lodEnd;
			/* 44h */	eastl::vector<LODScale> lodScales;
			/* 58h */	float emitScaleBegin;
			/* 5Ch */	float emitScaleEnd;
			/* 60h */	float sizeScaleBegin;
			/* 64h */	float sizeScaleEnd;
			/* 68h */	float alphaScaleBegin;
			/* 6Ch */	float alphaScaleEnd;
			/* 70h */	int appFlags;
			/* 74h */	int appFlagsMask;
			/* 78h */	short selectionGroup;
			/* 7Ah */	short selectionChance;
			/* 7Ch */	float timeScale;
			/* 80h */	int blockIndex;


			enum
			{
				kVisualEffectBlockFlagsMas = 0x1FF,
				kVEBlockFlagIgnoreLength = 1,
				kVEBlockFlagRespectLength = ~kVEBlockFlagIgnoreLength,
				kVEBlockFlagIgnoreParams = 0x20,
				kVEBlockFlagRigid = 0x40,
			};
		};
		ASSERT_SIZE(VisualEffectBlock, 0x84);
	}
}

