#pragma once

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>

namespace UI
{
	class ScrollFrameVertical
	{
		// no need to document the class

	public:
		static constexpr char16_t* GENERIC_LAYOUT = u"ScrollFrameVerticalGeneric";

		static UTFWin::IWindow* Create(const char16_t* pLayoutName, IWindowPtr& dstContent, bool = true);
	};

	namespace Addresses(ScrollFrameVertical)
	{
		DeclareAddress(Create);
	}
}