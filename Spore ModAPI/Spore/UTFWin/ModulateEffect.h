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
	class IModulateEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get first and second modulation color.
		/// @param[Out] color1
		/// @param[Out] color2
		///
		/* 14h */	virtual void GetColors(Color& color1, Color& color2) const = 0;

		///
		/// Set first and second modulation color.
		/// @param color1
		/// @param color2
		///
		/* 18h */	virtual void SetColors(Color color1, Color color2) = 0;

		static const uint32_t TYPE = 0x8F8BBAD8;
	};

	class ModulateEffect : public BiStateEffect, public IModulateEffect
	{
	public:
		ModulateEffect();
		virtual ~ModulateEffect() {}

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual void GetColors(Color& color1, Color& color2) const override;
		/* 18h */	virtual void SetColors(Color color1, Color color2) override;

		virtual void func84h(int, float) override;

	protected:
		/* 64h */	Color mColor1;
		/* 68h */	Color mColor2;
		/* 6Ch */	int field_6C;  // not initialized

	};

	static_assert(sizeof(ModulateEffect) == 0x70, "sizeof(ModulateEffect) != 70h");

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(ModulateEffect)
	{
		DeclareAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0, 0x9633E0));
		DeclareAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0, 0x9636A0));

		DeclareAddress(SetSerializer, SelectAddress(0x9804D0, 0x9801D0, 0x980200));
		DeclareAddress(GetProxyID, SelectAddress(0x980410, 0x980110, 0x980140));

		DeclareAddress(func84h, SelectAddress(0x9803A0, 0x9800A0, 0x9800D0));

		DeclareAddress(ToWinProc, SelectAddress(0x980500, 0x980200, 0x980230));
		DeclareAddress(GetColors, SelectAddress(0x9803D0, 0x9800D0, 0x980100));
		DeclareAddress(SetColors, SelectAddress(0x9803F0, 0x9800F0, 0x980120));
	}
}