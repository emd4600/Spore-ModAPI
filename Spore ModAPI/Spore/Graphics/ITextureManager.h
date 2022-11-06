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
#include <Spore\Graphics\cImageDataRaw.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\App\cJob.h>
#include <Spore\Internal.h>

/// Easy access to Graphics::ITextureManager
#define TextureManager (*Graphics::ITextureManager::Get())

#define ITextureManagerPtr eastl::intrusive_ptr<Graphics::ITextureManager>

namespace Graphics
{
	class ITextureManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~ITextureManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual void Update() = 0;
		/* 18h */	virtual int EvictManagedResources() = 0;

		/// Gets the texture stored with the given file name. If the texture is not already loaded, it will be loaded in this method.
		/// The type ID will be ignored; generally it tries to load `.raster` textures.
		///
		/// In order to load textures that are not `.raster`, you must pass `kForceLoad` as a parameter.
		/// @param name
		/// @param flags
		/// @returns
		/* 1Ch */	virtual Texture* GetTexture(const struct ResourceKey name, int flags = 0) = 0;  // flags = 6 for rw4?

		/// Same as GetTexture().
		/// @param instanceID
		/// @param groupID
		/// @param arg_8
		/// @returns
		/* 20h */	virtual Texture* GetRasterTexture(uint32_t instanceID, uint32_t groupID, char arg_8 = 0) = 0;

		/// Tells whether a texture with this name is loaded in this manager, or a .raster texture exists with this name.
		/// @param name The name of the texture. The type ID will be ignored.
		/// @returns
		/* 24h */	virtual bool HasTexture(const struct ResourceKey name) const = 0;

		/// Same as HasTexture().
		/// @param instanceID
		/// @param groupID
		/// @returns
		/* 28h */	virtual bool HasRasterTexture(uint32_t instanceID, uint32_t groupID) const = 0;

		/// Returns the ResourceKey name of the given Texture. The type ID might be irrelevant.
		/// @param pTexture The Texture whose name will be returned.
		/// @returns
		/* 2Ch */	virtual ResourceKey GetTextureName(const Texture* pTexture) const = 0;

		/// Returns the resource object for a given texture, which can be used to read and write the texture into a file.
		/// @param texture
		/// @returns
		/* 30h */	virtual cRwRasterDirectResource* GetRasterResource(Texture* texture) = 0;

		/// Waits (blocks execution) until a texture has completely loaded.
		/// @param texture
		/// @returns
		/* 34h */	virtual bool WaitForLoadInternal(Texture* texture) = 0;

		/// For textures that have to be loaded asynchronously, adds the texture loading as a dependency for a job
		/// (that is, the job won't execute until the texture finishes loading).
		/// @param texture
		/// @param job
		/// @returns
		/* 38h */	virtual bool AddTextureLoadDependency(Texture* texture, App::cJob* job) = 0;

		/// Creates a new raster texture and adds it to the raster manager, referenced by the given group and instance IDs.
		/// @param instanceID
		/// @param groupID
		/// @param width
		/// @param height
		/// @param mipmapLevels
		/// @param flags
		/// @param format
		/// @returns The new created texture.
		/* 3Ch */	virtual Texture* CreateTexture(uint32_t intanceID, uint32_t groupID, int width, int height, int mipmapLevels, int flags, D3DFORMAT format, int=0) = 0;

		/// Generates an automatic instance ID for group ID 0x40002200 and type ID `.raster`, then 
		/// creates a new raster texture and adds it to the raster manager, referenced by the given group and instance IDs.
		/// @param instanceID
		/// @param groupID
		/// @param width
		/// @param height
		/// @param mipmapLevels
		/// @param flags
		/// @param format
		/// @returns The new created texture.
		/* 40h */	virtual Texture* CreateTextureAutoKey(int width, int height, int mipmapLevels, int flags, D3DFORMAT format, int) = 0;
		
		/// Saves a texture into the given Resource::DBPF package, as a `.raster` file (it will use
		/// the `.raster` type ID regardless of the texture key)
		/// @param texture
		/// @param pDBPF
		/// @param async If true, texture will be saved asynchronously 
		/* 44h */	virtual bool WriteTexture(Texture* texture, Resource::DBPF* pDBPF, bool async) = 0;

		/// Generates an automatic instance ID for group ID 0x40002200 and type ID `.raster`, then 
		/// adds the given raster with that name to the manager.
		/// @param pRaster
		/// @param flags
		/// @returns The Texture object for the raster
		/* 48h */	virtual Texture* AddRasterAutoKey(RenderWare::Raster* pRaster, int flags = 0) = 0;

		/// Adds the given raster to the manager, where it can be obtained again using the group and instance IDs specified.
		/// @param instanceID
		/// @param groupID
		/// @param pRaster
		/// @param flags
		/// @returns The Texture object for the raster
		/* 4Ch */	virtual Texture* AddRaster(uint32_t instanceID, uint32_t groupID, RenderWare::Raster* pRaster, int flags = 0) = 0;

		/// Creates a new Texture that references the same underlying RenderWare::Raster as the given texture.
		/// @param instanceID
		/// @param groupID
		/// @param pTexture
		/// @param flags
		/// @returns The new Texture object
		/* 50h */	virtual Texture* CopyTextureAsReference(uint32_t instanceID, uint32_t groupID, Texture* pTexture, int flags = 0) = 0;

		/// Marks the given texture as (not) modified.
		/// @param texture
		/// @param modified
		/* 54h */	virtual void SetTextureModified(Texture* texture, bool modified) = 0;

		/// Extracts the raw contents of a raster texture.
		/// @param pRaster The source texture
		/// @param dst Pointer where the extracted data will be created
		/// @param async If true, extract asynchronously, in the background; if false, block the execution until extraction is complete.
		/// @param messageID For async extraction, ID of message sent when extraction has finished (defaults to `0x522264D`)
		/// @returns
		/* 58h */	virtual bool ExtractTextureRaster(RenderWare::Raster* pRaster, cImageDataRawPtr& dst, bool async, uint32_t messageID = 0) = 0;

		/// Extracts the raw contents of a texture.
		/// @param texture The source texture
		/// @param dst Pointer where the extracted data will be created
		/// @param async If true, extract asynchronously, in the background; if false, block the execution until extraction is complete.
		/// @param messageID For async extraction, ID of message sent when extraction has finished (defaults to `0x522264D`)
		/// @returns
		/* 5Ch */	virtual bool ExtractTexture(Texture* texture, cImageDataRawPtr& dst, bool async, uint32_t messageID = 0) = 0;

		/// Calls ReloadTexture() for the texture with the given key (type ID is ignored).
		/// @param name
		/// @returns
		/* 60h */	virtual bool ReloadTextureByKey(const struct ResourceKey name) = 0;
		
		/// Calls ReloadTexture() for the texture with the given group and instance IDs.
		/// It actually calls ReloadTextureByKey() with a `.raster` typeID, but that function ignores typeID, so it doesn't matter.
		/// @param instanceID
		/// @param groupID
		/// @returns
		/* 64h */	virtual bool ReloadTextureByID(uint32_t instanceID, uint32_t groupID) = 0;

		/// Reloads the texture by reading it from its file again.
		/// Removes the RasterResourceObject of the given texture and loads it from the resource manager again,
		/// using the same ResourceKey.
		/// @param texture
		/* 68h */	virtual bool ReloadTexture(Texture* texture) = 0;

		/// Adds all the textures from the given RW4 file (all the RenderWare::Raster sections).
		/// @param pRenderWare
		/* 6Ch */	virtual void RegisterRenderWareContents(RenderWare::RenderWareFile* pRenderWare) = 0;

		/// Removes all the textures that are contained in the given RW4 file.
		/// @param pRenderWare
		/* 70h */	virtual void UnregisterRenderWareContents(RenderWare::RenderWareFile* pRenderWare) = 0;

		/* 74h */	virtual int func74h() = 0;  // does nothing
		/* 78h */	virtual void func78h(int) = 0;  // does nothing

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
