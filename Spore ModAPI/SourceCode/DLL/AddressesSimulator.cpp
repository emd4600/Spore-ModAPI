#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Simulator\cAbductToolStrategy.h>
#include <Spore\Simulator\cArtilleryWeaponStrategy.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cCreatureAbility.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\cCropCirclesToolStrategy.h>
#include <Spore\Simulator\cDeepSpaceProjectileToolStrategy.h>
#include <Spore\Simulator\cDefaultAoETool.h>
#include <Spore\Simulator\cDefaultBeamTool.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cDragInputProjectileToolStrategy.h>
#include <Spore\Simulator\cDropCargoToolStrategy.h>
#include <Spore\Simulator\Cell\GameModeCell.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\cEnergyRepairToolStrategy.h>
#include <Spore\Simulator\cGameDataUFO.h>
#include <Spore\Simulator\cGameTerrainCursor.h>
#include <Spore\Simulator\cGenesisDeviceToolStrategy.h>
#include <Spore\Simulator\cGetOutOfUFOToolStrategy.h>
#include <Spore\Simulator\cGlobalMindEraseToolStrategy.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cMindEraseToolStrategy.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cPlaceObjectToolStrategy.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cPlayerInventory.h>
#include <Spore\Simulator\cTimeOfDay.h>
#include <Spore\Simulator\cRallyCallToolStrategy.h>
#include <Spore\Simulator\cRepairAOEToolStrategy.h>
#include <Spore\Simulator\cRepairToolStrategy.h>
#include <Spore\Simulator\cScanToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include <Spore\Simulator\cSimulatorSpaceGame.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cToolStrategy.h>
#include <Spore\Simulator\cTribeArchetype.h>
#include <Spore\Simulator\cTurretDefenseMissileWeapon.h>
#include <Spore\Simulator\cTurretFlakWeapon.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\cSimPlanetHighLOD.h>
#include <Spore\Simulator\cMissionManager.h>
#include <Spore\Simulator\Serialization.h>
#include <Spore\Simulator\SubSystem\cRelationshipManager.h>
#include <Spore\Simulator\SubSystem\GameBehaviorManager.h>
#include <Spore\Simulator\SubSystem\GameInputManager.h>
#include <Spore\Simulator\SubSystem\GameModeManager.h>
#include <Spore\Simulator\SubSystem\GameNounManager.h>
#include <Spore\Simulator\SubSystem\GameTimeManager.h>
#include <Spore\Simulator\SubSystem\GameViewManager.h>
#include <Spore\Simulator\SubSystem\PlanetModel.h>
#include <Spore\Simulator\SubSystem\SimulatorSystem.h>
#include <Spore\Simulator\SubSystem\SpacePlayerData.h>
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\TerraformingManager.h>
#include <Spore\Simulator\SubSystem\ToolManager.h>
#include <Spore\Simulator\SubSystem\CommManager.h>
#include <Spore\Simulator\SubSystem\UIEventLog.h>
#include <Spore\Simulator\SubSystem\AnimalSpeciesManager.h>
#include <Spore\Simulator\SubSystem\PlantSpeciesManager.h>
#include <Spore\Simulator\NounClassFactories.h>

namespace Addresses(Simulator)
{
	DefineAddress(GetArchetypeRelationshipsID, SelectAddress(0xC30530, NO_ADDRESS, 0xC30E20));

	DefineAddress(LightingWorld_ptr, SelectAddress(0x1682CD4, NO_ADDRESS, 0x167EA54));

	DefineAddress(GetActiveStar, SelectAddress(0x10222B0, 0x10210E0, 0x10210E0));
	DefineAddress(GetActiveStarRecord, SelectAddress(0x10222C0, 0x10210F0, 0x10210F0));

	DefineAddress(GetPlayerEmpire, SelectAddress(0x1022380, 0x10211B0, 0x10211B0));
	DefineAddress(GetPlayerEmpireID, SelectAddress(0x10220F0, 0x1020F40, 0x1020F40));

	DefineAddress(GetCurrentContext, SelectAddress(0x10220E0, 0x1020F30, 0x1020F30));

	DefineAddress(SpaceTeleportTo, SelectAddress(0x1023A80, , 0x10228C0));
	DefineAddress(GalaxyCoordinatesTo3D, SelectAddress(0x1066640, , 0x1065A60));

	DefineAddress(RegisterNounType, SelectAddress(0xB23CE0, , 0xB23E40));
	DefineAddress(GetNounCreateMap, SelectAddress(0xB22090, , 0xB221A0));
}

namespace Simulator
{
	namespace Addresses(cAbductToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105AC80, NO_ADDRESS, 0x105A0D0));
		DefineAddress(OnMouseUp, SelectAddress(0x1055C90, NO_ADDRESS, 0x10550E0));
		DefineAddress(GetAimPoint, SelectAddress(0x1053B00, NO_ADDRESS, 0x1052FA0));
	}

	namespace Addresses(cArtilleryWeaponStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105C870, NO_ADDRESS, 0x105BCD0));
		DefineAddress(WhileFiring, SelectAddress(0x10588C0, NO_ADDRESS, 0x1057D20));
	}

	namespace Addresses(cCity)
	{
		DefineAddress(IsAboveCity, SelectAddress(0xBD90C0, , 0xBD9D50));
		DefineAddress(SpawnVehicle, SelectAddress(0xBDD410, , 0xBDDEF0));
	}

	namespace Addresses(cCreatureAbility)
	{
		DefineAddress(Parse, SelectAddress(0x4D9140, 0x4D92E0, 0x4D9310));

		DefineAddress(GetAnimationID, SelectAddress(0x4D3B60, NO_ADDRESS, 0x4D3D30));
	}

	namespace Addresses(cCreatureAnimal) 
	{
		DefineAddress(Create, SelectAddress(0xC092A0, NO_ADDRESS, 0xC09B40));
	}

	namespace Addresses(cCreatureBase)
	{
		DefineAddress(PlayAnimation, SelectAddress(0xC11CD0, NO_ADDRESS, 0xC12470));
		DefineAddress(PlayAnimationTo, SelectAddress(0xC14380, NO_ADDRESS, 0xC14B20));
		DefineAddress(WalkTo, SelectAddress(0xC1BE40, NO_ADDRESS, 0xC1C720));
	}

	namespace Addresses(cCropCirclesToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105CAC0, NO_ADDRESS, 0x105BDB0));
	}

	namespace Addresses(cDeepSpaceProjectileToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x10562F0, NO_ADDRESS, 0x1055740));
	}

	namespace Addresses(cDefaultAoETool)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x1053AF0, NO_ADDRESS, 0x1052F90));
		DefineAddress(OnHit, SelectAddress(0x105AC70, NO_ADDRESS, 0x105B660));
		DefineAddress(WhileFiring, SelectAddress(0x10576B0, NO_ADDRESS, 0x1056B20));
		DefineAddress(OnMouseUp, SelectAddress(0x1054A40, NO_ADDRESS, 0x1053E90));

		DefineAddress(func48h, SelectAddress(0x1055BA0, NO_ADDRESS, 0x1054FF0));
		DefineAddress(func4Ch, SelectAddress(0x1054A80, NO_ADDRESS, 0x1053ED0));
	}

	namespace Addresses(cDefaultBeamTool)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x10548B0, NO_ADDRESS, 0x1053D00));
		DefineAddress(OnHit, SelectAddress(0x105ABC0, NO_ADDRESS, 0x105A020));
		DefineAddress(WhileFiring, SelectAddress(0x105AA90, NO_ADDRESS, 0x1059EF0));
		DefineAddress(OnMouseUp, SelectAddress(0x1054910, NO_ADDRESS, 0x1053D60));

		DefineAddress(func48h, SelectAddress(0x1055A20, NO_ADDRESS, 0x1054E70));
		DefineAddress(func4Ch, SelectAddress(0x1054960, NO_ADDRESS, 0x1053DB0));
	}

	namespace Addresses(cDefaultProjectileWeapon)
	{
		DefineAddress(OnHit, SelectAddress(0x105BEC0, NO_ADDRESS, 0x105B310));
		DefineAddress(WhileFiring, SelectAddress(0x1057AA0, NO_ADDRESS, 0x1056F10));
	}

	namespace Addresses(cDragInputProjectileToolStrategy)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x1055D10, NO_ADDRESS, 0x1055160));
		DefineAddress(OnHit, SelectAddress(0x105AC70, NO_ADDRESS, 0x105B660));
		DefineAddress(WhileFiring, SelectAddress(0x1058500, NO_ADDRESS, 0x1057960));
		DefineAddress(ProcessCost, SelectAddress(0x1056020, NO_ADDRESS, 0x1055470));
	}

	namespace Addresses(cDropCargoToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057710, NO_ADDRESS, 0x1056B80));
		DefineAddress(WhileAiming, SelectAddress(0x1054BE0, NO_ADDRESS, 0x1054030));
		DefineAddress(WhileFiring, SelectAddress(0x105B5C0, NO_ADDRESS, 0x105AA10));
		DefineAddress(OnMouseUp, SelectAddress(0x1054B50, NO_ADDRESS, 0x1053FA0));
	}

	namespace Addresses(Cell) 
	{
		DefineAddress(GoalCards_ptr, SelectAddress(0x16B8068, 0x16B4DC8, 0x16B3DE8));
	}

	namespace Cell
	{
		namespace Addresses(GameModeCell)
		{
			DefineAddress(AddRef, SelectAddress(0x1098140, 0xDD3D10, 0xDD3CA0));
			DefineAddress(Release, SelectAddress(0xE1CF40, 0x1154790, 0x1154790));
			DefineAddress(func0Ch, SelectAddress(0xA37650, 0xB1FB00, 0xB1FB30));
			DefineAddress(Initialize, SelectAddress(0xE82280, 0xE81CF0, 0xE81CF0));
			DefineAddress(Dispose, SelectAddress(0xE824C0, 0xE81F30, 0xE81F30));
			DefineAddress(OnEnter, SelectAddress(0xE55950, 0xE55300, 0xE552F0));
			DefineAddress(OnExit, SelectAddress(0xE80190, 0xE7FC00, 0xE7FC00));
			DefineAddress(func20h, SelectAddress(0xE515F0, 0xE50FF0, 0xE50FE0));
			DefineAddress(OnKeyDown, SelectAddress(0xE81E80, 0xE818F0, 0xE818F0));
			DefineAddress(OnKeyUp, SelectAddress(0xE51600, 0xE51000, 0xE50FF0));
			DefineAddress(OnMouseDown, SelectAddress(0xE6CDE0, 0xE6C860, 0xE6C860));
			DefineAddress(OnMouseUp, SelectAddress(0xE5C6F0, 0xE5C110, 0xE5C0F0));
			DefineAddress(OnMouseMove, SelectAddress(0xE51620, 0xE51020, 0xE51010));
			DefineAddress(OnMouseWheel, SelectAddress(0xE7DBC0, 0xE7D660, 0xE7D660));
			DefineAddress(Update, SelectAddress(0xE80F10, 0xE80980, 0xE80980));

			DefineAddress(HandleMessage, SelectAddress(0xE5CB90, 0xE62C90, 0xE62700));
		}
	}

	namespace Addresses(cEmpire)
	{
		DefineAddress(GetSpeciesProfile, SelectAddress(0xC304F0, , 0xC30DE0));
		DefineAddress(SetSpeciesProfile, SelectAddress(0xC32FB0, 0xC337D0, 0xC337F0));
		DefineAddress(sub_C32EA0, SelectAddress(0xC32EA0, 0xC336C0, 0xC336E0));
		DefineAddress(CaptureSystem, SelectAddress(0xC8C320, , 0xC8D190));
	}

	namespace Addresses(cEnergyRepairToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057750, NO_ADDRESS, 0x1056BC0));
		DefineAddress(OnHit, SelectAddress(0x105BC60, NO_ADDRESS, 0x105B0B0));
		DefineAddress(ProcessCost, SelectAddress(0x1054110, NO_ADDRESS, 0x10535A0));
	}

	namespace Addresses(cGameDataUFO)
	{
		DefineAddress(ChangeEnergy, SelectAddress(0xC382C0, NO_ADDRESS, 0xC38B50));
	}
	namespace Addresses(cGameTerrainCursor)
	{
		DefineAddress(GetTerrainCursor, SelectAddress(0xB30BE0, NO_ADDRESS, 0xB30EB0));
	}

	namespace Addresses(cGenesisDeviceToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105CAC0, NO_ADDRESS, 0x105BF20));
	}

	namespace Addresses(cGetOutOfUFOToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054C30, NO_ADDRESS, 0x1054080));
		DefineAddress(Update, SelectAddress(0x1057890, NO_ADDRESS, 0x1056D00));
		DefineAddress(WhileAiming, SelectAddress(0x1054C10, NO_ADDRESS, 0x1054060));
		DefineAddress(OnHit, SelectAddress(0x105BDB0, NO_ADDRESS, 0x105B200));
	}

	namespace Addresses(cGlobalMindEraseToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1059BB0, NO_ADDRESS, 0x1059010));
	}

	namespace Addresses(cGonzagoTimer) 
	{
		DefineAddress(GetSimulatorTime_ptr, SelectAddress(0xB63580, , 0xB63980));
	}

	namespace Addresses(cMindEraseToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105C890, NO_ADDRESS, 0x105BCF0));
	}

	namespace Addresses(cPlaceColonyToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054C70, NO_ADDRESS, 0x10540C0));
		DefineAddress(OnDeselect, SelectAddress(0x1054D50, NO_ADDRESS, 0x10541A0));
		DefineAddress(Update, SelectAddress(0x10596D0, NO_ADDRESS, 0x1058B30));
		DefineAddress(WhileAiming, SelectAddress(0x105C210, NO_ADDRESS, 0x105B670));
		DefineAddress(SelectedUpdate, SelectAddress(0x1054E00, NO_ADDRESS, 0x1054300));
		DefineAddress(OnHit, SelectAddress(0x105C4D0, NO_ADDRESS, 0x105B930));
	}

	namespace Addresses(cPlaceObjectToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1059300, NO_ADDRESS, 0x1058760));
		DefineAddress(OnDeselect, SelectAddress(0x1054E90, NO_ADDRESS, 0x1054250));
		DefineAddress(Update, SelectAddress(0x1058740, NO_ADDRESS, 0x1057BA0));
		DefineAddress(WhileAiming, SelectAddress(0x105C570, NO_ADDRESS, 0x105B9D0));
		DefineAddress(SelectedUpdate, SelectAddress(0x1054E00, NO_ADDRESS, 0x1054300));
		DefineAddress(OnHit, SelectAddress(0x105C7E0, NO_ADDRESS, 0x105BC40));
	}

	namespace Addresses(cPlanet) 
	{
		DefineAddress(GetTemperatureScore, SelectAddress(0xC6FD80, NO_ADDRESS, 0xC70BC0));
	}

	namespace Addresses(cPlayerInventory)
	{
		DefineAddress(GetUnlockableTool, SelectAddress(0xFF4640, 0xFF3BF0, 0xFF3BF0));
	}

	namespace Addresses(cRallyCallToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x105CB20, NO_ADDRESS, 0x105BF80));
	}

	namespace Addresses(cRepairAOEToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1058B90, NO_ADDRESS, 0x1057FF0));
	}

	namespace Addresses(cRepairToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057810, NO_ADDRESS, 0x1056C80));
		DefineAddress(OnHit, SelectAddress(0x105BCF0, NO_ADDRESS, 0x105B140));
		DefineAddress(WhileFiring, SelectAddress(0x10577D0, NO_ADDRESS, 0x1056C40));
		DefineAddress(ProcessCost, SelectAddress(0x1054160, NO_ADDRESS, 0x10535F0));
	}

	namespace Addresses(cScanToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054B10, NO_ADDRESS, 0x1053F60));
		DefineAddress(OnHit, SelectAddress(0x105B400, NO_ADDRESS, 0x105A850));
	}

	namespace Addresses(cSimulatorPlayerUFO)
	{
		DefineAddress(Get, SelectAddress(0xFFC990, NO_ADDRESS, 0xFFBD00));
	}

	namespace Addresses(cSimulatorSpaceGame)
	{
		DefineAddress(Get, SelectAddress(0x10036E0, 0x1002A70, 0x1002A70));
	}

	namespace Addresses(cSpaceToolData)
	{
		DefineAddress(AddAmmo, SelectAddress(0x104D730, 0x104CBE0, 0x104CBE0));
		DefineAddress(ConsumeAmmo, SelectAddress(0x104D760, 0x104CC10, 0x104CC10));
		DefineAddress(GetStrategy, SelectAddress(0x1050490, NO_ADDRESS, 0x1050030));
		DefineAddress(ShowEventLog, SelectAddress(0x1053350, NO_ADDRESS, 0x1052800));
	}

	namespace Addresses(cStarRecord)
	{
		DefineAddress(GetPlanetRecord, SelectAddress(0xBB9B40, NO_ADDRESS, 0xBBABD0));
	}

	namespace Addresses(cToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054340, NO_ADDRESS, 0x1053790));

		DefineAddress(Update, SelectAddress(0x1056CC0, NO_ADDRESS, 0x1056130));
		DefineAddress(WhileAiming, SelectAddress(0x10544E0, NO_ADDRESS, 0x1053930));

		DefineAddress(SelectedUpdate, SelectAddress(0x1054710, NO_ADDRESS, 0x1053B60));
		DefineAddress(OnHit, SelectAddress(0x1059F50, NO_ADDRESS, 0x10593B0));
		DefineAddress(WhileFiring, SelectAddress(0x1057410, NO_ADDRESS, 0x1056880));
		DefineAddress(OnMouseUp, SelectAddress(0x10541D0, NO_ADDRESS, 0x1053660));
		DefineAddress(GetAimPoint, SelectAddress(0x1053A70, NO_ADDRESS, 0x1052F10));
		DefineAddress(func40h, SelectAddress(0x1054740, NO_ADDRESS, 0x1053B90));
	}

	namespace Addresses(cTurretDefenseMissileWeapon)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1057D70, NO_ADDRESS, 0x10571E0));
	}

	namespace Addresses(cTurretFlakWeapon)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1057FD0, NO_ADDRESS, 0x1057430));
	}

	namespace Addresses(cVehicle)
	{
		DefineAddress(Load, SelectAddress(0xCA6060, NO_ADDRESS, 0xCA67C0));
	}

	namespace Addresses(cRelationshipManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D220, 0xB3D390, 0xB3D3C0));

		DefineAddress(IsAtWar, SelectAddress(0xD014C0, 0xD01F80, 0xD01F90));
		DefineAddress(IsAtWar2, SelectAddress(0xD01490, , 0xD01F60));
		DefineAddress(IsAllied, SelectAddress(0xD01560, , 0xD02030));
		DefineAddress(IsAllied2, SelectAddress(0xD01520, , 0xD01FF0));
		DefineAddress(DeclareWar, SelectAddress(0xD05840, 0xD065E0, 0xD065E0));
		DefineAddress(DeclarePeace, SelectAddress(0xD02B90, , 0xD03920));
		DefineAddress(DeclareAlliance, SelectAddress(0xD05BC0, , 0xD06960));
		DefineAddress(BreakAlliance, SelectAddress(0xD013A0, , 0xD01E70));
		DefineAddress(ResetRelationship, SelectAddress(0xD04AD0, , 0xD05870));
		DefineAddress(ApplyRelationship, SelectAddress(0xD054E0, 0xD06280, 0xD06280));
		DefineAddress(RelationshipExists, SelectAddress(0xD010C0, , 0xD01B90));
		DefineAddress(GetRelationshipEventValue, SelectAddress(0xD010F0, , 0xD01BC0));
	}

	namespace Addresses(cGameBehaviorManager) 
	{
		DefineAddress(Get, SelectAddress(0xB3D1C0, , 0xB3D360));
	}

	namespace Addresses(cGameInputManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D1B0, NO_ADDRESS, 0xB3D350));
	}

	namespace Addresses(cGameModeManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D280, 0xB3D3F0, 0xB3D420));

		DefineAddress(GetActiveDifficultyTuning, SelectAddress(0xB1DD10, 0xB1DD90, 0xB1DDC0));
		DefineAddress(GetDifficultyTuning, SelectAddress(0xB1D980, 0xB1DA00, 0xB1DA30));

		DefineAddress(SubmitEditorRequest, SelectAddress(0xB1DD70, , 0xB1DE20));

		//PLACEHOLDER 0xB1E2A0 transition to another game mode?
	}

	namespace Addresses(cGameNounManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D260, 0xB3D3D0, 0xB3D400));
		DefineAddress(CreateInstance, SelectAddress(0xB20A90, 0xB20B80, 0xB20BF0));
		DefineAddress(DestroyInstance, SelectAddress(0xB22450, NO_ADDRESS, 0xB22560));
		DefineAddress(GetData, SelectAddress(0xB21280, 0xB21260, 0xB212D0));

		DefineAddress(UpdateModels, SelectAddress(0xB227E0, NO_ADDRESS, 0xB228F0));
		DefineAddress(SetAvatar, SelectAddress(0xB1FB90, NO_ADDRESS, 0xB1FCA0));
	}

	namespace Addresses(cGameViewManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D1A0, 0xB3D310, 0xB3D340));
	}

	namespace Addresses(cPlanetModel)
	{
		DefineAddress(Get, SelectAddress(0xB3D2B0, NO_ADDRESS, 0xB3D450));

		DefineAddress(IsInWater, SelectAddress(0xB7DC90, NO_ADDRESS, 0xB7E530));
		DefineAddress(GetNearestCity, SelectAddress(0xB88DF0, NO_ADDRESS, 0xB895F0));
		DefineAddress(ToSurface, SelectAddress(0xB80F30, NO_ADDRESS, 0xB81780));
		DefineAddress(GetGravity, SelectAddress(0xB7DD40, NO_ADDRESS, 0xB7E5E0));
		DefineAddress(GetHeightAt, SelectAddress(0xB7E860, NO_ADDRESS, 0xB7F0C0));
		DefineAddress(GetOrientation, SelectAddress(0xB7EB40, , 0xB7F3A0));
	}

	namespace Addresses(cSimulatorSystem)
	{
		DefineAddress(Get, SelectAddress(0xB3D190, , 0xB3D330));
		DefineAddress(Create, SelectAddress(0xB5DD00, , 0xB5E160));
	}

	namespace Addresses(SpacePlayerData)
	{
		DefineAddress(ptr, SelectAddress(0x16E1D0C, 0x16DEA6C, 0x16DDA8C));
	}

	namespace Addresses(cStarManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D200, 0xB3D370, 0xB3D3A0));

		DefineAddress(GetPlanetRecord, SelectAddress(0xBA6540, 0xBA6EF0, 0xBA6F10));
		DefineAddress(NextPoliticalID, SelectAddress(0xBA5DA0, NO_ADDRESS, 0xBA6780));
		DefineAddress(GetEmpireForStar, SelectAddress(0xBB0230, NO_ADDRESS, 0xBB14D0));
		DefineAddress(RecordToPlanet, SelectAddress(0xBB4960, NO_ADDRESS, 0xBB5B50));
		DefineAddress(FindClosestStar, SelectAddress(0xBAFD80, , 0xBB1020));
		DefineAddress(FindStars, SelectAddress(0xBAFF70, , 0xBB1210));
	}

	namespace Addresses(cSpaceTradeRouteManager)
	{
		DefineAddress(HasTradeRoute, SelectAddress(0x1038C10, NO_ADDRESS, 0x1037D40));
	}

	namespace Addresses(cTerraformingManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D390, NO_ADDRESS, 0xB3D530));

		DefineAddress(GetTScore, SelectAddress(0xBBB750, NO_ADDRESS, 0xBBC7E0));
		DefineAddress(CalculateTScore, SelectAddress(0xFC2760, NO_ADDRESS, 0xFC2040));
	}

	namespace Addresses(cToolManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D2F0, 0xB3D460, 0xB3D490));

		DefineAddress(LoadTool, SelectAddress(0x104EEA0, 0x104E350, 0x104E350));
		DefineAddress(GetStrategy, SelectAddress(0x10503B0, NO_ADDRESS, 0x104F860));

		DefineAddress(ActivateTool, SelectAddress(0x1050710, NO_ADDRESS, 0x104FBC0));
		DefineAddress(DeactivateTool, SelectAddress(0x1050770, NO_ADDRESS, 0x104FC20));
		DefineAddress(OnMouseUp, SelectAddress(0x10505F0, NO_ADDRESS, 0x104FAA0));
	}


	namespace Addresses(ClassSerializer)
	{
		DefineAddress(Read, SelectAddress(0x693F20, , 0x693DE0));
		DefineAddress(Write, SelectAddress(0x692B10, , 0x6928C0));
	}

	namespace Addresses(XmlSerializer)
	{
		DefineAddress(AttributesToXml, SelectAddress(0x695D40, , 0x695B20));
	}

	namespace Addresses(cGameData)
	{
		DefineAddress(Write, SelectAddress(0xB18430, , 0xB184D0));
		DefineAddress(Read, SelectAddress(0xB184A0, , 0xB18540));
		DefineAddress(func18h, SelectAddress(0xB18270, , 0xB18320));
		DefineAddress(WriteToXML, SelectAddress(0xB18390, , 0xB18440));

		DefineAddress(SetDefinitionID, SelectAddress(0xB18290, , 0xB18340));
		DefineAddress(SetGameDataOwner, SelectAddress(0xB183E0, , 0xB18490));
		DefineAddress(IsDestroyed, SelectAddress(0xB18260, , 0xB18310));

		DefineAddress(SetGameDataOwner2, SelectAddress(0xB183E0, , 0xB18490));

		DefineAddress(func3Ch, SelectAddress(0xB18280, , 0xB18330));

		DefineAddress(RemoveOwner, SelectAddress(0xAFF820, , 0xAFFD20));

		DefineAddress(WriteAsText, SelectAddress(0xB182B0, , 0xB18360));
	}

	namespace Addresses(cCommManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D400, , 0xB3D5A0));

		DefineAddress(CreateCivCommEvent, SelectAddress(0xAEABB0, , 0xAEB1C0));
		DefineAddress(CreateSpaceCommEvent, SelectAddress(0xAEAAD0, , 0xAEB0E0));
		DefineAddress(ShowCommEvent, SelectAddress(0xAEB800, , 0xAEBE10));
		DefineAddress(HandleCivCommAction, SelectAddress(0xAEB200, , 0xAEB810));
		DefineAddress(HandleSpaceCommAction, SelectAddress(0xAEB120, , 0xAEB730));
		DefineAddress(IsCommScreenActive, SelectAddress(0xAE8EA0, , 0xAE9310));
	};

	namespace Addresses(cUIEventLog)
	{
		DefineAddress(Get, SelectAddress(0xB3D340, , 0xB3D4E0));
		DefineAddress(ShowEvent, SelectAddress(0xDD7810, , 0xDD85E0));
		DefineAddress(SetDescription, SelectAddress(0xDD6120, , 0xDD6D80));
		DefineAddress(HideEvent, SelectAddress(0xDD6040, , 0xDD6CA0));
		DefineAddress(SetVisible, SelectAddress(0xDD7F70, , 0xDD8D40));
	}

	namespace Addresses(cSimPlanetHighLOD)
	{
		DefineAddress(DestroyCity, SelectAddress(0xFFB440, , 0xFFA7B0));
	}

	namespace Addresses(cMissionManager)
	{
		DefineAddress(Get, SelectAddress(0xFEC0C0, , 0xFEB880));
		DefineAddress(CreateMission, SelectAddress(0xFECC50, , 0xFEC420));
		DefineAddress(ChooseMission, SelectAddress(0xFEF450, , 0xFEEBC0));
		DefineAddress(HasMissionsAvailable, SelectAddress(0xFEEAE0, , 0xFEE260));
		DefineAddress(GetMissionByID, SelectAddress(0xFEEB90, , 0xFEE310));
		DefineAddress(GetMissionTrackColor, SelectAddress(0xFEC510, , 0xFEBCE0));
		DefineAddress(ThereIsEventInPlanet, SelectAddress(0xFEE8A0, , 0xFEE020));
	}

	namespace Addresses(cGameTimeManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D2E0, , 0xB3D480));
		DefineAddress(Pause, SelectAddress(0xB32140, , 0x00b32330));
		DefineAddress(Resume, SelectAddress(0xB32170, , 0x00b32360));
		DefineAddress(Toggle, SelectAddress(0xB32170, , 0x00b32390));
		DefineAddress(GetPauseCount, SelectAddress(0xB31EE0, , 0x00b321e0));
		DefineAddress(ConvertDeltaTime, SelectAddress(0xB31AA0, , 0xb31da0));
		DefineAddress(SetSpeed, SelectAddress(0xB32370, , 0x00b32560));
	}

	namespace Addresses(cTimeOfDay)
	{
		DefineAddress(Get, SelectAddress(0xBC2550, , 0xBC3220));
		DefineAddress(SetSpeedMultiplier, SelectAddress(0xBC1D60, , 0xBC2A30));
		DefineAddress(SetDayDuration, SelectAddress(0xBC1CD0, , 0xBC29A0));
		DefineAddress(SetTimeOfDay, SelectAddress(0xBC23A0, , 0xBC3070));
	}

	namespace Addresses(cAnimalSpeciesManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D3B0, , 0xB3D550));
		DefineAddress(CreateAnimalItem, SelectAddress(0xAC0E90, , 0xAC0C00));
	}

	namespace Addresses(cPlantSpeciesManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D380, , 0xB3D520));
		DefineAddress(CreateAnimalItem, SelectAddress(0xB8FEF0, , 0xB90560));
	}

	namespace Addresses(cSpaceInventoryItem)
	{
		DefineAddress(CreateMultiDeliveryObject, SelectAddress(0xC86C00, , 0xC86C00));
	}

	namespace Addresses(cTribeArchetype)
	{
		DefineAddress(GetTribeArchetype, SelectAddress(0xC8E060, , 0xC8EC00));
	}
}
#endif
