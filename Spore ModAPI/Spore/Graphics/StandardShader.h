#pragma once

#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\ShaderDataUniform.h>
#include <EASTL\vector.h>
#include <D3D9.h>

namespace Graphics
{
	class StandardShader
		: public MaterialShader
	{
	public:
		StandardShader();

		int Release();

		void Reset();

		bool Read(IO::IStream* pStream, uint32_t shaderID, int version);

		/// This function is called when rendering a mesh, before the \c DrawIndexedPrimitives is called.
		/// This function is responsible of loading the shaders into DirectX.
		static BOOL Load(RenderWare::Mesh* mesh);

	protected:
		/* 48h */	eastl::intrusive_ptr<IDirect3DVertexShader9> mVertexShaders[16];
		/* 88h */	eastl::intrusive_ptr<IDirect3DPixelShader9> mPixelShaders[16];
		/* C8h */	eastl::vector<ShaderDataUniform> mVertexShaderData[16];
		/* 208h */	eastl::vector<ShaderDataUniform> mPixelShaderData[16];
	};
	ASSERT_SIZE(StandardShader, 0x348);

	namespace Addresses(StandardShader) {
		DeclareAddress(ctor);
		DeclareAddress(Read);
		DeclareAddress(Reset);
		DeclareAddress(Release);

		DeclareAddress(Load);
	}
}