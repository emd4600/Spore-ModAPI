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

#include <Spore\Swarm\IEffectsManager.h>
#include <Spore\Swarm\EffectDirectory.h>
#include <Spore\Object.h>
#include <Spore\Clock.h>
#include <Spore\MathUtils.h>

#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\hash_map.h>

namespace Swarm
{
	class cEffectsManager 
		: public IEffectsManager
		, public IVirtual
	{
	protected:
		///
		/// Returns an integer that contains both the index to the EffectDirectory that contains the wanted effect as 
		/// well as the index to the effect inside that directory.
		///
		/// The returned integer uses the following structure: 0xXXYYYYYY, where XX is the index to the directory and
		/// YYYYYY the index to the effect.
		///
		int GetDirectoryAndEffectIndex(uint32_t instanceID, uint32_t groupID);

	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	bool field_0C;
		/* 10h */	Clock field_10;
		/* 28h */	float mfSimMS;
		/* 2Ch */	eastl::vector<EffectDirectoryPtr> mDirectories;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	float field_50;
		/* 54h */	int field_54;
		/* 58h */	float field_58;
		/* 5Ch */	float field_5C;
		/* 60h */	float field_60;
		/* 64h */	float field_64;
		/* 68h */	int mAppFlags;
		/* 6Ch */	int field_6C;
		/* 70h */	int field_70;
		/* 74h */	int8_t field_74[0x4C];
		/* C0h */	eastl::string field_C0;
		/* D0h */	cGlobalParams field_D0;
		/* 1F0h */	int field_1F0;
		/* 1F4h */	int field_1F4;
		/* 1F8h */	int field_1F8;
		/* 1FCh */	int field_1FC;
		/* 200h */	int field_200;
		/* 204h */	int field_204;
		/* 208h */	int field_208;
		/* 20Ch */	int field_20C;
		/* 210h */	int field_210;
		/* 214h */	int field_214;
		/* 218h */	int field_218;
		/* 21Ch */	int field_21C;
		/* 220h */	int field_220;
		/* 224h */	eastl::hash_map<uint32_t, IEffectsWorldPtr> mWorlds;
		/* 244h */	IEffectsWorldPtr mpActiveWorld;
		/* 248h */	eastl::string field_248;

		// 74h	int mnLive;
		// 78h	int mnRun;
		// 7Ch	int mnCmpts;

		// 94h	int mnModels;
		// 98h	int mnMetaParticles;
		// 9Ch	int mnDecals;
		// A0h	int mnSounds;
		// /* A4h */	int mnRibbons;

		// D0h	float mfDensity;

		// 148h	 bool mbNoAlpha;

		// 1E0h bool mbShowBounds;
		// 1E1h	bool mbShowSurfaces;
		// 1E2h	bool mbShowEffects;  // Show effect locations		
	};
	ASSERT_SIZE(cEffectsManager, 0x258);

	namespace Addresses(cSwarmManager)
	{
		DeclareAddress(GetDirectoryAndEffectIndex);
	}
	namespace Addresses(cEffectsManager)
	{
		DeclareAddress(GetDirectoryAndEffectIndex);
	}
}