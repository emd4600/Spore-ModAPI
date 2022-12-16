#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Clock.h>
#include <Spore\FixedPoolAllocator.h>
#include <Spore\Input.h>
#include <Spore\LocalizedString.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>
#include <Spore\Transform.h>

namespace Addresses(Internal)
{
	DefineAddress(Allocator_ptr, SelectAddress(0x16CCDC4, 0x16C8B44));
	DefineAddress(new_, SelectAddress(0xF47650, 0xF47240));
	DefineAddress(delete_, SelectAddress(0xF47630, 0xF47220));
}

namespace Addresses(Clock)
{
	DefineAddress(Stop, SelectAddress(0x93A810, 0x93A250));
	DefineAddress(SetMode, SelectAddress(0x93A6D0, 0x93A110));
	DefineAddress(GetElapsedTicks, SelectAddress(0x93A8D0, 0x93A310));
	DefineAddress(GetElapsedTime, SelectAddress(0x93AB10, 0x93A550));
	const uintptr_t Pause = Stop;


	// 1 - year
	// 2 - month
	// 6 - day of month
	// 8 - hour
	// 9 - minute
	// 10 - second
	//DefineAddress(GetTimeParam, SelectAddress(0x92E320, , PLACEHOLDER));
};

namespace Addresses(FixedPoolAllocator)
{
	DefineAddress(dtor, SelectAddress(0x926360, 0x9260F0));
	DefineAddress(Alloc, SelectAddress(0x926370, 0x926100));
	DefineAddress(Alloc_, SelectAddress(0x926490, 0x926220));
	DefineAddress(Free, SelectAddress(0x9263B0, 0x926140));
};

namespace Addresses(GameInput)
{
	DefineAddress(OnKeyDown, SelectAddress(0x697CA0, 0x697A50));
	DefineAddress(OnKeyUp, SelectAddress(0x697CD0, 0x697A80));

	DefineAddress(IsMouseButtonDown, SelectAddress(0x8D3650, 0x8D3340));
}

namespace Addresses(LocalizedString)
{
	DefineAddress(GetText, SelectAddress(0x6B5890, 0x6B5550));
	DefineAddress(SetText, SelectAddress(0x6B5780, 0x6B5440));

	DefineAddress(ctor_0, SelectAddress(0x6B5330, 0x6B4FF0));
	DefineAddress(ctor_1, SelectAddress(0x6B5A40, 0x6B5700));
	DefineAddress(dtor, SelectAddress(0x6B5510, 0x6B51D0));
}

namespace Addresses(Math)
{
	DefineAddress(MultiplyVectorScalar, SelectAddress(0x41DB70, 0x41DC60));
	DefineAddress(EulerToMatrix, SelectAddress(0x453AD0, 0x453DF0));
	DefineAddress(MatrixToEuler, SelectAddress(0x6A3BA0, 0x6A3920));

	DefineAddress(RandomNumberGenerator_ptr, SelectAddress(0x16059E8, 0x1601760));
}

namespace Math
{
	namespace Addresses(BoundingBox) {
		DefineAddress(ApplyTransform, SelectAddress(0x409D30, 0x409DD0));
	}

	namespace Addresses(RandomNumberGenerator) {
		DefineAddress(RandomInt, SelectAddress(0xA68FA0, 0xA68F70));
		DefineAddress(RandomFloat, SelectAddress(0x9365A0, 0x936040));
	}
}

namespace Addresses(ResourceKey)
{
	DefineAddress(Parse, SelectAddress(0x68DD00, 0x68D830));
}

namespace Addresses(Transform)
{
	DefineAddress(ToMatrix4, SelectAddress(0x6B9720, 0x6B93F0));
	DefineAddress(assign, SelectAddress(0x40CC10, 0x40CCB0));
}
#endif
