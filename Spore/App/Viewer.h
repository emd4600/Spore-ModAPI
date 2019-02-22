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

#include <Spore\MathUtils.h>
#include <Spore\Transform.h>

using namespace Math;

namespace App
{
	//class ViewProperties
	//{
	//public:
	//	/* 00h */	Matrix4 field_0;

	//	/* 64h */	float scaleX;
	//	/* 68h */	float scaleY;
	//	/* 6Ch */	int field_6C;
	//	/* 70h */	float nearPlane;
	//	/* 74h */	float farPlane;
	//	/* 78h */	D3DVIEWPORT9 viewport;
	//};

	class Viewer
	{
	public:
		bool Initialize(bool);

		void ClearScene(int8_t flags);
		bool LoadTransformations();

		void SetBackgroundColor(const Math::ColorRGBA& color);

		float GetNearPlane() const;
		float GetFarPlane() const;

		void SetNearPlane(float fValue);
		void SetFarPlane(float fValue);

		void SetAspectRatio(float fValue);

		void SetCameraMaterialLODs(const Math::Vector4& values);

		void SetRenderType(int renderType, bool = 0);

		void SetViewTransform(const Transform& transform);

		// mouseDirection is a normalized vector
		bool GetCameraToMouse(Vector3& cameraPosition, Vector3& mouseDirection);

		bool GetCameraToPoint(float x, float y, Vector3& cameraPosition, Vector3& direction);

	protected:
		/* 00h */	Matrix4 field_00;
		/* 40h */	Matrix4 field_40;
		/* 80h */	Matrix4 field_80;
		/* C0h */	Matrix4 field_C0;
		/* 100h */	Matrix4 field_100;
		/* 140h */	ColorRGBA backgroundColor;
		/* 150h */	int renderType;  // 0xF -> hologram!
		/* 154h */	bool field_154;  // related to renderType, a char/bool?
		/* 158h */	int field_158;  // this points to a structure made of field_154 and renderType, it's used in shader const 0x201 (used when selecting shaders)
		/* 15Ch */	float cameraMaterialLODs[4];
		/* 16Ch */	bool field_16C;
		// /* 170h */	ViewProperties* viewProperties;
	};

	namespace InternalAddressList(Viewer)
	{
		DefineAddress(SetViewTransform, GetAddress(0x7C53A0, 0x7C4D70, 0x7C4DD0));
		DefineAddress(Initialize, GetAddress(0x7C5470, 0x7C4E40, 0x7C4EA0));
		DefineAddress(ClearScene, GetAddress(0x7C42F0, 0x7C3CC0, 0x7C3D20));
		DefineAddress(LoadTransformations, GetAddress(0x7C5650, 0x7C5020, 0x7C5080));
		DefineAddress(SetBackgroundColor, GetAddress(0x7C42C0, 0x7C3C90, 0x7C3CF0));
		DefineAddress(GetNearPlane, GetAddress(0x7C4330, 0x7C3D00, 0x7C3D60));
		DefineAddress(GetFarPlane, GetAddress(0x7C4340, 0x7C3D10, 0x7C3D70));
		DefineAddress(SetNearPlane, GetAddress(0x7C5240, 0x7C4C10, 0x7C4C70));
		DefineAddress(SetFarPlane, GetAddress(0x7C5260, 0x7C4C30, 0x7C4C90));
		DefineAddress(SetAspectRatio, GetAddress(0x7C51F0, 0x7C4BC0, 0x7C4C20));
		DefineAddress(SetCameraMaterialLODs, GetAddress(0x7C43A0, 0x7C3D70, 0x7C3DD0));
		DefineAddress(SetRenderType, GetAddress(0x7C4380, 0x7C3D50, 0x7C3DB0));
		DefineAddress(GetCameraToMouse, GetAddress(0x7C4FA0, 0x7C4970, 0x7C49D0));
		DefineAddress(GetCameraToPoint, GetAddress(0x7C4FA0, 0x7C47A0, 0x7C4800));
	}
}