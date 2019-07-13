/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Simulator\Cell\GameModeCell.h>

namespace Simulator
{
	namespace Cell
	{
		using namespace App;

		GameModeCell::GameModeCell() {};
		GameModeCell::~GameModeCell() {};


		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, int, AddRef);
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, int, Release);
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, bool, func0Ch);
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, Initialize, Args(App::IGameModeManager* pManager), Args(pManager));
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, bool, Dispose);
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, bool, OnEnter);
		auto_METHOD_VIRTUAL_VOID_(GameModeCell, IGameMode, OnExit);
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, void*, func20h, Args(int arg_0), Args(arg_0));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnKeyDown, Args(int virtualKey, KeyModifiers modifiers), Args(virtualKey, modifiers));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnKeyUp, Args(int virtualKey, KeyModifiers modifiers), Args(virtualKey, modifiers));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseDown, Args(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState), Args(mouseButton, mouseX, mouseY, mouseState));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseUp, Args(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState), Args(mouseButton, mouseX, mouseY, mouseState));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseMove, Args(float mouseX, float mouseY, MouseState mouseState), Args(mouseX, mouseY, mouseState));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseWheel, Args(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState), Args(nWheelDelta, mouseX, mouseY, mouseState));
		auto_METHOD_VIRTUAL_VOID(GameModeCell, IGameMode, Update, Args(float fDelta1, float fDelta2), Args(fDelta1, fDelta2));
		auto_METHOD_VIRTUAL(GameModeCell, IUnmanagedMessageListener, bool, HandleMessage, Args(uint32_t messageID, void* pMessage), Args(messageID, pMessage));

	}
}