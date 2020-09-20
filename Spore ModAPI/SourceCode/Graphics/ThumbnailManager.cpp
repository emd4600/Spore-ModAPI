#ifndef MODAPI_DLL_EXPORT
#include <Spore\Graphics\IThumbnailManager.h>

namespace Graphics
{
	auto_STATIC_METHOD_(IThumbnailManager, IThumbnailManager*, Get);

	PlanetThumbnailRequest::PlanetThumbnailRequest()
		: mpRenderable()
		, mpTexture()
		, mName()
		, mMessageID()
	{
	}
}
#endif
