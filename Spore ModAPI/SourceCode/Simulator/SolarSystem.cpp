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
#include <Spore\Simulator\cStar.h>

namespace Simulator
{
	void cHitSphere::SetParameters(const Vector3& origin, float radius)
	{
		SetPosition(origin);
		mRadius = radius;
	}

	auto_METHOD_VOID(cSolarSystem, Load, Args(cStar* pStar), Args(pStar));
	auto_METHOD_VOID_(cSolarSystem, LoadBinaryStar);
	auto_METHOD_VOID_(cSolarSystem, LoadAsteroids);
	auto_METHOD_VOID(cSolarSystem, GenerateGraphics, Args(bool create), Args(create));
	auto_METHOD_VOID(cSolarSystem, GenerateCelestialBodiesEffects, 
		Args(bool create, float scale), Args(create, scale));

	auto_STATIC_METHOD_VOID(cSolarSystem, CreateStarEffect,
		Args(IEffectPtr& dst, Swarm::IEffectsWorld* pEffectWorld, StarType starType),
		Args(dst, pEffectWorld, starType));


	auto_METHOD_(cStar, cSolarSystem*, GetSolarSystem);
	auto_METHOD_(cStar, bool, IsBinaryStar);
	auto_METHOD_(cStar, bool, IsStarOrBinaryStar);


	auto_METHOD_VIRTUAL(cCelestialBody, ISimulatorSerializable, bool, Write, Args(ISerializerStream* arg), Args(arg));
	auto_METHOD_VIRTUAL(cCelestialBody, ISimulatorSerializable, bool, Read, Args(ISerializerStream* arg), Args(arg));
	auto_METHOD_VIRTUAL(cCelestialBody, cGameData, bool, WriteToXML, Args(XmlSerializer* arg), Args(arg));
	auto_METHOD_VIRTUAL_VOID_(cCelestialBody, cGameData, RemoveOwner);

	void* cCelestialBody::Cast(uint32_t typeID) const
	{
		if (typeID == TYPE) return (cCelestialBody*)this;
		else return cGameData::Cast(typeID);
	}

	uint32_t cCelestialBody::GetNounID() const
	{
		return NOUN_ID;
	}

	uint32_t cCelestialBody::GetCastID() const
	{
		return TYPE;
	}

	cCelestialBody::cCelestialBody(cCelestialBodyType type)
		: mType(type)
		, mOrbit()
		, mPosition()
		, mfRotationRate()
		, mName()
		, mpEffect()
		, mpHitSphere()
		, mfHitSphereSize(1.0f)
	{
	}
}
#endif
