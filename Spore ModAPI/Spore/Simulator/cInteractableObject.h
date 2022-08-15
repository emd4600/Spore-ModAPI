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
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\LocalizedString.h>

#define cInteractableObjectPtr eastl::intrusive_ptr<Simulator::cInteractableObject>

namespace Simulator
{
	class cCreatureBase;
	
	enum OrnamentType
	{
		kOrnamentFlower = 1,
		kOrnamentBone = 2,
		kOrnamentStick = 3
	};
	
	class cInteractableObject
		: public cGameData
		, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x398420D;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 108h */	intrusive_ptr<cCreatureBase> mpWhoIsInteractingWithMe;
		/* 10Ch */	int field_10C;
		/* 110h */	int mType;
		/* 114h */	int mPhysicsPropertyListId;  // an int, specifies what type of physics to use?
		/* 118h */	LocalizedString mName;
		/* 12Ch */	bool mbHasAttractorEffects;
		/* 12Dh */	bool field_12D;
	};
	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cInteractableObject) == 0x130, "sizeof(cOrnament) != 130h");
}