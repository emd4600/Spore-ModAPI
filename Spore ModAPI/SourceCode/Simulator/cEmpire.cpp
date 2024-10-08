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
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\SubSystem\StarManager.h>

namespace Simulator
{
	auto_STATIC_METHOD(Simulator, uint32_t, GetArchetypeRelationshipsID,
		Args(int archetype, int difficulty), Args(archetype, difficulty));

	auto_STATIC_METHOD_VOID(cEmpire, CaptureSystem, Args(cStarRecord* pStarRecord, uint32_t empireID), Args(pStarRecord, empireID));

	auto_METHOD_VOID(cEmpire, AddStarOwnership, Args(cStarRecord* pStarRecord), Args(pStarRecord));

	auto_METHOD_(cEmpire, cSpeciesProfile*, GetSpeciesProfile);
	auto_METHOD_VOID(cEmpire, SetSpeciesProfile, Args(cSpeciesProfile* pSpecies), Args(pSpecies));

	auto_METHOD_(cEmpire, cPlanetRecord*, RequireHomePlanet);

	cStarRecord* cEmpire::GetHomeStarRecord() {
		if (mHomeStar.internalValue != -1) {
			return StarManager.GetStarRecord(mHomeStar);
		}
		else {
			return nullptr;
		}
	}

	Math::ColorRGB cEmpire::UpdateAndGetColor() {
		Math::ColorRGB dst;
		CALL(GetAddress(cEmpire, UpdateAndGetColor), void, Args(cEmpire*, Math::ColorRGB&), Args(this, dst));
		return dst;
	}
}
#endif
