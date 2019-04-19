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
#include <Spore\Simulator\SubSystem\GameModeManager.h>
#include <Spore\CommonIDs.h>

/// 
/// @page game_modes Game Modes
///
/// This page includes information about game modes and cameras in Spore.
/// To use game modes and cameras, you need to include the GameModes.h
///
/// A game mode is a mode in the game which has its own controls and cameras. The existing modes in Spore are: 'Editors',
/// 'Cinematics', 'ScenarioMode' (adventure editor), and each of the stages. There can only be one active game mode at a time.
///
/// @tableofcontents
///
/// @section gm_tutorial1 Tutorial: Create a new game mode
///
/// To create a new game mode, you need to inherit the class App::IGameMode. For that, you would need to give an implementation
/// to all its methods; if you want a version where you only override what you want (and that is already reference counted for you),
/// inherit App::DefaultGameMode instead.
///
/// ~~~~~~~~~~~~~{.cpp}
/// class MyGameMode : public App::DefaultGameMode
/// {
/// public:
///		// In this example, we want to provide code for when the mouse is clicked.
///		virtual bool OnMouseDown(int mouseState, float mouseX, float mouseY, int flags) override;
/// };
/// ~~~~~~~~~~~~~
///
/// You can use the "ModAPI Game Mode" item template to create a basic IGameMode class.
///
/// In order to be able to use the new game mode, we need to add it to the App::IGameModeManager. We can do this in an
/// initialization function:
/// ~~~~~~~~~~~~~{.cpp}
/// bool AddGameMode()
/// {
///		// The method takes an ID and a name, both can be used to set this game mode as the active one.
///		App::IGameModeManager::Get()->AddGameMode(new MyGameMode(), 0x76df83a3, "MyGameMode");
///		return true;
/// }
/// ~~~~~~~~~~~~~
///
/// Finally, we have to add this initialization function in the DllMain method of our mod:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// /* inside the DllMain function */
/// // This line is always necessary
/// ModAPI::ModAPIUtils::InitModAPI();
/// 
/// ModAPI::ModAPIUtils::AddInitFunction(AddGameMode);
/// ~~~~~~~~~~~~~~~~~
///
/// @section gm_tutorial2 Tutorial: Set the active game mode
/// 
/// There can only be one active mode at once. When the active mode is changed, the old one is notified, so the user does
/// not have to worry about the transition and whatever mode that was before. The active mode can be set by either ID or 
/// name, with the App::IGameModeManager::SetActiveMode() and App::IGameModeManager::SetActiveModeByName() methods, respectively:
/// ~~~~~~~~~~~~~{.cpp}
/// // both set the game mode created in the example before
/// App::IGameModeManager::Get()->SetActiveMode(0x76df83a3);
/// App::IGameModeManager::Get()->SetActiveModeByName("MyGameMode");
/// ~~~~~~~~~~~~~
///
/// @section gm_tutorial3 Tutorial: Working with cameras
///
/// Similar to game modes, there can only be one active camera at a time. Cameras have their own controls (mouse and keyboard).
/// Cameras are defined in .prop files in the camera_properties~ folder. When the game mode is activated, you should set which camera
/// you want to use (otherwise, the previous one would be used). Check the App::ICameraManager class for more info:
/// ~~~~~~~~~~~~~{.cpp}
/// // This method is called when the game mode is set as active
/// bool MyGameMode::OnEnter()
/// {
///		App::IGameModeManager::Get()->GetCameraManager()->SetActiveCameraByKey("EditorCameraCreatureUI");
///		...
///		return true;
/// }
/// ~~~~~~~~~~~~~
///
/// @section gm_tutorial4 Tutorial Creating custom cameras
///
/// The available cameras in the game might not be enough for you. If you want to control directly how the camera works
/// (the mouse/keyboard input, the functionality of the camera) you must create a new camera type. First, you must inherit
/// the App::ICamera class, or App::DefaultCamera if you don't want to implement all methods. Most methods are very similar to the 
/// ones in game modes.
/// 
/// This is enough to use new cameras. In order to be able to set the camera as active, first you would need to add it to the
/// camera manager with App::ICameraManager::PutCamera():
/// ~~~~~~~~~~~~~{.cpp}
/// App::IGameModeManager::Get()->GetCameraManager()->PutCamera(0x8f645234, new MyCamera());
/// // Now you can set the camera as active using the 0x8f645234 ID
/// ~~~~~~~~~~~~~
///
/// If you want to be able to use this camera in camera_properties~ .prop files, you need to add a factory function:
/// ~~~~~~~~~~~~~{.cpp}
/// App::ICamera* MyCameraFactory(App::PropertyList* propList)
/// {
///		MyCamera* pCamera = new MyCamera();
///		// we assume MyCamera has a method for reading the .prop file
///		pCamera->ReadProp(propList);
///		return pCamera;
/// }
///
/// // You need to add the factory function in an initialization function. And you need to add the initialization function
/// // in the DllMain function as shown before
/// bool AddMyCamera()
/// {
///		App::IGameModeManager::Get()->GetCameraManager()->AddCameraType(0x00DF8567, MyCameraFactory);
///		return true;
/// }
/// ~~~~~~~~~~~~~
/// Now, if in a camera .prop file you set the 'cameraType' property to 0x00DF8567, the new camera type will be used.
///
/// @section more_info More information:
/// - App::IGameMode
/// - App::IGameModeManager
/// - App::ICamera
/// - App::ICameraManager
/// - App::Viewer
///