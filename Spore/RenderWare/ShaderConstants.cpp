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

#include <Spore\RenderWare\ShaderConstants.h>
#include <ModAPI\MainUtilities.h>
#include <ModAPI\ShaderConstantsManager.h>

void RenderWare::ShaderConstants::RegisterShaderConstant(int index, ProcessCallback pFunc1, ProcessCallback pFunc2, ProcessCallback pFunc3, LoadValuesCallback pLoadValues)
{
	ShaderConstantDecl* decls = ModAPI::ModAPIUtils::GetShaderConstantsManager()->GetDeclarations(ModAPI::ShaderConstantsManager::GetRegisterIndex(index));
	if (decls == nullptr)
	{
		STATIC_CALL(GetAddress(0x11F69C0, 0x11F42A0, 0x11F42A0), void,
			PARAMS(int index, ProcessCallback pFunc1, ProcessCallback pFunc2, ProcessCallback pFunc3, LoadValuesCallback pLoadValues),
			PARAMS(index, pFunc1, pFunc2, pFunc3, pLoadValues));
	}
	else
	{
		int realIndex = ModAPI::ShaderConstantsManager::GetRealIndex(index);
		
		decls[realIndex].index = index;
		decls[realIndex].field_04 = 0;
		decls[realIndex].field_08 = 0;
		decls[realIndex].field_0C = 0;
		decls[realIndex].field_10 = pFunc1;
		decls[realIndex].field_14 = pFunc2;
		decls[realIndex].field_18 = pFunc3;
		decls[realIndex].pLoadValues = pLoadValues;
	}
}