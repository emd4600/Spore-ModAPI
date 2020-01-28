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

#include <Spore\Simulator\cInteractableObject.h>
#include <Spore\Simulator\cOrnamentBase.h>
#include <Spore\Simulator\cCombatant.h>

#define cInteractiveOrnamentPtr intrusive_ptr<Simulator::cInteractiveOrnament>

namespace Simulator
{
	class cInteractiveOrnament
		: public cInteractableObject
		, public cOrnamentBase
		, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0x3A25119;
		static const uint32_t NOUN_ID = 0x3A2511E;

		using Object::Release;
		using Object::AddRef;
		using Object::Cast;
	
		enum Flags
		{
			kUsesLifetime = 2,
			kPickupEnabled = 0x200
		};
		
	public:
		/* 238h */	int mFlags;
		/* 23Ch */	bool field_23C;  // true
		/* 240h */	int mLifetime;  // -1
		/* 244h */	int mFadeTimer;
		/* 248h */	int field_248;  // -1
		/* 24Ch */	vector<int> field_24C;  // only 2 items, destructed models?
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cInteractiveOrnament) == 0x260, "sizeof(cInteractiveOrnament) != 260h");
}