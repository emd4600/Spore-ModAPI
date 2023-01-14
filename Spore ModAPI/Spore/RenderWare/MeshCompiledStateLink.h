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
	/// By default this only links one material; more materials can be used with MeshCompiledStateLink_
	///
	struct MeshCompiledStateLink
	{
		MeshCompiledStateLink();

		/* 00h */	Mesh* mpMesh;
		/* 04h */	size_t mCompiledStatesCount;
		/* 08h */	CompiledState* mpCompiledStates[1];

		static const uint32_t RW_TYPE = 0x2001a;
	};

	template <int nCompiledStates = 1>
	struct MeshCompiledStateLink_ : public MeshCompiledStateLink
	{
		MeshCompiledStateLink_();

	private:
		int padding[nCompiledStates-1];
	};

	template <int nCompiledStates>
	inline MeshCompiledStateLink_<nCompiledStates>::MeshCompiledStateLink_()
		: MeshCompiledStateLink()
		, padding{}
	{
		mCompiledStatesCount = nCompiledStates;
	}
}