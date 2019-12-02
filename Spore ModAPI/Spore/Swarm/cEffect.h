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

#include <Spore\Swarm\Components\VisualEffect.h>
#include <Spore\ResourceID.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>

#include <EASTL\intrusive_ptr.h>

using namespace eastl;
using namespace Math;

namespace Swarm
{
	class ISwarmManager;

	class cEffect
	{
	public:

		virtual int AddRef();
		virtual int Release();

		/* 08h */	virtual void Show(int = 0);
		/* 0Ch */	virtual int Hide(int = 0);

		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual int func14h() = 0;
		/* 18h */	virtual void SetTransform(Transform& transform) = 0;
		/* 1Ch */	virtual int func1Ch() = 0;
		/* 20h */	virtual Transform GetTransform() const = 0;
		/* 24h */	virtual int func24h() = 0;
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual int func2Ch() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual int func34h() = 0;
		/* 38h */	virtual int func38h() = 0;
		/* 3Ch */	virtual void SetSeed(int32_t seed) = 0;
		/* 40h */	virtual int func40h() = 0;
		/* 44h */	virtual int func44h() = 0;
		/* 48h */	virtual int func48h() = 0;
		/* 4Ch */	virtual int func4Ch() = 0;
		/* 50h */	virtual int func50h() = 0;
		/* 54h */	virtual int func54h() = 0;
		/* 58h */	virtual int func58h() = 0;
		/* 5Ch */	virtual int func5Ch() = 0;
		/* 60h */	virtual ResourceID GetName() = 0;
		/* 64h */	virtual void func64h() = 0;

		// my own addition
		void GetIndex(size_t& dstDirectoryIndex, size_t& dstEffectIndex) const;

		Components::VisualEffect* GetVisualEffect();

	protected:
		enum
		{
			kFlagTransformed = 4
		};

		int vftable_04h;
		int vftable_08h;
		int field_0Ch;

		/* 10h */	int mnRefCount;
		/* 14h */	intrusive_ptr<ISwarmManager> mpManager;
		/* 18h */	uint32_t mnInstanceID;
		/* 1Ch */	uint32_t mnGroupID;
		/* 20h */	uint32_t mnEffectIndex;  // & 0xFF000000 is the EffectDirectory index
		/* 24h */	int field_24;
		/* 28h */	Components::VisualEffect* mpVisualEffect;
		/* 2Ch */	int mnFlags;
		/* 30h */	Vector3 field_30;
		/* 3Ch */	Vector3 field_3C;
		/* 48h */	int field_48;
		/* 4Ch */	float field_4C;
		/* 50h */	Vector3 field_50;
		/* 5Ch */	uint32_t mNotifyMessageID;
		/* 60h */	int field_60;
		/* 64h */	Transform field_64;
		/* 9Ch */	Transform mTransform;
		/* D4h */	Transform field_D4;
		/* 10Ch */	Transform field_10C;
		/* 144h */	vector<int> field_144;
		/* 158h */	int field_158;
		/* 15Ch */	int field_15C;
		/* 160h */	int field_160;
		/* 164h */	int field_164;
		/* 168h */	float field_168;
		/* 16Ch */	float field_16C;
		/* 170h */	float field_170;
		/* 174h */	int field_174;
		/* 178h */	int field_178;
		/* 17Ch */	int field_17C;
		/* 180h */	int32_t mnSeed;
		/* 184h */	int field_184;  // not initialized
	};


	inline void cEffect::GetIndex(size_t& dstDirectoryIndex, size_t& dstEffectIndex) const
	{
		dstDirectoryIndex = mnEffectIndex >> 24;
		dstEffectIndex = mnEffectIndex & 0x00FFFFFF;
	}

	inline Components::VisualEffect* cEffect::GetVisualEffect()
	{
		return mpVisualEffect;
	}
}
