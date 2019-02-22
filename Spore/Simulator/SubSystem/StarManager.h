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

namespace Simulator
{
	class cTradeRouteData
	{
	public:
		/* 04h */	uint32_t mPoliticalID1;
		/* 08h */	uint32_t mPoliticalID2;
		/* 0Ch */	StarIndex mStarID1;
		/* 10h */	StarIndex mStarID2;
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

		bool HasTradeRoute(StarIndex star, uint32_t empireID);

	protected:
		/* 04h */	map<int, cTradeRouteData> mTradeRoutes;
		/* 20h */	int field_20;
	};

	typedef map<uint32_t, intrusive_ptr<cEmpire>> EmpiresMap;

	class cStarManager
		: public cStrategy
		, public App::IMessageListener
	{
	public:

		///
		/// Returns the empire that has the given political ID, or nullptr if no empire uses it.
		/// @param politicalID
		///
		cEmpire* GetEmpire(uint32_t politicalID);

		///
		/// Returns the star record assigned to the specified id.
		/// There are three possibilities:
		/// - If id == 0, the galaxy center is returned ?
		/// - If id == -1, nullptr is returned.
		/// - Otherwise, the id is divided in sector index (& 0xFFFFF000) and star index (& 0x00000FFF)
		/// and the star record is returned.
		cStarRecord* GetStarRecord(StarIndex recordIndex);

		// & 0xFFFFFF is the star record index, 0xFF000000 is the planet index
		cPlanetRecord* GetPlanetRecord(PlanetIndex recordIndex);

		EmpiresMap& GetEmpires();

		inline uint32_t GetGrobEmpireID() { return mGrobEmpireID; }

		// sub_1023630 fill fake spaceplayerdata?

		/// Generates a new political ID.
		uint32_t NextPoliticalID(bool);

		/// Returns the empire that controls this star record, creating it if necessary.
		/// If no empire controls this star record or the one that controls it does not yet exist,
		/// it will be created and added to the empire map.
		/// @param starRecord
		cEmpire* GetEmpireForStar(cStarRecord* starRecord);

		void RecordToPlanet(cPlanetRecord* record, intrusive_ptr<cPlanet>& dst);

	protected:
		/* 20h */	map<int, int> field_20;
		/* 3Ch */	vector<int> field_3C;
		/* 50h */	vector<int> field_50;
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
		/* 148h */	intrusive_ptr<Object> field_148;
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
		/* 1D4h */	int field_1D4;  // 0x1234, used to give empire record numbers? If so, sub_BA5DA0 generates the next one
		/* 1D8h */	uint32_t mGrobEmpireID;  // -1
		/* 1DCh */	intrusive_ptr<cStarRecord> field_1DC;
		/* 1E0h */	cSpaceTradeRouteManager mTradeRouteMgr;
		/* 204h */	intrusive_ptr<cRelationshipManager> mpRelationshipManager;
		/* 208h */	vector<int> field_208;
		/* 21Ch */	bool field_21C;  // true
		/* 220h */	intrusive_ptr<Object> field_220;
		/* 224h */	intrusive_ptr<Object> field_224;  // not really object
		/* 228h */	intrusive_ptr<Object> field_228;  // not really object

	public:
		///
		/// Returns the active Simulator star manager, used for most things in space stage. Same as StarManager().
		///
		static cStarManager* Get();
	};

	///
	/// Returns the active Simulator star manager, used for most things in space stage. Same as cStarManager::Get().
	///
	inline cStarManager* StarManager()
	{
		return cStarManager::Get();
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpaceTradeRouteManager) == 0x24, "sizeof(cSpaceTradeRouteManager) != 24h");

	static_assert(sizeof(cStarManager) == 0x22C, "sizeof(cStarManager) != 22Ch");

	namespace InternalAddressList(cStarManager)
	{
		DefineAddress(Get, GetAddress(0xB3D200, 0xB3D370, 0xB3D3A0));

		DefineAddress(GetPlanetRecord, GetAddress(0xBA6540, 0xBA6EF0, 0xBA6F10));
		DefineAddress(NextPoliticalID, GetAddress(0xBA5DA0, NO_ADDRESS, 0xBA6780));
		DefineAddress(GetEmpireForStar, GetAddress(0xBB0230, NO_ADDRESS, 0xBB14D0));
		DefineAddress(RecordToPlanet, GetAddress(0xBB4960, NO_ADDRESS, 0xBB5B50));
	}

	namespace InternalAddressList(cSpaceTradeRouteManager)
	{
		DefineAddress(HasTradeRoute, GetAddress(0x1038C10, NO_ADDRESS, 0x1037D40));
	}
}
