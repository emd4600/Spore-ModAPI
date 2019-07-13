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

#include <Spore\Simulator\cDefaultBeamTool.h>

namespace Simulator
{
	class cAbductToolStrategy
		: public cDefaultBeamTool
	{
	public:
		static const uint32_t STRATEGY_ID = 0xF58C1654;

		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType) override;
		virtual bool OnMouseUp(cSpaceToolData* pTool) override;
		virtual Vector3 GetAimPoint() override;
	};

	namespace Addresses(cAbductToolStrategy)
	{
		DeclareAddress(OnHit, SelectAddress(0x105AC80, NO_ADDRESS, 0x105A0D0));
		DeclareAddress(OnMouseUp, SelectAddress(0x1055C90, NO_ADDRESS, 0x10550E0));
		DeclareAddress(GetAimPoint, SelectAddress(0x1053B00, NO_ADDRESS, 0x1052FA0));
	}
}