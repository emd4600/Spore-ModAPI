#pragma once

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

	namespace InternalAddressList(IStateManager) {
		DefineAddress(Get, GetAddress(0x67DE40, , PLACEHOLDER));
	}
}