#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\ShaderData.h>
#include <Spore\RenderWare\Raster.h>
#include <d3d9.h>

namespace Graphics
{
	namespace Addresses(Renderer) {
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

		inline IDirect3D9* GetDirect3D() {
			return *(IDirect3D9**)(GetAddress(RenderUtils, D3D_ptr));
		}

		/// Returns the Direct3D Device used for all rendering operations in the game.
		inline IDirect3DDevice9* GetDevice() {
			return *(IDirect3DDevice9**)(GetAddress(RenderUtils, Device_ptr));
		}

		/// Returns a pointer to the array that contains the values of shader data. 
		/// For example, you can do GetShaderData()[ShaderData::skinWeights];
		inline void** GetShaderData() {
			return (void**)(GetAddress(RenderUtils, ShaderData_ptr));
		}

		/// Returns the current MaterialShader object which is being used to render.
		/// This can either be a ShaderBuilder or an StandardShader.
		inline MaterialShader* GetMaterialShader() {
			return *(MaterialShader**)(GetAddress(RenderUtils, MaterialShader_ptr));
		}

		/// Returns the 'modelToWorld' matrix.
		inline D3DMATRIX* GetModelToWorld() {
			return *(D3DMATRIX**)(GetAddress(RenderUtils, ModelToWorld_ptr));
		}

		/// Sets the 'modelToWorld' matrix.
		/// @param value
		inline void SetModelMatrix(D3DMATRIX* value) {
			*(D3DMATRIX**)(GetAddress(RenderUtils, ModelToWorld_ptr)) = value;
		}

		/// Returns the 'modelToWorld' matrix, transposed.
		inline D3DMATRIX* GetModelToWorldTransposed() {
			return *(D3DMATRIX**)(GetAddress(RenderUtils, ModelToWorldTransposed_ptr));
		}

		/// Sets the 'modelToWorld' matrix, transposed.
		/// @param value
		inline void SetModelToWorldTransposed(D3DMATRIX* value) {
			*(D3DMATRIX**)(GetAddress(RenderUtils, ModelToWorldTransposed_ptr)) = value;
		}

		inline D3DPRESENT_PARAMETERS& GetPresentationParameters() {
			return *(D3DPRESENT_PARAMETERS*)(GetAddress(RenderUtils, PresentationParameters_ptr));
		}

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

		/// Sends the given raster to the Direct3D device.
		/// @param slotIndex The slot this raster will occupy, between 0 and 15.
		/// @param raster
		void SetTexture(int slotIndex, RenderWare::Raster* raster);

		/// Sets the given raster to be the active Direct3D render target for the given index.
		/// Only works if the Raster is a surface.
		/// @param index The render target index
		/// @returns D3D_OK if the operation succeeded, an error code otherwise.
		inline HRESULT SetRenderTarget(int index, RenderWare::Raster* raster) {
			return GetDevice()->SetRenderTarget(0, raster->pSurface);
		}
	}
}