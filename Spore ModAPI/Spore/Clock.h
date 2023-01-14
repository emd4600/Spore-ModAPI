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

#include <Spore\Internal.h>

///
/// A class used for measuring time. It supports multiple precisions from the enum Clock::Mode:
/// *minutes*, *seconds*, *milliseconds*, *microseconds*, *nanoseconds*, *ticks* and *processor time stamp*.
///
/// In order to use a clock, first you have to start it with the Clock::Start() method. Then just use the
/// Clock::GetElapsed() method (or its variants) to get the elapsed time since the clock was started.
///
/// You can pause the clock using Clock::Pause(), then use `Start()` again to continue counting the accumulated time.
/// If you want to clear the accumulated time and count from 0, use Clock::Reset().
///
class Clock
{
public:
	enum class Mode
	{
		/// Uses QueryPerformanceCounter to measure time (in ticks).
		Ticks = 0,
		/// Uses __rdtsc (Read Time Stamp Counter) to get the current time (in ticks?), instead of QueryPerformanceCounter.
		ProcessorTimeStamp = 1,
		/// Measures the time with nanosecond precision (1 second = 10e9 nanoseconds).
		/// Uses QueryPerformanceCounter to measure time.
		Nanoseconds = 2,
		/// Measures the time with microsecond precision (1 second = 10e6 microseconds).
		/// Uses QueryPerformanceCounter to measure time.
		Microseconds = 3,
		/// Measures the time with milliseconds precision (1 second = 10e3 milliseconds).
		/// Uses QueryPerformanceCounter to measure time.
		Milliseconds = 4,
		/// Measures the time with seconds precision.
		/// Uses QueryPerformanceCounter to measure time.
		Seconds = 5,
		/// Measures the time with minute precision (60 seconds = 1 minute).
		/// Uses QueryPerformanceCounter to measure time.
		Minutes = 6,
	};

	/// Creates a new clock object with the specified precision mode. Optionally, you can make
	/// the clock start counting.
	/// @param mode The precision with which the clock will measure time.
	/// @param start [Optional] If true, the clock will start counting time. False by default.
	Clock(Clock::Mode mode = Clock::Mode::Ticks, bool start = false);

	/// Changes the precision mode.
	/// @param mode The precision with which the clock will measure time.
	void SetMode(Clock::Mode mode);

	/// Starts the clock, if it's not already running. If the clock was paused, it will continue
	/// counting from the time accumulated until the last pause.
	void Start();

	/// Stops the clock, reseting the initial time to 0. After pausing, the clock can be started again using
	/// Clock::Start(); if started again, it will continue with the time accumulated until the stop.
	void Pause();

	/// Stops the clock and clears all accumulated time. This is equivalent to creating a new clock again.
	/// After a reset, getting the elapsed time will return 0 until the clock is started again.
	void Reset();

	/// Returns the elapsed time in the specified precision measure, conserving all decimals.
	/// @returns The time passed since the clock was created/reset, in the assigned units.
	float GetElapsed() const;

	/// Returns the elapsed time in ticks (regardles of the clock mode).
	LARGE_INTEGER GetElapsedTicks() const;

	/// Returns the elapsed time in the specified precision measure, rounded to the closest integer.
	int GetElapsedTime() const;

	/// Tells whether the clock is counting (`true`) or is paused (`false`).
	bool IsRunning() const;

protected:
	LARGE_INTEGER mStartTime;
	LARGE_INTEGER mAccumulatedTime;
	/// The mode (precision) with which the time is measured.
	Clock::Mode mMode;
	/// Derived from mMode, how many units of measurement (seconds, nanoseconds, etc) are equal to 1 tick.
	float mMeasurePerTick;  // 1.0f

};
ASSERT_SIZE(Clock, 0x18);

namespace Addresses(Clock)
{
	DeclareAddress(Stop);
	DeclareAddress(Pause);
	DeclareAddress(SetMode);
	DeclareAddress(GetElapsedTicks);
	DeclareAddress(GetElapsedTime);


	// 1 - year
	// 2 - month
	// 6 - day of month
	// 8 - hour
	// 9 - minute
	// 10 - second
	//DeclareAddress(GetTimeParam);
};

#ifndef SDK_TO_GHIDRA
inline void Clock::Reset() {
	mStartTime.QuadPart = 0;
	mAccumulatedTime.QuadPart = 0;
}

inline void Clock::Start()
{
	if (!mStartTime.QuadPart)
	{
		if (mMode == Clock::Mode::ProcessorTimeStamp)
		{
			mStartTime.QuadPart = __rdtsc();
		}
		else
		{
			QueryPerformanceCounter(&mStartTime);
		}
	}
};

inline float Clock::GetElapsed() const
{
	return GetElapsedTicks().LowPart * mMeasurePerTick;
}

inline bool Clock::IsRunning() const {
	return mStartTime.QuadPart != 0;
}
#endif
