#pragma once

#include <Spore\Internal.h>
#include <Spore\RenderWare\Raster.h>

namespace Graphics
{
	typedef RenderWare::Raster RenderTargetTexture;
	typedef RenderTargetTexture RTT;

	class Texture;

	class IRenderTargetManager
	{
	private:
		struct Entry {
			/* 24h */	D3DFORMAT format;
			/* 28h */	int width;
			/* 2Ch */	int height;
			/* 30h */	
			/* 34h */	// use count? enabled?
			/* 38h */	Texture* pTexture;
		};
		// size 3C

	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual bool Initialize() = 0;
		/* 0Ch */	virtual bool Dispose() = 0;

		/* 10h */	virtual class ResourceID func10h(int width, int height, D3DFORMAT format, int flags = 0, int = -1, int = 0) = 0; 
		/* 14h */	virtual int func14h() = 0;
		
		//PLACEHOLDER
		// with 0x15, returns rendering RTT?
		/* 18h */	virtual RenderTargetTexture* GetRTT(int index, int=0) const = 0;
		///* 1C8h */	virtual Texture* GetRTT(int index, int = 0) const = 0;

		//  48h */	virtual SetName

		static IRenderTargetManager* Get();
		
	protected:
		// /* 18h */	vector<>
	};

	inline IRenderTargetManager* RenderTargetManager() {
		return IRenderTargetManager::Get();
	}

	namespace Addresses(IRenderTargetManager) {
		DeclareAddress(Get, SelectAddress(0x67DEC0, , 0x67DD60));
	}
}

namespace Addresses(Graphics) {
	DeclareAddress(MainColorRTT_ptr, SelectAddress(0x15D4AC8, , 0x15D0838));
	DeclareAddress(MainDepthRTT_ptr, SelectAddress(0x15D4ACC, , 0x15D083C));
}

namespace Graphics
{
	inline RenderTargetTexture* GetMainColorRTT() {
		return *(RenderWare::Raster**)(GetAddress(Graphics, MainColorRTT_ptr));
	}

	inline RenderTargetTexture* GetMainDepthRTT() {
		return *(RenderWare::Raster**)(GetAddress(Graphics, MainDepthRTT_ptr));
	}
}