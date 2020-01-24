#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include "Application.h"
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\IO.h>

bool ShaderFragments_detour::DETOUR(DatabasePackedFile* pDBPF)
{
	pDBPF = ResourceManager.GetDBPF(
		ResourceKey(mShaderPath, Graphics::IMaterialManager::kSporeMaterialTypeID, Graphics::IMaterialManager::kShaderFragmentsGroupID));

	return original_function(this, pDBPF);
}

void LoadMaterials(uint32_t, void*, void*) {
	StandardFileFilter filter;
	filter.groupID = IMaterialManager::kShadersGroupID;
	filter.typeID = TypeIDs::smt;

	vector<ResourceKey> keys;
	if (ResourceManager.GetFileKeys(keys, &filter)) {
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

	if (ResourceManager.GetFileKeys(keys, &filter)) {
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
	fixed_map<uint32_t, intrusive_ptr<Simulator::ISimulatorStrategy>, MAX_MODS> simulatorStrategies;

	long AttachDetour()
	{
		long result = 0;
		result |= ShaderFragments_detour::attach(GetAddress(cMaterialManager, ReadShaderFragments));
		result |= sub_7E6C60_detour::attach(Address(SelectAddress(0x7E6C60, 0x7E67E0, 0x7E6850)));
		result |= AppInit_detour::attach(Address(SelectAddress(0xF48230, , 0xF47E90)));
		result |= AppShutdown_detour::attach(Address(SelectAddress(0xF47950, , 0xF475A0)));

		//result |= PersistanceMan_Write_detour::attach(Address(SelectAddress(0xB26670, , PLACEHOLDER)));
		//result |= PersistanceMan_Read_detour::attach(Address(SelectAddress(0xB266B0, , PLACEHOLDER)));

		return result;
	}

	void DetachDetour() {
		// DetachDetour calls new, which causes crash since we are using the Spore one.

		/*ShaderFragments_detour::detach();
		sub_7E6C60_detour::detach();
		AppInit_detour::detach();
		AppShutdown_detour::detach();*/
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

	ModAPI::simulatorStrategies.clear();

	return original_function(this);
}


namespace ModAPI
{
	bool ReadSubsystems(Simulator::ISerializerStream* stream, void* data)
	{
		auto s = stream->GetRecord()->GetStream();

		int count;
		IO::ReadInt32(s, &count);

		vector<uint32_t> ids(count);
		vector<int> sizes(count);
		for (int i = 0; i < count; ++i) {
			IO::ReadUInt32(s, &ids[i]);
			IO::ReadInt32(s, &sizes[i]);
		}

		for (int i = 0; i < count; ++i) {
			auto it = simulatorStrategies.find(ids[i]);
			if (it == simulatorStrategies.end() || !it->second)
			{
				s->SetPosition(sizes[i], IO::kPositionTypeCurrent);
			}
			else
			{
				it->second->Read(stream);
			}
		}

		return true;
	}

	bool WriteSubsystems(Simulator::ISerializerStream* stream, void* data)
	{
		auto s = stream->GetRecord()->GetStream();

		int count = simulatorStrategies.size();
		IO::WriteInt32(s, &count);

		int originalOffset = s->GetPosition();

		vector<uint32_t> ids(count);
		vector<int> sizes(count);
		for (int i = 0; i < count; ++i) {
			IO::WriteUInt32(s, &ids[i]);
			IO::WriteInt32(s, &sizes[i]);
		}

		int i = 0;
		for (auto it : simulatorStrategies) {
			int offset = s->GetPosition();
			it.second->Write(stream);

			ids[i] = it.first;
			sizes[i] = s->GetPosition() - offset;
			++i;
		}

		int finalOffset = s->GetPosition();

		s->SetPosition(originalOffset);
		for (int i = 0; i < count; ++i) {
			IO::WriteUInt32(s, &ids[i]);
			IO::WriteInt32(s, &sizes[i]);
		}

		s->SetPosition(finalOffset);

		return true;
	}

	void EmptyReadText(const string& str, void* dst) {
	}
	void EmptyWriteText(char* buf, void* src) {
		buf[0] = '\0';
	}

	Simulator::Attribute ATTRIBUTES[] = {
		Simulator::Attribute("mSubSystems", 0x01001000, 0, &ReadSubsystems, &WriteSubsystems, &EmptyReadText, &EmptyWriteText, nullptr),
		Simulator::Attribute()
	};
}

bool ModAPI::PersistanceMan_Write_detour::DETOUR(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ModAPI::ATTRIBUTES).Write(stream);
}

bool ModAPI::PersistanceMan_Read_detour::DETOUR(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ModAPI::ATTRIBUTES).Read(stream);
}

#endif
