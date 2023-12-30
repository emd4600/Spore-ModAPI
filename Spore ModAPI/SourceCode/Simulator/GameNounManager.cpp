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

#include <Spore\Simulator\SubSystem\GameNounManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cGameNounManager, cGameNounManager*, Get);

	auto_METHOD(cGameNounManager, cGameData*, CreateInstance, Args(uint32_t nounID), Args(nounID));
	auto_METHOD_VOID(cGameNounManager, DestroyInstance, Args(cGameData* p), Args(p));

	auto_METHOD_VOID_(cGameNounManager, UpdateModels);

	auto_METHOD_VOID(cGameNounManager, SetAvatar, Args(cCreatureAnimal* pAnimal), Args(pAnimal));

	cCreatureAnimal* cGameNounManager::GetAvatar() {
		return mpAvatar.get();
	}

	cTribe* cGameNounManager::GetPlayerTribe() {
		return mpPlayerTribe.get();
	}

	auto_METHOD_(cGameNounManager, cCivilization*, GetPlayerCivilization);
}
#endif
