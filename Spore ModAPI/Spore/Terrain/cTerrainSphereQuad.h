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

#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Terrain\cTerrainShaderMgr.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Terrain
{
	class cTerrainSphere;

	struct TerrainTransform
	{
		/* 00h */	D3DMATRIX worldViewProjection;
		/* 40h */	Math::Vector4 QuadFaceUVXform;
		/* 50h */	Math::Vector4 QuadMorphValue;
		/* 60h */	Math::Vector4 QuadFaceElemMap;
		/* 70h */	Math::Vector4 QuadFaceSignMap;
		/* 80h */	Math::Vector4 QuadFaceXForm[3];
	};
	ASSERT_SIZE(TerrainTransform, 0xB0);

	struct TerrainQuadMesh
	{
		/* 00h */	RenderWare::VertexBuffer* vertexBuffer;
		/* 04h */	RenderWare::IndexBuffer* indexBuffer;
		// anything else?
	};

	class cTerrainSphereQuad
	{
	public:
		void Initialize(cTerrainSphere* pSphere, int, int index, const Math::Vector2& coord0, const Math::Vector2& coord1, int);

		/// Loads the `mTerrainTransform` field into the shader data `terrainTransform`, it also loads the
		/// shader data `pcaTexture`.
		/// @param pViewer
		void LoadTerrainTransform(App::cViewer* pViewer);

		/// Draws the sphere quad mesh, this does not change any materials.
		/// @param pVertices
		/// @param pIndices
		/// @param startIndex
		/// @param indicesCount
		void Draw(RenderWare::VertexBuffer* pVertices, RenderWare::IndexBuffer* pIndices, int startIndex, int indicesCount);

		/// Called by Terrain::cTerrainSphere::RenderTerrainLand().
		/// Source code: @ref SourceCode-Terrain-cTerrainSphereQuad-RenderLand
		/// @param pViewer Camera and viewport configuration
		/// @param stats Structure used to write rendering statistics
		void RenderLand(App::cViewer* pViewer, Graphics::RenderStatistics& stats);

		/// Called by Terrain::cTerrainSphere::RenderTerrainSeabedAsLand().
		/// Source code: @ref SourceCode-Terrain-cTerrainSphereQuad-RenderSeabedAsLand
		/// @param pViewer Camera and viewport configuration
		/// @param stats Structure used to write rendering statistics
		void RenderSeabedAsLand(App::cViewer* pViewer, Graphics::RenderStatistics& stats);

		/// Called by Terrain::cTerrainSphere::RenderTerrainWater().
		/// Source code: @ref SourceCode-Terrain-cTerrainSphereQuad-RenderWater
		/// @param pViewer Camera and viewport configuration
		/// @param stats Structure used to write rendering statistics
		/// @param material Material that must be used to render the water (e.g. ice, lava, water, etc)
		/// @param flags Additional rendering flags, not used.
		void RenderWater(App::cViewer* pViewer, Graphics::RenderStatistics& stats, TerrainMaterialIndex material, int flags);

		/// Called by Terrain::cTerrainSphere::RenderTerrainAtmosphere(). 
		/// Source code: @ref SourceCode-Terrain-cTerrainSphereQuad-RenderAtmosphere
		/// @param pViewer Camera and viewport configuration
		/// @param stats Structure used to write rendering statistics
		void RenderAtmosphere(App::cViewer* pViewer, Graphics::RenderStatistics& stats);

		/// Called by Terrain::cTerrainSphere::RenderTerrainDecals(). 
		/// @param pViewer Camera and viewport configuration
		/// @param stats Structure used to write rendering statistics
		void RenderDecals(App::cViewer* pViewer, Graphics::RenderStatistics& stats);

		/// Recalculates the geometry of the terrain quad only if needed,
		/// calling UpdateVertexBuffer() and UpdateIndexBuffer accordingly.
		void UpdateBuffers();

		/// Recalculates the vertex buffer of the terrain quad, and sets `mMustUpdateVertexBuffer` to false.
		void UpdateVertexBuffer();

		/// Recalculates the index buffer of the terrain quad, and sets `mMustUpdateIndexBuffer` to false.
		void UpdateIndexBuffer();

	public:
		/* 00h */	cTerrainSphere* mpSphere;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int mPlanetLODChunkRes;
		/// Index of sphere quad, from 0 to 5
		/* 1Ch */	int mIndex;
		// UV coords?
		/* 20h */	Math::Vector2 field_20;
		/* 28h */	Math::Vector2 field_28;
		/* 30h */	float field_30;  // 1.0
		/* 34h */	Math::Vector3 field_34;  // 0, 0, 1
		/* 40h */	char padding_40[0x64 - 0x40];
		/* 64h */	float field_64;
		/* 68h */	float field_68;
		/* 6Ch */	bool mIsLowRes;
		/* 70h */	Math::BoundingBox mChunkBoundingBox;
		/* 88h */	float field_88;
		/* 8Ch */	float field_8C;
		/* 90h */	bool mMustUpdateVertexBuffer;
		/* 91h */	bool mMustUpdateIndexBuffer;
		/* 94h */	TerrainQuadMesh* mpMesh;
		/* 98h */	int mIndicesCount;
		/* 9Ch */	int mWaterIndicesCount;
		/* A0h */	int mWaterIndicesStart;
		/* A4h */	TerrainTransform mTerrainTransform;
		// 154h vector with struct of size 16 with pointer to cTerrainSphereDecal
		/* 154h */	eastl::vector<int> field_154;
		/* 168h */	int field_168;
		/* 16Ch */	int field_16C;
		/* 170h */	int field_170;
		// related with mPlanetLODChunkRes
		/* 174h */	void* mAboveBelowMap;
		/* 178h */	int field_178;
		/* 17Ch */	Math::Vector2 field_17C;  // not initialized
		/* 184h */	Math::Vector2 field_184;  // not initialized
		/* 18Ch */	eastl::vector<int> field_18C;
		/* 1A0h */	eastl::vector<int> field_1A0;
		/* 1B4h */	int field_1B4;  // not initialized
	};
	ASSERT_SIZE(cTerrainSphereQuad, 0x1B8);

	namespace Addresses(cTerrainSphereQuad)
	{
		DeclareAddress(Initialize);  // 0xFB5540 0xFB4DE0
		DeclareAddress(LoadTerrainTransform);  // 0xFB73F3 0xFB1750
		DeclareAddress(Draw);  // 0xFAF550 0xFAEEC0
		DeclareAddress(RenderLand);  // 0xFB6DC0 0xFB66A0
		DeclareAddress(RenderSeabedAsLand);  // 0xFB74F0 0xFB6DD0
		DeclareAddress(RenderWater);  // 0xFB6F40 0xFB6820
		DeclareAddress(RenderAtmosphere);  // 0xFB73C0 0xFB6CA0
		DeclareAddress(RenderDecals);  // 0xFB36C0 0xFB3010
		DeclareAddress(UpdateVertexBuffer);  // 0xFB6D20 0xFB6600
		DeclareAddress(UpdateIndexBuffer);  // 0xFB4AE0 0xFB4380
	}

	inline void cTerrainSphereQuad::UpdateBuffers()
	{
		if (mMustUpdateVertexBuffer) {
			UpdateVertexBuffer();
		}
		if (mMustUpdateIndexBuffer) {
			UpdateIndexBuffer();
		}
	}
}