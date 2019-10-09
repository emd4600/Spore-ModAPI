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

#include <Spore\Swarm\Components\VisualEffect.h>

namespace Swarm
{
	namespace Components
	{
		VisualEffect::VisualEffect()
			: flags(0)
			, componentAppFlagsMask(0)
			, notifyMessageID(0)
			, screenSizeRange()
			, cursorActiveDistance(0)
			, cursorButton(0)
			, lodDistances()
			, extendedLodWeights()
			, field_3C(0)
			, seed(0)
			, blocks()
		{

		}

		VisualEffectBlock::VisualEffectBlock()
			: blockType(0)
			, flags(kVEBlockFlagRigid)
			, transform()
			, lodBegin()
			, lodEnd()
			, lodScales()
			, emitScaleBegin(1.0f)
			, emitScaleEnd(1.0f)
			, sizeScaleBegin(1.0f)
			, sizeScaleEnd(1.0f)
			, alphaScaleBegin(1.0f)
			, alphaScaleEnd(1.0f)
			, appFlags(0)
			, appFlagsMask(0)
			, selectionGroup(0)
			, selectionChance(0)
			, timeScale(1.0f)
			, blockIndex(-1)
		{
		}
	}
}