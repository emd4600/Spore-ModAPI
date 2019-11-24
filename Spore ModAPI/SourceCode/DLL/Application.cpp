#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include "Application.h"
#include <Spore\ArgScript\FormatParser.h>
#include <detours.h>

bool ShaderFragments_detour::DETOUR(DatabasePackedFile* pDBPF)
{
	pDBPF = Resource::ResourceManager()->GetDBPF(
		ResourceKey(mShaderPath, Graphics::IMaterialManager::kSporeMaterialTypeID, Graphics::IMaterialManager::kShaderFragmentsGroupID));

	return original_function(this, pDBPF);
}

void LoadMaterials(uint32_t, void*, void*) {
	StandardFileFilter filter;
	filter.groupID = IMaterialManager::kShadersGroupID;
	filter.typeID = TypeIDs::smt;

	vector<ResourceKey> keys;
	if (ResourceManager()->GetFileKeys(keys, &filter)) {
		for (const ResourceKey& key : keys) {
			// Don't read the Spore ones, from 0 to 3
			if (key.instanceID > 3) {
				if (IMaterialManager::ReadCompiledShaders(key.instanceID)) {
					App::ConsolePrintF("Loaded shaders 0x%x", key.instanceID);
				}
				else {
					App::ConsolePrintF("Error loading shaders 0x%x", key.instanceID);
				}
			}
		}
	}

	keys.clear();

	filter.groupID = IMaterialManager::kCompiledStatesLinkGroupID;
	filter.typeID = TypeIDs::smt;

	if (ResourceManager()->GetFileKeys(keys, &filter)) {
		for (const ResourceKey& key : keys) {
			// Don't read the Spore ones, from 0 to 3
			if (key.instanceID > 3) {
				if (IMaterialManager::ReadMaterials(key.instanceID)) {
					App::ConsolePrintF("Loaded materials 0x%x", key.instanceID);
				}
				else {
					App::ConsolePrintF("Error loading materials 0x%x", key.instanceID);
				}
			}
		}
	}
}

namespace ModAPI
{
	fixed_vector<InitFunction, MAX_MODS> initFunctions;
	fixed_vector<InitFunction, MAX_MODS> postInitFunctions;
	fixed_vector<InitFunction, MAX_MODS> disposeFunctions;

	long AttachDetour()
	{
		long result = 0;
		result |= ShaderFragments_detour::attach(GetAddress(cMaterialManager, ReadShaderFragments));
		result |= sub_7E6C60_detour::attach(Address(SelectAddress(0x7E6C60, 0x7E67E0, 0x7E6850)));
		result |= AppInit_detour::attach(Address(SelectAddress(0xF48230, , 0xF47E90)));
		result |= AppShutdown_detour::attach(Address(SelectAddress(0xF47950, , 0xF475A0)));
		return result;
	}

	void DetachDetour() {
		ShaderFragments_detour::detach();
		sub_7E6C60_detour::detach();
		AppInit_detour::detach();
		AppShutdown_detour::detach();
	}
}

int ModAPI::sub_7E6C60_detour::DETOUR(int arg_0)
{
	int result = original_function(this, arg_0);

	for (ModAPI::InitFunction& func : ModAPI::initFunctions) func();

	return result;
}

int ModAPI::AppInit_detour::DETOUR(int arg_0)
{
	int result = original_function(this, arg_0);

	for (ModAPI::InitFunction& func : ModAPI::postInitFunctions) func();

	return result;
}

int ModAPI::AppShutdown_detour::DETOUR()
{
	for (int i = ModAPI::disposeFunctions.size() - 1; i >= 0; --i) ModAPI::disposeFunctions[i]();

	return original_function(this);
}

#endif
