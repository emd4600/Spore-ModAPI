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
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cVisiblePlanet.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSolarHitSphere.h>
#include <Spore\Simulator\cPlanetRecord.h>

#define cPlanetPtr intrusive_ptr<Simulator::cPlanet>

namespace Simulator
{
	class cSimPlanetLowLOD;  //TODO PLACEHOLDER
	class cEmpire;
	

	/// Visual representation of a planet (or asteroids). The information of a planet is stored in the 
	/// Simulator::cPlanetRecord class, but that class does not hold any visual information. Whenever a 
	/// planet must be viewed (in the solar system view in Space stage, or when you see planets in the sky
	/// while you are in a planet), this cPlanet class is used.
	/// You can use the Simulator::cStarManager::RecordToPlanet() method to generate a planet from a planet record.
	class cPlanet
		/* 00h */	: public cSpatialObject
		/* D4h */	, public cGameData
	{
	public:
		static const uint32_t TYPE = 0x3275872;
		static const uint32_t NOUN_ID = 0x3275728;

		using Object::AddRef;
		using Object::Release;

		/// Returns the temperature score of the planet record in the [0, 1] range or 0.5
		/// if there is no planet record
		float GetTemperatureScore() const;

		/// Returns the empire that controls this planet, if any.
		cEmpire* GetEmpire();

		/// Sets and enables the graphical representation of the planet. Depending on the type, this creates
		/// and sets visible the `mpSolarHitSphere` and the `mpVisiblePlanet`.
		/// @param mode
		void SetRepresentationMode(PlanetRepresentationMode mode);

	public:
		/* 108h */	int mNumSpecializedBehaviorUFOs;
		/* 10Ch */	Math::Matrix3 field_10C;
		/* 130h */	int field_130;
		/* 134h */	int field_134;
		/* 138h */	int field_138;
		/* 13Ch */	cPlanetRecordPtr mpPlanetRecord;
		/* 140h */	uint32_t mPlanetKey;  // not initialized
		/* 144h */	uint32_t mStarterWorldID;
		/* 148h */	Math::Vector3 mOrbitedPlanetLastKnownPosition;
		/* 154h */	intrusive_ptr<cSimPlanetLowLOD> mpPlanetSim;
		/* 158h */	PlanetRepresentationMode mGraphicRepresentationMode;
		/* 15Ch */	string16 mImpostorModel;
		/* 16Ch */	uint32_t mEffectScript;  // not initialized
		/* 170h */	vector<int> field_170;
		/* 184h */	float mPlanetScale;
		/* 188h */	cSolarHitSpherePtr mpSolarHitSphere;
		/* 18Ch */	cVisiblePlanetPtr mpVisiblePlanet;
		/* 190h */	bool field_190;  // true
		/* 198h */	cGonzagoTimer mTimeSinceLastColonyPlaced;
		/* 1B8h */	bool field_1B8;  // true
		/* 1BCh */	int mPlanetFlags;
		/* 1C0h */	cPlanetPtr mpParent;
		/* 1C4h */	uint32_t field_1C4;  // 0xFFD3D3D3
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cPlanet) == 0x1C8, "sizeof(cPlanet) != 1C8h");

	namespace Addresses(cPlanet) {
		DeclareAddress(GetTemperatureScore);
		DeclareAddress(SetRepresentationMode);
	}
}