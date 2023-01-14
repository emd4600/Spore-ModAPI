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

#include <Spore\Object.h>
#include <Spore\LocalizedString.h>
#include <Spore\Editors\PlayAnimPanel.h>

#include <EASTL\vector.h>

#define PlayAnimButtonPtr eastl::intrusive_ptr<Editors::PlayAnimButton>

namespace Editors
{
	class PlayAnimButton 
		: public DefaultRefCounted
	{
	public:
		// Members in these classes are marked as public because they act more as just struct/containers...

		/* 08h */	uint32_t mPlayAnimName;
		/* 0Ch */	uint32_t mPlayAnimBabyName;
		/* 10h */	float mfPlayAnimBabySpeed;
		/* 14h */	float mfPlayAnimBabyDelay;
		/* 18h */	uint32_t mButtonImageNormal;
		/* 1Ch */	uint32_t mButtonImageDisabled;
		/* 20h */	uint32_t mButtonImageHighlighted;
		/* 24h */	uint32_t mButtonImageActive;
		/* 28h */	uint32_t field_28;
		/* 2Ch */	uint32_t field_2C;
		/* 30h */	uint32_t field_30;
		/* 34h */	uint32_t field_34;
		/* 38h */	uint32_t field_38;
		/* 3Ch */	LocalizedString mAnimButtonTooltip;
	};
	ASSERT_SIZE(PlayAnimButton, 0x50);

}