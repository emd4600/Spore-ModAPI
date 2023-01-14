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
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>

#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>
#include <Spore\Simulator\SubSystem\GameViewManager.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\ModAPI.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cSimulatorSystem, cSimulatorSystem*, Get);

	bool cSimulatorSystem::AddStrategy(ISimulatorStrategy* strategy, uint32_t id) {
		if (!ModAPI::AddSimulatorStrategy(strategy, id)) return false;
		mSubSystems.push_back(strategy);
		strategy->Initialize();
		return true;
	}

	void InitializeWithoutPlanet() {
		cStarRecord* pRecord = StarManager.GetStarRecord(0);
		pRecord->mEmpireID = StarManager.NextPoliticalID(true);
		SpacePlayerData::Get()->mPlayerEmpireID = pRecord->mEmpireID;
		SpacePlayerData::Get()->mpPlayerEmpire = StarManager.GetEmpireForStar(pRecord);

		cPlanetPtr planet;
		StarManager.RecordToPlanet(pRecord->GetPlanetRecord(0), planet);
		SpacePlayerData::Get()->mpActivePlanet = planet.get();

		GameViewManager.PrepareSimulator();
	}

	/// cStrategy ///

	cStrategy::cStrategy()
		: mnRefCount(0)
		, mLastGameMode(0xFFFFFFFF)
		, mCurrentGameMode(0xFFFFFFFF)
		, field_14(0xFFFFFFFF)
		, field_18(0)
	{}
	cStrategy::~cStrategy() {}

	int cStrategy::AddRef() {
		return ++mnRefCount;
	}

	int cStrategy::Release() {
		if (--mnRefCount == 0) {
			delete this;
			return 0;
		}
		else return mnRefCount;
	}

	void cStrategy::OnModeExited(uint32_t previousModeID, uint32_t newModeID) {
		if (newModeID != GetLastGameMode()) {
			func40h(newModeID);
			func48h();
		}
	}
	void cStrategy::OnModeEntered(uint32_t previousModeID, uint32_t newModeID) {
		if (newModeID != GetCurrentGameMode()) {
			func44h(newModeID);
			func4Ch();
		}
	}
	uint32_t cStrategy::GetLastGameMode() const {
		return mLastGameMode;
	}
	uint32_t cStrategy::GetCurrentGameMode() const {
		return mCurrentGameMode;
	}
	bool cStrategy::func24h(uint32_t mode) {
		return mode == GetCurrentGameMode() && mode == GetLastGameMode() && field_14 == 0xFFFFFFFF;
	}

	void cStrategy::OnLoad(const cSavedGameHeader& savedGame) {}

	void cStrategy::Update(int deltaTime, int deltaGameTime) {}
	void cStrategy::PostUpdate(int deltaTime, int deltaGameTime) {}

	void cStrategy::func40h(uint32_t mode) {
		field_18 = 1;
		if (field_14 == 0xFFFFFFFF) field_14 = mode;
	}
	void cStrategy::func44h(uint32_t mode) {
		field_18 = 2;
		if (field_14 == 0xFFFFFFFF) field_14 = mode;
	}
	void cStrategy::func48h() {
		mLastGameMode = field_14;
		field_14 = 0xFFFFFFFF;
		field_18 = 0;
	}
	void cStrategy::func4Ch() {
		mCurrentGameMode = field_14;
		field_14 = 0xFFFFFFFF;
		field_18 = 0;
	}
}
#endif
