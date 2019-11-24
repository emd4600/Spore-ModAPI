#ifndef MODAPI_DLL_EXPORT
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

	auto_METHOD(cViewer, bool, Initialize, Args(bool arg_0), Args(arg_0));

	auto_METHOD(cViewer, bool, ClearScene, Args(int8_t flags), Args(flags));
	auto_METHOD_(cViewer, bool, LoadTransformations);

	auto_METHOD_VOID(cViewer, SetBackgroundColor, Args(const Math::ColorRGBA& color), Args(color));

	auto_METHOD_const_(cViewer, float, GetNearPlane);
	auto_METHOD_const_(cViewer, float, GetFarPlane);

	auto_METHOD_VOID(cViewer, SetNearPlane, Args(float value), Args(value));
	auto_METHOD_VOID(cViewer, SetFarPlane, Args(float value), Args(value));

	auto_METHOD_VOID(cViewer, SetAspectRatio, Args(float value), Args(value));

	auto_METHOD_VOID(cViewer, SetCameraMaterialLODs, Args(const Vector4& values), Args(values));
	auto_METHOD_const_(cViewer, Vector4, GetCameraMaterialLODs);

	auto_METHOD_VOID(cViewer, SetRenderType, Args(int arg_0, bool arg_4), Args(arg_0, arg_4));

	auto_METHOD_VOID(cViewer, SetViewTransform, Args(const Transform& transform), Args(transform));
	auto_METHOD_const_(cViewer, Transform, GetViewTransform);

	auto_METHOD_const(cViewer, bool, GetCameraToMouse, Args(Vector3& dst1, Vector3& dst2), Args(dst1, dst2));

	auto_METHOD_const(cViewer, bool, GetCameraToPoint, Args(float x, float y, Vector3& dst1, Vector3& dst2), Args(x, y, dst1, dst2));
}
#endif
