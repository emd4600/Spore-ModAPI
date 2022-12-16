#ifndef MODAPI_DLL_EXPORT
#include <Spore\Skinner\cPaintSystem.h>

namespace Skinner
{
	auto_STATIC_METHOD_(cPaintSystem, cPaintSystem*, Get);

	auto_STATIC_METHOD_VOID(cSkinPainter, CreateTextures, Args(int textureSize), Args(textureSize));

	auto_METHOD_VOID_(cSkinnerTexturePainter, StartRender);
	auto_METHOD_VOID_(cSkinnerTexturePainter, EndRender);
	auto_METHOD_VOID(cSkinnerTexturePainter, Clear, Args(const Math::ColorRGB& color, float alpha), Args(color, alpha));
	auto_METHOD_VOID(cSkinnerTexturePainter, PaintRegion, Args(const Vector2& uv0, const Vector2& uv1, int index), Args(uv0, uv1, index));
	auto_METHOD_VOID(cSkinnerTexturePainter, SetColorWriteEnable, 
		Args(bool a1, bool a2, bool a3, bool a4), Args(a1, a2, a3, a4));

	void cSkinnerTexturePainter::AddCustomParams(int index, const Math::ColorRGBA& param)
	{
		if (mNumParams <= index)
		{
			mNumParams = index + 1;
		}
		mCustomParams[index] = param;
	}
	void cSkinnerTexturePainter::AddRaster(int index, RenderWare::Raster* raster)
	{
		if (mNumRasters <= index)
		{
			mNumRasters = index + 1;
		}
		mSrcRasters[index] = raster;
	}
}

#endif