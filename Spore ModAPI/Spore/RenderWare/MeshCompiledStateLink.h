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

#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\CompiledState.h>

namespace RenderWare
{
	///
	/// This structure links one or more compiled states (that is, materials) to a mesh.
	///
	template <int nCompiledStates = 1>
	struct MeshCompiledStateLink
	{
		MeshCompiledStateLink();

		/* 00h */	Mesh* mpMesh;
		/* 04h */	size_t mnCompiledStatesCount;
		/* 08h */	CompiledState* mpCompiledStates[nCompiledStates];

		static const uint32_t TYPE = 0x2001a;
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	template <int nCompiledStates>
	MeshCompiledStateLink< nCompiledStates>::MeshCompiledStateLink()
		: mpMesh(nullptr)
		, mnCompiledStatesCount(nCompiledStates)
		, mpCompiledStates{}
	{
	}
}