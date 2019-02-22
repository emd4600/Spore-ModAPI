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

#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\RenderWare\CompiledState.h>
#include <Spore\Resource\IResourceManager.h>

#include <Spore\IO\StreamAdapter.h>

namespace Graphics
{

	auto_STATIC_METHOD_(IMaterialManager, IMaterialManager*, Get);

	auto_STATIC_METHOD(MaterialShader, MaterialShader*, Initialize,
		PARAMS(MaterialShader* dst, uint32_t shaderID, int arg_8, int arg_C, int arg_10, int arg_14, int arg_18, int arg_1C, int arg_20),
		PARAMS(dst, shaderID, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, arg_20));

	auto_STATIC_METHOD(MaterialShader, MaterialShader*, GetMaterialShader, PARAMS(uint32_t materialID), PARAMS(materialID));

	auto_METHOD(MaterialShader, bool, ReadStandard, PARAMS(IO::IStream* pStream, uint32_t shaderID, int version),
		PARAMS(pStream, shaderID, version));

	auto_METHOD_VOID_(MaterialShader, Reset);

	int MaterialShader::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}
	auto_METHOD_(MaterialShader, int, Release);

	MaterialShader::MaterialShader()
	{
		VOID_THISCALL(GetMethodAddress(MaterialShader, ctor), this);
	}

	bool IMaterialManager::ReadCompiledShaders(uint32_t instanceID) {
		using namespace Resource;

		auto fileKey = ResourceKey(instanceID, IMaterialManager::kSporeMaterialTypeID, IMaterialManager::kCompiledShadersGroupID);
		auto dbpf = ResourceManager()->GetDBPF(fileKey);

		if (!dbpf) return false;

		IPFRecord* record;
		if (!dbpf->GetFile(fileKey, &record)) return false;

		return ReadCompiledShaders(record->GetStream());
	}

	bool IMaterialManager::ReadCompiledShaders(IO::IStream* pStream) {
		auto mgr = (cMaterialManager*) IMaterialManager::Get();
		return mgr->ReadCompiledShadersImpl(pStream);
	}

	bool cMaterialManager::ReadCompiledShadersImpl(IO::IStream* pStream) 
	{
		int version;
		IO::ReadInt32(pStream, &version);

		if (version > 7) return false;

		int count;
		IO::ReadInt32(pStream, &count);

		//field_10.mStandardShaders.clear();
		//field_10.mStandardShaders.reserve(count);

		for (int i = 0; i < count; ++i) {
			uint32_t shaderID;
			IO::ReadUInt32(pStream, &shaderID);

			MaterialShader* pShader;
			auto it = field_10.mStandardShadersMap.find(shaderID);
			if (it != field_10.mStandardShadersMap.cend()) {
				pShader = it->second.get();
				pShader->Reset();
			}
			else {
				pShader = new MaterialShader();
				if (shaderID < 0x70000000 || shaderID > 0x80000000) {
					field_10.mStandardShadersMap[shaderID] = pShader;
				}
			}

			pShader->ReadStandard(pStream, shaderID, version);

			field_10.mStandardShaders.push_back(pShader);
		}

		return true;
	}

	bool IMaterialManager::ReadMaterials(uint32_t instanceID) {
		using namespace Resource;
		using namespace RenderWare;

		ResourceObject* pRenderWare;
		auto rwKey = ResourceKey(instanceID, RenderWareFile::TYPE, IMaterialManager::kCompiledStatesGroupID);
		if (!ResourceManager()->GetResource(rwKey, &pRenderWare)) return false;

		auto dbpf = ResourceManager()->GetDBPF(rwKey);

		IPFRecord* record;
		if (!dbpf->GetFile(ResourceKey(instanceID, IMaterialManager::kSporeMaterialTypeID, IMaterialManager::kCompiledStatesLinkGroupID), &record)) {
			return false;
		}

		auto mgr = (cMaterialManager*)IMaterialManager::Get();
		return mgr->ReadMaterialsImpl(record->GetStream(), object_cast<RenderWareFile>(pRenderWare));
	}

	using namespace RenderWare;
	bool cMaterialManager::ReadMaterialsImpl(IO::IStream* pStream, RenderWareFile* pRenderWare)
	{

		this->mMaterialsMutex.Lock(Mutex::kDefaultWait);

		bool result = false;

		int version;
		IO::ReadInt32(pStream, &version);

		if (version == 0) {
			uint32_t materialID;
			IO::ReadUInt32(pStream, &materialID);
			result = true;

			int index = 0;

			while (materialID != 0xFFFFFFFF) {
				Material& material = this->mMaterials[materialID];
				material.materialID = materialID;

				IO::ReadUInt8(pStream, &material.mnCompiledStates);
				uint8_t textureCount;
				IO::ReadUInt8(pStream, &textureCount);

				material.mTextures.clear();
				material.mTextures.resize(textureCount);

				for (int i = 0; i < textureCount; ++i) {
					uint32_t instanceID, groupID;
					IO::ReadUInt32(pStream, &instanceID);
					IO::ReadUInt32(pStream, &groupID);

					material.mTextures[i] = TextureManager()->GetRasterTexture(instanceID, groupID);
				}

				for (int i = 0; i < material.mnCompiledStates; ++i) {
					RWObjectQuery query;
					pRenderWare->mpHeader->GetRWObject(index, query);
					if (query.typeCode == CompiledState::TYPE) {
						material.mCompiledStates[i] = (CompiledState*)query.pData;
					}
					++index;
				}

				if (!material.mTextures.empty()) {
					++material.mnRefCount;
				}

				IO::ReadUInt32(pStream, &materialID);
			}
		}

		this->mMaterialsMutex.Unlock();
		return result;
	}

	int Material::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}
	int Material::Release()
	{
		--mnRefCount;
		// does not use destructor?
		return mnRefCount;
	}
}