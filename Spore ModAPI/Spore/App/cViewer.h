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
#include <Spore\Graphics\IRenderTargetManager.h>
#include <d3d9types.h>

using namespace Math;

namespace App
{
	/// This class represents all the camera and viewport configuration used to render a scene.
	/// This includes the FOV, projection matrix, view matrix (i.e. camera orientation and position),
	/// as well as the color and depth buffers where the scene will be rendered into.
	/// It also has the "renderType" variable, a specific thing to Spore, which is used in shader 
	/// selection.
	class cViewer
	{
	public:
		struct Camera;

		bool Initialize(bool isParallelProjection = false);

		void Dispose();

		///
		/// Clears one or more surfaces such as the render target, the depth buffer or the stencil buffer.
		/// This calls the IDirect3DDevice9::Clear() method using this Viewer background color.
		/// It will also call IDirect3DDevice9::SetViewport() if the current viewport is not that from the viewer.
		/// @param flags A combination of flags in the D3DCLEAR enum.
		/// @returns true If the operation was carried out successfully.
		bool ClearScene(int8_t flags);

		/// Call before rendering, loads all the viewer data into the renderer system;
		/// must be paired with a EndUpdate() call
		/// @returns
		bool BeginUpdate();

		/// Call after finished rendering, has to be paired with a BeginUpdate() call
		/// @returns
		bool EndUpdate();

		///
		/// Sets the background color that is shown in the background of the scene.
		/// More exactly, this is the color used to clear the scene.
		/// @param color
		void SetBackgroundColor(const Math::ColorRGBA& color);

		float GetNearPlane() const;
		float GetFarPlane() const;

		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		void SetAspectRatio(float aspectRatio);

		void SetPerspectiveProjection(float fovDegrees);
		void SetParallelProjection(float viewWindowX, float viewWindowY);
		void SetViewport(const IntRectangle& viewport);
		void SetViewWindow(const Vector2& window);
		void SetViewOffset(const Vector2& offset);

		void SetCameraMaterialLODs(const Vector4& values);
		Vector4 GetCameraMaterialLODs() const;

		void SetRenderType(int renderType, bool = 0);

		/// Sets the target raster where the scene will be painted.
		/// @param raster
		void SetTargetRaster(RenderWare::Raster* raster);  //TODO

		/// Sets the target raster where the scene depth buffer will be painted.
		/// @param raster
		void SetTargetZBuffer(RenderWare::Raster* raster);  //TODO

		/// Sets the camera position and direction.
		/// @param transform The transform applied to the camera.
		void SetCameraTransform(const Transform& transform);

		Transform GetViewTransform() const;

		///
		/// Just calls GetCameraToPoint() for the current mouse coordinates.
		/// @param cameraPosition [Output]
		/// @param direction [Output]
		bool GetCameraToMouse(Vector3& cameraPosition, Vector3& direction) const;

		///
		///
		/// @param x
		/// @param y
		/// @param cameraPosition [Output]
		/// @param direction [Output]
		// direction is a normalized vector
		bool GetCameraToPoint(float x, float y, Vector3& cameraPosition, Vector3& direction) const;

		Camera* GetCamera();

		D3DVIEWPORT9 GetViewport() const;

	public:
		enum class Projection : int
		{
			NA = 0,
			Perspective = 1,
			Parallel = 2,
			PerspectiveInfinite = 3
		};

		struct Camera
		{
		public:
			/* 00h */	Matrix4 transform;  // worldToCameraTranspose
			/* 40h */	RenderWare::Raster* rasters[4];
			/* 50h */	RenderWare::Raster* zbuffer;
			/* 54h */	Vector2 viewOffset;
			/* 5Ch */	Vector2 viewWindow;
			/* 64h */	Vector2 recipViewWindow;  // scale?
			/* 6Ch */	Projection projectionType;  // 1 2 or 3, used to set projection matrix
			/* 70h */	float nearPlane;
			/* 74h */	float farPlane;
			/* 78h */	D3DVIEWPORT9 viewport;
			/* 90h */	void* window;
			/* 94h */	int stencilClear;
		};

		/* 00h */	Matrix4 viewTransform;
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
		/* 170h */	Camera* pCamera;

	private:
		// renamed to SetCameraTransform();
		void SetViewTransform(const Transform& transform);
	};

	ASSERT_SIZE(cViewer, 0x174);

	inline void cViewer::SetCameraTransform(const Transform& transform) {
		SetViewTransform(transform);
	}

	inline D3DVIEWPORT9 cViewer::GetViewport() const
	{
		return pCamera->viewport;
	}

	inline cViewer::Camera* cViewer::GetCamera() {
		return pCamera;
	}

	namespace Addresses(cViewer)
	{
		DeclareAddress(SetViewTransform);
		DeclareAddress(GetViewTransform);
		DeclareAddress(Initialize);
		DeclareAddress(ClearScene);
		DeclareAddress(LoadTransformations);
		DeclareAddress(SetBackgroundColor);
		DeclareAddress(GetNearPlane);
		DeclareAddress(GetFarPlane);
		DeclareAddress(SetNearPlane);
		DeclareAddress(SetFarPlane);
		DeclareAddress(SetAspectRatio);
		DeclareAddress(SetCameraMaterialLODs);
		DeclareAddress(GetCameraMaterialLODs);
		DeclareAddress(SetRenderType);
		DeclareAddress(GetCameraToMouse);
		DeclareAddress(GetCameraToPoint);
		DeclareAddress(SetViewWindow);  // 0x7C51A0 0x7C4BD0
		DeclareAddress(SetViewOffset);  // 0x7C5170 0x7C4BA0
		DeclareAddress(SetViewport);  // 0x7C5100 0x7C4B30
		DeclareAddress(SetPerspectiveProjection);  // 0x7C5A50 0x7C5480
		DeclareAddress(SetParallelProjection);  // 0x7C5AC0 0x7C54F0
		DeclareAddress(Dispose);  // 0x7C4240 0x7C3C70
		DeclareAddress(BeginUpdate);
		DeclareAddress(EndUpdate); // 0x7C42B0 0x7C3CE0
	}
}