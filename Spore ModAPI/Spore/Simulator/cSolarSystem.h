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
#include <EASTL\vector.h>

#define cSolarSystemPtr intrusive_ptr<Simulator::cSolarSystem>

namespace Simulator
{
	class cSolarSystem
		: public DefaultRefCounted
		, public ISimulatorSerializable
	{
	public:
		static const uint32_t TYPE = 0x38CF949;
		static const uint32_t NOUN_ID = 0x38CF94C;

		using Object::AddRef;
		using Object::Release;

	protected:
		/* 0Ch */	int field_C;
		/* 10h */	vector<intrusive_ptr<cPlanet>> mPlanets;  // release at C0h
		/* 24h */	vector<intrusive_ptr<cCelestialBody>> mCelestialBodies;
		/* 38h */	intrusive_ptr<cCelestialBody> mpStar1;
		/* 3Ch */	intrusive_ptr<cCelestialBody> mpStar2;
		/* 40h */	vector<int> field_40;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSolarSystem) == 0x54, "sizeof(cSolarSystem) != 54h");
}