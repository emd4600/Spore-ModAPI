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

	enum RelationshipEvents
	{
		kRelationshipEventCompliment = 0x0526E4E5,
		kRelationshipEventTrade = 0x0526E4EE,
		kRelationshipEventGift = 0x0526E4F2,
		kRelationshipEventBuyCityOver = 0x0526E4F5,
		kRelationshipEventJoinedAlliance = 0x0526E4F8,
		kRelationshipEventBribeNode = 0x0526E4FB,
		kRelationshipEventInsult = 0x0526E4FE,
		kRelationshipEventHostility = 0x0526E501,
		kRelationshipEventReligion = 0x0526E504,
		kRelationshipEventBuyCityUnder = 0x0526E50A,
		kRelationshipEventDemandRejected = 0x0526E50E,
		kRelationshipEventDeclaredWar = 0x0526E512,
		kRelationshipEventUsedNuclearWeapon = 0x05776D99,
		kRelationshipEventBrokeDeal = 0x05ADB0AA,
		kRelationshipEventFoughtEnemy = 0x05DA8036,

		kRelationshipEventSpaceMissionComplete = 0x0526E519,
		kRelationshipEventSpaceMissionFailed = 0x0526E51C,
		kRelationshipEventSpaceMissionRejected = 0x0526E51D,
		kRelationshipEventSpaceMissionAborted = 0x0526E51E,
		kRelationshipEventSpaceGiveGift = 0x0526E51F,
		kRelationshipEventSpaceBreakAlliance = 0x0526E521,
		kRelationshipEventSpaceCreateAlliance = 0x0526E524,
		kRelationshipEventSpaceTradeComplete = 0x0526E527,
		kRelationshipEventSpaceTradeDeclined = 0x0526E52A,
		kRelationshipEventSpaceCityPanicked = 0x0526E52D,
		kRelationshipEventSpaceTerraformWorsened = 0x0526E531,
		kRelationshipEventSpaceTerraformImproved = 0x0526E535,
		kRelationshipEventSpaceTerraformExtinction = 0x0526E537,
		kRelationshipEventSpaceDestroyBuilding = 0x0526E53C,
		kRelationshipEventSpaceDestroyAllyUFO = 0x0526E542,
		kRelationshipEventSpaceBadToolUse = 0x0526E545,
		kRelationshipEventSpaceGoodToolUse = 0x0526E56A,
		kRelationshipEventSpaceFloodCity = 0x0526E5CF,
		kRelationshipEventSpaceAbductCitizen = 0x0526E5D4,
		kRelationshipEventSpaceStealCommodity = 0x0526E5D8,
		kRelationshipEventSpaceCheatGood = 0x0526E5DC,
		kRelationshipEventSpaceCheatBad = 0x0526E5F3,
		kRelationshipEventSpaceNewEmpireAndCTMGOwner = 0x0526E5F4,
		kRelationshipEventSpaceUpliftedCiv = 0x055165F5,
		kRelationshipEventSpaceBadSystemPurchaseOffer = 0x05590199,
		kRelationshipEventSpaceGoodSystemPurchaseOffer = 0x055901B3,
		kRelationshipEventSpaceBeNice = 0x0577909A,
		kRelationshipEventSpaceBeNasty = 0x0577909B,
		kRelationshipEventSpacePushedTooFar = 0x057B4514,
		kRelationshipEventSpaceCapturedASystem = 0x057B9100,
		kRelationshipEventSpaceWasAtWar = 0x057E4FE3,
		kRelationshipEventSpaceEmbassyBonus = 0x0580E23B,
		kRelationshipEventSpaceDestroyUFO = 0x0591F833,
		kRelationshipEventSpaceWitholdTribute = 0x0594AFFF,
		kRelationshipEventSpaceAcceptGift = 0x0594B017,
		kRelationshipEventSpaceMissionStarted = 0x05B6CE81,
		kRelationshipEventSpaceCommunicatedNice = 0x05B6CF09,
		kRelationshipEventSpacePersonalityNice = 0x05B6FCC9,
		kRelationshipEventSpacePersonalityMean = 0x05B6FCD4,
		kRelationshipEventSpaceAvoidedContact = 0x05B942D0,
		kRelationshipEventSpaceCommunicatedMean = 0x05F62736,
		kRelationshipEventSpaceStartedWar = 0x05F8A1AD,
		kRelationshipEventSpaceArchetypeNice = 0x05FF85B2,
		kRelationshipEventSpaceArchetypeMean = 0x05FF85B3,
		kRelationshipEventSpaceArchetypeMods = 0x05FF85B4,
		kRelationshipEventSpaceSuperPower = 0x0601DF2A,
		kRelationshipEventSpaceTradeRouteSpice = 0x0667AF08,
		kRelationshipEventSpaceAlliedWithGrob = 0x068B2938,
		kRelationshipEventSpaceCommittedAtrocity = 0x068B2971,

		kRelationshipEventTribeAttack = 0x0530CF00,
		kRelationshipEventTribeKill = 0x0530CF01,
		kRelationshipEventTribeRaid = 0x0530CF02,
		kRelationshipEventTribeStealBaby = 0x0530CF03,
		kRelationshipEventTribeAttackToolOrHut = 0x0530CF04,
		kRelationshipEventTribeDestroyTool = 0x0530CF05,
		kRelationshipEventTribeGift = 0x0530CF06,
		kRelationshipEventTribeSocial = 0x0530CF07,
		kRelationshipEventTribeRecruit = 0x0530CF08,
		kRelationshipEventTribeConvert = 0x0530CF09,
		kRelationshipEventTribeCheatGood = 0x0530CF0A,
		kRelationshipEventTribeCheatBad = 0x0530CF0B,
		kRelationshipEventTribeSocialPower = 0x54EAB4B3
	};

	class cRelationshipData
	{
	public:
		/* 00h */	float mValue;
		// Flag 0x1 is at war
		/* 04h */	int mFlags;
		/* 08h */	map<uint32_t, float> mRelationshipEvents;
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

		/// Returns true if the two political entities are currently at war, or false otherwise.
		/// The order of the parameters is irrelevant.
		/// @param politicalID1
		/// @param politicalID2
		bool IsAtWar(uint32_t politicalID1, uint32_t politicalID2);

		/// Declares war between the two empires, applying a bad relationship between them.
		/// @param pEmpire1
		/// @param pEmpire2
		void DeclareWar(cEmpire* pEmpire1, cEmpire* pEmpire2);

		/// Declares peace between two political entities. This does not change the relationship events or score.
		/// @param politicalID1
		/// @param politicalID2
		void DeclarePeace(uint32_t politicalID1, uint32_t politicalID2);

		/// Resets the relationship between two political entities, setting their global relationship to 0
		/// and removing all events between them.
		/// @param politicalID1
		/// @param politicalID2
		void ResetRelationship(uint32_t politicalID1, uint32_t politicalID2);

		/// Applies a relationship event between two political entites (tribes, civilizations, empires,...).
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

	protected:
		/* 10h */	float field_10;
		/* 14h */	float field_14;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	bool mbIsInitialized;
		/* 24h */	map<pair<uint32_t, uint32_t>, cRelationshipData> mRelationships;  // map of maps?
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	vector<int> field_48;
		/* 5Ch */	int field_5C;  // not initialized
		/* 60h */	vector<uint32_t> mEmpiresToDecayPending;
		/* 74h */	int field_74;  // not initialized
		/* 78h */	int field_78;
		/* 7Ch */	int field_7C;  // not initialized
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	App::MessageListenerData mMessageData;
		/* 9Ch */	vector<int> field_9C;  // vector of maps? Similar to relationships, but for non-empires
		/* B0h */	int field_B0;  // not initialized
		/* B4h */	vector<int> field_B4;
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	vector<int> field_CC;
		/* E0h */	int field_E0;  // not initialized
		/* E4h */	map<int, int> field_E4;

	public:
		/// Gets the active relationship manager, which depends on the current game stage.
		static cRelationshipManager* Get();
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cRelationshipManager) == 0x100, "sizeof(cRelationshipManager) != 100h");

	namespace Addresses(cRelationshipManager)
	{
		DeclareAddress(Get);

		DeclareAddress(IsAtWar);
		DeclareAddress(IsAtWar2);
		DeclareAddress(DeclareWar);
		DeclareAddress(DeclarePeace);
		DeclareAddress(ResetRelationship);
		DeclareAddress(ApplyRelationship);
	}
}
