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

#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>

#define TuningSpine (*Editors::cTuningSpine::Get())

namespace Editors
{
	class cTuningSpine
	{
	public:
		static cTuningSpine* Get();

		virtual ~cTuningSpine() = 0;

	public:
		/* 04h */	Math::ColorRGB tuningSpineHandleColor;
		/* 10h */	float tuningSpineHandleSize;
		/* 14h */	float tuningSpineHandleAlpha;
		/* 18h */	float tuningSpineHandleOverdrawAlpha;
		/* 1Ch */	float tuningSpineHandleDistance;
		/* 20h */	Math::ColorRGBA tuningVertebraTorsoRolloverColor;
		/* 30h */	Math::ColorRGBA tuningVertebraTorsoSelectedColor;
		/* 40h */	Math::ColorRGBA tuningVertebraHighlightColor;
		/* 50h */	Math::ColorRGBA tuningVertebraUnselectedColor;
		/* 60h */	ResourceKey editorSpineHandleTuningFile;
		/* 6Ch */	ResourceKey editorDeformHandleTuningFile;
		/* 78h */	ResourceKey editorNudgeHandleTuningFile;
		/* 84h */	ResourceKey editorPowerHandleTuningFile;
		/* 90h */	ResourceKey editorBallConnectorHandleTuningFile;
		/* 9Ch */	ResourceKey editorRotationBallHandleTuningFile;
		/* A8h */	ResourceKey editorRotationRingHandleTuningFile;
		/* B4h */	float tuningVertebraFadeTime;
	};
	ASSERT_SIZE(cTuningSpine, 0xB8);

	namespace Addresses(cTuningSpine)
	{
		DeclareAddress(Get);  // 0x401070, 0x401070
	}
}