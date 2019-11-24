#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Internal.h>

namespace Graphics
{
	class IGraphicsManager
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
		virtual int func34h() = 0;
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
		virtual int func68h() = 0;
		virtual int func6ch() = 0;
		virtual int func70h() = 0;

		virtual Texture* GetDepthTexture() = 0;

		//static IGraphicsManager* Get();
	};

	namespace Addresses(IGraphicsManager) {
		//DeclareAddress(Get);
	}
}