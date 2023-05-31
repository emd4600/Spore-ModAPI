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

/// @file GameModes.h
/// This file contains all the necessary includes for working with game modes and cameras in the game. 
/// For more information, check the IGameMode and ICamera classes.

#include <Spore\App\IGameMode.h>
#include <Spore\App\IGameModeManager.h>
#include <Spore\App\DefaultGameMode.h>
#include <Spore\App\ICamera.h>
#include <Spore\App\ICameraManager.h>
#include <Spore\App\DefaultCamera.h>
#include <Spore\App\cViewer.h>
#include <Spore\App\cMouseCamera.h>
#include <Spore\Simulator\SubSystem\GameModeManager.h>
#include <Spore\CommonIDs.h>
