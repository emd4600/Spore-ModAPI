#pragma once

#include <Spore\UTFWin\IWinProc.h>

#define SpaceToolPanelUIPtr eastl::intrusive_ptr<UI::SpaceToolPanelUI>

namespace UI
{
	/// A class that represents one of the panels that contain multiple tools in the space tool palette.
	/// These are the panels inside spacetoolui~, such as "panel-combat-top~"
	class SpaceToolPanelUI
		: public UTFWin::IWinProc
	{
		//TODO PLACEHOLDER
	};
}