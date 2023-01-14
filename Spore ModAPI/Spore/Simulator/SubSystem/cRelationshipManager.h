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

#include <Spore\App\MessageListenerData.h>
#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\SimulatorEnums.h>

#include <EASTL\map.h>
#include <EASTL\vector.h>

/// Access the active relationship manager, which depends on the current game stage. Check cRelationshipManager.
#define RelationshipManager (*Simulator::cRelationshipManager::Get())

namespace Simulator
{
	class cEmpire;

	class UnknownManagerSuperclass
	{
	public:
		virtual ~UnknownManagerSuperclass() = 0;
		virtual void Initialize() = 0;
		virtual void Dispose() = 0;
		virtual void func0Ch(int, int) = 0;
		virtual void func10h(int, int) = 0;
		virtual uint32_t GetType() = 0;

	protected:
		int mnRefCount;
	};

	class cRelationshipData
	{
	public:
		/* 00h */	float mValue;
		// Flag 0x1 is at war, 0x2 allied?
		/* 04h */	int mFlags;
		/* 08h */	eastl::map<uint32_t, float> mRelationshipEvents;
	};

	/// Handles relationships between political entities.
	/// 
	/// A political entity is a tribe, civilization, empire, etc. Relationships are always between two
	/// different political enties (such as two empires). They are composed of a series of events (declared war,
	/// gave gift, etc) and a global score (negative means you hate each other, positive you like each other).
	class cRelationshipManager
		: public UnknownManagerSuperclass  // ?
		, public App::IMessageListener
		, public ISimulatorSerializable
	{
	public:
		static const uint32_t TYPE = 0x301B5D9F;

		/// Returns true if the two empires are currently at war, or false otherwise.
		/// The order of the parameters is irrelevant.
		/// @param pEmpire1
		/// @param pEmpire2
		bool IsAtWar(cEmpire* pEmpire1, cEmpire* pEmpire2);

#ifndef SDK_TO_GHIDRA
		/// Returns true if the two political entities are currently at war, or false otherwise.
		/// The order of the parameters is irrelevant.
		/// @param politicalID1
		/// @param politicalID2
		bool IsAtWar(uint32_t politicalID1, uint32_t politicalID2);

		/// Returns true if there is an alliance between the two empires, or false otherwise.
		/// The order of the parameters is irrelevant.
		/// @param pEmpire1
		/// @param pEmpire2
		bool IsAllied(cEmpire* pEmpire1, cEmpire* pEmpire2);
#else
		bool IsAtWar2(uint32_t politicalID1, uint32_t politicalID2);
		bool IsAllied2(cEmpire* pEmpire1, cEmpire* pEmpire2);
#endif

		/// Returns true if there is an alliance between the two political entities, or false otherwise.
		/// The order of the parameters is irrelevant.
		/// @param politicalID1
		/// @param politicalID2
		bool IsAllied(uint32_t politicalID1, uint32_t politicalID2);

		/// Declares war between the two empires, applying a bad relationship between them.
		/// @param pEmpire1
		/// @param pEmpire2
		void DeclareWar(cEmpire* pEmpire1, cEmpire* pEmpire2);

		/// Declares peace between two empires. This does not change the relationship events or score.
		/// @param pEmpire1
		/// @param pEmpire2
		void DeclarePeace(cEmpire* pEmpire1, cEmpire* pEmpire2);

		/// Declares an alliance between two empires. 
		/// If one of the empires is the player, it sends a SimulatorMessages::kMsgPlayerEmpireAllied message.
		void DeclareAlliance(cEmpire* pEmpire1, cEmpire* pEmpire2);

		/// Breaks the alliance between two empires, if it exists.
		/// If one of the empires is the player, it sends a SimulatorMessages::kMsgPlayerEmpireLostAlliance message.
		void BreakAlliance(cEmpire* pEmpire1, cEmpire* pEmpire2);


		//TODO sub_D001E0

		/// Resets the relationship between two political entities, setting their global relationship to 0
		/// and removing all events between them.
		/// @param politicalID1
		/// @param politicalID2
		void ResetRelationship(uint32_t politicalID1, uint32_t politicalID2);

		/// Applies a relationship event between two political entities (tribes, civilizations, empires,...).
		/// The relationship ID is a property ID; the list of base relationships is found in the RelationshipEvents enum,
		/// but more can be added.
		/// The relations aren't necessarily symmetric, so there's one of the two political entities that is considered
		/// the causant of the relation change (for example, the empire that declared war is responsible for the bad relation).
		/// @param politicalID ID of the political entity
		/// @param causePoliticalID ID of the other political entity, that caused the relation change
		/// @param relationshipID ID of the relationship properties, like those in RelationshipEvents
		/// @param scale Optional, a multiplier over the effect the relationship has.
		/// @returns The current state of the relationship
		float ApplyRelationship(uint32_t politicalID, uint32_t causePoliticalID, uint32_t relationshipID, float scale = 1.0f);

		/// Returns true if there is a relationship between the two political entities.
		/// @param politicalID1
		/// @param politicalID2
		/// @returns
		bool RelationshipExists(uint32_t politicalID1, uint32_t politicalID2);

		/// Returns the value of a relationship event between two political entities, or 0 if no such relation exists.
		/// @param politicalID1
		/// @param politicalID2
		/// @param relationshipID
		/// @returns
		float GetRelationshipEventValue(uint32_t politicalID1, uint32_t politicalID2, uint32_t relationshipID);

	public:
		/* 10h */	float field_10;
		/* 14h */	float field_14;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	bool mbIsInitialized;
		/* 24h */	eastl::map<eastl::pair<uint32_t, uint32_t>, cRelationshipData> mRelationships;  // map of maps?
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	eastl::vector<int> field_48;
		/* 5Ch */	int field_5C;  // not initialized
		/* 60h */	eastl::vector<uint32_t> mEmpiresToDecayPending;
		/* 74h */	int field_74;  // not initialized
		/* 78h */	int field_78;
		/* 7Ch */	int field_7C;  // not initialized
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	App::MessageListenerData mMessageData;
		/* 9Ch */	eastl::vector<int> field_9C;  // vector of maps? Similar to relationships, but for non-empires
		/* B0h */	int field_B0;  // not initialized
		/* B4h */	eastl::vector<int> field_B4;
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	eastl::vector<int> field_CC;
		/* E0h */	int field_E0;  // not initialized
		/* E4h */	eastl::map<int, int> field_E4;

	public:
		/// Gets the active relationship manager, which depends on the current game stage.
		static cRelationshipManager* Get();
	};
	ASSERT_SIZE(cRelationshipManager, 0x100);

	namespace Addresses(cRelationshipManager)
	{
		DeclareAddress(Get);

		DeclareAddress(IsAtWar);
		DeclareAddress(IsAtWar2);
		DeclareAddress(IsAllied);
		DeclareAddress(IsAllied2);
		DeclareAddress(DeclareWar);
		DeclareAddress(DeclarePeace);
		DeclareAddress(DeclareAlliance);
		DeclareAddress(BreakAlliance);
		DeclareAddress(ResetRelationship);
		DeclareAddress(ApplyRelationship);
		DeclareAddress(RelationshipExists);
		DeclareAddress(GetRelationshipEventValue);
	}
}
