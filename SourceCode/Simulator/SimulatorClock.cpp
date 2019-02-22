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

#include <Spore\Simulator\cGonzagoTimer.h>

namespace Simulator
{
	cGonzagoTimer::cGonzagoTimer()
		: cGonzagoTimer((TimeFunction_t)(GetMethodAddress(cGonzagoTimer, GetSimulatorTime_ptr)))
	{
	}

	cGonzagoTimer::cGonzagoTimer(TimeFunction_t pTimeFunction)
		: mElapsedTime()
		, field_10()
		, mbRunning()
		, mpTimeFunction(pTimeFunction)
	{
	}

	void cGonzagoTimer::Stop()
	{
		mElapsedTime.QuadPart = 0;
		field_10.QuadPart = 0;
		mbRunning = false;
	}

	void cGonzagoTimer::SetTime(LARGE_INTEGER time)
	{
		if (mbRunning)
		{
			field_10 = time;
		}
	}

	void cGonzagoTimer::UpdateTime()
	{
		if (mbRunning)
		{
			mElapsedTime.QuadPart = mpTimeFunction().QuadPart - field_10.QuadPart;

			mbRunning = false;
		}
	}

	void cGonzagoTimer::Start()
	{
		field_10.QuadPart = mpTimeFunction().QuadPart;
		mElapsedTime.QuadPart = 0;
		mbRunning = true;
	}

	bool cGonzagoTimer::IsRunning() {
		return mbRunning;
	}

	LARGE_INTEGER cGonzagoTimer::GetElapsed()
	{
		if (mbRunning)
		{
			LARGE_INTEGER value;
			value.QuadPart = (mpTimeFunction().QuadPart + (mElapsedTime.QuadPart - field_10.QuadPart));
			return value;
		}
		else
		{
			return mElapsedTime;
		}
	}
}