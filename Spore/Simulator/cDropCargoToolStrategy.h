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
	class cDropCargoToolStrategy
		: public cDefaultBeamTool
	{
	public:
		static const uint32_t STRATEGY_ID = 0xD001F5E2;

		virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
		virtual bool WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors) override;
		virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
		virtual bool OnMouseUp(cSpaceToolData* pTool) override;
	};

	namespace InternalAddressList(cDropCargoToolStrategy)
	{
		DefineAddress(Update, GetAddress(0x1057710, NO_ADDRESS, 0x1056B80));
		DefineAddress(WhileAiming, GetAddress(0x1054BE0, NO_ADDRESS, 0x1054030));
		DefineAddress(WhileFiring, GetAddress(0x105B5C0, NO_ADDRESS, 0x105AA10));
		DefineAddress(OnMouseUp, GetAddress(0x1054B50, NO_ADDRESS, 0x1053FA0));
	}
}