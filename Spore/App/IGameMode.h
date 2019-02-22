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

// it contains useful enums for handling events
#include <Spore\UTFWin\Message.h>

namespace App
{
	class IGameModeManager;

	///
	/// An interface that represents a mode in the game, that can receive mouse/keyboard input and update every frame.
	/// There can be only an active game mode at a time; modes are managed using the IGameModeManager class.
	/// When a game mode is set as active, the OnEnter() method is called; when the mode is no longer active, 
	/// the OnExit() method will be called.
	///
	class IGameMode
	{
	public:
		///
		/// Increases the reference count and returns it. 
		///
		/* 00h */	virtual int AddRef() = 0;

		/// 
		/// Decreases the reference count and returns it.
		/// If the reference count reaches 0, 'delete this' is called.
		///
		/* 04h */	virtual int Release() = 0;

		/* 08h */	virtual ~IGameMode() {};

		/* 0Ch */	virtual bool func0Ch() = 0;

		///
		/// This method is called once on every game mode when all modes have been added.
		/// This should take care of all initializations and setups that are required.
		/// @param pManager The GameModeManager that has called this method.
		///
		/* 10h */	virtual bool Initialize(IGameModeManager* pManager) = 0;

		///
		/// This method is called once on every game mode when the game closes.
		/// This should reverse everything the Initialize method did.
		///
		/* 14h */	virtual bool Dispose() = 0;

		///
		/// This method is called when the game mode is set as active, and therefore, entered.
		///
		/* 18h */	virtual bool OnEnter() = 0;

		///
		/// This method is called when a different game mode is set as active, and therefore, this game mode is exited (no longer active).
		///
		/* 1Ch */	virtual void OnExit() = 0;

		/* 20h */	virtual void* func20h(int) = 0;

		///
		/// An event listener called every time a key is pressed while this mode is active.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values UTFWin::kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 24h */	virtual bool OnKeyDown(int virtualKey, int modifiers) = 0;

		///
		/// An event listener called every time a key is released while this mode is active.
		/// @param virtualKey The VK code of the key.
		/// @param modifiers The modifiers (Ctrl, Alt and Shift) currently being pressed. They use the enum values UTFWin::kModifier....
		/// @returns Whether the event was handled or not.
		///
		/* 28h */	virtual bool OnKeyUp(int virtualKey, int modifiers) = 0;

		///
		/// An event listener called every time a mouse key is pressed while this mode is active.
		/// @param mouseButton The button that was pressed, in the MouseButtons enum.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param flags The state of the mouse, flags in the MouseFlags enum.
		/// @returns Whether the event was handled or not.
		///
		/* 2Ch */	virtual bool OnMouseDown(int mouseButton, float mouseX, float mouseY, int flags) = 0;

		///
		/// An event listener called every time a mouse key is released while this mode is active.
		/// @param mouseButton The button that was pressed, in the MouseButtons enum.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param flags The state of the mouse, flags in the MouseFlags enum.
		/// @returns Whether the event was handled or not.
		///
		/* 30h */	virtual bool OnMouseUp(int mouseButton, float mouseX, float mouseY, int flags) = 0;

		///
		/// An event listener called every time the mouse is moved while this mode is active.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param state The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 34h */	virtual bool OnMouseMove(float mouseX, float mouseY, int state) = 0;

		///
		/// An event listener called every time the mouse wheel is moved while this mode is active.
		/// @param nWheelDelta The amount of units the wheel moved. This is a multiple of UTFWin::kMouseWheelDelta.
		/// @param fMouseX The X position of the mouse.
		/// @param fMouseY The Y position of the mouse.
		/// @param flags The state of the mouse, flags of the UTFWin::kMouse.... values.
		/// @returns Whether the event was handled or not.
		///
		/* 38h */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int flags) = 0;

		///
		/// An event listener called every game loop.
		/// @param fDelta1 The amount of seconds elapsed since this the last update.
		/// @param fDelta2 Usually the same as fDelta1.
		///
		/* 3Ch */	virtual void Update(float fDelta1, float fDelta2) = 0;
	};

	///
	/// Same as App::IGameMode, but this one includes a Cast method similar to the one in the Object class.
	///
	class IGameModeObject : public IGameMode
	{
	public:

		virtual void* Cast(uint32_t typeID) = 0;
	};
}