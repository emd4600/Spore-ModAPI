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
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\LambdaRenderable.h>


/// Access the active render manager.
#define RenderManager (*Graphics::IRenderManager::Get())

#define IRenderManagerPtr intrusive_ptr<Graphics::IRenderManager>

namespace Graphics
{
	using namespace eastl;

	struct RenderererParams
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

	///
	/// This class manages the rendering process in the game. It can be used to add IRenderable objects to the render queue.
	/// When added, an index in the queue must be specified; this index is important since defines at which moment the object is
	/// rendered. The minimum index is defined as Graphics::kRenderQueueMain; lower indices are used to render the user interface
	/// and might cause problems.
	///
	class IRenderManager
	{
	public:

		struct RenderLayer
		{
			IRenderablePtr mpRenderable;
			int mIndex;
			int mFlags;
			int field_0C;  // 1 by default,  0x10000 means rendered?
			float field_10;
		};

		// off_14114E0

		virtual int AddRef() = 0;
		virtual int Release() = 0;
		virtual ~IRenderManager() = 0;

		//TODO this is totally incomplete!
		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual int func14h() = 0;
		/* 18h */	virtual int func18h() = 0;
		/* 1Ch */	virtual RenderererParams& GetParameters() = 0;
		/* 20h */	virtual int GetAdapterCount() = 0;
		/* 24h */	virtual int func24h() = 0;
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual int func2Ch() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual int func34h() = 0;
		/* 38h */	virtual int func38h() = 0;
		// Called in the GraphicsSystem Update method
		/* 3Ch */	virtual int func3Ch() = 0;  // calls device Present(), then begins scene and renders everything
		/* 40h */	virtual int RenderLayers(int, int startLayer, int endLayer, int, bool, int flags) = 0;  // renders all objects?
		/* 44h */	virtual int func44h() = 0;
		/* 48h */	virtual int func48h() = 0;

		/// Adds a IRenderable object to the specified queue index; the same renderable can be assigned to multiple layers.
		/// If there already was a renderable there, it will get removed.
		/// @param object Pointer to the renderable object
		/// @param layerIndex The index of the layer the given object renders.
		/// @param flags
		/* 4Ch */	virtual void AddRenderable(IRenderable* object, int layerIndex, int flags = 0) = 0;

		/// Adds a renderable function to the specified queue index; the same renderable can be assigned to multiple layers.
		/// If there already was a renderable there, it will get removed.
		/// @param renderFunction Renderable function, can be a lambdas
		/// @param layerIndex The index of the layer the given object renders.
		/// @param flags
		inline void AddRenderable(LambdaRenderable::Render_t renderFunction, int layerIndex, int flags = 0)
		{
			AddRenderable(new LambdaRenderable(renderFunction), layerIndex, flags);
		}

		///
		/// Removes the IRenderable object assigned to the specified queue index.
		/// @param nQueueIndex
		///
		/* 50h */	virtual bool RemoveRenderable(int nQueueIndex) = 0;

		/// Removes all renderables from the manager.
		/* 54h */	virtual void ClearRenderables() = 0;

		/// Returns the renderable assigned to the given layer, or nullptr if there is none.
		/// @param layerIndex 
		/* 58h */	virtual IRenderable* GetRenderable(int layerIndex) = 0;

		/* 5Ch */	virtual int AddRenderableExtraFlags(int layerIndex, int flags) = 0;  // changes field_0C
		/* 60h */	virtual int RemoveRenderableExtraFlags(int layerIndex, int flags) = 0;  // changes field_0C
		/* 64h */	virtual int GetRenderableExtraFlags(int layerIndex) = 0;
		/* 68h */	virtual int GetRenderablesCount() const = 0;
		/* 6Ch */	virtual IRenderable* GetRenderableAt(int index) = 0;
		/* 70h */	virtual RenderLayer& GetRenderLayerAt(int index) = 0;

		// 80h update?

		// field 33Ch cViewer

		///
		/// Gets the active render manager.
		///
		static IRenderManager* Get();
	};

	inline void GetMousePosition(int& mouseX, int& mouseY) {
		auto params = RenderManager.GetParameters();
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
}