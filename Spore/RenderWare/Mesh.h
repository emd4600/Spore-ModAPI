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
#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\RenderWare\VertexBuffer.h>

namespace RenderWare
{
	///
	/// A structure that represents a basic mesh, made up of vertices and triangles. See IndexBuffer and VertexBuffer
	/// for more information.
	///
	template <int kNumBuffers = 1>
	struct Mesh
	{
		Mesh();

		///
		/// Returns the number of triangles this mesh would use if the primitive type was the one specified.
		/// @param primitiveType The type of primitive, in the D3DPRIMITIVETYPE enum.
		///
		size_t CalculateTriangleCount(D3DPRIMITIVETYPE primitiveType);

		///
		/// Sets the IndexBuffer used by this mesh. The primitive type will be set to use the one the buffer uses.
		/// CalculateTriangleCount(D3DPRIMITIVETYPE) will be called to update the triangle count.
		/// @param pBuffer The new IndexBuffer.
		///
		void SetIndexBuffer(IndexBuffer* pBuffer);

		///
		/// Sets the number of indicies used in this mesh. The primitive type will be set to use the one the index buffer uses.
		/// CalculateTriangleCount(D3DPRIMITIVETYPE) will be called to update the triangle count.
		/// @param nIndicesCount The new number of indices.
		///
		void SetIndicesCount(size_t nIndicesCount);

		///
		/// Sets the VertexBuffer used by this mesh at the given index. Meshes can use multiple vertex buffers, although usually 
		/// only one is used. The index is expected to be lower than the amount of buffers specified using the templated parameter.
		/// The primitive type will be set to use the one the index buffer uses.
		/// CalculateTriangleCount(D3DPRIMITIVETYPE) will be called to update the triangle count.
		/// @param nIndex The index of the VertexBuffer, usually 0.
		/// @param pVertexBuffer The VertexBuffer to use.
		///
		void SetVertexBuffer(size_t nIndex, VertexBuffer* pVertexBuffer);


		///
		/// Renders this mesh. This will use the material set in the Renderer. 
		/// 
		void Render();

		/* 00h */	int field_0;
		/* 04h */	D3DPRIMITIVETYPE primitiveType;
		/* 08h */	IndexBuffer* pIndexBuffer;
		/* 0Ch */	size_t triangleCount;
		/* 10h */	size_t vertexBuffersCount;
		/* 14h */	size_t firstIndex;
		/* 18h */	size_t indicesCount;
		/* 1Ch */	size_t firstVertex;
		/* 20h */	size_t vertexCount;
		/* 24h */	VertexBuffer* pVertexBuffers[kNumBuffers];


		static const uint32_t TYPE = 0x20009;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace InternalAddressList(Mesh)
	{
		DefineAddress(CalculateTriangleCount, GetAddress(0x011FBD30, 0x011F95F0, 0x011F95F0));
		DefineAddress(SetIndexBuffer, GetAddress(0x011FBE50, 0x011F9710, 0x011F9710));
		DefineAddress(SetIndicesCount, GetAddress(0x011FBE20, 0x011F96E0, 0x011F96E0));
		DefineAddress(SetVertexBuffer, GetAddress(0x011FBDE0, 0x011F96A0, 0x011F96A0));
		DefineAddress(Render, GetAddress(0x011FBE80, 0x011F9740, 0x011F9740));
	}

	template <int kNumBuffers>
	size_t Mesh<kNumBuffers>::CalculateTriangleCount(D3DPRIMITIVETYPE primitiveType) {
		return CALL(GetMethodAddress(Mesh, CalculateTriangleCount), size_t,
			PARAMS(Mesh<kNumBuffers>*, D3DPRIMITIVETYPE), PARAMS(this, primitiveType));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetIndexBuffer(IndexBuffer* indexBuffer) {
		CALL(GetMethodAddress(Mesh, SetIndexBuffer), void,
			PARAMS(Mesh<kNumBuffers>*, IndexBuffer*), PARAMS(this, indexBuffer));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetVertexBuffer(size_t index, VertexBuffer* vertexBuffer) {
		CALL(GetMethodAddress(Mesh, SetVertexBuffer), void,
			PARAMS(Mesh<kNumBuffers>*, size_t, VertexBuffer*), PARAMS(this, index, vertexBuffer));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetIndicesCount(size_t indicesCount) {
		CALL(GetMethodAddress(Mesh, SetIndicesCount), void,
			PARAMS(Mesh<kNumBuffers>*, size_t), PARAMS(this, indicesCount));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::Render() {
		CALL(GetMethodAddress(Mesh, Render), void,
			PARAMS(Mesh<kNumBuffers>*), PARAMS(this));
	}

	template <int kNumBuffers>
	Mesh<kNumBuffers>::Mesh()
		: field_0(0)
		, primitiveType(D3DPT_TRIANGLELIST)
		, pIndexBuffer(nullptr)
		, triangleCount()
		, vertexBuffersCount(kNumBuffers)
		, firstIndex()
		, indicesCount()
		, firstVertex()
		, vertexCount()
		, pVertexBuffers{}
	{

	}
}