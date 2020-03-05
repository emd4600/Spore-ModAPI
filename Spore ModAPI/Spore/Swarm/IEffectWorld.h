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
#include <Spore\Swarm\IEffect.h>

#define IEffectWorldPtr intrusive_ptr<Swarm::IEffectWorld>

using namespace eastl;

namespace Swarm
{

	///
	/// An effect world is a space in the game which contains effects. The equivalent in models would be Graphics::IModelWorld.
	/// Effects in a certain world do not interact with effects of other worlds.
	///
	class IEffectWorld
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		///
		/// Creates a new instance of an effect of the given name. The groupID is usually 0, so the first argument is the
		/// actual effect ID. An uninitialized intrusive_ptr to an IEffect must be given.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		/// @param[out] dst An uninitialized intrusive_ptr<IEffect> where the created instance will be put.
		///
		/* 08h */	virtual bool CreateEffect(uint32_t instanceID, uint32_t groupID, intrusive_ptr<IEffect>& dst) = 0;
		/* 0Ch */	virtual void SetState(SwarmState state) = 0;

		///
		/// Returns the current state of the effect world.
		///
		/* 10h */	virtual SwarmState GetState() = 0;

		// Probably distance and level?
		/* 14h */	virtual void SetLOD(float, int) = 0;
		/* 18h */	virtual void func18h(int) = 0;
		/* 1Ch */	virtual void func1Ch(int) = 0;
		/* 20h */	virtual int func20h() = 0;
		/* 24h */	virtual void func24h(int) = 0;
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual int func2Ch() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual void func34h() = 0;
		/* 38h */	virtual void func38h() = 0;
		/* 3Ch */	virtual void func3Ch(float, float, int) = 0;
		/* 40h */	virtual void func40h() = 0;
		/* 44h */	virtual void func44h(int, int, int) = 0;
		/* 48h */	virtual void func48h(int, int, int) = 0;
		/* 4Ch */	virtual void func4Ch() = 0;
		/* 50h */	virtual bool func50h() = 0;
		/* 54h */	virtual void func54h(float, float, int) = 0;
	};
}