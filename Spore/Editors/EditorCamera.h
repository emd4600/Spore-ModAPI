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
#include <Spore\App\Viewer.h>
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
		virtual void Update(int nDeltaTime, App::Viewer* pViewer) override;
		virtual void func24h(bool) override;
		virtual bool OnKeyDown(int virtualKey, int modifiers) override;
		virtual bool OnKeyUp(int virtualKey, int modifiers) override;
		virtual bool OnMouseDown(int mouseState, float mouseX, float mouseY, int flags) override;
		virtual bool OnMouseUp(int mouseState, float mouseX, float mouseY, int flags) override;
		virtual bool OnMouseMove(float mouseX, float mouseY, int state) override;
		virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state) override;
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
		/* E8h */	App::Viewer* mpViewer;
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(EditorCamera) == 0xEC, "sizeof(EditorCamera) != 0xEC");

	namespace InternalAddressList(EditorCamera)
	{
		DefineAddress(AddRef, GetAddress(0xCF91C0, 0x671F20, 0x671F20));
		DefineAddress(Release, GetAddress(0xD57BB0, 0xAE05F0, 0xAE0620));
		DefineAddress(Cast, GetAddress(0x7C6A50, 0x5A2030, 0x5A2030));
		DefineAddress(OnAttach, GetAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(OnDeattach, GetAddress(0x66AD60, 0xB1E3E0, 0xB1E410));
		DefineAddress(OnEnter, GetAddress(0x5A2040, 0x5A22F0, 0x5A22F0));
		DefineAddress(OnExit, GetAddress(0x7E66D0, 0xC2E620, 0xC2E640));
		DefineAddress(Update, GetAddress(0x5A3B40, 0x5A3E00, 0x5A3E00));
		DefineAddress(func24h, GetAddress(0x5A1D90, 0x5A2050, 0x5A2050));
		DefineAddress(OnKeyDown, GetAddress(0x5A1DA0, 0x5A2060, 0x5A2060));
		DefineAddress(OnKeyUp, GetAddress(0x5A1E40, 0x5A2100, 0x5A2100));
		DefineAddress(OnMouseDown, GetAddress(0x5A2C50, 0x5A2F00, 0x5A2F00));
		DefineAddress(OnMouseUp, GetAddress(0x5A1EE0, 0x5A21A0, 0x5A21A0));
		DefineAddress(OnMouseMove, GetAddress(0x5A2CB0, 0x5A2F70, 0x5A2F70));
		DefineAddress(OnMouseWheel, GetAddress(0x5A22B0, 0x5A2560, 0x5A2560));
		DefineAddress(func40h, GetAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(func44h, GetAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(func48h, GetAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(GetPropertyList, GetAddress(0x6BD860, 0x7F5550, 0x7F55C0));
		DefineAddress(Initialize, GetAddress(0x5A2330, 0x5A25E0, 0x5A25E0));
		DefineAddress(func54h, GetAddress(0x5A2070, 0x5A2320, 0x5A2320));

	}
}