#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\MeshCompiledStateLink.h>

namespace RenderWare
{
	auto_METHOD(Mesh, size_t, CalculateTriangleCount, Args(D3DPRIMITIVETYPE primitiveType), Args(primitiveType));
	auto_METHOD_VOID(Mesh, SetIndexBuffer, Args(IndexBuffer* indexBuffer), Args(indexBuffer));
	auto_METHOD_VOID(Mesh, SetVertexBuffer, Args(size_t index, VertexBuffer* vertexBuffer), Args(index, vertexBuffer));
	auto_METHOD_VOID(Mesh, SetIndicesCount, Args(size_t indicesCount), Args(indicesCount));
	auto_METHOD_VOID_(Mesh, Render);

	Mesh::Mesh()
		: instancedSize(sizeof(*this))
		, primitiveType(D3DPT_TRIANGLELIST)
		, pIndexBuffer(nullptr)
		, triangleCount()
		, vertexBuffersCount(1)
		, firstIndex()
		, indicesCount()
		, firstVertex()
		, vertexCount()
		, pVertexBuffers{}
	{

	}

	MeshCompiledStateLink::MeshCompiledStateLink()
		: mpMesh(nullptr)
		, mCompiledStatesCount(1)
		, mpCompiledStates{}
	{
	}
}