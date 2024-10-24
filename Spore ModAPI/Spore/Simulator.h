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

#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\SubSystem\GameInputManager.h>
#include <Spore\Simulator\SubSystem\GameModeManager.h>
#include <Spore\Simulator\SubSystem\GameNounManager.h>
#include <Spore\Simulator\SubSystem\GameViewManager.h>
#include <Spore\Simulator\SubSystem\GameTimeManager.h>
#include <Spore\Simulator\SubSystem\GamePersistenceManager.h>
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\ToolManager.h>
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>
#include <Spore\Simulator\SubSystem\PlanetModel.h>
#include <Spore\Simulator\SubSystem\UIEventLog.h>
#include <Spore\Simulator\SubSystem\PlantSpeciesManager.h>
#include <Spore\Simulator\SubSystem\AnimalSpeciesManager.h>
#include <Spore\Simulator\SubSystem\SpaceGfx.h>
#include <Spore\Simulator\SubSystem\SpaceTrading.h>
#include <Spore\Simulator\SubSystem\TerraformingManager.h>
#include <Spore\Simulator\SubSystem\CinematicManager.h>
#include <Spore\Simulator\SubSystem\UIAssetDiscoveryManager.h>
#include <Spore\Simulator\SubSystem\BundleManager.h>
#include <Spore\Simulator\SubSystem\GamePlantManager.h>
#include <Spore\Simulator\SubSystem\ObstacleManager.h>

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\cBuilding.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cSimulatorSpaceGame.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include <Spore\Simulator\cMissionManager.h>
#include <Spore\Simulator\cTimeOfDay.h>
#include <Spore\Simulator\cCreatureCitizen.h>
#include <Spore\Simulator\cGamePlant.h>
#include <Spore\Simulator\cBuildingScenario.h>
#include <Spore\Simulator\cBuildingIndustry.h>
#include <Spore\Simulator\cBuildingHouse.h>
#include <Spore\Simulator\cBuildingEntertainment.h>
#include <Spore\Simulator\cBuildingCityHall.h>
#include <Spore\Simulator\cStar.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cPlanetRecord.h>
#include <Spore\Simulator\cCelestialBody.h>
#include <Spore\Simulator\cSimulatorUniverse.h>
#include <Spore\Simulator\cSolarSystem.h>
#include <Spore\Simulator\cScenarioEditHistory.h>
#include <Spore\Simulator\SpaceConstants.h>
#include <Spore\Simulator\cDefaultToolProjectile.h>
#include <Spore\Simulator\cDeepSpaceProjectile.h>
#include <Spore\Simulator\cSpaceDefenseMissile.h>
#include <Spore\Simulator\cArtilleryProjectile.h>
#include <Spore\Simulator\cFlakProjectile.h>
#include <Spore\Simulator\cCulturalProjectile.h>
#include <Spore\Simulator\cICBM.h>
#include <Spore\Simulator\cDefaultAoEArea.h>
#include <Spore\Simulator\cSpear.h>
#include <Spore\Simulator\cCollectableItems.h>
#include <Spore\Simulator\cMovableDestructibleOrnament.h>
#include <Spore\Simulator\cToolObject.h>
#include <Spore\Simulator\cPlanetaryArtifact.h>
#include <Spore\Simulator\cRaidEvent.h>
#include <Spore\Simulator\cRaidPlunderEvent.h>
#include <Spore\Simulator\cInteractableObject.h>
#include <Spore\Simulator\cInteractiveOrnament.h>

#include <Spore\Simulator\SimulatorMessages.h>


// Needed to load creatures
#include <Spore\Editors\SpeciesManager.h>
#include <Spore\CommonIDs.h>

#include <Spore\Simulator\Serialization.h>
#include <Spore\Simulator\SerializationTypes.h>
#include <Spore\Simulator\NounClassFactories.h>

#include <Spore\App\ScenarioMode.h>
#include <Spore\App\cCreatureModeStrategy.h>
#include <Spore\App\cCellModeStrategy.h>