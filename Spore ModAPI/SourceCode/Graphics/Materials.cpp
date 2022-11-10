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
#include <Spore\Graphics\CompiledShader.h>
#include <Spore\Graphics\StandardShader.h>
#include <Spore\Graphics\ShaderBuilder.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Graphics\RenderUtils.h>
#include <Spore\RenderWare\CompiledState.h>
#include <Spore\Resource\IResourceManager.h>

#include <Spore\IO\StreamAdapter.h>

namespace Graphics
{
	auto_STATIC_METHOD_(IMaterialManager, IMaterialManager*, Get);

	auto_STATIC_METHOD(StandardShader, BOOL, Load, Args(RenderWare::Mesh* mesh), Args(mesh));
	auto_STATIC_METHOD(ShaderBuilder, BOOL, Load, Args(RenderWare::Mesh* mesh), Args(mesh));

	auto_STATIC_METHOD(MaterialShader, MaterialShader*, Initialize,
		Args(MaterialShader* dst, uint32_t shaderID, int arg_8, int arg_C, int arg_10, int arg_14, int arg_18, int arg_1C, int arg_20),
		Args(dst, shaderID, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, arg_20));

	auto_STATIC_METHOD(MaterialShader, MaterialShader*, GetMaterialShader, Args(uint32_t materialID), Args(materialID));

	auto_METHOD(StandardShader, bool, Read, Args(IO::IStream* pStream, uint32_t shaderID, int version),
		Args(pStream, shaderID, version));

	auto_METHOD_VOID_(StandardShader, Reset);

	auto_METHOD(ShaderBuilder, bool, Read, Args(IO::IStream* pStream, uint32_t shaderID, int version),
		Args(pStream, shaderID, version));

	int MaterialShader::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}
	auto_METHOD_(StandardShader, int, Release);
	auto_METHOD_(ShaderBuilder, int, Release);

	StandardShader::StandardShader()
	{
		VOID_THISCALL(GetAddress(StandardShader, ctor), this);
	}

	ShaderBuilder::ShaderBuilder()
	{
		VOID_THISCALL(GetAddress(ShaderBuilder, ctor), this);
	}

	bool IMaterialManager::ReadCompiledShaders(uint32_t instanceID) {
		using namespace Resource;

		auto fileKey = ResourceKey(instanceID, IMaterialManager::kSporeMaterialTypeID, IMaterialManager::kShadersGroupID);
		auto dbpf = ResourceManager.GetDBPF(fileKey);

		if (!dbpf) return false;

		IPFRecord* record;
		if (!dbpf->OpenRecord(fileKey, &record)) return false;

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

		// We don't want to delete the existing ones!
		//field_10.mStandardShaders.clear();
		//field_10.mStandardShaders.resize(count);

		for (int i = 0; i < count; ++i) {
			uint32_t shaderID;
			IO::ReadUInt32(pStream, &shaderID);

			StandardShader* pShader;
			auto it = field_10.mStandardShadersMap.find(shaderID);
			if (it != field_10.mStandardShadersMap.cend()) {
				pShader = it->second.get();
				pShader->Reset();
			}
			else {
				pShader = new StandardShader();
				if (shaderID < 0x70000000 || shaderID > 0x80000000) {
					field_10.mStandardShadersMap[shaderID] = pShader;
				}
			}

			pShader->Read(pStream, shaderID, version);

			field_10.mStandardShaders.push_back(pShader);
		}

		IO::ReadInt32(pStream, &count);

		//field_10.mShaderBuilders.clear();
		//field_10.mShaderBuilders.resize(count);


		for (int i = 0; i < count; ++i) {
			uint32_t shaderID;
			IO::ReadUInt32(pStream, &shaderID);

			ShaderBuilder* pShader;
			auto it = field_10.mShaderBuildersMap.find(shaderID);
			if (it != field_10.mShaderBuildersMap.cend()) {
				pShader = it->second.get();
			}
			else {
				pShader = new ShaderBuilder();
				if (shaderID < 0x70000000 || shaderID > 0x80000000) {
					field_10.mShaderBuildersMap[shaderID] = pShader;
				}
			}

			pShader->Read(pStream, shaderID, version);

			field_10.mShaderBuilders.push_back(pShader);
		}

		ReadCompiledVertexShaders(pStream);
		ReadCompiledPixelShaders(pStream);

		return true;
	}

	bool IMaterialManager::ReadMaterials(uint32_t instanceID) {
		using namespace Resource;
		using namespace RenderWare;

		ResourceObjectPtr pRenderWare;
		auto rwKey = ResourceKey(instanceID, RenderWareFile::TYPE, IMaterialManager::kCompiledStatesGroupID);
		if (!ResourceManager.GetResource(rwKey, &pRenderWare)) return false;

		auto dbpf = ResourceManager.GetDBPF(rwKey);

		IPFRecord* record;
		if (!dbpf->OpenRecord(ResourceKey(instanceID, IMaterialManager::kSporeMaterialTypeID, IMaterialManager::kCompiledStatesLinkGroupID), &record)) {
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

				IO::ReadUInt8(pStream, &material.statesCount);
				uint8_t textureCount;
				IO::ReadUInt8(pStream, &textureCount);

				material.textures.clear();
				material.textures.resize(textureCount);

				for (int i = 0; i < textureCount; ++i) {
					uint32_t instanceID, groupID;
					IO::ReadUInt32(pStream, &instanceID);
					IO::ReadUInt32(pStream, &groupID);

					material.textures[i] = TextureManager.GetRasterTexture(instanceID, groupID);
				}

				for (int i = 0; i < material.statesCount; ++i) {
					RWObjectQuery query;
					pRenderWare->mpHeader->GetRWObject(index, query);
					if (query.typeCode == CompiledState::TYPE) {
						material.states[i] = (CompiledState*)query.pData;
					}
					++index;
				}

				if (!material.textures.empty()) {
					material.AddRef();
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

	template <typename T>
	CompiledShader<T>::CompiledShader()
		: mFragmentIndices()
		, mpDXShader(nullptr)
		, field_24()
		, mDataCount()
		, mShaderData()
		, mStartRegisters()
		, mDataFlags()
	{
	}

	void ReadCompiledVertexShaders(IO::IStream* pStream)
	{
		int count;
		IO::ReadInt32(pStream, &count);  // this is ignored
		IO::ReadInt32(pStream, &count);

		for (int i = 0; i < count; ++i)
		{
			VertexShader shader;
			
			pStream->Read(shader.mFragmentIndices, 32);

			int size = 0;
			IO::ReadInt32(pStream, &size);

			if (size) {
				char* data = new char[size];
				pStream->Read(data, size);
				RenderUtils::GetDevice()->CreateVertexShader((DWORD*)data, &shader.mpDXShader);
			}

			IO::ReadInt32(pStream, &shader.mDataCount);

			NamedShaderDataUniform** pPointers = (NamedShaderDataUniform**)GetAddress(Graphics, VertexShaderDataUniforms_ptr);
			NamedShaderDataUniform* data = *pPointers;
			*(pPointers + 1) = *pPointers = *pPointers + shader.mDataCount;

			for (int i = 0; i < shader.mDataCount; ++i) {
				IO::ReadInt16(pStream, &data->dataIndex);
				IO::ReadInt16(pStream, &data->field_12);
				IO::ReadInt16(pStream, &data->registerSize);
				IO::ReadInt16(pStream, &data->registerIndex);
				IO::ReadInt32(pStream, &data->flags);
				shader.mShaderData[i] = data;

				++data;
			}

			IO::ReadInt32(pStream, shader.mStartRegisters, shader.mDataCount);
			IO::ReadInt32(pStream, &shader.mDataFlags);

			GetVertexShaders().push_back(shader);
		}
	}

	void ReadCompiledPixelShaders(IO::IStream* pStream)
	{
		int count;
		IO::ReadInt32(pStream, &count);  // this is ignored
		IO::ReadInt32(pStream, &count);

		for (int i = 0; i < count; ++i)
		{
			PixelShader shader;

			pStream->Read(shader.mFragmentIndices, 32);

			int size = 0;
			IO::ReadInt32(pStream, &size);

			if (size) {
				char* data = new char[size];
				pStream->Read(data, size);
				RenderUtils::GetDevice()->CreatePixelShader((DWORD*)data, &shader.mpDXShader);
			}

			IO::ReadInt32(pStream, &shader.mDataCount);

			NamedShaderDataUniform** pPointers = (NamedShaderDataUniform**)GetAddress(Graphics, PixelShaderDataUniforms_ptr);
			NamedShaderDataUniform* data = *pPointers;
			*(pPointers + 1) = *pPointers = *pPointers + shader.mDataCount;

			for (int i = 0; i < shader.mDataCount; ++i) {
				IO::ReadInt16(pStream, &data->dataIndex);
				IO::ReadInt16(pStream, &data->field_12);
				IO::ReadInt16(pStream, &data->registerSize);
				IO::ReadInt16(pStream, &data->registerIndex);
				IO::ReadInt32(pStream, &data->flags);
				shader.mShaderData[i] = data;

				++data;
			}

			IO::ReadInt32(pStream, shader.mStartRegisters, shader.mDataCount);
			IO::ReadInt32(pStream, &shader.mDataFlags);

			GetPixelShaders().push_back(shader);
		}
	}
}
