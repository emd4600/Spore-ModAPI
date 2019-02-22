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

namespace TypeIDs
{
	enum : uint32_t
	{
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
		ufo = 0x476A98C7
	};
}

namespace GroupIDs
{
	enum : uint32_t
	{

		/// Where cell .cll files are stored
		CellModels = 0x40616200,
		/// Where creature .crt files are stored
		CreatureModels = 0x40626200,
		/// Where building .bld files are stored
		BuildingModels = 0x40636200,
		/// Where vehicle .vcl files are stored
		VehicleModels = 0x40646200,
		/// Where vehicle .ufo files are stored
		UfoModels = 0x40656200,
		/// Where flora .flr files are stored
		FloraModels = 0x40666200,

		CivicObjects = 0x9430ADD7
	};
}