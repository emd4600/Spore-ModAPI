#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\RenderWare\VertexDescription.h>
#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\Raster.h>
#include <Spore\Graphics\RenderUtils.h>

namespace RenderWare
{
	void IndexBuffer::ReleaseDirectX()
	{
		if (pDXBuffer != nullptr)
		{
			pDXBuffer->Release();
			pDXBuffer = nullptr;
		}
	}

	IndexBuffer::IndexBuffer()
		: pDXBuffer(nullptr)
		, startIndex(0)
		, primitiveType(D3DPT_TRIANGLELIST)
		, usage(D3DUSAGE_WRITEONLY)
		, format(D3DFORMAT::D3DFMT_INDEX16)
		, indicesCount(0)
		, pIndexData(nullptr)
	{
	}

	void IndexBuffer::CreateDirectX() {
		auto device = Graphics::RenderUtils::GetDevice();
		int size = (format == D3DFMT_INDEX16 ? 2 : 4) * indicesCount;
		device->CreateIndexBuffer(size, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, format, D3DPOOL_DEFAULT,
			&this->pDXBuffer, NULL);
	}

	void IndexBuffer::LockDirectXData() {
		int size = (format == D3DFMT_INDEX16 ? 2 : 4) * indicesCount;
		void* data;
		pDXBuffer->Lock(0, size, &data, D3DLOCK_NOOVERWRITE);
		memcpy_s(data, size, pIndexData, size);
		pDXBuffer->Unlock();
	}


	void VertexBuffer::ReleaseDirectX()
	{
		if (this->pDXBuffer != nullptr)
		{
			this->pDXBuffer->Release();
			this->pDXBuffer = nullptr;
		}
	}

	void VertexBuffer::CreateDirectX() {
		auto device = Graphics::RenderUtils::GetDevice();
		device->CreateVertexBuffer(vertexCount*stride, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, 
			&this->pDXBuffer, NULL);
	}

	void VertexBuffer::LockDirectXData() {
		int size = vertexCount*stride;
		void* data;
		pDXBuffer->Lock(0, size, &data, D3DLOCK_NOOVERWRITE);
		memcpy_s(data, size, pVertexData, size);
		pDXBuffer->Unlock();
	}

	VertexBuffer::VertexBuffer()
		: pVertexDescription(nullptr)
		, pDXBuffer(nullptr)
		, baseVertexIndex(0)
		, vertexCount(0)
		, usage(0)
		, stride(0)
		, lockFlags(0)
		, pVertexData(nullptr)
	{
	}


	VertexElement::VertexElement()
		: stream(0)
		, offset(0)
		, type(0)
		, method(0)
		, usage(0)
		, usageIndex(0)
		, rwDecl()
	{
	}

	VertexElement::VertexElement(uint16_t stream_, uint16_t offset_, char type_, char method_,
		char usage_, char usageIndex_, int typeCode_)

		: stream(stream_)
		, offset(offset_)
		, type(type_)
		, method(method_)
		, usage(usage_)
		, usageIndex(usageIndex_)
		, rwDecl(typeCode_)
	{

	}

	VertexDescriptionBase::VertexDescriptionBase()
		: elementsUsed(0)  // 0x0008c045
		, elementsHash(0)  // 0x51010101
		, lockFlags(0)
		, elementsCount(1)
		, pDXVertexDeclaration(nullptr)
		, pNextParent(nullptr)
		, pNextSibling(nullptr)
		, elements{}
	{

	}

	void VertexDescriptionBase::ReleaseDirectX()
	{
		if (pDXVertexDeclaration != nullptr)
		{
			pDXVertexDeclaration->Release();
			pDXVertexDeclaration = nullptr;
		}
	}

	void VertexDescriptionBase::CreateDeclaration(IDirect3DDevice9* pDevice)
	{
		D3DVERTEXELEMENT9 dxElements[17];

		for (int i = 0; i < this->elementsCount && i < 16; i++)
		{
			dxElements[i].Method = this->elements[i].method;
			dxElements[i].Offset = this->elements[i].offset;
			dxElements[i].Type = this->elements[i].type;
			dxElements[i].Stream = this->elements[i].stream;
			dxElements[i].Usage = this->elements[i].usage;
			dxElements[i].UsageIndex = this->elements[i].usageIndex;
		}
		dxElements[this->elementsCount] = D3DDECL_END();

		pDevice->CreateVertexDeclaration(dxElements, &this->pDXVertexDeclaration);
	}

	void VertexDescriptionBase::LoadDeclaration() {
		CALL(GetAddress(VertexDescription, LoadDeclaration), void,
			Args(VertexDescriptionBase*), Args(this));
	}


	void VertexDescriptionBase::SetElement(int index, const VertexElement& element)
	{
		this->elements[index] = element;
		this->elementsUsed |= 1 << element.rwDecl;
	}
}
#endif
