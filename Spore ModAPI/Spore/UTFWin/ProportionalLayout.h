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

#define ProportionalLayoutPtr eastl::intrusive_ptr<UTFWin::ProportionalLayout>

namespace UTFWin
{
	class ProportionalLayout 
		: public InteractiveWinProc
		, public ILayoutStyle
	{
	public:
		ProportionalLayout();
		ProportionalLayout(float left, float top, float right, float bottom);
		virtual ~ProportionalLayout() {}

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
	ASSERT_SIZE(ProportionalLayout, 0x20);

	namespace Addresses(ProportionalLayout)
	{
		DeclareAddress(Cast);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(ApplyLayout);
		DeclareAddress(RevertLayout);

		DeclareAddress(OnLayout);
	}
}