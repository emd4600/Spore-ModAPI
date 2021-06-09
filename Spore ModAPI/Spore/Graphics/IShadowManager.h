#pragma once

#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Internal.h>

/// Access the active shadow manager.
#define ShadowManager (*Graphics::IShadowManager::Get())

#define IShadowManagerPtr intrusive_ptr<Graphics::IShadowManager>

namespace Graphics
{
	class IShadowManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IShadowManager() = 0;
		/* 0Ch */	virtual void Update() = 0;
		/* 10h */	virtual void SetLightingWorld(ILightingWorld* world) = 0;
		/* 14h */	virtual void func14h(int) = 0;
		// 11D00 extra flags are added
		/* 18h */	virtual void AddModelWorld(IModelWorld* world, int flags = 0) = 0;
		/* 1Ch */	virtual void func1Ch(int, int flags = 0) = 0;
		/* 20h */	virtual void AddRenderable(IRenderable* renderable, int flags = 0) = 0;
		// removes lighting world and renderables
		/* 24h */	virtual void ClearData() = 0;
		/* 28h */	virtual void func28h(bool) = 0;  // set use shadow curve?
		/* 2Ch */	virtual bool func2Ch() = 0;  // returns field_0C
		/* 30h */	virtual void SetSunDirection(const Vector3& direction) = 0;
		/* 34h */	virtual Vector3 GetSunDirection() = 0;
		/* 38h */	virtual void func38h(const Vector3&, const Vector3&) = 0;
		/* 3Ch */	virtual Vector3 func3Ch() = 0;
		/* 40h */	virtual void func40h() = 0;
		/* 44h */	virtual void func44h() = 0;
		/* 48h */	virtual void func48h(uint32_t) = 0;
		/* 4Ch */	virtual uint32_t func4Ch() = 0;
		/// Loads all the shadow data into the renderer.
		/* 50h */	virtual void PrepareRender(ILightingWorld* world) = 0;

		///
		/// Returns the active shadow manager.
		///
		static IShadowManager* Get();

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
}