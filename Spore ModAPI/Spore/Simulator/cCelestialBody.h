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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\cEllipticalOrbit.h>
#include <Spore\Simulator\cSolarHitSphere.h>
#include <Spore\Swarm\IEffect.h>
#include <Spore\MathUtils.h>
#include <EASTL\string.h>

#define cCelestialBodyPtr intrusive_ptr<Simulator::cCelestialBody>

namespace Simulator
{
	/// Represents celestial bodies in a solar system (except planets), that is, the star and
	/// the comets. This is the actual graphical representation that you see in the solar system view,
	/// with the graphics itself being `mpEffect`. Celestial bodies are used by the cSolarSystem class.
	class cCelestialBody
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x38CFB68;
		static const uint32_t NOUN_ID = 0x38CFB6B;

	public:
		/* 34h */	cCelestialBodyType mType;
		/* 38h */	cEllipticalOrbit mOrbit;
		/* A0h */	Math::Vector3 mPosition;
		/* ACh */	float mfRotationRate;
		/// Name of the celestial body, shown in a tooltip when hovering it with the mouse.
		/* B0h */	string16 mName;
		/// Effect `0x3D6F8D8` for type Comet
		/* C0h */	IEffectPtr mpEffect;
		/* C4h */	cSolarHitSpherePtr mpHitSphere;
		/// Probably used to detect the mouse.
		/* C8h */	float mfHitSphereSize;  // 1.0
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCelestialBody) == 0xCC, "sizeof(cCelestialBody) != CCh");
}