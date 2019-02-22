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
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, Initialize, PARAMS(App::IGameModeManager* pManager), PARAMS(pManager));
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, bool, Dispose);
		auto_METHOD_VIRTUAL_(GameModeCell, IGameMode, bool, OnEnter);
		auto_METHOD_VIRTUAL_VOID_(GameModeCell, IGameMode, OnExit);
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, void*, func20h, PARAMS(int arg_0), PARAMS(arg_0));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnKeyDown, PARAMS(int virtualKey, int modifiers), PARAMS(virtualKey, modifiers));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnKeyUp, PARAMS(int virtualKey, int modifiers), PARAMS(virtualKey, modifiers));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseDown, PARAMS(int mouseState, float mouseX, float mouseY, int flags), PARAMS(mouseState, mouseX, mouseY, flags));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseUp, PARAMS(int mouseState, float mouseX, float mouseY, int flags), PARAMS(mouseState, mouseX, mouseY, flags));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseMove, PARAMS(float mouseX, float mouseY, int state), PARAMS(mouseX, mouseY, state));
		auto_METHOD_VIRTUAL(GameModeCell, IGameMode, bool, OnMouseWheel, PARAMS(int nWheelDelta, float mouseX, float mouseY, int state), PARAMS(nWheelDelta, mouseX, mouseY, state));
		auto_METHOD_VIRTUAL_VOID(GameModeCell, IGameMode, Update, PARAMS(float fDelta1, float fDelta2), PARAMS(fDelta1, fDelta2));
		auto_METHOD_VIRTUAL(GameModeCell, IUnmanagedMessageListener, bool, HandleMessage, PARAMS(uint32_t messageID, void* pMessage), PARAMS(messageID, pMessage));

	}
}