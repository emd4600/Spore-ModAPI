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
#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cScenarioClass.h>
#include <Spore\Simulator\cScenarioMarker.h>
#include <EASTL\intrusive_list.h>

#define cGameDataPtr intrusive_ptr<Simulator::cGameData>

namespace Simulator
{
	/// Base class for most Simulator objects. All cGameData objects have a *political ID* that uniquely
	/// identifies the object, and is often used to reference it in other classes.
	class cGameData 
		: public ISimulatorSerializable
		, public DefaultRefCounted
		, public intrusive_list_node
	{
	public:
		static const uint32_t TYPE = 0x17F243B;
		static const uint32_t NOUN_ID = 0x17F243B;

		cGameData();
		virtual ~cGameData() {}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		// ISimulatorSerializable
		/* 10h */	virtual bool Write(ISerializerStream* stream) = 0;  //PLACEHOLDER
		/* 14h */	virtual bool Read(ISerializerStream* stream) override;
		/* 18h */	virtual bool ISimulatorSerializable_func18h() override;
		/* 1Ch */	virtual bool WriteToXML(XmlSerializer*) override;  // write as text?
		// GetNounID is not implemented

		/// arg0->field_4 is definition ID, field_C is prop, field_0 is noun ID
		/* 24h */	virtual bool SetDefinitionID(int, int, int);  // 3 arguments, parses prop?? // the parameter is not a uint32_t
		/* 28h */	virtual void SetGameDataOwner(cGameData* pOwner);  // also sets politicalID
		/* 2Ch */	virtual bool IsDestroyed();
		/* 30h */	virtual cGameData* GetGameDataOwner();
		/* 34h */	virtual void SetGameDataOwner2(cGameData* pOwner);  // also sets politicalID
		/// Returns the TYPE field of the class, that is used for object casting.
		/* 38h */	virtual uint32_t GetCastID() const = 0;
		/* 3Ch */	virtual bool cGameData_func3Ch(int);  // just calls 40h
		/* 40h */	virtual bool cGameData_func40h();
		/* 44h */	virtual void RemoveOwner();
		/* 48h */	virtual void SetPoliticalID(uint32_t id);
		/* 4Ch */	virtual uint32_t GetPoliticalID();
		/* 50h */	virtual int WriteAsText(int);  // related with attributes

		/// Returns the scenario class for this game data, if any; if scenario data is not available
		/// (for example, player is not in an adventure), the game will crash.
		/// The scenario class is the object that holds all the adventure-related data of this object.
		/// @returns The scenario class for this object.
		cScenarioClass* GetScenarioClass();

	public:
		/* 14h */	int field_14;
		/* 18h */	cScenarioMarker* mpScenarioMarker;
		/* 1Ch */	int mScenarioClassIndex;  // -1
		/* 20h */	bool field_20;
		/* 21h */	bool mbIsDestroyed;
		/* 24h */	uint32_t mID;  // -1
		/* 28h */	uint32_t mDefinitionID;
		/* 2Ch */	intrusive_ptr<cGameData> mpGameDataOwner;
		/* 30h */	uint32_t mPoliticalID;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameData) == 0x34, "sizeof(cGameData) != 34h");

	namespace Addresses(cGameData) {
		DeclareAddress(Write);
		DeclareAddress(Read);
		DeclareAddress(ISimulatorSerializable_func18h);
		DeclareAddress(WriteToXML);

		DeclareAddress(SetDefinitionID);
		DeclareAddress(SetGameDataOwner);
		DeclareAddress(IsDestroyed);

		DeclareAddress(SetGameDataOwner2);

		DeclareAddress(cGameData_func3Ch);

		DeclareAddress(RemoveOwner);

		DeclareAddress(WriteAsText);
	}
	// Addresses kept for backwards compatibility
	namespace Addresses(cGameData)
	{
		DeclareAddress(func18h);
		DeclareAddress(func3Ch);
	}
}
