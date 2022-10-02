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

#include <Spore\Graphics\Texture.h>

#include <Spore\Internal.h>

/// Access the active texture manager.
#define TextureManager (*Graphics::ITextureManager::Get())

#define ITextureManagerPtr intrusive_ptr<Graphics::ITextureManager>

namespace Graphics
{
	class ITextureManager
	{
	public:
		enum
		{
			/// Forces the texture to load. If no .raster exists, this will look for rw4 as well
			kForceLoad = 2,
			/// If enabled, SetLOD() will be called to the texture with the current level of detail
			kSetLOD = 4
		};

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~ITextureManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;

		/* 10h */	virtual bool func10h() = 0;
		/* 14h */	virtual void func14h() = 0;  // lots of arguments, probably an struct
		/* 18h */	virtual int EvictManagedResources() = 0;

		///
		/// Gets the texture stored with the given file name. If the texture is not already loaded, it will be loaded in this method.
		/// The type ID will be ignored; generally it tries to load `.raster` textures.
		///
		/// In order to load textures that are not `.raster`, you must pass `kForceLoad` as a parameter.
		/// @param name
		/// @param flags
		/// @returns
		/* 1Ch */	virtual Texture* GetTexture(const struct ResourceKey name, int flags = 0) = 0;  // flags = 6 for rw4?

		///
		/// Same as GetTexture().
		/// @param instanceID
		/// @param groupID
		/// @param arg_8
		/// @returns
		/* 20h */	virtual Texture* GetRasterTexture(uint32_t instanceID, uint32_t groupID, char arg_8 = 0) = 0;

		///
		/// Tells whether a texture with this name is loaded in this manager, or a .raster texture exists with this name.
		/// @param name The name of the texture. The type ID will be ignored.
		/// @returns
		/* 24h */	virtual bool HasTexture(const struct ResourceKey name) const = 0;

		///
		/// Same as HasTexture().
		/// @param instanceID
		/// @param groupID
		/// @returns
		/* 28h */	virtual bool HasRasterTexture(uint32_t instanceID, uint32_t groupID) const = 0;

		///
		/// Returns the ResourceKey name of the given Texture. The type ID might be irrelevant.
		/// @param pTexture The Texture whose name will be returned.
		/// @returns
		/* 2Ch */	virtual ResourceKey GetTextureName(const Texture* pTexture) const = 0;

		/* 30h */	virtual int func30h(Texture* texture) = 0;
		/* 34h */	virtual bool func34h(Texture* texture) = 0;
		/* 38h */	virtual bool func38h(Texture* texture, void* arg_4) = 0;

		/* 3Ch */	virtual Texture* CreateTexture(uint32_t intanceID, uint32_t groupID, int width, int height, int mipmapLevels, int flags, D3DFORMAT format, int) = 0;
		/* 40h */	virtual int func40h(int, int, int, int, int, int) = 0;
		//PLACEHOLDER save texture?
		/* 44h */	virtual bool func44h(Texture* texture, int, int) = 0;
		/* 48h */	virtual int func48h(int, int) = 0;
		/* 4Ch */	virtual Texture* AddTextureFromRaster(uint32_t instanceID, uint32_t groupID, Raster* pRaster, int) = 0;
		/* 50h */	virtual int func50h(int, int, int, int) = 0;
		/* 54h */	virtual void func54h(Texture* texture, bool) = 0;
		/* 58h */	virtual bool func58h(int, int, int, int) = 0;
		/* 5Ch */	virtual bool func5Ch(Texture* texture, int, int, int) = 0;
		/* 60h */	virtual bool func60h(const struct ResourceKey name) = 0;
		/* 64h */	virtual bool func64h(uint32_t instanceID, uint32_t groupID) = 0;
		/* 68h */	virtual bool func68h(Texture* texture) = 0;
		/* 6Ch */	virtual void func6Ch(int) = 0;
		/* 70h */	virtual void func70h(int) = 0;
		/* 74h */	virtual int func74h() = 0;
		/* 78h */	virtual void func78h(int) = 0;

		///
		/// Returns the active texture manager.
		///
		static ITextureManager* Get();
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(ITextureManager)
	{
		DeclareAddress(Get);
	}
}
