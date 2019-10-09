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

#include <Spore\UTFWin\EventTimeFunctionBase.h>

namespace UTFWin
{
	class BehaviourTimeRamp : public EventTimeFunctionBase
	{
	public:
		BehaviourTimeRamp();
		virtual ~BehaviourTimeRamp();
	};

	class BehaviourTimeSmoothRamp : public BehaviourTimeRamp
	{
	public:
		BehaviourTimeSmoothRamp();
		BehaviourTimeSmoothRamp(float fSmoothTimeIn, float fSmoothTimeOut);
		virtual ~BehaviourTimeSmoothRamp();
	};

	enum class OscillatorTimeFunction : uint32_t
	{
		Wave = 1
	};

	class BehaviourTimeOscillator : public EventTimeFunctionBase
	{
	public:
		BehaviourTimeOscillator();
		BehaviourTimeOscillator(bool bCeiling);
		virtual ~BehaviourTimeOscillator();

	protected:
		/* 48h */	bool mbCeiling;
		/* 49h */	bool field_49;
		/* 4Ch */	OscillatorTimeFunction mType;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////


	inline BehaviourTimeRamp::~BehaviourTimeRamp() {}


	inline BehaviourTimeSmoothRamp::BehaviourTimeSmoothRamp()
		: BehaviourTimeSmoothRamp(0.5f, 0.5f)
	{
	}

	inline BehaviourTimeSmoothRamp::~BehaviourTimeSmoothRamp() {}


	inline BehaviourTimeOscillator::BehaviourTimeOscillator()
		: BehaviourTimeOscillator(true)
	{
	}

	inline BehaviourTimeOscillator::~BehaviourTimeOscillator() {}
}