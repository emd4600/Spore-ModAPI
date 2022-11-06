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

#include <EASTL\vector.h>

#define PlayAnimPanelPtr eastl::intrusive_ptr<Editors::PlayAnimPanel>

using namespace eastl;

namespace Editors
{
	class PlayAnimButton;

	class PlayAnimPanel 
		: public DefaultRefCounted
	{
	public:
		// Members in these classes are marked as public because they act more as just struct/containers...

		/* 08h */	int mnAnimPanelOrder;
		/* 0Ch */	uint32_t mAnimPanelIcon;
		/* 10h */	uint32_t mAnimPanelIconShadow;
		/* 14h */	vector<intrusive_ptr<PlayAnimButton>> mButtons;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(PlayAnimPanel) == 0x28, "sizeof(PlayAnimPanel) != 28h");
}
