#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\HintManager.h>

namespace UI
{
	auto_STATIC_METHOD_(cHintManager, cHintManager*, Get);
	auto_METHOD_VOID(cHintManager, ShowHint, Args(uint32_t hintID), Args(hintID));
}
#endif
