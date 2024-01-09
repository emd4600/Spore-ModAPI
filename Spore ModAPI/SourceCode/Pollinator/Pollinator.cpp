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