#pragma once

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>

namespace UI
{
	class ScrollFrameVertical
	{
		// no need to document the class

	public:
#ifndef SDK_TO_GHIDRA
		static constexpr char16_t* GENERIC_LAYOUT = u"ScrollFrameVerticalGeneric";
#endif

		static UTFWin::IWindow* Create(const char16_t* pLayoutName, IWindowPtr& dstContent, bool = true);
	};

	namespace Addresses(ScrollFrameVertical)
	{
		DeclareAddress(Create);
	}
}