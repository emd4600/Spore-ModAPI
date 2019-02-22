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
	class cGetOutOfUFOToolStrategy
		: public cToolStrategy
	{
	public:
		static const uint32_t STRATEGY_ID = 0x21D49382;

		virtual bool OnSelect(cSpaceToolData* pTool) override;
		virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
		virtual bool WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors) override;
		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType) override;
	};

	namespace InternalAddressList(cGetOutOfUFOToolStrategy)
	{
		DefineAddress(OnSelect, GetAddress(0x1054C30, NO_ADDRESS, 0x1054080));
		DefineAddress(Update, GetAddress(0x1057890, NO_ADDRESS, 0x1056D00));
		DefineAddress(WhileAiming, GetAddress(0x1054C10, NO_ADDRESS, 0x1054060));
		DefineAddress(OnHit, GetAddress(0x105BDB0, NO_ADDRESS, 0x105B200));
	}
}