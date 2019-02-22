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
#include <Spore\Simulator\SubSystem\ToolManager.h>

namespace Simulator
{
	auto_METHOD(cToolManager, bool, LoadTool, PARAMS(const ResourceKey& id, intrusive_ptr<cSpaceToolData>& dst),
		PARAMS(id, dst));

	auto_STATIC_METHOD_(cToolManager, cToolManager*, Get);

	auto_METHOD(cToolManager, cToolStrategy*, GetStrategy, PARAMS(uint32_t strategyID), PARAMS(strategyID));

	auto_METHOD(cToolManager, bool, ActivateTool, PARAMS(cSpaceToolData* pTool), PARAMS(pTool));
	auto_METHOD(cToolManager, bool, DeactivateTool, PARAMS(cSpaceToolData* pTool), PARAMS(pTool));
	auto_METHOD(cToolManager, bool, OnMouseUp, PARAMS(cSpaceToolData* pTool), PARAMS(pTool));

	const char16_t* cToolManager::GetToolFailText(ToolFailText index) {
		return mToolFailTexts[index].GetText();
	}

	void cToolManager::AddStrategy(cToolStrategy* pStrategy, uint32_t id)
	{
		mStrategies[id] = pStrategy;
	}
}