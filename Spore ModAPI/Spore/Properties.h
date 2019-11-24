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

/// @file Properties.h
/// This file includes all the necessary headers for working with properties and .prop files.
/// For more information, check the Property class.

#include <Spore\App\Property.h>
#include <Spore\App\PropertyList.h>
#include <Spore\App\DirectPropertyList.h>
#include <Spore\App\IPropManager.h>
#include <Spore\App\SPPropertyIDs.h>

///
/// @namespace App
/// This namespace contains basic utilities that allow to properly interact with the app. Those utilities are:
/// - Game modes: Game modes are the contexts where the game is played. They can receive input events (mouse and keyboard) and
///   they have an update method. For example, each stage in the game is a Game mode. For more information, check the 
///   IGameMode and IGameModeManager classes.
/// - Cameras: With cameras you can control the view in the game. Cameras can receive input events (mouse and keyboard) and they
///   have an update method. For more information, check the ICameraManager and ICamera classes.
/// - Messages: Messages are the basic unit of communication between different objects in the app. 
///   For more information, check the Message, IMessageListener and IMessageManager classes.
/// - Properties: .prop files are the basic unit of configuration in the game files. Most game objects are defined using property lists.
///   For more information, check the Property, PropertyList and IPropManager classes, and the SPPropertyIDs namespace.
/// - Cheats: The ICheatManager class takes care of the cheats and the console of the game.
///
