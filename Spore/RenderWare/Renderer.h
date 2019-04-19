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

#include <d3d9.h>
#include "Shader.h"
#include <Spore\Graphics\MaterialShader.h>
#include "..\Internal.h"

namespace RenderWare
{
	namespace Renderer
	{
		/* -- DEVICE -- */

		inline IDirect3DDevice9* GetDevice() {
			return *(IDirect3DDevice9**)GetAddress(0x016FFD00, 0x16F99D0, 0x16F89D0);
		}

		/* -- VERTEX SHADER -- */

		inline IDirect3DVertexShader9* GetDXVertexShader() {
			return *(IDirect3DVertexShader9**)GetAddress(0x016FD894, 0x16F7564, 0x16F6564);
		}

		inline void SetDXVertexShader(IDirect3DVertexShader9* dxShader) {
			*(IDirect3DVertexShader9**)GetAddress(0x016FD894, 0x16F7564, 0x16F6564) = dxShader;
		}

		inline VertexShader* GetVertexShader() {
			return *(VertexShader**)GetAddress(0x016287D8, 0x1625568, 0x1624568);
		}

		inline void SetVertexShader(VertexShader* shader) {
			*(VertexShader**)GetAddress(0x016287D8, 0x1625568, 0x1624568) = shader;
		}

		void LoadVertexShaderConstants(int renderFlags, bool shaderChanged);
		/*{
			STATIC_CALL(GetAddress(0x006FE510, 0), void,
				PARAMS(int renderFlags, bool shaderChanged),
				PARAMS(renderFlags, shaderChanged));
		}*/

		/* -- PIXEL SHADER -- */

		inline IDirect3DPixelShader9* GetDXPixelShader() {
			return *(IDirect3DPixelShader9**)GetAddress(0x016FFCFC, 0x16F99CC, 0x16F89CC);
		}

		inline void SetDXPixelShader(IDirect3DPixelShader9* dxShader) {
			*(IDirect3DPixelShader9**)GetAddress(0x016FFCFC, 0x16F99CC, 0x16F89CC) = dxShader;
		}

		inline PixelShader* GetPixelShader() {
			return *(PixelShader**)GetAddress(0x0161D9D0, 0x161A760, 0x1619760);
		}

		inline void SetPixelShader(PixelShader* shader) {
			*(PixelShader**)GetAddress(0x0161D9D0, 0x161A760, 0x1619760) = shader;
		}

		void LoadPixelShaderConstants(int renderFlags, bool shaderChanged);
		/*{
			STATIC_CALL(GetAddress(0x006FA8F0, 0), void,
				PARAMS(int renderFlags, bool shaderChanged),
				PARAMS(renderFlags, shaderChanged));
		}*/

		/* -- MISC -- */

		inline int GetCompiledStateRenderFlags() {
			return *(int*)GetAddress(0x01700440, 0x16FA110, 0x16F9110);
		}

		inline void** GetShaderConstantsValues() {
			return (void**)GetAddress(0x016FD8D8, 0x16F75A8, 0x16F65A8);
		}

		inline Graphics::MaterialShader* GetMaterial() {
			return *(Graphics::MaterialShader**)GetAddress(0x016FD898, 0x16F7568, 0x16F6568);
		}

		inline D3DMATRIX* GetModelMatrix() {
			return *(D3DMATRIX**)GetAddress(0x016FF8DC, 0x16F95AC, 0x16F85AC);
		}

		inline void SetModelMatrix(D3DMATRIX* value) {
			*(D3DMATRIX**)GetAddress(0x016FF8DC, 0x16F95AC, 0x16F85AC) = value;
		}

		inline D3DMATRIX* GetTransposedModelMatrix() {
			return *(D3DMATRIX**)GetAddress(0x1700024, 0x16F9CF4, 0x16F8CF4);
		}

		inline void SetTransposedModelMatrix(D3DMATRIX* value) {
			*(D3DMATRIX**)GetAddress(0x1700024, 0x16F9CF4, 0x16F8CF4) = value;
		}

		/* -- STATES -- */

		inline void SetShaderConstantValue(short index, void* value, bool overrideIfEqual) {
			STATIC_CALL(GetAddress(0x7786E0, 0x777B50, 0x777B50), void, PARAMS(short, void*, bool), PARAMS(index, value, overrideIfEqual));
		}

		inline void __cdecl SetRenderState(int state, int value) {
			STATIC_CALL(GetAddress(0x529720, 0x529350, 0x529350), void, PARAMS(int, int), PARAMS(state, value));
		}
	}
}