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

#include <Spore\UTFWin\EventPropertyObject.h>

namespace UTFWin
{
	class IEventTimeFunction : public EventPropertyObject
	{
	public:
		static const uint32_t TYPE = 0x243A853;

	private:
		// It has a lot of things to do, so we disable this. Maybe we'll add support for these event things in the future.
		virtual void func00h() = 0;
	};

	class EventTimeFunctionBase : public IEventTimeFunction
	{
	public:

	protected:
		/* 0Ch */	float mfDuration;
		/* 10h */	float mfFrequency;
		/* 14h */	float mfDamping;
		/* 18h */	float mfSmoothTimeIn;
		/* 1Ch */	float mfSmoothTimeOut;
		/* 20h */	float mfPreDelayTime;
		/* 24h */	float mfPostDelayTime;
		/* 28h */	float field_28;
		/* 2Ch */	float field_2C;
		/* 30h */	float field_30;
		/* 34h */	float field_34;
		/* 38h */	bool field_38;
		/* 39h */	bool mbNegated;
		/* 3Ah */	bool field_3A;
		/* 3Ch */	float field_3C;
		/* 40h */	float field_40;
		/* 44h */	float field_44;
	};
	ASSERT_SIZE(EventTimeFunctionBase, 0x48);
}