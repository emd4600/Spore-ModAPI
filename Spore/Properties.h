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

/// 
/// @page properties Properties
///
/// If you ever look to the Spore files in a .package, you will see most of them are .prop files. Those files contain
/// properties, configuration that is used in almost everything in the game. To use properties, you need to include
/// the header Properties.h
///
/// @tableofcontents
///
/// @section prop_tutorial1 Tutorial: Get a certain .prop file
///
/// A .prop file is represented by the App::PropertyList class. To get a specific .prop list from the game files, 
/// you need to use the App::IPropManager::GetPropertyList() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // The arguments are instanceID, groupID. This is to get the ConsequenceTraits!clg_meat.prop file.
/// App::PropertyList::Pointer pProp = nullptr;  // this is just an intrusive_ptr
/// App::IPropManager::Get()->GetPropertyList(Hash::FNV("clg_meat"), Hash::FNV("consequencetraits"), pProp);
/// // the method will return a bool value, whether the list was found or not.
/// ~~~~~~~~~~~~~~~~~
///
/// @section prop_tutorial2 Tutorial: Get properties from a property list.
/// 
/// The easiest way to get the values of properties from a PropertyList is using the static functions declared in the
/// App::Property class. Although you can work with properties directly, usually you only need their values. 
///
/// To get a single value, the methods are App::Property::GetX(), where 'X' is the type of the value. For example:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // It's recommended to give a default value
/// bool bCreateNew = false; 
/// uint32_t nCreatureCount = 0;  // instead of using int or unsigned int, here you must use the int32_t and uint32_t types.
/// 
/// // Assuming pProp is a PropertyList*. If pProp is a intrusive_ptr<PropertyList>, you must use pProp.get() to get the pointer.
/// App::Property::GetBool(pProp, Hash::FNV("nestCreateNew"), bCreateNew); 
/// App::Property::GetInt32(pProp, Hash::FNV("nestCreatureCount"), nCreatureCount); 
/// ~~~~~~~~~~~~~~~~~
///
/// Some properties come in arrays; i.e. a single property has more than one value. The methods are 
/// App::Property::GetArrayX(), where 'X' is the type of the value. For example:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// Transform* pTransformations = nullptr;
/// size_t nTransformCount = 0;  // this value will receive how many values were in the array
///
/// // Assuming pProp is a PropertyList*. If pProp is a intrusive_ptr<PropertyList>, you must use pProp.get() to get the pointer.
/// App::Property::GetArrayTransform(pProp, Hash::FNV("nestTransformations"), nTransformCount, pTransformations); 
/// ~~~~~~~~~~~~~~~~~
///
/// @section prop_tutorial3 Tutorial: Adding properties to a list
///
/// PROP files can be used to saving data. Creating a new list and storing properties to it is really simple:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// PropertyList* pProp = new PropertyList();
/// // sets the value of the int32 property 'dnaAmount' to 80.
/// pProp->SetProperty(Hash::FNV("dnaAmount"), &Property().SetValueInt32(80));
/// ~~~~~~~~~~~~~~~~~
/// For other types, just check the SetValueX() methods (where 'X' is the type of the property) in App::Property class.
///
/// Setting arrays is very similar, you must use the SetArrayX
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// PropertyList* pProp = new PropertyList();
///
/// int32_t values[3] = {30, 40, 10};
///
/// // sets the value of the int32s property 'dnaAmount' to (30, 40, 10).
/// pProp->SetProperty(Hash::FNV("dnaAmount"), &Property().SetArrayInt32(values, 3));
/// ~~~~~~~~~~~~~~~~~
///
/// Finally, you probably want to save this prop list you have created into a file. If you get the IStream* of the file
/// (check the @ref resources "Resources" page for more info), you can save the .prop file with App::PropertyList::Write().
///
/// @section prop_tutorial4 Tutorial: Use App properties
///
/// App properties are special properties that can be accessed with very good performance, and therefore are used generally
/// in the code. They are the properties you find defined in the AppProperties.trigger file, and are configured in the Config
/// ConfigManager.txt files.
///
/// 1. Get the app properties list, with App::GetAppProperties().
/// 2. Use the GetDirectBool(), GetDirectInt() or GetDirectFloat() functions to get the value of those properties.
/// The property IDs used by app properties are defined in the App::SPPropertyIDs namespace.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// if (App::GetAppProperties()->GetDirectBool(App::SPPropertyIDs::kRenderEffects))
/// {
///		...
/// }
/// ~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - App::Property
/// - App::PropertyList
/// - App::IPropManager
/// - App::SPPropertyIDs
///
