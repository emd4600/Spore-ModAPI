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
#include <Spore\Swarm\cSurfaceInfo.h>
#include <Spore\Swarm\Components\cDescription.h>
#include <Spore\Swarm\Components\TextureSlot.h>
#include <Spore\Swarm\Components\Wiggle.h>
#include <Spore\Swarm\Components\RandomWalk.h>
#include <Spore\Swarm\Components\Attractor.h>
#include <Spore\Swarm\Components\PathPoint.h>

#include <EASTL\vector.h>

namespace Swarm
{
	namespace Components
	{
		class ParticleEffect
			: public cDescription
		{
		public:
			/* 08h */	int flags;
			/* 0Ch */	int unkFlags;
			/* 10h */	float life[2];
			/* 18h */	float prerollTime;
			/* 1Ch */	float emitDelay[2];
			/* 24h */	float emitRetrigger[2];
			/* 2Ch */	Math::Vector3 emitDirectionBBMin;
			/* 38h */	Math::Vector3 emitDirectionBBMax;
			/* 44h */	float emitSpeed[2];
			/* 4Ch */	Math::Vector3 emitVolumeBBMin;
			/* 58h */	Math::Vector3 emitVolumeBBMax;
			/* 64h */	float torusWidth;
			/* 68h */	eastl::vector<float> rate;
			/* 7Ch */	float rateLoop;
			/* 80h */	int rateCurveCycles;
			/* 84h */	float rateSpeedScale;
			/* 88h */	eastl::vector<float> size;
			/* 9Ch */	float sizeVary;
			/* A0h */	eastl::vector<float> aspectRatio;
			/* B4h */	float aspectRatioVary;
			/* B8h */	eastl::vector<float> rotation;
			/* CCh */	float rotationVary;
			/* D0h */	float rotationOffset;
			/* D4h */	eastl::vector<Math::ColorRGB> color;
			/* E8h */	Math::ColorRGB colorVary;
			/* F4h */	eastl::vector<float> alpha;
			/* 108h */	float alphaVary;
			/* 10Ch */	int field_10C;
			/* 110h */	TextureSlot texture;
			/* 130h */	char physicsType;
			/* 131h */	char overrideSet;
			/* 132h */	char tileCount[2];
			/* 134h */	char alignMode;
			/* 135h */	char frameStart;
			/* 136h */	char frameCount;
			/* 137h */	char frameRandom;
			/* 138h */	float frameSpeed;
			/* 13Ch */	Math::Vector3 directionalForcesSum;
			/* 148h */	float windStrength;
			/* 14Ch */	float gravityStrength;
			/* 150h */	float radialForce;
			/* 154h */	Math::Vector3 radialForceLocation;
			/* 160h */	float drag;
			/* 164h */	float velocityStrength;
			/* 168h */	float screwRate;
			/* 16Ch */	eastl::vector<Wiggle> wiggles;
			/* 180h */	uint8_t screenBloomAlphaRate;
			/* 181h */	uint8_t screenBloomAlphaBase;
			/* 182h */	uint8_t screenBloomScaleRate;
			/* 183h */	uint8_t screenBloomScaleBase;
			/* 184h */	eastl::vector<Math::ColorRGB> loopBoxColor;
			/* 198h */	eastl::vector<float> loopBoxAlpha;
			/* 1ACh */	eastl::vector<cSurfaceInfo> surfaces;
			/* 1C0h */	float mapBounce;
			/* 1C4h */	float mapRepulseHeight;
			/* 1C8h */	float mapRepulseStrength;
			/* 1CCh */	float mapRepulseScoutDistance;
			/* 1D0h */	float mapRepulseDistance;
			/* 1D4h */	float mapRepulseKillHeight;
			/* 1D8h */	float probabilityDeath;
			/* 1DCh */	float altitudeRange[2];
			/* 1E4h */	int field_1E4;
			/* 1E8h */	ResourceID forceMapID;
			/* 1F0h */	ResourceID emitRateMapID;
			/* 1F8h */	ResourceID emitColorMap;
			/* 200h */	RandomWalk randomWalk;
			/* 234h */	Math::Vector3 attractorOrigin;
			/* 240h */	Attractor attractor;
			/* 25Ch */	eastl::vector<PathPoint> pathPoints;
		};
		ASSERT_SIZE(ParticleEffect, 0x270);
	}
}