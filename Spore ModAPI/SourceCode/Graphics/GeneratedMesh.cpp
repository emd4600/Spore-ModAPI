#ifndef MODAPI_DLL_EXPORT
#include <Spore\Graphics\GeneratedMesh.h>

namespace Graphics
{
	using namespace RenderWare;

	const RenderWare::VertexElement PosNormalVertex::ELEMENTS[2] = {
		{0, offsetof(PosNormalVertex, pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, RWDECL_VERTEX_POSITION},
		{0, offsetof(PosNormalVertex, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, RWDECL_VERTEX_NORMAL}
	};

	const RenderWare::VertexElement PosUvVertex::ELEMENTS[2] = {
		{0, offsetof(PosNormalVertex, pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, RWDECL_VERTEX_POSITION},
		{0, offsetof(StandardVertex, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0, RWDECL_VERTEX_TEXCOORD0},
	};

	const RenderWare::VertexElement StandardVertex::ELEMENTS[4] = {
		{0, offsetof(StandardVertex, pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, RWDECL_VERTEX_POSITION},
		{0, offsetof(StandardVertex, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0, RWDECL_VERTEX_TEXCOORD0},
		{0, offsetof(StandardVertex, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, RWDECL_VERTEX_NORMAL},
		{0, offsetof(StandardVertex, tangent), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0, RWDECL_VERTEX_TANGENT}
	};

	const RenderWare::VertexElement StandardVertexCompact::ELEMENTS[4] = {
		{0, offsetof(StandardVertexCompact, pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, RWDECL_VERTEX_POSITION},
		{0, offsetof(StandardVertexCompact, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0, RWDECL_VERTEX_TEXCOORD0},
		{0, offsetof(StandardVertexCompact, normal), D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, RWDECL_VERTEX_NORMAL},
		{0, offsetof(StandardVertexCompact, tangent), D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0, RWDECL_VERTEX_TANGENT}
	};


	GeneratedMesh<PosUvVertex>* GenerateScreenPlane(float z)
	{
		auto mesh = new GeneratedMesh<PosUvVertex>(4, 2);
		mesh->SetVertex(0, { { -1.0f, -1.0f, z }, {0, 1.0f} });
		mesh->SetVertex(1, { { 1.0f, -1.0f, z },  {1.0f, 1.0f} });
		mesh->SetVertex(2, { { -1.0f, 1.0f, z },  {0, 0} });
		mesh->SetVertex(3, { { 1.0f, 1.0f, z },   {1.0f, 0} });
		mesh->SetTriangle(0, 0, 1, 2);
		mesh->SetTriangle(1, 1, 2, 3);
		mesh->SubmitGeometry();
		return mesh;
	}
}
#endif