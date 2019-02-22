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

/// @file Models.h
/// This file includes all the necessary headers for working with models in Spore.

/// @namespace Graphics
/// This namespace includes classes related to graphics rendering in the game. Some things included are models, textures and
/// materials.

/// 
/// @page models Models
///
/// This page has information about interacting with models. To use them,
/// you need to include the header Models.h
///
/// @tableofcontents
///
/// @section models_tutorial1 Tutorial: Add models to an existing world
///
/// In order for a model to be displayed, it needs to be inside an Graphics::IModelWorld. If you are modifying an existing
/// context (say, for example, the editors) you will probably have access to an exsting model world; if you don't, the next
/// tutorial shows how to create a new model world.
///
/// Loading a new model from the game files and adding it into a model world is really simple, just two lines of code:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // assuming you have a IModelWorld* called 'pModelWorld'
/// // this loads the ep1_altarreligious.prop model in the civicobjects folder.
/// Graphics::Model* pModel = pModelWorld->LoadModel(Hash::FNV("ep1_altarreligious"), Hash::FNV("civicobjects"));
/// pModelWorld->ShowModel(pModel);
/// ~~~~~~~~~~~~~~~~~
/// Check the Graphics::IModelWorld::LoadModel() and Graphics::IModelWorld::ShowModel()
///
/// @section models_tutorial2 Tutorial: Create a new model world
///
/// 1. Create a new model world using the Graphics::IModelManager class. Ensure you set it to visible so it can be seen.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // CreateWorld requires an ID that identifies the model world, it can be anything you want as long as it is unique.
/// IModelWorld* pModelWorld = Graphics::IModelManager::Get()->CreateWorld(0x95f3d2ab);
/// pModelWorld->SetVisible(true);
/// ~~~~~~~~~~~~~~~~~
///
/// 2. The model world must be added into the rendering queue so that it is rendered. This step is not necessary if you use
/// your own IRenderable object and render the world there.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// Graphics::IRenderManager::Get()->AddRenderable(pModelWorld->ToRenderable(), Graphics::kRenderQueueMain);
/// ~~~~~~~~~~~~~~~~~
///
/// @section models_tutorial3 Tutorial: Transforming the model/setting the model invisible
///
/// When a model is loaded, it is set as visible by default. However, not all models must be visible always; to toggle their
/// visibility, use the Graphics::IModelWorld::SetModelVisibility() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // assuming you have a IModelWorld* called 'pModelWorld'
/// pModelWorld->SetModelVisibility(pModel, false);  // 'false' -> invisible, 'true' -> visible
/// ~~~~~~~~~~~~~~~~~
/// The method takes as a parameter pointer to the Model whose visibility must be changed; that's the pointer returned by
/// the LoadModel method, so it's always recommendable to keep it somewhere.
///
/// When a model is loaded, it is located at the origin of coordinates by default, with a scale of 1 (i.e. no scaling) and
/// no rotation. Obviously, it might be convenient to move it somwhere else, or to make it smaller, or to rotate it. For that
/// the Transform class and the Graphics::Model::SetTransform() method are used. That method takes a Transform as an input, which
/// can either come from a 'transform' property in a .PROP file or be created on the code. For example, this code does
/// some transformation to a model:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // pModel is a Model* returned by the LoadModel() method
/// // This set the scale of the model to 0.5f (so it will be half the original size)
/// // and moves it one unit up. As you can see, transformations can be concatenated
/// pModel->SetTransform(Transform().SetScale(0.5f).SetOffset(Math::Vector3(0, 0, 1.0f)));
/// ~~~~~~~~~~~~~~~~~
/// Rotating a transformation can often be counter-intuitive, since it takes a 3x3 matrix. To rotate it with euler values,
/// you must use the Math::EulerToMatrix() and the Math::ToRadians() methods. For example:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // pModel is a Model* returned by the LoadModel() method
/// // This rotates the model 90 degrees in the Y axis. The angles must be in radians.
/// pModel->SetTransform(Transform().SetRotation(Math::EulerToMatrix(Math::Euler(0, Math::ToRadians(90.0f), 0))));
/// ~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - Graphics::IModelWorld
/// - Graphics::IModelManager
/// - Graphics::Model
/// - Transform
///

#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\IRenderManager.h>
#include <Spore\Graphics\ILightingManager.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\ModelAsset.h>
