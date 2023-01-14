#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <EASTL\bitset.h>

namespace Graphics
{
	namespace GlobalState
	{
		enum SoftState
		{
			kSoftStateTransform = 1,
			kSoftStateColor = 0x10,
		};

		enum MatrixType
		{
			MATRIXTYPE_NA = 0x0,
			MATRIXTYPE_NORMAL = 0x1,
			MATRIXTYPE_ORTHOGONAL = 0x2,
			MATRIXTYPE_ORTHONORMAL = 0x3,
			MATRIXTYPE_IDENTITY = 0x4,
		};

		void D3D9Sync();
		void Dispatch();

		int GetSoftStateDirty();
		void SetSoftStateDirty(int state);

		MatrixType GetTransformType();
		Math::Matrix4* GetTransform();
		void SetTransform(const Math::Matrix4& matrix, MatrixType type = MATRIXTYPE_ORTHOGONAL);

		Math::ColorRGBA& GetColor();
		void SetColor(const Math::ColorRGBA& color);

		int* GetRenderStates();
		// shifted by 7, the first render state
		eastl::bitset<203>& GetRenderStateDirty();

#ifndef SDK_TO_GHIDRA
		inline void SetRenderState(D3DRENDERSTATETYPE state, int value) 
		{
			GetRenderStates()[state] = value;
			GetRenderStateDirty().set(state - 7, true);
		}
#endif

#ifdef SDK_TO_GHIDRA
		Math::Matrix4* sTransform;
		MatrixType sTransformType;
		Math::ColorRGBA sColor;
		int sSoftStateDirty;
		int sRenderStates[210];
		eastl::bitset<203> sRenderStateDirty;
#endif
	}

	namespace Addresses(GlobalState)
	{
		DeclareAddress(D3D9Sync);
		DeclareAddress(Dispatch);
		DeclareAddress(transform_ptr);
		DeclareAddress(transformType_ptr);
		DeclareAddress(color_ptr);
		DeclareAddress(softStateDirty_ptr);
		DeclareAddress(SetTransform);
		DeclareAddress(renderStates_ptr);
		DeclareAddress(renderStateDirty_ptr);
	}
}