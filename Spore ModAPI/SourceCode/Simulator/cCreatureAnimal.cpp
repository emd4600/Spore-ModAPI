#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\Simulator\cCreatureAnimal.h>

namespace Simulator
{
	auto_STATIC_METHOD(cCreatureAnimal, cCreatureAnimal*, Create,
		Args(const Vector3& pPosition, cSpeciesProfile* pSpecies, int age, cHerd* pHerd, bool bIsAvatar, bool arg_14),
		Args(pPosition, pSpecies, age, pHerd, bIsAvatar, arg_14));

	auto_METHOD(cCreatureBase, Anim::AnimIndex, PlayAnimation, 
		Args(uint32_t animationID, int arg1, bool arg2),
		Args(animationID, arg1, arg2));

	auto_METHOD(cCreatureBase, Anim::AnimIndex, PlayAnimationTo, 
		Args(uint32_t animationID, cSpatialObject* otherObject, int arg1, int arg2),
		Args(animationID, otherObject, arg1, arg2));

	auto_METHOD_VOID(cCreatureBase, WalkTo, Args(int arg0, const Vector3& arg1, const Vector3& arg2, float arg3, float arg4),
		Args(arg0, arg1, arg2, arg3, arg4));


	auto_METHOD(cCreatureBase, int, GetAbilityIndexByType, Args(int arg), Args(arg));

	auto_METHOD_(cCreatureBase, cCreatureAnimal*, GetAnimalTarget);

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, CreateEffectForPool1Renamed,
		Args(uint32_t effectId, uint32_t poolId),
		Args(effectId, poolId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, CreateEffectForPool1,
		Args(uint32_t effectId),
		Args(effectId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, CreateAndStartEffectForPool1Renamed,
		Args(uint32_t effectId, uint32_t poolId),
		Args(effectId, poolId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, CreateAndStartEffectForPool1,
		Args(uint32_t effectId),
		Args(effectId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, CreateEffectForPool2Renamed,
		Args(uint32_t effectId, uint32_t poolId),
		Args(effectId, poolId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, StartOrStopEffectFromPool1,
		Args(bool create, uint32_t effectId, uint32_t poolId),
		Args(create, effectId, poolId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, StartOrStopEffectFromPool2,
		Args(bool create, uint32_t effectId, uint32_t poolId),
		Args(create, effectId, poolId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, GetEffectFromPools,
		Args(uint32_t effectId),
		Args(effectId));

	auto_METHOD(cCreatureBase, Swarm::IVisualEffect*, StopEffectFromPools,
		Args(uint32_t effectId, int hardStop),
		Args(effectId, hardStop));

	auto_METHOD(cCreatureBase, int, PlayVoice,
		Args(const char* pName, int param2, int param3),
		Args(pName, param2, param3));


	auto_METHOD_VOID(cCreatureAnimal, NPCTickAI, Args(float f), Args(f));
	auto_METHOD_VOID(cCreatureAnimal, AvatarTickAI, Args(float f), Args(f));
}
#endif
