#include "stdafx.h"
#include "AnimEditorBlocks.h"

const Color BLOCKS_COLOR = 0xFFd6d489;
const Color SELECTED_BLOCKS_COLOR = 0xFFFF0000;

const RenderWare::VertexElement AnimEditorBlocks::Vertex::ELEMENTS[4] = {
		{0, offsetof(Vertex, pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, Graphics::RWDECL_VERTEX_POSITION},
		{0, offsetof(Vertex, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, Graphics::RWDECL_VERTEX_NORMAL},
		{0, offsetof(Vertex, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0, Graphics::RWDECL_VERTEX_TEXCOORD0},
		{0, offsetof(Vertex, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0, Graphics::RWDECL_VERTEX_COLOR}
};

int TRIANGLES[][3] = {
	{ 0, 1, 2 }, { 0, 2, 3 },
	{ 4, 6, 5 }, { 4, 7, 6 },
	{ 8, 11, 10 }, { 8, 10, 9 },
	{ 15, 12, 13 }, { 15, 13, 14 },
	{ 19, 16, 17 }, { 19, 17, 18 },
	{ 20, 23, 22 }, { 20, 22, 21 }
};

Vector3 VERTEX_POSITIONS[] = {
	// TOP FACE
	{ 1.0f, 1.0f, 1.0f },
	{ -1.0f, 1.0f, 1.0f },
	{ -1.0f, -1.0f, 1.0f },
	{ 1.0f, -1.0f, 1.0f },
	// BOTTOM FACE
	{ 1.0f, 1.0f, -1.0f },
	{ -1.0f, 1.0f, -1.0f },
	{ -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f },
	// RIGHT FACE
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, 1.0f },
	// LEFT FACE
	{ -1.0f, 1.0f, 1.0f },
	{ -1.0f, 1.0f, -1.0f },
	{ -1.0f, -1.0f, -1.0f },
	{ -1.0f, -1.0f, 1.0f },
	// FRONT FACE
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, -1.0f },
	{ -1.0f, 1.0f, -1.0f },
	{ -1.0f, 1.0f, 1.0f },
	// BACK FACE
	{ 1.0f, -1.0f, 1.0f },
	{ 1.0f, -1.0f, -1.0f },
	{ -1.0f, -1.0f, -1.0f },
	{ -1.0f, -1.0f, 1.0f }
};

Vector2 VERTEX_TEXCOORDS[] = {
	{ 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 1.0f }
};

Vector3 FACE_NORMALS[] = {
	Z_AXIS, -Z_AXIS, X_AXIS, -X_AXIS, Y_AXIS, -Y_AXIS
};

const int VERTICES_PER_MESH = 6 * 4;
const int TRIANGLES_PER_MESH = 6 * 2;

void AnimEditorBlocks::GenerateMesh(Anim::anim_cid* cid)
{
	mp_cid = cid;
	unsigned int numBlocks = cid->blocks.size();
	mpMesh = new Graphics::GeneratedMesh<Vertex>(numBlocks * VERTICES_PER_MESH, numBlocks * TRIANGLES_PER_MESH);

	for (unsigned int i = 0; i < numBlocks; ++i)
	{
		auto& block = cid->blocks[i];
		Vector3 dir = block.pBlock->bboxDirection;
		GenerateBlockMesh(i, dir);
	}

	mpMesh->SubmitGeometry();
}

void AnimEditorBlocks::GenerateBlockMesh(int submeshIndex, const Vector3& dir)
{
	Vertex vertex;
	vertex.color = BLOCKS_COLOR;
	for (unsigned int i = 0; i < 6; ++i)
	{
		vertex.normal = FACE_NORMALS[i];

		for (int j = 0; j < 4; ++j) {
			int index = i * 4 + j;
			vertex.uv = VERTEX_TEXCOORDS[j];
			vertex.pos = VERTEX_POSITIONS[index];
			vertex.pos = Vector3(vertex.pos.x * dir.x, vertex.pos.y * dir.y, vertex.pos.z * dir.z);
			mpMesh->SetVertex(index + submeshIndex * VERTICES_PER_MESH, vertex);
		}

		int v = submeshIndex * VERTICES_PER_MESH;

		int* triangle = TRIANGLES[i * 2];
		mpMesh->SetTriangle(submeshIndex * TRIANGLES_PER_MESH + i * 2, v + triangle[0], v + triangle[1], v + triangle[2]);

		triangle = TRIANGLES[i * 2 + 1];
		mpMesh->SetTriangle(submeshIndex * TRIANGLES_PER_MESH + i * 2 + 1, v + triangle[0], v + triangle[1], v + triangle[2]);
	}

	mpMesh->AddMaterial(0xB660F636, submeshIndex * TRIANGLES_PER_MESH * 3, TRIANGLES_PER_MESH * 3);
}

void AnimEditorBlocks::Render()
{
	unsigned int numBlocks = mp_cid->blocks.size();
	for (unsigned int i = 0; i < numBlocks; ++i)
	{
		auto& block = mp_cid->blocks[i];
		Vector3 center = block.bboxCenter - Vector3(-3.0f, 0, 0);

		mpMesh->SetTransform(i, Transform().SetOffset(center).SetRotation(block.orientation).ToMatrix4());
		mpMesh->SetColor(i, { 1.0f, 0.0f, 0.0f, 1.0f });
	}

	if (mpMesh) {
		mpMesh->Render();
	}
}