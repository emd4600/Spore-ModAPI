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

#include "..\Internal.h"
#include <EASTL\map.h>

#define SHADER_CONSTANT_CALLBACK(name) static void __cdecl name(int startRegister, int registerSize, RenderWare::ShaderConstants::ShaderType type)

namespace RenderWare
{
	namespace ShaderConstants
	{
		// There are up to 2048 shader constant indices, but apparently above 1024 they give trouble

		struct ConstantMapComparator {
			bool operator() (const char* lhs, const char* rhs) const {
				return _stricmp(lhs, rhs) < 0;
			}
		};

		typedef eastl::map<const char*, int, ConstantMapComparator> ShaderConstantsMap;

		static ShaderConstantsMap AssignedConstants = {
			{ "skinWeights", 0x003 },
			{ "skinBones", 0x004 },
			{ "modelToClip", 0x006 },
			{ "modelToCamera", 0x007 },
			{ "modelToWorld", 0x008 },
			{ "worldToClip", 0x00C },
			{ "cameraToWorld", 0x00D },
			{ "cameraToWorldTranspose", 0x010 },
			{ "worldCameraPosition", 0x01F },
			{ "worldCameraDirection", 0x021 },
			{ "materialColor", 0x022 },
			{ "ambient", 0x023 },
			{ "time", 0x027 },

			{ "objectTypeColor", 0x202 },
			{ "frameInfo", 0x203 },
			{ "screenInfo", 0x204 },
			{ "customParams", 0x206 },
			{ "materialParams", 0x210 },
			{ "uvTweak", 0x211 },
			{ "dirLightsWorld", 0x214 },
			{ "shCoeffs", 0x21A },
			// 0x219 to display buildings and creatures?
			{ "expandAmount", 0x220 },
			{ "shadowMapInfo", 0x223 },
			{ "foggingCPU", 0x225 },
			{ "patchLocation", 0x226 },
			{ "viewTransform", 0x252 },
			{ "pcaTexture", 0x22f },
			{ "renderDepth", 0x231 },
			{ "gameInfo", 0x248 },

			{ "terrainTint", 0x233 },
			{ "terrainBrushCubeMatRot", 0x241 },
			{ "terrainSynthParams", 0x242 },
			{ "ramp", 0x24A },

			{ "terrainLighting", 0x24C },
			{ "worldToPatch", 0x23D },
			{ "beachColor", 0x250 },
			{ "cliffColor", 0x251 },
			{ "terrainTransform", 0x301 },
			{ "decalState", 0x304 },
			{ "terrainState", 0x305 },

			{ "ModAPIShader", 0x3FF }
		};

		enum class ShaderType
		{
			PIXEL_SHADER = 0,
			VERTEX_SHADER = 1
		};
		typedef void(__cdecl*LoadValuesCallback)(int startRegister, int registerSize, ShaderType shaderType);
		typedef void(__cdecl*ProcessCallback)(void* renderWare, void* data);

		static void __cdecl DefaultProcess(void* renderWare, void* data) {};

		extern void RegisterShaderConstant(int index, ProcessCallback pFunc1, ProcessCallback pFunc2, ProcessCallback pFunc3, LoadValuesCallback pLoadValues);

		/*{
			STATIC_CALL(GetAddress(0x11F69C0, 0), void,
				PARAMS(int index, ProcessCallback func1, ProcessCallback func2, ProcessCallback func3, LoadValuesCallback pLoadValues),
				PARAMS(index, func1, func2, func3, pLoadValues));
		}*/

		struct ShaderConstantDecl
		{
			short index;
			int field_04;
			int field_08;
			int field_0C;
			ProcessCallback field_10;
			ProcessCallback field_14;
			ProcessCallback field_18;
			LoadValuesCallback pLoadValues;
		};

		static_assert(sizeof(ShaderConstantDecl) == 0x20, "sizeof(ShaderConstantDecl) != 20h");
	}
}