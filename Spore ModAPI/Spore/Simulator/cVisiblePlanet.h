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

#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cGameData.h>

#define cVisiblePlanetPtr eastl::intrusive_ptr<Simulator::cVisiblePlanet>

namespace Simulator
{
	class cPlanet;

	class cVisiblePlanet
		: public cSpatialObject
		, public cGameData
	{
	public:
		static const uint32_t TYPE = 0x44462A6;
		static const uint32_t NOUN_ID = 0x44462A6;

		using Object::Cast;
		using Object::AddRef;
		using Object::Release;

	public:
		/* 108h */	eastl::intrusive_ptr<cPlanet> mpPlanet;
	};
	ASSERT_SIZE(cVisiblePlanet, 0x10C);

	class cPlanetGfx
		: public cSpatialObjectView
	{
	public:
		static const uint32_t VIEW_ID = cVisiblePlanet::NOUN_ID;

	public:
		/* 34h */	eastl::intrusive_ptr<cPlanet> mpPlanet;
		/* 38h */	eastl::vector<IVisualEffectPtr> field_38;
		/* 4Ch */	eastl::vector<int> field_4C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
	};
	ASSERT_SIZE(cPlanetGfx, 0x68);
}