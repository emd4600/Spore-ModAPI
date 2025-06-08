#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\UTFWin\SporeTooltipWinProc.h>
#include <SourceCode\Utility.h>

namespace UTFWin
{
	//// SporeTooltipWinProc ////

	SporeTooltipWinProc::SporeTooltipWinProc()
		: mLayoutName("Tooltips")
		, mControlID(0x3754E6C)
		, mDetailControlID(0x3754E6C)
		, mText()
		, mDetailedText()
		, mOffsetPosition(0, 30.0f)
		, field_4C()
		, mLocaleID()
		, mLayoutGroupID()
		, field_58()
		, mBehaviour(TooltipBehaviour::Default)
		, field_60()
		, field_64(-1)
	{
	}

	SporeTooltipWinProc::SporeTooltipWinProc(
		const char16_t* pLayoutName,
		uint32_t controlID,
		const char16_t* pText,
		const Math::Point& offsetPositon,
		TooltipBehaviour behaviour,
		const char16_t* pDetailedText,
		uint32_t detailControlID)

		: mLayoutName(pLayoutName)
		, mControlID(controlID)
		, mDetailControlID(detailControlID)
		, mText(pText)
		, mDetailedText(pDetailedText)
		, mOffsetPosition(offsetPositon)
		, field_4C()
		, mLocaleID()
		, mLayoutGroupID()
		, field_58()
		, mBehaviour(behaviour)
		, field_60()
		, field_64(-1)
	{
	}

	DEFAULT_REFCOUNT(SporeTooltipWinProc);

	auto_METHOD_VIRTUAL_VOID(SporeTooltipWinProc, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(SporeTooltipWinProc, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_const_(SporeTooltipWinProc, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(SporeTooltipWinProc, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	void* SporeTooltipWinProc::Cast(uint32_t type) const 
	{
		if (type == SporeTooltipWinProc::TYPE)
		{
			return (SporeTooltipWinProc*) this;
		}
		else
		{
			return InteractiveWinProc::Cast(type);
		}
	}
}
#endif
