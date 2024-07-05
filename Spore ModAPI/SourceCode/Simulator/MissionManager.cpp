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
#include <Spore\Simulator\cMissionManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cMissionManager, cMissionManager*, Get);

	auto_METHOD(cMissionManager, cMission*, CreateMission,
		Args(uint32_t missionID, cPlanetRecord* pSourcePlanetRecord, cEmpire* pOwnerEmpire, cMission* pParentMission),
		Args(missionID, pSourcePlanetRecord, pOwnerEmpire, pParentMission));

	auto_METHOD(cMissionManager, cMission*, ChooseMission,
		Args(cEmpire* pEmpire, cPlanetRecord* pPlanetRecord),
		Args(pEmpire, pPlanetRecord));

	auto_METHOD(cMissionManager, bool, HasMissionsAvailable,
		Args(cEmpire* pEmpire, cPlanetRecord* pPlanetRecord),
		Args(pEmpire, pPlanetRecord));

	auto_METHOD(cMissionManager, cMission*, GetMissionByID,
		Args(uint32_t missionID),
		Args(missionID));

	auto_METHOD(cMissionManager, bool, GetMissionTrackColor,
		Args(cMission* pMission, Color& dst),
		Args(pMission, dst));

	auto_METHOD(cMissionManager, bool, ThereIsEventInPlanet,
		Args(cPlanetRecord* pPlanetRecord),
		Args(pPlanetRecord));

	auto_METHOD_VOID(cMission, SetState,
		Args(MissionState state),
		Args(state));

}
#endif