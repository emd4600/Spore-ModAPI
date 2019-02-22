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

#include <cinttypes>
#include <d3d9.h>
#include <Spore\Internal.h>

namespace RenderWare
{

	enum class RWVertexElementType : uint32_t
	{
		Position = 0,
		Normals = 2,
		UV = 6,
		BoneAssignments = 0xE,
		SkinWeights = 0xF,
		Tangents = 0x13
	};

	/// Defines the vertex data layout. Each vertex can contain one or more data types, and each data type is described by a vertex element.
	struct VertexElement
	{
		/// Stream number.
		/* 00h */	uint16_t mnStream;
		/// Offset from the beginning of the vertex data to the data associated with the particular data type.
		/* 02h */	uint16_t mnOffset;
		/// The data type, specified as a D3DDECLTYPE. One of several predefined types that define the data size. Some methods have an implied type.
		/* 04h */	char type;
		/// The method specifies the tessellator processing, which determines how the tessellator interprets (or operates on) the vertex data. For more information, see D3DDECLMETHOD.
		/* 05h */	char method;
		/// Defines what the data will be used for; that is, the interoperability between vertex data layouts and vertex shaders.Each usage acts to bind a vertex declaration to a vertex shader.In some cases, they have a special interpretation.For example, an element that specifies D3DDECLUSAGE_NORMAL or D3DDECLUSAGE_POSITION is used by the N - patch tessellator to set up tessellation.See D3DDECLUSAGE for a list of the available semantics.D3DDECLUSAGE_TEXCOORD can be used for user - defined fields(which don't have an existing usage defined).
		/* 06h */	char usage;
		/// Modifies the usage data to allow the user to specify multiple usage types.
		/* 07h */	char usageIndex;
		/* 08h */	RWVertexElementType mTypeCode;

		VertexElement();
		VertexElement(uint16_t stream, uint16_t offset, char type, char method, char usage, char usageIndex, RWVertexElementType typeCode);
	};

	///
	/// A vertex declaration defines the vertex buffer layout and programs the tessellation engine.
	/// This structure has a template parameter which is the number of elements it contains.
	/// For example, to use 3 elements: new VertexDescription<3>();
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [Vertex Declaration](https://msdn.microsoft.com/en-us/library/windows/desktop/bb206335.aspx)
	/// - [D3DVERTEXELEMENT9](https://msdn.microsoft.com/en-us/library/windows/desktop/bb172630.aspx)
	///
	template <uint16_t nVertexElements = (uint16_t)0>
	struct VertexDescription
	{
		VertexDescription();

		///
		/// Creates the IDirect3DVertexDeclaration9 object required by Direct3D 9 using the elements in this description.
		/// 
		void CreateDeclaration(IDirect3DDevice9* pDevice);

		///
		/// Loads this IDirect3DVertexDeclaration9 into DirectX.
		///
		void LoadDeclaration();

		///
		/// Releases the DirectX object.
		///
		void ReleaseDirectX();

		/* 00h */	int field_0;
		/* 04h */	int field_4;

		/// The IDirect3DVertexDeclaration9 that operates behind this structure.
		/* 08h */	IDirect3DVertexDeclaration9* mpDXVertexDeclaration;

		/// The amount of elements contained in this description.
		/* 0Ch */	uint16_t mnElementsCount;

		/* 0Eh */	char field_E;

		/// The size in bytes of each vertex.
		/* 0Fh */	uint8_t mnStride;

		/* 10h */	int field_10;
		/* 14h */	int field_14;

		/// An array of all the VertexElement objects of this description.
		/* 18h */	VertexElement mElements[nVertexElements];

		static const uint32_t TYPE = 0x20004;
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace InternalAddressList(VertexDescription)
	{
		DefineAddress(LoadDeclaration, GetAddress(0x011F5310, 0x11F2BF0, 0x11F2BF0));
		DefineAddress(Process, GetAddress(0x11F5350, 0x11F2C30, 0x11F2C30));
	}

	template <uint16_t kVertexElements = 0>
	VertexDescription<kVertexElements>::VertexDescription()
		: field_10(0x0008c045)
		, field_14(0x51010101)
		, field_E(0)
		, mnElementsCount(kVertexElements)
		, mpDXVertexDeclaration(nullptr)
		, field_0(0)
		, field_4(0)
		, mElements{}
	{

	}

	template <uint16_t kVertexElements = 0>
	void VertexDescription<kVertexElements>::ReleaseDirectX()
	{
		if (mpDXVertexDeclaration != nullptr)
		{
			mpDXVertexDeclaration->Release();
			mpDXVertexDeclaration = nullptr;
		}
	}

	template <uint16_t kVertexElements = 0>
	void VertexDescription<kVertexElements>::CreateDeclaration(IDirect3DDevice9* pDevice)
	{
		D3DVERTEXELEMENT9 dxElements[17];

		for (int i = 0; i < this->c && i < 16; i++)
		{
			dxElements[i].Method = this->mElements[i].method;
			dxElements[i].Offset = this->mElements[i].mnOffset;
			dxElements[i].Type = this->mElements[i].type;
			dxElements[i].Stream = this->mElements[i].mnStream;
			dxElements[i].Usage = this->mElements[i].usage;
			dxElements[i].UsageIndex = this->mElements[i].usageIndex;
		}
		dxElements[this->mnElementsCount] = D3DDECL_END();

		pDevice->CreateVertexDeclaration(dxElements, &this->mpDXVertexDeclaration);
	}

	template <uint16_t kVertexElements = 0>
	inline auto_METHOD_VOID_(VertexDescription<kVertexElements>, LoadDeclaration);
}