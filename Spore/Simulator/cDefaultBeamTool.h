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
	class cDefaultBeamTool
		: public cToolStrategy
	{
	public:
		static const uint32_t STRATEGY_ID = 0xFC20C32D;
		static const uint32_t TYPE = 0x60079DE;

		virtual void OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition) override;
		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType) override;
		virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
		virtual bool OnMouseUp(cSpaceToolData* pTool) override;

		virtual bool func48h(cSpaceToolData* pTool, const Vector3&);
		virtual bool func4Ch(cSpaceToolData* pTool, const Vector3&);
	};

	namespace InternalAddressList(cDefaultBeamTool)
	{
		DefineAddress(OnMouseDown, GetAddress(0x10548B0, NO_ADDRESS, 0x1053D00));
		DefineAddress(OnHit, GetAddress(0x105ABC0, NO_ADDRESS, 0x105A020));
		DefineAddress(WhileFiring, GetAddress(0x105AA90, NO_ADDRESS, 0x1059EF0));
		DefineAddress(OnMouseUp, GetAddress(0x1054910, NO_ADDRESS, 0x1053D60));

		DefineAddress(func48h, GetAddress(0x1055A20, NO_ADDRESS, 0x1054E70));
		DefineAddress(func4Ch, GetAddress(0x1054960, NO_ADDRESS, 0x1053DB0));
	}
}