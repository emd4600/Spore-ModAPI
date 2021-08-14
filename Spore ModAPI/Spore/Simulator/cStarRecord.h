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

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cStarRecordPtr intrusive_ptr<Simulator::cStarRecord>

namespace Simulator
{
	typedef int TimeStamp[9];

	enum class StarType : int
	{
		None = 0,
		/// The galactic core
		GalacticCore = 1,
		/// Black holes
		BlackHole = 2,
		/// Proto-planetary disks
		ProtoPlanetary = 3,
		/// Yellow stars
		StarG = 4,
		/// Blue stars
		StarO = 5,
		/// Red stars
		StarM = 6,
		/// Binary O-O (blue-blue) star system
		BinaryOO = 7,
		/// Binary O-M (blue-red) star system
		BinaryOM = 8,
		/// Binary O-G (blue-yellow) star system
		BinaryOG = 9,
		/// Binary G-G (yellow-yellow) star system
		BinaryGG = 10,
		/// Binary G-M (yellow-red) star system
		BinaryGM = 11,
		/// Binary M-M (red-red) star system
		BinaryMM = 12
	};

	class cStarRecord
		: public ISimulatorSerializable
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x3E4353B;

		using Object::AddRef;
		using Object::Release;

		//TODO uint32_t getEmpireID PLACEHOLDER

		StarType GetType() const;
		TechLevel GetTechLevel() const;

		cPlanetRecord* GetPlanetRecord(size_t planetIndex);

	public:
		/* 0Ch */	int mLastObservedTime;
		/* 10h */	int mSavedGameVersionMajor;
		/* 14h */	int mSavedGameVersionMinor;
		/* 18h */	TimeStamp mSavedGameTimeStamp;
		/* 3Ch */	Math::Vector3 mPosition;
		/* 48h */	StarType mType;  // 1 - Galactic Core
		/* 4Ch */	TechLevel mTechLevel;
		/* 50h */	bool field_50;
		/* 54h */	uint32_t mEmpireID;  // -1
		/* 58h */	uint32_t mStarterWorldID;
		/* 5Ch */	int mFlags;
		/* 60h */	string16 mName;
		/* 70h */	uint32_t mKey;  // not initialized
		/* 74h */	ResourceKey mCitizenSpeciesKey;
		/* 80h */	cSpeciesProfile* mpSpeciesProfile;
		/* 84h */	vector<cPlanetRecordPtr> mPlanets;
		/* 98h */	vector<cPlanetRecordPtr> field_98;
		/* ACh */	char mPlanetCount;

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cStarRecord) == 0xB0, "sizeof(cStarRecord) != B0h");

	namespace Addresses(cStarRecord)
	{
		DeclareAddress(GetPlanetRecord);
	}
}