#include <Spore\UTFWin\CursorManager.h>

namespace UTFWin
{
	auto_STATIC_METHOD_(cCursorManager, cCursorManager*, Get);

	auto_METHOD(cCursorManager, bool, Load, Args(uint32_t arg0, const char16_t* arg1, bool arg2, int arg3, int arg4),
		Args(arg0, arg1, arg2, arg3, arg4));

	auto_METHOD_const_(cCursorManager, uint32_t, GetActiveCursor);
	auto_METHOD(cCursorManager, bool, SetActiveCursor, Args(uint32_t id), Args(id));
}