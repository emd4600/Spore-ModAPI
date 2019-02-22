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
	/// A structure that contains information for a texture.
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [IDirect3DTexture9 interface](https://msdn.microsoft.com/en-us/library/windows/desktop/bb205909.aspx)
	/// - [IDirect3DDevice9::CreateTexture method(https://msdn.microsoft.com/en-us/library/windows/desktop/bb174363.aspx)
	///
	struct Raster
	{
		Raster();

		/* 00h */	uint32_t mTextureFormat;
		/* 04h */	uint16_t mnTextureFlags;
		/* 06h */	uint16_t mnVolumeDepth;
		/* 08h */	IDirect3DBaseTexture9* mpDXBaseTexture;
		/* 0Ch */	uint16_t mnWidth;
		/* 0Eh */	uint16_t mnHeight;
		/* 10h */	char field_10;
		/* 11h */	uint8_t mnMipmapLevels;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	void* mpTextureData;

		static const uint32_t TYPE = 0x20003;
	};
}