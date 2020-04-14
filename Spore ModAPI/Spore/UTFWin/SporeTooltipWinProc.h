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

#include <Spore\UTFWin\InteractiveWinProc.h>
#include <Spore\UTFWin\ILayoutElement.h>
#include <EASTL\string.h>

#define SporeTooltipWinProcPtr intrusive_ptr<UTFWin::SporeTooltipWinProc>

namespace UTFWin
{
	using namespace eastl;

	enum class TooltipBehaviour : uint32_t
	{
		Default = 0,
		UnderWindow = 1,
		Offset = 2,
	};

	class SporeTooltipWinProc : public InteractiveWinProc
	{
	public:
		static const uint32_t TYPE = 0x3796CE5;

		SporeTooltipWinProc();
		SporeTooltipWinProc(
			const char16_t* pLayoutName,
			uint32_t controlID,
			const char16_t* pText,
			const Math::Point& offsetPositon, 
			TooltipBehaviour behaviour,
			const char16_t* pDetailedText,
			uint32_t detailControlID);

		virtual ~SporeTooltipWinProc() {};

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;


	public:
		/// Filename of the layout which contains tooltip window, by default "Tooltips".
		/* 0Ch */	string16 mLayoutName;
		/// Control ID of tooltip window, by default 0x3754E6C.
		/* 1Ch */	uint32_t mControlID;  // 0x3754E6C
		/// Control ID of detailed tooltip window, by default 0x3754E6C.
		/* 20h */	uint32_t mDetailControlID;  // 0x3754E6C
		/// Text to display in tooltip.
		/* 24h */	string16 mText;
		/// Detailed text to display in tooltip after extended hover.
		/* 34h */	string16 mDetailedText;
		/// The offset of the tooltip window relative to the cursor, by default (0, 30).
		/* 44h */	Math::Point mOffsetPosition;  // (0, 30)
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	bool field_58;
		/// Sets the tooltip display behavior.
		/* 5Ch */	TooltipBehaviour mBehaviour;
		/* 60h */	int field_60;
		/* 64h */	int field_64;  // -1
	};

	typedef SporeTooltipWinProc Tooltip;

	///
	/// Creates an instance of the Tooltip class that can be used to display the given text as a tooltip.
	/// Tooltips are window procedures, so you can add it to a window with IWindow::AddWinProc().
	/// @param pText The text the tooltip displays.
	/// @param pDetailedText [Optional] The detailed text showed when the mouse has been a while hovering.
	/// @param pLayoutName [Optional] The name of the UI layout used in the tooltip.
	/// @param controlID [Optional] The ControlID of the window in the layout that will display the text.
	/// @param detailControlID [Optional] The ControlID of the window in the layout that will display the detailed text.
	///
	inline Tooltip* CreateTooltip(
		const char16_t* pText,
		const char16_t* pDetailedText = nullptr,
		const char16_t* pLayoutName = u"tooltips",
		uint32_t controlID = 0x3754E6C,
		uint32_t detailControlID = 0x3754E6C
		)
	{
		return new SporeTooltipWinProc(pLayoutName, controlID, pText, Math::Point(0, 30.0f), TooltipBehaviour::Default,
			pDetailedText, detailControlID);
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(SporeTooltipWinProc) == 0x68, "sizeof(SporeTooltipWinProc) != 68h");

	namespace Addresses(SporeTooltipWinProc)
	{
		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
	}
}