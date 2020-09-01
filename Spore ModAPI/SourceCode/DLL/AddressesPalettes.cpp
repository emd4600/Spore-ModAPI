#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Palettes\ColorPickerUI.h>
#include <Spore\Palettes\ColorSwatchUI.h>
#include <Spore\Palettes\ItemViewer.h>
#include <Spore\Palettes\AdvancedItemViewer.h>
#include <Spore\Palettes\PaletteCategory.h>
#include <Spore\Palettes\PaletteCategoryUI.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Palettes\PaletteMain.h>
#include <Spore\Palettes\PalettePage.h>
#include <Spore\Palettes\PalettePageUI.h>
#include <Spore\Palettes\PaletteUI.h>
#include <Spore\Palettes\StandardItemUI.h>
#include <Spore\Palettes\SwatchManager.h>

namespace Palettes
{
	namespace Addresses(ColorPickerUI)
	{
		DefineAddress(Load, SelectAddress(0x5A5D50, 0x5A5EB0, 0x5A5EB0));
		DefineAddress(SetVisible, SelectAddress(0x5A3F30, 0x5A41F0, 0x5A41F0));
		DefineAddress(GetSwatchArea, SelectAddress(0x5A4480, 0x5A4740, 0x5A4740));
		DefineAddress(Update, SelectAddress(0x5A6C40, 0x5A6DA0, 0x5A6DA0));
		DefineAddress(SetColor, SelectAddress(0x5A4B50, , 0x5A4E10));
	}

	namespace Addresses(ColorSwatchUI)
	{
		DefineAddress(Load, SelectAddress(0x5A4F00, 0x5A51B0, 0x5A51B0));
		DefineAddress(SetArea, SelectAddress(0x5A4230, 0x5A44F0, 0x5A44F0));
		DefineAddress(GenerateExpansionArea, SelectAddress(0x5A46C0, 0x5A4980, 0x5A4980));
		DefineAddress(AddTooltip, SelectAddress(0x5A43B0, 0x5A4670, 0x5A4670));
		DefineAddress(Update, SelectAddress(0x5A6260, 0x5A63C0, 0x5A63C0));
		DefineAddress(Destroy, SelectAddress(0x5A5C40, , 0x5A5DA0));

		DefineAddress(HandleUIMessage, SelectAddress(0x5A58B0, 0x5A5B60, 0x5A5B60));
	}

	namespace Addresses(cSwatchManager)
	{
		DefineAddress(Get, SelectAddress(0x401020, , 0x401020));
		DefineAddress(SetUnloadTime, SelectAddress(0x5F0B00, , 0x5F0CE0));
		DefineAddress(AddViewer, SelectAddress(0x5F0B40, , 0x5F0D20));
	}

	namespace Addresses(PaletteCategory)
	{
		DefineAddress(ReadProp, SelectAddress(0x5C1D50, 0x5C1EE0, 0x5C1F10));
		DefineAddress(GetCategory, SelectAddress(0x5C1D00, 0x5C1E30, 0x5C1E60));
		DefineAddress(HasCategory, SelectAddress(0x5C1CD0, 0x5C1E00, 0x5C1E30));
	}

	namespace Addresses(PaletteCategoryUI)
	{
		DefineAddress(Load, SelectAddress(0x5C5560, 0x5C5480, 0x5C54B0));
		DefineAddress(LoadPages, SelectAddress(0x5C5380, 0x5C52A0, 0x5C52D0));
		DefineAddress(FlipPage, SelectAddress(0x5C3C60, 0x5C3CE0, 0x5C3D10));
		DefineAddress(HandleMessage, SelectAddress(0x5C3730, 0x5C37B0, 0x5C37E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x5C40F0, 0x5C4170, 0x5C41A0));
		DefineAddress(Update, SelectAddress(0x5C28D0, 0x5C2970, 0x5C29A0));
		DefineAddress(LayoutPagePanel, SelectAddress(0x5C3000, , 0x5C30F0));
	}

	namespace Addresses(PageArrowsUI)
	{
		DefineAddress(HandleUIMessage, SelectAddress(0x5C0920, 0x5C0AC0, 0x5C0AF0));
		DefineAddress(Load, SelectAddress(0x5C0760, 0x5C0900, 0x5C0930));
		DefineAddress(Update, SelectAddress(0x5C09A0, 0x5C0B20, 0x5C0B50));
	}

	namespace Addresses(PaletteItem)
	{
		DefineAddress(Load, SelectAddress(0x5C69A0, 0x5C68D0, 0x5C6900));
	}

	namespace Addresses(PaletteMain)
	{
		DefineAddress(GetCategory, SelectAddress(0x5C5F90, 0x5C5EB0, 0x5C5EE0));
		DefineAddress(ReadProp, SelectAddress(0x5C64E0, 0x5C6400, 0x5C6430));
		DefineAddress(ReadModuleProp, SelectAddress(0x5C61B0, 0x5C60D0, 0x5C6100));
		DefineAddress(Unload, SelectAddress(0x5C5DC0, , 0x5C5D10));
	}

	namespace Addresses(PalettePage)
	{
		DefineAddress(ReadProp, SelectAddress(0x5C84D0, 0x5C8690, 0x5C86C0));
		DefineAddress(Load, SelectAddress(0x5C89D0, 0x5C8B90, 0x5C8BC0));
		DefineAddress(ReadItemsModule, SelectAddress(0x5C8040, 0x5C80B0, 0x5C80E0));
	}

	namespace Addresses(PalettePageUI)
	{
		DefineAddress(Load, SelectAddress(0x5C9020, 0x5C92F0, 0x5C9320));
		DefineAddress(GetItemArea, SelectAddress(0x5C8CD0, 0x5C8E30, 0x5C8E60));
	}

	namespace Addresses(PaletteUI)
	{
		DefineAddress(Load, SelectAddress(0x5CB180, 0x5CB660, 0x5CB690));
		DefineAddress(Update, SelectAddress(0x5CA590, 0x5CAA40, 0x5CAA70));
		DefineAddress(Unload, SelectAddress(0x5CB670, , 0x5CBB80));
		DefineAddress(HandleUIMessage, SelectAddress(0x5CB080, 0x5CB560, 0x5CB590));
	}

	namespace Addresses(StandardItemUI)
	{
		DefineAddress(HandleUIMessage, SelectAddress(0x5C73F0, 0x5C7320, 0x5C7350));
	}

	namespace Addresses(ItemViewer)
	{
		DefineAddress(InitializeViewerCamera, SelectAddress(0x5F3B50, , 0x5F3D80));

		DefineAddress(UnkUnload1, SelectAddress(0x5F65C0, , 0x5F6860));
		DefineAddress(UnkUnload2, SelectAddress(0x80E5E0, , 0x80E020));

		DefineAddress(Unload, SelectAddress(0x5F6690, , 0x5F6930));
	}

	namespace Addresses(AdvancedItemViewer)
	{
		DefineAddress(SetAutoRotate, SelectAddress(0x5F4800, , 0x5F4A30));
		DefineAddress(SetZoom, SelectAddress(0x5F2190, , 0x5F2370));

		DefineAddress(HandleUIMessage, SelectAddress(0x5F2630, , 0x5F2840));
		DefineAddress(Unload, SelectAddress(0x5F68D0, , 0x5F6B70));
		DefineAddress(Update, SelectAddress(0x5F7290, , 0x5F7520));
		DefineAddress(Load, SelectAddress(0x5F5D10, , 0x5F5FB0));
		DefineAddress(SetName, SelectAddress(0x5F3EE0, , 0x5F4110));
		DefineAddress(func40h, SelectAddress(0x5F4520, , 0x5F4750));
		DefineAddress(func44h, SelectAddress(0x5F2ED0, , 0x5F30F0));
		DefineAddress(func48h, SelectAddress(0x5F45B0, , 0x5F47E0));
		DefineAddress(func4Ch, SelectAddress(0x5F2F20, , 0x5F3140));
		DefineAddress(func50h, SelectAddress(0x5F4850, , 0x5F4A80));
		DefineAddress(func54h, SelectAddress(0x5F3010, , 0x5F3230));
		DefineAddress(func58h, SelectAddress(0x5F21B0, , 0x5F2390));
		DefineAddress(IsOutside, SelectAddress(0x5F3190, , 0x5F33B0));
		DefineAddress(OnOutside, SelectAddress(0x5F49E0, , 0x5F4C10));
		DefineAddress(func64h, SelectAddress(0x5F4130, , 0x5F4360));
		DefineAddress(RotateModel, SelectAddress(0x5F53D0, , 0x5F5670));
		DefineAddress(func6Ch, SelectAddress(0x5F2C70, , 0x5F2E80));
		DefineAddress(func70h, SelectAddress(0x5F2D20, , 0x5F2F30));
		DefineAddress(func74h, SelectAddress(0x5F2FC0, , 0x5F31E0));
		DefineAddress(func78h, SelectAddress(0x5F2060, , 0x5F2250));

		DefineAddress(HandleMessage, SelectAddress(0x5F4550, , 0x5F4780));

		DefineAddress(Initialize, SelectAddress(0x5F4170, , 0x5F43A0));
	}
}
#endif
