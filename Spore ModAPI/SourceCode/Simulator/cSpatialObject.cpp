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
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cLocomotiveObject.h>

namespace Simulator
{
	Vector3 cLocomotiveObject::GetVelocity()
	{
		return mVelocity;
	}
	void cLocomotiveObject::SetVelocity(const Vector3& velocity) {
		this->mVelocity = velocity;
	}

	Math::Quaternion cSpatialObject::GetOrientationYawTowards(const Vector3& targetpos)
	{
		Vector3 upVector = GetPosition().Normalized(); // Local up axis

		// Compute direction to the target
		Vector3 direction = (targetpos - GetPosition()).Normalized();

		// Project onto the X-Z plane (perpendicular to upVector)
		direction = (direction - upVector * direction.Dot(upVector)).Normalized();

		// Project forward vector onto the same X-Z plane
		Vector3 forward = (GetDirection() - upVector * GetDirection().Dot(upVector)).Normalized();

		// Compute the yaw rotation needed
		Quaternion yawRotation;
		yawRotation = yawRotation.GetRotationTo(forward, direction);

		// Apply the yaw rotation while maintaining the original pitch and roll
		return (yawRotation * GetOrientation());
	}
}
#endif
