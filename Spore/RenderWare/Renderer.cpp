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

#include <Spore\RenderWare\Renderer.h>
#include <ModAPI\MainUtilities.h>
#include <ModAPI\ShaderConstantsManager.h>

using namespace RenderWare;

void Renderer::LoadVertexShaderConstants(int renderFlags, bool shaderChanged)
{
	VertexShader* vertexShader = Renderer::GetVertexShader();
	if (shaderChanged)
	{
		renderFlags |= vertexShader->field_12C;
	}

	if (renderFlags & vertexShader->field_12C)
	{
		for (int i = 0; i < vertexShader->constantsCount; i++)
		{
			if (vertexShader->constants[i]->field_18 & renderFlags)
			{
				if ((vertexShader->constants[i]->field_18 & 8) && !shaderChanged)
				{
					int flag = 1 << (vertexShader->constants[i]->field_12 & 0x1F);
					if (((int*)GetAddress(0x16FFD28, 0x16F99F8, 0x16F89F8))[vertexShader->constants[i]->field_12 >> 5] & flag)
					{
						continue;
					}
				}
				ModAPI::ShaderConstantsManager* manager = ModAPI::ModAPIUtils::GetShaderConstantsManager();
				int registerIndex = ModAPI::ShaderConstantsManager::GetRegisterIndex(vertexShader->constants[i]->constantIndex);
				auto decls = manager->GetDeclarations(registerIndex);
				if (decls != nullptr)
				{
					decls[ModAPI::ShaderConstantsManager::GetRealIndex(vertexShader->constants[i]->constantIndex)].pLoadValues(
						vertexShader->startRegisters[i], vertexShader->constants[i]->registerSize, ShaderConstants::ShaderType::VERTEX_SHADER);
				}
			}
		}
	}
}

void Renderer::LoadPixelShaderConstants(int renderFlags, bool shaderChanged)
{
	PixelShader* pixelShader = Renderer::GetPixelShader();
	if (shaderChanged)
	{
		renderFlags |= pixelShader->field_12C;
	}

	if (renderFlags & pixelShader->field_12C)
	{
		for (int i = 0; i < pixelShader->constantsCount; i++)
		{
			if (pixelShader->constants[i]->field_18 & renderFlags)
			{
				if ((pixelShader->constants[i]->field_18 & 8) && !shaderChanged)
				{
					int flag = 1 << (pixelShader->constants[i]->field_12 & 0x1F);
					if (((int*)GetAddress(0x16FFD28, 0x16F99F8, 0x16F89F8))[pixelShader->constants[i]->field_12 >> 5] & flag)
					{
						continue;
					}
				}
				ModAPI::ShaderConstantsManager* manager = ModAPI::ModAPIUtils::GetShaderConstantsManager();
				int registerIndex = ModAPI::ShaderConstantsManager::GetRegisterIndex(pixelShader->constants[i]->constantIndex);
				auto decls = manager->GetDeclarations(registerIndex);
				if (decls != nullptr)
				{
					decls[ModAPI::ShaderConstantsManager::GetRealIndex(pixelShader->constants[i]->constantIndex)].pLoadValues(
						pixelShader->startRegisters[i], pixelShader->constants[i]->registerSize, ShaderConstants::ShaderType::PIXEL_SHADER);
				}
			}
		}
	}
}