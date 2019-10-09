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

#include <Spore\Resource\ResourceObject.h>
#include <Spore\MathUtils.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Simulator
{
	class cStarRecord;

	typedef uint32_t StarIndex;

	inline size_t GetSectorIndex(StarIndex starIndex) {
		return (int(starIndex) & 0xFFFFF000) >> 24;
	}
	inline size_t GetStarIndex(StarIndex starIndex) {
		return int(starIndex) & 0x00000FFF;
	}

	typedef uint32_t PlanetIndex;

	inline StarIndex GetStarRecordIndex(PlanetIndex planetIndex) {
		return int(planetIndex) & 0x00FFFFFF;
	}
	inline size_t GetPlanetIndex(PlanetIndex planetIndex) {
		return (int(planetIndex) & 0xFF000000) >> 24;
	}

	class cEllipticalOrbit
	{
	public:
		/* 00h */	bool mbNullOrbit;  // true
		/* 04h */	Math::Vector3 mPlaneNormal;
		/* 10h */	float mEccentricity;
		/* 14h */	Math::Vector3 mPerihelion;
		/* 20h */	float mPeriod;
	};

	class cPlanetRecord
		: public Resource::SpecialResourceObject
	{
	public:
		cStarRecord* GetStarRecord();

		inline StarIndex GetStarIndex() {
			return Simulator::GetStarIndex(mKey.instanceID);
		}

	public:
		/* 18h */	string16 mName;
		/* 28h */	int mType;  // -1
		/* 2Ch */	int mFlags;  // not initialized
		/* 30h */	cEllipticalOrbit mOrbit;
		/* 54h */	char padding_54[0x44];
		/* 98h */	bool mbRotationIsNull;  // true
		/* 9Ch */	Math::Vector3 mRotationAxis;  // (0, 0, 1)
		/* A8h */	float mRotationPeriod;  // 1.0
		/* ACh */	char field_AC;  // 0xFF
		/* ACh */	char field_AD;  // 0xFF
		/* B0h */	float mAtmosphereScore;  // -1.0
		/* B4h */	float mTemperatureScore;  // -1.0
		/* B8h */	float mWaterScore;  // -1.0
		/* BCh */	vector<ResourceKey> mPlantSpecies;
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
		/* 194h */	int mTechLevel;  // 5 empire, 1 wildlife
		/* 198h */	ResourceKey mSpiceGen;
		/* 1A4h */	ResourceKey mGeneratedTerrainKey;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cPlanetRecord) == 0x1B0, "sizeof(cPlanetRecord) != 1B0h");
}