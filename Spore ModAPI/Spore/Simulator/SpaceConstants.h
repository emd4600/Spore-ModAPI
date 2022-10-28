#pragma once

#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Internal.h>

namespace Simulator
{
	/// Used to obtain the individual star types of each of the two stars in a binary system.
	/// @param binaryType Type of the system, which should be a binary system.
	/// @param[out] star1 Type of the first star.
	/// @param[out] star2 Type of the second star.
	void GetBinarySystemStarTypes(StarType binaryType, StarType& star1, StarType& star2);

	/// Returns the radius that is used as a base for calculating planet orbits in a binary-star system.
	/// It calculates it by predicting how the two stars should orbit around one another, depending on
	/// their mass and radius calculated using GetSolarStarRadius() and GetSolarStarMass()
	float GetBinarySystemBaseRadius(StarType binaryType);

	/// Returns the solar temperature for a given star type. 
	/// - For star types that are not stars (e.g. black holes, planetary disks, etc) it returns 1. 
	///	- For binary systems, it is the sum of the temperature of each of the stars.
	/// - For red, yellow and blue stars, it returns the `solarStarTemperature` property of their property list.
	/// @param starType
	/// @returns
	float GetSolarStarTemperature(StarType starType);

	/// Returns the stellar mass for a given star type, in solar mass units (1.0 is the mass of the Sun, 2.0 is twice
	/// as massive as the Sun, etc). 
	/// - For the galactic core, it returns 300.
	/// - For black holes and proto-planteray disks, it returns 100.
	/// - For binary systems, it is the sum of the stellar mass of each of the stars.
	/// - For red, yellow and blue stars, it returns the `solarStarMass` property of their property list.
	/// @param starType
	/// @returns
	float GetSolarStarMass(StarType starType);

	/// Returns the radius for a given star type.
	/// - For black holes and the galactic core, it returns 100.
	/// - For proto-planteray disks, it returns 1.
	/// - For binary systems, it is the sum of the radius of each of the stars.
	/// - For red, yellow and blue stars, it returns the `solarStarRadius` property of their property list.
	/// @param starType
	/// @returns
	float GetSolarStarRadius(StarType starType);

	/// Returns the rotation rate for a given star type, only used for individual stars.
	/// The returned value is an angle in radius, probably the angular change per second.
	/// For red, yellow and blue stars it returns the `solarStarRotationRate` property of their property list
	/// (converted to radians, the property is in degrees), for all the rest it returns 0.1
	float GetSolarStarRotationRate(StarType starType);

	/// Returns the distance from the center of the solar system for cold, normal and hot orbits.
	/// First, a base radius is calculated, using GetBinarySystemBaseRadius() and GetSolarStarRadius().
	/// - Hot orbits are `baseRadius + 15`
	/// - Normal orbits are `baseRadius * 85`
	/// - Cold orbits are `baseRadius * 195`
	/// @param starType
	/// @param orbitTemperature
	/// @returns
	float GetSolarStarOrbitRadius(StarType starType, SolarSystemOrbitTemperature orbitTemperature);

	/// Returns the type of temperature (very cold, cold, normal, hot, very hot) of a planet.
	/// @param temperatureScore The temperature score of the planet, from 0.0 (cold) to 1.0 (hot).
	/// @returns
	PlanetTemperatureType GetPlanetTemperatureType(float temperatureScore);

	/// Returns true if the given star type is a binary star, false otherwise.
	/// @param starType
	/// @returns
	bool IsBinaryStar(StarType starType);

	/// Returns true if the given star is not a single star or binary star system, false otherwise.
	/// @param starType
	/// @returns
	bool IsNotStarOrBinaryStar(StarType starType);

	float* GetPrecalculatedSolarStarRadius();
}

namespace Addresses(Simulator)
{
	DeclareAddress(GetBinarySystemStarTypes);  // 0xC8A790 0xC8B600
	DeclareAddress(GetBinarySystemBaseRadius);  // 0xC83720 0xC845B0
	DeclareAddress(GetSolarStarTemperature);  // 0xC83610 0xC844A0
	DeclareAddress(GetSolarStarMass);  // 0xC834A0 0xC84330
	DeclareAddress(GetSolarStarRadius);  // 0xC83420 0xC842B0
	DeclareAddress(GetSolarStarRotationRate);  // 0xC835A0 0xC84430
	DeclareAddress(GetSolarStarOrbitRadius);  // 0xC83F60 0xC84DF0
	DeclareAddress(GetPlanetTemperatureType);  // 0xFC26B0 0xFC1F90
	DeclareAddress(IsBinaryStar);  // 0xC8A770 0xC8B5E0
	DeclareAddress(IsNotStarOrBinaryStar);  // 0xC8A840 0xC8B6B0
	DeclareAddress(PrecalculatedSolarStarRadius_ptr);  // 0x157DCF0 0x1579D10
}