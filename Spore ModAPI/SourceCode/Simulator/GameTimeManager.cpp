#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\Simulator\SubSystem\GameTimeManager.h>
#include <Spore\Simulator\cTimeOfDay.h>


namespace Simulator
{
	auto_STATIC_METHOD_(cTimeOfDay, cTimeOfDay*, Get);

	auto_METHOD_VOID(cTimeOfDay, SetDayDuration, Args(float seconds), Args(seconds));
	auto_METHOD_VOID(cTimeOfDay, SetSpeedMultiplier, Args(float multiplier), Args(multiplier));
	auto_METHOD_VOID(cTimeOfDay, SetTimeOfDay, Args(float timeOfDay, const Math::Vector3& position), Args(timeOfDay, position));

	auto_STATIC_METHOD_(cGameTimeManager, cGameTimeManager*, Get);

	auto_METHOD(cGameTimeManager, int, Pause, Args(TimeManagerPause pauseType), Args(pauseType));
	auto_METHOD(cGameTimeManager, int, Resume, Args(TimeManagerPause pauseType), Args(pauseType));
	auto_METHOD(cGameTimeManager, bool, Toggle, Args(TimeManagerPause pauseType), Args(pauseType));
	auto_METHOD(cGameTimeManager, int, GetPauseCount, Args(TimeManagerPause pauseType), Args(pauseType));
	auto_METHOD(cGameTimeManager, int, ConvertDeltaTime, Args(int time), Args(time));
	auto_METHOD_VOID(cGameTimeManager, SetSpeed, Args(int index), Args(index));

	LARGE_INTEGER cGameTimeManager::GetTimeAtStartOfFrame() {
		return mTimeAtStartOfFrame;
	}

	void cGameTimeManager::SetSpeedFactors(float speed0, float speed1, float speed2, float speed3)
	{
		mSpeedFactors[0] = speed0;
		mSpeedFactors[1] = speed1;
		mSpeedFactors[2] = speed2;
		mSpeedFactors[3] = speed3;
	}

	float cGameTimeManager::GetSpeed() {
		return mCurrentSpeed;
	}
}
#endif
