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

#define cGonzagoTimerPtr eastl::intrusive_ptr<Simulator::cGonzagoTimer>

namespace Simulator
{
	/// A class for measuring time inside Simulator modes. This is the equivalent to the Clock class
	/// but in the Simulator.
	class cGonzagoTimer : public DefaultRefCounted
	{
	public:
		typedef LARGE_INTEGER(*TimeFunction_t)();

		cGonzagoTimer(TimeFunction_t pTimeFunction);
		cGonzagoTimer();
		virtual ~cGonzagoTimer() {};

		void Stop();

		void SetTime(LARGE_INTEGER time);

		void UpdateTime();

		void Start();

		/// Tells whether the timer is currently running and, therefore, measuring time.
		bool IsRunning();

		/// Returns the elapsed time, in milliseconds.
		LARGE_INTEGER GetElapsed();

	protected:
 
		/* 08h */	LARGE_INTEGER mElapsedTime;
		/* 10h */	LARGE_INTEGER field_10;
		/* 18h */	bool mbRunning;
		/* 1Ch */	TimeFunction_t mpTimeFunction;
	};
	ASSERT_SIZE(cGonzagoTimer, 0x20);
	static_assert(alignof(cGonzagoTimer) == 8, "alignof(cGonzagoTimer) != 8");

	namespace Addresses(cGonzagoTimer) {
		DeclareAddress(GetSimulatorTime_ptr);
	}
}