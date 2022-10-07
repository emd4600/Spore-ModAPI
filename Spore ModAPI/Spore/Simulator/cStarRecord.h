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

#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cStarRecordPtr eastl::intrusive_ptr<Simulator::cStarRecord>

namespace Simulator
{
	typedef int TimeStamp[9];

	enum StarFlags
	{
		kStarFlagHasRare = 0x1000,  // 1 << 12
	};

	/// Keeps all the information related to a star and all the elements in its solar system. 
	/// This does not represent the star visually (that is the Simulator::cPlanet class),
	/// this is just information about the planet that will be stored in the galaxy database 
	/// in the saved games folder. 
	/// 
	/// This class represents any element in the galaxy view, so it is also used by binary stars, 
	/// black holes, proto-planteary disks and the galaxy center. 
	/// 
	/// Star records are uniquely identified with a StarID, which can be retrieved using GetID().
	/// You can get the record from an ID using StarID::GetRecord().
	/// 
	/// The vector `mPlanets` only gets loaded when it is needed, so sometimes it might be empty even if
	/// this star has planets. To force it to load, use cStarRecord::GetPlanetRecords() to access the vector instead.
	/// 
	/// You can create a star record using `(cStarRecord*)ClassManager.Create(cStarRecord::CLASS_ID)`
	class cStarRecord
		: public ISimulatorSerializable
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x3E4353B;
		static const uint32_t CLASS_ID = 0x3E4353C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		//TODO uint32_t getEmpireID PLACEHOLDER

		StarType GetType() const;
		TechLevel GetTechLevel() const;

		inline StarID GetID() const;

		/// Returns the planet record information at the given orbit index (0 - planet closest to the sun,
		/// 1 - second planet, etc)
		cPlanetRecord* GetPlanetRecord(size_t planetIndex);

		/// Returns a reference to the planet records of this star, loading them if they are not loaded.
		/// It is preferrable to use this instead of `mPlanets`.
		/// @returns A read only vector of the planet records in this star.
		vector<cPlanetRecordPtr>& GetPlanetRecords();

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
		//TODO 1 << 4 (16) is visited? sub_BB8B50
		/* 5Ch */	int mFlags;
		/* 60h */	string16 mName;
		/* 70h */	StarID mKey;  // not initialized
		/* 74h */	ResourceKey mCitizenSpeciesKey;
		/* 80h */	cSpeciesProfile* mpSpeciesProfile;
		/* 84h */	vector<cPlanetRecordPtr> mPlanets;
		/// Subset of mPlanets, only those with a specific flag set
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
		DeclareAddress(GetPlanetRecords);  // 0xBB9870   0xBBA900
	}

	inline StarID cStarRecord::GetID() const
	{
		return mKey;
	}
}