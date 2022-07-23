#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\MathUtils.h>

/// Accesses (and creates if necessary) the current instance of Simulator::cTimeOfDay
#define TimeOfDay (*Simulator::cTimeOfDay::Get())

namespace Simulator
{
	/// Class used to manage day duration and current time of day in planets.
	/// The current time of day is not stored directly in this class, but this class
	/// can be used to change it.
	/// 
	/// This is a singleton class, so use TimeOfDay to access it.
	/// For example, `TimeOfDay.SetDayDuration(3600)`.
	class cTimeOfDay
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0x2143CD1;

		/// Returns the only cTimeOfDay instance; this function also creates
		/// that instance the first time it is called.
		static cTimeOfDay* Get();

		/// Makes the day go faster (for values greater than 1) or slower (for values lower than 1).
		/// For example, `SetSpeedMultiplier(2.0)` makes the day be twice as short 
		/// as specified in `SetDayDuration()`.
		/// @param multiplier
		void SetSpeedMultiplier(float multiplier);

		/// Sets how many seconds it takes to make a whole day, in seconds.
		/// @param seconds
		void SetDayDuration(float seconds);

		/// Sets the time at a specific position in the planet, as a number between 0.0 and 1.0.
		/// The number represents the fraction of a day, with 0.0 being equivalent to 00:00 and 
		/// 1.0 equivalent to 24:00 (which means it's the same time as 0.0).
		/// You can use the `ConvertEarthTime()` method to convert from hours:minutes to the time units
		/// required by this function.
		/// @param timeOfDay A number between 0.0 and 1.0
		/// @param position The position in the planet where it will be the specified time of day.
		void SetTimeOfDay(float timeOfDay, const Math::Vector3& position);

		/// Converts hours and minutes to a fraction of a day, from 0.0 to 1.0, 
		/// as required by `SetTimeOfDay` (in Earth time, so a day is 24 hours and an hour 60 minutes).
		/// For example, `ConvertEarthTime(12.0f, 0.0f)` returns `0.5`.
		/// @param hours 
		/// @param minutes
		inline float ConvertEarthTime(float hours, float minutes);

	public:
		/* 10h */	vector<float> field_10;  // initialized with one entry, 1440.0
		/// How many seconds it takes to make a day, in seconds. Default value is 86400.0 (24 hours)
		/* 24h */	float mDayDuration;  // 86400.0
	};
	ASSERT_SIZE(cTimeOfDay, 0x28);

	namespace Addresses(cTimeOfDay)
	{
		DeclareAddress(Get);  // 0xBC2550
		DeclareAddress(SetSpeedMultiplier);  // 0xBC1D60
		DeclareAddress(SetDayDuration);  // 0xBC1CD0
		DeclareAddress(SetTimeOfDay);  // 0xBC23A0
	}

	float cTimeOfDay::ConvertEarthTime(float hours, float minutes)
	{
		return hours / 24.0f + minutes / 1440.0f;
	}
}
