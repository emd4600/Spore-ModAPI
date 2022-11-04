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

#include <Spore\Swarm\IVisualEffect.h>
#include <Spore\Swarm\cSurfaceInfo.h>

namespace Swarm
{
	class ISurface
	{
	public:
		/* 00h */	virtual int Release() = 0;
		/* 04h */	virtual int AddRef() = 0;

		/* 08h */	virtual bool ApplySurface(float, const Vector3&, Vector3&, Vector3&, void*, void*) = 0;

		/* 0Ch */	virtual float DistanceFromSurface(const Vector3& srcPoint, void*, void*) = 0;

		// second-to-last parameter is Transform*?
		/* 10h */	virtual bool FindClosestSurfacePoint(const Vector3& srcPoint, Vector3&, Vector3*, Quaternion*, void*, void*) = 0;

		/* 14h */	virtual bool MovePointAlongSurface(const Vector3& srcPoint, Vector3&, Vector3*, Quaternion*, void*, void*) = 0;

		/* 18h */	virtual void func18h(int, int, int) = 0;

		/* 1Ch */	virtual int NumStateBytes() = 0;
		/* 20h */	virtual void InitStateData(cSurfaceInfo* surfaceInfo, const Transform&, const Transform&, void* data) = 0;
		/* 24h */	virtual void ReleaseStateData(void*) = 0;

		/* 28h */	virtual int NumParticleBytes() = 0;
		/* 2Ch */	virtual void InitParticleData(cSurfaceInfo* surfaceInfo, void* data, IVisualEffect* effect) = 0;
		/* 30h */	virtual void ReleaseParticleData(void*) = 0;
	};
}