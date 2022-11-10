#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\App\cViewer.h>

namespace Skinner
{
	class cSkinnerTexture
	{
	public:
		/// Call before doing an editing action on this texture.
		void StartRender();

		/// Call to finish an editing action on this texture.
		void EndRender();

		/// Removes all contents of this texture and replaces them with a clear background of the specified color.
		/// @param color
		/// @param alpha
		void Clear(const Math::ColorRGB& color, float alpha);

	public:
		/* 00h */	App::cViewer* mpViewer;
		/* 04h */	uint32_t mMaterialID;
		/* 08h */	int mFlags;
		/* 0Ch */	Math::ColorRGBA field_C;
		/* 1Ch */	char padding_1C[0x20];
		/* 3Ch */	RenderWare::Raster* field_3C[1];  //TODO how many?
		/* 40h */	char padding_40[0x50 - 0x40];
		/* 50h */	Graphics::RenderTargetID mRenderTargetID;
		/* 58h */	int mWidth;
		/* 5Ch */	int mHeight;
		/* 60h */	RenderWare::Raster* mpRaster;
	};
	ASSERT_SIZE(cSkinnerTexture, 0x64);

	namespace Addresses(cSkinnerTexture)
	{
		DeclareAddress(StartRender);  // 0x529260
		DeclareAddress(EndRender);  // 0x529FC0
		DeclareAddress(Clear);  // 0x5296A0
	}
}