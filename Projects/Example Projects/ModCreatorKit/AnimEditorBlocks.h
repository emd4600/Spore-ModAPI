#pragma once

#include <Spore\Anim\AnimatedCreature.h>
#include <Spore\Graphics\GeneratedMesh.h>
#include <Spore\Object.h>

#define AnimEditorBlocksPtr eastl::intrusive_ptr<AnimEditorBlocks>

class AnimEditorBlocks
	: public DefaultRefCounted
{
public:
	void GenerateMesh(Anim::anim_cid* cid);
	void Render();

private:
	struct Vertex
	{
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
		Color color;

		static const RenderWare::VertexElement ELEMENTS[4];
	};
	void GenerateBlockMesh(int submeshIndex, const Vector3& dir);

	intrusive_ptr<Graphics::GeneratedMesh<Vertex>> mpMesh;
	Anim::anim_cid* mp_cid;
};