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

#include <Spore\Simulator\cToolStrategy.h>

namespace Simulator
{
	class cDefaultAoETool
		: public cToolStrategy
	{
	public:
		static const uint32_t STRATEGY_ID = 0x6CB0B689;

		virtual void OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition) override;
		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType) override;
		virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
		virtual bool OnMouseUp(cSpaceToolData* pTool) override;

		virtual bool func48h(cSpaceToolData* pTool, const Vector3&);
		virtual bool func4Ch(cSpaceToolData* pTool, const Vector3&);
	};

	namespace Addresses(cDefaultAoETool)
	{
		DeclareAddress(OnMouseDown, SelectAddress(0x1053AF0, NO_ADDRESS, 0x1052F90));
		DeclareAddress(OnHit, SelectAddress(0x105AC70, NO_ADDRESS, 0x105B660));
		DeclareAddress(WhileFiring, SelectAddress(0x10576B0, NO_ADDRESS, 0x1056B20));
		DeclareAddress(OnMouseUp, SelectAddress(0x1054A40, NO_ADDRESS, 0x1053E90));

		DeclareAddress(func48h, SelectAddress(0x1055BA0, NO_ADDRESS, 0x1054FF0));
		DeclareAddress(func4Ch, SelectAddress(0x1054A80, NO_ADDRESS, 0x1053ED0));
	}
}