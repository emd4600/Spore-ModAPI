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

#include <Spore\App\cViewer.h>

namespace App
{

	auto_METHOD(cViewer, bool, Initialize, PARAMS(bool arg_0), PARAMS(arg_0));

	auto_METHOD(cViewer, bool, ClearScene, PARAMS(int8_t flags), PARAMS(flags));
	auto_METHOD_(cViewer, bool, LoadTransformations);

	auto_METHOD_VOID(cViewer, SetBackgroundColor, PARAMS(const Math::ColorRGBA& color), PARAMS(color));

	auto_METHOD_const_(cViewer, float, GetNearPlane);
	auto_METHOD_const_(cViewer, float, GetFarPlane);

	auto_METHOD_VOID(cViewer, SetNearPlane, PARAMS(float value), PARAMS(value));
	auto_METHOD_VOID(cViewer, SetFarPlane, PARAMS(float value), PARAMS(value));

	auto_METHOD_VOID(cViewer, SetAspectRatio, PARAMS(float value), PARAMS(value));

	auto_METHOD_VOID(cViewer, SetCameraMaterialLODs, PARAMS(const Vector4& values), PARAMS(values));
	auto_METHOD_const_(cViewer, Vector4, GetCameraMaterialLODs);

	auto_METHOD_VOID(cViewer, SetRenderType, PARAMS(int arg_0, bool arg_4), PARAMS(arg_0, arg_4));

	auto_METHOD_VOID(cViewer, SetViewTransform, PARAMS(const Transform& transform), PARAMS(transform));
	auto_METHOD_const_(cViewer, Transform, GetViewTransform);

	auto_METHOD_const(cViewer, bool, GetCameraToMouse, PARAMS(Vector3& dst1, Vector3& dst2), PARAMS(dst1, dst2));

	auto_METHOD_const(cViewer, bool, GetCameraToPoint, PARAMS(float x, float y, Vector3& dst1, Vector3& dst2), PARAMS(x, y, dst1, dst2));
}