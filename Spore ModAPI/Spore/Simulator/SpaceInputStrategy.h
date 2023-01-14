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
	namespace SpaceInputStrategy
	{
		const char* const TriggerFile = "TriggerConfigSpaceGame";

		enum Actions
		{
			kZoomIn = 0x00000009,
			kZoomOut = 0x00000010,
			kDiscreteZoomIn = 0x11111111,
			kDiscreteZoomOut = 0x22222222,
			kPitchUp = 0x00000007,
			kPitchDown = 0x00000008,
			kRotateLeft = 0x00000011,
			kRotateRight = 0x00000012,
			kMovementMouse = 0xcccccccc,  // right button
			kToolsMouse = 0xdddddddd,  // left button
			kCameraMouse = 0xcdcdcdcd,  // middle button
		};
	}
}