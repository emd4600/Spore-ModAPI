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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cCreatureCitizen.h>
#include <Spore\Simulator\cCityWalls.h>
#include <Spore\Editors\INameableEntity.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

#define cCommunityPtr eastl::intrusive_ptr<Simulator::cCommunity>

namespace Simulator
{
	struct cEmptyBubble
	{
		/* 00h */	Math::Vector3 mCenter;
		/* 0Ch */	float mRadius;
		/* 10h */	uint32_t mSourceID;
	};

	struct cLaneInfo
	{
		/* 00h */	Math::Vector3 mPosition;
		/* 0Ch */	eastl::vector<int> mConnections;
	};

	///
	/// The following attributes are saved:
	/// - mCommunitySize
	/// - mAssemblyBubbles
	/// - mLanes
	/// - mName
	/// - mDescription
	/// - mpLeader
	///
	class cCommunity 
		: public cGameData
		, public Editors::INameableEntity
	{
	public:
		// No TYPE

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Returns the leader of this community, casted as a cCreatureCitizen.
		/// This can be used in cTribe to get the tribe chief.
		/// @returns
		inline cCreatureCitizen* GetLeaderCitizen();

		/* 54h */	virtual int func54h();  // returns 0
		/* 58h */	virtual Vector3	func58h();  // in city, returns walls position
		/* 5Ch */	virtual Vector3	func5Ch();
		/* 60h */	virtual float func60h();
		/* 64h */	virtual Vector3& func64h();
		/* 68h */	virtual void func68h();
		/* 6Ch */	virtual cCityWalls* GetCityWalls();  // returns 0
		/* 70h */	virtual eastl::vector<ObjectPtr>& GetPopulation();
		/* 74h */	virtual int GetPopulationCount();  // returns the count of vector returned by func70h
		/* 78h */	virtual void func78h(); 
		/* 7Ch */	virtual eastl::string16& GetCommunityName();
		/* 80h */	virtual void func80h();
		/* 84h */	virtual void func84h();  // deletes AssemblyBubbles?
		/* 88h */	virtual void func88h();  // does nothing

	public:
		/* 38h */	int mCommunitySize;
		/* 3Ch */	eastl::vector<int> field_3C;
		/* 50h */	int field_50;  // not initialized
		/* 54h */	int field_54;  // not initialized
		/* 58h */	eastl::vector<int> field_58;
		/* 6Ch */	bool field_6C;
		/* 70h */	eastl::vector<cEmptyBubble> mAssemblyBubbles;
		/* 84h */	eastl::vector<cLaneInfo> mLanes;
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	int field_A0;
		/* A4h */	int field_A4;
		/* A8h */	int field_A8;
		/* ACh */	int field_AC;
		/* B0h */	cGonzagoTimer field_B0;
		/* D0h */	eastl::vector<cSpatialObjectPtr> field_D0;  // With release at C0h
		/* E4h */	eastl::vector<ObjectPtr> mCommunityMembers;
		/* F8h */	eastl::string16 mName;
		/* 108h */	eastl::string16 mDescription;
		/* 118h */	int field_118;  // -1
		/* 11Ch */	cCreatureBasePtr mpLeader;
	};
	ASSERT_SIZE(cCommunity, 0x120);

	cCreatureCitizen* cCommunity::GetLeaderCitizen()
	{
		return object_cast<cCreatureCitizen>(mpLeader.get());
	}
}