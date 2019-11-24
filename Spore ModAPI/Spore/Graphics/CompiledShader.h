#pragma once

#include <Spore\Graphics\ShaderDataUniform.h>
#include <EASTL\intrusive_ptr.h>
#include <d3d9.h>

namespace Graphics
{
	using namespace eastl;

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

	static_assert(sizeof(PixelShader) == 0x130, "sizeof(Shader) != 130h");

	namespace Addresses(CompiledShader) {
		//DeclareAddress(ReadCompiledVertexShaders);
		//DeclareAddress(ReadCompiledPixelShaders);

		DeclareAddress(VertexShaders_ptr);
		DeclareAddress(PixelShaders_ptr);
	}

	inline vector<VertexShader>& GetVertexShaders() {
		return *(vector<VertexShader>*)(GetAddress(CompiledShader, VertexShaders_ptr));
	}

	inline vector<PixelShader>& GetPixelShaders() {
		return *(vector<PixelShader>*)(GetAddress(CompiledShader, PixelShaders_ptr));
	}

	void ReadCompiledVertexShaders(IO::IStream* pStream);
	void ReadCompiledPixelShaders(IO::IStream* pStream);
}