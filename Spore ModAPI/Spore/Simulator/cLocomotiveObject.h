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

#include <Spore\Simulator\cSpatialObject.h>
#include <EASTL\fixed_vector.h>

#define cLocomotiveObjectPtr eastl::intrusive_ptr<Simulator::cLocomotiveObject>

namespace Simulator
{
	struct cLocomotionRequest 
	{
		/* 00h */	eastl::vector<int> field_00;
		/* 14h */	Vector3 dstPos;
		/* 20h */	float goalStopDistance;
		/* 24h */	int field_24;

		/* 50h */	Vector3 field_50;
		/* 5Ch */	int field_5C;  // 3
		/* 60h */	float acceptableStopDistance;
		/* 64h */	float field_64;  // 0.99
		/* 68h */	float field_68;  // FLT_MAX
		/* 6Ch */	float field_6C;  // 0.0
		/* 70h */	int field_70;

		///* 60h */	Vector4 orientation;

	};

	class cLocomotiveObject_superclass {
	public:
		virtual ~cLocomotiveObject_superclass();
		virtual void func04h(bool);

		int field_4;
	};

	class cLocomotiveObject
		: public cSpatialObject
		, cLocomotiveObject_superclass
	{
	public:
		static const uint32_t TYPE = 0x116DD1B;

		//PLACEHOLDER vftable, might contain interesting movement methods

		/* C4h */	virtual void SetDesiredSpeed(float speed, int);
		/* C8h */	virtual float GetDesiredSpeed() const;
		/* CCh */	virtual float GetStandardSpeed() const;
		// returns mStandardSpeed * ?? + creatureBaseAcceleration;
		/* D0h */	virtual float funcD0h() const;
		/* D4h */	virtual float funcD4h() const;
		// related with species profile?
		/* D8h */	virtual float funcD8h() const;
		/* DCh */	virtual void funcDCh(int);  // some kind of movement request? sets mInTransitTime = 0
		// the bool might be "relative" position?
		/* E0h */	virtual void MoveTo(const Vector3& dst, float goalStopDistance = 1.0f, float acceptableStopDistance = 2.0f, bool=false);
		/* E4h */	virtual void funcE4h(const Vector3&, int);
		/* E8h */	virtual void funcE8h(const Vector3&, float, float);
		/* ECh */	virtual void StopMovement();
		/* F0h */	virtual void funcF0h();  // find neighbours?
		/* F4h */	virtual void ClearNeighbours();
		/* F8h */	virtual bool funcF8h();  // related with idle animation

		Vector3 GetVelocity();
		void SetVelocity(const Vector3& velocity);

	public:
		/* DCh */	eastl::vector<int> field_DC;
		/* F0h */	eastl::fixed_vector<float, 32> field_F0;
		/* 188h */	float field_188;
		/* 18Ch */	float field_18C;
		/* 190h */	Vector3 field_190;
		/* 19Ch */	bool field_19C;
		/* 1A0h */	float mInTransitTime;
		/* 1A4h */	int field_1A4;
		/* 1A8h */	Vector3 field_1A8;
		/* 1B4h */	Vector3 field_1B4;
		/* 1C0h */	float field_1C0;
		/* 1C4h */	float field_1C4;
		/* 1C8h */	Vector3 mVelocity;
		/* 1D4h */	Vector3 mAngularVelocity;
		/* 1E0h */	float mDesiredSpeed;
		/* 1E4h */	float mStandardSpeed;  // 1.0
		/* 1E8h */	float mTurnRate;  // PI
		/* 1ECh	*/	float mAngleVelocity;
		/* 1F0h */	int mPlanetCorrection;  // 1
		// This is some kind of struct for movement requests?
		// size 74h, movement request
		/* 1F4h */	eastl::vector<int> field_1F4;
		/* 208h */	Vector3 field_208;
		/* 214h */	float field_214;  // 1.0
		/* 218h */	int field_218;
		/* 21Ch */	Matrix3 field_21C;
		/* 240h */	bool field_240;
		/* 244h */	float field_244;
		/* 248h */	float field_248;
		/* 24Ch */	float field_24C;
		/* 250h */	int field_250;
		/* 254h */	float field_254;  // 2.0
		/* 258h */	float field_258;  // 0.9
		/* 25Ch */	float field_25C;  // FLOAT_MAX
		/* 260h */	float field_260;
		/* 264h */	int field_264;
		/* 268h */	bool mbSelfPowered;  // true
		/* 26Ch */	float mNeighborCheckRadius;  // 20.0
		/* 270h */	int field_270;
		/* 274h */	bool field_274;
		/* 278h */	eastl::fixed_vector<cSpatialObjectPtr, 128> mNeighbors;
		/* 490h */	eastl::fixed_vector<int, 4> field_490;
		/* 4B8h */	eastl::vector<int> field_4B8;
		/* 4CCh */	int field_4CC;  //PLACEHOLDER important cLomotionStrategy
	};
	ASSERT_SIZE(cLocomotiveObject, 0x4D0);
}