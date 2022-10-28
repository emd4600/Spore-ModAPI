#pragma once

#include <Spore\RenderWare\IndexBuffer.h>
#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\RenderWare\VertexDescription.h>
#include <Spore\Graphics\RenderStatistics.h>
#include <Spore\Graphics\IMaterialManager.h>

namespace Graphics
{
	class cBufferDraw
	{
	public:
		enum class VertexType
		{
			V3FC4B = 0,
			V3FT2F = 1,
			V3FC4BT2F = 2,
			V3FC4BT3F = 3,
			V3FN3FC4BT2F = 4,
			V3FC4BP1F = 5,
			V4FN4FC4BT2F = 6,
			V4FN4FC4BC4B = 7,
			V4FN4FG3FC4BC4B = 8,
			V4FN3FC4BT4FT4FT4FT4FT4F = 9,
			V3FC4BT2FT2FT2F = 10,
			V4FN4FC4BC4BT4B = 11
		};
		enum class IndexType
		{
			PointList = 0,
			LineList = 1,
			TriangleList2 = 2,
			TriangleList = 3,
			TriangleStrip = 4,
			TriangleFan = 5,
		};

		static bool LockVertexBuffer(VertexType vertexType, int numVertices, void*& pDstData, int& dstStride);
		static bool UnlockVertexBuffer();

		static void UnlockAndDrawMaterial1Texture(IndexType indexType, Material* pMaterial, Texture* pTexture, const RenderStatistics& stats);
		static void UnlockAndDrawMaterial(IndexType indexType, Material* pMaterial, const RenderStatistics& stats);
		static void UnlockAndDrawNoMaterial(IndexType indexType, const RenderStatistics& stats);

		static cBufferDraw* Get();

	public:
		static const int MAX_VERTICES = 8184;

		/* 00h */	RenderWare::VertexBuffer* mVertexBuffers[12];
		/* 30h */	RenderWare::IndexBuffer* mpIndexBuffer;
		/* 34h */	RenderWare::VertexDescriptionBase* mVertexDescriptions[12];
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/// Index to first free vertex for each vertex type
		/* 70h */	int mFirstFreeVertex[12];
		/* A0h */	int mLastVertex[12];
		/* D0h */	int field_D0[12];
		/* 100h */	void* field_100[12];
		/* 130h */	int field_130[12];
		/* 160h */	int field_160[12];
		/// True if a vertex buffer is locked
		/* 190h */	bool mIsLocked;
		/* 194h */	int field_194;
		/* 198h */	int field_198;
		/* 19Ch */	bool field_19C;
		/* 1A0h */	int mCurrentIndex;  // 12
		/* 1A4h */	int field_1A4;  // 6
		/* 1A8h */	int field_1A8;
		/* 1ACh */	int field_1AC;
		/* 1B0h */	int field_1B0;
	};
	ASSERT_SIZE(cBufferDraw, 0x1B4);

	namespace Addresses(cBufferDraw)
	{
		DeclareAddress(ptr);  // 0x160B998 0x1607728
		DeclareAddress(LockVertexBuffer);  // 0x6DE220 0x6DDD40
		DeclareAddress(UnlockVertexBuffer);  // 0x6DE440 0x6DDF60
		DeclareAddress(UnlockAndDrawMaterial1Texture);  // 0x6DE2E0 0x6DDE00
		DeclareAddress(UnlockAndDrawMaterial);  // 0x6DE2A0 0x6DDDC0
		DeclareAddress(UnlockAndDrawNoMaterial);  // 0x6DE270 0x6DDD90
	}
}