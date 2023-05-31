#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\Swarm\IEffectMap.h>

namespace Swarm
{
	namespace Components
	{
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


	//// cEffectMapBase ////

	cEffectMapBase::~cEffectMapBase() {}
	void cEffectMapBase::Start() {}
	void cEffectMapBase::Finish() {}
	int cEffectMapBase::ModificationCount() { return 0; }
	float cEffectMapBase::Height(const Math::Vector3&) { return 1.0f; }
	Math::Vector3 cEffectMapBase::Normal(const Math::Vector3&) { return { 0.0f, 0.0f, 1.0f }; }
	Math::Vector3 cEffectMapBase::Velocity(const Math::Vector3&) { return { 0.0f, 0.0f, 1.0f }; }

	Math::ColorRGBA cEffectMapBase::ColorAlpha(void* unk) {
		typedef float(__thiscall*UnkVftableFunction_t)(void*);
		return { 1.0f, 1.0f, 1.0f, (*(*((UnkVftableFunction_t**)unk) + 8))(unk)};
	}
}
#endif
