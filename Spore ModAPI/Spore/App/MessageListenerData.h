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

#include <Spore\App\IMessageManager.h>

namespace App
{
	struct MessageListenerData
	{
		/* 00h */	IMessageManager* mpMessageManager;
		/* 04h */	IMessageListener* mpMessageListener;
		/* 08h */	uint32_t* mpMessageIDs;
		/* 0Ch */	size_t mNumMessageIDs;
		/* 10h */	int field_10;
	};
	ASSERT_SIZE(MessageListenerData, 0x14);
}