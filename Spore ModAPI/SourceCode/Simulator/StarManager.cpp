#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <Spore\Simulator\SubSystem\SpaceGfx.h>
#include <Spore\Simulator\SpaceConstants.h>

namespace Simulator
{

	auto_METHOD(cSpaceTradeRouteManager, bool, HasTradeRoute, Args(StarID star, uint32_t empireID), Args(star, empireID));

	auto_STATIC_METHOD_(cStarManager, cStarManager*, Get);

	auto_METHOD(cStarManager, cPlanetRecord*, GetPlanetRecord, Args(PlanetID recordIndex), Args(recordIndex));

	cEmpire* cStarManager::GetEmpire(uint32_t politicalID)
	{
		auto it = mEmpires.find(politicalID);
		if (it != mEmpires.end())
		{
			return it->second.get();
		}
		else
		{
			return nullptr;
		}
	}

	cStarRecord* cStarManager::GetStarRecord(StarID id)
	{
		if (id.internalValue == 0)
		{
			return mpTempStar.get();
		}
		else if (id.internalValue == -1)
		{
			return nullptr;
		}
		else
		{
			return mStarRecordGrid[id.GetSectorIndex()][id.GetStarIndex()].get();
		}
	}

	EmpiresMap& cStarManager::GetEmpires()
	{
		return mEmpires;
	}


	auto_METHOD(cStarManager, uint32_t, NextPoliticalID, Args(bool arg), Args(arg));
	auto_METHOD(cStarManager, cEmpire*, GetEmpireForStar, Args(cStarRecord* arg), Args(arg));

	auto_METHOD_VOID(cStarManager, RecordToPlanet, Args(cPlanetRecord* record, cPlanetPtr& dst),
		Args(record, dst));


	StarRequestFilter::StarRequestFilter()
		: starTypes(0x1FFF)
		, techLevels(0x3F)
		, flags()
		, minDistance(-1.0f)
		, maxDistance(-1.0f)
		, field_14(-1.0f)
		, field_18()
	{
	}

	void StarRequestFilter::AddStarType(StarType type) {
		starTypes |= 1 << int(type);
	}
	void StarRequestFilter::AddTechLevel(TechLevel level) {
		techLevels |= 1 << int(level);
	}
	void StarRequestFilter::RemoveStarType(StarType type) {
		starTypes &= ~(1 << int(type));
	}
	void StarRequestFilter::RemoveTechLevel(TechLevel level) {
		techLevels &= ~(1 << int(level));
	}

	auto_METHOD(cStarManager, cStarRecord*, FindClosestStar, 
		Args(const Vector3& coords, const StarRequestFilter& filter), Args(coords, filter));

	auto_METHOD_VOID(cStarManager, FindStars,
		Args(const Vector3& coords, const StarRequestFilter& filter, eastl::vector<cStarRecordPtr>& dst),
		Args(coords, filter, dst));

	auto_METHOD_VOID(cStarManager, CalculatePlanetScores,
		Args(cPlanetRecord* pPlanetRecord, cStarRecord* pStar, int arg), Args(pPlanetRecord, pStar, arg));

	auto_METHOD_VOID(cStarManager, GetStarGridPosition,
		Args(const Vector3& position, unsigned int& dstX, unsigned int& dstY), Args(position, dstX, dstY));

	auto_METHOD_VOID(cStarManager, GenerateEllipticalOrbit,
		Args(cStarRecord* pStarRecord, cEllipticalOrbit& dst, float mind, float maxd, cPlanetRecord* pOrbitAroundPlanet),
		Args(pStarRecord, dst, mind, maxd, pOrbitAroundPlanet));

	auto_METHOD_VOID_(cStarManager, GenerateSolSystem);

	auto_METHOD_VOID(cStarManager, RequirePlanetsForStar,
		Args(cStarRecord* pStarRecord, StarRequestFilter* pFilter),
		Args(pStarRecord, pFilter));

	auto_METHOD_VOID(cStarManager, GeneratePlanetsForStar,
		Args(cStarRecord* pStarRecord, StarRequestFilter* pFilter, bool arg),
		Args(pStarRecord, pFilter, arg));

	auto_STATIC_METHOD(cStarManager, bool, StarGenerationMessageHandler,
		Args(uint32_t messageId, Swarm::Components::DistributeEffectMessageData* pDistributeData, StarType starType),
		Args(messageId, pDistributeData, starType));


	cPlanetRecord* PlanetID::GetRecord() const
	{
		return StarManager.GetPlanetRecord(*this);
	}

	cStarRecord* StarID::GetRecord() const
	{
		return StarManager.GetStarRecord(*this);
	}



	auto_STATIC_METHOD_(cSpaceGfx, cSpaceGfx*, Get);
	auto_METHOD_VOID_(cSpaceGfx, InitializeInternal);
	auto_METHOD_VOID_(cSpaceGfx, DisposeInternal);
}

auto_STATIC_METHOD_VOID(Simulator, SpaceTeleportTo, Args(cStarRecord* star), Args(star));

auto_STATIC_METHOD(Simulator, Vector3&, GalaxyCoordinatesTo3D, 
	Args(float parsecDistance, float angle, Vector3& dst), Args(parsecDistance, angle, dst));


auto_STATIC_METHOD_VOID(Simulator, GetBinarySystemStarTypes,
	Args(Simulator::StarType binaryType, Simulator::StarType& star1, Simulator::StarType& star2), 
	Args(binaryType, star1, star2));

auto_STATIC_METHOD(Simulator, float, GetBinarySystemBaseRadius,
	Args(Simulator::StarType binaryType), Args(binaryType));

auto_STATIC_METHOD(Simulator, float, GetSolarStarTemperature,
	Args(Simulator::StarType starType), Args(starType));

auto_STATIC_METHOD(Simulator, float, GetSolarStarMass, 
	Args(Simulator::StarType starType), Args(starType));

auto_STATIC_METHOD(Simulator, float, GetSolarStarRadius,
	Args(Simulator::StarType starType), Args(starType));

auto_STATIC_METHOD(Simulator, float, GetSolarStarRotationRate,
	Args(Simulator::StarType starType), Args(starType));

auto_STATIC_METHOD(Simulator, float, GetSolarStarOrbitRadius,
	Args(Simulator::StarType starType, Simulator::SolarSystemOrbitTemperature orbitTemperature), 
	Args(starType, orbitTemperature));

auto_STATIC_METHOD(Simulator, Simulator::PlanetTemperatureType,  GetPlanetTemperatureType,
	Args(float temperatureScore), Args(temperatureScore));

auto_STATIC_METHOD(Simulator, bool, IsBinaryStar,
	Args(Simulator::StarType starType), Args(starType));

auto_STATIC_METHOD(Simulator, bool, IsNotStarOrBinaryStar,
	Args(Simulator::StarType starType), Args(starType));

float* Simulator::GetPrecalculatedSolarStarRadius() {
	return (float*)GetAddress(Simulator, PrecalculatedSolarStarRadius_ptr);
}

#endif
