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

#include <Spore\Clock.h>

Clock::Clock(Clock::Mode mode, bool bStart)
	: mStartTime()
	, field_8()
	, mMode()
	, mfMeasurePerTick(1.0f)
{
	this->SetMode(mode);

	if (bStart)
	{
		this->Start();
	}
}

auto_METHOD_VOID(Clock, SetMode, Args(Clock::Mode mode), Args(mode));
auto_METHOD_VOID_(Clock, Stop);
auto_METHOD_(Clock, LARGE_INTEGER, GetElapsedTicks);
auto_METHOD_(Clock, LARGE_INTEGER, GetElapsedTime);
