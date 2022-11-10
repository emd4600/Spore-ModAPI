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

#define IPerspectiveEffectPtr eastl::intrusive_ptr<UTFWin::IPerspectiveEffect>

namespace UTFWin
{
	class PerspectiveEffect;

	class IPerspectiveEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get near plane z-position (strength of perspective effect).
		///
		/* 14h */	virtual float GetNearPlane() const = 0;

		///
		/// Set near plane z-position (strength of perspective effect).
		/// @param nearPlane
		///
		/* 18h */	virtual void SetNearPlane(float nearPlane) = 0;

		static const uint32_t TYPE = 0xEF2B293B;
	};

	class PerspectiveEffect : public Effect, public IPerspectiveEffect
	{
	public:
		PerspectiveEffect();
		virtual ~PerspectiveEffect() {}

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual float GetNearPlane() const override;
		/* 18h */	virtual void SetNearPlane(float nearPlane) override;

		virtual void func80h(int);

	protected:
		/* 10h */	float mfNearPlane;
	};
	ASSERT_SIZE(PerspectiveEffect, 0x14);

	namespace Addresses(PerspectiveEffect)
	{
		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(func80h);

		DeclareAddress(ToWinProc);
		DeclareAddress(GetNearPlane);
		DeclareAddress(SetNearPlane);
	}
};
