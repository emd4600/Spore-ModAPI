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
#include <Spore\Simulator\cCelestialBody.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cStarRecord.h>
#include <EASTL\vector.h>

#define cSolarSystemPtr intrusive_ptr<Simulator::cSolarSystem>

namespace Simulator
{
	class cStar;

	/// Holds visual information about a solar system in the solar system view, or when inside a planet.
	/// In Space Stage, when inside a solar system, this class generates all what you see inside it: 
	/// it generates the effects of the star/black hole/binary stars/etc, comets, and planets.
	/// Stars and comets are represented by the Simulator::cCelestialBody class, and planets by the 
	/// Simulator::cPlanet class. Both classes have a Simulator::cEllipticalOrbit that describes the
	/// orbit of that celestial body or planet.
	/// 
	/// First, the solar system is generated with the cSolarSystem::Load() method using a Simulator::cStar object.
	/// This does not generate any graphics (models or effects), it just creates the 
	class cSolarSystem
		: public DefaultRefCounted
		, public ISimulatorSerializable
	{
	public:
		static const uint32_t TYPE = 0x38CF949;
		static const uint32_t NOUN_ID = 0x38CF94C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Generates all data of the solar system for the given star data.
		/// By default, this generates `mpStar1` (and `mpStar2` if it's a binary system),
		/// the asteroids, and the planets. This does not any visual effects yet, it only sets up the
		/// Simulator classes (cCelestialBody and cPlanet).
		/// Source code: @ref SourceCode-Simulator-cSolarSystem-Load
		/// @param pStar
		void Load(cStar* pStar);

		/// Called by Load() only in binary systems, generates the two individual star celestial bodies.
		void LoadBinaryStar();

		/// Called by Load(), generates the asteroids celestial bodies.
		void LoadAsteroids();

		/// Loads/unloads the effects and graphics of this solar system. 
		/// If `create` is true it must generate them, if it is false it must destroy them instead.
		/// This method must also create the cSolarHitSphere hit spheres of the celestial bodies.
		/// @param create If true, create and load the graphics, if false, destroy them.
		void GenerateGraphics(bool create);

		/// Loads/unloads the effects for the celestial bodies of this solar system.
		/// This method generates the effect of the star (or black hole/planetary disk etc) and comets.
		/// By default, these are the effects used:
		/// - Comets: `0x3D6F8D8`
		/// - Stars: check CreateStarEffect()
		/// Source code: @ref SourceCode-Simulator-cSolarSystem-GenerateCelestialBodiesEffects
		/// @param create If true, create and load the graphics, if false, destroy them.
		/// @param scale The scale that will be applied to the effects.
		void GenerateCelestialBodiesEffects(bool create, float scale);

		/// Instantiates the effect of a star in the solar system view. This method does nothing for
		/// binary star types, as those are two effects of their respective star types.
		/// By default, the effects are:
		/// - StarType::GalacticCore: `0x3D6EF7B`
		/// - StarType::BlackHole: `0x3D6EEF6`
		/// - StarType::ProtoPlanetary: `0x3D6EF40`
		/// - StarType::StarG: `0x3D6EF4D`
		/// - StarType::StarO: `0x3D6EF59`
		/// - StarType::StarM: `0x3D6EF67`
		/// @param dst The effect must be created into this variable.
		/// @param pEffectWorld Effect world where the effect must be created.
		/// @param starType The kind of star, except binary stars.
		static void CreateStarEffect(IVisualEffectPtr& dst, Swarm::IEffectsWorld* pEffectWorld, StarType starType);

	public:
		/* 0Ch */	intrusive_ptr<cStar> mpOwnerStar;
		/* 10h */	vector<cPlanetPtr> mPlanets;
		/* 24h */	vector<cCelestialBodyPtr> mCelestialBodies;
		/* 38h */	cCelestialBodyPtr mpStar1;
		/* 3Ch */	cCelestialBodyPtr mpStar2;
		/* 40h */	vector<ModelPtr> field_40;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSolarSystem) == 0x54, "sizeof(cSolarSystem) != 54h");

	namespace Addresses(cSolarSystem)
	{
		DeclareAddress(Load);  // 0xC85AC0  0xC868F0
		DeclareAddress(LoadBinaryStar);  // 0xC848A0  0xC856D0
		DeclareAddress(LoadAsteroids);  // 0xC84D90  0xC85BC0
		DeclareAddress(GenerateGraphics);  // 0xC85FD0 0xC86E00
		DeclareAddress(CreateStarEffect);  // 0xC82FF0 0xC83E80
		DeclareAddress(GenerateCelestialBodiesEffects);
	}
}