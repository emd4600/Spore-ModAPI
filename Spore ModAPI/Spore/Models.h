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

/// @namespace RenderWare
///
/// @brief The representation of `.rw4` models/textures/materials


#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\IRenderManager.h>
#include <Spore\Graphics\ILightingManager.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\ModelAsset.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Graphics\Renderer.h>
#include <Spore\Graphics\GlobalState.h>