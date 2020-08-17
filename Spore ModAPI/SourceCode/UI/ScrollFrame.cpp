#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\ScrollFrameVertical.h>

namespace UI
{
	auto_STATIC_METHOD(ScrollFrameVertical, UTFWin::IWindow*, Create,
		Args(const char16_t* pLayoutName, IWindowPtr& dstContent, bool arg_8),
		Args(pLayoutName, dstContent, arg_8));
}
#endif
