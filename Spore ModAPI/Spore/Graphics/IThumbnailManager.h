#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Object.h>
#include <EASTL\string.h>

#define ThumbnailManager (*Graphics::IThumbnailManager::Get())
#define PlanetThumbnailRequestPtr eastl::intrusive_ptr<Graphics::PlanetThumbnailRequest>

namespace Graphics
{
	class PlanetThumbnailRequest
		: public DefaultRefCounted  // actually it doesn't have the last method
	{
	public:
		PlanetThumbnailRequest();

		/* 08h */	float mRadius;  // not initialized
		/* 0Ch */	int field_C;  // not initialized
		/* 10h */	IRenderablePtr mpRenderable;
		/* 14h */	TexturePtr mpTexture;
		/* 18h */	string mName;
		/// ID of message sent when the image finishes rendering
		/* 28h */	uint32_t mMessageID;
	};
	ASSERT_SIZE(PlanetThumbnailRequest, 0x2C);

	class IThumbnailManager
	{
	public:
		virtual int func00h() = 0;
		virtual int func04h() = 0;
		virtual int func08h() = 0;
		virtual int func0ch() = 0;
		virtual int func10h() = 0;
		virtual int func14h() = 0;
		virtual int func18h() = 0;
		virtual int func1ch() = 0;
		virtual int func20h() = 0;
		virtual int func24h() = 0;
		virtual int func28h() = 0;
		virtual int func2ch() = 0;
		virtual int func30h() = 0;
		virtual int RenderPlanetThumbnail(PlanetThumbnailRequest* request, int thumbnailSize) = 0;
		virtual int func38h() = 0;
		virtual int func3ch() = 0;
		virtual int func40h() = 0;
		virtual int func44h() = 0;
		virtual int func48h() = 0;
		virtual int func4ch() = 0;
		virtual int func50h() = 0;
		virtual int func54h() = 0;
		virtual int func58h() = 0;
		virtual int func5ch() = 0;
		virtual int func60h() = 0;
		virtual int func64h() = 0;

		static IThumbnailManager* Get();
	};

	namespace Addresses(IThumbnailManager) {
		DeclareAddress(Get);
	}
}