#ifndef MODAPI_DLL_EXPORT
#include <Spore\Pollinator\cAssetMetadata.h>
#include <Spore\Pollinator\AchievementsManager.h>

namespace Pollinator
{
	//// cAssetMetadata ////

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

	auto_METHOD(cAssetMetadata, bool, SetAll,
		Args(const ResourceKey& assetKey,
			uint64_t assetId,
			uint64_t timeCreated,
			const char16_t* authorName,
			uint64_t authorId,
			const char16_t* name,
			const char16_t* description,
			const char16_t* tags,
			const char* authors,
			bool useCurrentTimeForTimeDownloaded),
		Args(assetKey, assetId, timeCreated, authorName, authorId, name, description, tags, authors, useCurrentTimeForTimeDownloaded));

	//// cAchievementsManager ////

	auto_STATIC_METHOD_(cAchievementsManager, cAchievementsManager*, Get);

	auto_METHOD_(cAchievementsManager, bool, Init);

	auto_METHOD(cAchievementsManager, cAchievementDefinition*, GetAchievementDefinition, Args(uint32_t aID), Args(aID));

	auto_METHOD(cAchievementsManager, bool, EvaluateTriggerOp, Args(uint32_t aID), Args(aID));

	auto_METHOD_VOID(cAchievementsManager, AddProgress, Args(uint32_t aID, int delta), Args(aID, delta));

	auto_METHOD_VOID(cAchievementsManager, SetProgressFlags, Args(uint32_t aID, int progressFlags, bool value), Args(aID, progressFlags, value));

	auto_METHOD(cAchievementsManager, bool, EarnAchievement, Args(uint32_t aID), Args(aID));
}
#endif