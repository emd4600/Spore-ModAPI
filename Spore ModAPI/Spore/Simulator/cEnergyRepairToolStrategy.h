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

#include <Spore\Simulator\cRepairToolStrategy.h>

#define cEnergyRepairToolStrategyPtr eastl::intrusive_ptr<Simulator::cEnergyRepairToolStrategy>

namespace Simulator
{
	class cEnergyRepairToolStrategy
		: public cRepairToolStrategy
	{
	public:
		static const uint32_t STRATEGY_ID = 0x28AE31DE;

		virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
		virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;
		virtual int ProcessCost(int useCost) override;
	};

	namespace Addresses(cEnergyRepairToolStrategy)
	{
		DeclareAddress(Update);
		DeclareAddress(OnHit);
		DeclareAddress(ProcessCost);
	}
}
