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
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\ToolManager.h>
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>
#include <Spore\Simulator\SubSystem\PlanetModel.h>

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\GameNounIDs.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\cBuilding.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cSimulatorSpaceGame.h>


// Needed to load creatures
#include <Spore\Editors\SpeciesManager.h>
#include <Spore\CommonIDs.h>

#include <Spore\Simulator\Serialization.h>
#include <Spore\Simulator\SerializationTypes.h>
#include <Spore\Simulator\NounClassFactories.h>