#pragma once

#include <Spore\Internal.h>

namespace UI
{
	namespace GameSettings
	{
		bool Show(uint32_t gameModeID);
	}

	namespace Addresses(GameSettings)
	{
		DeclareAddress(Show);
	}
}