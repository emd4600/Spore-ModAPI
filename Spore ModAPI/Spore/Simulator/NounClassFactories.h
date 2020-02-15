#pragma once

#include <Spore\Internal.h>
#include <EASTL\hash_map.h>

namespace Simulator
{
	class cGameData;

	typedef cGameData*(*NounCreateFunction)();

	void RegisterNounType(uint32_t nounID, uint32_t typeID, const char* name);

	eastl::hash_map<uint32_t, NounCreateFunction> GetNounCreateMap();
}

namespace Addresses(Simulator) {
	DeclareAddress(RegisterNounType);
	DeclareAddress(GetNounCreateMap);
}