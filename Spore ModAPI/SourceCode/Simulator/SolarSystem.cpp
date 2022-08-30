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
#include <Spore\Simulator\cHitSphere.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cSolarSystem.h>

namespace Simulator
{
	void cHitSphere::SetParameters(const Vector3& origin, float radius)
	{
		SetPosition(origin);
		mRadius = radius;
	}

	auto_METHOD_VOID(cSolarSystem, Load, Args(cStar* pStar), Args(pStar));
	auto_METHOD_VOID(cSolarSystem, GenerateGraphics, Args(bool create), Args(create));
	auto_METHOD_VOID(cSolarSystem, GenerateCelestialBodiesEffects, 
		Args(bool create, float scale), Args(create, scale));

	auto_STATIC_METHOD_VOID(cSolarSystem, CreateStarEffect,
		Args(IEffectPtr& dst, Swarm::IEffectWorld* pEffectWorld, StarType starType),
		Args(dst, pEffectWorld, starType));
}
#endif
