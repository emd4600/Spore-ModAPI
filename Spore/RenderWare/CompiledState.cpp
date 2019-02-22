/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include "CompiledState.h"
#include "VertexDescription.h"

#define HAS_FLAG(value, flag) (value & flag) != 0
#define FIELD(ptr, offset) *(int*)((char*)ptr + offset)
#define FIELD_SHORT(ptr, offset) *(short*)((char*)ptr + offset)

using namespace RenderWare;

void CompiledState::processData(CompiledState* data, RenderWareFile* renderWare)
{
	// does something with 18h
	// usual flags 0000 0000 0001 0000 1000 0000 0001 1100

	char* esi = (char*)((reinterpret_cast<int>(data)+0x1B) & ~15);

	if (data->flags != 0)
	{
		if (HAS_FLAG(data->flags, 1))
		{
			if (HAS_FLAG(data->flags, 2))
			{
				*(int*)esi = reinterpret_cast<int>(renderWare->getObject(*(int*)esi));
				esi += 4;
			}
			else
			{
				esi += 0x40;
			}
		}

		// Vertex description
		if (HAS_FLAG(data->flags, (int)CompiledState::Flags::UseVertexDescription))
		{
			// process vertex description (Spore loads the elements, don't need to make this here)
			esi += ((reinterpret_cast<VertexDescription*>(esi))->elementsCount + 2) * sizeof(VertexElement);
		}

		if (HAS_FLAG(data->flags, (int)CompiledState::Flags::UseShaderConstants))
		{
			// here come the shader constants

			char* edi = esi;

			// checks flags in *esi, but rarely happens
			while (*(short*)(edi = esi) != 0)
			{
				esi += 8;
				if (FIELD_SHORT(edi, 0) > 0)
				{
					short shaderConstantIndex = FIELD_SHORT(edi, 0);
					esi += FIELD_SHORT(edi, 2);
					// executes shaderConstants[shaderConstantIndex].field_18(esi, renderWare);
					esi += FIELD(edi, 4);
				}
				else
				{
					FIELD(esi, 0) = reinterpret_cast<int>(renderWare->getObject(FIELD(esi, 0)));
					if (FIELD(esi, 0) == 0)
					{
						// FIELD(esi, 0) = shaderConstants[shaderConstantIndex].field_C
					}
					esi += 4;
				}
			}
		}

		// materialColor
		if (HAS_FLAG(data->flags, (int)CompiledState::Flags::UseMaterialColor))
		{
			esi += 0x10;
		}

		// ambientColor
		if (HAS_FLAG(data->flags, (int)CompiledState::Flags::UseAmbientColor))
		{
			esi += 0xC;
		}

		int ebx = data->flags & 0x3FC0;  // 0xFF << 6;
		if (ebx != 0)
		{
			for (int i = 0; i < 8; i++)
			{
				if (HAS_FLAG(data->flags, 1 << (6 + i)))
				{
					FIELD(esi, 0) = reinterpret_cast<int>(renderWare->getObject(FIELD(esi, 0)));
					esi += 4;
				}
			}
		}

		if (HAS_FLAG(data->flags, (int)CompiledState::Flags::UseBooleans))
		{
			esi += 0x11;
		}

		if (HAS_FLAG(data->flags, 0xF0000))
		{
			if (HAS_FLAG(data->flags, 0x10000))
			{
				// used in shader constant 0x25
				esi += 4;
			}

			if (HAS_FLAG(data->flags, 0xE0000))
			{
				if (HAS_FLAG(data->flags, 0x20000))
				{
					// used in shader constant 0x24
					esi += 0xC;
				}
				if (HAS_FLAG(data->flags, 0x40000))
				{
					// used in shader constant 0x25 too
					esi += 4;
				}
				if (HAS_FLAG(data->flags, 0x80000))
				{
					// used in shader constant 0x25 too
					esi += 4;
				}
			}
		}
	}

	if (data->field_14 != 0)
	{
		if (HAS_FLAG(data->field_14, 0x20000))
		{
			esi += 0x1C;
		}
		if (HAS_FLAG(data->field_14, 0x40000))
		{
			esi += 0x44;
		}
		if (HAS_FLAG(data->field_14, 0x80000))
		{
			esi += 0x44;
		}
	}

	// RenderStates
	if (HAS_FLAG(data->field_10, 0x20000))
	{
		esi += 4;

		// Warning: I think it's not exactly this!
		StateValue* renderStates = (StateValue*)esi;
		int i = -1;
		do {
			esi += sizeof(StateValue);
			i++;
		} while (renderStates[i].state != -1 && renderStates[i].value != -1);
	}

	if (HAS_FLAG(data->field_10, 0x100000))
	{
		if (FIELD(esi, 0) != -1)
		{
			FIELD(esi, 0) = reinterpret_cast<int>(renderWare->getObject(FIELD(esi, 0)));
		}
	}

	// Texture Slots
	if (HAS_FLAG(data->field_10, 0xDFFFF))
	{
		esi += 8;

		while (true)
		{
			if (FIELD(esi, 0) != -1)
			{
				// Raster*
				FIELD(esi, 0) = reinterpret_cast<int>(renderWare->getObject(FIELD(esi, 0)));
			}

			// usually 0x3F
			int hasStageStates = FIELD(esi, 0);
			esi += 4;
			esi += 4;

			if (hasStageStates != 0)
			{
				StateValue* stageStates = (StateValue*)esi;
				int i = 0;
				while (stageStates[i++].state != -1) {
					esi += 8;
				}
				esi += 4;
			}

			// usually 0x73
			int hasSamplerStates = FIELD(esi, 0);
			esi += 4;

			if (hasSamplerStates != 0)
			{
				StateValue* samplerStates = (StateValue*)esi;
				int i = 0;
				while (samplerStates[i++].state != -1) {
					esi += 8;
				}
				esi += 4;
			}

			if (FIELD(esi, 0) == -1) {
				esi += 4;
				break;
			}
			else {
				esi += 4;
			}
		}
	}
}