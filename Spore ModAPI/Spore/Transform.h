/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include "MathUtils.h"

///
/// A class that represents a 3D transformation; it can store the same information as a 4x4 matrix, but it's easier to use.
/// This class stores the location, scale and rotation (as a 3x3 matrix) separately, making it a lot easier to use than a matrix.
/// It has a method to convert it to a 4x4 matrix, so that it can be used in matematical operations.
/// Transforms can be multiplied in order to concatenate multiple transformations using `Multiply(other)`
///
class Transform {

public:
	Transform();

	enum TransformFlags
	{
		kTransformFlagScale = 1,
		kTransformFlagRotation = 2,
		kTransformFlagOffset = 4,
	};

	const Math::Vector3& GetOffset() const;
	Transform& SetOffset(const Math::Vector3& value);
	Transform& SetOffset(float x, float y, float z);

	float GetScale() const;
	Transform& SetScale(float value);

	const Math::Matrix3& GetRotation() const;
	Transform& SetRotation(const Math::Matrix3& value);
	Transform& SetRotation(const Math::Vector3& euler);
	Transform& SetRotation(const Math::Quaternion& value);

	/// Returns the 4x4 matrix that represents this transform. This matrix
	/// can be used to apply the transform to vectors, by just multiplying.
	Math::Matrix4 ToMatrix4() const;

	/// Inverts this transform, so that now it will do exactly the opposite transformation.
	/// A transform multiplied by its inverse results in the identity transform, which doesn't change anything.
	void Invert();

	/// Applies another transform into this transform.
	/// @param other
	Transform& PreTransformBy(const Transform& other);

protected:
	/* 00h */	int16_t	mnFlags;
	/* 02h */	int16_t	mnTransformCount;  // ?
	/* 04h */	Math::Vector3 mOffset;
	/* 10h */	float	mfScale;
	/* 14h */	Math::Matrix3 mRotation;
};
ASSERT_SIZE(Transform, 0x38);

namespace Addresses(Transform)
{
	DeclareAddress(ToMatrix4);
	DeclareAddress(assign);  // This name is wrong, it's actually multiply operation
	DeclareAddress(PreTransformBy);
}

inline const Math::Vector3& Transform::GetOffset() const
{
	return mOffset;
}
inline Transform& Transform::SetOffset(const Math::Vector3& value)
{
	mOffset = value;
	mnFlags |= kTransformFlagOffset;

	return *this;
}
inline Transform& Transform::SetOffset(float x, float y, float z)
{
	mOffset = {x, y, z};
	mnFlags |= kTransformFlagOffset;

	return *this;
}

inline float Transform::GetScale() const
{
	return mfScale;
}
inline Transform& Transform::SetScale(float value)
{
	mfScale = value;
	mnFlags |= kTransformFlagScale;

	return *this;
}

inline const Math::Matrix3& Transform::GetRotation() const
{
	return mRotation;
}
inline Transform& Transform::SetRotation(const Math::Matrix3& value)
{
	mRotation = value;
	mnFlags |= kTransformFlagRotation;

	return *this;
}

inline Transform& Transform::SetRotation(const Math::Vector3& euler)
{
	mRotation = Math::Matrix3::FromEuler(euler);
	mnFlags |= kTransformFlagRotation;

	return *this;
}

inline Transform& Transform::SetRotation(const Math::Quaternion& value)
{
	mRotation = value.ToMatrix();
	mnFlags |= kTransformFlagRotation;

	return *this;
}