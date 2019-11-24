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
#include <Spore\Simulator\SubSystem\PlanetModel.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cPlanetModel, cPlanetModel*, Get);

	auto_METHOD(cPlanetModel, bool, IsInWater, Args(const Vector3& position), Args(position));
	auto_METHOD(cPlanetModel, cCity*, GetNearestCity, Args(const Vector3& position), Args(position));
	auto_METHOD(cPlanetModel, Vector3, ToSurface, Args(const Vector3& position), Args(position));

	auto_METHOD(cPlanetModel, float, GetHeightAt, const Vector3& position, position);
	auto_METHOD_const_(cPlanetModel, float, GetGravity);
	
	RedirectMethod_structret_const(cPlanetModel, GetOrientation, Vector4,
		Args(const Vector3& position, const Vector3& direction), Args(position, direction));
}
#endif
