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

/// Access the active relationship manager, which depends on the current game stage.
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
	};

	class cRelationshipData
	{
	public:
		/* 00h */	float mfValue;
		/* 04h */	int mFlags;
		/* 08h */	map<uint32_t, float> mRelationshipEvents;
	};

	class cRelationshipManager
		: public UnknownManagerSuperclass  // ?
		, public App::IMessageListener
		, public ISimulatorSerializable
	{
	public:
		static const uint32_t TYPE = 0x301B5D9F;

		bool IsAtWar(cEmpire* pEmpire1, cEmpire* pEmpire2);

		void DeclareWar(cEmpire* pEmpire1, cEmpire* pEmpire2);

		float ApplyRelationship(uint32_t empireID, uint32_t causeEmpireID, uint32_t relationshipID, float scale = 1.0f);

	protected:
		/* 10h */	float field_10;
		/* 14h */	float field_14;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	bool mbIsInitialized;
		/* 24h */	map<int, cRelationshipData> mRelationships;  // map of maps?
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
		/* 9Ch */	vector<int> field_9C;  // vector of maps?
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
		DeclareAddress(DeclareWar);
		DeclareAddress(ApplyRelationship);
	}
}
