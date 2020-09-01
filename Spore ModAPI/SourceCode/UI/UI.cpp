#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\GameSettings.h>

namespace UI
{
	auto_STATIC_METHOD(GameSettings, bool, Show, Args(uint32_t gameModeID), Args(gameModeID));
}
#endif