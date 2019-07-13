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
#include <Spore\Simulator\SubSystem\TerraformingManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cTerraformingManager, cTerraformingManager*, Get);

	auto_METHOD(cTerraformingManager, int, CalculateTScore,
		Args(float atmosphereScore, float temperatureScore), Args(atmosphereScore, temperatureScore));

	auto_METHOD(cTerraformingManager, int, GetTScore, Args(const cPlanetRecord* pPlanet), Args(pPlanet));
}