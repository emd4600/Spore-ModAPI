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

#include <cstdint>
#include <d3d9.h>

namespace RenderWare
{
	///
	/// A buffer that contains all the indices (so triangles) data.
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [IDirect3DDevice9::CreateIndexBuffer method](https://msdn.microsoft.com/en-us/library/windows/desktop/bb174357.aspx)
	/// - [IDirect3DIndexBuffer9 interface](https://msdn.microsoft.com/en-us/library/windows/desktop/bb205865.aspx)
	/// - [IDirect3DDevice9::DrawIndexedPrimitive method](https://msdn.microsoft.com/en-us/library/windows/desktop/bb174369.aspx)
	///
	struct IndexBuffer
	{
		IndexBuffer();

		///
		/// Releases the DirectX buffer.
		///
		void ReleaseDirectX();

		///
		/// Creates the DirectX buffer. This will set the 'pDXBuffer' field.
		void CreateDirectX();

		/// Sends the buffer data into the DirectX object.
		void LockDirectXData();


		/// Applications use the methods of the IDirect3DIndexBuffer9 interface to manipulate an index buffer resource.
		/* 00h */	IDirect3DIndexBuffer9* pDXBuffer;

		/// The first index (not triangle, index) that will be rendered.
		/* 04h */	size_t startIndex;

		/// Number of indices to render. The number of vertices used is a function of the indices count and the primitive type.
		/* 08h */	size_t indicesCount;

		/// Usage can be 0, which indicates no usage value. However, if usage is desired, use a combination of one or more D3DUSAGE constants.
		/// By default it's D3DUSAGE_WRITEONLY
		/* 0Ch */	DWORD usage;

		/// Member of the D3DFORMAT enumerated type, describing the format of the index buffer. By default it's D3DFMT_INDEX16
		/* 10h */	D3DFORMAT format;

		/// Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
		/// By default it's D3DPT_TRIANGLELIST.
		/* 14h */	D3DPRIMITIVETYPE primitiveType;

		/// The raw data of the indices. If format is D3DFMT_INDEX16, this is a uint16_t array. If format is D3DFMT_INDEX32, this is a uint32_t array.
		/* 18h */	void* pIndexData;


		static const uint32_t RW_TYPE = 0x20007;
	};
}