#pragma once

#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\VertexDescription.h>
#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

#define GeneratedMeshPtr(T) intrusive_ptr<Graphics::GeneratedMesh<T>>

namespace Graphics
{
	using namespace eastl;
	using namespace Math;

	struct PosNormalVertex
	{
		Vector3 pos;
		Vector3 normal;

		static const RenderWare::VertexElement ELEMENTS[2];
	};

	struct StandardVertex
	{
		Vector3 pos;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;

		static const RenderWare::VertexElement ELEMENTS[4];
	};

	template <typename Vertex>
	class GeneratedMesh
		: public DefaultRefCounted
	{
	public:
		GeneratedMesh(int numVertices = 0, int numTriangles = 0);
		virtual ~GeneratedMesh();

		/// Returns how many vertices there are in this mesh.
		int GetVertexCount() const;

		/// Returns how many indices there are in this mesh.
		/// The triangle count will be this quantity divided by 3.
		int GetIndexCount() const;

		/// Returns how many triangles this mesh has.
		/// The triangle count is just the index count divided by 3.
		int GetTriangleCount() const;

		/// Adds a new vertex to this mesh, increasing the vertex count by one.
		/// Returns the index of the new vertex.
		/// @param vertex The vertex data that will be added.
		/// @returns The index of this vertex.
		int AddVertex(const Vertex& vertex);

		/// Sets the data of a particular vertex in the mesh.
		/// The index is expected to be between 0 and the vertex count.
		/// @param index The index of the vertex to set.
		/// @param verte The vertex data.
		void SetVertex(int index, const Vertex& vertex);

		/// Returns the vertex data of the vertex at the specified index.
		/// @param index The index of the vertex.
		Vertex GetVertex(int index) const;

		/// Sets the indices of a triangle, this can be used if the number of triangles has been
		/// specified beforehand in the constructor.
		/// @param tindex Index of the triangle
		/// @param i
		/// @param j
		/// @param k
		void SetTriangle(int tindex, int i, int j, int k);

		/// Adds a triangle into this mesh, given its 3 vertex indices.
		/// @param i
		/// @param j
		/// @param k
		/// @returns The index of the triangle.
		int AddTriangle(int i, int j, int k);

		/// Used to get the indices of the triangle identified by `tindex`, which
		/// is the value returned by AddTriangle()
		/// @param tindex Index of the triangle, as returned by AddTriangle()
		/// @param i
		/// @param j
		/// @param k
		void GetTriangle(int tindex, int& i, int& j, int& k) const;

		/// Assigns a material to a portion of this mesh. The material is only assigned to the 
		/// triangles made with the indices between `start` and `start + indexCount`; with the default parameters,
		/// the material will be assigned to all the mesh.
		/// `minVertex` is used for performance purposes, and is the lowest vertex index that will have the material.
		///
		/// The method returns the index of this material, which can be used to later assign textures.
		int AddMaterial(uint32_t materialID, int start = 0, int indexCount = -1, int minVertex = 0);

		/// Returns the amount of materials assigned to this mesh. This can 
		/// be used to iterate them using GetMaterial().
		int GetMaterialCount() const;

		/// Removes all materials from the mesh. Nothing will be rendered after this.
		void ClearMaterials() const;

		/// Gets the information about a material assigned to this mesh.
		/// For a given material index, it gets the parameters with which it was assigned.
		/// @param index The index of the material, between 0 and GetMaterialCount()
		/// @param[out] materialID The ID of the material.
		/// @param[out] start
		/// @param[out] indexCount
		/// @param[out] minVertex
		void GetMaterial(int index, uint32_t& materialID, int& start, int& indexCount, int& minVertex) const;
		
		/// Changes a texture for one of the materials used in this mesh.
		/// The `raster` object will NOT be memory managed by this mesh.
		/// @param materialIndex The index of the material to change, as returned by AddMaterial().
		/// @param samplerIndex The index of the sampler where the texture will be assigned.
		/// @param raster The raster object to assign.
		/// @param compiledStateIndex For materials that have more than one compiled state, which one will be changed.
		void SetTexture(int materialIndex, int samplerIndex, RenderWare::Raster* raster, int compiledStateIndex = 0);

		/// Returns the raster texture that is being used for a certain material in this mesh.
		/// @param materialIndex The index of the material, as returned by AddMaterial().
		/// @param samplerIndex The index of the sampler of the texture inside the material.
		/// @param compiledStateIndex For materials that have more than one compiled state.
		/// @returns The raster texture used in the material.
		RenderWare::Raster* GetTexture(int materialIndex, int samplerIndex, int compiledStateIndex = 0) const;

		BoundingBox GetBoundingBox();

		void Submit();

		void Render();

	protected:
		RenderWare::VertexBuffer mVertexBuffer;
		RenderWare::IndexBuffer mIndexBuffer;
		RenderWare::VertexDescription<sizeof(Vertex::ELEMENTS)/sizeof(RenderWare::VertexElement)> mVertexDesc;

		vector<Vertex> mVertices;
		vector<uint16_t> mIndices;

		vector<RenderWare::Mesh<1>> mMeshes;
		vector<MaterialPtr> mMaterials;

		BoundingBox mBounds;
		bool mBoundsValid;
	};

	template <typename Vertex>
	GeneratedMesh<Vertex>::GeneratedMesh(int numVertices, int numTriangles)
		: mVertices(numVertices)
		, mIndices(numTriangles * 3)
		, mBoundsValid(false)
		, mBounds()
	{
		mVertexBuffer.baseVertexIndex = 0;
		mVertexBuffer.usage = 8;
		mVertexBuffer.vertexCount = numVertices;
		mVertexBuffer.stride = sizeof(Vertex);
		mVertexBuffer.lockFlags = 0;
		mVertexBuffer.pVertexDescription = &mVertexDesc;
		mVertexBuffer.pVertexData = mVertices.data();

		mIndexBuffer.format = D3DFORMAT::D3DFMT_INDEX16;
		mIndexBuffer.indicesCount = numTriangles * 3;
		mIndexBuffer.usage = D3DUSAGE_WRITEONLY;
		mIndexBuffer.primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
		mIndexBuffer.pIndexData = mIndices.data();

		mVertexDesc.stride = sizeof(Vertex);

		for (int i = 0; i < mVertexDesc.elementsCount; ++i) {
			mVertexDesc.SetElement(i, Vertex::ELEMENTS[i]);
			mVertexDesc.elementsHash |= RenderWare::RWDECL_VERTEX2[Vertex::ELEMENTS[i].rwDecl];
		}
	}

	template <typename Vertex>
	inline GeneratedMesh<Vertex>::~GeneratedMesh() {
		mIndexBuffer.ReleaseDirectX();
		mVertexBuffer.ReleaseDirectX();
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::GetVertexCount() const {
		return mVertexBuffer.vertexCount;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::GetIndexCount() const {
		return mIndexBuffer.indicesCount;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::GetTriangleCount() const {
		return mIndexBuffer.indicesCount / 3;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::AddVertex(const Vertex& vertex) {
		mVertices.push_back(vertex);

		mBoundsValid = false;
		mVertexBuffer.vertexCount++;
		mVertexBuffer.pVertexData = mVertices.data();

		return mVertexBuffer.vertexCount - 1;
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SetVertex(int index, const Vertex& vertex) {
		mVertices[index] = vertex;
		mBoundsValid = false;
	}

	template <typename Vertex>
	inline Vertex GeneratedMesh<Vertex>::GetVertex(int index) const {
		return mVertices[index];
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SetTriangle(int tindex, int i, int j, int k) {
		mIndices[tindex * 3 + 0] = i;
		mIndices[tindex * 3 + 1] = j;
		mIndices[tindex * 3 + 2] = k;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::AddTriangle(int i, int j, int k) {
		mIndices.push_back(i);
		mIndices.push_back(j);
		mIndices.push_back(k);

		mIndexBuffer.indicesCount = mIndices.size();
		mIndexBuffer.pIndexData = mIndices.data();

		return mIndices.size() / 3 - 1;
	}

	template <typename Vertex>
	void GeneratedMesh<Vertex>::GetTriangle(int tindex, int& i, int& j, int& k) const {
		int index = tindex * 3;
		i = mIndices[index + 0];
		j = mIndices[index + 1];
		k = mIndices[index + 2];
	}
	
	template <typename Vertex>
	int GeneratedMesh<Vertex>::AddMaterial(uint32_t materialID, int start, int indicesCount, int minVertex) {
		if (indicesCount == -1) indicesCount = mIndices.size();

		RenderWare::Mesh<1> mesh;
		mesh.instancedSize = 40;  // ?
		mesh.firstIndex = start;
		mesh.firstVertex = minVertex;
		mesh.SetIndexBuffer(&mIndexBuffer);
		mesh.SetVertexBuffer(0, &mVertexBuffer);
		mesh.SetIndicesCount(indicesCount);

		mMeshes.push_back(mesh);

		mMaterials.push_back(MaterialManager.GetMaterial(materialID));

		return mMeshes.size() - 1;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::GetMaterialCount() const {
		return mMaterials.size();
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::ClearMaterials() const {
		mMaterials.clear();
		mMeshes.clear();
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::GetMaterial(int index, uint32_t& materialID, int& start, int& indexCount, int& minVertex) const {
		materialID = mMaterials[index]->materialID;
		start = mMeshes[index].firstIndex;
		indexCount = mMeshes[index].indicesCount;
		minVertex = mMeshes[index].firstVertex;
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SetTexture(int materialIndex, int samplerIndex, RenderWare::Raster* raster, int compiledStateIndex) {
		mMaterials[materialIndex]->states[compiledStateIndex]->SetRaster(samplerIndex, raster);
	}

	template <typename Vertex>
	inline RenderWare::Raster* GeneratedMesh<Vertex>::GetTexture(int materialIndex, int samplerIndex, int compiledStateIndex) const {
		if (materialIndex >= mMaterials.size()) return nullptr;
		if (compiledStateIndex >= mMaterials[materialIndex]->statesCount) return;
		return mMaterials[materialIndex]->states[compiledStateIndex]->GetRaster(samplerIndex);
	}

	template <typename Vertex>
	BoundingBox GeneratedMesh<Vertex>::GetBoundingBox() {
		if (!mBoundsValid) {
			int offset = 0;
			for (int i = 0; i < mVertexDesc.elementsCount; ++i) {
				if (mVertexDesc.elements[i]->rwDecl == RWDECL_VERTEX_POSITION) {
					offset = mVertexDesc.elements[i]->offset;
					break;
				}
			}
			mBounds.lower = { FLT_MAX, FLT_MAX, FLT_MAX };
			mBounds.upper = { FLT_MIN, FLT_MIN, FLT_MIN };
			for (const Vertex& v : mVertices) {
				Vector3& pos = *(Vector3*)(((char*)v) + offset);

				if (pos.x > mBounds.upper.x) mBounds.upper.x = pos.x;
				if (pos.y > mBounds.upper.y) mBounds.upper.y = pos.y;
				if (pos.z > mBounds.upper.z) mBounds.upper.z = pos.z;

				if (pos.x < mBounds.lower.x) mBounds.lower.x = pos.x;
				if (pos.y < mBounds.lower.y) mBounds.lower.y = pos.y;
				if (pos.z < mBounds.lower.z) mBounds.lower.z = pos.z;
			}

			mBoundsValid = true;
		}
		return mBounds;
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::Render() {
		for (int i = 0; i < GetMaterialCount(); ++i) {
			mMaterials[i]->states[0]->Load();
			mMeshes[i].Render();
		}
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::Submit() {
		mVertexBuffer.CreateDirectX();
		mVertexBuffer.LockDirectXData();
		mIndexBuffer.CreateDirectX();
		mIndexBuffer.LockDirectXData();
	}
}
