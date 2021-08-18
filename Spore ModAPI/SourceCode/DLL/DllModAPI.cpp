#ifdef MODAPI_DLL_EXPORT

#include "stdafx.h"
#include "Application.h"
#include <Spore\ModAPI.h>

namespace ModAPI
{
	int GetMajorVersion() {
		return 2;
	}
	int GetMinorVersion() {
		return 5;
	}
	int GetBuildVersion() {
		return SDK_BUILD_VER;
	}

	void AddInitFunction(InitFunction f) {
		initFunctions.push_back(f);
	}

	void AddPostInitFunction(InitFunction f) {
		postInitFunctions.push_back(f);
	}

	void AddDisposeFunction(InitFunction f) {
		disposeFunctions.push_back(f);
	}

	bool AddSimulatorStrategy(Simulator::ISimulatorStrategy* strategy, uint32_t id) {
		if (strategy && simulatorStrategies.find(id) == simulatorStrategies.end()) {
			simulatorStrategies[id] = strategy;
			return true;
		}
		return false;
	}

	GameType GetGameType()
	{
#if EXECUTABLE_TYPE == 0
		return GameType::Disk;
#else
		return GameType::March2017;
#endif
	}

	uintptr_t ChooseAddress(uintptr_t disk, uintptr_t march2017) {
#if EXECUTABLE_TYPE == 0
		return disk;
#else
		return march2017;
#endif
	}
}

#endif