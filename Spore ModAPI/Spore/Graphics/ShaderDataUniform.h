#pragma once

#include <EASTL\string.h>
#include <Spore\Internal.h>

namespace Graphics
{
	struct ShaderDataUniform
	{
		short dataIndex;
		short field_2;
		short registerSize;
		short registerIndex;
		int flags;
	};

	struct NamedShaderDataUniform
	{
		eastl::string name;
		short dataIndex;
		short field_12;
		short registerSize;
		short registerIndex;
		int flags;
	};
}

namespace Addresses(Graphics)
{
	DeclareAddress(VertexShaderDataUniforms_ptr);
	DeclareAddress(PixelShaderDataUniforms_ptr);
}

#ifdef SDK_TO_GHIDRA
namespace Graphics
{
	NamedShaderDataUniform* sVertexShaderDataUniforms;
	NamedShaderDataUniform* sPixelShaderDataUniforms;
}
#endif
