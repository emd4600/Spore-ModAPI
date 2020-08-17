#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>

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

		int GetSoftStateDirty();
		void SetSoftStateDirty(int state);

		MatrixType GetTransformType();
		Math::Matrix4* GetTransform();
		void SetTransform(const Math::Matrix4& matrix, MatrixType type = MATRIXTYPE_ORTHOGONAL);

		Math::ColorRGBA& GetColor();
		void SetColor(const Math::ColorRGBA& color);
	}

	namespace Addresses(GlobalState)
	{
		DeclareAddress(transform_ptr);
		DeclareAddress(transformType_ptr);
		DeclareAddress(color_ptr);
		DeclareAddress(softStateDirty_ptr);
		DeclareAddress(SetTransform);
	}
}