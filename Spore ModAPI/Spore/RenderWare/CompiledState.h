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
#include <Spore\Graphics\GlobalState.h>

namespace RenderWare
{
	struct CompiledState;

	/// Structure used to configure textures in a CompiledState. 
	/// The benefit of this structure is that it keeps track of the previous of the state,
	/// and restores it once the TextureSlot object is destroyed.
	struct TextureSlot
	{
		/* 00h */	CompiledState* compiledState;
		/* 04h */	int slotIndex;
		/* 08h */	Raster* raster;
		/* 0Ch */	Raster* originalRaster;

		TextureSlot();
		~TextureSlot();

		/// Sets one texture of a compiled state, storing the previous texture in this slot so it
		/// can be restored later. `slotIndex` is the number used to reference the texture inside the shader.
		/// @param compiledState
		/// @param slotIndex
		/// @param raster
		void SetTexture(CompiledState* compiledState, int slotIndex, Raster* raster);
	};

	/// This structure contains properties that tells the renderer how to draw a certain object.
	/// This is often called "materials" in other games, as this decides the shader and some of its parameters,
	/// the textures that will be used, etc. 
	struct CompiledState
	{
		enum class Flags : uint32_t
		{
			UseTransform = 0x01,
			UseTransformObject = 0x02,
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

		/* 00h */	int instancedSize;
		/* 04h */	int primitiveType;
		/* 08h */	int softStateDirty;  // flags1
		/* 0Ch */	int softStateDelta;  // flags2
		/* 10h */	int hardStateDirty;  // flags3
		/* 14h */	int hardStateDelta;
		/* 18h */	Graphics::MaterialShader* shader;

		/// Sends the data of this compiled state into the renderer's active material state.
		void Load();

		Raster* GetRaster(size_t nSlotIndex);
		void SetRaster(size_t nSlotIndex, Raster* pRaster);

		/// Sets the matrix transform, only if it is enabled for this compiled state.
		/// Returns false if it wasn't enabled.
		bool SetTransform(const Math::Matrix4& matrix, Graphics::GlobalState::MatrixType type = Graphics::GlobalState::MATRIXTYPE_ORTHOGONAL);

		inline char* GetData() {
			char* thisp = (char*)this;
			return (char*)(((int)thisp + 0x2B) & ~15);
		}

		static const uint32_t TYPE = 0x2000B;
	};
	ASSERT_SIZE(TextureSlot, 0x10);

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