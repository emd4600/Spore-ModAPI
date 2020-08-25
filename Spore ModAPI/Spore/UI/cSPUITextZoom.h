#pragma once

#include <Spore\UTFWin\IText.h>

#define cSPUITextZoomPtr eastl::intrusive_ptr<UI::cSPUITextZoom>

namespace UI
{
	class cSPUITextZoom
		: public DefaultRefCounted
	{
	public:
		cSPUITextZoom();

		bool Initialize(UTFWin::IText* pText, int = 0, int = 0, int = 0, struct ResourceKey = {});

	private:
		char padding_8[0x70];
	};
	ASSERT_SIZE(cSPUITextZoom, 0x78);

	namespace Addresses(cSPUITextZoom)
	{
		DeclareAddress(ctor);
		DeclareAddress(Initialize);
	}
}