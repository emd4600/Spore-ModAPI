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

#include <Spore\RenderWare\Raster.h>
#include <Spore\Graphics\MaterialShader.h>

namespace RenderWare
{
	struct CompiledState;

	struct TextureSlot
	{
		/* 00h */	CompiledState* compiledState;
		/* 04h */	int slotIndex;
		/* 08h */	Raster* raster;
		/* 0Ch */	Raster* originalRaster;

		void SetTexture(CompiledState* compiledState, int slotIndex, Raster* raster);
	};

	struct CompiledState
	{
		enum class Flags : uint32_t
		{
			UseShaderConstants = 0x08,
			UseMaterialColor = 0x10,
			UseAmbientColor = 0x20,
			UseVertexDescription = 0x100000,
			UseBooleans = 0x8000
		};

		enum class Flags3 : uint32_t
		{
			UseTextureSlots = 0xDFFFF,
			UseRenderStates = 0x20000
		};

		/* 00h */	int field_0;
		/* 04h */	int field_4;
		/* 08h */	int flags;  // flags?
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	Graphics::MaterialShader* pMaterialShader;  // RWShaderManager

		void Load();

		Raster* GetRaster(size_t nSlotIndex);
		void SetRaster(size_t nSlotIndex, Raster* pRaster);

		static const uint32_t TYPE = 0x2000B;
	};

	/////////////////////////////////
	//// INTERnAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(TextureSlot) == 0x10, "sizeof(TextureSlot) != 10h");

	namespace Addresses(TextureSlot)
	{
		DeclareAddress(SetTexture);
	}

	namespace Addresses(CompiledState)
	{
		DeclareAddress(Load);
		DeclareAddress(GetRaster);
		DeclareAddress(SetRaster);
	}

	inline auto_METHOD_VOID_(CompiledState, Load);

	inline auto_METHOD(CompiledState, Raster*, GetRaster, Args(size_t slotIndex), Args(slotIndex));
	inline auto_METHOD_VOID(CompiledState, SetRaster, Args(size_t slotIndex, Raster* raster), Args(slotIndex, raster));


	inline auto_METHOD_VOID(TextureSlot, SetTexture, Args(CompiledState* compiledState, int slotIndex, Raster* raster), Args(compiledState, slotIndex, raster));
}