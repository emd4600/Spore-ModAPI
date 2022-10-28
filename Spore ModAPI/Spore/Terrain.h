#pragma once

/// @file Terrain.h
/// This file includes all the necessary headers for working with the planet terrain in Spore.

/// @namespace Terrain
///
/// @brief Everything related with the planet terrain system.
/// 
/// Planets in Spore are spheres, but geometrically they are actually cubes, with the faces deformed outwards to look like a sphere.
/// The main terrain class for a planet is Terrain::cTerrainSphere, which is composed of 6 Terrain::cTerrainSphereQuad faces.
///

#include <Spore\Terrain\cTerrainSphere.h>
#include <Spore\Terrain\cTerrainSphereQuad.h>
#include <Spore\Terrain\TerrainRendering.h>
#include <Spore\Terrain\ITerrainResourceManager.h>
#include <Spore\Terrain\cTerrainMapSet.h>
#include <Spore\Terrain\cTerrainShaderMgr.h>