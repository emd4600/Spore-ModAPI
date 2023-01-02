#pragma once

#include <Spore\Internal.h>
#include <Spore\App\IClassManager.h>
#include <EASTL\hash_map.h>

namespace Simulator
{
	class cGameData;

	typedef cGameData*(*NounCreateFunction)();

	class NounCreateMap 
		: public App::ISPClassFactory
	{
	public:
#ifndef SDK_TO_GHIDRA
		inline NounCreateFunction& operator[](uint32_t key) {
			return classMap[key];
		}
#endif

	protected:
		eastl::hash_map<uint32_t, NounCreateFunction> classMap;
	};

	void RegisterNounType(uint32_t nounID, uint32_t typeID, const char* name);

	// When we add them it has already been added to the class manager
	//NounCreateMap& GetNounCreateMap();
}

namespace Addresses(Simulator) {
	DeclareAddress(RegisterNounType);
	DeclareAddress(GetNounCreateMap);
}