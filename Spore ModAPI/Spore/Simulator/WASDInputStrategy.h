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

namespace Simulator
{
	namespace WASDInputStrategy
	{
		const char* const TriggerFile = "TriggerConfigWASD";

		enum
		{
			kMoveForward = 0x00000001,
			kMoveBackward = 0x00000002,
			kMoveLeft = 0x00000003,
			kMoveRight = 0x00000004,
			kStrafeLeft = 0x00000005,
			kStrafeRight = 0x00000006
		};
	}
}