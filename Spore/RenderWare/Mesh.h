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
		/* 04h */	D3DPRIMITIVETYPE mPrimitiveType;
		/* 08h */	IndexBuffer* mpIndexBuffer;
		/* 0Ch */	size_t mnTriangleCount;
		/* 10h */	size_t mnVertexBuffersCount;
		/* 14h */	size_t mnFirstIndex;
		/* 18h */	size_t mnIndicesCount;
		/* 1Ch */	size_t mnFirstVertex;
		/* 20h */	size_t mnVertexCount;
		/* 24h */	VertexBuffer* mpVertexBuffers[kNumBuffers];


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
	auto_METHOD(Mesh<kNumBuffers>, size_t, CalculateTriangleCount, PARAMS(D3DPRIMITIVETYPE primitiveType), PARAMS(primitiveType));
	template <int kNumBuffers>
	auto_METHOD(Mesh<kNumBuffers>, void, SetIndexBuffer, PARAMS(IndexBuffer* indexBuffer), PARAMS(indexBuffer));
	template <int kNumBuffers>
	auto_METHOD(Mesh<kNumBuffers>, void, SetIndicesCount, PARAMS(size_t indicesCount), PARAMS(indicesCount));
	template <int kNumBuffers>
	auto_METHOD(Mesh<kNumBuffers>, void, SetVertexBuffer, PARAMS(size_t index, VertexBuffer* vertexBuffer), PARAMS(index, vertexBuffer));
	template <int kNumBuffers>
	auto_METHOD_(Mesh<kNumBuffers>, void, Render);

	template <int kNumBuffers>
	Mesh<kNumBuffers>::Mesh()
		: field_0(0)
		, mPrimitiveType(D3DPT_TRIANGLELIST)
		, mpIndexBuffer(nullptr)
		, mnTriangleCount()
		, mnVertexBufferCount(kNumBuffers)
		, mnFirstIndex()
		, mnPrimitiveCount()
		, mnFirstVertex()
		, mnVertexCount()
		, mpVertexBuffers{}
	{

	}
}