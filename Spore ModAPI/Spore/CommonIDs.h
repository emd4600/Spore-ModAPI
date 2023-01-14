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

#include <stdint.h>

enum ModelTypes
{
	kPlantSmall = 0xBCD73E89,
	kPlantMedium = 0xB8669EC9,
	kPlantLarge = 0x37148141,
	kCell = 0xDFAD9F51,
	kCreature = 0x9EA3031A,
	kTribeCreature = 0x372E2C04,
	kCivCreature = 0xCCC35C46,
	kSpaceCreature = 0x65672ADE,
	kAdventurerCreature = 0x4178B8E8,
	kBuildingCityHall = 0x99E92F05,
	kBuildingEntertainment = 0x72C49181,
	kBuildingIndustry = 0x47C10953,
	kBuildingHouse = 0x4E3F7777,
	kBuildingFarm = 0xBDD15F3D,
	kVehicleHarvester = 0xC0B74287,
	kVehicleMilitaryLand = 0x7D433FAD,
	kVehicleMilitaryWater = 0x8F963DCB,
	kVehicleMilitaryAir = 0x441CD3E6,
	kVehicleCulturalLand = 0x9AD7D4AA,
	kVehicleCulturalWater = 0x1F2A25B6,
	kVehicleCulturalAir = 0x449C040F,
	kVehicleEconomicLand = 0xF670AA43,
	kVehicleEconomicWater = 0x2A5147A9,
	kVehicleEconomicAir = 0x1A4E0708,
	kVehicleColonyLand = 0xBC1041E6,
	kVehicleColonyWater = 0xC15695DA,
	kVehicleColonyAir = 0x2090A11B,
	kVehicleUFO = 0x98E03C0D,

};

enum GameModeIDs
{
	/// Not a game mode by itself, used to index game modes.
	kGameModeBase = 0x1654C00,
	kGameCell = 0x1654C00,
	kGameCreature = 0x1654C01,
	kGameTribe = 0x1654C02,
	kGameCiv = 0x1654C04,
	kGameSpace = 0x1654C05,
	kGameEditMode = 0x1654C06,
	kLoadGameMode = 0x1654C08,
	kScenarioMode = 0x1654C10,
	
	kEditorMode = 0x00DBDBA1,
	kGGEMode = 0x2CCD1D2,
	kGameCinematicsMode = 0x8916F92D
};

enum VehicleLocomotion
{
	kVehicleLand = 0,
	kVehicleWater = 1,
	kVehicleAir = 2,
};

enum VehiclePurpose
{
	kVehicleMilitary = 0,
	kVehicleCultural = 1,
	kVehicleEconomic = 2,
	kVehicleColony = 3,
};

enum Difficulty
{
	kDifficultyEasy = 0,
	kDifficultyMedium = 1,
	kDifficultyHard = 2,
};

/// Contains the ID of some important file types.
namespace TypeIDs
{
	enum Names : uint32_t
	{
		jpeg = 0x2F7D0002,
		png = 0x2F7D0004,
		bmp = 0x2F7D0005,
		tga = 0x2F7D0006,
		gif = 0x2F7D0007,
		/// App::PropertyList files.
		prop = 0x00B1B104,
		/// Most textures and models.
		rw4 = 0x2F4E681B,
		/// Creatures
		crt = 0x2B978C46,
		/// Buildings.
		bld = 0x2399BE55,
		/// Land, water and air vehicles.
		vcl = 0x24682294,
		/// Cells.
		cll = 0x3D97A8E4,
		/// Spaceships.
		ufo = 0x476A98C7,
		/// Flora.
		flr = 0x438F6347,
		/// City Music Planner (Anthems)
		cmp = 0x04F684A4,
		/// Binary Editor Model
		bem = 0x1A99B06B,
		/// Spore Materials
		smt = 0x0469A3F7,
		/// Game-generated textures
		raster = 0x2F4E681C,
		/// Game-generated models
		gmdl = 0x00E6BCE5,
		/// Effect directory
		effdir = 0xEA5118B0,
		/// Animation data
		animation = 0xEE17C6AD,
		/// Data of an adventure
		adventure = 0x366A930D,
		/// Type for Pollinator::cAssetMetadata files
		pollen_metadata = 0x30BDEE3
	};
}

/// Contains the ID of some important Spore folders.
namespace GroupIDs
{
	// We cannot use enum class, doesn't implicitly cast
	enum Names : uint32_t
	{
		/// Global folder, also known as animations~. It's 0x00000000
		Global = 0,

		/// Where camera configuration .prop files are stored
		CameraProperties = 0x40410100,

		NounDefinitions = 0x02E9C426,

		/// Where editor configuration .prop files are stored
		EditorSetup = 0x40600100,
		EditorConfig = 0x40600100,

		/// Where part models are stored
		EditorRigblocks = 0x40606000,

		GameTuning = 0x02AE0C7E,

		/// Contains the palette files loaded by Palettes::PaletteMain
		Palettes = 0x406B6A00,
		PaletteDefinitions = 0x406B6A00,

		/// Where adventure props are stored
		PaletteItems = 0xD87454E6,

		/// Where editor paint .prop files are stored
		Paints = 0x406A0200,

		Physics = 0x02A8CB47,

		Verbtrays = 0xAF028F41,

		/// Where space tools .prop files are stored
		SpaceTools = 0x30608F0B,
		/// Where trading configuration of space items are stored
		SpaceTrading = 0x034D97FA,

		TribalTools = 0xF37C24E6,
		TribePlans = 0x72D02C25,

		Abilities = 0x01B68DB4,
		CreatureAbilities = 0xDD91AC58,
		TribeAbilities = 0xC85C1F8B,
		AbilityTemplates = 0xD2FCB262,
		TribeAbilityTemplates = 0x57C90330,

		/// Where cell .cll files are stored
		CellModels = 0x40616200,
		/// Where creature .crt files are stored
		CreatureModels = 0x40626200,
		// The super high-res.gmdl files of creatures are stored in this folder
		CreatureModelsHQ = 0x40627100,
		/// Where building .bld files are stored
		BuildingModels = 0x40636200,
		/// Where vehicle .vcl files are stored
		VehicleModels = 0x40646200,
		/// Where vehicle .ufo files are stored
		UfoModels = 0x40656200,
		UFOModels = 0x40656200,
		/// Where flora .flr files are stored
		FloraModels = 0x40666200,
		/// Where city music .cmp files are stored
		CityMusic = 0x40C0C200,

		CivicObjects = 0x9430ADD7,

		/// The main folder that contains planet scripts. The rest of the folders can be obtained by adding 0x100, 0x200,..., 0xF00
		PlanetScripts = 0x4184A100,

		/// This folder contains popups used in Space stage that can be used with UIEventLog. The hash is FNV of 'Data/Events/Space'.
		SpacePopups = 0x131A9F54,
		SpaceEvents = 0x131A9F54,
		/// This folder contains popups used in Civilization stage that can be used with UIEventLog. The hash is FNV of 'Data/Events/CityCiv'.
		CivPopups = 0xAA9A8ED7,
		CivEvents = 0xAA9A8ED7,
		/// This folder contains popups used in Tribe stage that can be used with UIEventLog. The hash is FNV of 'Data/Events/Tribe'.
		TribePopups = 0x182CD6CE,
		TribeEvents = 0x182CD6CE,

		CivicThumbs = 0x65928944,
		PlannerThumbnails = 0x65928944,

		AssetBrowserData = 0x851D4139,
		AssetBrowserConfig = 0x9A74416B,
		AssetBrowserFeedLists = 0x6EDC12D4,
		AssetBrowserFeedCategories = 0x06B38241,
		AssetBrowserFeedItems = 0x4E5892EB,
		AssetBrowserFilter = 0xCC489C6F,
		AssetBrowserSort = 0xC5296FA9,
		AssetBrowserGraphics = 0xCA14DE92,

		Achievements = 0x05BEFD27,
		AchievementImages = 0x260EB59C,

		Cursors = 0x02393C07,

		terrainSystem_gameAsset = 0x40A02200,

		CompiledStatesLink = 0x40212000,
		CompiledStates = 0x40212001,
		ShaderFragments = 0x40212002,
		Shaders = 0x40212004,
	};
}
