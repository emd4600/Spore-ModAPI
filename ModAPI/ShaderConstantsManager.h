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

#include <EASTL\vector.h>
#include <Spore\RenderWare\ShaderConstants.h>

namespace ModAPI
{
	using namespace RenderWare;

	class ShaderConstantsManager
	{
	public:
		ShaderConstantsManager();
		~ShaderConstantsManager();

		int GetIndex(const char* name);
		int Register(ShaderConstants::ShaderConstantsMap* shaderConstants);

		ShaderConstants::ShaderConstantDecl* GetDeclarations(int registerIndex);

		static int GetRealIndex(int shConstIndex);
		static int GetRegisterIndex(int shConstIndex);
		static int GetShaderConstantIndex(int registerIndex, int shConstIndex);

		void AddSporeConstants();

	private:
		// A ShConst index is 16 bit long. The first 10 bits are the index itself
		static const int kIndexBits = 10;
		static const int kRegisterIndexBits = 6;

	public:
		static const int kMaxConstantRegisters = 1 << kRegisterIndexBits;  // 64 = 2^6
		static const int kMaxConstants = 1024;

	private:
		int nRegisters_;
		ShaderConstants::ShaderConstantsMap* registeredConstants_[kMaxConstantRegisters];
		ShaderConstants::ShaderConstantDecl* constantsDecl_[kMaxConstantRegisters];

		// here we store all decls that must be deleted
		eastl::vector<ShaderConstants::ShaderConstantDecl*> allocatedDecls_;
	};
}