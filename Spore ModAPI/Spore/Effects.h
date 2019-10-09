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

/// @file Effects.h
/// This file includes all the necessary headers to use the Swarm effect system in Spore.

#include <Spore\Swarm\ISwarmManager.h>
#include <Spore\Swarm\IEffect.h>
#include <Spore\Swarm\IEffectWorld.h>

/// @namespace Swarm
///
/// This namespace contains all the necessary classes needed for working with the Swarm effect system.
/// The main class is the Swarm::ISwarmManager, which is used to control everything related with the system.
/// Swarm::IEffect classes are instances of the effects which can be sued to display and transform effects in the game.ç
///

/// 
/// @page effects Effects
///
/// This page has information about interacting with the Swarm effect system. To use it,
/// you need to include the header Effects.h
///
/// @tableofcontents
///
/// @section effects_tutorial1 Tutorial: Create an instance of an effect
///
/// Creating a new instance of an effect, so it can be displayed, is really simple. You just have to use the 
/// Swarm::ISwarmManager::CreateEffect() method to create an instance, and then use the Swarm::IEffect::Show() method
/// to start showing it. When you are done with it, use Swarm::IEffect::Kill() to destroy the instance.
///
/// ~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
/// intrusive_ptr<IEffect> pEffect;
/// if (Swarm::ISwarmManager::Get()->CreateEffect(Hash::FNV("SG_ufo_scan_HitGround"), 0, pEffect))
/// {
///		// This will only be executed if the effect existed and a new instance was created
///		pEffect->Show();
/// }
/// ~~~~~~~~~~~~~~~~~~~~~~~~
///
/// When an effect is loaded, it is located at the origin of coordinates by default, with a scale of 1 (i.e. no scaling) and
/// no rotation. Obviously, it might be convenient to move it somwhere else, or to make it smaller, or to rotate it. For that
/// the Transform class and the Swarm::IEffect::SetTransform() method are used. That method takes a Transform as an input, which
/// can either come from a 'transform' property in a .PROP file or be created on the code. For example, this code does
/// some transformation to an effect:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // pEffect is an intrusive_ptr<IEffect> returned by the CreateEffect() method
/// // This set the scale of the effect to 0.5f (so it will be half the original size)
/// // and moves it one unit up. As you can see, transformations can be concatenated
/// pEffect->SetTransform(Transform().SetScale(0.5f).SetOffset(Math::Vector3(0, 0, 1.0f)));
/// ~~~~~~~~~~~~~~~~~
/// Rotating a transformation can often be counter-intuitive, since it takes a 3x3 matrix. To rotate it with euler values,
/// you must use the Math::EulerToMatrix() and the Math::ToRadians() methods. For example:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // pEffect is an intrusive_ptr<IEffect> returned by the CreateEffect() method
/// // This rotates the effect 90 degrees in the Y axis. The angles must be in radians.
/// pEffect->SetTransform(Transform().SetRotation(Math::EulerToMatrix(Math::Euler(0, Math::ToRadians(90.0f), 0))));
/// ~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - Swarm::ISwarmManager
/// - Swarm::IEffect
/// - Swarm::IEffectWorld
/// - Swarm
///
