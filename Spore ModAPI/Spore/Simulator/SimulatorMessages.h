/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Spore\Object.h>
#include <Spore\ResourceKey.h>
#include <Spore\App\StandardMessage.h>
#include <Spore\Simulator\cMission.h>

namespace Simulator
{
	enum SimulatorMessages
	{
		/// Simulator::EnterEditorMessage; Enters the correct editor modifying the specified creation.
		kMsgEnterEditor = 0x53850BAE,

		kMsgSwitchGameMode = 0x0212D3E7,

		/// Saves the game, pausing the game and showing a dialog on success. Use with message data `1` (as in, an integer).
		kMsgSaveGame = 0x1CD20F0,

		/// Simulator::GameNounStatusChangedMessage
		kMsgGameNounStatusChanged = 0x1A0219E,

		/// Simulator::MissionUpdateMessage; every update of a mission, only if the mission is ongoing
		kMsgMissionUpdate = 0x38CF2FD,

		/// Simulator::CombatantKilledMessage; called when a combatant is killed 
		kMsgCombatantKilled = 0x1622184,

		/// kills persistant swarm effects. Used at the end of certain stages
		kMsgKillPersistentEffects = 0x0667af52,

		//////////////////
		// Cell Stage
		//////////////////
		
		// Sent when the cell stage intro cinematic effect ends
		kMsgCinematicGGE2CLGEnds = 0x04065b23,

		/// Sent when cell stage has begun
		kMsgCellStageStart = 0x047c1d19,


		//////////////////
		// Creature Stage
		//////////////////

		/// Hatches the avatar creature's egg in creature stage
		kMsgHatchAvatarEggs = 0x06566531,

		/// Upgrades the player's nest to the current brain level(?) in creature stage. May be cutscene only.
		kMsgUpgradeNest = 0x06555abc,

		/// Respawns the avatar creature at their nest in creature stage
		kMsgRestartAtNest = 0x04f60b92,

		/// Loads the avatar into the creature editor
		kEnterCreatureEditor = 0x04d9686f,

		/// TODO, uses data
		//kCinematicCRG2TRGPreload = 0x04b719d4,

		/// Transitions creature stage to tribal stage
		kMsgCinematicTransitionToTribe = 0x0477f66c,

		///////////////
		// Tribe Stage
		///////////////

		/// Upgrades the player tribe's main hut (Cutscene only)
		kMsgTribeUpgradeHut = 0x0575116e,

		/// Upgrades the player tribe's campfire and layout decal (Cutscene only)
		kMsgTribeUpgradeCampfire = 0x0575116f,

		/// Upgrades the player tribe's totem base and food mat (Cutscene only)
		kMsgTribeUpgradeFoodMat = 0x05751170,
		
		/// Restarts the tribal stage (as though tribal hut has been destroyed)
		kMsgTribeRestart = 0x0420e32a,

		/// Sent to notify the game that a new tribal totem needs to be added
		kMsgNotifyTotemNeeded = 0x05cd5482,
		
		/// Sent to notify the game that the tribal upgrade or totem placement has finished so that game can save
		kMsgNotifyUpgradeDone = 0x05cd5482,
		
		/// Moves the tribal camera  to point towards the center of your tribe
		kMsgTribeMoveCameraToTribe = 0x056cf231,

		/// TRG2CVG - Shows the city hall
		kMsgCinematicTRG2CVGShowCityHall = 0x069479a8,

		/// TRG2CVG - Hides the city hall
		kMsgCinematicTRG2CVGHideCityHall = 0x0694797d,
		
		/////////////
		// Civ Stage
		/////////////

		/// Sent when the cutscene for a new city appearing plays in civ stage
		kMsgCinematicNewCityAppears = 0x05668f43,

		/// Sent when the captured city's buildings restart their runtime effects in civ stage
		kMsgCinematicCityChangeStartBuildingsEffects = 0x05f4d02a,

		/// Sent when the captured city's buildings swap their models in civ stage
		kMsgCinematicCityChangeSwapBuildings = 0x05dfb77f,

		/// Sent when the captured city's wall color changes in civ stage
		kMsgCinematicCityChangeChangeWallColor = 0x05dfb782,

		/// Sent when the captured city's civilization ownership changes in civ stage
		kMsgCinematicCityChangeChangeCivilization = 0x05dbc31e,

		/// Sent when a tier 3 superweapon cutscene begins in civ stage (?)
		kMsgCivTriggerSuperweapon = 0x06524f8f,
		
		/// Sent when the UFO appears at the very end of civ stage
		kMsgShowUFOForTransition = 0x0590cd26,

		///////////////
		// Space Stage
		///////////////

		/// Sent when the player gets new tools in a space stage cutscene (TODO: Does this also get called outside of cutscenes?)
		kMsgCinematicSpaceGetTools = 0x06526395,

		/// Sent from the cutscene where the player first picks up spice in space stage
		kMsgCinematicSpaceFirstSpicePickup = 0x06834927,

		/// Plays the "UFO Effect" of swirly lights appearing around the player's ship in a space stage cutscene
		kMsgCinematicSpaceUFOEffect = 0x0665e639,

		/// Sent when a new badge appears on the screen in space stage
		kMsgCinematicScreenBadgeEffect = 0x0665e1ab,

		/// Sent when the atmosphere dome goes down on a space stage colony (TODO: Does this also get called outside of cutscenes?)
		kMsgCinematicSpaceColonyAtmosphereDomeDown = 0x065e622c,

		/// Simulator::PlayerEmpireAlliedMessage; called when the player empire makes a new alliance
		kMsgPlayerEmpireAllied = 0x4445D43,

		/// Simulator::PlayerEmpireLostAllianceMessage; called when the player empire loses an alliance
		kMsgPlayerEmpireLostAlliance = 0x4445D44,

		/// Called when a spaceship uses an sculpting or coloring tool and it hits the planet. No parameters.
		kMsgSculptOrColorToolHit = 0xF46092DB,

		/// Simulator::ToolOnHitMessage; called when a space tool hits a target
		kMsgToolOnHit = 0x56690BB,

		/// Message emitted by the galaxy generation effect to create stars of StarType::StarG (yellow) type.
		kMsgGalaxyGenerateStarG = 0x35B2B15,
		/// Message emitted by the galaxy generation effect to create stars of StarType::StarO (blue) type.
		kMsgGalaxyGenerateStarO = 0x36998AE,
		/// Message emitted by the galaxy generation effect to create stars of StarType::StarM (red) type.
		kMsgGalaxyGenerateStarM = 0x3757942,
		/// Message emitted by the galaxy generation effect to create black holes (StarType::BlackHole).
		kMsgGalaxyGenerateBlackHole = 0x36AD255,
		/// Message emitted by the galaxy generation effect to create proto-planteray disks (StarType::ProtoPlanetary).
		kMsgGalaxyGenerateProtoPlanetary = 0x36AD784,
		/// Message emitted by the galaxy generation effect to create galactic cores (StarType::GalacticCore).
		kMsgGalaxyGenerateGalacticCore = 0x3D1DEBA,
		/// Message emitted by the galaxy generation effect to create binary O-O (blue-blue) star systems (StarType::BinaryOO).
		kMsgGalaxyGenerateBinaryOO = 0x3DFF99F,
		/// Message emitted by the galaxy generation effect to create binary O-M (blue-red) star systems (StarType::BinaryOM).
		kMsgGalaxyGenerateBinaryOM = 0x3DFF9A9,
		/// Message emitted by the galaxy generation effect to create binary O-G (blue-yellow) star systems (StarType::BinaryOG).
		kMsgGalaxyGenerateBinaryOG = 0x3DFF9B1,
		/// Message emitted by the galaxy generation effect to create binary G-G (yellow-yellow) star systems (StarType::BinaryGG).
		kMsgGalaxyGenerateBinaryGG = 0x3DFF9BA,
		/// Message emitted by the galaxy generation effect to create binary G-M (yellow-red) star systems (StarType::BinaryGM).
		kMsgGalaxyGenerateBinaryGM = 0x3DFF9C1,
		/// Message emitted by the galaxy generation effect to create binary M-M (red-red) star systems (StarType::BinaryMM).
		kMsgGalaxyGenerateBinaryMM = 0x3DFF9C6,

		/// Simulator::SpaceRareFoundMessage ; sent when a rare item is found (even if it had already been found before) in Space Stage. 
		kMsgSpaceRareFound = 0xF46092D4,
		/// Sent when a rare item is discovered (i.e. it had not been found before) in Space Stage. The parameter is a uint32_t* to the rare instance ID.
		kMsgSpaceRareDiscovered = 0x6779F04,

		/// Sent when the ownership of some star changes. No parameters.
		kMsgStarOwnershipChanged = 0x55BD8F7,

		/////////////////
		// Scenario Mode
		/////////////////

		/// Simulator::ScenarioCreatureHealedMessage; called when a creature is healed (either by natural heal rate, or using a medkit) in Scenario mode
		kMsgScenarioCreatureHealed = 0x7C789F8,

		/// Simulator::ScenarioEnergyConsumedMessage; sent when the player consumes captain energy
		kMsgScenarioEnergyConsumed = 0x7C7A52E,

		/// No data, called when pressing the undo button in the scenario editor
		kMsgScenarioUndo = 0xC9D86390,
		/// No data, called when pressing the redo button in the scenario editor
		kMsgScenarioRedo = 0xC9D86391,

		/// Called when the captain is finished beaming down in scenario mode
		kMsgCinematicScenarioBeamDownComplete = 0x078eab55,

		/// Removes the avatar from a scenario cutscene
		kMsgCinematicScenarioClearAvatar = 0x07b509fe,

		/// Called when the size of the talked-to creature or object is being calculated. (TODO: Seems to generate one of 3 values, how to access these?)
		kMsgCinematicTalkToSizeSetup = 0x07d0c530,

		/// Called when the greeting style of the talked-to creature is being determined. (TODO: Seems to generate one of 5 values, how to access these?)
		kMsgCinematicTalkToGreetSetup = 0x07da0410,

		/// Called when the textbox style of the talked-to creature or object is being determined. (TODO: Seems to generate one of 5 values, how to access these?)
		kMsgCinematicTalkToTextSetup = 0x0754ae8a,

		/// Called when the animation style (sentient, animal, epic) of the talked-to creature is being determined.  (TODO: Seems to generate one of 3 values, how to access these?)
		kMsgCinematicTalkToAnimStyleSetup = 0x07688cad,

		/// Called when the animation emotion of the talked-to creature is being determined.  (TODO: Seems to generate one of 5 values, how to access these?)
		kMsgCinematicTalkToAnimEmotionSetup = 0x07688cad,

		/// Called when the page waiting style (wait for next or wait for last) of the talk-to dialogue is being determined (TODO: Seems to generate one of 2 values, how to access these?)
		kMsgCinematicTalkToPageSetup = 0x0750d732,

		/// Called when the talk-to dialogue skips a blank page
		kMsgCinematicTalkToSkipBlankPage = 0x07aaa58c,

		

	};

	class IMessageParameters
	{
	public:
		inline virtual ~IMessageParameters() {}
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};

	//TODO
	class EnterModeMessage
	{
		/* 08h */	uint32_t mModeID;

		/* 10h */	uint32_t mPreviousModeID;
	};

	class EnterEditorMessage : public IMessageParameters, public IVirtual
	{
	public:
		EnterEditorMessage();
		EnterEditorMessage(uint32_t editorID, ResourceKey creationName, int field_1C = 0);
		inline virtual ~EnterEditorMessage() {};

		virtual int AddRef() override;
		virtual int Release() override;

	protected:
		int mnRefCount;

	public:
		/// The ID of the editor to enter, for exmple CivAccessoriesEditorSetup
		/* 0Ch */	uint32_t mEditorID;
		/// The name of the creation, for example creature_editorModel~!0x8E6A1FF5.crt
		/* 10h */	ResourceKey mCreationName;
		/* 1Ch */	int field_1C;
	};

	/// Called every update of a mission, only if the mission is ongoing
	class MissionUpdateMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgMissionUpdate;

		/// Returns the mission that updated.
		inline cMission* GetMission() {
			return (cMission*)params[0].object;
		}
	};

	/// Called when a cCombatant is killed.
	class CombatantKilledMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgCombatantKilled;

		/// Returns the combatant that was killed
		inline cCombatant* GetCombatant() {
			return (cCombatant*)params[0].ptr;
		}

		/// Returns the combatant that attacked, might be null.
		inline cCombatant* GetAttacker() {
			return (cCombatant*)params[1].ptr;
		}
	};

	/// Called when the player empire makes a new alliance
	class PlayerEmpireAlliedMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgPlayerEmpireAllied;

		/// Returns the empire with whom the player made an alliance
		inline cEmpire* GetAlliedEmpire() {
			return (cEmpire*)params[0].ptr;
		}

		/// Returns the player empire that just made the alliance
		inline cEmpire* GetPlayerEmpire() {
			return (cEmpire*)params[1].ptr;
		}
	};

	/// Called when the player empire loses an alliance
	class PlayerEmpireLostAllianceMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgPlayerEmpireLostAlliance;

		/// Returns the empire with whom the player had the an alliance
		inline cEmpire* GetAlliedEmpire() {
			return (cEmpire*)params[0].ptr;
		}

		/// Returns the player empire that just lost the alliance
		inline cEmpire* GetPlayerEmpire() {
			return (cEmpire*)params[1].ptr;
		}
	};

	/// Called when a space tool hits a target. Called by cToolStrategy::OnHit 
	class ToolOnHitMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgToolOnHit;

		/// Returns the key that identifies the tool, as returned by cSpaceToolData::GetItemID()
		inline const ResourceKey& GetAlliedEmpire() {
			return *(ResourceKey*)params[0].ptr;
		}
	};

	class GameNounStatusChangedMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgGameNounStatusChanged;

		inline int GetStatus() {
			return params[0].int32;
		}

		/// Returns the noun, can be null
		inline cGameData* GetNoun() {
			return (cGameData*)params[1].ptr;
		}
	};

	/// Called when a creature is healed (either by natural heal rate, or using a medkit) in Scenario mode
	class ScenarioCreatureHealedMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgScenarioCreatureHealed;

		inline float GetAmountHealed() {
			return params[0]._float;
		}
	};

	/// Called when the player captain consumes energy in Scenario mode
	class ScenarioEnergyConsumedMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgScenarioEnergyConsumed;

		inline float GetAmountConsumed() {
			return params[0]._float;
		}
	};

	/// Sent when a rare item is found (even if it had already been found before) in Space Stage. 
	class SpaceRareFoundMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = kMsgSpaceRareFound;

		inline uint32_t GetRareID() {
			return params[0].uint32;
		}
	};
}