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

namespace Simulator
{
	enum GameNounIDs
	{
		kGameData = 0x17F243B,
		kCheatObject = 0x2A37E35,
		kMissionFetch = 0x2AFD284,
		kMissionHappinessEvent = 0x4F3BDE9,
		kMissionMakeAlly = 0x4F77499,
		kRaidPlunderEvent = 0x397BFF3,
		kRaidEvent = 0x3960C0E,
		kMissionColonize = 0x2BA2A0E,
		kMissionEradicate = 0x2F99994,
		kMissionExplore = 0x32A12F1,
		kMissionWar = 0x330FC49,
		kMissionScan = 0x347092D,
		kMissionTerraform = 0x35988F4,
		kMissionTrade = 0x2ADEDFF,
		kMissionTradeRoute = 0x447092D,
		kMissionMultiDelivery = 0x35ED8F6,
		kMissionBiosphere = 0x437444B,
		kGenericPressureEvent = 0x317AFCC,
		kMissionMultiStep = 0x4222283,
		kMissionBalance = 0x347092E,
		kMissionFindAliens = 0x347092F,
		kMissionFlight101 = 0x4222284,
		kMissionUseTool = 0x2ADEDEE,
		kMissionStory201 = 0x4222285,
		kMissionChangeArchetype = 0x4622285,
		kMissionTrackBadge = 0x4633285,
		kMissionAdventure = 0x46332A5,
		kPlayer = 0x2C21781,
		kMilitaryAttackCityOrder = 0x2E9AE6C,
		kCulturalConvertCityOrder = 0x3DF2CC5,
		kGameTerrainCursor = 0x18C40BC,
		kBuildingCityHall = 0x18EA1EB,
		kBuildingIndustry = 0x18EA2CC,
		kBuildingHouse = 0x18EB106,
		kBuildingEntertainment = 0x1A56ABA,
		kBuildingScenario = 0x70703B3,
		kTurret = 0x436F342,
		kCelestialBody = 0x38CFB6B,
		kGameBundle = 0x18C431C,
		kCulturalTarget = 0x3D5C325,
		kCity = 0x18C43E8,
		kGameBundleGroundContainer = 0x1906183,
		kVehicle = 0x18C6DE8,
		kVehicleGroupOrder = 0x2E98AB7,
		kCityWalls = 0x18C7C97,
		kCityTerritory = 0x244FB08,
		kPlaceholderColonyEditorCursorAttachment = 0x2C5C93A,
		kPlanetaryArtifact = 0x2DD8C42,
		kToolObject = 0x4E3FAB5,
		kCivilization = 0x18C816A,
		kCreatureAnimal = 0x18EB45E,
		kCreatureCitizen = 0x18EB4B7,
		kObstacle = 0x3ED8573,
		kGamePlant = 0x18C84A9,
		kFruit = 0x2C9CC91,
		kFruitGroup = 0x2E96892,
		kNest = 0x52AA6122,
		kHerd = 0x1BE418E,
		kEgg = 0x2A034CD,
		kInteractiveOrnament = 0x3A2511E,
		kGameplayMarker = 0x36BE27E,
		kOrnament = 0x18C88E4,
		kAnimalTrap = 0x61494BE,
		kTotemPole = 0x55CF865,
		kTribeFoodMat = 0x629BAFE,
		kRock = 0x2A8FB3F,
		kCommodityNode = 0x403DF5C,
		kMovableDestructibleOrnament = 0x283DDB1,
		kSolarHitSphere = 0x32F9778,
		kHitSphere = 0x2E72CAE,
		kInterCityRoad = 0x2B8A4E7,
		kTribe = 0x18C6D19,
		kTribeTool = 0x18C8F0C,
		kSpear = 0x24270C9,
		kArtilleryProjectile = 0x18C9380,
		kFlakProjectile = 0x240E3BF,
		kDefaultToolProjectile = 0x24270C5,
		kDeepSpaceProjectile = 0x24270C7,
		kSpaceDefenseMissile = 0x244D3C8,
		kDefaultBeamProjectile = 0x24630D7,
		kDefaultAoEArea = 0x4167186,
		kCulturalProjectile = 0x4F76F0D,
		kResourceProjectile = 0x5776A2C,
		kICBM = 0x49CEC61,
		kSoundLoopObject = 0x18EB641,
		kRotationRing = 0x2EE8CE8,
		kRotationBall = 0x7292112,
		kMorphHandle = 0x7A30A12,
		kTargetMorphHandle = 0x76F6E64,
		kArrowMorphHandle = 0x771AD6F,
		kSimpleRotationRing = 0x7A81829,
		kSimpleRotationBall = 0x7ABDD91,
		kPlanet = 0x3275728,
		kVisiblePlanet = 0x44462A6,
		kStar = 0x355C93A,
		kSolarSystem = 0x38CF94C,
		kSimPlanetLowLOD = 0x3572E72,
		kEmpire = 0x18EB9D2,
		kSpaceInventory = 0x21FFA3F,
		kPlayerInventory = 0x2265FDC,
		kGameDataUFO = 0x18EBADC,
		kTribeHut = 0x1E4DAAE,
		kTribePlanner = 0x3098AF98,
		kCreatureSpeciesMission = 0x1406A572,
		kCreatureTutorialMission = 0x34066DBA,
		kTribeToTribeMission = 0x5436411A,
		kFindMission = 0x14D9597F,
		kNanoDrone = 0x6EF0F11,
		kPlaceableSound = 0x74E0069,
		kPlaceableEffect = 0x7B38BA7
	};
}
