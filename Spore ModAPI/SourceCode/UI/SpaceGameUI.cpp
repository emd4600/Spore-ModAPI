#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\SpaceGameUI.h>

namespace UI
{
	auto_METHOD_VOID(SpaceGameUI, SetActivePalette, Args(uint32_t paletteID), Args(paletteID));

	auto_METHOD(SpaceGameUI, bool, FillStarTooltipPlanetInfo,
		Args(UTFWin::UILayout* layout, int slotIndex, Simulator::cPlanetRecord* planetRecord),
		Args(layout, slotIndex, planetRecord));
}

#endif