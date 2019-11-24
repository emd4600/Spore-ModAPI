#pragma once

#include <Spore\Internal.h>

namespace ModAPI
{
	enum class GameType
	{
		Disk = 0,
		March2017 = 1,
	};

	typedef void(*InitFunction)();

	extern MODAPI void AddInitFunction(InitFunction);
	extern MODAPI void AddPostInitFunction(InitFunction);
	extern MODAPI void AddDisposeFunction(InitFunction);

	extern MODAPI GameType GetGameType();

	extern MODAPI int GetMajorVersion();
	extern MODAPI int GetMinorVersion();
	extern MODAPI int GetBuildVersion();

	extern MODAPI uintptr_t ChooseAddress(uintptr_t disk, uintptr_t march2017);
}