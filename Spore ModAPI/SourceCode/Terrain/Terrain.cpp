#ifndef MODAPI_DLL_EXPORT
#include <Spore\Internal.h>
#include <Spore\Terrain\ITerrainResourceManager.h>
#include <Spore\Terrain\cTerrainMapSet.h>
#include <Spore\Terrain\cTerrainSphere.h>
#include <Spore\Terrain\TerrainRendering.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Properties.h>
#include <Spore\CommonIDs.h>

namespace Terrain
{
	auto_STATIC_METHOD_(ITerrainResourceManager, ITerrainResourceManager*, Get);

	auto_METHOD_const(cTerrainMapSet, float, GetHeight, Args(const Vector3& v), Args(v));

	auto_METHOD_VOID(cTerrainSphere, Generate, 
		Args(int* unused0, int* unused1, bool arg_8, bool generateSingleStep, float generateTimeLimit), 
		Args(unused0, unused1, arg_8, generateSingleStep, generateTimeLimit));

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
		, mAtmosphereMap()
		, field_208()
		, field_20C()
		, field_210()
		, factoredTerrainUserColorElevations()
		, factoredTerrainUserColorElevationColors()
	{
	}

	cTerrainStateMgr::TerrainTextures::TerrainTextures()
		: mpWaterFoamCutMap()
		, mpWaterPCAComponent0()
		, mpWaterPCAComponent1()
		, mpTextureAboveDetail2()
		, mpTextureBelow()
		, mpLavaDetail()
		, mpLavaRamp()
		, mpIceDetailNear()
		, mpIceDetailMid()
		, mpIceRamp()
		, mpTextureBeach()
		, mpTextureCliff()
		, mpAtmospherePackedCurves()
		, mpAboveColorRamp()
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


	auto_METHOD_VOID_(cTerrainSphere, PrepareShaderData);

	auto_METHOD_VOID(cTerrainSphere, RenderTerrainLand, Args(Graphics::RenderStatistics& stats, int flags), Args(stats, flags));
	auto_METHOD_VOID(cTerrainSphere, RenderTerrainSeabedAsLand, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats), Args(pViewer, stats));
	auto_METHOD_VOID(cTerrainSphere, RenderTerrainWater, Args(Graphics::RenderStatistics& stats, int flags), Args(stats, flags));
	auto_METHOD_VOID(cTerrainSphere, RenderTerrainDecals, Args(Graphics::RenderStatistics& stats, int flags), Args(stats, flags));
	auto_METHOD_VOID(cTerrainSphere, RenderTerrainRibbons, Args(Graphics::RenderStatistics& stats, int flags), Args(stats, flags));
	auto_METHOD_VOID(cTerrainSphere, RenderTerrainAtmosphere, Args(Graphics::RenderStatistics& stats, int flags), Args(stats, flags));

	auto_METHOD_VOID(cTerrainSphere, MainRenderPass, Args(App::cViewer** ppViewer, Graphics::RenderStatistics& stats, int flags), Args(ppViewer, stats, flags));

	auto_METHOD_VOID_(cTerrainSphere, RenderWaterReflectionAndRefraction);
	auto_METHOD_VOID_(cTerrainSphere, RenderWaterRefraction);
	auto_METHOD_VOID_(cTerrainSphere, RenderWaterReflection);

	RenderWare::Raster* cTerrainSphere::GetQuadNormalMap(int quadIndex) {
		return mTerrainNormalMaps[quadIndex]->GetRaster();
	}
	RenderWare::Raster* cTerrainSphere::GetQuadHeightMap(int quadIndex) {
		return mTerrainHeightMaps[quadIndex]->GetRaster();
	}
	RenderWare::Raster* cTerrainSphere::GetQuadControlMap(int quadIndex) {
		return mTerrainControlMaps[quadIndex]->GetRaster();
	}

	auto_METHOD(cTerrainSphere, RenderWare::Raster*, GetSimDataRTT, Args(int quadIndex), Args(quadIndex));

	auto_METHOD_VOID_(cTerrainSphere, CreateRTTs);



	auto_METHOD_VOID(cTerrainSphereQuad, Initialize,
		Args(cTerrainSphere* pSphere, int arg1, int index, const Math::Vector2& coord0, const Math::Vector2& coord1, int arg5),
		Args(pSphere, arg1, index, coord0, coord1, arg5));

	auto_METHOD_VOID(cTerrainSphereQuad, LoadTerrainTransform, Args(App::cViewer* pViewer), Args(pViewer));

	auto_METHOD_VOID(cTerrainSphereQuad, Draw,
		Args(RenderWare::VertexBuffer* pVertices, RenderWare::IndexBuffer* pIndices, int startIndex, int indicesCount),
		Args(pVertices, pIndices, startIndex, indicesCount));

	auto_METHOD_VOID(cTerrainSphereQuad, RenderLand, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats), Args(pViewer, stats));
	auto_METHOD_VOID(cTerrainSphereQuad, RenderSeabedAsLand, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats), Args(pViewer, stats));
	auto_METHOD_VOID(cTerrainSphereQuad, RenderWater, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats, TerrainMaterialIndex material, int flags), Args(pViewer, stats, material, flags));
	auto_METHOD_VOID(cTerrainSphereQuad, RenderAtmosphere, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats), Args(pViewer, stats));
	auto_METHOD_VOID(cTerrainSphereQuad, RenderDecals, Args(App::cViewer* pViewer, Graphics::RenderStatistics& stats), Args(pViewer, stats));

	auto_METHOD_VOID_(cTerrainSphereQuad, UpdateVertexBuffer);
	auto_METHOD_VOID_(cTerrainSphereQuad, UpdateIndexBuffer);



	TerrainMaterialIndex GetActiveMaterialIndex() {
		return *(TerrainMaterialIndex*)GetAddress(Terrain, CurrentMaterialIndex_ptr);
	}
	void SetActiveMaterialIndex(TerrainMaterialIndex material) {
		*(TerrainMaterialIndex*)GetAddress(Terrain, CurrentMaterialIndex_ptr) = material;
	}

	int GetActiveQuadIndex() {
		return *(int*)GetAddress(Terrain, CurrentQuadIndex_ptr);
	}
	void SetActiveQuadIndex(int index) {
		*(int*)GetAddress(Terrain, CurrentQuadIndex_ptr) = index;
	}

	bool IsActiveQuadMaterial(TerrainMaterialIndex material, int quadIndex) {
		return GetActiveQuadIndex() == quadIndex && GetActiveMaterialIndex() == material;
	}
	void SetActiveQuadMaterial(TerrainMaterialIndex material, int quadIndex) {
		SetActiveQuadIndex(quadIndex);
		SetActiveMaterialIndex(material);
	}


	RenderWare::IndexBuffer* GetAtmosphereIndexBuffer();  //TODO

	auto_STATIC_METHOD_VOID_(Terrain, CreateRefractionRTTs);
	auto_STATIC_METHOD_VOID_(Terrain, DisposeRefractionRTTs);

	Graphics::RenderTargetID* GetRefractionBuffersRenderTargetID() {
		return (Graphics::RenderTargetID*)GetAddress(Terrain, TerrainRefractionBuffersRTT_ID_ptr);
	}
	Graphics::Texture* GetRefractionBuffersRenderTargetTexture() {
		return *(Graphics::Texture**)GetAddress(Terrain, TerrainRefractionBuffersRTTTexture_ptr);
	}
	RenderWare::Raster* GetRefractionBuffersRenderTarget() {
		return GetRefractionBuffersRenderTargetTexture()->GetRaster();
	}
	void SetRefractionBuffersRenderTargetTexture(Graphics::Texture* texture) {
		*(Graphics::Texture**)GetAddress(Terrain, TerrainRefractionBuffersRTTTexture_ptr) = texture;
	}

	Graphics::RenderTargetID* GetRefractionBlur1RenderTargetID() {
		return (Graphics::RenderTargetID*)GetAddress(Terrain, TerrainRefractionBlur1RTT_ID_ptr);
	}
	Graphics::RenderTargetID* GetRefractionBlur2RenderTargetID() {
		return (Graphics::RenderTargetID*)GetAddress(Terrain, TerrainRefractionBlur2RTT_ID_ptr);
	}

	App::cViewer* GetRefractionViewer() {
		return (App::cViewer*)GetAddress(Terrain, TerrainRefractionViewer_ptr);
	}

	auto_STATIC_METHOD_VOID_(Terrain, CreateReflectionRTTs);
	auto_STATIC_METHOD_VOID_(Terrain, DisposeReflectionRTTs);

	TexturePtr& GetReflectionTexture() {
		return *(TexturePtr*)GetAddress(Terrain, TerrainReflectionTexture_ptr);
	}
	App::cViewer* GetReflectionViewer() {
		return (App::cViewer*)GetAddress(Terrain, TerrainReflectionViewer_ptr);
	}

	auto_STATIC_METHOD_VOID_(Terrain, CreateScatterRTTs);

	TexturePtr& GetBakeInScatterTexture() {
		return *(TexturePtr*)GetAddress(Terrain, TerrainBakeInScatterTexture_ptr);
	}
	TexturePtr& GetScatterTexture() {
		return *(TexturePtr*)GetAddress(Terrain, TerrainScatterTexture_ptr);
	}
	App::cViewer* GetScatterViewer() {
		return (App::cViewer*)GetAddress(Terrain, TerrainScatterViewer_ptr);
	}

	Graphics::Texture** GetSimDataRenderTargetTextures() {
		return (Graphics::Texture**)GetAddress(Terrain, TerrainSimDataTextures_ptr);
	}
	Graphics::RenderTargetID* GetSimDataRenderTargetIDs() {
		return (Graphics::RenderTargetID*)GetAddress(Terrain, TerrainSimDataRTTs_ID_ptr);
	}

	Graphics::RenderTargetID* GetColorMapID() {
		return (Graphics::RenderTargetID*)GetAddress(Terrain, TerrainColorMapRTT_ID_ptr);
	}
	RenderWare::Raster* GetColorMap() {
		return *(RenderWare::Raster**)GetAddress(Terrain, TerrainColorMapRTT_ptr);
	}
	void SetColorMap(RenderWare::Raster* pRaster) {
		*(RenderWare::Raster**)GetAddress(Terrain, TerrainColorMapRTT_ptr) = pRaster;
	}
	App::cViewer* GetColorMapViewer() {
		return (App::cViewer*)GetAddress(Terrain, TerrainColorMapViewer_ptr);
	}
}



#endif