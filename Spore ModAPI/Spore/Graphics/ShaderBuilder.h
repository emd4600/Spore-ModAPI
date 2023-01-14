#pragma once

#include <Spore\Graphics\MaterialShader.h>
#include <EASTL\vector.h>

namespace Graphics
{
	struct ShaderBuilderEntry
	{
		uint8_t index;
		uint16_t data[3];
		uint32_t vertexFlags;
		uint32_t requiredFlags;
		uint32_t excludedFlags;
		uint32_t flags;
		int8_t field_18;  // -1
	};

	class ShaderBuilder
		: public MaterialShader
	{
	public:
		ShaderBuilder();

		int Release();

		bool Read(IO::IStream* pStream, uint32_t shaderID, int version);

		/// This function is called when rendering a mesh, before the \c DrawIndexedPrimitives is called.
		/// This function is responsible of loading the shaders into DirectX.
		static BOOL Load(RenderWare::Mesh* mesh);

	protected:
		/* 48h */	eastl::vector<ShaderBuilderEntry> mVertexShaders[16];
		/* 188h */	eastl::vector<ShaderBuilderEntry> mPixelShaders[16];
	};
	ASSERT_SIZE(ShaderBuilder, 0x2C8);

	namespace Addresses(ShaderBuilder) {
		DeclareAddress(ctor);
		DeclareAddress(Read);
		DeclareAddress(Release);

		DeclareAddress(Load);
	}
}