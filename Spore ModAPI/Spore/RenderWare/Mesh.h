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
	/// A structure that represents a basic mesh, made up of vertices and triangles. By default it
	/// only has one vertex buffer, you can have more by using Mesh_ . A vertex and index buffer can be
	/// shared by multiple meshes, as each mesh specifies the vertex and index count.
	/// See IndexBuffer and VertexBuffer for more information.
	///
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

		/* 00h */	int instancedSize;
		/* 04h */	D3DPRIMITIVETYPE primitiveType;
		/* 08h */	IndexBuffer* pIndexBuffer;
		/* 0Ch */	size_t triangleCount;
		/* 10h */	size_t vertexBuffersCount;
		/* 14h */	size_t firstIndex;
		/* 18h */	size_t indicesCount;
		/* 1Ch */	size_t firstVertex;
		/* 20h */	size_t vertexCount;
		/* 24h */	VertexBuffer* pVertexBuffers[1];


		static const uint32_t RW_TYPE = 0x20009;
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

	template <int numBuffers = 1>
	struct Mesh_ : public Mesh
	{
		Mesh_();

	private:
		int padding[numBuffers - 1];
	};

	template <int numBuffers>
	inline Mesh_<numBuffers>::Mesh_()
		: Mesh()
		, padding{}
	{
		instancedSize = sizeof(Mesh_<numBuffers>);
		vertexBuffersCount = numBuffers;
	}
}