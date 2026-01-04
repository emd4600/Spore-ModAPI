#ifndef MODAPI_DLL_EXPORT
#include <Spore\Editors\VerbIconData.h>


namespace Editors
{
	auto_METHOD_VIRTUAL_(VerbIconData, VerbIconData, int, AddRef);
	auto_METHOD_VIRTUAL_(VerbIconData, VerbIconData, int, Release);
	auto_METHOD_VIRTUAL_(VerbIconData, VerbIconData, void*, Dispose);
	auto_METHOD_VIRTUAL(VerbIconData, VerbIconData, void*, AsInterface, Args(Editors::VerbIconData::InterfaceId interfaceID), Args(interfaceID));
	auto_METHOD_VIRTUAL_VOID(VerbIconData, VerbIconData, Init, Args(App::PropertyList* abilityProp), Args(abilityProp));
	auto_METHOD_VIRTUAL_VOID_(VerbIconData, VerbIconData, Shutdown);
	auto_METHOD_VIRTUAL_VOID(VerbIconData, VerbIconData, SetArrayIndex, Args(int arrayIndex), Args(arrayIndex));
	auto_METHOD_VIRTUAL_VOID(VerbIconData, VerbIconData, SetHotKey, Args(int verbIconTriggerKey), Args(verbIconTriggerKey));
	auto_METHOD_VIRTUAL(VerbIconData, VerbIconData, eastl::string16, GetIconName, Args(eastl::string16* iconName, bool includeLevel), Args(iconName, includeLevel));
	auto_METHOD_VIRTUAL(VerbIconData, VerbIconData, eastl::string16, GetIconDescription, Args(eastl::string16* iconDesc), Args(iconDesc));
}
#endif