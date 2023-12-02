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

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\StarID.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <EASTL\hash_map.h>

#define cPlayerPtr eastl::intrusive_ptr<Simulator::cPlayer>

namespace Simulator
{
	class cPlayer
		/* 00h */	: public cGameData
		/* 34h */	, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x3C609F8;

	public:
		/* 38h */	char field_38[0x68C - 0x38];
		/* 68Ch */	int field_68C;
		/* 690h */	int field_690;
		/* 694h */	int field_694;
		/* 698h */	char field_698[0x10E8 - 0x698];
		///* 69Ch */	ResourceKey field_69C;  // a creature key?
		/* 10E8h */	ObjectPtr field_10E8;  // cCollectableItemsPtr
		/* 10ECh */	int field_10EC;  // not initialized
		/* 10F0h */	float field_10F0;
		/* 10F4h */	float field_10F4;  // not initialized
		/* 10F8h */	int field_10F8;
		/* 10FCh */	uint32_t mConsequenceTraitCell;
		/* 1100h */	uint32_t mConsequenceTraitCreature;
		/* 1104h */	uint32_t mConsequenceTraitTribe;
		/* 1108h */	uint32_t mConsequenceTraitCiv;
		/* 110Ch */	char field_110C[0x10];
		/* 111Ch */	eastl::hash_map<int, int> field_111C;
		/* 113Ch */	eastl::vector<int> field_113C;
		/* 1150h */	int field_1150;
		/* 1154h */	int field_1154;
		/* 1158h */	int field_1158;
		/* 115Ch */	int field_115C;
		/* 1160h */	int field_1160;
		/* 1164h */	int field_1164;
		/* 1168h */	int field_1168;
		/* 116Ch */	int field_116C;
		/* 1170h */	int field_1170;
		/* 1174h */	int field_1174;  // not initialized
		/* 1178h */	int field_1178;  // not initialized
		/* 117Ch */	int field_117C;  // not initialized
		/* 1180h */	int field_1180;  // not initialized
		/* 1184h */	eastl::vector<PlanetID> mVisitedPlanets;
		/* 1198h */	eastl::vector<int> field_1198;
		/* 11ACh */	eastl::vector<int> field_11AC;
		/* 11C0h */	eastl::vector<int> field_11C0;
		/* 11D4h */	char padding_11D4[0x1248 - 0x11D4];
		/* 1248h */	Difficulty mDifficulty;
		/* 124Ch */	char padding_124C[0x1258 - 0x124C];
		/* 1258h */	cGonzagoTimer field_1258;
		/* 1278h */	char padding_1278[0x12D8 - 0x1278];
	};
	ASSERT_SIZE(cPlayer, 0x12D8);
}