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

#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\IWinProc.h>

#include <Spore\App\ICamera.h>

#include <EASTL\vector.h>
#include <EASTL\map.h>
#include <EASTL\string.h>

namespace GalaxyGameEntry
{
	//class UnknownGGEUIParent {
	//	virtual ~UnknownGGEUIParent() = 0;
	//};

	//// Although this class inherits from Object (via IWinProc) it's not refcounted;
	//// therefore, we cannot know when it will be deleted, so it's better not to use it (for example, don't use window->AddWinProc() with it)
	//class GlobalGGEUI : public UnknownGGEUIParent, public UTFWin::IWinProc
	//{
	//public:
	//	virtual ~GlobalGGEUI() = 0;

	//	char _padding_0[0x144];

	//	UTFWin::UILayout mainLayout;

	//	static GlobalGGEUI* GetGlobalGGEUI()
	//	{
	//		return *(GlobalGGEUI**)SelectAddress(0x16A55C4, 0x16A1344);
	//	}
	//};
	//PLACEHOLDER don't we need a Get method?

	struct Unknown
	{
		/* 00h */	eastl::map<int, int> field_0;
		/* 1Ch */	eastl::map<int, int> field_1C;
		/* 38h */	eastl::map<int, int> field_38;
		/* 54h */	eastl::map<int, int> field_54;
		/* 70h */	eastl::map<int, int> field_70;
	};
	ASSERT_SIZE(Unknown, 0x8C);

	namespace Addresses(GlobalGGEUI)
	{
		DeclareAddress(Initialize);
		DeclareAddress(InitializeUI);

		DeclareAddress(ptr);
	}

	class GlobalGGEUI
	{
	public:
		void Initialize();

		void InitializeUI();

	public:
#ifndef SDK_TO_GHIDRA
		static GlobalGGEUI* Get() {
			return *(GlobalGGEUI**)GetAddress(GlobalGGEUI, ptr);
		}
#endif

	public:
		enum Modes
		{
			kModeCreate = 2,

			kModeEdit = 5,

			kModeScenario = 0x0D,
		};
		//PLACEHOLDER wrong, where are the vftables??
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	eastl::vector<int, int> field_24;
		/* 38h */	int field_38;  // Sporepedia
		/* 3Ch */	Unknown field_3C;
		/* C8h */	bool field_C8;  // true
		/* C9h */	bool field_C9;
		/* CCh */	int field_CC;
		/* D0h */	eastl::string16 field_D0;
		/* E0h */	int field_E0;
		/* E4h */	bool field_E4;  // true
		/* E8h */	int field_E8;
		/* ECh */	bool field_EC;
		/* EDh */	bool field_ED;
		/* EEh */	bool field_EE;
		/* EFh */	bool field_EF;
		/* F0h */	int field_F0;
		/* F4h */	bool field_F4;
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	bool field_100;
		/* 101h */	bool field_101;
		/* 102h */	bool field_102;
		/* 103h */	bool field_103;  // true
		/* 104h */	bool field_104;
		/* 108h */	int field_108;
		/* 10Ch */	int field_10C;  // 8
		/* 110h */	eastl::vector<int, int> field_110;
		/* 124h */	eastl::map<int, int> field_124;
		/* 140h */	int field_140;  // not initialized
		/* 144h */	UTFWin::UILayout mZoomPanelLayout;
		/* 15Ch */	ObjectPtr field_15C;
		/* 160h */	ObjectPtr field_160;
		/* 164h */	ObjectPtr field_164;
		/* 168h */	ObjectPtr field_168;
		/* 16Ch */	ObjectPtr field_16C;
		/* 170h */	ObjectPtr field_170;
		/* 174h */	ObjectPtr field_174;
		/* 178h */	int field_178;
		/* 17Ch */	bool field_17C;
		/* 180h */	int field_180;
		/* 184h */	int field_184;
		/* 188h */	int field_188;
		/* 18Ch */	int field_18C;
		/* 190h */	int field_190;
		/* 194h */	float field_194;
		/* 198h */	ICameraPtr mpCamera;
		/* 19Ch */	ObjectPtr field_19C;
		/* 1A0h */	ObjectPtr field_1A0;
		/* 1A4h */	ObjectPtr field_1A4;
		/* 1A8h */	ObjectPtr field_1A8;
		/* 1ACh */	ObjectPtr field_1AC;
		/* 1B0h */	ObjectPtr field_1B0;
		/* 1B4h */	ObjectPtr field_1B4[9];
		/* 1D8h */	eastl::vector<int, int> field_1D8;
		/* 1ECh */	int field_1EC;
		/* 1F0h */	bool field_1F0;
		/* 1F1h */	bool field_1F1;
		char padding_1F2[2];
		/* 1F4h */	bool field_1F4;
		/* 1F5h */	bool field_1F5;
		/* 1F8h */	int field_1F8;
		/* 1FCh */	int field_1FC;
		char padding_200[0x4C];
		/* 24Ch */	bool field_24C;
		/* 24Dh */	bool field_24D;
		/* 250h	*/	int field_250;
		/* 254h */	eastl::map<int, int> field_254;
		/* 270h */	bool field_270;
		/* 271h */	bool mbScenarioStarEffectsEnabled;
	};

#ifdef SDK_TO_GHIDRA
	GlobalGGEUI* sGlobalGGEUI;
#endif
}
