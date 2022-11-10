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

#include <EASTL\vector.h>

#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Swarm\IEffectsWorld.h>

namespace Simulator
{
	namespace Cell
	{
		class CellGFX
		{
		public:
			enum
			{
				kCellLightingWorldID = 0x4A4D97F,
				kCellPreloadedModelWorldID = 0x1010050,
				kCellPreloadedEffectWorldID = 0x1010051,
				kCellSkyboxEffectWorldID = 0x1010000,
				kCellBackgroundEffectWorldID = 0x1010011,
				kCellBackgroundModelWorldID = 0x1010010,
				kCellBeachEffectWorldID = 0x1010016,
				kCellBeachModelWorldID = 0x1010015,
				kCellEffectWorldID = 0x1010021,
				kCellModelWorldID = 0x1010020,
				kCellForegroundEffectWorldID = 0x1010031,
			};

		public:

			/* 00h */	eastl::vector<ModelPtr> mPreloadedModels;
			/* 14h */	eastl::vector<TexturePtr> mPreloadedTextures;
			/* 28h */	eastl::vector<int> field_28;
			/* 3Ch */	int field_3C;
			/* 40h */	int field_40;
			/* 44h */	int field_44;
			/* 48h */	int field_48;
			/* 4Ch */	int field_4C;  // not initialized
			/* 50h */	IEffectsWorldPtr mpPreloadedEffectWorld;
			/* 54h */	IModelWorldPtr mpPreloadedModelWorld;
			/* 58h */	int mpPreloadedAnimWorld;
			/* 5Ch */	int field_5C[0x40];
			/* 15Ch */	int field_15C;
			/* 160h */	int field_160;
			/* 164h */	int field_164;
			/* 168h */	char field_168[0x1C];  // not initialized
			/* 184h */	int field_184;
			/* 188h */	int field_188;
			/* 18Ch */	int field_18C;
			/* 190h */	int field_190;  // not initialized
			/* 194h */	int field_194;
			/* 198h */	int field_198;  // not initialized
			/* 19Ch */	char field_19C[0x16000];
			/* 1619Ch */	int field_1619C;  // not initialized
			/* 161A0h */	ILightingWorldPtr mpLightingWorld;
			/* 161A4h */	int field_161A4;
			/* 161A8h */	IModelWorldPtr mpBeachModelWorld;
			/* 161ACh */	IEffectsWorldPtr mpBeachEffectWorld;
			/* 161B0h */	int field_161B0;
			/* 161B4h */	IEffectsWorldPtr mpSkyboxEffectWorld;
			/* 161B8h */	int field_161B8;
			/* 161BCh */	IEffectsWorldPtr mpBackgroundEffectWorld;
			/* 161C0h */	IModelWorldPtr mpBackgroundModelWorld;
			/* 161C4h */	int mpBackgroundAnimWorld;
			/* 161C8h */	IEffectsWorldPtr mpEffectWorld;
			/* 161CCh */	IModelWorldPtr mpModelWorld;
			/* 161D0h */	int mpAnimWorld;
			/* 161D4h */	IEffectsWorldPtr mpForegroundEffectWorld;
			/* 161D8h */	int field_161D8;
			/* 161DCh */	int field_161DC;
			/* 161E0h */	int field_161E0;
			/* 161E4h */	int field_161E4;
			/* 161E8h */	char padding_161E8[0x74];  // not initialized
		};
		ASSERT_SIZE(CellGFX, 0x1625C);
	}
}
