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

	/// Finds all the assets that match the given filter. This method will use a filter with the given ID
	/// in the `AssetBrowserFilter` folder. The `dst` vector will be filled with one instance for every 
	/// `browserFilterData` that has been searched; each instance contains vectors of the resource keys that match it.
	/// @param filterID ID of filter file in `AssetBrowserFilter` folder
	/// @param[out] dst The destination vector
	void ProcessAssetFilter(uint32_t filterID, eastl::vector<AssetBrowserQuery>& dst);

	//TODO ObjectTemplateDB
}

namespace Addresses(Sporepedia)
{
	DeclareAddress(ProcessAssetFilter);
}