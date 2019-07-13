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
		DeclareAddress(Cast, SelectAddress(0x97EA40, 0x97E760, 0x97E760));

		DeclareAddress(SetSerializer, SelectAddress(0x97EC70, 0x97E990, 0x97E990));
		DeclareAddress(GetProxyID, SelectAddress(0x97EAA0, 0x97E7B0, 0x97E7B0));

		DeclareAddress(ApplyLayout, SelectAddress(0x97EB70, 0x97E890, 0x97E890));
		DeclareAddress(RevertLayout, SelectAddress(0x97EBE0, 0x97E900, 0x97E900));

		DeclareAddress(OnLayout, SelectAddress(0x97EAF0, 0x97E810, 0x97E810));
	}
}