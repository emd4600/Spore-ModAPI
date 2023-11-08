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
	/// Low-level representation of a game texture. Its high-level equivalent is Graphics::Texture.
	/// Rasters can be loaded into shaders and materials using the TextureSlot structure.
	/// For more information, check the official Direct3D 9 documentation: 
	/// - [IDirect3DTexture9 interface](https://msdn.microsoft.com/en-us/library/windows/desktop/bb205909.aspx)
	/// - [IDirect3DDevice9::CreateTexture method](https://msdn.microsoft.com/en-us/library/windows/desktop/bb174363.aspx)
	struct Raster
	{
		enum Flags : uint16_t {
			/*kTypeTexture = 8,
			kTypeCubeTextureRTT = 9,
			kTypeTextureRTT = 10,

			kFlagDynamicUsage = 0x10,
			kFlagAutoGenMipap = 0x200,

			kFlagCubeTexture = 0x1000,
			kFlagVolumeTexture = 0x2000 // ?*/

			kTypeDepthStencilSurface = 2,
			kTypeTexture = 8,
			kTypeRenderTarget = 9,
			kTypeDepthStencilTexture = 10,

			kFlagDynamicUsage = 0x10,
			kFlagAutoGenMipap = 0x200,

			kFlagCubeTexture = 0x1000,
			kFlagVolumeTexture = 0x2000
		};

		Raster();
		~Raster();

		void Delete();

		/// Creates the corresponding Direct3D object for this raster, depending on the format and flags.
		void Create();

		HRESULT CreateTexture(DWORD usage = NULL, D3DPOOL pool = D3DPOOL_DEFAULT);

		void D3D9AddToUnmanagedList();

		/// Returns how many bytes are needed to store one raw mip level of the raster.
		/// @param mipLevel
		/// @returns
		int D3D9GetStreamedMipLevelSize(int mipLevel = 0);

		static Raster* CreateRaster(Raster*& pDst, uint16_t width, uint16_t height, uint8_t levels, int flagsDepth, D3DFORMAT format);

		bool CopyRaster(Raster* other);

		/// Sets the raw contents of a mip level of the raster.
		/// @param data
		/// @param mipLevel
		/// @returns
		bool Fill(int8_t* data, int mipLevel = 0);

		/// Extracts the raw contents of a mip level of the raster, and saves it in a byte array.
		/// The byte array must be of size returned by D3D9GetStreamedMipLevelSize()
		/// @param[out] dstData
		/// @param mipLevel
		/// @returns
		bool Extract(int8_t* dstData, int mipLevel = 0);

		/* 00h */	D3DFORMAT format;
		/* 04h */	uint16_t flags;  // the first byte chooses type
		/* 06h */	uint16_t volumeDepth;
		/* 08h */	union RasterDirect3dData {
			IDirect3DSurface9* pSurface;
			IDirect3DTexture9* pTexture;
			IDirect3DCubeTexture9* pCubeTexture;
			IDirect3DVolumeTexture9* pVolumeTexture;
		};
		/* 0Ch */	uint16_t width;
		/* 0Eh */	uint16_t height;
		/* 10h */	uint8_t depth;
		/* 11h */	uint8_t levels;
		/* 12h */	uint16_t cubeFaces;
		/* 14h */	Raster* pNextParent;
		/* 18h */	void* pSwapChain;
		/* 1Ch */	void* pTextureData;

		static const uint32_t RW_TYPE = 0x20003;
	};
	ASSERT_SIZE(Raster, 0x20);

	namespace Addresses(Raster)
	{
		DeclareAddress(Create);
		DeclareAddress(Delete);
		DeclareAddress(CreateRaster);
		DeclareAddress(D3D9AddToUnmanagedList);
		DeclareAddress(Extract);  // 0x11F2BC0 0x11F0490
		DeclareAddress(Fill);  // 0x11F29F0 0x11F02C0
		DeclareAddress(D3D9GetStreamedMipLevelSize);  // 0x11F2780 0x11F0050
	};
}