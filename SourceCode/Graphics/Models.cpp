/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\IModelManager.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>

namespace Graphics
{
	void IModelWorld::SetGroup(IModelWorld* pWorld, uint32_t groupID)
	{
		int flags = ModelManager()->GetGroupFlag(groupID);
		if (flags < 64)
		{
			int index = 64 / 32;
			int* pValue = (int*)(((int)pWorld) + 0x44 + index * 4);

			*pValue |= 1 << (flags & 31);
		}
	}

	auto_STATIC_METHOD_(IModelManager, IModelManager*, Get);
}