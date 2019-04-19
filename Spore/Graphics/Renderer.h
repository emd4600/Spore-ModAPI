#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\MaterialShader.h>
#include <d3d9.h>

namespace Graphics
{
	namespace InternalAddressList(Renderer) {
		DefineAddress(Device_ptr, GetAddress(0x016FFD00, 0x16F99D0, 0x16F89D0));
		DefineAddress(ShaderData_ptr, GetAddress(0x016FD8D8, 0x16F75A8, 0x16F65A8));
		DefineAddress(MaterialShader_ptr, GetAddress(0x016FD898, 0x16F7568, 0x16F6568));
		DefineAddress(ModelToWorld_ptr, GetAddress(0x016FF8DC, 0x16F95AC, 0x16F85AC));
		DefineAddress(ModelToWorldTransposed_ptr, GetAddress(0x1700024, 0x16F9CF4, 0x16F8CF4));

		DefineAddress(SetShaderData, GetAddress(0x7786E0, 0x777B50, 0x777B50));

		DefineAddress(CreateDevice, GetAddress(0x11FADF0, , PLACEHOLDER));
	}

	/// 
	/// This namespace contains most internal stuff related with rendering, such as 
	/// Direct3D Device and shaders, shader data, etc
	///
	namespace Renderer
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

		/// Returns the Direct3D Device used for all rendering operations in the game.
		inline IDirect3DDevice9* GetDevice() {
			return *(IDirect3DDevice9**)(GetMethodAddress(Renderer, Device_ptr));
		}

		/// Returns a pointer to the array that contains the values of shader data. 
		/// For example, you can do GetShaderData()[ShaderData::skinWeights];
		inline void** GetShaderData() {
			return (void**)(GetMethodAddress(Renderer, ShaderData_ptr));
		}

		/// Returns the current MaterialShader object which is being used to render.
		/// This can either be a ShaderBuilder or an StandardShader.
		inline MaterialShader* GetMaterialShader() {
			return *(MaterialShader**)(GetMethodAddress(Renderer, MaterialShader_ptr));
		}

		/// Returns the 'modelToWorld' matrix.
		inline D3DMATRIX* GetModelToWorld() {
			return *(D3DMATRIX**)(GetMethodAddress(Renderer, ModelToWorld_ptr));
		}

		/// Sets the 'modelToWorld' matrix.
		/// @param value
		inline void SetModelMatrix(D3DMATRIX* value) {
			*(D3DMATRIX**)(GetMethodAddress(Renderer, ModelToWorld_ptr)) = value;
		}

		/// Returns the 'modelToWorld' matrix, transposed.
		inline D3DMATRIX* GetModelToWorldTransposed() {
			return *(D3DMATRIX**)(GetMethodAddress(Renderer, ModelToWorldTransposed_ptr));
		}

		/// Sets the 'modelToWorld' matrix, transposed.
		/// @param value
		inline void SetModelToWorldTransposed(D3DMATRIX* value) {
			*(D3DMATRIX**)(GetMethodAddress(Renderer, ModelToWorldTransposed_ptr)) = value;
		}

		inline void SetShaderData(short index, void* value, bool overrideIfEqual=false) {
			STATIC_CALL((GetMethodAddress(Renderer, SetShaderData)), void, PARAMS(short, void*, bool), PARAMS(index, value, overrideIfEqual));
		}

		/// Creates the Direct3D device. This must not be called, as it would create another device; if you need to 
		/// modify this, detour this function.
		/// @param parameters
		int CreateDevice(DeviceParameters& parameters);
	}
}