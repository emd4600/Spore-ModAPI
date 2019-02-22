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

#include <Spore\Transform.h>
#include <Spore\ResourceID.h>

#include <EASTL\intrusive_ptr.h>

namespace Swarm
{
	///
	/// An instance of an effect in the game. The effect can receive transformations.
	/// Use Show() to activate the instance and kill to destroy the effect.
	///
	class IEffect
	{
	public:
		virtual int AddRef() = 0;
		virtual int Release() = 0;

		/* 08h */	virtual void Show(int = 0);
		/* 0Ch */	virtual int Kill(int = 0);

		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual void func14h(const Transform&) = 0;
		/* 18h */	virtual void SetTransform(const Transform& transform) = 0;
		/* 1Ch */	virtual Transform func1Ch() const = 0;
		/* 20h */	virtual Transform GetTransform() const = 0;
		/* 24h */	virtual void func24h(int, int) = 0;
		/* 28h */	virtual int func28h(int) = 0;
		/* 2Ch */	virtual void func2Ch(bool) = 0;
		/* 30h */	virtual void func30h(bool) = 0;
		/* 34h */	virtual bool func34h() = 0;
		/* 38h */	virtual bool func38h() = 0;
		/* 3Ch */	virtual void SetSeed(int32_t seed) = 0;
		/* 40h */	virtual bool func40h(int, int, int) = 0;
		/* 44h */	virtual bool func44h(int, int, int) = 0;
		/* 48h */	virtual bool func48h(int, int, int) = 0;
		/* 4Ch */	virtual bool func4Ch(int, int) = 0;
		/* 50h */	virtual int func50h(int, int) = 0;
		/* 54h */	virtual int func54h(int, int) = 0;
		/* 58h */	virtual int func58h(int, int) = 0;
		/* 5Ch */	virtual int func5Ch(int) = 0;
		/* 60h */	virtual ResourceID GetName() = 0;
		/* 64h */	virtual void func64h(int, int) = 0;
	};
}