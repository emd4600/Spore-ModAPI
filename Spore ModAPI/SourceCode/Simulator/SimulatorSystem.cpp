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
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>

#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>
#include <Spore\Simulator\SubSystem\GameViewManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cSimulatorSystem, cSimulatorSystem*, Get);

	void InitializeWithoutPlanet() {
		cStarRecord* pRecord = StarManager()->GetStarRecord(0);
		pRecord->mEmpireID = StarManager()->NextPoliticalID(true);
		SpacePlayerData::Get()->mPlayerEmpireID = pRecord->mEmpireID;
		SpacePlayerData::Get()->mpPlayerEmpire = StarManager()->GetEmpireForStar(pRecord);

		intrusive_ptr<cPlanet> planet;
		StarManager()->RecordToPlanet(pRecord->GetPlanetRecord(0), planet);
		SpacePlayerData::Get()->mpActivePlanet = planet.get();

		GameViewManager()->PrepareSimulator();
	}
}