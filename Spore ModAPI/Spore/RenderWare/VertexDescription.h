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
	enum RWElementDeclaration
	{
		RWDECL_VERTEX_POSITION = 0,
		RWDECL_VERTEX_XYZRHW = 1,
		RWDECL_VERTEX_NORMAL = 2,
		RWDECL_VERTEX_COLOR = 3,
		RWDECL_VERTEX_PRELIGHT = 4,
		RWDECL_VERTEX_COLOR1 = 5,  // specular
		RWDECL_VERTEX_TEXCOORD0 = 6,
		RWDECL_VERTEX_TEXCOORD1 = 7,
		RWDECL_VERTEX_TEXCOORD2 = 8,
		RWDECL_VERTEX_TEXCOORD3 = 9,
		RWDECL_VERTEX_TEXCOORD4 = 10,
		RWDECL_VERTEX_TEXCOORD5 = 11,
		RWDECL_VERTEX_TEXCOORD6 = 12,
		RWDECL_VERTEX_TEXCOORD7 = 13,
		RWDECL_VERTEX_BLENDINDICES = 14,
		RWDECL_VERTEX_BLENDWEIGHTS = 15,
		RWDECL_VERTEX_POINTSIZE = 16,
		RWDECL_VERTEX_POSITION2 = 17,
		RWDECL_VERTEX_NORMAL2 = 18,
		RWDECL_VERTEX_TANGENT = 19,
		RWDECL_VERTEX_BINORMAL = 20,
		RWDECL_VERTEX_FOG = 21,
		RWDECL_VERTEX_BLENDINDICES2 = 22,
		RWDECL_VERTEX_BLENDWEIGHTS2 = 23,

		RWDECL_VERTEX2_POSITION = 0x1,
		RWDECL_VERTEX2_POSITION2 = 0x2,  // invented
		RWDECL_VERTEX2_TANGENT = 0x100,
		RWDECL_VERTEX2_COLOR = 0x1000,
		RWDECL_VERTEX2_COLOR1 = 0x2000,
		RWDECL_VERTEX2_TEXCOORD0 = 0x10000,
		RWDECL_VERTEX2_TEXCOORD1 = 0x20000,
		RWDECL_VERTEX2_TEXCOORD2 = 0x40000,
		RWDECL_VERTEX2_TEXCOORD3 = 0x80000,
		RWDECL_VERTEX2_TEXCOORD4 = 0x100000,
		RWDECL_VERTEX2_TEXCOORD5 = 0x200000,
		RWDECL_VERTEX2_TEXCOORD6 = 0x400000,
		RWDECL_VERTEX2_TEXCOORD7 = 0x800000,
		RWDECL_VERTEX2_NORMAL = 0x1000000,
		RWDECL_VERTEX2_NORMAL2 = 0x2000000,  // invented
		RWDECL_VERTEX2_BLENDINDICES = 0x10000000,
		RWDECL_VERTEX2_BLENDINDICES2 = 0x20000000,  // invented
		RWDECL_VERTEX2_BLENDWEIGHTS = 0x40000000,
		RWDECL_VERTEX2_BLENDWEIGHTS2 = 0x80000000,  // invented
	};

	constexpr unsigned int RWDECL_VERTEX2[] = {
		RWDECL_VERTEX2_POSITION,
		0,
		RWDECL_VERTEX2_NORMAL,
		RWDECL_VERTEX2_COLOR,
		0,
		RWDECL_VERTEX2_COLOR1,
		RWDECL_VERTEX2_TEXCOORD0,
		RWDECL_VERTEX2_TEXCOORD1,
		RWDECL_VERTEX2_TEXCOORD2,
		RWDECL_VERTEX2_TEXCOORD3,
		RWDECL_VERTEX2_TEXCOORD4,
		RWDECL_VERTEX2_TEXCOORD5,
		RWDECL_VERTEX2_TEXCOORD6,
		RWDECL_VERTEX2_TEXCOORD7,
		RWDECL_VERTEX2_BLENDINDICES,
		RWDECL_VERTEX2_BLENDWEIGHTS,
		0,
		RWDECL_VERTEX2_POSITION2,
		RWDECL_VERTEX2_NORMAL2,
		RWDECL_VERTEX2_TANGENT,
		0,
		0,
		RWDECL_VERTEX2_BLENDINDICES2,
		RWDECL_VERTEX2_BLENDWEIGHTS2,
	};

	/// Defines the vertex data layout. Each vertex can contain one or more data types, and each data type is described by a vertex element.
	struct VertexElement
	{
		/// Stream number.
		/* 00h */	uint16_t stream;
		/// Offset from the beginning of the vertex data to the data associated with the particular data type.
		/* 02h */	uint16_t offset;
		/// The data type, specified as a D3DDECLTYPE. One of several predefined types that define the data size. Some methods have an implied type.
		/* 04h */	char type;
		/// The method specifies the tessellator processing, which determines how the tessellator interprets (or operates on) the vertex data. For more information, see D3DDECLMETHOD.
		/* 05h */	char method;
		/// Defines what the data will be used for; that is, the interoperability between vertex data layouts and vertex shaders.
		/// Each usage acts to bind a vertex declaration to a vertex shader. In some cases, they have a special interpretation.
		/// For example, an element that specifies D3DDECLUSAGE_NORMAL or D3DDECLUSAGE_POSITION is used by the N - patch tessellator to set up tessellation.
		/// See D3DDECLUSAGE for a list of the available semantics.
		/// D3DDECLUSAGE_TEXCOORD can be used for user - defined fields (which don't have an existing usage defined).
		/* 06h */	char usage;
		/// Modifies the usage data to allow the user to specify multiple usage types.
		/* 07h */	char usageIndex;
		/* 08h */	int rwDecl;

		VertexElement();
		VertexElement(uint16_t stream, uint16_t offset, char type, char method, char usage, char usageIndex, int rwDecl);
	};

	struct VertexDescriptionBase
	{
		static const uint32_t RW_TYPE = 0x20004;

		VertexDescriptionBase();

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

		void SetElement(int index, const VertexElement& element);

		void D3D9VertexDescriptorAddToList(VertexDescriptionBase*);

		/* 00h */	VertexDescriptionBase* pNextParent;
		/* 04h */	VertexDescriptionBase* pNextSibling;

		/// The IDirect3DVertexDeclaration9 that operates behind this structure.
		/* 08h */	IDirect3DVertexDeclaration9* pDXVertexDeclaration;

		/// The amount of elements contained in this description.
		/* 0Ch */	uint16_t elementsCount;

		/* 0Eh */	char lockFlags;

		/// The size in bytes of each vertex.
		/* 0Fh */	uint8_t stride;

		/* 10h */	int elementsUsed;
		/* 14h */	int elementsHash;

		/// An array of all the VertexElement objects of this description.
		/* 18h */	VertexElement elements[1];
	};

	///
	/// A vertex declaration defines the vertex buffer layout and programs the tessellation engine.
	/// This structure has a template parameter which is the number of elements it contains.
	/// For example, to use 3 elements: new VertexDescription<3>();
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [Vertex Declaration](https://msdn.microsoft.com/en-us/library/windows/desktop/bb206335.aspx)
	/// - [D3DVERTEXELEMENT9](https://msdn.microsoft.com/en-us/library/windows/desktop/bb172630.aspx)
	///
	template <uint16_t nVertexElements = (uint16_t)1>
	struct VertexDescription : public VertexDescriptionBase
	{
		VertexDescription();

	private:
		VertexElement padding[nVertexElements - 1];
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(VertexDescription)
	{
		DeclareAddress(LoadDeclaration);
		DeclareAddress(Process);
		DeclareAddress(D3D9VertexDescriptorAddToList);
	}

	template <uint16_t nVertexElements>
	inline VertexDescription<nVertexElements>::VertexDescription()
		: VertexDescriptionBase()
		, padding{}
	{
		elementsCount = nVertexElements;
	}
}