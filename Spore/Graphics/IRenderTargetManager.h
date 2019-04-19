#pragma once

#include <Spore\Internal.h>
#include <Spore\RenderWare\Raster.h>

namespace Graphics
{
	typedef RenderWare::Raster RenderTargetTexture;
	typedef RenderTargetTexture RTT;

	class IRenderTargetManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual bool Initialize() = 0;
		/* 0Ch */	virtual bool Dispose() = 0;

		static IRenderTargetManager* Get();
	};

	inline IRenderTargetManager* RenderTargetManager() {
		return IRenderTargetManager::Get();
	}

	namespace InternalAddressList(IRenderTargetManager) {
		DefineAddress(Get, GetAddress(0x67DEC0, , PLACEHOLDER));
	}
}

namespace InternalAddressList(Graphics) {
	DefineAddress(MainColorRTT_ptr, GetAddress(0x15D4AC8, , PLACEHOLDER));
	DefineAddress(MainDepthRTT_ptr, GetAddress(0x15D4ACC, , PLACEHOLDER));
}

namespace Graphics
{
	inline RenderTargetTexture* GetMainColorRTT() {
		return *(RenderTargetTexture**)(GetMethodAddress(Graphics, MainColorRTT_ptr));
	}

	inline RenderTargetTexture* GetMainDepthRTT() {
		return *(RenderTargetTexture**)(GetMethodAddress(Graphics, MainDepthRTT_ptr));
	}
}