#pragma once

#include <Spore\RenderWare\Mesh.h>
#include <Spore\RenderWare\VertexDescription.h>
#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\GlobalState.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

#ifndef SDK_TO_GHIDRA
#define GeneratedMeshPtr(T) eastl::intrusive_ptr<Graphics::GeneratedMesh<T>>

namespace Graphics
{
	struct PosNormalVertex
	{
		Math::Vector3 pos;
		Math::Vector3 normal;

		static const RenderWare::VertexElement ELEMENTS[2];
	};

	struct PosUvVertex
	{
		Math::Vector3 pos;
		Math::Vector2 uv;

		static const RenderWare::VertexElement ELEMENTS[2];
	};

	struct StandardVertex
	{
		Math::Vector3 pos;
		Math::Vector2 uv;
		Math::Vector3 normal;
		Math::Vector3 tangent;

		static const RenderWare::VertexElement ELEMENTS[4];
	};

	struct StandardVertexCompact
	{
		Math::Vector3 pos;
		Math::Vector2 uv;
		uint8_t normal[4];
		uint8_t tangent[4];

		inline void SetNormal(Math::Vector3 v) {
			normal[0] = int(roundf(v.x * 127.5f + 127.5f)) & 0xFF;
			normal[1] = int(roundf(v.y * 127.5f + 127.5f)) & 0xFF;
			normal[2] = int(roundf(v.z * 127.5f + 127.5f)) & 0xFF;
			normal[3] = 0;
		}
		inline void SetTangent(Math::Vector3 v) {
			tangent[0] = int(roundf(v.x * 127.5f + 127.5f)) & 0xFF;
			tangent[1] = int(roundf(v.y * 127.5f + 127.5f)) & 0xFF;
			tangent[2] = int(roundf(v.z * 127.5f + 127.5f)) & 0xFF;
			tangent[3] = 0;
		}

		static const RenderWare::VertexElement ELEMENTS[4];
	};

	template <typename Vertex>
	class GeneratedMesh
		: public DefaultRefCounted
	{
	public:
		GeneratedMesh(int numVertices = 0, int numTriangles = 0, D3DPRIMITIVETYPE primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST);
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

		Vertex& ModifyVertex(int index);

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
		void ClearMaterials();

		/// Gets the information about a material assigned to this mesh.
		/// For a given material index, it gets the parameters with which it was assigned.
		/// @param index The index of the material, between 0 and GetMaterialCount()
		/// @param[out] materialID The ID of the material.
		/// @param[out] start
		/// @param[out] indexCount
		/// @param[out] minVertex
		void GetMaterial(int index, uint32_t& materialID, int& start, int& indexCount, int& minVertex) const;

		Material* GetMaterial(int index) const;
		
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

		/// Returns the 4x4 matrix transformation that gets applied to a certain material of this mesh.
		/// By default it's the identity, that is, no transform.
		/// @param materialIndex The index of the material, as returned by AddMaterial().
		/// @returns The 4x4 matrix transformation
		const Math::Matrix4& GetTransform(int materialIndex);

		/// Sets the 4x4 matrix transformation that gets applied to a certain material of this mesh.
		/// By default it's the identity, that is, no transform.
		/// @param materialIndex The index of the material, as returned by AddMaterial().
		/// @returns The 4x4 matrix transformation
		void SetTransform(int materialIndex, const Math::Matrix4& transform);

		/// Returns the color that gets applied to a certain material of this mesh.
		/// By default it's white.
		/// @param materialIndex The index of the material, as returned by AddMaterial().
		/// @returns The material color.
		const Math::ColorRGBA& GetColor(int materialIndex);

		/// Sets the color that gets applied to a certain material of this mesh.
		/// By default it's white.
		/// @param materialIndex The index of the material, as returned by AddMaterial().
		/// @returns The material color.
		void SetColor(int materialIndex, const Math::ColorRGBA& color);

		Math::BoundingBox GetBoundingBox();

		void SubmitGeometry();
		void UnloadGeometry();

		void Render();

	protected:
		RenderWare::VertexBuffer mVertexBuffer;
		RenderWare::IndexBuffer mIndexBuffer;
		RenderWare::VertexDescription<sizeof(Vertex::ELEMENTS)/sizeof(RenderWare::VertexElement)> mVertexDesc;

		eastl::vector<Vertex> mVertices;
		eastl::vector<uint16_t> mIndices;

		eastl::vector<RenderWare::Mesh> mMeshes;
		eastl::vector<MaterialPtr> mMaterials;
		eastl::vector<Math::ColorRGBA> mColors;
		eastl::vector<Math::Matrix4> mTransforms;

		Math::BoundingBox mBounds;
		bool mBoundsValid;
	};


	GeneratedMesh<PosUvVertex>* GenerateScreenPlane(float z = 0.0);


	template <typename Vertex>
	GeneratedMesh<Vertex>::GeneratedMesh(int numVertices, int numTriangles, D3DPRIMITIVETYPE primitiveType)
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

		mIndexBuffer.format = D3DFORMAT::D3DFMT_INDEX16;
		mIndexBuffer.indicesCount = numTriangles * 3;
		mIndexBuffer.usage = D3DUSAGE_WRITEONLY;
		mIndexBuffer.primitiveType = primitiveType;

		mVertexDesc.stride = sizeof(Vertex);

		for (int i = 0; i < mVertexDesc.elementsCount; ++i) {
			mVertexDesc.SetElement(i, Vertex::ELEMENTS[i]);
			mVertexDesc.elementsHash |= RenderWare::RWDECL_VERTEX2[Vertex::ELEMENTS[i].rwDecl];
		}
	}

	template <typename Vertex>
	inline GeneratedMesh<Vertex>::~GeneratedMesh() {
		UnloadGeometry();
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
	inline Vertex& GeneratedMesh<Vertex>::ModifyVertex(int index) {
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

		RenderWare::Mesh mesh;
		mesh.firstIndex = start;
		mesh.firstVertex = minVertex;
		mesh.SetIndexBuffer(&mIndexBuffer);
		mesh.SetVertexBuffer(0, &mVertexBuffer);
		mesh.SetIndicesCount(indicesCount);

		mMeshes.push_back(mesh);
		mColors.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
		mTransforms.push_back(Math::Matrix4().SetIdentity());

		mMaterials.push_back(MaterialManager.GetMaterialInstance(materialID));

		return mMeshes.size() - 1;
	}

	template <typename Vertex>
	inline int GeneratedMesh<Vertex>::GetMaterialCount() const {
		return mMaterials.size();
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::ClearMaterials() {
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
	inline Material* GeneratedMesh<Vertex>::GetMaterial(int index) const {
		return mMaterials[index].get();
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
	inline const Math::Matrix4& GeneratedMesh<Vertex>::GetTransform(int materialIndex) {
		if (materialIndex >= mTransforms.size()) return nullptr;
		return mTransforms[materialIndex];
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SetTransform(int materialIndex, const Math::Matrix4& transform) {
		mTransforms[materialIndex] = transform;
	}

	template <typename Vertex>
	inline const Math::ColorRGBA& GeneratedMesh<Vertex>::GetColor(int materialIndex) {
		if (materialIndex >= mColors.size()) return nullptr;
		return mColors[materialIndex];
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SetColor(int materialIndex, const Math::ColorRGBA& color) {
		mColors[materialIndex] = color;
	}

	template <typename Vertex>
	Math::BoundingBox GeneratedMesh<Vertex>::GetBoundingBox() {
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
			//PLACEHOLDER GlobalState::SetTransform(mTransforms[i]);
			GlobalState::SetColor(mColors[i]);
			mMaterials[i]->states[0]->Load();
			//MessageBoxA(NULL, "", "", MB_OK);
			mMeshes[i].Render();
		}
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::SubmitGeometry() {
		mVertexBuffer.pVertexData = mVertices.data();
		mIndexBuffer.pIndexData = mIndices.data();

		mVertexBuffer.CreateDirectX();
		mVertexBuffer.LockDirectXData();
		mIndexBuffer.CreateDirectX();
		mIndexBuffer.LockDirectXData();
	}

	template <typename Vertex>
	inline void GeneratedMesh<Vertex>::UnloadGeometry() {
		mIndexBuffer.ReleaseDirectX();
		mVertexBuffer.ReleaseDirectX();
	}
}
#endif