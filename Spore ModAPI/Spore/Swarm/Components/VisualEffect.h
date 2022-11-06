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

#include "VisualEffectBlock.h"
#include <EASTL\vector.h>

namespace Swarm
{
	struct cVisualEffectDescription
	{
		/* 00h */	int flags;
		/* 04h */	int componentAppFlagsMask;
		/* 08h */	unsigned long notifyMessageID;
		/* 0Ch */	float screenSizeRange[2];
		/* 14h */	float cursorActiveDistance;
		/* 18h */	char cursorButton;
		/* 1Ch */	eastl::vector<float> lodDistances;
		/* 30h */	float extendedLodWeights[3];
		/* 3Ch */	float field_3C;
		/* 40h */	int seed;
		/* 44h */	eastl::vector<Components::VisualEffectBlock> blocks;
	};
	ASSERT_SIZE(cVisualEffectDescription, 0x58);
}