#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include "Application.h"
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\IO.h>

bool ShaderFragments_detour::DETOUR(Resource::Database* pDBPF)
{
	pDBPF = ResourceManager.FindDatabase(
		ResourceKey(mShaderPath, TypeIDs::smt, GroupIDs::ShaderFragments));

	return original_function(this, pDBPF);
}

void LoadMaterials() {
	Resource::StandardFileFilter filter;
	filter.groupID = GroupIDs::Shaders;
	filter.typeID = TypeIDs::smt;

	eastl::vector<ResourceKey> keys;
	if (ResourceManager.GetRecordKeyList(keys, &filter)) {
		for (const ResourceKey& key : keys) {
			// Don't read the Spore ones, from 0 to 3
			if (key.instanceID > 3) {
				if (Graphics::IMaterialManager::ReadCompiledShaders(key.instanceID)) {
					App::ConsolePrintF("Loaded shaders 0x%x", key.instanceID);
				}
				else {
					App::ConsolePrintF("Error loading shaders 0x%x", key.instanceID);
				}
			}
		}
	}

	keys.clear();

	filter.groupID = GroupIDs::CompiledStatesLink;
	filter.typeID = TypeIDs::smt;

	if (ResourceManager.GetRecordKeyList(keys, &filter)) {
		for (const ResourceKey& key : keys) {
			// Don't read the Spore ones, from 0 to 3
			if (key.instanceID > 3) {
				if (Graphics::IMaterialManager::ReadMaterials(key.instanceID)) {
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
	eastl::fixed_vector<InitFunction, MAX_MODS> initFunctions;
	eastl::fixed_vector<InitFunction, MAX_MODS> postInitFunctions;
	eastl::fixed_vector<InitFunction, MAX_MODS> disposeFunctions;
	eastl::fixed_map<uint32_t, ISimulatorStrategyPtr, MAX_MODS> simulatorStrategies;

	uint32_t CRC_TABLE[256];

	void GenerateCRCTable() {
		uint32_t polynomial = 0xEDB88320;
		for (uint32_t i = 0; i < 256; ++i) {
			uint32_t c = i;
			for (size_t j = 0; j < 8; ++j) {
				if (c & 1) {
					c = polynomial ^ (c >> 1);
				}
				else c >>= 1;
			}
			CRC_TABLE[i] = c;
		}
	}

	uint32_t CalculateCRC(uint32_t initial, const void* buf, size_t len)
	{
		uint32_t c = initial ^ 0xFFFFFFFF;
		const uint8_t* u = static_cast<const uint8_t*>(buf);
		for (size_t i = 0; i < len; ++i)
		{
			c = CRC_TABLE[(c ^ u[i]) & 0xFF] ^ (c >> 8);
		}
		return c ^ 0xFFFFFFFF;
	}

	long AttachDetour()
	{
		GenerateCRCTable();

		long result = 0;
		result |= ShaderFragments_detour::attach(GetAddress(Graphics::cMaterialManager, ReadShaderFragments));
		result |= sub_7E6C60_detour::attach(Address(SelectAddress(0x7E6C60, 0x7E6850)));
		result |= AppInit_detour::attach(Address(SelectAddress(0xF48230, 0xF47E90)));
		result |= AppShutdown_detour::attach(Address(SelectAddress(0xF47950, 0xF475A0)));

		result |= PersistanceMan_Write_detour::attach(Address(SelectAddress(0xB26670, 0xB267E0)));
		result |= PersistanceMan_Read_detour::attach(Address(SelectAddress(0xB266B0, 0xB26820)));

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

	LoadMaterials();
	for (ModAPI::InitFunction& func : ModAPI::postInitFunctions) func();

	return result;
}

int ModAPI::AppShutdown_detour::DETOUR()
{
	for (int i = ModAPI::disposeFunctions.size() - 1; i >= 0; --i) ModAPI::disposeFunctions[i]();

	for (auto it : ModAPI::simulatorStrategies) it.second->Dispose();
	ModAPI::simulatorStrategies.clear();

	return original_function(this);
}


namespace ModAPI
{
	bool ReadSubsystems(Simulator::ISerializerStream* stream, void* data)
	{
		auto s = stream->GetRecord()->GetStream();

		int count;
		if (!IO::ReadInt32(s, &count)) return false;

		if (s->GetAvailable() < count*12) return false;

		eastl::vector<uint32_t> ids(count);
		eastl::vector<int> sizes(count);
		for (int i = 0; i < count; ++i) {
			IO::ReadUInt32(s, &ids[i]);
			IO::ReadInt32(s, &sizes[i]);
		}

		for (int i = 0; i < count; ++i) {
			if (sizes[i] == 0) continue;
			if (s->GetAvailable() < sizes[i]) return false;

			auto it = simulatorStrategies.find(ids[i]);
			if (it == simulatorStrategies.end() || !it->second)
			{
				s->SetPosition(sizes[i], IO::PositionType::Current);
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

		eastl::vector<uint32_t> ids(count);
		eastl::vector<int> sizes(count);
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

	void EmptyReadText(const eastl::string& str, void* dst) {
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
