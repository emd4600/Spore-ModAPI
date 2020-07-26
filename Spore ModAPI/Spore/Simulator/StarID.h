#pragma once

#include <cstdint>

namespace Simulator
{
	typedef uint32_t StarID;

	/// Returns the index of the sector where this star is stored.
	/// @param star The key that uniquely identifies the star.
	inline size_t GetSectorIndex(StarID star) {
		return (int(star) & 0xFFFFF000) >> 12;
	}
	/// Returns the index of the star within its star sector.
	/// @param star The key that uniquely identifies the star.
	inline size_t GetStarIndex(StarID star) {
		return int(star) & 0x00000FFF;
	}

	typedef uint32_t PlanetID;

	/// Returns the key that uniquely identifies the star where the given planet is.
	/// @param planet The key that uniquely identifies the planet.
	inline StarID GetStarKey(PlanetID planet) {
		return int(planet) & 0x00FFFFFF;
	}
	/// Returns the index of the planet within its star system.
	/// @param planet The key that uniquely identifies the planet.
	inline size_t GetPlanetIndex(PlanetID planet) {
		return (int(planet) & 0xFF000000) >> 24;
	}
}