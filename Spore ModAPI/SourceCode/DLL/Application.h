#pragma once

#include <EASTL\fixed_vector.h>
#include <EASTL\fixed_map.h>
#include <Spore\ModAPI.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\CommonIDs.h>
#include <Spore\Messaging.h>
#include <Spore\Cheats.h>

using namespace Graphics;
using namespace Resource;

virtual_detour(ShaderFragments_detour, cMaterialManager, IMaterialManager, bool(DatabasePackedFile*)) {};

namespace ModAPI
{
	const int MAX_MODS = 2048;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> initFunctions;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> postInitFunctions;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> disposeFunctions;

	extern fixed_map<uint32_t, intrusive_ptr<Simulator::ISimulatorStrategy>, MAX_MODS> simulatorStrategies;

	long AttachDetour();
	void DetachDetour();

	class UnkClass {};
	member_detour(sub_7E6C60_detour, UnkClass, int(int)) {};
	member_detour(AppInit_detour, UnkClass, int(int)) {};
	member_detour(AppShutdown_detour, UnkClass, int()) {};

	member_detour(PersistanceMan_Write_detour, UnkClass, bool(Simulator::ISerializerStream*)) {};
	member_detour(PersistanceMan_Read_detour, UnkClass, bool(Simulator::ISerializerStream*)) {};
}