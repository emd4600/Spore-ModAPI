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
#pragma warning (disable:4351)

#include <d3d9.h>

#define MAX_SHADER_CONSTANTS 32

namespace RenderWare
{
	struct ShaderConstant
	{
		ShaderConstant() {}
		ShaderConstant(int _constantIndex, int _registerSize)
			:
			constantIndex(_constantIndex), registerSize(_registerSize),
			field_12(0), field_18(0),
			field_0(0), field_4(0), field_8(0), field_C(0)
		{
		}

		int field_0;
		int field_4;
		int field_8;
		int field_C;
		/* 10h */	short constantIndex;  // index to a table of constants, like the 'materialColor'
		short field_12;
		/* 14h */	short registerSize;
		int field_18;
	};

	static_assert(sizeof(ShaderConstant) == 0x1C, "sizeof(ShaderConstant) != 1Ch");

	// size 130h
	template <typename ShaderType>
	class Shader
	{
	public:
		Shader() :
			_padding_0(), dxShader(nullptr), constantsCount(0), constants(), startRegisters(), field_12C(0)
		{
		}

		char _padding_0[0x20];

		/* 20h */	ShaderType* dxShader;

		int field_24;

		/* 28h */	int constantsCount;
		/* 2Ch */	ShaderConstant* constants[MAX_SHADER_CONSTANTS];
		/* ACh */	int startRegisters[MAX_SHADER_CONSTANTS];

		int field_12C;
	};

	typedef Shader<IDirect3DVertexShader9> VertexShader;
	typedef Shader<IDirect3DPixelShader9> PixelShader;

	static_assert(sizeof(PixelShader) == 0x130, "sizeof(Shader) != 130h");
}

// loc_7C56F8 -> sets the thing which contains the Vertex shader