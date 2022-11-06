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

#include <Spore\RenderWare\Raster.h>
#include <Spore\Graphics\cRwDirectResource.h>
#include <Spore\ResourceKey.h>

#include <EASTL\intrusive_ptr.h>
#include <EASTL\vector.h>

#define TexturePtr eastl::intrusive_ptr<Graphics::Texture>

namespace Graphics
{
	enum TextureFlags
	{
		/// Tells the texture is still loading
		kTextureFlagIsLoading = 1,
		/// Forces the texture to load. If no .raster exists, this will look for rw4 as well
		kTextureFlagForceLoad = 2,
		/// If enabled, SetLOD() will be called to the texture with the current level of detail
		kTextureFlagSetLOD = 4,
		/// Tells that the texture has been modified and the changes have not been saved
		kTextureFlagModified = 8,
	};

	/// High level representation of a game texture. Interaction with this class is done
	/// through the TextureManager; textures are identified using an instance ID and group ID (there is also type ID,
	/// but it is often defaulted to `.raster` and ignored).
	/// The low level equivalent is RenderWare::Raster, which can be used to load the texture into shaders and materials.
	class Texture
	{
	public:
		int AddRef();
		int Release();

		/// Returns the underlying raster of this texture, which can be used to load it into shaders and materials.
		/// @returns
		RenderWare::Raster* GetRaster();

		/// Returns the underlying raster of this texture, waiting until the texture finishes loading if
		/// it is still loading asynchronously (so this will always return the final raster, and not temporary ones).
		/// @returns
		RenderWare::Raster* GetLoadedRaster();

		/// Returns true if the texture is fully loaded, false if it is still loading.
		/// @returns
		bool IsLoaded();

	protected:
		/* 00h */	RenderWare::Raster* mpRaster;
		/* 04h */	int mFlags;
		/* 08h */	int mnRefCount;   // ?
		/* 0Ch */	int field_0C;
		/* 10h */	ResourceKey mName;
		/* 1Ch */	cRwRasterDirectResourcePtr mpResource;
		//TODO more things , cJob
	};



	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	inline int Texture::AddRef()
	{
		return mnRefCount++;
	}
	inline int Texture::Release()
	{
		// for some reason, it does not delete itself
		if (mnRefCount-- < 1)
		{
			mnRefCount = 1;
		}

		return mnRefCount;
	}

	inline RenderWare::Raster* Texture::GetRaster() {
		return mpRaster;
	}

	inline bool Texture::IsLoaded() {
		return (mFlags & kTextureFlagIsLoading) == 0;
	}
}