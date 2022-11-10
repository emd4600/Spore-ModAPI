#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\RenderWare\CompiledState.h>
#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\Raster.h>
#include <Spore\RenderWare\RWHeader.h>
#include <Spore\RenderWare\VertexDescription.h>

namespace RenderWare
{
	namespace Addresses(TextureSlot)
	{
		DefineAddress(SetTexture, SelectAddress(0x00FC2ED0, 0x00FC27A0, 0x00FC27A0));
	}

	namespace Addresses(CompiledState)
	{
		DefineAddress(Load, SelectAddress(0x011F0D00, 0x011EE5D0, 0x011EE5D0));
		DefineAddress(GetRaster, SelectAddress(0x011F0FF0, 0x011EE8C0, 0x11EE8C0));
		DefineAddress(SetRaster, SelectAddress(0x011F0E30, 0x011EE700, 0x011EE700));
	}

	namespace Addresses(Mesh)
	{
		DefineAddress(CalculateTriangleCount, SelectAddress(0x011FBD30, 0x011F95F0, 0x011F95F0));
		DefineAddress(SetIndexBuffer, SelectAddress(0x011FBE50, 0x011F9710, 0x011F9710));
		DefineAddress(SetIndicesCount, SelectAddress(0x011FBE20, 0x011F96E0, 0x011F96E0));
		DefineAddress(SetVertexBuffer, SelectAddress(0x011FBDE0, 0x011F96A0, 0x011F96A0));
		DefineAddress(Render, SelectAddress(0x011FBE80, 0x011F9740, 0x011F9740));
	}

	namespace Addresses(Raster)
	{
		DefineAddress(Create, SelectAddress(0x11F22E0, , 0x11EFBB0));
		DefineAddress(Delete, SelectAddress(0x11F26E0, , 0x11EFFB0));
		DefineAddress(CreateRaster, SelectAddress(0x11F2630, , 0x11EFF00));
		DefineAddress(D3D9AddToUnmanagedList, SelectAddress(0x11F1E90, , 0x11EF760));
		DefineAddress(Extract, SelectAddress(0x11F2BC0, , 0x11F0490));
		DefineAddress(Fill, SelectAddress(0x11F29F0, , 0x11F02C0));
		DefineAddress(D3D9GetStreamedMipLevelSize, SelectAddress(0x11F2780, , 0x11F0050));
	};

	namespace Addresses(RWHeader)
	{
		DefineAddress(GetRWObject, SelectAddress(0x11E5060, , 0x11E2920));
	}

	namespace Addresses(VertexDescription)
	{
		DefineAddress(LoadDeclaration, SelectAddress(0x011F5310, 0x11F2BF0, 0x11F2BF0));
		DefineAddress(Process, SelectAddress(0x11F5350, 0x11F2C30, 0x11F2C30));
	}
}
#endif
