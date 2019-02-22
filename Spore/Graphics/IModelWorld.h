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

#include <cstdint>

#include <Spore\Graphics\ModelAsset.h>
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\App\PropertyList.h>

namespace Graphics
{
	///
	/// A model world is a space where models can be rendered in the game. Model worlds keep track of all the models
	/// loaded in order to render them when the model world itself is rendered. A world can also contain multiple
	/// lighting worlds; for more information, check the ILightingWorld interface. When no lighting worlds are added
	/// a default lighting is used.
	///
	/// In order for the model world to render, you must add it to the render queue. This step is not necessary
	/// if the IRenderable::Render() method is called directly from another renderer. For example:
	/// ~~~~~~~~~~~~~~{.cpp}
	/// Graphics::IRenderManager::Get()->AddRenderable(pModelWorld->ToRenderable(), Graphics::kRenderQueueMain);
	/// ~~~~~~~~~~~~~~
	/// You might use greater render queue indices, like Graphics::kRenderQueueMain + 1. An example of this would be 
	/// having a model world for translucid objects, which need to be rendered last. 
	///
	class IModelWorld
	{
	public:
		enum ModelWorldFlags {
			kBuildDrawLists = 0x00000100,
			kUpdateLOD = 0x00000200,
			kUseOccluders = 0x00000400,
			kSetState = 0x00000800,
			kDrawOpaque = 0x00001000,
			kDrawAlpha = 0x00002000,
			kDrawDebug = 0x00004000,
			kNoSort = 0x00008000,
			kForceOpaque = 0x00010000,

			kRenderAll = 0x00007f00,
			kRenderAllNoLOD = 0x00007d00,
		};

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		virtual ~IModelWorld() {};

		///
		/// Loads a model from the resources system with the given instance and group ID.
		/// Keep in mind that a model refers to the configuration file (i.e. the .prop file) which includes the 
		/// model files for each level of detail, the effects that must be used, etc.
		/// If the model configuration does not exist, a builtin model might be used.
		/// @param instanceID
		/// @param groupID
		///
		/* 0Ch */	virtual Model* LoadModel(uint32_t instanceID, uint32_t groupID, int arg_8 = 0) = 0;

		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual int func14h() = 0;
		/* 18h */	virtual int func18h() = 0;
		/* 1Ch */	virtual int func1Ch() = 0;
		/* 20h */	virtual int func20h() = 0;
		/* 24h */	virtual int func24h() = 0;
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual int func2Ch() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual int func34h() = 0;
		/* 38h */	virtual int func38h() = 0;
		/* 3Ch */	virtual int func3Ch() = 0;
		/* 40h */	virtual int func40h() = 0;
		/* 44h */	virtual int func44h() = 0;
		/* 48h */	virtual int func48h() = 0;
		/* 4Ch */	virtual int func4Ch() = 0;
		/* 50h */	virtual int func50h() = 0;
		/* 54h */	virtual int func54h() = 0;

		///
		/// Although this function is not necessary and it's usage is not really known, it's recommended to use
		/// it on every model loaded to avoid delays when those are displayed for the firt time
		/// @param pModel
		///
		/* 58h */	virtual void ShowModel(Model* pModel) = 0;

		/* 5Ch */	virtual int func5Ch() = 0;
		/* 60h */	virtual int func60h() = 0;
		/* 64h */	virtual int func64h() = 0;
		/* 68h */	virtual int func68h() = 0;
		/* 6Ch */	virtual int func6Ch() = 0;
		/* 70h */	virtual int func70h() = 0;
		/* 74h */	virtual int func74h() = 0;
		/* 78h */	virtual int func78h() = 0;
		/* 7Ch */	virtual int func7Ch() = 0;
		/* 80h */	virtual int func80h() = 0;
		/* 84h */	virtual int func84h() = 0;
		/* 88h */	virtual int func88h() = 0;
		/* 8Ch */	virtual int func8Ch() = 0;
		/* 90h */	virtual int func90h() = 0;
		/* 94h */	virtual int func94h() = 0;
		/* 98h */	virtual int func98h() = 0;
		/* 9Ch */	virtual int func9Ch() = 0;
		/* A0h */	virtual int funcA0h() = 0;
		/* A4h */	virtual int funcA4h() = 0;
		/* A8h */	virtual int funcA8h() = 0;
		/* ACh */	virtual int funcACh() = 0;
		/* B0h */	virtual int funcB0h() = 0;
		/* B4h */	virtual int funcB4h() = 0;
		/* B8h */	virtual int funcB8h() = 0;
		/* BCh */	virtual int funcBCh() = 0;
		/* C0h */	virtual int funcC0h() = 0;
		/* C4h */	virtual int funcC4h() = 0;
		/* C8h */	virtual int funcC8h() = 0;
		/* CCh */	virtual int funcCCh() = 0;
		/* D0h */	virtual int funcD0h() = 0;
		/* D4h */	virtual int funcD4h() = 0;
		/* D8h */	virtual int funcD8h() = 0;
		/* DCh */	virtual int funcDCh() = 0;
		/* E0h */	virtual int funcE0h() = 0;
		/* E4h */	virtual int funcE4h() = 0;
		/* E8h */	virtual int funcE8h() = 0;
		/* ECh */	virtual int funcECh() = 0;
		/* F0h */	virtual int funcF0h() = 0;
		/* F4h */	virtual int funcF4h() = 0;
		/* F8h */	virtual int funcF8h() = 0;
		/* FCh */	virtual int funcFCh() = 0;
		/* 100h */	virtual int func100h() = 0;
		/* 104h */	virtual int func104h() = 0;
		/* 108h */	virtual int func108h() = 0;
		/* 10Ch */	virtual int func10Ch() = 0;
		/* 110h */	virtual int func110h() = 0;
		/* 114h */	virtual int func114h() = 0;
		/* 118h */	virtual int func118h() = 0;
		/* 11Ch */	virtual int func11Ch() = 0;
		/* 120h */	virtual int func120h() = 0;
		/* 124h */	virtual int func124h() = 0;  // something related with PlanetModelDepthOffset ?
		/* 128h */	virtual int func128h() = 0;
		/* 12Ch */	virtual int func12Ch() = 0;
		/* 130h */	virtual int func130h() = 0;

		///
		/// Toggles the visibility of all the world, including the lighting and all the models contained.
		/// @param bVisible Whether the world must be visible or not.
		///
		/* 134h */	virtual void SetVisible(bool bVisible) = 0;

		/* 138h */	virtual int func138h() = 0;

		///
		/// Returns the IRenderable object that can be used to render this model world.
		///
		/* 13Ch */	virtual IRenderable* ToRenderable() = 0;

		/* 140h */	virtual int AddLightingWorld(ILightingWorld* pWorld, int, bool) = 0;


		/* 144h */	virtual int func144h() = 0;
		/* 148h */	virtual int func148h() = 0;
		/* 14Ch */	virtual int func14Ch() = 0;
		/* 150h */	virtual int func150h() = 0;
		/* 154h */	virtual int func154h() = 0;
		/* 158h */	virtual int func158h() = 0;
		/* 15Ch */	virtual int func15Ch() = 0;
		/* 160h */	virtual int func160h() = 0;
		/* 164h */	virtual int func164h() = 0;
		/* 168h */	virtual int func168h() = 0;

		///
		/// Changes the visibility of a given model inside this world.
		/// @param pModel The model to set visible/invisible, which must be included inside this world.
		/// @param bVisible Whether the model must be visible or not.
		///
		/* 16Ch */	virtual bool SetModelVisibility(Model* pModel, bool bVisible) = 0;

		/* 170h */	virtual void DestroyModel(Model* pModel, bool) = 0;  // ?

		/* 174h */	virtual bool Initialize() = 0;
		/* 178h */	virtual bool Dispose() = 0;

		///
		/// Assigns the required flags to the given IModelWorld depending on the groupID specified.
		/// @param pWorld The model world to modify.
		/// @param groupID The ID of the model group, in the ModelGroups enum.
		///
		static void SetGroup(IModelWorld* pWorld, uint32_t groupID);

	protected:
		void LoadModelProperties(const App::PropertyList* pPropList, ModelAsset* pAsset, int nFlags, int arg_C);

		// /* 19Ch */	intrusive_list<ModelAsset> ??

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace InternalAddressList(IModelWorld)
	{
		DefineAddress(LoadModelProperties, GetAddress(0x74C5D0, 0x74B7D0, 0x74B7D0));
	}

}