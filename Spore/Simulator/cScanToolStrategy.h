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
	class cScanToolStrategy
		: public cDefaultBeamTool
	{
	public:
		static const uint32_t STRATEGY_ID = 0xFE8FA3D3;

		virtual bool OnSelect(cSpaceToolData* pTool) override;
		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType) override;
	};

	namespace Addresses(cScanToolStrategy)
	{
		DeclareAddress(OnSelect, SelectAddress(0x1054B10, NO_ADDRESS, 0x1053F60));
		DeclareAddress(OnHit, SelectAddress(0x105B400, NO_ADDRESS, 0x105A850));
	}
}