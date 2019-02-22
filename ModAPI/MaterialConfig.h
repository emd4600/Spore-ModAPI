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
#include <EASTL\vector_map.h>
#include <EASTL\map.h>
#include <map>
#include <EASTL\string.h>
#include <EASTL\intrusive_ptr.h>

#include <Spore\MathUtils.h>
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\Line.h>
#include <Spore\RenderWare\CompiledState.h>
#include <Spore\Graphics\IMaterialManager.h>

using namespace eastl;

namespace ModAPI
{
	class CompiledStateBuilder;

	class MaterialConfig
	{
	public:
		struct ShaderConstant;
		struct TextureSlot;

		// typedef eastl::vector_map<unsigned long, intrusive_ptr<MaterialConfig>> MaterialMap;

		MaterialConfig();
		virtual ~MaterialConfig();

		string name;

		unsigned long materialID;
		int primitiveType;

		bool useMaterialColor;
		bool useAmbientColor;
		Math::ColorRGBA materialColor;
		Math::ColorRGB ambientColor;

		vector_map<int, int> renderStates;

		vector<ShaderConstant*> shaderConstants;
		vector<TextureSlot*> textureSlots;

		virtual int AddRef();
		virtual int Release();


		RenderWare::CompiledState* CreateCompiledState();

		static Graphics::Material* AddSporeMaterial(Graphics::Material* material);

		struct ShaderConstant
		{
			template<typename T>
			struct DataValue
			{
				DataValue(T value_)
					: value(value_)
				{
				}

				T value;

				inline void Write(ModAPI::CompiledStateBuilder* stream)
				{
					stream->Write<T>(value);
				}
			};

			ShaderConstant();
			~ShaderConstant();

			int index;
			int offset;
			vector<DataValue<void*>*> data;
		};

		struct TextureSlot
		{
			int samplerIndex;
			int stageStatesUnknown;
			int samplerStatesUnknown;

			vector_map<int, int> stageStates;
			vector_map<int, int> samplerStates;
		};

	private:
		int refCount_;

		static inline void writeInt(char* data, int& ptr, int value)
		{
			*(int*)(data + ptr) = value;
		}
	};
}