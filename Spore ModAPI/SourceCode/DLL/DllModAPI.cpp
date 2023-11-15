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

	static constexpr unsigned int SCRATCH_SIZE = 4096;
	char logScratch[SCRATCH_SIZE];

	void Log(const char* fmt, ...) {
		unsigned int offset = 0;
		
		__time64_t long_time;
		_time64(&long_time);

		long_time -= logFileStartTime;

		constexpr static char formatted[] = {"[00:00:00]: "};
		constexpr char format[] = {"[%02d:%02d:%02d]: "};
		const int secs = long_time % 60;
		long_time /= 60;
		const int mins = long_time % 60;
		long_time /= 60;
		const int hours = long_time % 24;

		sprintf_s(logScratch + offset, SCRATCH_SIZE - offset, format, hours,mins,secs);
		offset += (sizeof(formatted)-1)/sizeof(formatted[0]);

		va_list argList;
		va_start(argList, fmt);
		vsnprintf(logScratch + offset, SCRATCH_SIZE - offset, fmt, argList);
		va_end(argList);

		// vsnprintf does not guarantee a null terminator if the formatted string exceeds the buffer size
		logScratch[SCRATCH_SIZE - 1] = 0;

		if (logFile)
		{
			logFile->Write(logScratch, strlen(logScratch));
			logFile->Write("\n", 1);
			logFile->Flush();
		}
		App::ConsolePrintF(logScratch + offset);
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