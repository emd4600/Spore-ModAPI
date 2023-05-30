#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Graphics\CompiledShader.h>
#include <Spore\Graphics\IThumbnailManager.h>
#include <Spore\Graphics\ILightingManager.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\IModelManager.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\IRenderer.h>
#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Graphics\IShadowWorld.h>
#include <Spore\Graphics\cFrustumCull.h>
#include <Spore\Graphics\cModelWorld.h>
#include <Spore\Graphics\RenderUtils.h>
#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Graphics\ShaderDataUniform.h>
#include <Spore\Graphics\GlobalState.h>
#include <Spore\Graphics\ActiveState.h>
#include <Spore\Graphics\BufferDraw.h>

namespace Addresses(Graphics)
{
#ifndef SDK_TO_GHIDRA
	DefineAddress(VertexShaderDataUniforms_ptr, SelectAddress(0x162CE14, 0x1628BA4));
	DefineAddress(PixelShaderDataUniforms_ptr, SelectAddress(0x1624020, 0x161FDB4));	
#else
	DefineAddress(sVertexShaderDataUniforms, SelectAddress(0x162CE14, 0x1628BA4));
	DefineAddress(sPixelShaderDataUniforms, SelectAddress(0x1624020, 0x161FDB4));
#endif

#ifndef SDK_TO_GHIDRA
	DefineAddress(MainColorRTT_ptr, SelectAddress(0x15D4AC8, 0x15D0838));
	DefineAddress(MainDepthRTT_ptr, SelectAddress(0x15D4ACC, 0x15D083C));
#else
	DefineAddress(sMainColorRTT, SelectAddress(0x15D4AC8, 0x15D0838));
	DefineAddress(sMainDepthRTT, SelectAddress(0x15D4ACC, 0x15D083C));
#endif
}

namespace Graphics
{
	namespace Addresses(cMaterialManager)
	{
		DefineAddress(ReadShaderFragments, SelectAddress(0x70F7E0, 0x70F010));
	};

	namespace Addresses(CompiledShader) {
		//DefineAddress(ReadCompiledVertexShaders, SelectAddress(0x6FF950, 0x6FF480));
		//DefineAddress(ReadCompiledPixelShaders, SelectAddress(0x6FC5C0, 0x6FC280));

		DefineAddress(VertexShaders_ptr, SelectAddress(0x162CE90, 0x1628C20));
		DefineAddress(PixelShaders_ptr, SelectAddress(0x161DA88, 0x16198A0));
	}

	namespace Addresses(IThumbnailManager) {
		DefineAddress(Get, SelectAddress(0x67DED0, 0x67DD70));
	}

	namespace Addresses(IGraphicsManager) {
		//DefineAddress(Get, SelectAddress(0x67DE60, , PLACEHOLDER));
	}

	namespace Addresses(ILightingManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEB0, 0x67DD50));
	}

	namespace Addresses(IMaterialManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE90, 0x67DD30));
	}

	namespace Addresses(IModelManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEA0, 0x67DD40));
	}

	namespace Addresses(IModelWorld)
	{
		DefineAddress(LoadModelProperties, SelectAddress(0x74C5D0, 0x74B7D0));
	}

	namespace Addresses(IRenderManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE70, 0x67DD10));
	}
	namespace Addresses(IRenderer)
	{
		DefineAddress(Get, SelectAddress(0x67DE70, 0x67DD10));
	}

	namespace Addresses(IRenderTargetManager) {
		DefineAddress(Get, SelectAddress(0x67DEC0, 0x67DD60));
	}

	namespace Addresses(ITextureManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE80, 0x67DD20));
	}

	namespace Addresses(IShadowManager)
	{
		DefineAddress(Get, SelectAddress(0x67DEE0, 0x67DD80));
	}

	namespace Addresses(IShadowWorld)
	{
		DefineAddress(Get, SelectAddress(0x67DEE0, 0x67DD80));
	}

	namespace Addresses(MaterialShader) 
	{
		DefineAddress(Reset, SelectAddress(0x6E62F0, 0x6E5C40));
		DefineAddress(Initialize, SelectAddress(0x11F6B90, 0x11F4470));
		DefineAddress(GetMaterialShader, SelectAddress(0x11FC770, 0x11FA030));
	}

	namespace Addresses(Model)
	{
		DefineAddress(Release, SelectAddress(0x40F2C0, 0x40F360));
	}

	namespace Renderer_addresses
	{
		DefineAddress(D3D_ptr, SelectAddress(0x16FFCF8, 0x16F89C8));
		DefineAddress(Device_ptr, SelectAddress(0x016FFD00, 0x16F89D0));
		DefineAddress(ShaderData_ptr, SelectAddress(0x016FD8D8, 0x16F65A8));
		DefineAddress(MaterialShader_ptr, SelectAddress(0x016FD898, 0x16F6568));
		DefineAddress(ModelToWorld_ptr, SelectAddress(0x016FF8DC, 0x16F85AC));
		DefineAddress(ModelToWorldTransposed_ptr, SelectAddress(0x1700024, 0x16F8CF4));
		DefineAddress(PresentationParameters_ptr, SelectAddress(0x16FFECC, 0x16F8B9C));

		DefineAddress(SetShaderData, SelectAddress(0x7786E0, 0x777B50));
		DefineAddress(GetShaderDataSize, SelectAddress(0x778C50, 0x7780C0));
		DefineAddress(RegisterShaderData, SelectAddress(0x11F69C0, 0x11F42A0));

		DefineAddress(SetPresentationParameters, SelectAddress(0x11FA450, 0x11F7D30));
		DefineAddress(CreateDevice, SelectAddress(0x11FADF0, 0x11F86B0));

		DefineAddress(SetTexture, SelectAddress(0x11F39D0, 0x11F12A0));
	}
	namespace Addresses(RenderUtils)
	{
		DefineAddress(D3D_ptr, SelectAddress(0x16FFCF8, 0x16F89C8));
		DefineAddress(Device_ptr, SelectAddress(0x016FFD00, 0x16F89D0));
		DefineAddress(ShaderData_ptr, SelectAddress(0x016FD8D8, 0x16F65A8));
		DefineAddress(MaterialShader_ptr, SelectAddress(0x016FD898, 0x16F6568));
		DefineAddress(ModelToWorld_ptr, SelectAddress(0x016FF8DC, 0x16F85AC));
		DefineAddress(ModelToWorldTransposed_ptr, SelectAddress(0x1700024, 0x16F8CF4));
		DefineAddress(PresentationParameters_ptr, SelectAddress(0x16FFECC, 0x16F8B9C));

		DefineAddress(SetShaderData, SelectAddress(0x7786E0, 0x777B50));
		DefineAddress(GetShaderDataSize, SelectAddress(0x778C50, 0x7780C0));
		DefineAddress(RegisterShaderData, SelectAddress(0x11F69C0, 0x11F42A0));

		DefineAddress(SetPresentationParameters, SelectAddress(0x11FA450, 0x11F7D30));
		DefineAddress(CreateDevice, SelectAddress(0x11FADF0, 0x11F86B0));

		DefineAddress(SetTexture, SelectAddress(0x11F39D0, 0x11F12A0));

#ifdef SDK_TO_GHIDRA
		DefineAddress(sD3D, SelectAddress(0x16FFCF8, 0x16F89C8));
		DefineAddress(sDevice, SelectAddress(0x016FFD00, 0x16F89D0));
#endif
	}

	namespace Addresses(ActiveState)
	{
		DefineAddress(sShaderData, SelectAddress(0x016FD8D8, 0x16F65A8));
		DefineAddress(sShader, SelectAddress(0x016FD898, 0x16F6568));
		DefineAddress(sTransform, SelectAddress(0x016FF8DC, 0x16F85AC));
		DefineAddress(sTransposedTransform, SelectAddress(0x1700024, 0x16F8CF4));
		DefineAddress(sPresentParams, SelectAddress(0x16FFECC, 0x16F8B9C));
		DefineAddress(sRasterDelta, SelectAddress(0x16FFE30, 0x16F8B00));
		DefineAddress(SetTexture, SelectAddress(0x11F39D0, 0x11F12A0));
		DefineAddress(SetShaderData, SelectAddress(0x7786E0, 0x777B50));
	}

	namespace Addresses(ShaderBuilder) 
	{
		DefineAddress(ctor, SelectAddress(0x6FD630, 0x6FD310));
		DefineAddress(Read, SelectAddress(0x6FD980, 0x6FD660));
		DefineAddress(Release, SelectAddress(0x6FD6B0, 0x6FD390));

		DefineAddress(Load, SelectAddress(0x6FDB80, 0x6FD860));
	}

	namespace Addresses(StandardShader) 
	{
		DefineAddress(ctor, SelectAddress(0x6E5EF0, 0x6E5840));
		DefineAddress(Read, SelectAddress(0x6E6470, 0x6E5DC0));
		DefineAddress(Reset, SelectAddress(0x6E62F0, 0x6E5C40));
		DefineAddress(Release, SelectAddress(0x6E5EC0, 0x6E5810));

		DefineAddress(Load, SelectAddress(0x6E5C30, 0x6E5590));
	}

	namespace Addresses(GlobalState)
	{
		DefineAddress(D3D9Sync, SelectAddress(0x11F48F0, 0x11F21D0));
		DefineAddress(Dispatch, SelectAddress(0x11F4370, 0x11F1C40));
		DefineAddress(transform_ptr, SelectAddress(0x17016B0, 0x16FA380));
		DefineAddress(transformType_ptr, SelectAddress(0x17009D0, 0x16F96A0));
		DefineAddress(color_ptr, SelectAddress(0x17009D8, 0x16F96A8));
		DefineAddress(softStateDirty_ptr, SelectAddress(0x1700858, 0x16F9528));
		DefineAddress(SetTransform, SelectAddress(0x5295C0, 0x5291F0));
		DefineAddress(renderStates_ptr, SelectAddress(0x01700510, 0x16F91E0));
		DefineAddress(renderStateDirty_ptr, SelectAddress(0x017016BC, 0x16FA38C));

#ifdef SDK_TO_GHIDRA
		DefineAddress(sTransform, SelectAddress(0x17016B0, 0x16FA380));
		DefineAddress(sTransformType, SelectAddress(0x17009D0, 0x16F96A0));
		DefineAddress(sColor, SelectAddress(0x17009D8, 0x16F96A8));
		DefineAddress(sSoftStateDirty, SelectAddress(0x1700858, 0x16F9528));
		DefineAddress(sRenderStates, SelectAddress(0x01700510, 0x16F91E0));
		DefineAddress(sRenderStateDirty, SelectAddress(0x017016BC, 0x16FA38C));
#endif
	}

	namespace Addresses(cBufferDraw)
	{
		DefineAddress(ptr, SelectAddress(0x160B998, 0x1607728));
		DefineAddress(LockVertexBuffer, SelectAddress(0x6DE220, 0x6DDD40));
		DefineAddress(UnlockVertexBuffer, SelectAddress(0x6DE440, 0x6DDF60));
		DefineAddress(UnlockAndDrawMaterial1Texture, SelectAddress(0x6DE2E0, 0x6DDE00));
		DefineAddress(UnlockAndDrawMaterial, SelectAddress(0x6DE2A0, 0x6DDDC0));
		DefineAddress(UnlockAndDrawNoMaterial, SelectAddress(0x6DE270, 0x6DDD90));
	}

	namespace Addresses(cModelWorld)
	{
		DefineAddress(FinishBackgroundLoad, SelectAddress(0x7523E0, 0x7515D0));
		DefineAddress(UpdateWithLODMeshes, SelectAddress(0x74B7C0, 0x74A990));
	}

	namespace Addresses(cFrustumCull)
	{
		DefineAddress(OffsetPlanes, SelectAddress(0x6FFFE0, 0x6FFB10));
		DefineAddress(FrustumTestSphere, SelectAddress(0x700130, 0x6FFC60));
		DefineAddress(FrustumTestAABB, SelectAddress(0x700680, 0x07001B0));
		DefineAddress(UpdateFromProjectionMatrix, SelectAddress(0x700360, 0x6FFE90));
	}
}

#ifdef SDK_TO_GHIDRA
namespace Addresses(Graphics)
{
	DefineAddress(sVertexShaders, SelectAddress(0x162CE90, 0x1628C20));
	DefineAddress(sPixelShaders, SelectAddress(0x161DA88, 0x16198A0));
	DefineAddress(sBufferDraw, SelectAddress(0x160B998, 0x1607728));
}
#endif

#endif
