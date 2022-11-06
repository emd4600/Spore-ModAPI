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
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\ILayoutStyle.h>

#define SimpleLayoutPtr eastl::intrusive_ptr<UTFWin::SimpleLayout>

namespace UTFWin
{

	enum LayoutAnchor
	{
		kAnchorTop = 1,
		kAnchorBottom = 2,
		kAnchorLeft = 4,
		kAnchorRight = 8
	};

	class SimpleLayout
		: public InteractiveWinProc
		, public ILayoutStyle
	{
	public:
		SimpleLayout();
		SimpleLayout(int anchor);
		virtual ~SimpleLayout() {};

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

		virtual int GetAnchor() const;
		virtual void SetAnchor(int value);

	protected:
		int mAnchor;
	};

	static_assert(sizeof(SimpleLayout) == 0x14, "sizeof(SimpleLayout) != 14h");

	namespace Addresses(SimpleLayout)
	{
		DeclareAddress(Cast);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(ApplyLayout);
		DeclareAddress(RevertLayout);

		DeclareAddress(OnLayout);
	}
}