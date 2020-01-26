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

/// @file Effects.h
/// This file includes all the necessary headers to use the Swarm effect system in Spore.

#include <Spore\Swarm\ISwarmManager.h>
#include <Spore\Swarm\IEffect.h>
#include <Spore\Swarm\IEffectWorld.h>

/// @namespace Swarm
///
/// @brief %Swarm is the effects system in Spore
///
/// This namespace contains all the necessary classes needed for working with the Swarm effect system.
/// The main class is the Swarm::ISwarmManager, which is used to control everything related with the system.
/// Swarm::IEffect classes are instances of the effects which can be sued to display and transform effects in the game.
///
