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

#include <Spore\UTFWin\Effect.h>

namespace UTFWin
{
	class ICascadeEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get initial delay of the cascade, in seconds.
		///
		/* 14h */	virtual float GetDelay() const = 0;

		///
		/// Set initial delay of the cascade, in seconds.
		/// @param delay
		///
		/* 18h */	virtual void SetDelay(float delay) = 0;

		///
		/// Get interval between steps, in seconds.
		///
		/* 1Ch */	virtual float GetInterval() const = 0;

		///
		/// Set interval between steps, in seconds.
		/// @param interval
		///
		/* 20h */	virtual void SetInterval(float interval) = 0;

		static const uint32_t TYPE = 0x6F90A535;
	};

	class CascadeEffect : public Effect, public ICascadeEffect
	{
	public:
		CascadeEffect();
		virtual ~CascadeEffect() {};

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual float GetDelay() const override;
		/* 18h */	virtual void SetDelay(float delay) override;
		/* 1Ch */	virtual float GetInterval() const override;
		/* 20h */	virtual void SetInterval(float interval) override;

	protected:
		/* 10h */	float mfDelay;
		/* 14h */	float mfInterval;
		/* 18h */	Clock mClock;
		/* 30h */	int field_30;
		/* 34h */	int field_34;  // not initialized
		/* 38h */	bool field_38;
		/* 39h */	bool field_39;
		/* 3Ch */	int field_3C;  // not initialized

	};

	static_assert(sizeof(CascadeEffect) == 0x40, "sizeof(CascadeEffect) != 40h");


	//// INTERNAL IMPLEMENTATION ////

	namespace InternalAddressList(CascadeEffect)
	{
		DefineAddress(GetEventFlags, GetAddress(0x9675B0, 0x8F2710, 0x8F2720));
		DefineAddress(HandleUIMessage, GetAddress(0x967650, 0x9672D0, 0x9672D0));

		DefineAddress(SetSerializer, GetAddress(0x967620, 0x9672A0, 0x9672A0));
		DefineAddress(GetProxyID, GetAddress(0x9675E0, 0x967260, 0x967260));

		DefineAddress(ToWinProc, GetAddress(0x97E760, 0x96FEB0, 0x96FEB0));
		DefineAddress(GetDelay, GetAddress(0x980800, 0x97E440, 0x97E440));
		DefineAddress(SetDelay, GetAddress(0x9638F0, 0x967220, 0x967220));
		DefineAddress(GetInterval, GetAddress(0x97F190, 0x97EE80, 0x97EE80));
		DefineAddress(SetInterval, GetAddress(0x9675C0, 0x967240, 0x967240));
	}
}