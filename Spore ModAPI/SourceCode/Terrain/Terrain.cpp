#ifndef MODAPI_DLL_EXPORT
#include <Spore\Internal.h>
#include <Spore\Terrain\ITerrainResourceManager.h>
#include <Spore\Terrain\cTerrainMapSet.h>
#include <Spore\Terrain\Sphere\cTerrainSphere.h>

namespace Terrain
{
	auto_STATIC_METHOD_(ITerrainResourceManager, ITerrainResourceManager*, Get);

	auto_METHOD_const(cTerrainMapSet, float, GetHeight, Args(const Vector3& v), Args(v));

	namespace Sphere
	{
		auto_METHOD_VOID(cTerrainSphere, Generate, 
			Args(int* unused0, int* unused1, bool arg_8, bool generateSingleStep, float generateTimeLimit), 
			Args(unused0, unused1, arg_8, generateSingleStep, generateTimeLimit));
	}

	cTerrainMap::cTerrainMap()
		: mnRefCount()
		, size()
		, field_0C()
	{
	}

	cTerrainMap32::cTerrainMap32()
		: data()
	{}
	void* cTerrainMap32::GetData() {
		return data.data();
	}

	cTerrainMap16::cTerrainMap16()
		: data()
	{}
	void* cTerrainMap16::GetData() {
		return data.data();
	}

	int cTerrainMap::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}
	int cTerrainMap::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}


	cTerrainMapSet::cHeightRanges::cHeightRanges()
		: field_0(0x55)
		, field_4(1)
		, field_8(5)
		, field_C(0x15)
		, field_10(0x55)
		, field_14(0x155)
		, mpCell(new int[8190])
	{

	}

	cTerrainMapSet::cTerrainMapSet()
		: mnRefCount(0)
		, mMaps()
		, mPlanetRadius(500.0f)
		, mAltitudeRange(100.0f)
		, mWaterLevel()
		, field_40()
		, field_44(0.025f)
		, field_48()
		, mMaxCliffGradient()
		, field_50(-1.0f)
		, field_54(-1.0f)
		, mpHeightRanges(new cHeightRanges())
	{

	}

	cTerrainMapSet::~cTerrainMapSet()
	{
		if (mpHeightRanges) {
			if (mpHeightRanges->mpCell) delete mpHeightRanges->mpCell;
			delete mpHeightRanges;
		}
	}

	void cTerrainMapSet::SetMap(TerrainMapIndex index, cTerrainMap* pMap)
	{
		mMaps[(int)index] = pMap;
	}
	cTerrainMap* cTerrainMapSet::GetMap(TerrainMapIndex index) {
		return mMaps[(int)index].get();
	}


	cTerrainStateMgr::TerrainMaterial::TerrainMaterial()
		: kAtmThicknessByAtmosphereScore()
		, kFogByElevCreature()
		, kFogByElevTribe()
		, kFogByElevCiv()
		, kFogByElevSpace()
		, kFogDistBiasByTimeOfDay()
		, kFogDistBiasByAtmosphereScore()
		, kFogBiasByElev()
		, mWaterMap()
		, field_204()
		, mAtmosphereMap()
		, field_20C()
		, field_210()
		, factoredTerrainUserColorElevations()
		, factoredTerrainUserColorElevationColors()
	{
	}

	cTerrainStateMgr::TerrainTextures::TerrainTextures()
		: field_00()
		, field_04()
		, field_08()
		, pTextureAboveDetail2()
		, pTextureBelow()
		, field_14()
		, field_18()
		, field_1C()
		, pTextureBeach()
		, pTextureCliff()
		, field_30()
		, field_34()
		, field_38()
		, field_3C()
		, field_40()
		, field_44()
		, field_48()
		, field_4C()
		, field_50()
		, field_54()
	{

	}

	cTerrainStateMgr::cTerrainStateMgr(ITerrain* pTerrain)
		: mpTerrain(pTerrain)
		, mpMapSet(pTerrain->GetTerrainMapSet())
		, mMaterial()
		, mTextures()
		, field_5AC(true)
		, field_5AD()
		, mpMaterialPropList()
		, field_5B4()
		, field_5B8()
		, mAtmosphereType()
		, mWaterType()
		, field_5C8()
		, field_5D8()
		, field_5E8()
		, field_5F8()
		, field_5FC()
		, field_600(-1.0f)
		, mWaterLevel(0.5f)
		, field_608()
		, field_60C(1.0f)
		, mWaveFreq(1.0f)
		, mWaveAmp()
		, field_618()
		, field_61C()
		, field_620()
		, field_624()
		, field_7BC()
	{
		memset(field_628, 0, sizeof(field_628));
		memset(field_7C0, 0, sizeof(field_7C0));
		memset(field_940, 0, sizeof(field_940));
		memset(field_AC0, 0, sizeof(field_AC0));
	}
}

#endif