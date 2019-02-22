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

#include <Spore\App\Viewer.h>

namespace App
{

	auto_METHOD(Viewer, bool, Initialize, PARAMS(bool arg_0), PARAMS(arg_0));

	auto_METHOD_VOID(Viewer, ClearScene, PARAMS(int8_t flags), PARAMS(flags));
	auto_METHOD_(Viewer, bool, LoadTransformations);

	auto_METHOD_VOID(Viewer, SetBackgroundColor, PARAMS(const Math::ColorRGBA& color), PARAMS(color));

	auto_METHOD_const_(Viewer, float, GetNearPlane);
	auto_METHOD_const_(Viewer, float, GetFarPlane);

	auto_METHOD_VOID(Viewer, SetNearPlane, PARAMS(float value), PARAMS(value));
	auto_METHOD_VOID(Viewer, SetFarPlane, PARAMS(float value), PARAMS(value));

	auto_METHOD_VOID(Viewer, SetAspectRatio, PARAMS(float value), PARAMS(value));

	auto_METHOD_VOID(Viewer, SetCameraMaterialLODs, PARAMS(const Math::Vector4& values), PARAMS(values));

	auto_METHOD_VOID(Viewer, SetRenderType, PARAMS(int arg_0, bool arg_4), PARAMS(arg_0, arg_4));

	auto_METHOD_VOID(Viewer, SetViewTransform, PARAMS(const Transform& transform), PARAMS(transform));

	auto_METHOD(Viewer, bool, GetCameraToMouse, PARAMS(Vector3& dst1, Vector3& dst2), PARAMS(dst1, dst2));

	auto_METHOD(Viewer, bool, GetCameraToPoint, PARAMS(float x, float y, Vector3& dst1, Vector3& dst2), PARAMS(x, y, dst1, dst2));
}