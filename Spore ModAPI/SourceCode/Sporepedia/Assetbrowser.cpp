#ifndef MODAPI_DLL_EXPORT
#include <Spore\Internal.h>
#include <Spore\Sporepedia\AssetBrowserQuery.h>
#include <Spore\Sporepedia\ObjectTemplateDB.h>

auto_STATIC_METHOD_VOID(Sporepedia, ProcessAssetFilter,
	Args(uint32_t filterID, eastl::vector<AssetBrowserQuery>& dst),
	Args(filterID, dst));

namespace Sporepedia
{
	auto_STATIC_METHOD_(cObjectTemplateDB, cObjectTemplateDB*, Get);
}

#endif
