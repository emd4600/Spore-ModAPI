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

#define IGlideEffectPtr eastl::intrusive_ptr<UTFWin::IGlideEffect>

namespace UTFWin
{
	class IGlideEffect : public IBiStateEffect
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get the direction and distance to displace the window when hidden.
		///
		/* 14h */	virtual const Math::Point& GetOffset() const = 0;

		///
		/// Set the direction and distance to displace the window when hidden.
		/// @param offset
		///
		/* 18h */	virtual void SetOffset(const Math::Point& offset) = 0;

		static const uint32_t TYPE = 0xEF2B293B;
	};

	class GlideEffect : public BiStateEffect, public IGlideEffect
	{
	public:
		GlideEffect();
		virtual ~GlideEffect() {}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual const Math::Point& GetOffset() const override;
		/* 18h */	virtual void SetOffset(const Math::Point& offset) override;

		virtual int func80h() override;
		virtual void func88h(int, int, int) override;

	protected:
		/* 64h */	Math::Point mOffset;
		/* 6Ch */	int field_6C;  // not initialized

	};
	ASSERT_SIZE(GlideEffect, 0x70);

	namespace Addresses(GlideEffect)
	{
		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(func80h);
		DeclareAddress(func88h);

		DeclareAddress(ToWinProc);
		DeclareAddress(GetOffset);
		DeclareAddress(SetOffset);
	}
}
