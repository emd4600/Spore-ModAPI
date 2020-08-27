#pragma once

#include <Spore\ResourceKey.h>
#include <EASTL\vector.h>

namespace Sporepedia
{
	struct AssetBrowserQuery
	{
		/* 00h */	uint32_t browserFilterData;
		/* 04h */	bool hasDataKeys;
		/// Asset keys obtained with browserFilterData
		/* 08h */	eastl::vector<ResourceKey> dataKeys;
		/* 1Ch */	bool hasParameterKeys;
		/// Asset keys obtained after filtering by parameters
		/* 20h */	eastl::vector<ResourceKey> parameterKeys;
	};

	/// @param filterID ID of filter file in `AssetBrowserFilter` folder
	void ProcessAssetFilter(uint32_t filterID, eastl::vector<AssetBrowserQuery>& dst);

	//TODO ObjectTemplateDB
}

namespace Addresses(Sporepedia)
{
	DeclareAddress(ProcessAssetFilter);
}