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

#include <Spore\RenderWare\RenderWareFile.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\StandardShader.h>
#include <Spore\Graphics\ShaderBuilder.h>
#include <Spore\Object.h>
#include <Spore\Clock.h>
#include <Spore\Mutex.h>

#include <EASTL\hash_map.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

namespace Graphics
{
	class UnkMatManager
	{
	protected:
		/* 00h */	int field_00;
		/* 04h */	int field_04;
		/* 08h */	eastl::hash_map<int, int> field_08;
		/* 28h */	eastl::hash_map<int, int> field_28;
		/* 48h */	eastl::hash_map<int, int> field_48;
		/* 68h */	eastl::hash_map<int, int> field_68;
		/* 88h */	eastl::vector<eastl::intrusive_ptr<StandardShader>> mStandardShaders;
		/* 9Ch */	eastl::hash_map<int, int> field_9C;
		// They are only added here if they are outside the 0x70000000 - 0x80000000 range
		/* BCh */	eastl::hash_map<uint32_t, eastl::intrusive_ptr<StandardShader>> mStandardShadersMap;
		/* DCh */	eastl::vector<eastl::intrusive_ptr<ShaderBuilder>> mShaderBuilders;
		// They are only added here if they are outside the 0x70000000 - 0x80000000 range
		/* F0h */	eastl::hash_map<uint32_t, eastl::intrusive_ptr<ShaderBuilder>> mShaderBuildersMap;
		/* 110h */	eastl::string field_110;
		/* 120h */	char field_120[0x1C];  // not initialized
		/* 13Ch */	eastl::hash_map<int, int> field_13C;

		friend class cMaterialManager;
	};


	///
	/// The implementation of IMaterialManager; this should only be used for extending and detouring.
	///
	class cMaterialManager : public IMaterialManager, public IVirtual
	{
	public:
		bool ReadCompiledShadersImpl(IO::IStream* pStream);
		bool ReadMaterialsImpl(IO::IStream* pLinkStream, RenderWare::RenderWareFile* pRenderWare);

		bool ReadShaderFragments(Resource::Database* pDatabase);

	public:

		/* 08h */	int mnRefCount;
		/* 0Ch */	int field_0C;
		/* 10h */	UnkMatManager field_10;
		/* 16Ch */	int field_16C;  // not initialized
		/* 170h */	int field_170;  // not initialized
		/* 174h */	eastl::hash_map<uint32_t, Material> mMaterials;
		/* 194h */	eastl::hash_map<RenderWare::CompiledState*, uint32_t> field_194;
		/* 1B4h */	RenderWare::CompiledState* mpDefaultCompiledState;
		/* 1B8h */	bool field_1B8;
		/* 1BCh */	int _padding_1BC[4];
		/* 1CCh */	int field_1CC;  // 1
		/* 1D0h */	int field_1D0;  // -1
		/* 1D4h */	int field_1D4; 
		/* 1D8h */	eastl::fixed_vector<int, 4> field_1D8;
		/* 200h */	int mShaderPath;
		/* 204h */	eastl::intrusive_ptr<RenderWare::RenderWareFile> mpCompiledStatesFile;
		/* 208h */	Clock field_208;
		/* 220h */	int field_220;
		/* 224h */	int field_224;
		/* 228h */	int field_228;
		/* 22Ch */	int field_22C;
		/* 230h */	int field_230;
		/* 234h */	int field_234;
		/* 238h */	int field_238;
		/* 23Ch */	bool field_23C;
		/* 240h */	int field_240;  // 0x200
		/* 244h */	eastl::vector<MaterialPtr> mTexturedMaterials;
		/* 258h */	Mutex mMaterialsMutex;
	};
	
	namespace Addresses(cMaterialManager) 
	{
		DeclareAddress(ReadShaderFragments);
	};
}