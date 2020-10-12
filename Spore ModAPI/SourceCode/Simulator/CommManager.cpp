#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\SubSystem\CommManager.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cCommManager, cCommManager*, Get);

	auto_METHOD(cCommManager, cCommEvent*, CreateCivCommEvent,
		Args(cCivilization* sourceCiv, cCity* targetCity, PlanetID planetKey, uint32_t fileID, uint32_t dialogID, int priority),
		Args(sourceCiv, targetCity, planetKey, fileID, dialogID, priority));

	auto_METHOD(cCommManager, cCommEvent*, CreateSpaceCommEvent,
		Args(uint32_t source, PlanetID planetKey, uint32_t fileID,
			uint32_t dialogID, void* pMission, int priority, unsigned int duration),
		Args(source, planetKey, fileID, dialogID, pMission, priority, duration));

	auto_METHOD_VOID(cCommManager, ShowCommEvent, Args(cCommEvent* pEvent), Args(pEvent));

	auto_METHOD_const_(cCommManager, bool, IsCommScreenActive);

	auto_METHOD_VOID(cCommManager, HandleCivCommAction, 
		Args(const CnvAction& action, void* pUnk, cCity* pSourceCity, cCity* pTargetCity),
		Args(action, pUnk, pSourceCity, pTargetCity));

	auto_METHOD_VOID(cCommManager, HandleSpaceCommAction,
		Args(const CnvAction& action, uint32_t source, PlanetID planetKey, void* pMission),
		Args(action, source, planetKey, pMission));
}

#endif