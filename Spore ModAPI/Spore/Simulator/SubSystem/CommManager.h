#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cCommEvent.h>
#include <Spore\Simulator\ConversationResource.h>

#define CommManager (*Simulator::cCommManager::Get())

namespace Simulator
{
	class cCommManager
		: public cStrategy
	{
	public:		
		cCommEvent* CreateCivCommEvent(cCivilization* pSourceCivilization, cCity* pTargetCity, PlanetID planetKey, 
			uint32_t fileID, uint32_t dialogID, int priority = 0);

		cCommEvent* CreateSpaceCommEvent(uint32_t sourceEmpire, PlanetID planetKey, uint32_t fileID,
			uint32_t dialogID, void* pMission = nullptr, int priority = 0, unsigned int duration = 0);

		void ShowCommEvent(cCommEvent* pEvent);

		bool IsCommScreenActive() const;

		void HandleCivCommAction(const CnvAction& action, void* pSourceCiv, cCity* pSourceCity, cCity* pTargetCity);

		void HandleSpaceCommAction(const CnvAction& action, uint32_t source, PlanetID planetKey, void* pMission);

	public:
		/* 20h */	cCommEventPtr mCurrentCommEvent;
		/* 24h */	eastl::vector<cCommEventPtr> mListCommEvents;
		/* 38h */	int field_38;  // -1
		/* 3Ch */	ObjectPtr field_3C;
		/* 40h */	eastl::hash_map<uint32_t, eastl::vector<uint32_t>> mTransmissionCancelConditions;
		/* 60h */	bool field_60;
		/* 64h */	int field_64;

	public:
		static cCommManager* Get();
	};

	namespace Addresses(cCommManager)
	{
		DeclareAddress(Get);

		DeclareAddress(CreateCivCommEvent);
		DeclareAddress(CreateSpaceCommEvent);
		DeclareAddress(ShowCommEvent);
		DeclareAddress(HandleCivCommAction);
		DeclareAddress(HandleSpaceCommAction);
		DeclareAddress(IsCommScreenActive);
	}
}