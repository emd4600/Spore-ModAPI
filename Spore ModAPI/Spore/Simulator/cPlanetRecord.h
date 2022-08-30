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

#include <Spore\Simulator\StarID.h>
#include <Spore\Simulator\cEllipticalOrbit.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\MathUtils.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cPlanetRecordPtr intrusive_ptr<Simulator::cPlanetRecord>

namespace Simulator
{
	class cStarRecord;

	/// Keeps all the information related to a planet. This does not represent the planet visually 
	/// (that is the Simulator::cPlanet class), this is just information about the planet that will be stored
	/// in the galaxy database in the saved games folder. This class is used by Simulator::cStarRecord.
	/// Despite the name, this class also represents asteroid belts in a solar system.
	///  
	/// Planet records are uniquely identified with an ID, which can be retrieved using GetID().
	/// You can get the record from an ID using cStarManager::GetPlanetRecord().
	class cPlanetRecord
		: public Resource::SpecialResourceObject
	{
	public:
		cStarRecord* GetStarRecord() const;
		StarID GetStarID() const;
		PlanetID GetID() const;
		TechLevel GetTechLevel() const;

	public:
		/* 18h */	string16 mName;
		/// The type of the planet, which determines whether it is a gas giant, asteroid belt, or regular rocky planet.
		/* 28h */	PlanetType mType;  // -1
		// dictates whether or not a planet is destroyed - giving this flag to a planet turns it into a ball of lava, stops you visiting it and makes it vanish completely once you go to another system. And removing this flag makes the planet normal again.
		// 0x1000 - hot orbit, 0x2000 cold orbit??
		/* 2Ch */	int mFlags;  // not initialized
		/// The orbit this planet follows around its star.
		/* 30h */	cEllipticalOrbit mOrbit;
		/// If true, the planet does not rotate around itself (i.e. there are no "days").
		/* 98h */	bool mbRotationIsNull;  // true
		/// Axis of rotation for planet days, that is, in which axis the planet spins around itself.
		/* 9Ch */	Math::Vector3 mRotationAxis;  // (0, 0, 1)
		/// How much time, in real seconds, the planet takes to make a full spin around itself (that is, how long an astronomical day is for this planet).
		/* A8h */	float mRotationPeriod;  // 1.0
		/* ACh */	char field_AC;  // 0xFF
		/* ACh */	char field_AD;  // 0xFF
		/* B0h */	float mAtmosphereScore;  // -1.0
		/* B4h */	float mTemperatureScore;  // -1.0
		/* B8h */	float mWaterScore;  // -1.0
		/// IDs of the plant species that inhabit this planet.
		/* BCh */	vector<ResourceKey> mPlantSpecies;
		/// IDs of the animal species that inhabit this planet.
		/* D0h */	vector<ResourceKey> mAnimalSpecies;
		/* E4h */	vector<int> field_E4;
		/* F8h */	vector<int> field_F8;
		/* 10Ch */	int field_10C;  // not initialized
		/* 110h */	vector<int> field_110;
		/* 124h */	int mNumDefenderUFOs;
		/* 128h */	float mTimeLastBuiltUFOs;
		/* 12Ch */	float mTimeCalledReinforcements;
		/* 130h */	bool mbHomeWorld;
		/* 134h */	vector<int> field_134;
		/* 148h */	vector<uint32_t> mTerrainStampsToRemove;
		/* 15Ch */	vector<int> field_15C;
		/* 170h */	vector<int> field_170;
		/* 184h */	ResourceKey mKey;
		/* 190h */	int field_190;
		/* 194h */	TechLevel mTechLevel;
		/* 198h */	ResourceKey mSpiceGen;
		/* 1A4h */	ResourceKey mGeneratedTerrainKey;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cPlanetRecord) == 0x1B0, "sizeof(cPlanetRecord) != 1B0h");
}