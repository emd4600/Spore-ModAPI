#ifdef MODAPI_DLL_EXPORT
#include <Spore\Skinner\cPaintSystem.h>
#include <Spore\Skinner\cSkinnerTexturePainter.h>
#include <Spore\Skinner\cSkinPainter.h>

namespace Skinner
{
	namespace Addresses(cSkinnerTexturePainter)
	{
		DefineAddress(StartRender, SelectAddress(0x529260, 0x528E90));
		DefineAddress(EndRender, SelectAddress(0x529FC0, 0x529BF0));
		DefineAddress(Clear, SelectAddress(0x5296A0, 0x5292D0));
		DefineAddress(PaintRegion, SelectAddress(0x529A80, 0x5296B0));
		DefineAddress(SetColorWriteEnable, SelectAddress(0x529650, 0x529280));
	}

	namespace Addresses(cSkinPainter)
	{
		DefineAddress(CreateTextures, SelectAddress(0x5061D0, 0x506630));
	}

	namespace Addresses(cPaintSystem)
	{
		DefineAddress(Get, SelectAddress(0x401080, 0x401080));
	}
}
#endif
