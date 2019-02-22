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

namespace RenderWare
{
	void IndexBuffer::ReleaseDirectX()
	{
		if (mpDXBuffer != nullptr)
		{
			mpDXBuffer->Release();
			mpDXBuffer = nullptr;
		}
	}

	IndexBuffer::IndexBuffer()
		: mpDXBuffer(nullptr)
		, mnStartIndex(0)
		, mPrimitiveType(D3DPT_TRIANGLELIST)
		, mUsage(D3DUSAGE_WRITEONLY)
		, mFormat(D3DFORMAT::D3DFMT_INDEX16)
		, mnPrimitiveCount(0)
		, mpIndexData(nullptr)
	{
	}


	void VertexBuffer::ReleaseDirectX()
	{
		if (this->mpDXBuffer != nullptr)
		{
			this->mpDXBuffer->Release();
			this->mpDXBuffer = nullptr;
		}
	}

	VertexBuffer::VertexBuffer()
		: mpVertexDescription(nullptr)
		, mpDXBuffer(nullptr)
		, mnBaseVertexIndex(0)
		, mnVertexCount(0)
		, field_10(0)
		, mnStride(0)
		, mpVertexData(nullptr)
	{
	}


	VertexElement::VertexElement()
		: mnStream(0)
		, mnOffset(0)
		, type(0)
		, method(0)
		, usage(0)
		, usageIndex(0)
		, mTypeCode()
	{
	}

	VertexElement::VertexElement(uint16_t stream_, uint16_t offset_, char type_, char method_,
		char usage_, char usageIndex_, RWVertexElementType typeCode_)

		: mnStream(stream_)
		, mnOffset(offset_)
		, type(type_)
		, method(method_)
		, usage(usage_)
		, usageIndex(usageIndex_)
		, mTypeCode(typeCode_)
	{

	}


	Raster::Raster()
		: mTextureFormat(0)
		, mnTextureFlags()
		, mnVolumeDepth()
		, mpDXBaseTexture(nullptr)
		, mnWidth(0)
		, mnHeight(0)
		, field_10()
		, mnMipmapLevels(0)
		, field_14()
		, field_18()
		, mpTextureData(nullptr)
	{}
}
