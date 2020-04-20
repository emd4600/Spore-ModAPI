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

#include <Spore\Internal.h>
#include <Spore\IO\IStream.h>
#include <EASTL\intrusive_ptr.h>
#include <Spore\RenderWare\Mesh.h>

using namespace eastl;

namespace Graphics
{

	class MaterialShader
	{
	public:
		enum GeometryType
		{
			kGeometryTypeNA = 0xFFFFFFFF,
			kGeometryTypeStatic = 0x0,
			kGeometryTypeSkinned = 0x1,
			kGeometryTypeMorphed = 0x2,
			kGeometryTypeNumTypes = 0x3,
		};

		/// This type of function is called when rendering a mesh, before the \c DrawIndexedPrimitives is called.
		/// This function is responsible of loading the shaders into DirectX.
		typedef BOOL(*LoadShader_t)(RenderWare::Mesh<>*);

		int AddRef();

		inline LoadShader_t GetLoadMethod() const {
			return mpCallback;
		}

		inline void SetLoadMethod(LoadShader_t method) {
			mpCallback = method;
		}

	protected:
		/* 00h */	GeometryType mGeomType;
		/* 04h */	int mFlags;
		/* 08h */	int mElementTypes;
		/* 0Ch */	int16_t mVertexShaderVersion;
		/* 0Eh */	int16_t mVertexShaderVersion_;
		/* 10h */	int16_t mPixelShaderVersion;
		/* 12h */	int16_t mPixelShaderVersion_;
		/* 14h */	LoadShader_t mpCallback;
		/* 18h */	int mNumDataTypes;
		/* 1Ch */	int mDataTypeList;
		/* 20h */	int mVertexShaderUpdateFlags;
		/* 24h */	int mNumVertexShaderBuilders;
		/* 28h */	int mVertexShaderBuilders;
		/* 2Ch */	int mPixelShaderUpdateFlags;
		/* 30h */	int mNumPixelShaderBuilders;
		/* 34h */	int mPixelShaderBuilders;
		/* 38h */	uint32_t mID;
		/* 3Ch */	int mnRefCount;
		/* 40h */	int field_40;  // intrusive_list_node?
		/* 44h */	int field_44;


	public:
		static MaterialShader* Initialize(MaterialShader* dst, uint32_t shaderID, int arg_8, int arg_C, int arg_10,
			int vertexShaderVersion, int vertexShaderVersion_, int pixelShaderVersion, int pixelShaderVersion_);

		static MaterialShader* GetMaterialShader(uint32_t shaderID);

	};

	static_assert(sizeof(MaterialShader) == 0x48, "sizeof(MaterialShader) != 0x48");
	
	namespace Addresses(MaterialShader) {
		DeclareAddress(Reset);
		DeclareAddress(Initialize);
		DeclareAddress(GetMaterialShader);
	}
}