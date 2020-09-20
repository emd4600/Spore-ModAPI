#ifndef MODAPI_DLL_EXPORT
#include <Spore\Pollinator\cAssetMetadata.h>

namespace Pollinator
{
	auto_METHOD(cAssetMetadata, bool, Set,
		Args(const ResourceKey& key, const char16_t* pName, const char16_t* pDescription, const char16_t* pTags,
			const ResourceKey& parentAssetKey, bool isPollinated),
		Args(key, pName, pDescription, pTags, parentAssetKey, isPollinated));

	void* cAssetMetadata::Cast(uint32_t type) const
	{
		CLASS_CAST(cAssetMetadata);
		PARENT_CAST(Resource::ResourceObject);
		return nullptr;
	}
}
#endif