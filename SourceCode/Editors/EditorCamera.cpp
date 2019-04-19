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
#include <Spore\Editors\EditorCamera.h>

namespace Editors
{
	EditorCamera::EditorCamera(App::PropertyList* pPropList)
		: mnRefCount(0)
		, mpPropList(pPropList)
		, mfZoomScale(1.0f)
		, mfTranslateScale(1.0f)
		, mfRotateScale(1.0f)
		, field_20()
		, field_24()
		, mfInitialZoom(1.0f)
		, field_2C()
		, field_30()
		, field_34()
		, mfZoom(10.0f)
		, field_3C()
		, field_40()
		, field_44()
		, field_48()
		, field_4C()
		, field_50()
		, field_54()
		, mfMinZoomDistance(5.0f)
		, mfMaxZoomDistance(25.0f)
		, mfMinPitch()
		, mfMaxPitch()
		, mfNearClip(-1.0f)
		, mfFarClip(-1.0f)
		, mfInitialFOV(57.29578f)
		, field_74()
		, field_80()
		, field_8C(1.0f)
		, mbEditorCameraTurntableStyle()
		, field_94()
		, field_98()
		, field_9C()
		, mInput()
		, mpViewer(nullptr)
	{
	}

	auto_METHOD_VIRTUAL_(EditorCamera, EditorCamera, int, AddRef);
	auto_METHOD_VIRTUAL_(EditorCamera, EditorCamera, int, Release);
	auto_METHOD_VIRTUAL_const(EditorCamera, EditorCamera, void*, Cast, PARAMS(uint32_t type), PARAMS(type));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnAttach, PARAMS(App::ICameraManager* pManager), PARAMS(pManager));
	auto_METHOD_VIRTUAL_(EditorCamera, EditorCamera, bool, OnDeattach);
	auto_METHOD_VIRTUAL_VOID_(EditorCamera, EditorCamera, OnEnter);
	auto_METHOD_VIRTUAL_VOID_(EditorCamera, EditorCamera, OnExit);
	auto_METHOD_VIRTUAL_VOID(EditorCamera, EditorCamera, Update, PARAMS(int nDeltaTime, App::cViewer* pViewer), PARAMS(nDeltaTime, pViewer));
	auto_METHOD_VIRTUAL_VOID(EditorCamera, EditorCamera, func24h, PARAMS(bool arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnKeyDown, PARAMS(int virtualKey, int modifiers), PARAMS(virtualKey, modifiers));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnKeyUp, PARAMS(int virtualKey, int modifiers), PARAMS(virtualKey, modifiers));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnMouseDown, PARAMS(int mouseState, float mouseX, float mouseY, int flags), PARAMS(mouseState, mouseX, mouseY, flags));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnMouseUp, PARAMS(int mouseState, float mouseX, float mouseY, int flags), PARAMS(mouseState, mouseX, mouseY, flags));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnMouseMove, PARAMS(float mouseX, float mouseY, int state), PARAMS(mouseX, mouseY, state));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, OnMouseWheel, PARAMS(int nWheelDelta, float mouseX, float mouseY, int state), PARAMS(nWheelDelta, mouseX, mouseY, state));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, func40h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, func44h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(EditorCamera, EditorCamera, bool, func48h, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_(EditorCamera, EditorCamera, App::PropertyList*, GetPropertyList);
	auto_METHOD_VIRTUAL_VOID_(EditorCamera, EditorCamera, Initialize);
	auto_METHOD_VIRTUAL_VOID(EditorCamera, EditorCamera, func54h, PARAMS(Vector3& dst), PARAMS(dst));
}