#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\ShaderData.h>
#include <Spore\RenderWare\Raster.h>
#include <d3d9.h>

namespace Graphics
{
	namespace Renderer_addresses {
		DeclareAddress(D3D_ptr);
		DeclareAddress(Device_ptr);
		DeclareAddress(ShaderData_ptr);
		DeclareAddress(MaterialShader_ptr);
		DeclareAddress(ModelToWorld_ptr);
		DeclareAddress(ModelToWorldTransposed_ptr);
		DeclareAddress(PresentationParameters_ptr);

		DeclareAddress(SetShaderData);
		DeclareAddress(GetShaderDataSize);
		DeclareAddress(RegisterShaderData);

		DeclareAddress(SetPresentationParameters);
		DeclareAddress(CreateDevice);

		DeclareAddress(SetTexture);
	}
	namespace Addresses(RenderUtils) {
		DeclareAddress(D3D_ptr);
		DeclareAddress(Device_ptr);
		DeclareAddress(ShaderData_ptr);
		DeclareAddress(MaterialShader_ptr);
		DeclareAddress(ModelToWorld_ptr);
		DeclareAddress(ModelToWorldTransposed_ptr);
		DeclareAddress(PresentationParameters_ptr);

		DeclareAddress(SetShaderData);
		DeclareAddress(GetShaderDataSize);
		DeclareAddress(RegisterShaderData);

		DeclareAddress(SetPresentationParameters);
		DeclareAddress(CreateDevice);

		DeclareAddress(SetTexture);
	}

	/// 
	/// This namespace contains most internal stuff related with rendering, such as 
	/// Direct3D Device and shaders, shader data, etc
	///
	namespace RenderUtils
	{
		struct DeviceParameters
		{
			// 15 ints
			/* 00h */	UINT Adapter;
			/* 04h */	D3DDEVTYPE DeviceType;  // D3DDEVTYPE_HAL
			/* 08h */	UINT WindowHeight;
			/* 0Ch */	UINT WindowWidth;
			/* 10h */	UINT RefreshRate;
			/* 14h */	int field_14;
			/* 18h */	D3DFORMAT BackBufferFormat;
			/* 1Ch */	int field_1C;
			/* 20h */	BOOL VSync;
			/* 24h */	BOOL field_24;
			/* 28h */	int field_28;
			/* 2Ch */	BOOL NotHardwareVP;
			/* 30h */	BOOL NotPureDevice;
			/* 30h */	int field_30;
			/* 34h */	int field_34;
			/* 38h */	UINT NumFramesToBuffer;  // 2
		};

#ifndef SDK_TO_GHIDRA
		inline IDirect3D9* GetDirect3D() {
			return *(IDirect3D9**)(GetAddress(RenderUtils, D3D_ptr));
		}

		/// Returns the Direct3D Device used for all rendering operations in the game.
		inline IDirect3DDevice9* GetDevice() {
			return *(IDirect3DDevice9**)(GetAddress(RenderUtils, Device_ptr));
		}
#else
		IDirect3D9* sD3D;
		IDirect3DDevice9* sDevice;
#endif

		void SetShaderData(short index, void* value, bool overrideIfEqual = false);

		int GetShaderDataSize(short index);

		// max 2048
		void RegisterShaderData(short id, ShaderDataInformation::UnfixCB, 
			ShaderDataInformation::RefixCB, ShaderDataInformation::FixupCB, ShaderDataInformation::UploadCB);

		/// Assigns the presentation parameters that will be used by the DirectX device. 
		/// This must not be called, as it would create another device, but it can be detoured.
		/// @param parameters
		int SetPresentationParameters(const DeviceParameters& parameters);

		/// Creates the Direct3D device. This must not be called, as it would create another device; if you need to 
		/// modify this, detour this function.
		/// @param parameters
		int CreateDevice(DeviceParameters& parameters);
	}
}