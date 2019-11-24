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

	namespace Addresses(Mesh)
	{
		DeclareAddress(CalculateTriangleCount);
		DeclareAddress(SetIndexBuffer);
		DeclareAddress(SetIndicesCount);
		DeclareAddress(SetVertexBuffer);
		DeclareAddress(Render);
	}

	template <int kNumBuffers>
	size_t Mesh<kNumBuffers>::CalculateTriangleCount(D3DPRIMITIVETYPE primitiveType) {
		return CALL(GetAddress(Mesh, CalculateTriangleCount), size_t,
			Args(Mesh<kNumBuffers>*, D3DPRIMITIVETYPE), Args(this, primitiveType));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetIndexBuffer(IndexBuffer* indexBuffer) {
		CALL(GetAddress(Mesh, SetIndexBuffer), void,
			Args(Mesh<kNumBuffers>*, IndexBuffer*), Args(this, indexBuffer));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetVertexBuffer(size_t index, VertexBuffer* vertexBuffer) {
		CALL(GetAddress(Mesh, SetVertexBuffer), void,
			Args(Mesh<kNumBuffers>*, size_t, VertexBuffer*), Args(this, index, vertexBuffer));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::SetIndicesCount(size_t indicesCount) {
		CALL(GetAddress(Mesh, SetIndicesCount), void,
			Args(Mesh<kNumBuffers>*, size_t), Args(this, indicesCount));
	}

	template <int kNumBuffers>
	void Mesh<kNumBuffers>::Render() {
		CALL(GetAddress(Mesh, Render), void,
			Args(Mesh<kNumBuffers>*), Args(this));
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