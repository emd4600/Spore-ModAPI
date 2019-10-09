#pragma once

#error "Not supported yet"

#include <Spore\Internal.h>

namespace App
{
	//TODO PLACEHOLDER, ctor at loc_7E56F0
	class IStateManager
	{
	public:
		static IStateManager* Get();
	};

	inline IStateManager* StateManager() {
		return IStateManager::Get();
	}

	namespace Addresses(IStateManager) {
		DeclareAddress(Get, SelectAddress(0x67DE40, , PLACEHOLDER));
	}
}