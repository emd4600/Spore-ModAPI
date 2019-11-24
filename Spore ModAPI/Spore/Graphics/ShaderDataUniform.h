#pragma once

#include <EASTL\string.h>

namespace Graphics
{
	struct ShaderDataUniform
	{
		short field_0;
		short field_2;
		short field_4;
		short field_6;
		int flags;
	};

	struct NamedShaderDataUniform
	{
		eastl::string name;
		short field_10;
		short field_12;
		short field_14;
		short field_16;
		int flags;
	};
}

namespace Addresses(Graphics)
{
	DeclareAddress(VertexShaderDataUniforms_ptr);
	DeclareAddress(PixelShaderDataUniforms_ptr);
}