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

#include <Spore\RenderWare\KeyframeData.h>

namespace RenderWare
{
	///
	/// A channel is the group of keyframes that modify a bone.
	///
	struct AnimChannel
	{
		/* 00h */	KeyframeData* mpData;
		/* 04h */	size_t mnPoseSize;
		/* 08h */	int mPoseComponents;
	};

	///
	/// A structure that represents an animation made of multiple keyframes.
	///
	struct KeyframeAnim
	{
		

		// sub_75DE30

		/* 00h */	uint32_t* mpChannelNames;
		/* 04h */	size_t mnChannelCount;
		/* 08h */	uint32_t mSkeletonID;
		/* 0Ch */	int field_C;
		/* 10h */	KeyframeData* mpChannelData;
		/* 14h */	int field_14;  // paddingEndPos ?
		/* 18h */	int field_18;  // channelCount again=
		/* 1Ch */	int field_1C;
		/* 20h */	float animationLength;
		/* 24h */	size_t mnChannelSize;  // 12, sizeof(ChannelInfo)
		/* 28h */	int mFlags;  // pointer??
		/* 2Ch */	AnimChannel* mpChannels;

		// field_C and flags are used to find something...


		static const uint32_t RW_TYPE = 0x70001;
	};
}