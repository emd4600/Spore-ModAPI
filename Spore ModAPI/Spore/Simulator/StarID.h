#pragma once

#include <cstdint>
#include <Spore\Internal.h>

namespace Simulator
{
	class cStarRecord;
	class cPlanetRecord;

	/// 32 bits field used to uniquely identify a star within the galaxy. 
	/// The galaxy is divided in sectors, the star ID keeps the index to the sector and the index of the 
	/// star within the sector. Some bits are reserved to be able to form PlanetID. The bits are organized as:
	/// ```
	/// 31    24 23       12 11      0
	/// 00000000 sectorIndex starIndex
	/// ```
	struct StarID
	{
		uint32_t internalValue;

		/// Creates a star ID using the given sector and index of star within that sector.
		/// @param sectorIndex Index of galaxy sector, between 0 and 4095.
		/// @param starIndex Index of star within the sector, between 0 and 4095.
		inline StarID(unsigned int sectorIndex, unsigned int starIndex)
		{
			internalValue = ((sectorIndex & 0x00000FFF) << 12) | (starIndex & 0x00000FFF);
		}

		inline StarID(uint32_t value)
			: internalValue(value)
		{}

		cStarRecord* GetRecord() const;

		/// Returns the index of the sector where this star is stored.
		/// @returns
		inline unsigned int GetSectorIndex() const {
			return (internalValue & 0xFFFFF000) >> 12;
		}
		/// Returns the index of the star within its star sector.
		/// @returns
		inline unsigned int GetStarIndex() const {
			return internalValue & 0x00000FFF;
		}
	};
	ASSERT_SIZE(StarID, 4);

	/// 32 bits field that uniquely identifies a planet in the galaxy.
	/// This ID is made up by the StarID of the star system where the planet is, combined
	/// with an index of the planet within that solar system (where 0 is the closest to the sun,
	/// 1 is the second closest, etc).
	/// The bits are organized as:
	/// ```
	/// 31       24 23       12 11      0
	/// planetIndex sectorIndex starIndex
	///             (-------StarID------)
	/// ```
	struct PlanetID
	{
		uint32_t internalValue;

		/// Creates a planet ID combining the given star ID and index of the planet within that solar system 
		/// (where 0 is the closest to the sun, 1 the second closest, etc).
		/// @param starID ID of the star system where this planet is.
		/// @param starIndex Index of planet within the star system, between 0 and 255.
		inline PlanetID(StarID starID, unsigned int planetIndex)
		{
			internalValue = ((planetIndex & 0xFF) << 24) | (starID.internalValue & 0x00FFFFFF);
		}

		inline PlanetID(uint32_t value)
			: internalValue(value)
		{}

		cPlanetRecord* GetRecord() const;

		/// Returns the ID that uniquely identifies the star where this planet is.
		/// @returns
		inline StarID GetStarID() const {
			return internalValue & 0x00FFFFFF;
		}
		/// Returns the index of this planet within its star system.
		/// @returns
		inline unsigned int GetPlanetIndex() const {
			return internalValue & 0xFF000000 >> 24;
		}
	};
	ASSERT_SIZE(PlanetID, 4);
}