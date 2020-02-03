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
#include <Spore\App\cViewer.h>
#include <Spore\Input.h>

#define ICameraPtr intrusive_ptr<App::ICamera>

namespace App
{
	class ICameraManager;

	///
	/// This class represents a camera in the game, capable of setting the view transformations used for rendering and receiving input events.
	/// The active camera receives user input (mouse and keyboard) before the active game mode. Every game loop, The ICamera::Update() method
	/// is called on the active camera passing the active Viewer as the parameter, where the view transformations must be set. 
	/// To have multiple cameras apart from the active one, the input events and update methods can be called manually.
	///
	/// The class DefaultCamera provides default implementations for most methods in an ICamera, allowing you to create one without much trouble.
	///
	class ICamera 
		: public Object
	{
	public:

		static const uint32_t TYPE = 0x29DA727;

		///
		/// Event called when the camera is added to the camera manager.
		///
		/* 10h */	virtual bool OnAttach(ICameraManager* pManager) = 0;
		
		///
		/// Event called when the camera is no longer in the camera manager.
		///
		/* 14h */	virtual bool OnDeattach() = 0;

		///
		/// Event called when the camera is set as the active camera.
		///
		/* 18h */	virtual void OnEnter() = 0;

		///
		/// Event called when the camera is no longer the active camera.
		///
		/* 1Ch */	virtual void OnExit() = 0;

		///
		/// Event called every game loop, which should set all the transformations of the camera into the given Viewer.
		/// @param deltaTime The time ellapsed since the last call, in milliseconds.
		/// @param pViewer The Viewer instance where the transformations must be set.
		///
		/* 20h */	virtual void Update(int deltaTime, cViewer* pViewer) = 0;

		// some sort of input reset?
		/* 24h */	virtual void func24h(bool) = 0;
		
		///
		/// An event listener called every time a key is pressed while this camera is active.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed.
		/// @returns Whether the event was handled or not.
		///
		/* 28h */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) = 0;

		///
		/// An event listener called every time a key is released while this camera is active.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed.
		/// @returns Whether the event was handled or not.
		///
		/* 2Ch */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers) = 0;

		///
		/// An event listener called every time a mouse key is pressed while this camera is active.
		/// @param mouseButton The button that was pressed.
		/// @param mouseX The X position of the mouse.
		/// @param mouseY The Y position of the mouse.
		/// @param mouseState The state of the mouse.
		/// @returns Whether the event was handled or not.
		///
		/* 30h */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) = 0;

		///
		/// An event listener called every time a mouse key is released while this camera is active.
		/// @param mouseButton The button that was released.
		/// @param mouseX The X position of the mouse.
		/// @param mouseY The Y position of the mouse.
		/// @param mouseState The state of the mouse.
		/// @returns Whether the event was handled or not.
		///
		/* 34h */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) = 0;

		///
		/// An event listener called every time the mouse is moved while this camera is active.
		/// @param mouseX The X position of the mouse.
		/// @param mouseY The Y position of the mouse.
		/// @param mouseState The state of the mouse.
		/// @returns Whether the event was handled or not.
		///
		/* 38h */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) = 0;

		///
		/// An event listener called every time the mouse wheel is moved while this camera is active.
		/// @param wheelDelta The amount of units the wheel moved. This is a multiple of UTFWin::kMouseWheelDelta.
		/// @param mouseX The X position of the mouse.
		/// @param mouseY The Y position of the mouse.
		/// @param mouseState The state of the mouse.
		/// @returns Whether the event was handled or not.
		///
		/* 3Ch */	virtual bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) = 0;

		/* 40h */	virtual bool func40h(int) = 0;
		/* 44h */	virtual bool func44h(int) = 0;
		/* 48h */	virtual bool func48h(int) = 0;

		///
		/// Gets the property list from which this camera was generated.
		///
		/* 4Ch */	virtual PropertyList* GetPropertyList() = 0;
		/* 50h */	virtual void Initialize() = 0;  // here it parses the prop file
		/* 54h */	virtual void func54h(Vector3& dst) = 0;
	};
}