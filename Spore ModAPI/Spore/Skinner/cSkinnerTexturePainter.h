#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\App\cViewer.h>

namespace Skinner
{
	enum class MaterialIDs
	{
		// 0xA0468560 uses skpTexCopyShader
		// 0xa91b6551 uses skpSplatCopyTexShader
		// 0x9E74D163 uses skpBumpToNormal
		// 0x58653EAC (skpCopyIdentity) uses skpCopyIdentity
		// 0xfa2f3df4 uses skpDilateShader
		// 0x00f8b396 uses skpColorCopy
		// 0xD9EC39BC uses skpSplatTintShader
	};

	//TODO check sub_4CBC30

	enum class PainterJobIndex
	{
		CopyTex1ToTex0 = 9,
		PaintTintMasks = 10,

		BumpToNormalMap = 12,
	};

	struct Unk
	{
		/* 00h */	int vertexIndex;
		/* 04h */	int field_4;
		/* 08h */	unsigned int offset;
	};

	class cSkinnerTexturePainter
	{
	public:
		/// Call before doing an editing action on this texture.
		void StartRender();

		/// Call to finish an editing action on this texture.
		void EndRender();

		/// Sets which channels will be written in the next painting operation; those with false will not change.
		/// @param red
		/// @param green
		/// @param blue
		/// @param alpha
		void SetColorWriteEnable(bool red, bool green, bool blue, bool alpha);

		void AddCustomParam(int index, const Math::ColorRGBA& param);
		void AddRaster(int index, RenderWare::Raster* raster);

		/// Removes all contents of this texture and replaces them with a clear background of the specified color.
		/// @param color
		/// @param alpha
		void Clear(const Math::ColorRGB& color, float alpha);

		void PaintRegion(const Vector2& uv1, const Vector2& uv2, int index = -1);

	public:
		/* 00h */	App::cViewer* mpViewer;
		/* 04h */	uint32_t mMaterialID;
		/* 08h */	int mFlags;
		/* 0Ch */	Math::ColorRGBA mCustomParams[3];
		/* 3Ch */	RenderWare::Raster* mRasters[2];
		/* 44h */	int mNumParams;
		/* 48h */	int mNumRasters;
		/* 4Ch */	int field_4C;
		/* 50h */	Graphics::RenderTargetID mRenderTargetID;
		/* 58h */	int mWidth;
		/* 5Ch */	int mHeight;
		/* 60h */	RenderWare::Raster* mpRaster;
	};
	ASSERT_SIZE(cSkinnerTexturePainter, 0x64);

	namespace Addresses(cSkinnerTexturePainter)
	{
		DeclareAddress(StartRender);  // 0x529260 0x528E90
		DeclareAddress(EndRender);  // 0x529FC0 0x529BF0
		DeclareAddress(Clear);  // 0x5296A0 0x5292D0
		DeclareAddress(PaintRegion);  // 0x529A80 0x5296B0
		DeclareAddress(SetColorWriteEnable);  // 0x529650 0x529280
	}
}