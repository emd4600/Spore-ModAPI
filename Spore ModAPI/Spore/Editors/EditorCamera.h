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

#pragma once

#include <Spore\App\ICamera.h>
#include <Spore\App\cViewer.h>
#include <Spore\App\PropertyList.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Input.h>

namespace Editors
{
	// I don't know if this class can be used, this is just for investigation
	class EditorCamera 
		: public App::ICamera
		, public App::IMessageListener
		, public IVirtual
	{
	public:
		EditorCamera(App::PropertyList* pPropList);
		virtual ~EditorCamera() {}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;
		virtual bool OnAttach(App::ICameraManager* pManager) override;
		virtual bool OnDeattach() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update(int nDeltaTime, App::cViewer* pViewer) override;
		virtual void func24h(bool) override;
		virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
		virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
		virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseStates) override;
		virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool func40h(int) override;
		virtual bool func44h(int) override;
		virtual bool func48h(int) override;
		virtual App::PropertyList* GetPropertyList() override;
		virtual void Initialize() override;  // here it parses the prop file
		virtual void func54h(Vector3& dst) override;

	protected:
		/* 0Ch */	int mnRefCount;
		/* 10h */	intrusive_ptr<App::PropertyList> mpPropList;
		/* 14h */	float mfZoomScale;  // 1.0
		/* 18h */	float mfTranslateScale;  // 1.0
		/* 1Ch */	float mfRotateScale;  // 1.0
		/* 20h */	float field_20;
		/* 24h */	float field_24;
		/* 28h */	float mfInitialZoom;  // 1.0
		/* 2Ch */	bool field_2C;
		/* 30h */	float field_30;  // cameraInitialHeading
		/* 34h */	float field_34;  // cameraInitialPitch
		/* 38h */	float mfZoom;  // 10.0  // cameraInitialZoom
		/* 3Ch */	float field_3C;  // cameraInitialOffsetX
		/* 40h */	float field_40;  // cameraInitialOffsetY
		/* 44h */	float field_44;  // cameraInitialHeading
		/* 48h */	float field_48;  // cameraInitialPitch
		/* 4Ch */	float field_4C;  // cameraInitialZoom
		/* 50h */	float field_50;  // cameraInitialOffsetX
		/* 54h */	float field_54;  // cameraInitialOffsetY
		/* 58h */	float mfMinZoomDistance;  // 5.0
		/* 5Ch */	float mfMaxZoomDistance;  // 25.0
		/* 60h */	float mfMinPitch;
		/* 64h */	float mfMaxPitch;
		/* 68h */	float mfNearClip;  // -1
		/* 6Ch */	float mfFarClip;  // -1
		/* 70h */	float mfInitialFOV;  // 57.29578
		/* 74h */	Vector3 field_74;
		/* 80h */	Vector3 field_80;
		/* 8Ch */	float field_8C;  // 1.0
		/* 90h */	bool mbEditorCameraTurntableStyle;
		/* 94h */	float field_94;
		/* 98h */	float field_98;
		/* 9Ch */	bool field_9C;
		/* A0h */	GameInput mInput;
		/* E8h */	App::cViewer* mpViewer;
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(EditorCamera) == 0xEC, "sizeof(EditorCamera) != 0xEC");

	namespace Addresses(EditorCamera)
	{
		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(Cast);
		DeclareAddress(OnAttach);
		DeclareAddress(OnDeattach);
		DeclareAddress(OnEnter);
		DeclareAddress(OnExit);
		DeclareAddress(Update);
		DeclareAddress(func24h);
		DeclareAddress(OnKeyDown);
		DeclareAddress(OnKeyUp);
		DeclareAddress(OnMouseDown);
		DeclareAddress(OnMouseUp);
		DeclareAddress(OnMouseMove);
		DeclareAddress(OnMouseWheel);
		DeclareAddress(func40h);
		DeclareAddress(func44h);
		DeclareAddress(func48h);
		DeclareAddress(GetPropertyList);
		DeclareAddress(Initialize);
		DeclareAddress(func54h);

	}
}