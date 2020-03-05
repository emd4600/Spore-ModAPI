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
#include <Spore\Object.h>

#include <EASTL\intrusive_ptr.h>
#include <EASTL\utility.h>

#define IEffectPtr intrusive_ptr<Swarm::IEffect>

namespace Swarm
{
	/// An enum to represent the current state of an effect world and the Swarm manager.
	enum SwarmState
	{
		kStateActive = 0,
		kStatePaused = 1,
		kStateSuspended = 2,
		kStateHidden = 3,
		kStateManual = 4,
		kStateShutdown = 5,
	};

	///
	/// An instance of an effect in the game. The effect can receive transformations.
	/// Use Start() to activate the instance and Stop() to destroy the effect.
	///
	class IEffect
	{
	public:
		// <= 10
		enum IntParams
		{
			/// Set an override model. This requires two parameters: `int overrideSet` and `uint32_t name`
			kParamModelOverride = 0,
			/// Set an override texture. This requires two parameters: `int overrideSet` and `uint32_t name`
			kParamTextureOverride = 1,
			/// Select the given particle texture frame
			kParamSelectFrame = 2,
			/// Select the given effect state (Swarm::SwarmState)
			kParamSelectState = 3,
			/// Used in Distribute effects, expects a ResourceID*
			kParamDistID = 4,
			kParamDistUpdate = 5,
			kParamIntUser1 = 6,
			kParamIntUser2 = 7,
			kParamIntUser3 = 8,
			kParamIntUser4 = 9
		};

		enum FloatParams
		{
			kParamEmitStrength = 0,
			kParamParticleSizeScale = 1,
			kParamParticleLifeScale = 2,
			kParamEmitScale = 3,
			kParamTransparency = 4,
			/// Expects a ColorRGB
			kParamColor = 5,
			/// Expects a list of ColorRGBs
			kParamColorList = 6,
			/// Expects a Vector3
			kParamTargetPoint = 7,
			/// Expects a Vector3
			kParamExplosionLocation = 8,
			/// Expects a Vector3
			kParamAttractorLocation = 9,
			kParamAttractorIntensity = 10,
			/// Expects two Vector3s: position and direction
			kParamViewRay = 11,
			kParamEmissionVolume = 12,
			/// Expects a list of Vector3s
			kParamPath = 13,
			kParamShaderParams = 14,  // ?
			/// Controls the volume of sound effects
			kParamVolume = 15,
			/// Expects two floats
			kParamHeightRange = 16,
			kParamSubdivWindow = 17,
			kParamMapForceScale = 18,
			kParamLodDistanceScale = 19,
			kParamDistributeSizeScale = 20,
			kParamFloatUser1 = 21,
			kParamFloatUser2 = 22,
			kParamFloatUser3 = 23,
			kParamFloatUser4 = 24,

			// 0x101  BoundingBox
		};

		enum ObjectParams
		{

		};

		virtual int AddRef() = 0;
		virtual int Release() = 0;

		/* 08h */	virtual void Start(int hardStart = 1) = 0;
		/* 0Ch */	virtual int Stop(int hardStop = 1) = 0;

		/* 10h */	virtual int IsRunning() = 0;
		/* 14h */	virtual void func14h(const Transform&) = 0;
		/* 18h */	virtual void SetTransform(const Transform& transform) = 0;
		/* 1Ch */	virtual Transform func1Ch() const = 0;
		/* 20h */	virtual Transform GetTransform() const = 0;
		/* 24h */	virtual void func24h(int, int) = 0;
		/* 28h */	virtual int func28h(int) = 0;

		/// If true, pauses the effect; if false, it unpauses it.
		/// @param paused
		/* 2Ch */	virtual void SetPaused(bool paused) = 0;
		/* 30h */	virtual void SetHidden(bool hidden) = 0;
		/* 34h */	virtual bool IsPaused() = 0;
		/* 38h */	virtual bool IsHidden() = 0;
		/* 3Ch */	virtual void SetSeed(int32_t seed) = 0;
		/* 40h */	virtual bool SetVectorParams(FloatParams param, const Vector3* data, int count) = 0;
		/* 44h */	virtual bool SetFloatParams(FloatParams param, const float* data, int count) = 0;
		/* 48h */	virtual bool SetIntParams(IntParams param, const int* data, int count) = 0;
		/* 4Ch */	virtual bool SetObjectParam(ObjectParams param, Object* data) = 0;
		/* 50h */	virtual const Vector3& GetVectorParams(FloatParams param, int* dstCount = nullptr) = 0;
		/* 54h */	virtual const float* GetFloatParams(FloatParams params, int* dstCount = nullptr) = 0;
		/* 58h */	virtual const int* GetIntParams(IntParams param, int* dstCount = nullptr) = 0;
		/* 5Ch */	virtual Object* GetObjectParam(ObjectParams params) = 0;
		/* 60h */	virtual ResourceID GetName() = 0;
		/* 64h */	virtual void func64h(int, int) = 0;
	};
}