#pragma once

#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Internal.h>

/// Access the active shadow manager.
#define ShadowWorld (*Graphics::IShadowWorld::Get())

#define IShadowWorldPtr eastl::intrusive_ptr<Graphics::IShadowWorld>

namespace Graphics
{
	class IShadowWorld
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IShadowWorld() = 0;

		/* 0Ch */	virtual void Update() = 0;

		/* 10h */	virtual void SetLightingWorld(ILightingWorld* world) = 0;

		/* 14h */	virtual void SetShadowMapLayer(int) = 0;

		// 11D00 extra flags are added
		/* 18h */	virtual void AddModelWorld(IModelWorld* world, int flags = 0) = 0;

		/* 1Ch */	virtual void AddEffects(void* pEffectsRenderer, int flags = 0) = 0;

		/* 20h */	virtual void AddLayer(ILayer* layer, int flags = 0) = 0;

		// removes lighting world and renderables
		/* 24h */	virtual void Reset() = 0;

		/* 28h */	virtual void SetActive(bool active) = 0;  // set use shadow curve?

		/* 2Ch */	virtual bool IsActive() = 0;

		/* 30h */	virtual void SetDirection(const Vector3& direction) = 0;
		/* 34h */	virtual Vector3 GetDirection() = 0;

		/* 38h */	virtual void SetCentreOfInterest(const Vector3&, const Vector3&) = 0;

		/* 3Ch */	virtual void SetEffectiveViewer(const Vector3&) = 0;

		/* 40h */	virtual void PushState() = 0;
		/* 44h */	virtual void PopState() = 0;

		/* 48h */	virtual void SetActiveID(uint32_t) = 0;
		/* 4Ch */	virtual uint32_t GetActiveID() = 0;

		/// Loads all the shadow data into the renderer.
		/* 50h */	virtual void ApplyGlobalState(ILightingWorld* world) = 0;

		///
		/// Returns the active shadow manager.
		///
		static IShadowWorld* Get();

		// Actual shadow manager vftable starts at 08h

		// 14h bool ShadowNestedMaps
		// 15h bool ShadowBasisF32
		// 18h ILightingWorldPtr lightingWorld;
		// 1Ch vector? of renderables
		// E8h Raster* worldMap;
		// F4h object related with world map
		// FCh ResourceID worldMapRttId;
		// 1B8h cViewer* viewers;
		// 1C4h bool ShadowConvolutionMaps
		// 1C8h	Vector2 shadowCameraRange;
		// 1DCh int shadowScaleCurveCount;
		// 1E0h	float* shadowScaleCurve;
		// 1E4h int shadowStrengthCurveCount;
		// 1E8h	float* shadowStrengthCurve;
		// 1ECh int shadowCasterDistanceCount;
		// 1F0h	float* shadowCasterDistance;
		// 1F4h int shadowDepthRangeCount;
		// 1F8h	float* shadowDepthRange;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IShadowManager)
	{
		DeclareAddress(Get);
	}
	namespace Addresses(IShadowWorld)
	{
		DeclareAddress(Get);
	}
}