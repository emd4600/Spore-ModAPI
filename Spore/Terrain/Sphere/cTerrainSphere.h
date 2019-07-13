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

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Graphics\IRenderable.h>
#include <EASTL\vector.h>

#include <Spore\Terrain\ITerrain.h>

using namespace eastl;
using namespace Math;

namespace Terrain
{
	// related with ambient occlusion??
	class unk_class_0x13F3628 {
		virtual void unk() = 0;
	};

	namespace Sphere
	{
		class cTerrainSphere
			: public ITerrain
			, public Graphics::IRenderable
			, public App::IMessageListener
			, public unk_class_0x13F3628
			, public Resource::ResourceObject
		{
		public:

			/* 08h */	virtual int func08h();
			/* 0Ch */	virtual cTerrainMapSet* GetTerrainMapSet();

		protected:
			/* 24h */	int field_24;
			/* 28h */	int field_28;
			/* 2Ch */	intrusive_ptr<cTerrainMapSet> mpTerrainMapSet;

			/* FCh */	int field_FC;
			/* 100h */	int field_100;
			/* 104h */	int field_104;
			/* 108h */	bool field_108;  // true
			/* 10Ch */	float field_10C;  // 5.0
			/* 110h */	bool field_110;
			/* 111h */	bool field_111;
			/* 114h */	int field_114;

			/* 148h */	int field_148;
			/* 14Ch */	int field_14C;
			/* 150h */	int field_150;
			/* 154h */	int field_154;
			/* 158h */	int field_158;
			/* 15Ch */	int field_15C;
			/* 160h */	int field_160;
			/* 164h */	int field_164;
			/* 168h */	int field_168;
			/* 16Ch */	int field_16C;
			/* 170h */	int field_170;
			/* 174h */	int field_174;
			/* 178h */	int field_178;
			/* 17Ch */	int field_17C;
			/* 180h */	int field_180;
			/* 184h */	int field_184;
			/* 188h */	int field_188;
			/* 18Ch */	int field_18C;
			// The item has a size of 16
			/* 190h	*/	vector<void*> field_190;
			/* 1A4h */	vector<int> field_1A4;
			/* 1B8h */	vector<int> field_1B8;
			/* 1CCh */	int field_1CC;
			/* 1D0h */	int field_1D0;  // 4
			/* 1D4h */	int field_1D4;  // 16
			/* 1D8h */	float field_1D8;  // 25.0
			/* 1DCh */	float field_1DC;  // 100.0
			/* 1E0h */	float field_1E0;  // 1.0
			/* 1E4h */	float field_1E4;  // 1.0
			/* 1E8h */	bool field_1E8;  // true
			/* 1ECh */	float field_1EC;  // 1.0
			/* 1F0h */	float field_1F0;  // 1.0
			/* 1F4h */	float field_1F4;  // 1.0
			/* 1F8h */	float field_1F8;  // 1.0
			/* 1FCh */	float field_1FC;  // 1.0
			/* 200h */	float field_200;  // 1.0
			/* 204h */	float field_204;  // 1.0
			/* 208h */	float field_208;  // 1.0
			/* 20Ch */	int field_20C;
			/* 210h */	int field_210;
			/* 214h */	int field_214;
			/* 218h */	vector<int> field_218;
			/* 22Ch */	vector<int> field_22C;
			/* 240h */	vector<int> field_240;
			/* 254h */	vector<int> field_254;
			/* 268h */	vector<int> field_268;
			/* 27Ch */	vector<int> field_27C;
			/* 290h */	vector<int> field_290;
			/* 2A4h */	vector<int> field_2A4;
			/* 2B8h */	vector<int> field_2B8;
			/* 2CCh */	vector<int> field_2CC;
			/* 2E0h */	vector<int> field_2E0;
			/* 2F4h */	vector<int> field_2F4;
			/* 308h */	int field_308;
			/* 30Ch */	Vector4 field_30C;
			/* 31Ch */	Vector4 field_31C;
			/* 32Ch */	Vector4 field_32C;
			/* 33Ch */	bool field_33C;
			/* 33Dh */	bool field_33D;
			/* 340h */	int field_340;
			/* 344h */	int field_344;
			/* 348h */	bool field_348;
			/* 34Ch */	float field_34C;  // 1.0
			/* 350h */	float field_350;  // 1.0
			/* 354h */	float field_354;  // 1.0
			/* 358h */	float field_358;  // 1.0
			/* 35Ch */	float field_35C;  // 1.0
			/* 360h */	float field_360;  // -1.0
			/* 364h */	float field_364;  // -1.0
			/* 368h */	int field_368;  // not initialized
			/* 36Ch */	int field_36C;
			/* 370h */	bool field_370;

			/* 4F4h */	bool field_4F4;
			/* 4F5h */	bool field_4F5;  // true

			/* 758h */	vector<int> field_758;
			/* 76Ch */	bool field_76C;
			/* 770h */	vector<int> field_770;
			/* 784h */	vector<int> field_784;
			/* 798h */	vector<int> field_798;
			/* 7ACh */	int field_7AC;
			/* 7B0h */	int field_7B0;

		public:
			static cTerrainSphere* Create();  //PLACEHOLDER method
		};

		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		static_assert(sizeof(cTerrainSphere) == 0xA50, "sizeof(cTerrainSphere) != A50h");

		namespace Addresses(cTerrainSphere)
		{
			DeclareAddress(Create, SelectAddress(0xFA29A0, NO_ADDRESS, 0xFA2350));
		}
	}
}