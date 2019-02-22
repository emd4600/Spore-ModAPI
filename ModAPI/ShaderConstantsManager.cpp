#pragma warning(disable : 4351)

#include "ShaderConstantsManager.h"

#include "..\Spore\RenderWare\ShaderConstants.h"

using namespace ModAPI;
using namespace RenderWare;

ShaderConstantsManager::ShaderConstantsManager()
	: constantsDecl_(), registeredConstants_(), nRegisters_(0)
{
}

ShaderConstantsManager::~ShaderConstantsManager()
{
	for (auto decl : allocatedDecls_)
	{
		delete decl;
	}
}

void ShaderConstantsManager::AddSporeConstants()
{
	registeredConstants_[0] = &ShaderConstants::AssignedConstants;
	constantsDecl_[0] = (ShaderConstants::ShaderConstantDecl*) GetAddress(0x1701918, 0x16FB5E8, 0x16FA5E8);
	nRegisters_++;
}

int ShaderConstantsManager::GetRealIndex(int shConstIndex)
{
	return shConstIndex & ((1 << kIndexBits) - 1);
}

int ShaderConstantsManager::GetRegisterIndex(int shConstIndex)
{
	return shConstIndex >> kIndexBits;
}

int ShaderConstantsManager::GetShaderConstantIndex(int registerIndex, int shConstIndex)
{
	return (registerIndex << kIndexBits) | shConstIndex;
}

int ShaderConstantsManager::GetIndex(const char* name)
{
	int registerIndex = 0;
	for (auto constMap : registeredConstants_)
	{
		if (registerIndex >= nRegisters_) {
			break;
		}

		auto it = constMap->find(name);
		if (it != constMap->end())
		{
			return GetShaderConstantIndex(registerIndex, it->second);
		}

		registerIndex++;
	}
	return 0;
}

int ShaderConstantsManager::Register(ShaderConstants::ShaderConstantsMap* shaderConstants)
{
	if (nRegisters_ == kMaxConstantRegisters)
	{
		throw std::exception("All ModAPI shader constant registers are in use.");
	}

	registeredConstants_[nRegisters_] = shaderConstants;
	constantsDecl_[nRegisters_] = new RenderWare::ShaderConstants::ShaderConstantDecl[kMaxConstants];

	nRegisters_++;

	return nRegisters_ - 1;
}

ShaderConstants::ShaderConstantDecl* ShaderConstantsManager::GetDeclarations(int registerIndex)
{
	return constantsDecl_[registerIndex];
}