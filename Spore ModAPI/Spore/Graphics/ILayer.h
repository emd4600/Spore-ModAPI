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

#define ILayerPtr eastl::intrusive_ptr<Graphics::ILayer>

namespace Graphics
{
	/// This interfaces defines a layer that is rendered every game loop, by callings its ILayer::DrawLayer() method.
	/// Layers are rendered by the IRenderer in an ordered way, on top of each other.
	class ILayer
	{
	public:
		virtual int AddRef() = 0;
		virtual int Release() = 0;
		virtual ~ILayer() {};

		/// Renders this layer.
		/// @param flags The flags this layer was registered with, combined with the global render flags.
		/// @param layerIndex The layer index this layer was registered with.
		/// @param viewers
		/// @param statistics
		virtual void DrawLayer(int flags, int layerIndex, App::cViewer** viewers, RenderStatistics& statistics) = 0;
	};
}