/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\SimpleLayout.h>
#include <EASTL\internal\thread_support.h>

namespace UTFWin
{
	//////////////////////////////
	//// DefaultLayoutElement ////
	//////////////////////////////

	DefaultLayoutElement::DefaultLayoutElement()
		: mnRefCount(0)
	{}

	int DefaultLayoutElement::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}

	int DefaultLayoutElement::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			delete this;
		}
		return mnRefCount;
	}


	SimpleLayout::SimpleLayout()
		: mAnchor(kAnchorLeft | kAnchorTop)
	{
	}

	SimpleLayout::SimpleLayout(int anchor)
		: mAnchor(anchor)
	{
	}

	int SimpleLayout::GetEventFlags() const
	{
		return 0x108;
	}

	int SimpleLayout::GetAnchor() const
	{
		return mAnchor;
	}
	void SimpleLayout::SetAnchor(int value)
	{
		mAnchor = value;
	}

	IWinProc* SimpleLayout::ToWinProc() const
	{
		return (IWinProc*)this;
	}

	int SimpleLayout::AddRef()
	{
		return InteractiveWinProc::AddRef();
	}
	int SimpleLayout::Release()
	{
		return InteractiveWinProc::Release();
	}

	auto_METHOD_VIRTUAL_VOID(SimpleLayout, InteractiveWinProc, OnLayout,
		PARAMS(IWindow* window, Math::Rectangle& parentBounds), PARAMS(window, parentBounds));

	auto_METHOD_VIRTUAL_const(SimpleLayout, SimpleLayout, void*, Cast, PARAMS(uint32_t p), PARAMS(p));

	auto_METHOD_VIRTUAL_VOID(SimpleLayout, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(SimpleLayout, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SimpleLayout, ILayoutStyle, ApplyLayout, PARAMS(Math::Rectangle& dstBounds, const Math::Rectangle& parentBounds), PARAMS(dstBounds, parentBounds));
	auto_METHOD_VIRTUAL(SimpleLayout, ILayoutStyle, bool, RevertLayout, PARAMS(Math::Rectangle& dstBounds, const Math::Rectangle& parentBounds), PARAMS(dstBounds, parentBounds));

}