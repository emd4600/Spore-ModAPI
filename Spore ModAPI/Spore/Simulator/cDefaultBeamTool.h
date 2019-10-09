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

	namespace Addresses(cDefaultBeamTool)
	{
		DeclareAddress(OnMouseDown, SelectAddress(0x10548B0, NO_ADDRESS, 0x1053D00));
		DeclareAddress(OnHit, SelectAddress(0x105ABC0, NO_ADDRESS, 0x105A020));
		DeclareAddress(WhileFiring, SelectAddress(0x105AA90, NO_ADDRESS, 0x1059EF0));
		DeclareAddress(OnMouseUp, SelectAddress(0x1054910, NO_ADDRESS, 0x1053D60));

		DeclareAddress(func48h, SelectAddress(0x1055A20, NO_ADDRESS, 0x1054E70));
		DeclareAddress(func4Ch, SelectAddress(0x1054960, NO_ADDRESS, 0x1053DB0));
	}
}