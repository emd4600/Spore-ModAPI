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

#include <Spore\RenderWare\VertexDescription.h>
#include <d3d9.h>

namespace RenderWare
{
	///
	/// A buffer that contains all the vertices data.
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [IDirect3DDevice9::CreateVertexBuffer method](https://msdn.microsoft.com/en-us/library/windows/desktop/bb174364.aspx)
	/// - [IDirect3DVertexBuffer9 interface](https://msdn.microsoft.com/en-us/library/windows/desktop/bb205915.aspx)
	/// - [IDirect3DDevice9::DrawIndexedPrimitive method](https://msdn.microsoft.com/en-us/library/windows/desktop/bb174369.aspx)
	///
	struct VertexBuffer
	{
		VertexBuffer();

		///
		/// Releases the DirectX buffer.
		///
		void ReleaseDirectX();

		///
		/// Creates the DirectX buffer. This will set the 'pDXBuffer' field.
		void CreateDirectX();

		/// Sends the buffer data into the DirectX object.
		void LockDirectXData();

		/// The VertexDescription that defines the data that each vertex has.
		/* 00h */	VertexDescriptionBase* pVertexDescription;

		/// The IDirect3DVertexBuffer9 that is operating behind this structure.
		/* 04h */	IDirect3DVertexBuffer9* pDXBuffer;

		/// Offset from the start of the vertex buffer to the first vertex.
		/* 08h */	size_t baseVertexIndex;

		/// The amount of vertices contained in the buffer.
		/* 0Ch */	size_t vertexCount;

		/* 10h */	int usage;

		/// The size in bytes of each vertex structure.
		/* 14h */	uint8_t stride;
		/* 15h */	uint8_t lockFlags;

		/// The raw data of the vertices. This is an array of vertices, but the data they contain depends on the VertexDescription.
		/* 18h */	void* pVertexData;

		static const uint32_t RW_TYPE = 0x20005;
	};
}