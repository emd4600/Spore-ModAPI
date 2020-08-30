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

	namespace Addresses(ItemViewer)
	{
		DefineAddress(InitializeViewerCamera, SelectAddress(0x5F3B50, , 0x5F3D80));
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

	namespace Addresses(AdvancedItemViewer)
	{
		DefineAddress(SetAutoRotate, SelectAddress(0x5F4800, , 0x5F4A30));
		DefineAddress(SetZoom, SelectAddress(0x5F2190, , 0x5F2370));
	}
}
#endif
