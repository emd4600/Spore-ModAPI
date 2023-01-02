#pragma once

namespace Graphics
{
#ifdef SDK_TO_GHIDRA
	// We need a placeholder class
	class cFrustumCull
	{
		int todo;
	};
#else
	class cFrustumCull;  //TODO
#endif
}