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

#define IInflateEffectPtr eastl::intrusive_ptr<UTFWin::IInflateEffect>

namespace UTFWin
{
	class IInflateEffect : public UTFWinObject
	{
	public:
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get the scale factor of the window when triggered.
		///
		/* 14h */	virtual float GetScale() const = 0;

		///
		/// Set the scale factor of the window when triggered.
		/// @param scale
		///
		/* 18h */	virtual void SetScale(float scale) = 0;

		static const uint32_t TYPE = 0xAF3DAD29;
	};

	class InflateEffect : public BiStateEffect, public IInflateEffect
	{
	public:
		InflateEffect();
		virtual ~InflateEffect() {};


		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual float GetScale() const override;
		/* 18h */	virtual void SetScale(float scale) override;

		virtual int func80h() override;
		virtual void func88h(int, int, int) override;

	protected:
		/* 64h */	float mfScale;

		char padding_68[0x50];
	};

	static_assert(sizeof(InflateEffect) == 0xB8, "sizeof(InflateEffect) != B8h");

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(InflateEffect)
	{
		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(func80h);
		DeclareAddress(func88h);

		DeclareAddress(ToWinProc);
		DeclareAddress(GetScale);
		DeclareAddress(SetScale);
	}
};
