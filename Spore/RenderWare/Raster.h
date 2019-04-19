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
#include <Spore\Internal.h>

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
		enum : uint16_t {
			kTypeTexture = 8,
			kTypeCubeTextureRTT = 9,
			kTypeTextureRTT = 10,

			kFlagDynamicUsage = 0x10,
			kFlagAutoGenMipap = 0x200,

			kFlagCubeTexture = 0x1000
		};

		Raster();

		/// Creates the corresponding Direct3D object for this raster, depending on the format and flags.
		void Create();

		/* 00h */	D3DFORMAT format;
		/* 04h */	uint16_t flags;  // the first byte chooses type
		/* 06h */	uint16_t volumeDepth;
		/* 08h */	union {
			IDirect3DSurface9* pSurface;
			IDirect3DTexture9* pTexture;
			IDirect3DCubeTexture9* pCubeTexture;
			IDirect3DVolumeTexture9* pVolumeTexture;
		};
		/* 0Ch */	uint16_t width;
		/* 0Eh */	uint16_t height;
		/* 10h */	char field_10;
		/* 11h */	uint8_t levels;
		/* 12h */	uint16_t cubeFaces;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	void* pTextureData;

		static const uint32_t TYPE = 0x20003;
	};

	static_assert(sizeof(Raster) == 0x20, "sizeof(Raster) != 20h");

	namespace InternalAddressList(Raster)
	{
		DefineAddress(Create, GetAddress(0x11F22E0, , PLACEHOLDER));
	};
}