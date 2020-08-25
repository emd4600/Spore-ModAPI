#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\cSPUITextZoom.h>

namespace UI
{
	cSPUITextZoom::cSPUITextZoom()
	{
		CALL(GetAddress(cSPUITextZoom, ctor), void, Args(cSPUITextZoom*), Args(this));
	}

	auto_METHOD(cSPUITextZoom, bool, Initialize,
		Args(UTFWin::IText* pText, int arg1, int arg2, int arg3, struct ResourceKey arg4),
		Args(pText, arg1, arg2, arg3, arg4));
}
#endif
