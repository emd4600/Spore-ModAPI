#pragma once

#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\RenderUtils.h>
#include <Spore\Internal.h>

namespace Graphics
{
	namespace ActiveState
	{
		/// Sends the given raster to the Direct3D device.
		/// @param slotIndex The slot this raster will occupy, between 0 and 15.
		/// @param raster
		void SetTexture(int slotIndex, RenderWare::Raster* raster);

		/// Returns a pointer to the array that contains the values of shader data. 
		/// For example, you can do GetShaderData()[ShaderData::skinWeights];
		void** GetShaderData();
		/// Returns the current MaterialShader object which is being used to render.
		/// This can either be a ShaderBuilder or an StandardShader.
		MaterialShader* GetMaterialShader();

		/// Returns the 'modelToWorld' transform matrix.
		D3DMATRIX* GetTransform();

		/// Sets the 'modelToWorld' matrix.
		/// @param value
		void SetTransform(D3DMATRIX* value);

		/// Returns the 'modelToWorld' transform matrix, transposed.
		D3DMATRIX* GetTransposedTransform();

		/// Sets the 'modelToWorld' transform matrix, transposed.
		/// @param value
		void SetTransposedTransform(D3DMATRIX* value);

		D3DPRESENT_PARAMETERS& GetPresentParams();

#ifdef SDK_TO_GHIDRA
		void* sShaderData[0x800];
		MaterialShader* sShader;
		D3DMATRIX* sTransform;
		D3DMATRIX* sTransposedTransform;
		D3DPRESENT_PARAMETERS sPresentParams;
#endif

#ifndef SDK_TO_GHIDRA
		/// Sets the given raster to be the active Direct3D render target for the given index.
		/// Only works if the Raster is a surface.
		/// @param index The render target index
		/// @returns D3D_OK if the operation succeeded, an error code otherwise.
		inline HRESULT SetRenderTarget(int index, RenderWare::Raster* raster) {
			return RenderUtils::GetDevice()->SetRenderTarget(0, raster->pSurface);
		}
#endif
	}

	namespace Addresses(ActiveState)
	{
		DeclareAddress(sShaderData);
		DeclareAddress(sShader);
		DeclareAddress(sTransform);
		DeclareAddress(sTransposedTransform);
		DeclareAddress(sPresentParams);
		DeclareAddress(SetTexture);
	}
}