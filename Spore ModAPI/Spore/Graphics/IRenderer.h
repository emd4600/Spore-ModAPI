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

#include <EASTL\intrusive_ptr.h>
#include <Spore\Internal.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Graphics\LambdaRenderable.h>
#include <Spore\App\cJob.h>


/// Access the active render manager.
#define Renderer (*Graphics::IRenderer::Get())

#define IRendererPtr eastl::intrusive_ptr<Graphics::IRenderer>

namespace Graphics
{
	struct cRenderJobInfo
	{
		/* 00h */	int field_0;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
	};
	ASSERT_SIZE(cRenderJobInfo, 11 * 4);

	struct cScreenInfo
	{
		/* 00h */	int width;
		/* 04h */	int height;
		/* 08h */	int mouseX;
		/* 0Ch */	int mouseY;
		// more things
	};

	enum
	{
		kRenderQueueMain = 8  // ?
	};

	/// The available layer indices that can be used for adding renderers.
	/// Most of these have been copied from Darkspore globals.lua, so they might not match for Spore.
	enum class LayerIndices {

		// Layer 3 render from 4 to 21

		ClearScene = 0,

		// These two are used by cTerrainSphere, but not sure if it's for this
		//TODO not true? I think 7 is water reflection/refraction, 8 is planet terrain; planet rings just use effects
		Planets = 7,
		PlanetRings = 8,
		// It is used by a class called PlanetRibbonGfx
		TerrainRTT = 9,
		// ModelWorld
		Terrain = 10,
		// BlobShadowManager
		PlanetRibbons1 = 11,
		TerrainModels = 12,
		// ModelWorld
		Level = 13,
		// ??
		BlobShadows = 14,
		PreMain = 15,
		Main = 16,
		CreatureAnim = 17,
		PostMain = 18,
		CreatureFXAnim = 19,
		// ModelWorld
		EffectsMask = 20,

		// 22 screen effects

		UI = 30
	};


	/* Used in editor 
	/// Renders the background model world without shadows.
	kRenderLayerBackground = 0xC,
	/// Renders the creation and the pedestal (with shadows) 
	kRenderLayerPedestalCreation = 0xD,
	// 0x0F  only for paint mode
	// 0x11  pedestal
	// 0x14
	// 0x1A
	*/
	/* Used in effect rendering?
	0x12,
	0x3,
	0x20,
	0x16
	*/
	/* Used by UI Layer Manager
	0x1E,
	*/
	/* Used by Simulator BlobShadowManager
	0xB,
	*/
	/* Used by GGE sub_DDC370
	0x14, 
	0x1A,
	0xD
	*/
	/* Used by GameViewManager
	0xC,
	0xD,
	0x14,
	0x1A,
	0xF,
	// These two are for the anim world
	0xE,
	0x15,
	*/
	/* Related with SpaceGfx 
	5,
	0xD,
	4,
	6,
	*/
	/* Used by cTerrainSphere
	7,  // water reflection & refraction
	8,  // renders land, water, atmosphere, etc
	0x21,  // used by TerrainEditor? 
	0xA,  // modelworld 0x3FBAE24
	*/
	/* Used by Simulator::cPlanetModel
	9,
	0x19
	*/
	/* Used by IShadowWorld
	1 ? added every frame it seems, sub_77FF80
	*/
	//TODO either 5 or 0x12 is clouds, called by cTerrainSphere::RenderWaterReflection
	enum class LayerIndices2
	{
		Clear = 1,

		/// Used by effects renderer
		EffectsBackground = 3,
		Unk4 = 4,  // related with SpaceGfx 
		Unk5 = 5,  // related with SpaceGfx 
		Unk6 = 6,  // related with SpaceGfx 
		/// Renders RTTs used by the planet: water reflection & refraction and scatter map
		TerrainRTT = 7,
		/// Renders planet land, water, atmosphere, etc. Terrain::cTerrainSphere
		Terrain = 8,  
		/// Renders the national boundaries in a planet. Used by `PlanetRibbonGfx` (part of Simulator::cPlanetModel).
		PlanetNationalBoundaries = 9,
		UnkA = 0xA,  // cTerrainSphere, modelworld 0x3FBAE24
		/// Used by Simulator BlobShadowManager
		BlobShadows = 0xB,
		UnkC = 0xC,  // used by: editor, renders the background model world without shadows; GameViewManager
		UnkD = 0xD,  // used by: editor, renders the creation and the pedestal (with shadows); GGE sub_DDC370; GameViewManager; related with SpaceGfx 
		UnkE = 0xE,  // used by: GameViewManager, anim world
		UnkF = 0x0F,  // used by: editor, only for paint mode; GameViewManager

		Unk11 = 0x11,  // used by editor, pedestal
		Unk12 = 0x12,  // used in effect rendering?

		Unk14 = 0x14,  // used by: editor; GGE sub_DDC370; GameViewManager
		Unk15 = 0x15, // used by: GameViewManager, anim world
		/// Used by effects renderer, renders foreground screen effects
		EffectsForeground = 0x16,

		/// Renders the trade route ribbons in a planet. Used by `PlanetRibbonGfx` (part of Simulator::cPlanetModel).
		PlanetTradeRoutes = 0x19,
		Unk1A = 0x1A,  // used by: editor; GGE sub_DDC370; GameViewManager

		Unk1E = 0x1E,  // used in UI Layer Manager

		Unk20 = 0x20,  // used in effect rendering?
		Unk21 = 0x21,  // cTerrainSphere, TerrainEditor?
	};

	///
	/// This class manages the rendering process in the game. It can be used to add IRenderable objects to the render queue.
	/// When added, an index in the queue must be specified; this index is important since defines at which moment the object is
	/// rendered. The minimum index is defined as Graphics::kRenderQueueMain; lower indices are used to render the user interface
	/// and might cause problems.
	///
	/// //TODO Real name: Renderer
	class IRenderer
	{
	public:

		struct cLayerInfo
		{
			ILayerPtr mpRenderable;
			int mIndex;
			int mFlags;
			int field_0C;  // 1 by default,  0x10000 means rendered?
			float field_10;
		};

		// off_14114E0

		virtual int AddRef() = 0;
		virtual int Release() = 0;
		virtual ~IRenderer() = 0;

		//TODO this is totally incomplete!
		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;

		/* 14h */	virtual bool Start(int windowWidth, int windowHeight, bool, int) = 0;

		/* 18h */	virtual void Flip(bool, int, int, int) = 0;

		/* 1Ch */	virtual cScreenInfo& GetScreenInfo() = 0;

		/* 20h */	virtual int GetNumDisplays() = 0;

		/* 24h */	virtual void* func24h() = 0;
		/* 28h */	virtual int func28h(int adapter) = 0;

		/* 2Ch */	virtual void SetViewer(int viewerType, App::cViewer* viewer) = 0;
		/* 30h */	virtual App::cViewer* GetViewer(int viewerType) = 0;

		/* 34h */	virtual void Update(int) = 0;

		/* 38h */	virtual void func38h(bool) = 0;

		// Called in the GraphicsSystem Update method
		/* 3Ch */	virtual void Render(int) = 0;  // calls device Present(), then begins scene and renders everything

		/* 40h */	virtual void SubRender(const RenderStatistics& stats, int startLayer, int endLayer, App::cViewer** viewers, bool, int flags) = 0;  // renders all objects?

		/* 44h */	virtual int func44h() = 0;

		/* 48h */	virtual RenderStatistics GetRenderStats() = 0;

		/// Adds an ILayer object to the specified layer index; the same renderable can be assigned to multiple layers.
		/// If there already was a renderable there, it will get removed.
		/// @param layer Pointer to the renderable layer object
		/// @param layerIndex The index of the layer the given object renders.
		/// @param flags
		/* 4Ch */	virtual void RegisterLayer(ILayer* layer, int layerIndex, int flags = 0) = 0;

		/// Adds a renderable function to the specified layer index; the same renderable can be assigned to multiple layers.
		/// If there already was a renderable there, it will get removed.
		/// @param renderFunction Renderable function, can be a lambdas
		/// @param layerIndex The index of the layer the given object renders.
		/// @param flags
		inline void RegisterLayer(LambdaRenderable::Render_t renderFunction, int layerIndex, int flags = 0)
		{
			RegisterLayer(new LambdaRenderable(renderFunction), layerIndex, flags);
		}

		///
		/// Removes the IRenderable object assigned to the specified layer index.
		/// @param layerIndex
		///
		/* 50h */	virtual bool UnregisterLayer(int layerIndex) = 0;

		/// Removes all renderables from the manager.
		/* 54h */	virtual void ClearAllLayers() = 0;

		/// Returns the renderable assigned to the given layer, or nullptr if there is none.
		/// @param layerIndex 
		/* 58h */	virtual ILayer* Layer(int layerIndex) = 0;

		/* 5Ch */	virtual int SetInfoFlags(int layerIndex, int flags) = 0;  // changes field_0C
		/* 60h */	virtual int ClearInfoFlags(int layerIndex, int flags) = 0;  // changes field_0C
		/* 64h */	virtual int InfoFlags(int layerIndex) = 0;

		/* 68h */	virtual int NumLayers() const = 0;
		/* 6Ch */	virtual ILayer* LayerAtIndex(int index) = 0;
		/* 70h */	virtual cLayerInfo& LayerInfoAtIndex(int index) = 0;

		/// Creates a job that renders the given layer after all layers have been rendered.
		/// @param layer
		/// @param arg
		/// @param jobInfo
		/// @returns ID of the created job
		/* 74h */	virtual uint32_t AddPostRenderJob(ILayer* layer, int arg = 0, const cRenderJobInfo& jobInfo = cRenderJobInfo()) = 0;

		/// Creates a job that renders the given layer before any layers have been rendered.
		/// @param layer
		/// @param arg
		/// @param jobInfo
		/// @returns ID of the created job
		/* 78h */	virtual uint32_t AddPreRenderJob(ILayer* layer, int arg = 0, const cRenderJobInfo& jobInfo = cRenderJobInfo()) = 0;

		/* 7Ch */	virtual void RemovePreRenderJob(uint32_t jobID) = 0;

		/* 80h */	virtual void RemovePostRenderJob(uint32_t jobID) = 0;

		/* 84h */	virtual void BoostRenderJobBudget(int budget) = 0;

		/* 88h */	virtual void func88h() = 0;
		/* 8Ch */	virtual void func8Ch() = 0;

		// 88h, 8Ch used to lock scene, used by sub_F97DF0

		// field 33Ch cViewer

		///
		/// Gets the active renderer.
		///
		static IRenderer* Get();
	};

	inline void GetMousePosition(int& mouseX, int& mouseY) {
		auto params = Renderer.GetScreenInfo();
		mouseX = params.mouseX;
		mouseY = params.mouseY;
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IRenderManager)
	{
		DeclareAddress(Get);
	}
	namespace Addresses(IRenderer)
	{
		DeclareAddress(Get);
	}
}