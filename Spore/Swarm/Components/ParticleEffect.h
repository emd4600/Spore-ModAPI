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

#include <Spore\MathUtils.h>
#include <Spore\Swarm\Components\IEffectComponent.h>
#include <Spore\Swarm\Components\TextureSlot.h>
#include <Spore\Swarm\Components\Wiggle.h>
#include <Spore\Swarm\Components\Surface.h>
#include <Spore\Swarm\Components\RandomWalk.h>
#include <Spore\Swarm\Components\Attractor.h>
#include <Spore\Swarm\Components\PathPoint.h>

#include <EASTL\vector.h>

using namespace eastl;
using namespace Math;

namespace Swarm
{
	namespace Components
	{

		class ParticleEffect : public IEffectComponent
		{
		public:
			ParticleEffect()
			{
				VOID_THISCALL(GetAddress(0xAA3780, 0, 0), this);
			}

			/* 08h */	int flags;
			/* 0Ch */	int unkFlags;
			/* 10h */	float life[2];
			/* 18h */	float prerollTime;
			/* 1Ch */	float emitDelay[2];
			/* 24h */	float emitRetrigger[2];
			/* 2Ch */	Vector3 emitDirectionBBMin;
			/* 38h */	Vector3 emitDirectionBBMax;
			/* 44h */	float emitSpeed[2];
			/* 4Ch */	Vector3 emitVolumeBBMin;
			/* 58h */	Vector3 emitVolumeBBMax;
			/* 64h */	float torusWidth;

			/* 68h */	vector<float> rate;
			/* 7Ch */	float rateLoop;
			/* 80h */	int rateCurveCycles;
			/* 84h */	float rateSpeedScale;

			/* 88h */	vector<float> size;
			/* 9Ch */	float sizeVary;

			/* A0h */	vector<float> aspectRatio;
			/* B4h */	float aspectRatioVary;

			/* B8h */	vector<float> rotation;
			/* CCh */	float rotationVary;
			/* D0h */	float rotationOffset;

			/* D4h */	vector<ColorRGB> color;
			/* E8h */	ColorRGB colorVary;

			/* F4h */	vector<float> alpha;
			/* 108h */	float alphaVary;

			int field_10C;

			/* 110h */	TextureSlot texture;
			/* 130h */	char physicsType;
			/* 131h */	char overrideSet;
			/* 132h */	char tileCount[2];
			/* 134h */	char alignMode;
			/* 135h */	char frameStart;
			/* 136h */	char frameCount;
			/* 137h */	char frameRandom;
			/* 138h */	float frameSpeed;

			/* 13Ch */	Vector3 directionalForcesSum;
			/* 148h */	float windStrength;
			/* 14Ch */	float gravityStrength;
			/* 150h */	float radialForce;
			/* 154h */	Vector3 radialForceLocation;
			/* 160h */	float drag;
			/* 164h */	float velocityStrength;
			/* 168h */	float screwRate;

			/* 16Ch */	vector<Wiggle> wiggles;

			/* 180h */	unsigned char screenBloomAlphaRate;
			/* 181h */	unsigned char screenBloomAlphaBase;
			/* 182h */	unsigned char screenBloomScaleRate;
			/* 183h */	unsigned char screenBloomScaleBase;

			/* 184h */	vector<ColorRGB> loopBoxColor;
			/* 198h */	vector<float> loopBoxAlpha;

			/* 1ACh */	vector<Surface> surfaces;

			/* 1C0h */	float mapBounce;
			/* 1C4h */	float mapRepulseHeight;
			/* 1C8h */	float mapRepulseStrength;
			/* 1CCh */	float mapRepulseScoutDistance;
			/* 1D0h */	float mapRepulseDistance;
			/* 1D4h */	float mapRepulseKillHeight;
			/* 1D8h */	float probabilityDeath;
			/* 1DCh */	float altitudeRange[2];

			int field_1E4;

			/* 1E8h */	ResourceID forceMapID;
			/* 1F0h */	ResourceID emitRateMapID;
			/* 1F8h */	ResourceID emitColorMap;

			/* 200h */	RandomWalk randomWalk;

			/* 234h */	Vector3 attractorOrigin;
			/* 240h */	Attractor attractor;

			/* 25Ch */	vector<PathPoint> pathPoints;
		};

		static_assert(sizeof(ParticleEffect) == 0x270, "sizeof(ParticleEffect) != 270h");
	}
}