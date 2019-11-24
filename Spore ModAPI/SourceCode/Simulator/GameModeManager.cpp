#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\Simulator\SubSystem\GameModeManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cGameModeManager, cGameModeManager*, Get);

	uint32_t cGameModeManager::GetActiveModeID() {
		return mActiveModeID;
	}

	uint32_t GetGameModeID() {
		auto mgr = cGameModeManager::Get();
		return mgr == nullptr ? -1 : mgr->GetActiveModeID();
	}

	auto_METHOD_VOID(cGameModeManager, SubmitEditorRequest, Args(Editors::EditorRequest* pRequest), Args(pRequest));

	auto_METHOD(cGameModeManager, App::PropertyList*, GetDifficultyTuning,
		Args(uint32_t gameModeID, bool bUseCurrentDifficulty), Args(gameModeID, bUseCurrentDifficulty));

	auto_METHOD_(cGameModeManager, App::PropertyList*, GetActiveDifficultyTuning);
}
#endif
