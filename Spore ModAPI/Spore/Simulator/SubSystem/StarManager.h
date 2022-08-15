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

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

/// Access the active Simulator star manager, used for most things in space stage.
#define StarManager (*Simulator::cStarManager::Get())

namespace Simulator
{
	struct StarRequestFilter
	{
		StarRequestFilter();

		void AddStarType(StarType type);
		void AddTechLevel(TechLevel level);

		/// Flags that represent accepted star types. By default, all types are accepted.
		/// To accept specific types, first set to 0 and then call AddStarType()
		/* 00h */	int starTypes;  // 0x1FFF
		/// Flags that represent accepted planet tech levels. By default, all tech levels are accepted.
		/// To accept specific levels, first set to 0 and then call AddTechLevel()
		/* 04h */	int techLevels;  // 0x3F
		/* 08h */	int flags;  // 2 - has rare
		/* 0Ch */	float minDistance;  // -1
		/* 10h */	float maxDistance;  // -1
		/* 14h */	float field_14;  // -1
		/* 18h */	int field_18;
	};

	class cTradeRouteData
	{
	public:
		/* 04h */	uint32_t mPoliticalID1;
		/* 08h */	uint32_t mPoliticalID2;
		/* 0Ch */	StarID mStarID1;
		/* 10h */	StarID mStarID2;
		/* 14h */	float mTradeRouteProgress;
		/* 18h */	int field_18;
		/* 1Ch */	uint32_t mTimeSinceLastUFOMS;
		/* 20h */	uint32_t mTimeSinceLastSimMS;
		/* 24h */	float mRouteLength;
	};

	class cSpaceTradeRouteManager
	{
	public:
		virtual ~cSpaceTradeRouteManager();
		virtual bool Write(void*);
		virtual bool Read(void*);

		bool HasTradeRoute(StarID star, uint32_t empireID);

	public:
		/* 04h */	map<int, cTradeRouteData> mTradeRoutes;
		/* 20h */	int field_20;
	};

	typedef map<uint32_t, intrusive_ptr<cEmpire>> EmpiresMap;

	class cStarManager
		: public cStrategy
		, public App::IMessageListener
	{
	public:

		/// Returns the empire that has the given political ID, or nullptr if no empire uses it.
		/// @param politicalID
		cEmpire* GetEmpire(uint32_t politicalID);

		/// Returns the star record assigned to the specified id.
		/// There are three possibilities:
		/// - If id == 0, the galaxy center is returned ?
		/// - If id == -1, nullptr is returned.
		/// - Otherwise, the id is divided in sector index (& 0xFFFFF000) and star index (& 0x00000FFF)
		/// and the star record is returned.
		cStarRecord* GetStarRecord(StarID starID);

		// & 0xFFFFFF is the star record index, 0xFF000000 is the planet index
		cPlanetRecord* GetPlanetRecord(PlanetID planetID);

		EmpiresMap& GetEmpires();

		inline uint32_t GetGrobEmpireID() { return mGrobEmpireID; }

		// sub_1023630 fill fake spaceplayerdata?

		//PLACEHOLDER BAFD80 get star at position?

		/// Generates a new political ID.
		uint32_t NextPoliticalID(bool);

		/// Returns the empire that controls this star record, creating it if necessary.
		/// If no empire controls this star record or the one that controls it does not yet exist,
		/// it will be created and added to the empire map.
		/// @param starRecord
		cEmpire* GetEmpireForStar(cStarRecord* starRecord);

		void RecordToPlanet(cPlanetRecord* record, intrusive_ptr<cPlanet>& dst);

		cStarRecord* GetSol() const;

		cStarRecord* GetScenarioStar() const;

		/// Returns the record for the star closest to the given coords. The Z coordinate is not considered when calculating
		/// distances between stars. A StarRequestFilter can be passed to accept only certain stars (with a certain type,
		/// at a minimum distance, etc)
		/// @param coords The reference coordinates.
		/// @param filter A filter that describes which kind of stars are accepted.
		/// @returns The closest star record that matches the filter.
		cStarRecord* FindClosestStar(const Vector3& coords, const StarRequestFilter& filter = StarRequestFilter());

		/// Finds all the stars that match the given star filter. This can be used to find all the star systems
		/// close to a certain position that match some parameters. For example, you can find all the stars
		/// with empires in a 20 parsec radius, etc.
		/// @param coords The reference coordinates.
		/// @param filter A filter that describes which kind of stars are accepted.
		/// @param dst A vector where all found stars will be added.
		void FindStars(const Vector3& coords, const StarRequestFilter& filter, vector<cStarRecordPtr>& dst);

	public:
		/* 20h */	map<int, int> field_20;
		/* 3Ch */	vector<int> field_3C;
		/* 50h */	vector<cPlanetPtr> field_50;
		/* 64h */	bool field_64;
		/* 68h */	int field_68;  // not initialized
		/* 6Ch */	string16 field_6C;
		/* 7Ch */	char _padding_7C[0x24];  // not initialized;
		/* A0h */	vector<int> field_A0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;
		/* C8h */	vector<vector<intrusive_ptr<cStarRecord>>> mStarRecords;
		/* DCh */	vector<intrusive_ptr<Object>> field_DC;
		/* F0h */	vector<intrusive_ptr<Object>> field_F0;
		/* 104h */	vector<intrusive_ptr<Object>> field_104;
		/* 118h */	vector<intrusive_ptr<Object>> field_118;
		// maps politicalID to star record?
		/* 12Ch	*/	map<uint32_t, intrusive_ptr<Object>> field_12C;
		/* 148h */	intrusive_ptr<cStarRecord> mpSol;
		/* 14Ch */	intrusive_ptr<cStarRecord> field_14C;  // some kind of default record; the galaxy center?
		/* 150h	*/	EmpiresMap mEmpiresMap;
		/* 16Ch */	vector<int> field_16C;
		/* 180h */	int field_180;  // not initialized
		/* 184h */	map<int, int> field_184;
		/* 1A0h */	intrusive_ptr<Object> field_1A0;
		/* 1A4h */	intrusive_ptr<Object> field_1A4;
		/* 1A8h */	int field_1A8;
		/* 1ACh */	int field_1AC;
		/* 1B0h */	int field_1B0;
		/* 1B4h */	int field_1B4;
		/* 1B8h */	int field_1B8;
		/* 1B8h */	float field_1BC;
		/* 1C0h */	float field_1C0;
		/* 1C4h */	int field_1C4;
		/* 1C8h */	int field_1C8;  // not initialized
		/* 1C8h */	int field_1CC;  // not initialized
		/* 1D0h */	int field_1D0;  // not initialized
		// Empire IDs always have the first bit set to 1
		/* 1D4h */	int mNextEmpireID;  // 0x1234, used to give empire record numbers? If so, sub_BA5DA0 generates the next one
		/* 1D8h */	uint32_t mGrobEmpireID;  // -1
		/* 1DCh */	intrusive_ptr<cStarRecord> mpScenarioStar;
		/* 1E0h */	cSpaceTradeRouteManager mTradeRouteMgr;
		/* 204h */	intrusive_ptr<cRelationshipManager> mpRelationshipManager;
		/* 208h */	vector<int> field_208;
		/* 21Ch */	bool field_21C;  // true
		/* 220h */	intrusive_ptr<Object> field_220;
		/* 224h */	intrusive_ptr<Object> field_224;  // not really object
		/* 228h */	intrusive_ptr<Object> field_228;  // not really object

	public:
		/// Returns the active Simulator star manager, used for most things in space stage.
		static cStarManager* Get();
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpaceTradeRouteManager) == 0x24, "sizeof(cSpaceTradeRouteManager) != 24h");

	static_assert(sizeof(cStarManager) == 0x22C, "sizeof(cStarManager) != 22Ch");

	namespace Addresses(cStarManager)
	{
		DeclareAddress(Get);

		DeclareAddress(GetPlanetRecord);
		DeclareAddress(NextPoliticalID);
		DeclareAddress(GetEmpireForStar);
		DeclareAddress(RecordToPlanet);
		DeclareAddress(FindClosestStar);
		DeclareAddress(FindStars);
	}

	namespace Addresses(cSpaceTradeRouteManager)
	{
		DeclareAddress(HasTradeRoute);
	}

	inline cStarRecord* cStarManager::GetSol() const {
		return mpSol.get();
	}

	inline cStarRecord* cStarManager::GetScenarioStar() const {
		return mpScenarioStar.get();
	}

	///
	/// Teleports the player spaceship into the given star record.
	/// Only works if the player is in the galaxy view.
	/// @param star The star record the player will be teleported to.
	void SpaceTeleportTo(cStarRecord* star);

	/// Converts the parsec distance and angle into the 3D coordinates used in the galaxy map
	/// and in functions like cStarManager::FindClosestStar(). The Z coordinate will be 0.
	/// @param parsecDistance The distance from the galaxy center, in parsecs.
	/// @param angle The angle, in degrees.
	/// @param dst A 3D vector where the coordinates will be written.
	Vector3& GalaxyCoordinatesTo3D(float parsecDistance, float angle, Vector3& dst);
}

namespace Addresses(Simulator) {
	DeclareAddress(SpaceTeleportTo);
	DeclareAddress(GalaxyCoordinatesTo3D);
}
