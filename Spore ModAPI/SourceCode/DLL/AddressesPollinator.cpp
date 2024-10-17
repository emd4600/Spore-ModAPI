#ifdef MODAPI_DLL_EXPORT
#include <Spore\Pollinator\cAssetMetadata.h>
#include <Spore\Pollinator\AchievementsManager.h>

namespace Pollinator
{
	namespace Addresses(cAssetMetadata)
	{
		DefineAddress(Set, SelectAddress(0x5511D0, 0x551240));
		DefineAddress(SetAll, SelectAddress(0x5515B0, 0x551620));
	}

	namespace Addresses(cAchievementsManager)
	{
		DefineAddress(Get, SelectAddress(0x6755E0, 0x675210));
		DefineAddress(Init, SelectAddress(0x676D90, 0x676C40));
		DefineAddress(GetAchievementDefinition, SelectAddress(0x676770, 0x676620));
		DefineAddress(EvaluateTriggerOp, SelectAddress(0x676800, 0x6766B0));
		DefineAddress(EarnAchievement, SelectAddress(0x676820, 0x6766D0));
		DefineAddress(AddProgress, SelectAddress(0x676FA0, 0x676E50));
		DefineAddress(SetProgressFlags, SelectAddress(0x676FE0, 0x676E90));
	}
}
#endif
