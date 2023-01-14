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
///
/// @brief All the graphics system: rendering, shaders, models, lighting, textures,... 
///
/// This namespace includes classes related to graphics rendering in the game. Some things included are models, textures and
/// materials.
/// 
/// This namespace is deeply related with the RenderWare namespace; elements in Graphics are high-level representations,
/// easy to use, whereas RenderWare elements are low-level representations which are not needed to modify in most cases.
/// - Graphics::Model represents a 3D model made of triangulated meshes. It uses objects like RenderWare::VertexBuffer, RenderWare::IndexBuffer, RenderWare::Animations,...
/// - Graphics::Texture represents a game texture, which can be 2D or 3D (cube textures). It uses RenderWare::Raster.
/// - Graphics::Material contains the information of how a model mesh must be painted, that is, which shaders and textures it uses. It uses RenderWare::CompiledState

/// @namespace RenderWare
///
/// @brief The representation of `.rw4` models/textures/materials


#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\IRenderer.h>
#include <Spore\Graphics\ILightingManager.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Graphics\RenderUtils.h>
#include <Spore\Graphics\GlobalState.h>
#include <Spore\Graphics\ActiveState.h>
#include <Spore\Graphics\BufferDraw.h>