#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cCreatureGameData.h>

namespace Simulator
{
	auto_STATIC_METHOD_(cCreatureGameData, cCreatureGameData*, Get);

	auto_STATIC_METHOD_VOID(cCreatureGameData, AddEvolutionPoints, Args(float a), Args(a));

	auto_STATIC_METHOD_(cCreatureGameData, float, GetEvolutionPoints);

	auto_STATIC_METHOD_VOID(cCreatureGameData, SetEvolutionPoints, Args(float a), Args(a));

	auto_STATIC_METHOD(cCreatureGameData, float, GetEvoPointsToNextBrainLevel, Args(int a), Args(a));

	auto_STATIC_METHOD_VOID(cCreatureGameData, SetAbilityMode, Args(AbilityMode a, bool b), Args(a, b));

	auto_STATIC_METHOD_VOID_(cCreatureGameData, AfterGlideFinish);

	auto_STATIC_METHOD_VOID_(cCreatureGameData, CalculateAvatarNormalizingScale);

	auto_STATIC_METHOD(cCreatureGameData, float, GetAvatarNormalizingScale, Args(cCreatureBase* a), Args(a));
}
#endif
