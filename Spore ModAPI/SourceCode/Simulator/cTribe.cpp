#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cTribeArchetype.h>
#include <Spore\Simulator\cTribe.h>
#include <Spore\Simulator\cTribeTool.h>
#include <Spore\Simulator\cTribeToolData.h>
#include <Spore\Simulator\cTribeInputStrategy.h>

namespace Simulator
{
	auto_STATIC_METHOD(cTribeArchetype, cTribeArchetype*, GetTribeArchetype,
		Args(uint32_t archetype), Args(archetype));
	

	auto_STATIC_METHOD(Simulator, cTribe*, SpawnNpcTribe,
		Args(const Math::Vector3& position, int tribeArchetype, int numMembers, int arg0, bool arg1, cSpeciesProfile* species),
		Args(position, tribeArchetype, numMembers, arg0, arg1, species));

	auto_METHOD_VOID(cTribe, UpdateFoodVisuals, Args(float a), Args(a));

	auto_METHOD(cTribe, cTribeTool*, GetToolByType, Args(int toolType), Args(toolType));

	eastl::vector<cFishHotSpotUnk>& GetTribeFishHotSpots() {
		return *(eastl::vector<cFishHotSpotUnk>*)(GetAddress(Simulator, sTribeFishHotSpots_ptr));
	}

	cGonzagoTimer& GetTribeFishTimer() {
		return *(cGonzagoTimer*)(GetAddress(Simulator, sTribeFishTimer_ptr));
	}

	uint64_t GetTribeFishEndTime() {
		return *(uint64_t*)(GetAddress(Simulator, sTribeFishEndTime_ptr));
	}
	void SetTribeFishEndTime(uint64_t value) {
		*(uint64_t*)(GetAddress(Simulator, sTribeFishEndTime_ptr)) = value;
	}


	auto_METHOD_(cTribeTool, int, GetToolClass);
	auto_METHOD_(cTribeTool, int, GetRefundMoney);


	auto_STATIC_METHOD_VOID_(Simulator, LoadTribeToolsData);

	eastl::array<cTribeToolData*, 12> GetTribeToolDataArray() {
		return *(eastl::array<cTribeToolData*, 12>*)(GetAddress(Simulator, sTribeToolDataArray_ptr));
	}

	auto_STATIC_METHOD(Simulator, cTribeToolData*, GetTribeToolData, Args(int a), Args(a));

	auto_STATIC_METHOD_VOID_(Simulator, DisposeTribeToolsData);


	auto_METHOD(cTribeInputStrategy, int, ChooseInputActionID, 
		Args(cGameData* object, int unk), Args(object, unk));

	auto_METHOD(cTribeInputStrategy, bool, DoToolActionForAllSelected,
		Args(cTribeTool* tribeTool), Args(tribeTool));

	auto_METHOD_VOID(cTribeInputStrategy, DoActionForAllSelected, 
		Args(int citizenActionId, cGameData* actionObject, int unk),
		Args(citizenActionId, actionObject, unk));

	auto_METHOD_VOID(cTribeInputStrategy, DoActionGeneric, Args(cGameData* actionObject), Args(actionObject));

	auto_METHOD_VOID_(cTribeInputStrategy, SetHoverObjectCursorAndRollover);

	bool cTribeInputStrategy::IsInEditor() {
		return *(bool*)(GetAddress(cTribeInputStrategy, sIsInEditor_ptr));
	}

}
#endif