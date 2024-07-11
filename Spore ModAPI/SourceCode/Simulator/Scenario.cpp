#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cScenarioData.h>
#include <Spore\Simulator\cScenarioPlayMode.h>
#include <Spore\Simulator\cScenarioTerraformMode.h>
#include <Spore\Simulator\cScenarioEditHistory.h>
#include <Spore\Simulator\cScenarioSimulator.h>
#include <Spore\Simulator\cScenarioPowerup.h>

namespace Simulator
{
	auto_METHOD_VOID(cScenarioData, Initialize, Args(bool index), Args(index));

	auto_METHOD_VOID_(cScenarioData, StartHistoryEntry);
	auto_METHOD_VOID_(cScenarioData, CommitHistoryEntry);

	auto_METHOD(cScenarioData, cScenarioClass*, GetClass, Args(int index), Args(index));

	auto_METHOD(cScenarioData, cScenarioClassAct*, GetCurrentClassAct, Args(cGameData* pObject), Args(pObject));

	auto_METHOD(cScenarioData, cGameData*, GetObjectForMarker, Args(cScenarioMarker* p), Args(p));
	auto_METHOD(cScenarioData, cScenarioMarker*, GetMarkerForObject, Args(cGameData* p), Args(p));

	auto_STATIC_METHOD_(cScenarioData, int, GetEditModeActIndex);

	auto_STATIC_METHOD(cScenarioData, cGameData*, CreateObjectInstance, 
		Args(const ResourceKey& name, const Vector3& position, const Quaternion& orientation,
			float scale, bool isAvatar, int scenarioClassIndex, cScenarioMarker* pMarker, cScenarioMarkerAct* pActs, int actIndex),
		Args(name, position, orientation, scale, isAvatar, scenarioClassIndex, pMarker, pActs, actIndex));

	auto_STATIC_METHOD(cScenarioData, cGameData*, CreatePowerupObjectInstance,
		Args(App::PropertyList* pPropList, cScenarioMarker* pMarker, int scenarioClassIndex),
		Args(pPropList, pMarker, scenarioClassIndex));

	cScenarioEditHistory* cScenarioEditHistory::Get() 
	{
		return (cScenarioEditHistory*)GetAddress(cScenarioEditHistory, ptr);
	}

	auto_METHOD(cScenarioResource, bool, Read, Args(IO::IStream* pStream), Args(pStream));
	auto_METHOD(cScenarioResource, bool, Write, Args(IO::IStream* pStream), Args(pStream));

	auto_METHOD_VOID_(cScenarioTerraformMode, StartHistoryEntry);
	auto_METHOD_VOID_(cScenarioTerraformMode, CommitHistoryEntry);
	auto_METHOD_VOID(cScenarioTerraformMode, SetWaterColor, Args(const ColorRGB& color), Args(color));
	auto_METHOD_VOID(cScenarioTerraformMode, SetAtmosphereColor, Args(const ColorRGB& color), Args(color));
	auto_METHOD_VOID(cScenarioTerraformMode, SetCliffColor, Args(const ColorRGB& color), Args(color));
	auto_METHOD_VOID(cScenarioTerraformMode, SetBeachColor, Args(const ColorRGB& color), Args(color));

	auto_STATIC_METHOD(cScenarioClass, ScenarioObjectType, GetObjectType, Args(const ResourceKey& key), Args(key));
	auto_METHOD_(cScenarioClass, bool, IsConsumible);


	auto_STATIC_METHOD_(cScenarioSimulator, cScenarioSimulator*, Get);

	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateMedKit, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateEnergyKit, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateSpeedBoost, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateDamageBoost, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateArmorBoost, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateMine, Args(cScenarioPowerup* p1, cCombatant* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateJumpPad, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateTeleporter, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));
	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateGrenade, Args(cScenarioPowerup* p1, cCreatureBase* p2), Args(p1, p2));

	auto_STATIC_METHOD_VOID(cScenarioPowerup, ActivateGate,
		Args(cCreatureBase* p1, cScenarioPowerup* p2, cScenarioPowerup* p3),
		Args(p1, p2, p3));

	auto_STATIC_METHOD_VOID(cScenarioPowerup, ReactToPowerup,
		Args(cGameData* pFirst, cGameData* pSecond, void* p),
		Args(pFirst, pSecond, p));


	auto_METHOD_VOID(cScenarioPlayMode, SetCurrentAct, Args(int index, bool arg), Args(index, arg));
	auto_METHOD_VOID(cScenarioPlayMode, JumpToAct, Args(int actIndex), Args(actIndex));
	auto_METHOD_VOID_(cScenarioPlayMode, Initialize);
	auto_METHOD_VOID(cScenarioPlayMode, SetState, Args(ScenarioPlayModeState state), Args(state));
	auto_METHOD_(cScenarioPlayMode, bool, UpdateGoals);
	auto_METHOD_VOID(cScenarioPlayMode, Update, Args(int deltaTime), Args(deltaTime));
	auto_METHOD_VOID_(cScenarioPlayMode, CompleteAct);
	auto_METHOD_VOID_(cScenarioPlayMode, CheckGoalProgress);
	auto_STATIC_METHOD_VOID_(cScenarioPlayMode, RemoveInvisibleClasses);
	auto_STATIC_METHOD_VOID_(cScenarioPlayMode, ReadScenarioTuning);
}
#endif