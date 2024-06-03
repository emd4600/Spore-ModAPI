#pragma once

#include <EASTL\fixed_vector.h>
#include <EASTL\fixed_map.h>
#include <Spore\ModAPI.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\CommonIDs.h>
#include <Spore\Messaging.h>
#include <Spore\Cheats.h>
#include <Spore\IO.h>
#include <ctime>
#include <mutex>

virtual_detour(ShaderFragments_detour, Graphics::cMaterialManager, Graphics::IMaterialManager, bool(Resource::Database*)) {};

namespace ModAPI
{
	const int MAX_MODS = 2048;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> initFunctions;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> postInitFunctions;
	extern eastl::fixed_vector<InitFunction, MAX_MODS> disposeFunctions;

	extern eastl::fixed_map<uint32_t, ISimulatorStrategyPtr, MAX_MODS> simulatorStrategies;

	extern FileStreamPtr logFile;
	extern __time64_t logFileStartTime;
	extern std::mutex logFileMutex;

	long AttachDetour();
	void DetachDetour();

	class UnkClass {};
	member_detour(PreInit_detour, UnkClass, int(int, int)) {};
	member_detour(sub_7E6C60_detour, UnkClass, int(int)) {};
	member_detour(AppInit_detour, UnkClass, int(int)) {};
	member_detour(AppShutdown_detour, UnkClass, int()) {};

	member_detour(PersistanceMan_Write_detour, UnkClass, bool(Simulator::ISerializerStream*)) {};
	member_detour(PersistanceMan_Read_detour, UnkClass, bool(Simulator::ISerializerStream*)) {};
}