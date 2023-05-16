#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\App\cCellModeStrategy.h>
#include <Spore\Simulator\Cell\cCellGame.h>
#include <Spore\Simulator\Cell\cCellUI.h>
#include <Spore\Simulator\Cell\cCellGFX.h>

namespace App
{
	auto_METHOD_VIRTUAL_(cCellModeStrategy, IGameMode, int, AddRef);
	auto_METHOD_VIRTUAL_(cCellModeStrategy, IGameMode, int, Release);
	auto_METHOD_VIRTUAL_(cCellModeStrategy, IGameMode, bool, func0Ch);
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, Initialize, Args(App::IGameModeManager* pManager), Args(pManager));
	auto_METHOD_VIRTUAL_(cCellModeStrategy, IGameMode, bool, Dispose);
	auto_METHOD_VIRTUAL_(cCellModeStrategy, IGameMode, bool, OnEnter);
	auto_METHOD_VIRTUAL_VOID_(cCellModeStrategy, IGameMode, OnExit);
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, void*, func20h, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnKeyDown, Args(int virtualKey, KeyModifiers modifiers), Args(virtualKey, modifiers));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnKeyUp, Args(int virtualKey, KeyModifiers modifiers), Args(virtualKey, modifiers));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnMouseDown, Args(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState), Args(mouseButton, mouseX, mouseY, mouseState));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnMouseUp, Args(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState), Args(mouseButton, mouseX, mouseY, mouseState));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnMouseMove, Args(float mouseX, float mouseY, MouseState mouseState), Args(mouseX, mouseY, mouseState));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IGameMode, bool, OnMouseWheel, Args(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState), Args(nWheelDelta, mouseX, mouseY, mouseState));
	auto_METHOD_VIRTUAL_VOID(cCellModeStrategy, IGameMode, Update, Args(float fDelta1, float fDelta2), Args(fDelta1, fDelta2));
	auto_METHOD_VIRTUAL(cCellModeStrategy, IUnmanagedMessageListener, bool, HandleMessage, Args(uint32_t messageID, void* pMessage), Args(messageID, pMessage));
}

namespace Simulator
{
	namespace Cell
	{
		GoalCard* GetGoalCards() {
			return (GoalCard*)GetAddress(Cell, GoalCards_ptr);
		}

		cCellSerializableData* cCellSerializableData::Get()
		{
			return *(cCellSerializableData**)GetAddress(cCellSerializableData, _ptr);
		}
		cCellGFX* cCellGFX::Get()
		{
			return *(cCellGFX**)GetAddress(cCellGFX, _ptr);
		}
		cCellUI* cCellUI::Get()
		{
			return *(cCellUI**)GetAddress(cCellUI, _ptr);
		}
		cCellGame* cCellGame::Get()
		{
			return *(cCellGame**)GetAddress(cCellGame, _ptr);
		}
	}
}
#endif
