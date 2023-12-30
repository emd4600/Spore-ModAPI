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
#include <Spore\Simulator\cCity.h>

namespace Simulator
{
	auto_METHOD(cCity, bool, IsAboveCity, Args(const Vector3& position), Args(position));

	Vector3 cCity::GetWallsPosition() {
		return mpCityWalls->GetPosition();
	}

	auto_METHOD(cCity, cVehicle*, SpawnVehicle, 
		Args(VehiclePurpose speciality, VehicleLocomotion locomotion, struct ResourceKey key, bool isSpaceStage),
		Args(speciality, locomotion, key, isSpaceStage));


	auto_METHOD_VOID(cCity, AddBuilding, Args(cBuilding* a0, bool a1), Args(a0, a1));
	auto_METHOD(cCity, bool, RemoveBuilding, Args(cBuilding* a0), Args(a0));

	auto_STATIC_METHOD_VOID(cCity, ProcessBuildingUpdate, Args(cCity* a0, int a1, int a2), Args(a0, a1, a2));



	auto_METHOD_VOID(cCommunityLayout, SetParameters, Args(const Math::Vector3& a0, float a1, const Math::Vector3& a2, float a3), Args(a0, a1, a2, a3));

	auto_METHOD_VOID(cCommunityLayout, InitializeSlots, Args(const eastl::vector<Math::Vector3>& a0, float a1), Args(a0, a1));

	auto_METHOD_VOID_(cCommunityLayout, SnapSlotsToPlanet);


	auto_METHOD_VOID(cLayoutSlot, SetObject, Args(cGameData* obj), Args(obj));
	auto_METHOD_VOID(cLayoutSlot, RemoveObject, Args(cGameData* obj), Args(obj));
}
#endif
