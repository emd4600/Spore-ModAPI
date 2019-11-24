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

namespace Graphics
{
	class ITextureManager
	{
	public:

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~ITextureManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;

		/* 10h */	virtual bool func10h() = 0;
		/* 14h */	virtual void func14h() = 0;  // lots of arguments, probably an struct
		/* 18h */	virtual int EvictManagedResources() = 0;

		///
		/// Gets the texture stored with the given file name. If the texture is not already loaded, it will be loaded in this method.
		/// The type ID will be ignored; first, it will try to load it as a .raster texture, and if it's not found, it will use the rest of texture formats.
		/// @param name
		///
		/* 1Ch */	virtual Texture* GetTexture(const struct ResourceKey name, char arg_C = 0) = 0;  // arg_C = 6 for rw4?

		///
		/// Same as GetTexture().
		/// @param instanceID
		/// @param groupID
		///
		/* 20h */	virtual Texture* GetRasterTexture(uint32_t instanceID, uint32_t groupID, char arg_8 = 0) = 0;

		///
		/// Tells whether a texture with this name is loaded in this manager, or a .raster texture exists with this name.
		/// @param name The name of the texture. The type ID will be ignored.
		///
		/* 24h */	virtual bool HasTexture(const struct ResourceKey name) const = 0;

		///
		/// Same as HasTexture().
		/// @param instanceID
		/// @param groupID
		///
		/* 28h */	virtual bool HasRasterTexture(uint32_t instanceID, uint32_t groupID) const = 0;

		///
		/// Returns the ResourceKey name of the given Texture. The type ID might be irrelevant.
		/// @param pTexture The Texture whose name will be returned.
		///
		/* 2Ch */	virtual ResourceKey GetTextureName(const Texture* pTexture) const = 0;

		/* 30h */	virtual int func30h(Texture* texture) = 0;
		/* 34h */	virtual bool func34h(Texture* texture) = 0;
		/* 38h */	virtual bool func38h(Texture* texture, void* arg_4) = 0;

		/* 3Ch */	virtual int func3Ch(int, int, int, int, int, int, int, int) = 0;
		/* 40h */	virtual int func40h(int, int, int, int, int, int) = 0;
		/* 44h */	virtual bool func44h(Texture* texture, int, int) = 0;
		/* 48h */	virtual int func48h(int, int) = 0;
		/* 4Ch */	virtual int func4Ch(int, int, int, int) = 0;
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
		/// Returns the active texture manager. Same as TextureManager().
		///
		static ITextureManager* Get();
	};

	///
	/// Returns the active texture manager. Same as ITextureManager::Get().
	///
	inline ITextureManager* TextureManager()
	{
		return ITextureManager::Get();
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(ITextureManager)
	{
		DeclareAddress(Get);
	}
}
