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

#include <Spore\MathUtils.h>
#include <Spore\Input.h>
#include <Spore\LocalizedString.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\UTFWin\UILayout.h>
#include <EASTL\string.h>

#define CellUI (*Simulator::Cell::cCellUI::Get())

namespace Simulator
{
	namespace Cell
	{
		struct cCellUIRollover : public cObjectPoolClass
		{
			/* 04h */	cObjectPoolIndex mCellIndex;
			/* 08h */	float field_8;
			/* 0Ch */	int field_C;
			/* 10h */	float field_10;
			/* 14h */	float field_14;
			/* 18h */	float field_18;
			/* 1Ch */	float field_1C;
			/* 20h */	float field_20;
			/// How many seconds until the rollover disappears
			/* 24h */	float mDisappearTime;
			/* 28h */	float field_28;
			/* 2Ch */	float field_2C;
			/* 30h */	bool field_30;
			/* 34h */	UTFWin::UILayout* mpLayout;
		};
		ASSERT_SIZE(cCellUIRollover, 0x38);

		class cCellUI
		{
		public:
			static cCellUI* Get();

			static void Load();

		public:
			/* 00h */	GameInput mGameInput;
			/* 48h */	Math::Vector3 field_48;  // not initialized, sub_E50E00
			/* 54h */	Math::Vector3 field_54;  // not initialized
			/* 60h */	Math::Vector3 field_60;  // not initialized
			/* 6Ch */	Math::Vector3 field_6C;  // not initialized
			/* 78h */	Math::Vector3 field_78;  // not initialized
			/* 84h */	float field_84;  // not initialized
			/* 88h */	int field_88;  // not initialized
			/* 8Ch */	int field_8C;  // not initialized
			/// `GlobalUICell-3.spui`
			/* 90h */	UILayoutPtr mpGlobalUILayout;
			/* 94h */	int field_94;
			/* 98h */	int field_98;
			/// 32 objects of type cCellUIRollover
			/* 9Ch */	cObjectPool<cCellUIRollover> mRollovers;
			/* B8h */	int field_B8;  // not initialized
			/* BCh */	float field_BC;  // not initialized
			/* C0h */	int field_C0;  // not initialized
			/* C4h */	int field_C4;  // not initialized
			/* C8h */	int field_C8;  // not initialized
			/* CCh */	Math::Vector3 field_CC;  // not initialized
			/* D8h */	float field_D8;  // not initialized
			/* DCh */	int field_DC;  // not initialized
			/* E0h */	int field_E0;  // not initialized
			/* E4h */	bool field_E4;  // not initialized
			/* E8h */	Math::Vector3 field_E8;  // not initialized
			/* F4h */	int field_F4;  // not initialized
			/* F8h */	int field_F8;  // not initialized
			/* FCh */	int field_FC;  // not initialized
			/* 100h */	char field_100[0x800];  // not initialized
			/* 900h */	int field_900;  // not initialized
			/* 904h */	int field_904;  // not initialized
			/* 908h */	int field_908;  // not initialized
			/* 90Ch */	int field_90C;  // not initialized
			/* 910h */	eastl::string16 mCurrentHoveredCellName;
			/* 920h */	LocalizedString field_920;
			/* 934h */	bool field_934[0x10];  // not initialized
		};
		ASSERT_SIZE(cCellUI, 0x944);

#ifdef SDK_TO_GHIDRA
		cCellUI* sCellUI;
#endif

		namespace Addresses(cCellUI)
		{
			DeclareAddress(_ptr);  // 0x16B7E8C 0x16B3C0C
			DeclareAddress(Load);  // 0xE548B0 0xE54270
		}
	}
}