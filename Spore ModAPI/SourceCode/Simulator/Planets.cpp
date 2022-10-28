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
#include <Spore\Simulator\cPlanetRecord.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\SubSystem\StarManager.h>

namespace Simulator
{
	cStarRecord* cPlanetRecord::GetStarRecord() const {
		return StarManager.GetStarRecord(mKey.GetStarID());
	}

	StarID cPlanetRecord::GetStarID() const {
		return PlanetID(mKey).GetStarID();
	}

	PlanetID cPlanetRecord::GetID() const {
		return mKey;
	}

	TechLevel cPlanetRecord::GetTechLevel() const {
		return mTechLevel;
	}


	auto_METHOD_const_(cPlanet, float, GetTemperatureScore);

	cEmpire* cPlanet::GetEmpire() {
		if (mpPlanetRecord && mpPlanetRecord->GetTechLevel() == TechLevel::Empire) {
			return StarManager.GetEmpire(GetPoliticalID());
		}
		return nullptr;
	}

	auto_METHOD_VOID(cPlanet, SetRepresentationMode, Args(PlanetRepresentationMode mode), Args(mode));

	auto_STATIC_METHOD_VOID(cPlanetRecord, Create, Args(PlanetID planetId, cPlanetRecordPtr& dst), Args(planetId, dst));

	auto_STATIC_METHOD(cPlanetRecord, float, GetPerihelion,
		Args(cPlanetRecord* pRecord, MoonPerihelionType moonType), Args(pRecord, moonType));

	auto_METHOD(cPlanet, uint32_t, GetRingEffect, Args(bool isFromPlanet), Args(isFromPlanet));
}
#endif
