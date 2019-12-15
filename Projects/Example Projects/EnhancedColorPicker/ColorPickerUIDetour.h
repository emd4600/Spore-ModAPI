#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Palettes\ColorPickerUI.h>

using namespace Palettes;
using namespace UTFWin;

// We will detour the Load method so we can add our color picker button
member_detour(ColorPickerUI_Load_detour, ColorPickerUI, bool(IWindow*, uint32_t, uint32_t, vector<ColorRGB>*)) {};