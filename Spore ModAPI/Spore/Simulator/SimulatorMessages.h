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

		/// Simulator::GameNounStatusChangedMessage
		kMsgGameNounStatusChanged = 0x1A0219E,

		/// Simulator::MissionUpdateMessage; every update of a mission, only if the mission is ongoing
		kMsgMissionUpdate = 0x38CF2FD,

		/// Simulator::CombatantKilledMessage; called when a combatant is killed 
		kMsgCombatantKilled = 0x1622184,

		/// Simulator::PlayerEmpireAlliedMessage; called when the player empire makes a new alliance
		kMsgPlayerEmpireAllied = 0x4445D43,

		/// Simulator::PlayerEmpireLostAllianceMessage; called when the player empire loses an alliance
		kMsgPlayerEmpireLostAlliance = 0x4445D44,

		/// Called when a spaceship uses an sculpting or coloring tool and it hits the planet. No parameters.
		kMsgSculptOrColorToolHit = 0xF46092DB,

		/// Simulator::ToolOnHitMessage; called when a space tool hits a target
		kMsgToolOnHit = 0x56690BB,
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
}