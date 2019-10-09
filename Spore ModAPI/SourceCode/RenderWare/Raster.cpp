#include <Spore\Graphics\Renderer.h>
#include <Spore\RenderWare\Raster.h>

namespace RenderWare
{
	Raster::Raster()
		: format()
		, flags()
		, volumeDepth()
		, pSurface(nullptr)
		, width(0)
		, height(0)
		, field_10()
		, levels(0)
		, field_14()
		, field_18()
		, pTextureData(nullptr)
	{}

	auto_METHOD_VOID_(Raster, Create);

	HRESULT Raster::CreateTexture(DWORD usage, D3DPOOL pool) {
		return Graphics::Renderer::GetDevice()->CreateTexture(width, height, levels, usage,
			format, pool, &pTexture, NULL);
	}
}