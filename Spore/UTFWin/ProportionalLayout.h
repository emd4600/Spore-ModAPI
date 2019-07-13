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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\InteractiveWinProc.h>
#include <Spore\UTFWin\ILayoutStyle.h>

namespace UTFWin
{
	class ProportionalLayout 
		: public InteractiveWinProc
		, public ILayoutStyle
	{
	public:
		ProportionalLayout();
		virtual ~ProportionalLayout() {}

		static inline ProportionalLayout* New() {
			// __stdcall because it's cleanup by callee
			return ((ProportionalLayout*(__stdcall*)(void*, void*)) SelectAddress(0x97EDE0, 0x97EB00, 0x97EB00))(nullptr, nullptr);
		}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;
		virtual int GetEventFlags() const override;

		virtual void OnLayout(IWindow* window, Math::Rectangle& parentBounds) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual IWinProc* ToWinProc() const override;
		virtual void ApplyLayout(Math::Rectangle& area, const Math::Rectangle& parentArea) override;
		virtual bool RevertLayout(Math::Rectangle& area, const Math::Rectangle& parentArea) override;

		virtual const float* GetProportions() const;
		virtual void SetProportions(float values[4]);

	protected:
		// The relative origin of each edge, as a fraction of parent
		/* 10h */	float mProportions[4];

	};

	static_assert(sizeof(ProportionalLayout) == 0x20, "sizeof(ProportionalLayout) != 20h");

	namespace Addresses(ProportionalLayout)
	{
		DeclareAddress(Cast, SelectAddress(0x97EA40, 0x97E760, 0x97E760));

		DeclareAddress(SetSerializer, SelectAddress(0x97EDB0, 0x97EAD0, 0x97EAD0));
		DeclareAddress(GetProxyID, SelectAddress(0x97EAB0, 0x97E7D0, 0x97E7D0));

		DeclareAddress(ApplyLayout, SelectAddress(0x97ECC0, 0x97E9E0, 0x97E9E0));
		DeclareAddress(RevertLayout, SelectAddress(0x97ED30, 0x97EA50, 0x97EA50));

		DeclareAddress(OnLayout, SelectAddress(0x97EAF0, 0x97E810, 0x97E810));
	}
}