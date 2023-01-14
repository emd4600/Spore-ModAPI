#ifdef MODAPI_DLL_EXPORT
#include <Spore\Skinner\cPaintSystem.h>
#include <Spore\Skinner\cSkinnerTexturePainter.h>
#include <Spore\Skinner\cSkinPainter.h>
#include <Spore\Skinner\cSkinPainterPipeline.h>
#include <Spore\Skinner\cSkinPainterJob.h>
#include <Spore\Skinner\cSkinPainterJobAmbientOcclusion.h>
#include <Spore\Skinner\cSkinPainterJobApplyBrushes.h>
#include <Spore\Skinner\cSkinPainterJobBumpToNormal.h>
#include <Spore\Skinner\cSkinPainterJobColorDilateRepeat.h>
#include <Spore\Skinner\cSkinPainterJobCopyRigblocksTintMaskAlpha.h>
#include <Spore\Skinner\cSkinPainterJobCopyTex1AlphaToTex0.h>
#include <Spore\Skinner\cSkinPainterJobExtractTexture.h>
#include <Spore\Skinner\cSkinPainterJobPaintParts.h>

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

	namespace Addresses(cSkinPainterJob)
	{
		DefineAddress(DrawLayer, SelectAddress(0x5172C0, 0x5171B0));
		DefineAddress(Initialize, SelectAddress(0x517420, 0x517310));
	}

	namespace Addresses(cSkinPainterJobAmbientOcclusion)
	{
		DefineAddress(Execute, SelectAddress(0x519050, 0x518F20));
	}

	namespace Addresses(cSkinPainterJobApplyBrushes)
	{
		DefineAddress(Execute, SelectAddress(0x518440, 0x518310));
	}

	namespace Addresses(cSkinPainterJobBumpToNormal)
	{
		DefineAddress(Execute, SelectAddress(0x518E40, 0x518D10));
	}

	namespace Addresses(cSkinPainterJobColorDilateRepeat)
	{
		DefineAddress(Execute, SelectAddress(0x518510, 0x5183E0));
	}

	namespace Addresses(cSkinPainterJobCopyRigblocksTintMaskAlpha)
	{
		DefineAddress(Execute, SelectAddress(0x51A490, 0x51A360));
	}

	namespace Addresses(cSkinPainterJobCopyTex1AlphaToTex0)
	{
		DefineAddress(Execute, SelectAddress(0x518D40, 0x518C10));
	}

	namespace Addresses(cSkinPainterJobPaintParts)
	{
		DefineAddress(Execute, SelectAddress(0x519780, 0x519650));
	}

	namespace Addresses(cSkinPainterPipeline)
	{
		DefineAddress(ExecutePipeline, SelectAddress(0x51B110, 0x51AFE0));
		DefineAddress(PreloadTextures, SelectAddress(0x51AC90, 0x51AB60));
		DefineAddress(Initialize, SelectAddress(0x51AAE0, 0x51A9B0));
	}
}
namespace Addresses(Skinner)
{
	DefineAddress(GetCurrentColors, SelectAddress(0x15E3370,  0x15DF0F0));
}
#endif
