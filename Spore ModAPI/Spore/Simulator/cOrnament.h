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
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cScenarioPowerup.h>

#define cOrnamentPtr eastl::intrusive_ptr<Simulator::cOrnament>

namespace Simulator
{
	/// Used, among other things, for adventure objects (except pickable ones)
	class cOrnament
		/* 00h */	: public cGameData
		/* 34h */	, public cScenarioPowerup
		/* 70h */	, public cSpatialObject
		/* 148h */	, public cCombatant
		/* 210h */	, public cBehaviorList
	{
	public:
		static const uint32_t TYPE = 0x175CDC9;
		static const uint32_t NOUN_ID = 0x18C88E4;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;
		
	public:
		/* 228h */	int mStyle;
		/* 22Ch */	uint32_t mModelID;
		/* 230h */	bool field_230;  // true
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cOrnament) == 0x238, "sizeof(cOrnament) != 238h");
}