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

#include <Spore\App\PropertyList.h>
#include <Spore\App\ICamera.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\cViewer.h>

#define ICameraManagerPtr eastl::intrusive_ptr<App::ICameraManager>

namespace App
{
	///
	/// Camera types need a static function that creates the correct camera instance. 
	/// The function must take a PropertyList* as a parameter, and returns an ICamera*.
	/// This does not need to read the .prop file; instead, it should be stored in a field in the camera;
	/// the manager will call ICamera::Initialize() when necessary; there's where the .prop file should be read.
	///
	typedef ICamera*(*CameraFactoryFunction_t)(PropertyList* pPropList);

	///
	/// This manager handles the cameras in the game. A camera is represented by the class ICamera, and is responsible of
	/// setting the view transformations necessary for the game to render. The manager can only have one active camera at a time;
	/// this active camera receives the user input (mouse and keyboard) and updates the view transformations used for rendering.
	/// The cameras are mapped by ID and, optionally, by a name.
	///
	/// The manager also contains a map of camera types. An ID is mapped to a factory function that creates an ICamera of the appropiate type;
	/// when a camera .prop file is readed, the camera will be created with the appropiate factory according to its 'cameraType' property.
	/// On initialization, the manager reads all the cameras in the 0x40410100 (camera_properties~) folder.
	///
	/// This manager is different from most managers, that have a Get() method to get the current instance. ICameraManager depends on the
	/// mode manager, and therefore the method IGameModeManager::GetCameraManager() must be used.
	///
	class ICameraManager : public IMessageListener
	{
	public:
		virtual ~ICameraManager() {};

		/* 10h */	virtual bool Initialize(const char* pCheatName) = 0;
		/* 14h */	virtual bool Dispose() = 0;

		///
		/// Sets the Viewer that will receive the results of the camera in this camera manager.
		/// @param pViewer The new Viewer.
		///
		/* 18h */	virtual void SetViewer(cViewer* pViewer) = 0;

		///
		/// Gets the Viewer that will receive the results of the camera in this camera manager.
		///
		/* 1Ch */	virtual cViewer* GetViewer() = 0;

		///
		/// Adds a new camera type. When a camera settings .prop file uses the 'cameraType' property with
		/// this typeID value, the given factory function will be called to create a new ICamera.
		/// @param typeID The ID that identifies this type of camera.
		/// @param function A function that takes a App::PropertyList* parameter and returns an ICamera*.
		/// 
		/* 20h */	virtual void AddCameraType(uint32_t typeID, CameraFactoryFunction_t function) = 0;

		///
		/// Adds a new camera into this manager. The camera will be mapped to the given cameraID and ICamera::OnAttach(ICameraManager*) will be called.
		/// If another camera is already mapped to that ID, ICamera::OnDeattach() will be called on it. Additionally, if the camera replaced is 
		/// the active one, ICamera::OnExit() will be called, and the new camera will be the active.
		///
		/// A name can also be optionally specified.
		/// @param cameraID The ID that uniquely identifices the camera.
		/// @param pCamera The new ICamera.
		/// @param pName [Optional] A eastl::string that identifies the camera.
		///
		/* 24h */	virtual void PutCamera(uint32_t cameraID, ICamera* pCamera, const char16_t* pName = nullptr) = 0;

		///
		/// Reads and stores in this manager all the cameras in the 0x40410100 (camera_properties~) folder.
		///
		/* 28h */	virtual void ParseCameras() = 0;
		
		///
		/// A method called every game loop that updates the active camera.
		/// This will call the ICamera::Update() method on the active camera, passing the manager Viewer as a parameter.
		/// @param nDeltaTime The time ellapsed since the last call, in milliseconds.
		///
		/* 2Ch */	virtual void Update(int nDeltaTime) = 0;

		///
		/// Sets the active camera to the one that matches the given key eastl::string. Only the instance ID will be used,
		/// the rest will be ignored. The eastl::string will be parsed using ResourceKey::Parse(). 
		/// This will call SetActiveCameraByID(uint32_t).
		/// @param pKeyString The eastl::string representation of a ResourceKey.
		/// @returns True if the active camera was changed, false otherwise.
		///
		/* 30h */	virtual bool SetActiveCameraByKey(const char16_t* pKeyString) = 0;

		///
		/// Sets the active camera to the one mapped to the given ID. If the ID is not mapped, nothing will happen.
		/// This will call SetActiveCamera(size_t)
		/// @param cameraID The ID of the new active camera.
		/// @returns True if the active camera was changed, false otherwise.
		///
		/* 34h */	virtual bool SetActiveCameraByID(uint32_t cameraID) = 0;

		///
		/// Returns the currently active camera, or nullptr if there is no active camera.
		///
		/* 38h */	virtual ICamera* GetActiveCamera() = 0;

		///
		/// Returns the ID mapped to the currently active camera, or 0 if there is no active camera.
		///
		/* 3Ch */	virtual uint32_t GetActiveCameraID() = 0;

		///
		/// Returns the ICamera mapped to the given ID, or nullptr if there is no camera mapped to that ID.
		/// @param cameraID The ID of the camera.
		///
		/* 40h */	virtual ICamera* GetCamera(uint32_t cameraID) = 0;

		///
		/// Returns the ID of the camera mapped to the given name, or 0 if there is no ID mapped to that name.
		/// @param pName A char c-eastl::string.
		///
		/* 44h */	virtual uint32_t GetCameraID(const char* pName) = 0;

		///
		/// Returns the number of cameras contained in this manager.
		///
		/* 48h */	virtual size_t GetCamerasCount() = 0;

		///
		/// Returns the ICamera at the given index, or nullptr if the index is not valid.
		/// @param nIndex
		///
		/* 4Ch */	virtual ICamera* GetCameraAt(int nIndex) = 0;

		///
		/// Returns the camera ID at the given index, or nullptr if the index is not valid.
		/// @param nIndex
		///
		/* 50h */	virtual uint32_t GetCameraIDAt(int nIndex) = 0;

		///
		/// Sets the active camera of this manager, which will be used to calculate all the view transformations used for rendering,
		/// and that will receive all the input events. ICamera::OnEnter() will be called on the new active camera, and
		/// ICamera::OnExit() will be caleld on the old active camera.
		/// @param nIndex The index of the new active camera.
		/// @returns True if the active camera changed, false otherwise.
		///
		///
		/* 54h */	virtual bool SetActiveCamera(int nIndex) = 0;

		///
		/// Returns the index of the currently active camera, or -1 if there is no active camera.
		///
		/* 58h */	virtual int GetActiveCameraIndex() = 0;

		///
		/// Removes all the cameras and their mappings from this manager.
		///
		/* 5Ch */	virtual void RemoveCameras() = 0;
	};

}
