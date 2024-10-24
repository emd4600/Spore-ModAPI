#ifdef MODAPI_DLL_EXPORT

#include "stdafx.h"
#include "Application.h"
#include <Spore\ModAPI.h>
#include <Psapi.h>

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
		
		logFileMutex.lock();

		sprintf_s(logScratch, SCRATCH_SIZE, format, hours,mins,secs);
		unsigned int time_offset = (sizeof(formatted)-1)/sizeof(formatted[0]);

		va_list argList;
		va_start(argList, fmt);
		vsnprintf(logScratch + time_offset, SCRATCH_SIZE - time_offset, fmt, argList);
		va_end(argList);

		// vsnprintf does not guarantee a null terminator if the formatted string exceeds the buffer size
		logScratch[SCRATCH_SIZE - 1] = 0;

		auto log_len = strlen(logScratch);

		if (logFile)
		{
			logFile->Write(logScratch, log_len);
			logFile->Write("\n", 1);
			logFile->Flush();
		}
		App::ConsolePrintF(logScratch + time_offset);
		memset(logScratch, 0, log_len);
		logFileMutex.unlock();
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
#if EXECUTABLE_TYPE == 10
		static bool hasFoundGameType = false;
		static GameType cachedGameType = GameType::Disk;

		if (hasFoundGameType)
		{
			return cachedGameType;
		}

		wchar_t fileNameBuf[MAX_PATH] = { 0 };
		GetModuleFileNameW(GetModuleHandleA(NULL), fileNameBuf, MAX_PATH);

		WIN32_FILE_ATTRIBUTE_DATA fad;
		LARGE_INTEGER size;

		if (!GetFileAttributesExW(fileNameBuf, GetFileExInfoStandard, &fad))
		{
			MessageBoxA(NULL, "GetFileAttributesExA() Failed!", "Spore ModAPI", MB_ICONERROR | MB_OK);
			std::terminate();
		}

		size.HighPart = fad.nFileSizeHigh;
		size.LowPart  = fad.nFileSizeLow;

		if (size.QuadPart == 24904192 || size.QuadPart == 24909584)
		{ // disk version
			cachedGameType = GameType::Disk;
			hasFoundGameType = true;
		}
		else if (size.QuadPart == 24885248 || size.QuadPart == 24895536)
		{ // steam patched version
			cachedGameType = GameType::March2017;
			hasFoundGameType = true;
		}
		else
		{ // unknown version
			MessageBoxA(NULL, "unsupported Spore version", "Spore ModAPI", MB_ICONERROR | MB_OK);
			std::terminate();
		}

		return cachedGameType;
#elif EXECUTABLE_TYPE == 0
		return GameType::Disk;
#else
		return GameType::March2017;
#endif
	}

	uintptr_t ChooseAddress(uintptr_t disk, uintptr_t march2017) {
#if EXECUTABLE_TYPE == 10
		if (GetGameType() == GameType::Disk) {
			return disk;
		} else {
			return march2017;
		}
#elif EXECUTABLE_TYPE == 0
		return disk;
#else
		return march2017;
#endif
	}
}

#endif