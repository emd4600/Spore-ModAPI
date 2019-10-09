#pragma once

#include <Spore\Graphics\MaterialShader.h>
#include <Spore\Graphics\ShaderDataUniform.h>
#include <EASTL\vector.h>
#include <D3D9.h>

using namespace eastl;

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
		static BOOL Load(RenderWare::Mesh<>* mesh);

	protected:
		/* 48h */	intrusive_ptr<IDirect3DVertexShader9> mVertexShaders[16];
		/* 88h */	intrusive_ptr<IDirect3DPixelShader9> mPixelShaders[16];
		/* C8h */	vector<ShaderDataUniform> mVertexShaderData[16];
		/* 208h */	vector<ShaderDataUniform> mPixelShaderData[16];
	};

	static_assert(sizeof(StandardShader) == 0x348, "sizeof(StandardShader) != 0x348");

	namespace Addresses(StandardShader) {
		DeclareAddress(ctor, SelectAddress(0x6E5EF0, , 0x6E5840));
		DeclareAddress(Read, SelectAddress(0x6E6470, , 0x6E5DC0));
		DeclareAddress(Reset, SelectAddress(0x6E62F0, , 0x6E5C40));
		DeclareAddress(Release, SelectAddress(0x6E5EC0, , 0x6E5810));

		DeclareAddress(Load, SelectAddress(0x6E5C30, , 0x6E5590));
	}
}