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
#include <Spore\Resource\Database.h>
#include <Spore\RenderWare\CompiledState.h>
#include <Spore\RenderWare\RenderWareFile.h>

#include <EASTL\vector.h>
#include <EASTL\intrusive_ptr.h>

/// Access the active material manager.
#define MaterialManager (*Graphics::IMaterialManager::Get())

#define MaterialPtr eastl::intrusive_ptr<Graphics::Material>
#define IMaterialManagerPtr eastl::intrusive_ptr<Graphics::IMaterialManager>

namespace Graphics
{
	///
	/// Represents a material that controls the visual appearance of game objects.
	/// Materials contain one to four CompiledState objects, as well as any number of textures.
	/// Materials are identified using an ID.
	///
	class Material
	{
	public:
		inline RenderWare::CompiledState* GetState() { return states[0]; }

	public:
		/* 00h */	uint8_t statesCount;
		/* 04h */	RenderWare::CompiledState* states[4];
	private:
		/* 14h */	int mnRefCount;
	public:
		/* 18h */	uint32_t materialID;
		/* 1Ch */	int field_1C;  // RenderAsset ? RenderWareFile?
		/* 20h */	eastl::vector<TexturePtr>  textures;
		/* 34h */	char field_34[0x14];  // ?

		int AddRef();
		int Release();
	};
	ASSERT_SIZE(Material, 0x48);

	///
	/// This manager stores the information of materials, which are used to control the visual appearance of game objects.
	/// Materials are mapped in this manager using an ID, and they link to one or multiple CompiledState and Texture objects.
	/// For more information, check the Material class.
	///
	class IMaterialManager
	{
	public:
		enum
		{
			kCompiledStatesLinkGroupID = 0x40212000,
			kCompiledStatesGroupID = 0x40212001,
			kShaderFragmentsGroupID = 0x40212002,
			kShadersGroupID = 0x40212004,
			kSporeMaterialTypeID = 0x0469A3F7
		};

		/* 00h */	virtual void AddRef() = 0;
		/* 04h */	virtual void Release() = 0;
		/* 08h */	virtual ~IMaterialManager() = 0;

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual bool Update() = 0;
		/* 18h */	virtual void SetScriptFile(const char*) = 0;
		/* 1Ch */	virtual bool LoadMaterials() = 0;

		/* 20h */	virtual void HasMaterial2(uint32_t instanceID, uint32_t groupID) = 0;

		///
		/// Tells whether a material with this materialID is valid (that is, it has at least one compiled state). 
		/// If the materialID wasn't assigned to any material, it will return false.
		/// @param materialID The ID the material is assigned to.
		///
		/* 24h */	virtual bool HasMaterial(uint32_t materialID) = 0;

		///
		/// Gets the material assigned to the given ID. If no material exists with that ID, a new one will be created;
		/// therefore, this method always returns an object.
		/// @param materialID The ID the material is assigned to.
		///
		/* 28h */	virtual Material* GetMaterialInstance(uint32_t materialID) = 0;
		
		///
		/// Gets all the materials assigned to the IDs specified. If a certain ID does not have any material assigned,
		/// a new one will be created; therefore, this method always puts an object into the output array.
		/// @param[in] count The number of elements in the IDs array.
		/// @param[in] pMaterialIDs The IDs of the materials to get.
		/// @param[out] pDst A Material* array of nCount elements where the Material pointers will be written.
		///
		/* 2Ch */	virtual void GetMaterialInstances(size_t count, const uint32_t* pMaterialIDs, Material** pDst) = 0;


		/* 30h */	virtual Material* func30h(uint32_t, int) = 0;

		///
		/// Returns the ID of the given material.
		/// @param pMaterial
		///
		/* 34h */	virtual uint32_t GetIDFromMaterial(const Material* pMaterial) const = 0;

		/// Puts the ID of all the materials specified into the given array.
		/// @param[in] count The number of elements in the materials array.
		/// @param[in] pMaterials The materials whose ID will be got.
		/// @param[out] pDst A uint32_t array of nCount elements where the IDs will be written.
		/* 38h */	virtual void GetIDsFromMaterials(size_t count, const Material* const* pMaterials, uint32_t* pDst) const = 0;

		///
		/// Gets the textures used by a certain material. Optionally, a filter function can be specified to get only certain textures.
		/// @param[in] pMaterial The Material whose textures will be returned.
		/// @param[out] dst A vector where the textures will be output.
		/// @param[in] filterFunction [Optional] A filter function that takes a Texture* as a parameter and returns a bool, whether the texture must be added or not.
		///
		/* 3Ch */	virtual void GetTexturesFromMaterial(const Material* pMaterial, eastl::vector<TexturePtr>& dst, bool(*filterFunction)(Texture*) = nullptr) const = 0;

		// returns a material ID?
		/* 40h */	virtual uint32_t GetIDFromCompiledState(RenderWare::CompiledState*, RenderWare::RenderWareFile*) = 0;

		/* 44h */	virtual int WriteExternalReferences(int count, int* indices, IO::IStream* stream, eastl::vector<ResourceKey>* dstKeys) = 0;

		/* 48h */	virtual int ReadExternalReferences(IO::IStream* stream, int count, uint32_t* materialIDs, void** dstAutoListRC, const ResourceKey*) = 0;

		/* 4Ch */	virtual int GetExternalReferenceKeys(int count, int* indices, eastl::vector<ResourceKey>*& dstKeys, const ResourceKey*) = 0;

		/* 50h */	virtual void func50h(int) = 0;
		/* 54h */	virtual void UnregisterArenaContents(int) = 0;
		/* 58h */	virtual void func58h(int, int, int, int, int) = 0;
		/* 5Ch */	virtual bool WriteMaterials(Resource::Database* database) = 0;
		/* 60h */	virtual bool WriteFragments(Resource::Database* database) = 0;
		/* 64h */	virtual bool WriteShaders(Resource::Database* database) = 0;
		/* 68h */	virtual void ReleaseShaders() = 0;
		/* 6Ch */	virtual void RecreateShaders() = 0;
		/* 70h */	virtual void* GetScriptParser() = 0;
		/* 74h */	virtual void DumpNextFrame(int) = 0;
		/* 78h */	virtual bool ReadMaterials(Resource::Database* database) = 0;
		/* 7Ch */	virtual bool ReadFragments(Resource::Database* database) = 0;
		/* 80h */	virtual bool ReadShaders(Resource::Database* database) = 0;

		///
		/// Gets the active material manager.
		///
		static IMaterialManager* Get();

		static bool ReadCompiledShaders(uint32_t instanceID);
		static bool ReadCompiledShaders(IO::IStream* pStream);

		static bool ReadMaterials(uint32_t instanceID);
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IMaterialManager)
	{
		DeclareAddress(Get);
	}
}