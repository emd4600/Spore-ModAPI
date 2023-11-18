#pragma once

#include <Spore\Object.h>
#include <Spore\App\CommandLine.h>
#include <EASTL\vector.h>

#define StateManager (*App::IStateManager::Get())

namespace App
{
	class IStateManager
		: public Object
	{
	public:
		static const uint32_t TYPE = 0xBE9741;

		static IStateManager* Get();

		/* 10h */	virtual bool Init(const char* cheatName) = 0;
		/* 14h */	virtual bool Shutdown() = 0;
		/* 18h */	virtual void Update() = 0;
		/* 1Ch */	virtual bool LoadConfigFile(uint32_t instanceID, uint32_t groupID, App::CommandLine* commandLine, bool) = 0;
		/* 20h */	virtual bool LoadConfigFileFromDisk(const char16_t* path, App::CommandLine* commandLine, bool) = 0;
		/* 24h */	virtual bool IsValidState(uint32_t stateID) = 0;
		/* 28h */	virtual bool SwitchToState(uint32_t stateID) = 0;
		/// Always returns 0!!
		/* 2Ch */	virtual uint32_t CurrentState() = 0;
		/* 30h */	virtual const eastl::vector<uint32_t>& PreviousStates() = 0;
		/* 34h */	virtual bool StateOccurredPreviously(uint32_t stateID) = 0;
		/* 38h */	virtual uint32_t StateIDFromName(const char* name) = 0;
		/* 3Ch */	virtual const char* CurrentStateName() = 0;
		/* 40h */	virtual bool ResetToDefaultState() = 0;
	};

	namespace Addresses(IStateManager) {
		DeclareAddress(Get);  // 0x67DE40 0x67DCE0
	}
}