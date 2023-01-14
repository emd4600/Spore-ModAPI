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
	namespace ScenarioInputStrategy
	{
		const char* const TriggerFile = "TriggerConfigScenarioMode";

		enum Actions
		{
			kActJump = 0x00000007,
			kActSprint = 0x00000008,
			kActSneak = 0x00000009,
			kActBlock = 0x00000019,
			kActAction = 0x00000016,
			kActAutorun = 0x93cf382f,
			kActDropAllItems = 0x00000021,

			kActTargetNearest = 0x051893ad,
			kActUntarget = 0x00000015,
			kActToggleVerbTray = 0xf3ce0149,

			kActCameraRotateLeft = 0x00000010,
			kActCameraRotateRight = 0x00000011,
			kActCameraZoomIn = 0x00000012,
			kActCameraZoomOut = 0x00000013,
			kActCameraReset = 0x00000014,
			kActCameraPitchPan = 0x00000018,
			kActCameraControl = 0x0000000,
			
			kActDebugLocomotion = 0x99999992,
		};
	}
}