#ifndef MODAPI_DLL_EXPORT
#include <Spore\Graphics\Renderer.h>
#include <Spore\RenderWare\Raster.h>
#include <Spore\RenderWare\CompiledState.h> 

namespace RenderWare
{
	Raster::Raster()
		: format()
		, flags()
		, volumeDepth()
		, pSurface(nullptr)
		, width(0)
		, height(0)
		, depth()
		, cubeFaces()
		, levels(0)
		, pNextParent()
		, pSwapChain()
		, pTextureData(nullptr)
	{}

	Raster::~Raster() {
		Delete();
	}

	auto_METHOD_VOID_(Raster, Create);

	HRESULT Raster::CreateTexture(DWORD usage, D3DPOOL pool) {
		return Graphics::Renderer::GetDevice()->CreateTexture(width, height, levels, usage,
			format, pool, &pTexture, NULL);
	}

	auto_METHOD_VOID_(Raster, Delete);
	auto_METHOD_VOID_(Raster, D3D9AddToUnmanagedList);

	auto_STATIC_METHOD(Raster, Raster*, CreateRaster,
		Args(Raster*& pDst, uint16_t width, uint16_t height, uint8_t levels, int flagsDepth, D3DFORMAT format),
		Args(pDst, width, height, levels, flagsDepth, format));


	TextureSlot::TextureSlot() 
		: compiledState(nullptr)
		, slotIndex(0)
		, raster(nullptr)
		, originalRaster(nullptr)
	{}

	TextureSlot::~TextureSlot()
	{
		if (compiledState) {
			compiledState->SetRaster(slotIndex, originalRaster);
		}
	}
}
#endif
