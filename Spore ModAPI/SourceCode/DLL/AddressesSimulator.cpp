#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Simulator\cAbductToolStrategy.h>
#include <Spore\Simulator\cArtilleryWeaponStrategy.h>
#include <Spore\Simulator\cBadgeManager.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cCelestialBody.h>
#include <Spore\Simulator\cCreatureAbility.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cCreatureCitizen.h>
#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\cCropCirclesToolStrategy.h>
#include <Spore\Simulator\cDeepSpaceProjectileToolStrategy.h>
#include <Spore\Simulator\cDefaultAoETool.h>
#include <Spore\Simulator\cDefaultBeamTool.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cDragInputProjectileToolStrategy.h>
#include <Spore\Simulator\cDropCargoToolStrategy.h>
#include <Spore\Simulator\Cell\cCellGame.h>
#include <Spore\Simulator\Cell\cCellGFX.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>
#include <Spore\Simulator\Cell\cCelLResource.h>
#include <Spore\Simulator\Cell\cCellUI.h>
#include <Spore\Simulator\Cell\CellFunctions.h>
#include <Spore\Simulator\cCreatureGameData.h>
#include <Spore\Simulator\cCommunityLayout.h>
#include <Spore\Simulator\cEmpire.h>
#include <Spore\Simulator\cEnergyRepairToolStrategy.h>
#include <Spore\Simulator\cGameDataUFO.h>
#include <Spore\Simulator\cGameTerrainCursor.h>
#include <Spore\Simulator\cGenesisDeviceToolStrategy.h>
#include <Spore\Simulator\cGetOutOfUFOToolStrategy.h>
#include <Spore\Simulator\cGlobalMindEraseToolStrategy.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cMindEraseToolStrategy.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cPlaceObjectToolStrategy.h>
#include <Spore\Simulator\cPlanet.h>
#include <Spore\Simulator\cPlanetRecord.h>
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
#include <Spore\Simulator\cSpaceNames.h>
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cScenarioData.h>
#include <Spore\Simulator\cScenarioPlayMode.h>
#include <Spore\Simulator\cScenarioResource.h>
#include <Spore\Simulator\cScenarioEditHistory.h>
#include <Spore\Simulator\cScenarioPowerup.h>
#include <Spore\Simulator\cScenarioSimulator.h>
#include <Spore\Simulator\cScenarioTerraformMode.h>
#include <Spore\Simulator\cCultureSet.h>
#include <Spore\Simulator\SubSystem\SpaceGfx.h>
#include <Spore\Simulator\cHerd.h>
#include <Spore\Simulator\cToolStrategy.h>
#include <Spore\Simulator\cTribeArchetype.h>
#include <Spore\Simulator\cTurretDefenseMissileWeapon.h>
#include <Spore\Simulator\cTurretFlakWeapon.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\cSimPlanetHighLOD.h>
#include <Spore\Simulator\cSolarSystem.h>
#include <Spore\Simulator\cStar.h>
#include <Spore\Simulator\cMissionManager.h>
#include <Spore\Simulator\cSimulatorUniverse.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\Serialization.h>
#include <Spore\Simulator\SpaceConstants.h>
#include <Spore\Simulator\cArtilleryProjectile.h>
#include <Spore\Simulator\cCulturalProjectile.h>
#include <Spore\Simulator\cFlakProjectile.h>
#include <Spore\Simulator\cResourceProjectile.h>
#include <Spore\Simulator\cCollectableItems.h>
#include <Spore\Simulator\cSpaceDefenseMissile.h>
#include <Spore\Simulator\cDefaultToolProjectile.h>
#include <Spore\Simulator\cPlanetaryArtifact.h>
#include <Spore\Simulator\cTribe.h>
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
#include <Spore\Simulator\SubSystem\SpaceTrading.h>
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\TerraformingManager.h>
#include <Spore\Simulator\SubSystem\ToolManager.h>
#include <Spore\Simulator\SubSystem\CommManager.h>
#include <Spore\Simulator\SubSystem\UIEventLog.h>
#include <Spore\Simulator\SubSystem\AnimalSpeciesManager.h>
#include <Spore\Simulator\SubSystem\PlantSpeciesManager.h>
#include <Spore\Simulator\SubSystem\GamePersistenceManager.h>
#include <Spore\Simulator\NounClassFactories.h>

namespace Addresses(Simulator)
{
	DefineAddress(GetArchetypeRelationshipsID, SelectAddress(0xC30530, 0xC30E20));

	DefineAddress(GetActiveStar, SelectAddress(0x10222B0, 0x10210E0));
	DefineAddress(GetActiveStarRecord, SelectAddress(0x10222C0, 0x10210F0));

	DefineAddress(GetPlayerEmpire, SelectAddress(0x1022380, 0x10211B0));
	DefineAddress(GetPlayerEmpireID, SelectAddress(0x10220F0, 0x1020F40));

	DefineAddress(GetCurrentContext, SelectAddress(0x10220E0, 0x1020F30));

	DefineAddress(SpaceTeleportTo, SelectAddress(0x1023A80, 0x10228C0));
	DefineAddress(GalaxyCoordinatesTo3D, SelectAddress(0x1066640, 0x1065A60));

	DefineAddress(RegisterNounType, SelectAddress(0xB23CE0, 0xB23E40));
	DefineAddress(GetNounCreateMap, SelectAddress(0xB22090, 0xB221A0));

	DefineAddress(GetBinarySystemStarTypes, SelectAddress(0xC8A790, 0xC8B600));
	DefineAddress(GetBinarySystemBaseRadius, SelectAddress(0xC83720, 0xC845B0));
	DefineAddress(GetSolarStarTemperature, SelectAddress(0xC83610, 0xC844A0));
	DefineAddress(GetSolarStarMass, SelectAddress(0xC834A0, 0xC84330));
	DefineAddress(GetSolarStarRadius, SelectAddress(0xC83420, 0xC842B0));
	DefineAddress(GetSolarStarRotationRate, SelectAddress(0xC835A0, 0xC84430));
	DefineAddress(GetSolarStarOrbitRadius, SelectAddress(0xC83F60, 0xC84DF0));
	DefineAddress(GetPlanetTemperatureType, SelectAddress(0xFC26B0, 0xFC1F90));
	DefineAddress(IsBinaryStar, SelectAddress(0xC8A770, 0xC8B5E0));
	DefineAddress(IsNotStarOrBinaryStar, SelectAddress(0xC8A840, 0xC8B6B0));

	DefineAddress(LaunchDefaultToolProjectile, SelectAddress(0x1054F40, 0x1054390));

	DefineAddress(sCreatureGameUnlockCategoriesCount, SelectAddress(0x1587278, 0x1583298));

	DefineAddress(CreateUFO, SelectAddress(0x102BB50, 0x102AC60));

	DefineAddress(SpawnNpcTribe, SelectAddress(0xC92860, 0xC932F0));
	
	DefineAddress(GetMainSpeciesImageKey, SelectAddress(0x1066AF0, 0x1065F10));

	DefineAddress(GetPlayerHomePlanet, SelectAddress(0x10223F0, 0x1021220));

#ifndef SDK_TO_GHIDRA
	DefineAddress(LightingWorld_ptr, SelectAddress(0x1682CD4, 0x167EA54));
	DefineAddress(PrecalculatedSolarStarRadius_ptr, SelectAddress(0x157DCF0, 0x1579D10));
#else
	DefineAddress(sLightingWorld, SelectAddress(0x1682CD4, 0x167EA54));
	DefineAddress(sPrecalculatedSolarStarRadius, SelectAddress(0x157DCF0, 0x1579D10));
	DefineAddress(sSimulatorUniverse, SelectAddress(0x16E0A18, 0x16DC798));
#endif
}

namespace Simulator
{
	namespace Addresses(cEllipticalOrbit)
	{
		DefineAddress(Precalculate, SelectAddress(0xFE8C10, 0xFE82E0));
	}

	namespace Addresses(cAbductToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105AC80, 0x105A0D0));
		DefineAddress(OnMouseUp, SelectAddress(0x1055C90, 0x10550E0));
		DefineAddress(GetAimPoint, SelectAddress(0x1053B00, 0x1052FA0));
	}

	namespace Addresses(cArtilleryWeaponStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105C870, 0x105BCD0));
		DefineAddress(WhileFiring, SelectAddress(0x10588C0, 0x1057D20));
	}

	namespace Addresses(cCity)
	{
		DefineAddress(IsAboveCity, SelectAddress(0xBD90C0, 0xBD9D50));
		DefineAddress(SpawnVehicle, SelectAddress(0xBDD410, 0xBDDEF0));
		DefineAddress(ProcessBuildingUpdate, SelectAddress(0xBE1C10, 0xBE2590));
		DefineAddress(AddBuilding, SelectAddress(0xBE16C0, 0xBE2040));
		DefineAddress(RemoveBuilding, SelectAddress(0xBE2B20, 0xBE34A0));
	}

	namespace Addresses(cCreatureAbility)
	{
		DefineAddress(Parse, SelectAddress(0x4D9140, 0x4D9310));

		DefineAddress(GetAnimationID, SelectAddress(0x4D3B60, 0x4D3D30));
	}

	namespace Addresses(cCreatureAnimal) 
	{
		DefineAddress(Create, SelectAddress(0xC092A0, 0xC09B40));
		DefineAddress(NPCTickAI, SelectAddress(0xC08CD0, 0xC09570));
		DefineAddress(AvatarTickAI, SelectAddress(0xC03710, 0xC04020));
		DefineAddress(OnJumpLand, SelectAddress(0xC044D0, 0xC04CB0));
		DefineAddress(OnStartSwimming, SelectAddress(0xC04610, 0xC04DF0));
		DefineAddress(Update, SelectAddress(0xC0A590, 0xC0AE30));
	}

	namespace Addresses(cCreatureCitizen) {
		DefineAddress(Update, SelectAddress(0xC24210, 0xC24A30));
	}

	namespace Addresses(cCreatureBase)
	{
		DefineAddress(PlayAnimation, SelectAddress(0xC11CD0, 0xC12470));
		DefineAddress(PlayAnimationTo, SelectAddress(0xC14380, 0xC14B20));
		DefineAddress(WalkTo, SelectAddress(0xC1BE40, 0xC1C720));
		DefineAddress(GetAbilityIndexByType, SelectAddress(0xC0B930, 0xC0C1E0));
		DefineAddress(GetAnimalTarget, SelectAddress(0xC0E740, 0xC0EFF0));
		DefineAddress(CreateEffectForPool1Renamed, SelectAddress(0xC1C9A0, 0xC1D280));
		DefineAddress(CreateEffectForPool1, SelectAddress(0xC1CB10, 0xC1D3F0));
		DefineAddress(CreateAndStartEffectForPool1Renamed, SelectAddress(0xC1CC80, 0xC1D560));
		DefineAddress(CreateAndStartEffectForPool1, SelectAddress(0xC1CCB0, 0xC1D590));
		DefineAddress(CreateEffectForPool2Renamed, SelectAddress(0xC1CCE0, 0xC1D5C0));
		DefineAddress(StartOrStopEffectFromPool1, SelectAddress(0xC1FA20, 0xC20300));
		DefineAddress(StartOrStopEffectFromPool2, SelectAddress(0xC1CE60, 0xC1D740));
		DefineAddress(GetEffectFromPools, SelectAddress(0xC14830, 0xC14FD0));
		DefineAddress(StopEffectFromPools, SelectAddress(0xC16CB0, 0xC174B0));
		DefineAddress(PlayVoice, SelectAddress(0xC1CEC0, 0xC1D7A0));
		DefineAddress(PlayAbility, SelectAddress(0xC1DCE0, 0xC1E5C0));
		DefineAddress(DoJump, SelectAddress(0xC184A0, 0xC18CA0));
		DefineAddress(ConsumeEnergy, SelectAddress(0xC15780, 0xC15F20));
		DefineAddress(OnJumpLand, SelectAddress(0xC14670, 0xC14E10));
		DefineAddress(OnStartSwimming, SelectAddress(0xC147D0, 0xC14F70));
		DefineAddress(Update, SelectAddress(0xC20C50, 0xC21530));
	}

	namespace Addresses(cCropCirclesToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105CAC0, 0x105BDB0));
	}

	namespace Addresses(cDeepSpaceProjectileToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x10562F0, 0x1055740));
	}

	namespace Addresses(cDefaultAoETool)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x1053AF0, 0x1052F90));
		DefineAddress(OnHit, SelectAddress(0x105AC70, 0x105B660));
		DefineAddress(WhileFiring, SelectAddress(0x10576B0, 0x1056B20));
		DefineAddress(OnMouseUp, SelectAddress(0x1054A40, 0x1053E90));

		DefineAddress(func48h, SelectAddress(0x1055BA0, 0x1054FF0));
		DefineAddress(func4Ch, SelectAddress(0x1054A80, 0x1053ED0));
	}

	namespace Addresses(cDefaultBeamTool)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x10548B0, 0x1053D00));
		DefineAddress(OnHit, SelectAddress(0x105ABC0, 0x105A020));
		DefineAddress(WhileFiring, SelectAddress(0x105AA90, 0x1059EF0));
		DefineAddress(OnMouseUp, SelectAddress(0x1054910, 0x1053D60));

		DefineAddress(func48h, SelectAddress(0x1055A20, 0x1054E70));
		DefineAddress(func4Ch, SelectAddress(0x1054960, 0x1053DB0));
	}

	namespace Addresses(cDefaultProjectileWeapon)
	{
		DefineAddress(OnHit, SelectAddress(0x105BEC0, 0x105B310));
		DefineAddress(WhileFiring, SelectAddress(0x1057AA0, 0x1056F10));
	}

	namespace Addresses(cDragInputProjectileToolStrategy)
	{
		DefineAddress(OnMouseDown, SelectAddress(0x1055D10, 0x1055160));
		DefineAddress(OnHit, SelectAddress(0x105AC70, 0x105B660));
		DefineAddress(WhileFiring, SelectAddress(0x1058500, 0x1057960));
		DefineAddress(ProcessCost, SelectAddress(0x1056020, 0x1055470));
	}

	namespace Addresses(cDropCargoToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057710, 0x1056B80));
		DefineAddress(WhileAiming, SelectAddress(0x1054BE0, 0x1054030));
		DefineAddress(WhileFiring, SelectAddress(0x105B5C0, 0x105AA10));
		DefineAddress(OnMouseUp, SelectAddress(0x1054B50, 0x1053FA0));
	}

	namespace Addresses(Cell) 
	{
#ifndef SDK_TO_GHIDRA
		DefineAddress(GoalCards_ptr, SelectAddress(0x16B8068, 0x16B3DE8));
#else
		DefineAddress(sGoalCards, SelectAddress(0x16B8068, 0x16B3DE8));
#endif
	}

#ifndef SDK_TO_GHIDRA
	namespace Cell
	{
		namespace Addresses(GameModeCell)
		{
			DefineAddress(AddRef, SelectAddress(0x1098140, 0xDD3CA0));
			DefineAddress(Release, SelectAddress(0xE1CF40, 0x1154790));
			DefineAddress(func0Ch, SelectAddress(0xA37650, 0xB1FB30));
			DefineAddress(Initialize, SelectAddress(0xE82280, 0xE81CF0));
			DefineAddress(Dispose, SelectAddress(0xE824C0, 0xE81F30));
			DefineAddress(OnEnter, SelectAddress(0xE55950, 0xE552F0));
			DefineAddress(OnExit, SelectAddress(0xE80190, 0xE7FC00));
			DefineAddress(func20h, SelectAddress(0xE515F0, 0xE50FE0));
			DefineAddress(OnKeyDown, SelectAddress(0xE81E80, 0xE818F0));
			DefineAddress(OnKeyUp, SelectAddress(0xE51600, 0xE50FF0));
			DefineAddress(OnMouseDown, SelectAddress(0xE6CDE0, 0xE6C860));
			DefineAddress(OnMouseUp, SelectAddress(0xE5C6F0, 0xE5C0F0));
			DefineAddress(OnMouseMove, SelectAddress(0xE51620, 0xE51010));
			DefineAddress(OnMouseWheel, SelectAddress(0xE7DBC0, 0xE7D660));
			DefineAddress(Update, SelectAddress(0xE80F10, 0xE80980));

			DefineAddress(HandleMessage, SelectAddress(0xE5CB90, 0xE62700));
		}
	}
#endif

	namespace Addresses(cEmpire)
	{
		DefineAddress(GetSpeciesProfile, SelectAddress(0xC304F0, 0xC30DE0));
		DefineAddress(SetSpeciesProfile, SelectAddress(0xC32FB0, 0xC337F0));
		DefineAddress(sub_C32EA0, SelectAddress(0xC32EA0, 0xC336E0));
		DefineAddress(CaptureSystem, SelectAddress(0xC8C320, 0xC8D190));
		DefineAddress(UpdateAndGetColor, SelectAddress(0xC325F0, 0xC32E30));
		DefineAddress(AddStarOwnership, SelectAddress(0xC33AB0, 0xC34300));
		DefineAddress(RequireHomePlanet, SelectAddress(0xC30F90, 0xC31890));
	}

	namespace Addresses(cEnergyRepairToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057750, 0x1056BC0));
		DefineAddress(OnHit, SelectAddress(0x105BC60, 0x105B0B0));
		DefineAddress(ProcessCost, SelectAddress(0x1054110, 0x10535A0));
	}

	namespace Addresses(cGameDataUFO)
	{
		DefineAddress(ChangeEnergy, SelectAddress(0xC382C0, 0xC38B50));
		DefineAddress(Initialize, SelectAddress(0xC3D8D0, 0xC3E210));
	}
	namespace Addresses(cGameTerrainCursor)
	{
		DefineAddress(GetTerrainCursor, SelectAddress(0xB30BE0, 0xB30EB0));
	}

	namespace Addresses(cGenesisDeviceToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105CAC0, 0x105BF20));
	}

	namespace Addresses(cGetOutOfUFOToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054C30, 0x1054080));
		DefineAddress(Update, SelectAddress(0x1057890, 0x1056D00));
		DefineAddress(WhileAiming, SelectAddress(0x1054C10, 0x1054060));
		DefineAddress(OnHit, SelectAddress(0x105BDB0, 0x105B200));
	}

	namespace Addresses(cGlobalMindEraseToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1059BB0, 0x1059010));
	}

	namespace Addresses(cGonzagoTimer) 
	{
		DefineAddress(GetSimulatorTime_ptr, SelectAddress(0xB63580, 0xB639C0));
	}

	namespace Addresses(cMindEraseToolStrategy)
	{
		DefineAddress(OnHit, SelectAddress(0x105C890, 0x105BCF0));
	}

	namespace Addresses(cPlaceColonyToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054C70, 0x10540C0));
		DefineAddress(OnDeselect, SelectAddress(0x1054D50, 0x10541A0));
		DefineAddress(Update, SelectAddress(0x10596D0, 0x1058B30));
		DefineAddress(WhileAiming, SelectAddress(0x105C210, 0x105B670));
		DefineAddress(SelectedUpdate, SelectAddress(0x1054E00, 0x1054300));
		DefineAddress(OnHit, SelectAddress(0x105C4D0, 0x105B930));
	}

	namespace Addresses(cPlaceObjectToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1059300, 0x1058760));
		DefineAddress(OnDeselect, SelectAddress(0x1054E90, 0x1054250));
		DefineAddress(Update, SelectAddress(0x1058740, 0x1057BA0));
		DefineAddress(WhileAiming, SelectAddress(0x105C570, 0x105B9D0));
		DefineAddress(SelectedUpdate, SelectAddress(0x1054E00, 0x1054300));
		DefineAddress(OnHit, SelectAddress(0x105C7E0, 0x105BC40));
	}

	namespace Addresses(cPlanet) 
	{
		DefineAddress(GetTemperatureScore, SelectAddress(0xC6FD80, 0xC70BC0));
		DefineAddress(SetRepresentationMode, SelectAddress(0xC70CD0, 0xC71B70));
		DefineAddress(GetRingEffect, SelectAddress(0xC6FB50, 0xC70990));
	}

	namespace Addresses(cPlayerInventory)
	{
		DefineAddress(GetUnlockableTool, SelectAddress(0xFF4640, 0xFF3BF0));
	}

	namespace Addresses(cRallyCallToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x105CB20, 0x105BF80));
	}

	namespace Addresses(cRepairAOEToolStrategy)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1058B90, 0x1057FF0));
	}

	namespace Addresses(cRepairToolStrategy)
	{
		DefineAddress(Update, SelectAddress(0x1057810, 0x1056C80));
		DefineAddress(OnHit, SelectAddress(0x105BCF0, 0x105B140));
		DefineAddress(WhileFiring, SelectAddress(0x10577D0, 0x1056C40));
		DefineAddress(ProcessCost, SelectAddress(0x1054160, 0x10535F0));
	}

	namespace Addresses(cScanToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054B10, 0x1053F60));
		DefineAddress(OnHit, SelectAddress(0x105B400, 0x105A850));
	}

	namespace Addresses(cSimulatorPlayerUFO)
	{
		DefineAddress(Get, SelectAddress(0xFFC990, 0xFFBD00));
	}

	namespace Addresses(cSimulatorSpaceGame)
	{
		DefineAddress(Get, SelectAddress(0x10036E0, 0x1002A70));
	}

	namespace Addresses(cSpaceToolData)
	{
		DefineAddress(AddAmmo, SelectAddress(0x104D730, 0x104CBE0));
		DefineAddress(ConsumeAmmo, SelectAddress(0x104D760, 0x104CC10));
		DefineAddress(GetStrategy, SelectAddress(0x1050490, 0x1050030));
		DefineAddress(ShowEventLog, SelectAddress(0x1053350, 0x1052800));
	}

	namespace Addresses(cStarRecord)
	{
		DefineAddress(GetPlanetRecord, SelectAddress(0xBB9B40, 0xBBABD0));
		DefineAddress(GetPlanetRecords, SelectAddress(0xBB9870, 0xBBA900));
	}

	namespace Addresses(cToolStrategy)
	{
		DefineAddress(OnSelect, SelectAddress(0x1054340, 0x1053790));

		DefineAddress(Update, SelectAddress(0x1056CC0, 0x1056130));
		DefineAddress(WhileAiming, SelectAddress(0x10544E0, 0x1053930));

		DefineAddress(SelectedUpdate, SelectAddress(0x1054710, 0x1053B60));
		DefineAddress(OnHit, SelectAddress(0x1059F50, 0x10593B0));
		DefineAddress(WhileFiring, SelectAddress(0x1057410, 0x1056880));
		DefineAddress(OnMouseUp, SelectAddress(0x10541D0, 0x1053660));
		DefineAddress(GetAimPoint, SelectAddress(0x1053A70, 0x1052F10));
		DefineAddress(func40h, SelectAddress(0x1054740, 0x1053B90));
	}

	namespace Addresses(cTurretDefenseMissileWeapon)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1057D70, 0x10571E0));
	}

	namespace Addresses(cTurretFlakWeapon)
	{
		DefineAddress(WhileFiring, SelectAddress(0x1057FD0, 0x1057430));
	}

	namespace Addresses(cVehicle)
	{
		DefineAddress(Load, SelectAddress(0xCA6060, 0xCA67C0));
	}

	namespace Addresses(cRelationshipManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D220, 0xB3D3C0));

		DefineAddress(IsAtWar, SelectAddress(0xD014C0, 0xD01F90));
		DefineAddress(IsAtWar2, SelectAddress(0xD01490, 0xD01F60));
		DefineAddress(IsAllied, SelectAddress(0xD01560, 0xD02030));
		DefineAddress(IsAllied2, SelectAddress(0xD01520, 0xD01FF0));
		DefineAddress(DeclareWar, SelectAddress(0xD05840, 0xD065E0));
		DefineAddress(DeclarePeace, SelectAddress(0xD02B90, 0xD03920));
		DefineAddress(DeclareAlliance, SelectAddress(0xD05BC0, 0xD06960));
		DefineAddress(BreakAlliance, SelectAddress(0xD013A0, 0xD01E70));
		DefineAddress(ResetRelationship, SelectAddress(0xD04AD0, 0xD05870));
		DefineAddress(ApplyRelationship, SelectAddress(0xD054E0, 0xD06280));
		DefineAddress(RelationshipExists, SelectAddress(0xD010C0, 0xD01B90));
		DefineAddress(GetRelationshipEventValue, SelectAddress(0xD010F0, 0xD01BC0));
	}

	namespace Addresses(cGameBehaviorManager) 
	{
		DefineAddress(Get, SelectAddress(0xB3D1C0, 0xB3D360));
	}

	namespace Addresses(cGameInputManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D1B0, 0xB3D350));
	}

	namespace Addresses(cGameModeManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D280, 0xB3D420));

		DefineAddress(GetActiveDifficultyTuning, SelectAddress(0xB1DD10, 0xB1DDC0));
		DefineAddress(GetDifficultyTuning, SelectAddress(0xB1D980, 0xB1DA30));

		DefineAddress(SubmitEditorRequest, SelectAddress(0xB1DD70, 0xB1DE20));

		//PLACEHOLDER 0xB1E2A0 transition to another game mode?
	}

	namespace Addresses(cGameNounManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D260, 0xB3D400));
		DefineAddress(CreateInstance, SelectAddress(0xB20A90, 0xB20BF0));
		DefineAddress(DestroyInstance, SelectAddress(0xB22450, 0xB22560));
		DefineAddress(GetData, SelectAddress(0xB21280, 0xB212D0));

		DefineAddress(UpdateModels, SelectAddress(0xB227E0, 0xB228F0));
		DefineAddress(SetAvatar, SelectAddress(0xB1FB90, 0xB1FCA0));

		DefineAddress(GetPlayerCivilization, SelectAddress(0xB25E30, 0xB25F90));
		DefineAddress(CreateHerd, SelectAddress(0xB237C0, 0xB23920));
		DefineAddress(CreateNest, SelectAddress(0xB20C70, 0xB20DD0));
		DefineAddress(EnsurePlayer, SelectAddress(0xB20DE0, 0xB20F40));
	}

	namespace Addresses(cGameViewManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D1A0, 0xB3D340));
	}

	namespace Addresses(cPlanetModel)
	{
		DefineAddress(Get, SelectAddress(0xB3D2B0, 0xB3D450));

		DefineAddress(IsInWater, SelectAddress(0xB7DC90, 0xB7E530));
		DefineAddress(GetNearestCity, SelectAddress(0xB88DF0, 0xB895F0));
		DefineAddress(ToSurface, SelectAddress(0xB80F30, 0xB81780));
		DefineAddress(GetGravity, SelectAddress(0xB7DD40, 0xB7E5E0));
		DefineAddress(GetHeightAt, SelectAddress(0xB7E860, 0xB7F0C0));
		DefineAddress(GetOrientation, SelectAddress(0xB7EB40, 0xB7F3A0));
	}

	namespace Addresses(cSimulatorSystem)
	{
		DefineAddress(Get, SelectAddress(0xB3D190, 0xB3D330));
		DefineAddress(Create, SelectAddress(0xB5DD00, 0xB5E160));
	}

	namespace Addresses(SpacePlayerData)
	{
		DefineAddress(ptr, SelectAddress(0x16E1D0C, 0x16DDA8C));
	}

	namespace Addresses(cStarManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D200, 0xB3D3A0));

		DefineAddress(GetPlanetRecord, SelectAddress(0xBA6540, 0xBA6F10));
		DefineAddress(NextPoliticalID, SelectAddress(0xBA5DA0, 0xBA6780));
		DefineAddress(GetEmpireForStar, SelectAddress(0xBB0230, 0xBB14D0));
		DefineAddress(RecordToPlanet, SelectAddress(0xBB4960, 0xBB5B50));
		DefineAddress(FindClosestStar, SelectAddress(0xBAFD80, 0xBB1020));
		DefineAddress(FindStars, SelectAddress(0xBAFF70, 0xBB1210));

		DefineAddress(CalculatePlanetScores, SelectAddress(0xBA5C10, 0xBA65F0));
		DefineAddress(StarGenerationMessageHandler, SelectAddress(0xBB4D10, 0xBB5F00));
		DefineAddress(GetStarGridPosition, SelectAddress(0xBA6880, 0xBA7250));
		DefineAddress(GenerateEllipticalOrbit, SelectAddress(0xBA81B0, 0xBA8D90));
		DefineAddress(GenerateSolSystem, SelectAddress(0xBB1A00, 0xBB2BF0));
		DefineAddress(RequirePlanetsForStar, SelectAddress(0xBB3AA0, 0xBB4C90));
		DefineAddress(GeneratePlanetsForStar, SelectAddress(0xBB30B0, 0xBB42A0));
	}

	namespace Addresses(cSpaceTradeRouteManager)
	{
		DefineAddress(HasTradeRoute, SelectAddress(0x1038C10, 0x1037D40));
	}

	namespace Addresses(cTerraformingManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D390, 0xB3D530));

		DefineAddress(GetTScore, SelectAddress(0xBBB750, 0xBBC7E0));
		DefineAddress(CalculateTScore, SelectAddress(0xFC2760, 0xFC2040));
	}

	namespace Addresses(cToolManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D2F0, 0xB3D490));

		DefineAddress(LoadTool, SelectAddress(0x104EEA0, 0x104E350));
		DefineAddress(GetStrategy, SelectAddress(0x10503B0, 0x104F860));

		DefineAddress(ActivateTool, SelectAddress(0x1050710, 0x104FBC0));
		DefineAddress(DeactivateTool, SelectAddress(0x1050770, 0x104FC20));
		DefineAddress(OnMouseUp, SelectAddress(0x10505F0, 0x104FAA0));
	}


	namespace Addresses(ClassSerializer)
	{
		DefineAddress(Read, SelectAddress(0x693F20, 0x693DE0));
		DefineAddress(Write, SelectAddress(0x692B10, 0x6928C0));
	}

	namespace Addresses(XmlSerializer)
	{
		DefineAddress(AttributesToXml, SelectAddress(0x695D40, 0x695B20));
	}

	namespace Addresses(cGameData)
	{
		DefineAddress(Write, SelectAddress(0xB18430, 0xB184D0));
		DefineAddress(Read, SelectAddress(0xB184A0, 0xB18540));
		DefineAddress(func18h, SelectAddress(0xB18270, 0xB18320));
		DefineAddress(ISimulatorSerializable_func18h, SelectAddress(0xB18270, 0xB18320));
		DefineAddress(WriteToXML, SelectAddress(0xB18390, 0xB18440));

		DefineAddress(SetDefinitionID, SelectAddress(0xB18290, 0xB18340));
		DefineAddress(SetGameDataOwner, SelectAddress(0xB183E0, 0xB18490));
		DefineAddress(IsDestroyed, SelectAddress(0xB18260, 0xB18310));

		DefineAddress(SetGameDataOwner2, SelectAddress(0xB183E0, 0xB18490));

		DefineAddress(func3Ch, SelectAddress(0xB18280, 0xB18330));
		DefineAddress(cGameData_func3Ch, SelectAddress(0xB18280, 0xB18330));

		DefineAddress(RemoveOwner, SelectAddress(0xAFF820, 0xAFFD20));

		DefineAddress(WriteAsText, SelectAddress(0xB182B0, 0xB18360));
	}

	namespace Addresses(cCommManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D400, 0xB3D5A0));

		DefineAddress(CreateCivCommEvent, SelectAddress(0xAEABB0, 0xAEB1C0));
		DefineAddress(CreateSpaceCommEvent, SelectAddress(0xAEAAD0, 0xAEB0E0));
		DefineAddress(ShowCommEvent, SelectAddress(0xAEB800, 0xAEBE10));
		DefineAddress(HandleCivCommAction, SelectAddress(0xAEB200, 0xAEB810));
		DefineAddress(HandleSpaceCommAction, SelectAddress(0xAEB120, 0xAEB730));
		DefineAddress(IsCommScreenActive, SelectAddress(0xAE8EA0, 0xAE9310));
	};

	namespace Addresses(cUIEventLog)
	{
		DefineAddress(Get, SelectAddress(0xB3D340, 0xB3D4E0));
		DefineAddress(ShowEvent, SelectAddress(0xDD7810, 0xDD85E0));
		DefineAddress(SetDescription, SelectAddress(0xDD6120, 0xDD6D80));
		DefineAddress(HideEvent, SelectAddress(0xDD6040, 0xDD6CA0));
		DefineAddress(SetVisible, SelectAddress(0xDD7F70, 0xDD8D40));
	}

	namespace Addresses(cSimPlanetHighLOD)
	{
		DefineAddress(DestroyCity, SelectAddress(0xFFB440, 0xFFA7B0));
	}

	namespace Addresses(cMissionManager)
	{
		DefineAddress(Get, SelectAddress(0xFEC0C0, 0xFEB880));
		DefineAddress(CreateMission, SelectAddress(0xFECC50, 0xFEC420));
		DefineAddress(ChooseMission, SelectAddress(0xFEF450, 0xFEEBC0));
		DefineAddress(HasMissionsAvailable, SelectAddress(0xFEEAE0, 0xFEE260));
		DefineAddress(GetMissionByID, SelectAddress(0xFEEB90, 0xFEE310));
		DefineAddress(GetMissionTrackColor, SelectAddress(0xFEC510, 0xFEBCE0));
		DefineAddress(ThereIsEventInPlanet, SelectAddress(0xFEE8A0, 0xFEE020));
	}

	namespace Addresses(cMission)
	{
		DefineAddress(SetState, SelectAddress(0xC47C40, 0xC47E20));
	}

	namespace Addresses(cGameTimeManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D2E0, 0xB3D480));
		DefineAddress(Pause, SelectAddress(0xB32140, 0x00b32330));
		DefineAddress(Resume, SelectAddress(0xB32170, 0x00b32360));
		DefineAddress(Toggle, SelectAddress(0xB32170, 0x00b32390));
		DefineAddress(GetPauseCount, SelectAddress(0xB31EE0, 0x00b321e0));
		DefineAddress(ConvertDeltaTime, SelectAddress(0xB31AA0, 0xb31da0));
		DefineAddress(SetSpeed, SelectAddress(0xB32370, 0x00b32560));
	}

	namespace Addresses(cTimeOfDay)
	{
		DefineAddress(Get, SelectAddress(0xBC2550, 0xBC3220));
		DefineAddress(SetSpeedMultiplier, SelectAddress(0xBC1D60, 0xBC2A30));
		DefineAddress(SetDayDuration, SelectAddress(0xBC1CD0, 0xBC29A0));
		DefineAddress(SetTimeOfDay, SelectAddress(0xBC23A0, 0xBC3070));
	}

	namespace Addresses(cAnimalSpeciesManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D3B0, 0xB3D550));
		DefineAddress(CreateAnimalItem, SelectAddress(0xAC0E90, 0xAC0C00));
	}

	namespace Addresses(cPlantSpeciesManager)
	{
		DefineAddress(Get, SelectAddress(0xB3D380, 0xB3D520));
		DefineAddress(CreatePlantItem, SelectAddress(0xB8FEF0, 0xB90560));
	}

	namespace Addresses(cSpaceInventoryItem)
	{
		DefineAddress(CreateMultiDeliveryObject, SelectAddress(0xC86C00, 0xC86C00));
		DefineAddress(SetPropList, SelectAddress(0xC86B20, 0xC87980));
		DefineAddress(CreateTradingObject, SelectAddress(0x103B470, 0x103A490));
	}

	namespace Addresses(cTribeArchetype)
	{
		DefineAddress(GetTribeArchetype, SelectAddress(0xC8E060, 0xC8EC00));
	}

	namespace Addresses(cSolarSystem)
	{
		DefineAddress(Load, SelectAddress(0xC85AC0, 0xC868F0));
		DefineAddress(LoadBinaryStar, SelectAddress(0xC848A0, 0xC856D0));
		DefineAddress(LoadAsteroids, SelectAddress(0xC84D90, 0xC85BC0));
		DefineAddress(GenerateGraphics, SelectAddress(0xC85FD0, 0xC86E00));
		DefineAddress(CreateStarEffect, SelectAddress(0xC82FF0, 0xC83E80));
		DefineAddress(GenerateCelestialBodiesEffects, SelectAddress(0xC83920, 0xC847B0));
	}

	namespace Addresses(cStar)
	{
		DefineAddress(GetSolarSystem, SelectAddress(0xC8AA90, 0xC8B900));
		DefineAddress(IsBinaryStar, SelectAddress(0xC8AB00, 0xC8B970));
		DefineAddress(IsStarOrBinaryStar, SelectAddress(0xC8AB20, 0xC8B990));
	}

	namespace Addresses(cScenarioEditHistory)
	{
		DefineAddress(ptr, SelectAddress(0x160A850, 0x16065D8));
	}

	namespace Addresses(cScenarioData)
	{
		DefineAddress(Initialize, SelectAddress(0xF44AC0, 0xF44690));
		DefineAddress(StartHistoryEntry, SelectAddress(0xF45C40, 0xF45810));
		DefineAddress(CommitHistoryEntry, SelectAddress(0xF45D50, 0xF45920));
		DefineAddress(GetClass, SelectAddress(0xF3EBA0, 0xF3E740));
		DefineAddress(GetCurrentClassAct, SelectAddress(0xF3FC50, 0xF3F7F0));
		DefineAddress(GetEditModeActIndex, SelectAddress(0xEFC740, 0xEFC410));
		DefineAddress(CreateObjectInstance, SelectAddress(0xEEE090, 0xEEDD40));
		DefineAddress(CreatePowerupObjectInstance, SelectAddress(0xF216A0, 0xF212C0));
		DefineAddress(GetObjectForMarker, SelectAddress(0xF3D810, 0xF3D620));
		DefineAddress(GetMarkerForObject, SelectAddress(0xF3D810, 0xF3D620));
	}

	namespace Addresses(cScenarioResource)
	{
		DefineAddress(Read, SelectAddress(0xF2FDD0, 0xF2FC40));
		DefineAddress(Write, SelectAddress(0xF261F0, 0xF25E00));
	}

	namespace Addresses(cScenarioTerraformMode)
	{
		DefineAddress(StartHistoryEntry, SelectAddress(0xF33AD0, 0xF33A90));
		DefineAddress(CommitHistoryEntry, SelectAddress(0xF45D50, 0xF34400));
		DefineAddress(SetWaterColor, SelectAddress(0xF32140, 0xF31FA0));
		DefineAddress(SetAtmosphereColor, SelectAddress(0xF32190, 0xF31FF0));
		DefineAddress(SetBeachColor, SelectAddress(0xF321E0, 0xF32040));
		DefineAddress(SetCliffColor, SelectAddress(0xF32230, 0xF32090));
	}

	namespace Addresses(cHerd)
	{
		DefineAddress(Create, SelectAddress(0xB237C0, 0xB23920));
	}

	namespace Addresses(cScenarioClass)
	{
		DefineAddress(GetObjectType, SelectAddress(0xEED090, 0xEECD40));
		DefineAddress(IsConsumible, SelectAddress(0xF27A90, 0xF27730));
	}

	namespace Addresses(cScenarioPowerup)
	{
		DefineAddress(ReactToPowerup, SelectAddress(0xF23FD0, 0xF23BF0));
		//TODO DefineAddress(ApplyBoost, SelectAddress(0xF20670, 0xF20290));
		DefineAddress(ActivateMedKit, SelectAddress(0xF229C0, 0xF225E0));
		DefineAddress(ActivateEnergyKit, SelectAddress(0xF22BE0, 0xF22800));
		DefineAddress(ActivateSpeedBoost, SelectAddress(0xF232B0, 0xF22ED0));
		DefineAddress(ActivateDamageBoost, SelectAddress(0xF23000, 0xF22C20));
		DefineAddress(ActivateArmorBoost, SelectAddress(0xF22D50, 0xF22970));
		DefineAddress(ActivateMine, SelectAddress(0xF20BB0, 0xF207D0));
		DefineAddress(ActivateJumpPad, SelectAddress(0xF23890, 0xF234B0));
		DefineAddress(ActivateTeleporter, SelectAddress(0xF23660, 0xF23280));
		DefineAddress(ActivateGate, SelectAddress(0xF23E90, 0xF23AB0));
		DefineAddress(ActivateGrenade, SelectAddress(0xF20C40, 0xF20860));
	}

	namespace Addresses(cScenarioSimulator)
	{
		DefineAddress(Get, SelectAddress(0xC02AE0, 0xC033C0));
	}

	namespace Addresses(cScenarioPlayMode)
	{
		DefineAddress(Initialize, SelectAddress(0xF1F450, 0xF1F060));
		DefineAddress(SetCurrentAct, SelectAddress(0xF1F260, 0xF1EE70));
		DefineAddress(JumpToAct, SelectAddress(0xF1F7B0, 0xF1F3C0));
		DefineAddress(SetState, SelectAddress(0xF1ADB0, 0xF1A9C0));
		DefineAddress(UpdateGoals, SelectAddress(0xF1C780, 0xF1C390));
		DefineAddress(Update, SelectAddress(0xF1FD50, 0xF1F960));
		DefineAddress(CompleteAct, SelectAddress(0xF1F680, 0xF1F290));
		DefineAddress(CheckGoalProgress, SelectAddress(0xF1F8D0, 0xF1F4E0));
		DefineAddress(RemoveInvisibleClasses, SelectAddress(0xF1AFD0, 0xF1ABE0));
		DefineAddress(ReadScenarioTuning, SelectAddress(0xF1E2F0, 0xF1DF00));
	}

	namespace Addresses(cPlanetRecord)
	{
		DefineAddress(Create, SelectAddress(0xBA5920, 0xBA6300));
		DefineAddress(GetPerihelion, SelectAddress(0xC70190, 0xC70FC0));
		DefineAddress(FillPlanetDataForTechLevel, SelectAddress(0xB96820, 0xB97090));
		DefineAddress(CalculateSpiceProduction, SelectAddress(0xC6F920, 0xC70760));
		DefineAddress(CalculateDeltaSpiceProduction, SelectAddress(0xC71200, 0xC720A0));
		DefineAddress(GetTerrainScriptSource, SelectAddress(0xB8D690, 0xB8DEB0));
		DefineAddress(HasControlledCity, SelectAddress(0xC6F4B0, 0xC702F0));
		DefineAddress(GetTypeIconKey, SelectAddress(0xE2EBE0, 0xE2EB70));
	}

	namespace Addresses(cCivData) {
		DefineAddress(AddCityData, SelectAddress(0xFF35E0, 0xFF2B20));
	}

	namespace Addresses(cSpaceGfx)
	{
		DefineAddress(Get, SelectAddress(0xB3D3D0, 0xB3D570));
		DefineAddress(InitializeInternal, SelectAddress(0x10367E0, 0x1035910));
		DefineAddress(DisposeInternal, SelectAddress(0x1038190, 0x10372C0));
	}

	namespace Addresses(cBadgeManager)
	{
		DefineAddress(AddToBadgeProgress, SelectAddress(0xFE5BF0, 0xFE52C0));
	}

	namespace Addresses(cCelestialBody)
	{
		DefineAddress(Write, SelectAddress(0xBD56B0, 0xBD6380));
		DefineAddress(Read, SelectAddress(0xBD5720, 0xBD63F0));
		DefineAddress(WriteToXML, SelectAddress(0xBD5960, 0xBD6630));
		DefineAddress(RemoveOwner, SelectAddress(0xBD5640, 0xBD6310));
	}

	namespace Addresses(cCreatureGameData)
	{
		DefineAddress(Get, SelectAddress(0xD2D640, 0xD2E340));
		DefineAddress(GetEvoPointsToNextBrainLevel, SelectAddress(0xD2D680, 0xD2E380));
		DefineAddress(GetAbilityMode, SelectAddress(0xD2D790, 0xD2E490));
		DefineAddress(SetAbilityMode, SelectAddress(0xD2D7A0, 0xD2E4A0));
		DefineAddress(AfterGlideFinish, SelectAddress(0xD2D880, 0xD2E580));
		DefineAddress(CalculateAvatarNormalizingScale, SelectAddress(0xD2DA20, 0xD2E720));
		DefineAddress(GetAvatarNormalizingScale, SelectAddress(0xD2DB00, 0xD2E800));
		DefineAddress(GetEvolutionPoints, SelectAddress(0xD2D650, 0xD2E350));
		DefineAddress(SetEvolutionPoints, SelectAddress(0xD2D780, 0xD2E480));
		DefineAddress(AddEvolutionPoints, SelectAddress(0xD2DBA0, 0xD2E8A0));
	}

	namespace Addresses(cSpaceNames)
	{
		DefineAddress(Get, SelectAddress(0x4010A0, 0x4010A0));
		DefineAddress(GenerateRandomName, SelectAddress(0x5ECD40, 0x5ED000));
	}

#ifndef SDK_TO_GHIDRA
	namespace Addresses(cObjectPool)
	{
		DefineAddress(Initialize, SelectAddress(0xB71A10, 0xB72190));
		DefineAddress(_dtor, SelectAddress(0xB71A70, 0xB721F0));
		DefineAddress(Get, SelectAddress(0x0B71BA0, 0xB72320));
		DefineAddress(Clear, SelectAddress(0xB71AA0, 0xB72220));
		DefineAddress(CreateObject, SelectAddress(0xB71AF0, 0xB72270));
		DefineAddress(GetIfNotDeleted, SelectAddress(0xB71B60, 0xB722E0));
		DefineAddress(DeleteObject, SelectAddress(0xB71BF0, 0xB72370));
		DefineAddress(Iterate, SelectAddress(0xB71BC0, 0xB72340));
	}
#endif
	namespace Addresses(cObjectPool_)
	{
		DefineAddress(Initialize, SelectAddress(0xB71A10, 0xB72190));
		DefineAddress(_dtor, SelectAddress(0xB71A70, 0xB721F0));
		DefineAddress(Get, SelectAddress(0x0B71BA0, 0xB72320));
		DefineAddress(Clear, SelectAddress(0xB71AA0, 0xB72220));
		DefineAddress(CreateObject, SelectAddress(0xB71AF0, 0xB72270));
		DefineAddress(GetIfNotDeleted, SelectAddress(0xB71B60, 0xB722E0));
		DefineAddress(DeleteObject, SelectAddress(0xB71BF0, 0xB72370));
		DefineAddress(Iterate, SelectAddress(0xB71BC0, 0xB72340));
	}

	namespace Addresses(cSimulatorUniverse)
	{
#ifndef SDK_TO_GHIDRA
		DefineAddress(_ptr, SelectAddress(0x16E0A18, 0x16DC798));
#endif
	}

	namespace Cell
	{
		namespace Addresses(cCellGame)
		{
			DefineAddress(_ptr, SelectAddress(0x16B7E84, 0x16B3C04));
			DefineAddress(Initialize, SelectAddress(0xE81130, 0xE80BA0));
			DefineAddress(CreateCellObject, SelectAddress(0xE74F60, 0xE74A20));
			DefineAddress(MovePlayerToMousePosition, SelectAddress(0xE5BD90, 0xE5B790));
			DefineAddress(GetScaleDifferenceWithPlayer, SelectAddress(0xE57940, 0xE57340));
			DefineAddress(ShouldNotAttack, SelectAddress(0xE57A60, 0xE57460));
		}

		namespace Addresses(cCellGFX)
		{
			DefineAddress(_ptr, SelectAddress(0x16B7E88, 0x16B3C08));
			DefineAddress(PreloadResources, SelectAddress(0xE66C90, 0xE666F0));
			DefineAddress(PreloadCellResource, SelectAddress(0xE66950, 0xE663B0));
			DefineAddress(PreloadPopulateResource, SelectAddress(0xE66B60, 0xE665C0));
			DefineAddress(PreloadLootTableResource, SelectAddress(0xE50290, 0xE4FC00));
			DefineAddress(PreloadCreature, SelectAddress(0xE64F10, 0xE64980));
			DefineAddress(AddPreloadedEffect, SelectAddress(0xE66820, 0xE66280));
			DefineAddress(AddPreloadedTexture, SelectAddress(0xE65F10, 0xE65970));
			DefineAddress(AddPreloadedModel, SelectAddress(0xE659B0, 0xE65410));
			DefineAddress(AddPreloadedModel2, SelectAddress(0xE65940, 0xE653A0));
			DefineAddress(Initialize, SelectAddress(0xE5E130, 0xE5DBA0));
			DefineAddress(StartDisplay, SelectAddress(0xE55780, 0xE55120));
			DefineAddress(CreateEffect, SelectAddress(0x628470, 0x628480));
			DefineAddress(LoadEffectMap, SelectAddress(0xE63AF0, 0xE63560));
			DefineAddress(InstanceEffectOnCell, SelectAddress(0xE66DE0, 0xE66840));
#ifndef SDK_TO_GHIDRA
			DefineAddress(sVisibleBackgroundBBox_ptr, SelectAddress(0x16B7F08, 0x16B3C88));
			DefineAddress(sFrustumCull_ptr, SelectAddress(0x16B7F38, 0x16B3CB8));
#else
			DefineAddress(sVisibleBackgroundBBox, SelectAddress(0x16B7F08, 0x16B3C88));
			DefineAddress(sFrustumCull, SelectAddress(0x16B7F38, 0x16B3CB8));
#endif
		}

		namespace Addresses(cCellUI)
		{
			DefineAddress(_ptr, SelectAddress(0x16B7E8C, 0x16B3C0C));
			DefineAddress(Load, SelectAddress(0xE548B0, 0xE54270));
			DefineAddress(ShowHealthRollover, SelectAddress(0xE628D0, 0xE62340));
		}

		namespace Addresses(cCellSerializableData)
		{
			DefineAddress(_ptr, SelectAddress(0x16B8060, 0x16B3DE0));
		}

		namespace Addresses(cCellDataReference_)
		{
			DefineAddress(Create, SelectAddress(0xE829B0, 0xE82420));
		}
	}

	namespace Addresses(Cell)
	{
		DefineAddress(GetData, SelectAddress(0xE4D2A0, 0xE4CBF0));
		DefineAddress(GetGlobalsData, SelectAddress(0xE4D4A0, 0xE4CE20));
		DefineAddress(sSerializer__lootTable, SelectAddress(0x16B52A0, 0x16B1020));
		DefineAddress(sSerializer__cell, SelectAddress(0x16B1730, 0x16AD4B0));
		DefineAddress(sSerializer__populate, SelectAddress(0x16B4D00, 0x16B0A80));
		DefineAddress(sSerializer__world, SelectAddress(0x16B1650, 0x16AD3D0));
		DefineAddress(sSerializer__look_table, SelectAddress(0x16B1624, 0x16AD3A4));
		DefineAddress(sSerializer__random_creature, SelectAddress(0x16B16A8, 0x16AD428));
		DefineAddress(sSerializer__look_algorithm, SelectAddress(0x16B52F8, 0x16B1078));
		DefineAddress(sSerializer__backgroundMap, SelectAddress(0x16B52CC, 0x16B104C));
		DefineAddress(sSerializer__effectMap, SelectAddress(0x16B5000, 0x16B0D80));
		DefineAddress(sSerializer__powers, SelectAddress(0x16B4E64, 0x16B0BE4));
		DefineAddress(sSerializer__globals, SelectAddress(0x16B4DDC, 0x16B0B5C));
		DefineAddress(sSerializer__structure, SelectAddress(0x16B16D4, 0x16AD454));

		DefineAddress(GetCurrentAdvectInfo, SelectAddress(0xE594F0, 0xE58EF0));
		DefineAddress(GetNextAdvectID, SelectAddress(0xE59430, 0xE58E30));
		DefineAddress(CreateCellObject, SelectAddress(0xE74F60, 0xE74A20));
		DefineAddress(MovePlayerToMousePosition, SelectAddress(0xE5BD90, 0xE5B790));
		DefineAddress(GetScaleDifferenceWithPlayer, SelectAddress(0xE57940, 0xE57340));
		DefineAddress(ShouldNotAttack, SelectAddress(0xE57A60, 0xE57460));
		DefineAddress(GetDamageAmount, SelectAddress(0xE58F80, 0xE58980));
		DefineAddress(FindCellsInRadius, SelectAddress(0xE876D0, 0xE87210));
		DefineAddress(PlayAnimation, SelectAddress(0xE6D780, 0xE6D200));
		DefineAddress(GetModelKeyForCellResource, SelectAddress(0xE65BE0, 0xE65640));
	}

#ifdef SDK_TO_GHIDRA
	namespace Addresses(Cell)
	{
		DefineAddress(sCellGame, SelectAddress(0x16B7E84, 0x16B3C04));
		DefineAddress(sCellGFX, SelectAddress(0x16B7E88, 0x16B3C08));
		DefineAddress(sCellUI, SelectAddress(0x16B7E8C, 0x16B3C0C));
		DefineAddress(sCellSerializableData, SelectAddress(0x16B8060, 0x16B3DE0));
	}
#endif

	namespace Addresses(cSpaceTrading)
	{
		DefineAddress(Get, SelectAddress(0xB3D330, 0xB3D4D0));
		DefineAddress(ClearNPCStores, SelectAddress(0x103E9D0, 0x103DCD0));
		DefineAddress(IsRare, SelectAddress(0x103B3B0, 0x103A3D0));
		DefineAddress(ObtainTradingObject, SelectAddress(0x1040890, 0x103FC20));
		DefineAddress(AssignPlanetSpice, SelectAddress(0x103D750, 0x103CA50));
		DefineAddress(GetRareHasBeenFound, SelectAddress(0x103BC30, 0x103AC50));
		DefineAddress(SetRareAsFound, SelectAddress(0x1040820, 0x103FBB0));
		DefineAddress(GenerateNPCStore, SelectAddress(0x103F560, 0x103E8F0));
	}

	namespace Addresses(cGamePersistenceManager) 
	{
		DefineAddress(Get, SelectAddress(0xB3D2A0, 0xB3D440));
	}
	
	namespace Addresses(cIdentityColorable)
	{
		DefineAddress(AssignNames, SelectAddress(0xB6F040, 0xB6F480));
	}

	namespace Addresses(cSpeciesProfile)
	{
		DefineAddress(GetSpeciesName, SelectAddress(0x4DA1C0, 0x4DA390));
	}

 	namespace Addresses(cCultureSet) 
	{
		DefineAddress(PickCreation, SelectAddress(0xBF8DF0, 0xBF9840));
	}

	namespace Addresses(cCommunityLayout)
	{
		DefineAddress(InitializeSlots, SelectAddress(0xAFE620, 0xAFEB80));
		DefineAddress(SnapSlotsToPlanet, SelectAddress(0xAFA690, 0xAFAE40));
		DefineAddress(SetParameters, SelectAddress(0xAF95D0, 0xAF9C70));
	}

	namespace Addresses(cLayoutSlot)
	{
		DefineAddress(SetObject, SelectAddress(0xAF9890, 0xAF9FB0));
		DefineAddress(RemoveObject, SelectAddress(0xAF9900, 0xAFA020));
	}

	namespace Addresses(cArtilleryProjectile)
	{
		DefineAddress(LaunchProjectile, SelectAddress(0xCB68C0, 0xCB71C0));
	}
	namespace Addresses(cCulturalProjectile)
	{
		DefineAddress(LaunchProjectile, SelectAddress(0xCBD0A0, 0xCBDB90));
	}
	namespace Addresses(cFlakProjectile)
	{
		DefineAddress(LaunchProjectile, SelectAddress(0xCB7400, 0xCB7CF0));
	}
	namespace Addresses(cResourceProjectile)
	{
		DefineAddress(LaunchProjectile, SelectAddress(0xCBDCD0, 0xCBE7C0));
	}
	namespace Addresses(cSpaceDefenseMissile)
	{
		DefineAddress(LaunchProjectile, SelectAddress(0xCB7FD0, 0xCB88B0));
	}

	namespace Addresses(cCollectableItems)
	{
		DefineAddress(LoadConfig, SelectAddress(0x599100, 0x599440));
		DefineAddress(AddUnlockableItem, SelectAddress(0x598A70, 0x598DB0));
		DefineAddress(AddUnlockableItemFromProp, SelectAddress(0x598B50, 0x598E90));
		DefineAddress(sub_597BC0, SelectAddress(0x597BC0, 0x597F00));
		DefineAddress(sub_597390, SelectAddress(0x597390, 0x5976D0));
	}

	namespace Addresses(CreatureGamePartUnlocking)
	{
		DefineAddress(sub_D3B460, SelectAddress(0xD3B460, 0xD3BF50));
	}

	namespace Addresses(cPlanetaryArtifact)
	{
		DefineAddress(SetLocomotion, SelectAddress(0xC687D0, 0xC69230));
		DefineAddress(LoadFromItem, SelectAddress(0xC73F90, 0xC74ED0));
	}

	namespace Addresses(cSpatialObject) {
		DefineAddress(SetModelKey, SelectAddress(0xC87B30, 0xC889A0));
	}
}

#ifdef SDK_TO_GHIDRA
namespace Addresses(Simulator)
{
	DefineAddress(sSpacePlayerData, SelectAddress(0x16E1D0C, 0x16DDA8C));
	DefineAddress(sScenarioEditHistory, SelectAddress(0x160A850, 0x16065D8));
	DefineAddress(TimeAtStartOfFrame, SelectAddress(0xB63580, 0xB63980));
	DefineAddress(sCreatureGameData, SelectAddress(0x16A25F0, 0x169E370));
}
#endif

#endif
