#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Graphics\CompiledShader.h>
#include <Spore\Graphics\IGraphicsManager.h>
#include <Spore\Graphics\ILightingManager.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\IRenderManager.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Graphics\Renderer.h>
#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Graphics\ShaderDataUniform.h>

namespace Addresses(Graphics)
{
	DefineAddress(VertexShaderDataUniforms_ptr, SelectAddress(0x162CE14, , 0x1628BA4));
	DefineAddress(PixelShaderDataUniforms_ptr, SelectAddress(0x1624020, , 0x161FDB4));
}

namespace Graphics
{
	namespace Addresses(cMaterialManager)
	{
		DefineAddress(ReadShaderFragments, SelectAddress(0x70F7E0, , 0x70F010));
	};

	namespace Addresses(CompiledShader) {
		//DefineAddress(ReadCompiledVertexShaders, SelectAddress(0x6FF950, , 0x6FF480));
		//DefineAddress(ReadCompiledPixelShaders, SelectAddress(0x6FC5C0, , 0x6FC280));

		DefineAddress(VertexShaders_ptr, SelectAddress(0x162CE90, , 0x1628C20));
		DefineAddress(PixelShaders_ptr, SelectAddress(0x161DA88, , 0x16198A0));
	}

	namespace Addresses(IGraphicsManager) {
		//DefineAddress(Get, SelectAddress(0x67DE60, , PLACEHOLDER));
	}

	namespace Addresses(ILightingManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEB0, 0x67DD50, 0x67DD50));
	}

	namespace Addresses(IMaterialManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE90, 0x67DD30, 0x67DD30));
	}

	namespace Addresses(IModelManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEA0, 0x67DD40, 0x67DD40));
	}

	namespace Addresses(IModelWorld)
	{
		DefineAddress(LoadModelProperties, SelectAddress(0x74C5D0, 0x74B7D0, 0x74B7D0));
	}

	namespace Addresses(IRenderManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE70, 0x67DD10, 0x67DD10));
	}

	namespace Addresses(IRenderTargetManager) {
		DefineAddress(Get, SelectAddress(0x67DEC0, , 0x67DD60));
	}

	DefineAddress(MainColorRTT_ptr, SelectAddress(0x15D4AC8, , 0x15D0838));
	DefineAddress(MainDepthRTT_ptr, SelectAddress(0x15D4ACC, , 0x15D083C));

	namespace Addresses(ITextureManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE80, 0x67DD20, 0x67DD20));
	}

	namespace Addresses(MaterialShader) 
	{
		DefineAddress(Reset, SelectAddress(0x6E62F0, , 0x6E5C40));
		DefineAddress(Initialize, SelectAddress(0x11F6B90, 0x11F4470, 0x11F4470));
		DefineAddress(GetMaterialShader, SelectAddress(0x11FC770, 0x11FA030, 0x11FA030));
	}

	namespace Addresses(Model)
	{
		DefineAddress(Release, SelectAddress(0x40F2C0, 0x40F360, 0x40F360));
	}

	namespace Addresses(Renderer) 
	{
		DefineAddress(D3D_ptr, SelectAddress(0x16FFCF8, , 0x16F89C8));
		DefineAddress(Device_ptr, SelectAddress(0x016FFD00, 0x16F99D0, 0x16F89D0));
		DefineAddress(ShaderData_ptr, SelectAddress(0x016FD8D8, 0x16F75A8, 0x16F65A8));
		DefineAddress(MaterialShader_ptr, SelectAddress(0x016FD898, 0x16F7568, 0x16F6568));
		DefineAddress(ModelToWorld_ptr, SelectAddress(0x016FF8DC, 0x16F95AC, 0x16F85AC));
		DefineAddress(ModelToWorldTransposed_ptr, SelectAddress(0x1700024, 0x16F9CF4, 0x16F8CF4));
		DefineAddress(PresentationParameters_ptr, SelectAddress(0x16FFECC,, 0x16F8B9C));

		DefineAddress(SetShaderData, SelectAddress(0x7786E0, 0x777B50, 0x777B50));
		DefineAddress(GetShaderDataSize, SelectAddress(0x778C50, , 0x7780C0));
		DefineAddress(RegisterShaderData, SelectAddress(0x11F69C0, , 0x11F42A0));

		DefineAddress(SetPresentationParameters, SelectAddress(0x11FA450, , 0x11F7D30));
		DefineAddress(CreateDevice, SelectAddress(0x11FADF0, , 0x11F86B0));

		DefineAddress(SetTexture, SelectAddress(0x11F39D0, , 0x11F12A0));
	}

	namespace Addresses(ShaderBuilder) 
	{
		DefineAddress(ctor, SelectAddress(0x6FD630, , 0x6FD310));
		DefineAddress(Read, SelectAddress(0x6FD980, , 0x6FD660));
		DefineAddress(Release, SelectAddress(0x6FD6B0, , 0x6FD390));

		DefineAddress(Load, SelectAddress(0x6FDB80, , 0x6FD860));
	}

	namespace Addresses(StandardShader) 
	{
		DefineAddress(ctor, SelectAddress(0x6E5EF0, , 0x6E5840));
		DefineAddress(Read, SelectAddress(0x6E6470, , 0x6E5DC0));
		DefineAddress(Reset, SelectAddress(0x6E62F0, , 0x6E5C40));
		DefineAddress(Release, SelectAddress(0x6E5EC0, , 0x6E5810));

		DefineAddress(Load, SelectAddress(0x6E5C30, , 0x6E5590));
	}
}
#endif
