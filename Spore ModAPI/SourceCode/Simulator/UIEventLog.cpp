#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\SubSystem\UIEventLog.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cUIEventLog, cUIEventLog*, Get);

	auto_METHOD(cUIEventLog, uint32_t, ShowEvent,
		Args(uint32_t instanceID, uint32_t groupID, int arg3, Math::Vector3* arg4, bool arg5, int arg6),
		Args(instanceID, groupID, arg3, arg4, arg5, arg6));

	auto_METHOD_VOID(cUIEventLog, HideEvent, Args(uint32_t eventID, bool partially), Args(eventID, partially));
	auto_METHOD_VOID(cUIEventLog, SetDescription, Args(uint32_t eventID, const char16_t* pText), Args(eventID, pText));
	auto_METHOD_VOID(cUIEventLog, SetVisible, Args(bool visible), Args(visible));
}
#endif