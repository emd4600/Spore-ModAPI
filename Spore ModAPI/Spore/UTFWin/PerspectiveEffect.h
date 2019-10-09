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

	static_assert(sizeof(PerspectiveEffect) == 0x14, "sizeof(PerspectiveEffect) != 14h");

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(PerspectiveEffect)
	{
		DeclareAddress(GetEventFlags, SelectAddress(0x980770, 0x980440, 0x980470));
		DeclareAddress(HandleUIMessage, SelectAddress(0x980780, 0x980450, 0x980480));

		DeclareAddress(SetSerializer, SelectAddress(0x980850, 0x980560, 0x980590));
		DeclareAddress(GetProxyID, SelectAddress(0x980810, 0x9804E0, 0x980510));

		DeclareAddress(func80h, SelectAddress(0x9807E0, 0x9804B0, 0x9804E0));

		DeclareAddress(ToWinProc, SelectAddress(0x97E760, 0x96FEB0, 0x96FEB0));
		DeclareAddress(GetNearPlane, SelectAddress(0x980800, 0x97E440, 0x97E440));
		DeclareAddress(SetNearPlane, SelectAddress(0x97E770, 0x9804D0, 0x980500));
	}
};
