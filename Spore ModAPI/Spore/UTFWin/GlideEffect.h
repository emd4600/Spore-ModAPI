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
	class IGlideEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get the direction and distance to displace the window when hidden.
		///
		/* 14h */	virtual const Point& GetOffset() const = 0;

		///
		/// Set the direction and distance to displace the window when hidden.
		/// @param offset
		///
		/* 18h */	virtual void SetOffset(const Point& offset) = 0;

		static const uint32_t TYPE = 0xEF2B293B;
	};

	class GlideEffect : public BiStateEffect, public IGlideEffect
	{
	public:
		GlideEffect();
		virtual ~GlideEffect() {}

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual const Point& GetOffset() const override;
		/* 18h */	virtual void SetOffset(const Point& offset) override;

		virtual int func80h() override;
		virtual void func88h(int, int, int) override;

	protected:
		/* 64h */	Point mOffset;
		/* 6Ch */	int field_6C;  // not initialized

	};

	static_assert(sizeof(GlideEffect) == 0x70, "sizeof(GlideEffect) != 70h");

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(GlideEffect)
	{
		DeclareAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0, 0x9633E0));
		DeclareAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0, 0x9636A0));

		DeclareAddress(SetSerializer, SelectAddress(0x970380, 0x96FFE0, 0x96FFE0));
		DeclareAddress(GetProxyID, SelectAddress(0x970250, 0x96FEC0, 0x96FEC0));

		DeclareAddress(func80h, SelectAddress(0xE1CF40, 0x1154790, 0x1154790));
		DeclareAddress(func88h, SelectAddress(0x970310, 0x96FF70, 0x96FF70));

		DeclareAddress(ToWinProc, SelectAddress(0x980500, 0x980200, 0x980230));
		DeclareAddress(GetOffset, SelectAddress(0x766FC0, 0x6E6560, 0x6E6560));
		DeclareAddress(SetOffset, SelectAddress(0x970360, 0x96FFC0, 0x96FFC0));
	}
}
