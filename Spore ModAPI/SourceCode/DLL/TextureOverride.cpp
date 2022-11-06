#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include "TextureOverride.h"
#include <Spore\Cheats.h>
#include <Spore\CommonIDs.h>
#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\cModelInstance.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <Spore\App\PropertyList.h>
#include <EASTL\map.h>

const uint32_t kOverridePropertyIDs[] = {
	id("modelTexturesLODHi"),
	id("modelTexturesLOD0"),
	id("modelTexturesLOD1"),
	id("modelTexturesLOD2"),
	id("modelTexturesLOD3"),
};
const uint32_t kOverrideKeysPropertyIDs[] = {
	id("modelTexturesLODHiKeys"),
	id("modelTexturesLOD0Keys"),
	id("modelTexturesLOD1Keys"),
	id("modelTexturesLOD2Keys"),
	id("modelTexturesLOD3Keys"),
};

bool UsesOverride(RenderWare::RenderWareFile* renderWare) {
	for (size_t i = 0; i < renderWare->mpHeader->mnSectionCount; ++i) {
		auto info = renderWare->mpHeader->mpSectionInfos[i];
		if (info.typeCode == 0x20008) return true;
	}
	return false;
}

class ReplacedModelInstance
	: public Graphics::cModelInstance
{
public:
	~ReplacedModelInstance() {
		for (auto m : mMaterials) {
			for (int i = 0; i < m->statesCount; ++i) {
				_aligned_free(m->states[i]);
				m->states[i] = nullptr;
			}
			m->statesCount = 0;
		}
	}
};

Graphics::cModelInstance* CopyMesh(Graphics::cModelInstance* mesh) {
	Graphics::cModelInstance* copy = new Graphics::cModelInstance();
	copy->mMeshes = mesh->mMeshes;
	copy->field_1C = mesh->field_1C;
	copy->mMaterialInfos = mesh->mMaterialInfos;
	copy->mRegionMaterialInfos = mesh->mRegionMaterialInfos;
	copy->field_70 = mesh->field_70;
	copy->mBoundingBox = mesh->mBoundingBox;
	copy->mBoundingRadius = mesh->mBoundingRadius;
	copy->mpRenderWare = mesh->mpRenderWare;
	copy->field_C8 = mesh->field_C8;
	copy->field_CC = mesh->field_CC;
	copy->field_D0 = mesh->field_D0;
	copy->field_D4 = mesh->field_D4;
	copy->field_EC = mesh->field_EC;
	copy->mpAnimations = mesh->mpAnimations;
	copy->field_F4 = mesh->field_F4;
	copy->field_F8 = mesh->field_F8;
	copy->field_FC = mesh->field_FC;

	for (auto material : mesh->mMaterials) {
		if (material->states[0]) {
			int size = material->states[0]->instancedSize;
			void* buffer = _aligned_malloc(size, 16);
			memcpy_s(buffer, size, material->states[0], size);
			uint32_t id = MaterialManager.AssignRWMaterial((RenderWare::CompiledState*)buffer, mesh->mpRenderWare.get());
			copy->mMaterials.push_back(MaterialManager.GetMaterial(id));
		}
	}
	return copy;
}

bool ApplyOverride(Graphics::cMWModelInternal* asset, cModelInstancePtr& mesh, int lod) {
	auto propList = asset->mpPropList.get();
	uint32_t propertyID = kOverridePropertyIDs[lod + 1];
	uint32_t propertyKeysID = kOverrideKeysPropertyIDs[lod + 1];

	bool hasPropOverride = propList->HasProperty(propertyID) && propList->HasProperty(propertyKeysID);
	if (!mesh) {
		if (hasPropOverride) {
			App::ConsolePrintF("0x%x!0x%x.prop error: tried to apply texture override to inexistent LOD%i",
				propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod);
			return false;
		}
		return true;
	}
	if (lod != 0 && !hasPropOverride) {
		propertyID = kOverridePropertyIDs[1];
		propertyKeysID = kOverrideKeysPropertyIDs[1];
		hasPropOverride = propList->HasProperty(propertyID) && propList->HasProperty(propertyKeysID);
	}
	if (!mesh->mpRenderWare || mesh->mpRenderWare->GetResourceKey().typeID != TypeIDs::rw4) {
		if (hasPropOverride) {
			App::ConsolePrintF("0x%x!0x%x.prop error: tried to apply texture override to LOD%i, which does not use RW4",
				propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod);
			return false;
		}
		return true;
	}
	if (UsesOverride(mesh->mpRenderWare.get())) {
		if (!hasPropOverride) {
			App::ConsolePrintF("0x%x!0x%x.prop error: LOD%i override not specified, but model requires it",
				propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod);
			return false;
		}

		string8* overrideNames;
		size_t overrideCount;
		App::Property::GetArrayString8(propList, propertyID, overrideCount, overrideNames);

		ResourceKey* overrideKeys;
		size_t overrideCount2;
		App::Property::GetArrayKey(propList, propertyKeysID, overrideCount2, overrideKeys);

		if (overrideCount != overrideCount2) {
			App::ConsolePrintF("0x%x!0x%x.prop error: texture override incorrectly defined for LOD%i",
				propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod);
			return false;
		}

		map<string, ResourceKey> overrides;
		for (size_t i = 0; i < overrideCount; ++i) {
			overrides[overrideNames[i]] = overrideKeys[i];
		}

		// We don't know if the detoured method might be called more than once for the same model,
		// so maybe the cModelInstance here has already been altered and we don't need to duplicate it
		bool meshCopied = false;



		for (size_t m = 0; m < mesh->mMaterials.size(); ++m) {
			for (int i = 0; i < mesh->mMaterials[m]->statesCount; ++i) {
				auto state = mesh->mMaterials[m]->states[i];
				int textureFlags = state->hardStateDirty;
				for (int j = 0; j < 16; ++j) {
					if (!(textureFlags & 1)) continue;
					textureFlags >>= 1;
					RenderWare::Raster* raster = state->GetRaster(j);
					if (raster && raster->format == id("TextureOverride")) 
					{
						if (!meshCopied) {
							mesh = CopyMesh(mesh.get());
							state = mesh->mMaterials[m]->states[i];
							meshCopied = true;
						}

						char* name = ((char*)raster) + 4;

						auto it = overrides.find(string(name));
						if (it == overrides.end()) {
							App::ConsolePrintF("0x%x!0x%x.prop LOD%i error: no override found for texture slot \"%s\"",
								propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod, name);
							return false;
						}

						auto texture = TextureManager.GetTexture(it->second, 2);
						if (!texture) {
							App::ConsolePrintF("0x%x!0x%x.prop LOD%i error: texture 0x%x!0x%x does not exist",
								propList->GetResourceKey().groupID, propList->GetResourceKey().instanceID, lod, it->second.groupID, it->second.instanceID);
							return false;
						}

						state->SetRaster(j, texture->GetRaster());
						mesh->mMaterials[m]->textures.push_back(texture);
					}
				}
			}
		}
	}
	return true;
}

bool ApplyOverride(Graphics::Model* pModel) {
	if (pModel && pModel->mpPropList) {
		auto asset = static_cast<Graphics::cMWModelInternal*>(pModel);
		for (int i = 0; i < 4; ++i) {
			if (!ApplyOverride(asset, asset->mMeshLods[i], i)) {
				return false;
			}
		}
		ApplyOverride(asset, asset->mMeshLodHi, -1);
	}
	return true;
}


class Unk {};
member_detour(SetModel__detour, Unk, int(Graphics::Model**)) {
	int detoured(Graphics::Model** ppModel) {
		Graphics::Model* model = *ppModel;
		
		int result = original_function(this, ppModel);

		if (!ApplyOverride(model)) {
			auto asset = static_cast<Graphics::cMWModelInternal*>(model);
			asset->mMeshLods[0] = nullptr;
			asset->mMeshLods[1] = nullptr;
			asset->mMeshLods[2] = nullptr;
			asset->mMeshLods[3] = nullptr;
			asset->mMeshLodHi = nullptr;
			asset->mMeshHull = nullptr;
		}

		return result;
	}
};

member_detour(SetModel2__detour, Unk, void(App::PropertyList*, Graphics::cMWModelInternal*, int)) {
	void detoured(App::PropertyList* propList, Graphics::cMWModelInternal* pAsset, int flags) {
		Graphics::Model* model = static_cast<Graphics::Model*>(pAsset);

		original_function(this, propList, pAsset, flags);

		if (!ApplyOverride(model)) {
			auto asset = static_cast<Graphics::cMWModelInternal*>(model);
			asset->mMeshLods[0] = nullptr;
			asset->mMeshLods[1] = nullptr;
			asset->mMeshLods[2] = nullptr;
			asset->mMeshLods[3] = nullptr;
			asset->mMeshLodHi = nullptr;
			asset->mMeshHull = nullptr;
		}
	}
};

long TextureOverride::AttachDetour() {
	long result = 0;
	result |= SetModel__detour::attach(Address(SelectAddress(0x7523E0, , 0x7515D0)));
	result |= SetModel2__detour::attach(Address(SelectAddress(0x74B7C0, , 0x74A990)));
	return result;
}

#endif