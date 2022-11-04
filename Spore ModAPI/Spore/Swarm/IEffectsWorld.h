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

#include <EASTL\intrusive_ptr.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <Spore\Swarm\IVisualEffect.h>
#include <Spore\Swarm\cGlobalParams.h>

#define IEffectsWorldPtr eastl::intrusive_ptr<Swarm::IEffectsWorld>

namespace Swarm
{
	class IEffectsManager;

	struct cEffectInfo
	{
		/* 00h */	string field_0;
		/* 10h */	string field_10;
		/* 20h */	IVisualEffectPtr field_20;
	};
	ASSERT_SIZE(cEffectInfo, 0x24);

	/// An effects world is a space in the game which contains effects. The equivalent in models would be Graphics::IModelWorld.
	/// Effects in a certain world do not interact with effects of other worlds.
	class IEffectsWorld
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		/// Creates a new instance of an effect of the given name. The groupID is usually 0, so the first argument is the
		/// actual effect ID. An uninitialized intrusive_ptr to an IEffect must be given.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		/// @param[out] dst An uninitialized IVisualEffectPtr where the created instance will be put.
		/// @returns True if the method succeeded, false if the effect wasn't created.
		/* 08h */	virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffectPtr& dst) = 0;

		/// Sets the current state of the effect world.
		/// @param state
		/* 0Ch */	virtual void SetState(SwarmState state) = 0;

		/// Returns the current state of the effect world.
		/// @returns
		/* 10h */	virtual SwarmState GetState() = 0;

		// Probably distance and level?
		/* 14h */	virtual void SetLOD(float, int) = 0;

		/* 18h */	virtual void SetDefaultTimeline(int timelineType) = 0;

		/* 1Ch */	virtual void SetRenderer(void*) = 0;
		/* 20h */	virtual void* GetRenderer() = 0;

		/* 24h */	virtual void SetParamUpdateFlags(int) = 0;
		/* 28h */	virtual int GetParamUpdateFlags() = 0;

		/* 2Ch */	virtual cGlobalParams* GetGlobalParams() = 0;

		/* 30h */	virtual IEffectsManager* GetManager() = 0;

		/* 34h */	virtual void KillAllEffects() = 0;

		/* 38h */	virtual void KillOrphanedEffects() = 0;

		// last parameter is cComponentStats*
		/* 3Ch */	virtual void ManualUpdate(float, float, void*) = 0;

		/* 40h */	virtual void ResetState() = 0;

		/* 44h */	virtual void GetActiveEffectInfo(eastl::vector<cEffectInfo>& dst, const char* pPattern, int infoLevel) = 0;
		/* 48h */	virtual void ApplyToActiveEffects(void(*callback)(IVisualEffect*, void*), void*, int infoLevel) = 0;

		/* 4Ch */	virtual bool Initialize() = 0;
		/* 50h */	virtual bool Dispose() = 0;

		// last parameter is cComponentStats*
		/* 54h */	virtual void DoUpdate(float, float, void*) = 0;
	};
}