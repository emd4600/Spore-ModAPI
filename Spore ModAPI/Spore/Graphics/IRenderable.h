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

#include <Spore\App\cViewer.h>
#include <Spore\Graphics\RenderStatistics.h>

#define IRenderablePtr eastl::intrusive_ptr<Graphics::IRenderable>

namespace Graphics
{
	///
	/// This interface defines an object that can be rendered, and whose render method is called on every game loop.
	///
	class IRenderable
	{
	public:
		virtual int AddRef() = 0;
		virtual int Release() = 0;
		virtual ~IRenderable() {};

		// arg_8 is a pointer to a pointer to a cViewer
		///
		/// @param flags The flags this renderable was registered with, combined with the global render flags.
		/// @param layerIndex The layer index this renderable was registered with.
		/// @param arg_8
		/// @param statistics
		virtual void Render(int flags, int layerIndex, App::cViewer** arg_8, RenderStatistics& statistics) = 0;
	};
}