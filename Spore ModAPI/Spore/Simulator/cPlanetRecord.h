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
#include <Spore\App\IDGenerator.h>
#include <Spore\MathUtils.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cPlanetRecordPtr eastl::intrusive_ptr<Simulator::cPlanetRecord>

namespace Simulator
{
	class cStarRecord;
	class cEmpire;

	struct cWallData
	{
		/* 00h */	uint16_t mAnchorPointIndex;
		/* 02h */	int16_t mAnchorPointType;
	};
	ASSERT_SIZE(cWallData, 0x4);

	struct cOrnamentData
	{
		/* 00h */	Math::Vector3 mPosition;
		/* 0Ch */	Math::Quaternion mOrientation;
		/* 1Ch */	float mHealthPoints;
		/* 20h */	int mDamageState;
		/* 24h */	ResourceKey mModelKey;
		/* 30h */	uint32_t mClassId;
	};
	ASSERT_SIZE(cOrnamentData, 0x34);

	struct cBuildingData
	{
		/* 00h */	Math::Vector3 mPosition;
		/* 0Ch */	Math::Quaternion mOrientation;
		/* 1Ch */	float mHealthPoints;
		/* 20h */	int mDamageState;
		/* 24h */	bool mConnected;
		/* 25h */	bool mIrradiated;
		/* 28h */	int mEffectiveness;
		/* 2Ch */	int mFreezeCount;
		/* 30h */	int mSlot;
		/* 34h */	uint32_t mClassId;
	};
	ASSERT_SIZE(cBuildingData, 0x38);

	struct cCityData
	{
		/* 00h */	Math::Vector3 mPosition;
		/* 0Ch */	Math::Quaternion mOrientation;
		/* 1Ch */	float mSpiceProduction;
		/* 20h */	int mMaxSize;
		/* 24h */	int mSize;
		/* 28h */	uint8_t mTurretLocations;
		/* 2Ch */	int mFinalIncome;
		/* 30h */	float mHappiness;
		/* 34h */	int mVehicleSpecialty;  //TODO
		/* 38h */	uint32_t mCaptureID;
		/* 3Ch */	float mCapturePercent;
		/* 40h */	eastl::string16 mName;
		/* 50h */	eastl::string16 mDescription;
		/* 60h */	int16_t field_60[14];
		/* 7Ch */	eastl::vector<cBuildingData> mBuilding;
		/* 90h */	eastl::vector<cOrnamentData> mOrnament;
		/* A4h */	eastl::vector<cWallData> mWall;
		/* B8h */	uint32_t mWallStyle;
		/* BCh */	uint32_t mLevelHandle;
		/* C0h */	uint32_t mTextureHandle;
	};
	ASSERT_SIZE(cCityData, 0xC4);

	struct cVehicleData
	{
		/* 00h */	Math::Vector3 mPosition;
		/* 0Ch */	int mLocomotion;
		/* 10h */	int mPurpose;
	};
	ASSERT_SIZE(cVehicleData, 0x14);

	struct cCivData
	{
		/* 00h */	eastl::vector<ResourceKey> mModelKeys;
		/* 14h */	uint32_t mPoliticalID;
		/* 18h */	uint32_t mColorID;
		/* 1Ch */	float mWealth;
		/* 20h */	int mNumTurrets;
		/* 24h */	int mNumBuildings;
		/* 28h */	eastl::vector<cVehicleData*> mVehicles;
		/* 3Ch */	eastl::vector<cCityData*> mCities;

		/// Adds the given city data to this civilization data, and recalculates the number of turrets and buildings.
		/// @param cityData
		void AddCityData(cCityData* cityData);
	};
	ASSERT_SIZE(cCivData, 0x50);
	namespace Addresses(cCivData) {
		DeclareAddress(AddCityData);  // 0xFF35E0 0xFF2B20
	}

	struct cTribeData
	{
		/* 00h */	uint32_t mPoliticalID;
		/* 04h */	Math::Vector3 mPosition;
		/* 10h */	int mPopulation;
		/* 14h */	int mFood;
	};
	ASSERT_SIZE(cTribeData, 0x18);

	struct cCommodityNodeData
	{
		/* 00h */	uint32_t mOwner;
		/* 04h */	int mMineState;
	};
	ASSERT_SIZE(cCommodityNodeData, 0x8);

	struct cPlanetObjectData
	{
		/* 00h */	uint32_t mObjectType;
		/* 04h */	Math::Vector3 mObjectPosition;
		/* 10h */	uint16_t mAmmo;
		/* 12h */	uint8_t mArtifactType;
		/* 14h */	float mHealth;
		/* 18h */	unsigned int mLootDropTimeS;
		/* 1Ch */	ResourceKey mKey;
		/* 28h */	uint8_t mFlags;
	};
	ASSERT_SIZE(cPlanetObjectData, 0x2C);

	enum PlanetFlags
	{
		kPlanetFlagHasRings = 0x2,  // 1 << 1
		kPlanetFlagIsMoon = 0x4,  // 1 << 2

		kPlanetFlagIsDestroyed = 0x100,  // 1 << 8

		kPlanetFlagRedOrbit = 0x1000,  // 1 << 12
		kPlanetFlagBlueOrbit = 0x2000,  // 1 << 13
	};

	/// Keeps all the information related to a planet. This does not represent the planet visually 
	/// (that is the Simulator::cPlanet class), this is just information about the planet that will be stored
	/// in the galaxy database in the saved games folder. This class is used by Simulator::cStarRecord.
	/// Despite the name, this class also represents asteroid belts in a solar system.
	///  
	/// Planet records are uniquely identified with a PlanetID, which can be retrieved using GetID().
	/// You can get the record from an ID using cStarManager::GetPlanetRecord().
	class cPlanetRecord
		: public Resource::CachedResourceObject
	{
	public:
		static const uint32_t TYPE = 0x3E434E1;

		cStarRecord* GetStarRecord() const;
		StarID GetStarID() const;
		PlanetID GetID() const;
		TechLevel GetTechLevel() const;

		inline bool IsMoon() const {
			return (mFlags & kPlanetFlagIsMoon) != 0;
		}
		inline bool IsDestroyed() const {
			return (mFlags & kPlanetFlagIsDestroyed) != 0;
		}

		void SetGeneratedTerrainKey(const ResourceKey& key);
		ResourceKey& GetGeneratedTerrainKey();

		ResourceKey GetTerrainScriptSource();

		/// Return the key of the sentient species that inhabits this planet.
		/// Only for tribe or greater tech level.
		const ResourceKey& GetCitizenSpeciesKey();

		/// Returns the key to the icon that is displayed in planet tooltip.
		/// This depends on tech level, and whether it has an adventure.
		static const ResourceKey& GetTypeIconKey(cPlanetRecord* record);

		/// Generates a `.prop` file ResourceKey that is currently unused in game packages, so that 
		/// the planet terrain can be saved there.
		/// @returns
		static ResourceKey GenerateTerrainKey();

		/// Returns the distance of the perihelion, which is the planet's closest point to the parent object
		/// in its orbit (the parent object is either a sun, or another planet if this planet is a moon).
		/// @param pRecord The planet
		/// @param moonType Only used for moons (planets orbiting other planets), determines how the perihelion is calculated
		/// @returns
		static float GetPerihelion(cPlanetRecord* pRecord, MoonPerihelionType moonType);

		static void Create(PlanetID planetId, cPlanetRecordPtr& dst);

		/// Generates the civilization/tribe data, including cities, for a planet record.
		/// The number and type of cities will depend on whether it is Empire or Civilization level.
		/// For Empire level, the owner star of the planet must belong to an empire.
		/// @param planetRecord
		/// @param techLevel
		static void FillPlanetDataForTechLevel(cPlanetRecord* planetRecord, TechLevel techLevel);

		/// Calculates the current total spice of a planet, which is the sum of the
		/// production of all its cities. If 'removeSpice' is not 0, that amount of spice will be 
		/// removed from the planet.
		/// @param planetRecord
		/// @param removeSpice
		/// @returns The total spice production of the planet.
		static int CalculateSpiceProduction(cPlanetRecord* planetRecord, int removeSpice = 0);

		/// Method that calculates how much spice is being produced on a single planet, based on difficulty tunings
		/// and number of cities. This method is called every X ticks to update the total spice held on each city.
		/// @param baseValue Base value of the computation (e.g. cCityData::mSpiceProduction)
		/// @param maxOutput Maximum output value, only applied if `limitOutput` is true
		/// @param extraFactor Extra multilpier for the base value
		/// @param isHomeWorld
		/// @param useSuperpowerMultiplier
		/// @param useStorageMultiplier
		/// @param finalFactor Extra multiplied applied to the final output value
		/// @param numCities
		/// @param limitOutput If true, the output value will be capped at `maxOutput`
		/// @returns
		static float CalculateDeltaSpiceProduction(
			float baseValue, float maxOutput, float extraFactor, bool isHomeWorld, 
			bool useSuperpowerMultiplier, bool useStorageMultiplier, float finalFactor, int numCities, bool limitOutput);

		/// Return true if the planet has any city controlled by the specified empire.
		/// If 'requireMoreThanOneTurret' is true, then it will only return true if the controlled city
		/// has more than one turret.
		/// @param planetRecord
		/// @param empire
		/// @param requireMoreThanOneTurret
		static bool HasControlledCity(cPlanetRecord* planetRecord, cEmpire* empire, bool requireMoreThanOneTurret = false);

		/// Generates a terrain file for this planet, assigning it a random source terrain file for T0 planets.
		/// The method will generate a random ID, call SetGeneratedTerrainKey(), and call ITerrainResourceManager::LoadPlanetInfo()
		/// (which returns a random planet, based on the generated terrain key), until it finds a source terrain with temperature score
		/// lower than 0.33 or higher than 0.66.
		/// The planet record temperature and atmosphere scores will be set to the final terrain ones.
		/// @param planetRecord
		static void AssignTerrainT0(cPlanetRecord* planetRecord);

		/// Generates a terrain file for this planet, assigning it a random source terrain file for non-T0 planets.
		/// The method will generate a random ID, call SetGeneratedTerrainKey(), and call ITerrainResourceManager::LoadPlanetInfo()
		/// (which returns a random planet, based on the generated terrain key).
		/// The planet record temperature and atmosphere scores will be set to the final terrain ones.
		/// @param planetRecord
		static void AssignTerrainNonT0(cPlanetRecord* planetRecord);

	public:
		/* 18h */	eastl::string16 mName;
		/// The type of the planet, which determines whether it is a gas giant, asteroid belt, or regular rocky planet.
		/* 28h */	PlanetType mType;  // -1
		// dictates whether or not a planet is destroyed - giving this flag to a planet turns it into a ball of lava, stops you visiting it and makes it vanish completely once you go to another system. And removing this flag makes the planet normal again.
		/* 2Ch */	int mFlags;  // not initialized
		/// The orbit this planet follows around its star.
		/* 30h */	cEllipticalOrbit mOrbit;
		/// If true, the planet does not rotate around itself (i.e. there are no "days").
		/* 98h */	bool mbRotationIsNull;  // true
		/// Axis of rotation for planet days, that is, in which axis the planet spins around itself.
		/* 9Ch */	Math::Vector3 mRotationAxis;  // (0, 0, 1)
		/// How much time, in real seconds, the planet takes to make a full spin around itself (that is, how long an astronomical day is for this planet).
		/* A8h */	float mRotationPeriod;  // 1.0
		/* ACh */	int8_t mPlanetRing;  // 0xFF ring type TODO sub_C6FB50
		/* ADh */	char field_AD;  // 0xFF
		/* B0h */	float mAtmosphereScore;  // -1.0
		/* B4h */	float mTemperatureScore;  // -1.0
		/* B8h */	float mWaterScore;  // -1.0
		/// IDs of the plant species that inhabit this planet.
		/* BCh */	eastl::vector<ResourceKey> mPlantSpecies;
		/// IDs of the animal species that inhabit this planet.
		/* D0h */	eastl::vector<ResourceKey> mAnimalSpecies;
		/* E4h */	eastl::vector<cCommodityNodeData*> mCommodityNodes;
		/* F8h */	eastl::vector<int> field_F8;
		/* 10Ch */	int field_10C;  // not initialized
		/* 110h */	eastl::vector<int> field_110;
		/* 124h */	int mNumDefenderUFOs;
		/* 128h */	float mTimeLastBuiltUFOs;
		/* 12Ch */	float mTimeCalledReinforcements;
		/* 130h */	bool mbHomeWorld;
		/* 134h */	eastl::vector<cPlanetObjectData> mPlanetObjects;
		/* 148h */	eastl::vector<uint32_t> mTerrainStampsToRemove;
		/* 15Ch */	eastl::vector<cCivData*> mCivData;
		/* 170h */	eastl::vector<cTribeData*> mTribeData;
		/* 184h */	PlanetID mKey;
		/* 188h */	ResourceKey field_188;
		/* 194h */	TechLevel mTechLevel;
		/// ID of the spice file of this planet in GroupIDs::SpaceTrading_; all zeros if it hasn't been assigned yet
		/* 198h */	ResourceKey mSpiceGen;
		/* 1A4h */	ResourceKey mGeneratedTerrainKey;
	};
	ASSERT_SIZE(cPlanetRecord, 0x1B0);

	/// Returns the key to the image file that represents this planet main species,
	/// for planets in tribe, civilization, or space tech level.
	/// @param planetRecord
	ResourceKey GetMainSpeciesImageKey(cPlanetRecord* planetRecord);


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(cPlanetRecord)
	{
		DeclareAddress(Create);  // 0xBA5920, 0xBA6300
		DeclareAddress(GetPerihelion);  // 0xC70190 0xC70FC0
		DeclareAddress(FillPlanetDataForTechLevel);  // 0xB96820 0xB97090
		DeclareAddress(CalculateSpiceProduction);  // 0xC6F920 0xC70760
		DeclareAddress(CalculateDeltaSpiceProduction);  // 0xC71200 0xC720A0
		DeclareAddress(GetTerrainScriptSource);  // 0xB8D690 0xB8DEB0
		DeclareAddress(HasControlledCity);  // 0xC6F4B0 0xC702F0
		DeclareAddress(GetTypeIconKey);  // 0xE2EBE0 0xE2EB70
		DeclareAddress(GetCitizenSpeciesKey);  // 0xB8D9C0 0xB8E1E0
		DeclareAddress(AssignTerrainT0);  // 0xBA5740 0xBA6120
		DeclareAddress(AssignTerrainNonT0);  // 0xBA5890 0xBA6270
	}

	inline ResourceKey cPlanetRecord::GenerateTerrainKey()
	{
		ResourceKey dst;
		IDGenerator.Generate(dst, 0x00B1B104, 0x84, 0, 0xAF, 0);
		return dst;
	}

	inline void cPlanetRecord::SetGeneratedTerrainKey(const ResourceKey& key)
	{
		mGeneratedTerrainKey = key;
	}
	inline ResourceKey& cPlanetRecord::GetGeneratedTerrainKey()
	{
		return mGeneratedTerrainKey;
	}
}

namespace Addresses(Simulator) {
	DeclareAddress(GetMainSpeciesImageKey);  // 0x1066AF0 0x1065F10
}