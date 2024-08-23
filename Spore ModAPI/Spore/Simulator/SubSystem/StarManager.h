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
#include <Spore\Simulator\cCollectableItems.h>
#include <Spore\Resource\Database.h>
#include <Spore\Swarm\Components\DistributeEffect.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
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
		void RemoveStarType(StarType type);
		void RemoveTechLevel(TechLevel level);

		/// Flags that represent accepted star types. By default, all types are accepted.
		/// To accept specific types, first set to 0 and then call AddStarType()
		/* 00h */	int starTypes;  // 0x1FFF
		/// Flags that represent accepted planet tech levels. By default, all tech levels are accepted.
		/// To accept specific levels, first set to 0 and then call AddTechLevel()
		/* 04h */	int techLevels;  // 0x3F
		/* 08h */	int flags;  // 2 - has rare
		/// Minimum distance for stars to be detected, in parsecs.
		/* 0Ch */	float minDistance;  // -1
		/// Maximum distance for stars to be detected, in parsecs.
		/* 10h */	float maxDistance;  // -1
		/* 14h */	float field_14;  // -1
		/* 18h */	int field_18;
	};

	class cTradeRouteData
	{
	public:
		/* 00h */	virtual ~cTradeRouteData();
		/* 04h */	virtual bool Write(ISerializerStream* stream);
		/* 08h */	virtual bool Read(ISerializerStream* stream);

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
	ASSERT_SIZE(cTradeRouteData, 0x28);

	class cSpaceTradeRouteManager
	{
	public:
		virtual ~cSpaceTradeRouteManager();
		virtual bool Write(void*);
		virtual bool Read(void*);

		bool HasTradeRoute(StarID star, uint32_t empireID);

	public:
		/* 04h */	eastl::map<int, cTradeRouteData> mTradeRoutes;
		/* 20h */	int field_20;
	};
	ASSERT_SIZE(cSpaceTradeRouteManager, 0x24);

	typedef eastl::map<uint32_t, cEmpirePtr> EmpiresMap;

	/// This class controls most stuff related with the galaxy, stars, planets and empires.
	/// Use StarManager to access it, like `StarManager.GetSol()`
	/// 
	/// Stars and planets are organized in "records": cStarRecord and cPlanetRecord. Those contain all the data
	/// that is saved into the save games database, and is loaded every time you open the game.
	/// A star record is anything you can click on the galaxy view: stars but also black holes, proto-planterary disks, 
	/// binary star systems, and the galaxy core. The star records keeps a field of StarType to differentiate them.
	///
	/// The galaxy is divided in a 64x64 grid of star sectors, each star sector can have at most 4096 stars.
	/// This is only used to quickly access stars, and it doesn't seem to have any impact on the game.
	/// 
	/// The galaxy is generated using the `0x035DD6E7` (`SG_galaxy_messages~`) effect. This effect is a bunch of `distribute`
	/// effects, one for each star type, which generate random positions depending on a map (with the shape of the galaxy);
	/// then a message is emmited (check SimulatorMessages::kMsgGalaxyGenerateBlackHole and similars) which is handled by the
	/// cStarManager::StarGenerationMessageHandler() method.
	/// 
	/// After the galaxy has been generated it is recommended to not add any new star records; if you want to make special stars,
	/// you can instead use cStarManager::FindClosestStar() to get the star you want, then make whatever changes you need. This
	/// is what cStarManager::GenerateSolSystem() does (we recommend you detour that method since it is executed before saving 
	/// the star database).
	/// 
	/// Galaxy generation generates the star records, but NOT the planets. Planet records are only created when a star system
	/// is first visited (or a bit earlier, for example if a mission has to know a planet from a star) by calling cStarManager::RequirePlanetsForStar().
	/// This means that most theoretical planets in the galaxy never actually exist, since their stars are never visited.
	/// Even when planets are generated, cStarRecord::mPlanets might be empty, as it is only loaded when needed; use cStarRecord::GetPlanetRecords()
	/// instead.
	/// If you want to change how planets are generated for a star, detour cStarManager::GeneratePlanetsForStar().
	class cStarManager
		: public cStrategy
		, public App::IMessageListener
	{
	public:

		/// Returns the empire that has the given political ID, or nullptr if no empire uses it.
		/// @param politicalID
		/// @returns
		cEmpire* GetEmpire(uint32_t politicalID);

		/// Returns the star record assigned to the specified id.
		/// There are three possibilities:
		/// - If id == 0, the temporary star is returned (it is nowhere in the galaxy)
		/// - If id == -1, nullptr is returned.
		/// - Otherwise, the id is divided in sector index (& 0xFFFFF000) and star index (& 0x00000FFF)
		/// and the star record is returned.
		/// @param starID
		/// @returns
		cStarRecord* GetStarRecord(StarID starID);

		/// Returns the planet recor assigned to the specified id.
		/// @param planetID
		/// @returns
		cPlanetRecord* GetPlanetRecord(PlanetID planetID);

		EmpiresMap& GetEmpires();

		/// Returns the political ID of the Grox empire.
		/// @return
		uint32_t GetGrobEmpireID();

		// sub_1023630 fill fake spaceplayerdata?

		/// Generates a new political ID.
		uint32_t NextPoliticalID(bool);

		/// Returns the empire that controls this star record, creating it if necessary.
		/// If no empire controls this star record or the one that controls it does not yet exist,
		/// it will be created and added to the empire map.
		/// @param starRecord
		cEmpire* GetEmpireForStar(cStarRecord* starRecord);

		/// Creates a cPlanet from its planet record.
		/// @param record
		/// @param[out] dst
		void RecordToPlanet(cPlanetRecord* record, cPlanetPtr& dst);

		/// Returns the star record for the Sol system (the one that contains the Earth, Mars, etc)
		/// @returns
		cStarRecord* GetSol() const;

		/// Can only be used in adventure (scenario) mode, returns the star record being used for the adventure.
		/// If not playing from the Space stage, this will return a temporary star that is nowhere in the galaxy.
		/// @returns
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
		void FindStars(const Vector3& coords, const StarRequestFilter& filter, eastl::vector<cStarRecordPtr>& dst);

		/// Calculates the `mAtmosphereScore`, `mTemperatureScore` and `mWaterScore` of a cPlanetRecord depending on the planet type and
		/// the generated terrain key. If planet type is PlanetType::Unset, this method will also set it to the corresponding
		/// PlanetType::T0, PlanetType::T1, PlanetType::T2 or PlanetType::T3 type. 
		/// @param pPlanetRecord
		/// @param pStarRecord Not used
		void CalculatePlanetScores(cPlanetRecord* pPlanetRecord, cStarRecord* pStarRecord = nullptr, int = 0);

		/// Obtains the X and Y coordinates within the 64x64 grid in which galaxy stars are organized.
		/// @param position Real position of the star
		/// @param[out] dstX
		/// @param[out] dstY		
		void GetStarGridPosition(const Vector3& position, unsigned int& dstX, unsigned int& dstY);

		/// Converts X and Y indices of the star record grid (like obtained with GetStarGridPosition())
		/// and translates them into an index that can be used to access the corresponding star second in `mStarRecordGrid`.
		/// @param gridX
		/// @param gridY
		/// @returns
		unsigned int GetRecordGridIndex(unsigned int gridX, unsigned int gridY);

		/// Generates an elliptical orbit that has a distance between the `minDistance` and `maxDistance` arguments.
		/// By default, the orbit is made around the given star but if `pOrbitAroundPlanet` is specified, it
		/// will be made to orbit the planet instead (like a moon).
		/// The period of the orbit will be detemined as a function of the distance and properties 
		/// `averageMoonOrbitPeriodGasGiant`, `averageMoonOrbitPeriodRocky` and `averagePlanetaryOrbitPeriod`.
		/// @param pStarRecord
		/// @param[out] dst
		/// @param minDistance
		/// @param maxDistance
		/// @param pOrbitAroundPlanet Optional, if specified orbit will be around this planet instead of the star.
		void GenerateEllipticalOrbit(cStarRecord* pStarRecord, cEllipticalOrbit& dst, float minDistance, float maxDistance, cPlanetRecord* pOrbitAroundPlanet = nullptr);

		/// Generates the sol system with the Earth and the rest of planets; this does not create a new star record, instead
		/// it modifies the star closest to the `(257.34799, 257.34799)` position.
		/// This method is called during the galaxy generation (which only happens after a galaxy reset) and before the 
		/// stars database is saved, so it can be detoured to make changes to other stars as well.
		void GenerateSolSystem();

		/// Generates the StarID for a new star that would be added to `mStarRecordGrid`. 
		/// The star record using this ID will have to be added at the end of the corresponding vector using GetStarGridPosition()
		/// @param position Position of the star in the galaxy
		StarID CreateNewStarID(const Vector3& position);

		/// Ensures that the given star record has planets. If cStarRecord::mPlanetCount is 0, it will generate them
		/// calling GeneratePlanetsForStar().
		/// @param pStarRecord
		/// @param pFilter
		void RequirePlanetsForStar(cStarRecord* pStarRecord, StarRequestFilter* pFilter = nullptr);

		/// Generates the planets for a star record. Planet records are not generated when the galaxy is generated;
		/// instead, they are only created the first time the star is discovered. This function will create a number
		/// of planets between properties `numPlanetsMin` and `numPlanetsMax` from `mpSolarSystemPropList`.
		/// This function changes the cStarRecord::mPlanetCount of the star, but it does NOT add the planets to the
		/// star planets vector.
		/// @param pStarRecord
		/// @param pFilter
		/// @param useMaxPlanets If true, spawn the maximum amount of planets.
		void GeneratePlanetsForStar(cStarRecord* pStarRecord, StarRequestFilter* pFilter, bool useMaxPlanets);

		/// Method used by the galaxy generation effect to create the cStarRecord instances. This method is the handler of the corresponding
		/// `kMsgGalaxyGenerate...` messages, such as SimulatorMessages::kMsgGalaxyGenerateBlackHole. The method generates
		/// one cStarRecord for every entry in the `pDistributeData` object.
		/// @param messageId
		/// @param pDistributeData
		/// @param starType
		/// @returns True
		static bool StarGenerationMessageHandler(uint32_t messageId, Swarm::Components::DistributeEffectMessageData* pDistributeData, StarType starType);

	public:
		/* 20h */	eastl::map<int, int> field_20;
		/* 3Ch */	eastl::vector<int> field_3C;
		/* 50h */	eastl::vector<cPlanetPtr> field_50;
		/* 64h */	bool field_64;
		/* 68h */	int field_68;  // not initialized
		/* 6Ch */	eastl::string16 field_6C;
		/* 7Ch */	char _padding_7C[0x24];  // not initialized;
		/// List of all instance IDs of files in `StarterWorlds` folder, only the ones that aren't already used
		/* A0h */	eastl::vector<uint32_t> mAvailableStarterWorlds;
		/* B4h */	App::MessageListenerData mMessageListenerData;
		/// All star records of the galaxy, organized in a grid of 64x64 different blocks. First index is "y" index of the grid,
		/// second index is "x" index of the grid. You can get x, y for certain coordinates with the GetStarGridPosition() method
		/* C8h */	eastl::vector<eastl::vector<cStarRecordPtr>> mStarRecordGrid;
		/* DCh */	eastl::vector<cStarRecordPtr> mStarterStarRecords;
		/* F0h */	eastl::vector<cStarRecordPtr> mSavedGameStarRecords;
		/* 104h */	eastl::vector<cStarRecordPtr> mBlackHoles;
		/* 118h */	eastl::vector<cStarRecordPtr> mPossibleStartLocations;
		/// Maps empire political IDs to their home star cStarRecord
		/* 12Ch	*/	eastl::map<uint32_t, cStarRecordPtr> mEmpireHomeStarRecords;
		/* 148h */	cStarRecordPtr mSol;
		/// A star record used in contexts where a real one is not available, such as playing an adventure from the create menu.
		/* 14Ch */	cStarRecordPtr mpTempStar;
		/* 150h	*/	EmpiresMap mEmpires;
		/* 16Ch */	eastl::vector<eastl::string16> mEmpireNamesInUse;
		/* 180h */	int field_180;  // not initialized
		/* 184h */	eastl::map<PlanetID, uint32_t> mAdventureIDs;  //TODO
		///`gametuning~!SpaceSolarSystem.prop`
		/* 1A0h */	PropertyListPtr mpSolarSystemPropList;
		///`gametuning~!SpaceGalacticConstants.prop`
		/* 1A4h */	PropertyListPtr mpGalacticConstantsPropList;
		/* 1A8h */	int mTScoreTribePlanet;
		/* 1ACh */	int mTScoreCivPlanet;
		/* 1B0h */	int mTScoreColonyPlanet;
		/* 1B4h */	int mTScoreEmpireHomeWorld;
		/* 1B8h */	int mTScoreGrobPlanet;
		/* 1BCh */	float mGrobOnlyRadius;
		/* 1C0h */	float mChanceStarIsHomeStar;
		/* 1C4h */	int mPercentChanceStarHasRare;
		/* 1C8h */	int mGalacticCoreTravelLimit;  // not initialized
		/* 1C8h */	Vector2 mGalacticCoreTravelRadii;  // not initialized
		// Empire IDs always have the first bit set to 1
		/* 1D4h */	int mNextPoliticalID;  // 0x1234, used to give empire record numbers? If so, sub_BA5DA0 generates the next one
		/// Political ID for the Grox (Grob)
		/* 1D8h */	uint32_t mGrobID;  // -1
		/* 1DCh */	cStarRecordPtr mpScenarioStar;
		/* 1E0h */	cSpaceTradeRouteManager mTradeRouteManager;
		/* 204h */	eastl::intrusive_ptr<cRelationshipManager> mpRelationshipManager;
		//TODO
		/* 208h */	eastl::vector<eastl::string> mTransactionLog;
		/* 21Ch */	bool field_21C;  // true
		/* 220h */	cCollectableItemsPtr mpGlobalCLGItems;
		/// `planetRecords.pkt`
		/* 224h */	DatabasePtr mpPlanetRecordsTempDatabase;
		/// `planetRecords.pkp`
		/* 228h */	DatabasePtr mpPlanetRecordsDatabase;

	public:
		/// Returns the active Simulator star manager, used for most things in space stage.
		static cStarManager* Get();
	};
	ASSERT_SIZE(cStarManager, 0x22C);

	namespace Addresses(cStarManager)
	{
		DeclareAddress(Get);

		DeclareAddress(GetPlanetRecord);
		DeclareAddress(NextPoliticalID);
		DeclareAddress(GetEmpireForStar);
		DeclareAddress(RecordToPlanet);
		DeclareAddress(FindClosestStar);
		DeclareAddress(FindStars);
		DeclareAddress(CalculatePlanetScores);  // 0xBA5C10, 0xBA65F0
		DeclareAddress(StarGenerationMessageHandler);  // 0xBB4D10, 0xBB5F00
		DeclareAddress(GetStarGridPosition);  // 0xBA6880, 0xBA7250
		DeclareAddress(GenerateEllipticalOrbit);  // 0xBA81B0, 0xBA8D90
		DeclareAddress(GenerateSolSystem);  // 0xBB1A00, 0xBB2BF0
		DeclareAddress(RequirePlanetsForStar);  // 0xBB3AA0 0xBB4C90
		DeclareAddress(GeneratePlanetsForStar);  // 0xBB30B0 0xBB42A0
	}

	namespace Addresses(cSpaceTradeRouteManager)
	{
		DeclareAddress(HasTradeRoute);
	}

#ifndef SDK_TO_GHIDRA
	inline cStarRecord* cStarManager::GetSol() const {
		return mSol.get();
	}

	inline cStarRecord* cStarManager::GetScenarioStar() const {
		return mpScenarioStar.get();
	}

	inline unsigned int GetRecordGridIndex(unsigned int gridX, unsigned int gridY)
	{
		return gridY * 64 + gridX;
	}

	inline StarID cStarManager::CreateNewStarID(const Vector3& position)
	{
		unsigned int gridX, gridY;
		GetStarGridPosition(position, gridX, gridY);
		unsigned int sectorIndex = GetRecordGridIndex(gridX, gridY);
		unsigned int size = mStarRecordGrid[sectorIndex].size();
		return StarID(sectorIndex, size);
	}

	inline uint32_t cStarManager::GetGrobEmpireID() { return mGrobID; }
#endif


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
