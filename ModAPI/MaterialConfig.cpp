#include "MaterialConfig.h"
#include "CompiledStateBuilder.h"
#include "..\Spore\RenderWare\Material.h"
#include "..\Spore\Graphics\MaterialManager.h"
#include "MainUtilities.h"

// only for debugging
#include <Windows.h>

using namespace ModAPI;


MaterialConfig::MaterialConfig()
	:
	name(), materialID(), useMaterialColor(false), useAmbientColor(false), renderStates(), shaderConstants(), primitiveType(4),
	materialColor(), ambientColor()
{
}

MaterialConfig::~MaterialConfig()
{
	for (ShaderConstant* shConst : shaderConstants)
	{
		delete shConst;
	}
}

int MaterialConfig::AddRef()
{
	return refCount_++;
}

int MaterialConfig::Release()
{
	if (refCount_-- <= 0)
	{
		delete this;
	}
	return refCount_;
}

MaterialConfig::ShaderConstant::ShaderConstant()
	: offset(), data(), index()
{
}


MaterialConfig::ShaderConstant::~ShaderConstant()
{
	for (DataValue<void*>* value : data)
	{
		delete value;
	}
}



RenderWare::CompiledState* MaterialConfig::CreateCompiledState()
{
	CompiledStateBuilder stream = CompiledStateBuilder();

	int flags1 = 0;
	int	flags2 = 0;
	int	flags3 = 0;

	// always used ? don't really know what it does
	flags1 |= 4;
	flags2 |= 0x8000;


	if (this->useMaterialColor)
	{
		flags1 |= static_cast<int>(RenderWare::CompiledState::Flags::UseMaterialColor);
	}
	if (this->useAmbientColor)
	{
		flags1 |= static_cast<int>(RenderWare::CompiledState::Flags::UseAmbientColor);
	}
	//TODO unknown booleans
	
	if (!this->shaderConstants.empty())
	{
		flags1 |= static_cast<int>(RenderWare::CompiledState::Flags::UseShaderConstants);
		flags2 |= static_cast<int>(RenderWare::CompiledState::Flags::UseShaderConstants);
	}

	if (!this->renderStates.empty())
	{
		flags3 |= static_cast<int>(RenderWare::CompiledState::Flags3::UseRenderStates);
	}
	
	if (!this->textureSlots.empty())
	{
		flags3 |= static_cast<int>(RenderWare::CompiledState::Flags3::UseTextureSlots);
	}


	stream.Write<int>(0);  // size
	stream.Write<int>(this->primitiveType);
	stream.Write<int>(flags1);
	stream.Write<int>(flags2);
	stream.Write<int>(flags3);
	stream.Write<int>(0);  // field_14, also used as flags ?
	stream.Write<RenderWare::Material*>(RenderWare::Material::GetMaterial(this->materialID));
	stream.Write<int>(0);  // just padding

	// here would go the vertex description

	if (!this->shaderConstants.empty())
	{
		for (auto shConst : this->shaderConstants)
		{
			stream.Write<short>(shConst->index);
			stream.Write<short>(shConst->offset);
			stream.Write<int>(0);  // the size, we'll do it later

			int dataStart = stream.GetOffset();
			for (auto value : shConst->data)
			{
				value->Write(&stream);
			}
			int dataEnd = stream.GetOffset();

			// go back and set the size
			stream.SetOffset(dataStart - 4);
			stream.Write<int>(dataEnd - dataStart);
			stream.SetOffset(dataEnd);
		}

		stream.Write<int>(0);
		stream.Write<int>(0);
	}

	if (this->useMaterialColor)
	{
		stream.Write<float>(this->materialColor.r);
		stream.Write<float>(this->materialColor.g);
		stream.Write<float>(this->materialColor.b);
		stream.Write<float>(this->materialColor.a);
	}
	if (this->useAmbientColor)
	{
		stream.Write<float>(this->ambientColor.r);
		stream.Write<float>(this->ambientColor.g);
		stream.Write<float>(this->ambientColor.b);
	}

	//TODO here go the unknown booleans

	if (!this->renderStates.empty())
	{
		stream.Write<int>(0);

		for (auto state : this->renderStates)
		{
			stream.Write<int>(state.first);
			stream.Write<int>(state.second);
		}

		stream.Write<int>(-1);
		stream.Write<int>(-1);
	}

	// here go the texture slots
	if (!this->textureSlots.empty())
	{
		stream.Write<int>(-1);

		for (TextureSlot* slot : this->textureSlots)
		{
			stream.Write<int>(slot->samplerIndex);
			stream.Write<int>(0);  // no texture set for now

			stream.Write<int>(slot->stageStatesUnknown);
			if (slot->stageStatesUnknown != 0)
			{
				for (auto state : slot->stageStates)
				{
					stream.Write<int>(state.first);
					stream.Write<int>(state.second);
				}

				stream.Write<int>(-1);
			}

			stream.Write<int>(slot->samplerStatesUnknown);
			if (slot->samplerStatesUnknown != 0)
			{
				for (auto state : slot->samplerStates)
				{
					stream.Write<int>(state.first);
					stream.Write<int>(state.second);
				}

				stream.Write<int>(-1);
			}
		}

		stream.Write<int>(-1);
	}

	int streamSize = stream.GetSize();

	stream.SetOffset(0);
	stream.Write<int>(streamSize);

	//char* buffer = new char[stream.GetSize()];

	// CompiledState must be aligned
	char* buffer = (char*)_aligned_malloc(streamSize, 16);
	stream.CopyBuffer(buffer);

	return (RenderWare::CompiledState*) buffer;
}

Graphics::Material* MaterialConfig::AddSporeMaterial(Graphics::Material* material)
{
	if (material == nullptr) {
		return nullptr;
	}

	Graphics::Material* dstMaterial = Graphics::MaterialManager::GetMaterialManager()->GetMaterial(material->materialID);

	dstMaterial->nCompiledStates = material->nCompiledStates;
	for (int i = 0; i < material->nCompiledStates; i++) {
		dstMaterial->compiledStates[i] = material->compiledStates[i];
	}

	//dstMaterial->textures.insert(dstMaterial->textures.end(), material->textures.begin(), material->textures.end());
	for (unsigned int i = 0; i < material->textures.size(); i++)
	{
		dstMaterial->textures.push_back(material->textures[i]);
	}

	return dstMaterial;
}