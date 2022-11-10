#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\ShaderDataUniform.h>
#include <Spore\IO.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\vector.h>
#include <d3d9.h>

namespace Graphics
{
	template <typename T> class CompiledShader
	{
	public:
		static const int MAX_SHADER_CONSTANTS = 32;

		CompiledShader();

	public:
		/* 00h */	uint8_t mFragmentIndices[32];
		/* 20h */	T* mpDXShader;
		int field_24;
		/* 28h */	int mDataCount;
		/* 2Ch */	NamedShaderDataUniform* mShaderData[MAX_SHADER_CONSTANTS];
		/* ACh */	int mStartRegisters[MAX_SHADER_CONSTANTS];
		/* 12Ch */	int mDataFlags;
	};

	typedef CompiledShader<IDirect3DVertexShader9> VertexShader;
	typedef CompiledShader<IDirect3DPixelShader9> PixelShader;

	ASSERT_SIZE(PixelShader, 0x130);

	namespace Addresses(CompiledShader) {
		//DeclareAddress(ReadCompiledVertexShaders);
		//DeclareAddress(ReadCompiledPixelShaders);

		DeclareAddress(VertexShaders_ptr);
		DeclareAddress(PixelShaders_ptr);
	}

	inline eastl::vector<VertexShader>& GetVertexShaders() {
		return *(eastl::vector<VertexShader>*)(GetAddress(CompiledShader, VertexShaders_ptr));
	}

	inline eastl::vector<PixelShader>& GetPixelShaders() {
		return *(eastl::vector<PixelShader>*)(GetAddress(CompiledShader, PixelShaders_ptr));
	}

	void ReadCompiledVertexShaders(IO::IStream* pStream);
	void ReadCompiledPixelShaders(IO::IStream* pStream);
}