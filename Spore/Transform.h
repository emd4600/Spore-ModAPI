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

using namespace Math;

///
/// A class that represents a 3D transformation; it can store the same information as a 4x4 matrix, but it's easier to use.
/// This class stores the location, scale and rotation (as a 3x3 matrix) separately, making it a lot easier to use than a matrix.
/// It does have a method to convert it to a 4x4 matrix, so that it can be used in matematical operations. (NOT YET, TODO!)
/// Transforms can be multiplied in order to concatenate multiple transformations.
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

	const Vector3& GetOffset() const;
	Transform& SetOffset(const Vector3& value);

	float GetScale() const;
	Transform& SetScale(float value);

	const Matrix3& GetRotation() const;
	Transform& SetRotation(Matrix3& value);

	Matrix4 ToMatrix4() const;

	Transform& operator*(const Transform& other);

protected:
	/* 00h */	int16_t	mnFlags;
	/* 02h */	int16_t	mnTransformCount;  // ?
	/* 04h */	Vector3 mOffset;
	/* 10h */	float	mfScale;
	/* 14h */	Matrix3 mRotation;
};

/////////////////////////////////
//// INTERNAL IMPLEMENTATION ////
/////////////////////////////////

namespace InternalAddressList(Transform)
{
	DefineAddress(ToMatrix4, GetAddress(0x6B9720, 0x6B93F0, 0x6B93F0));
}

static_assert(sizeof(Transform) == 0x38, "sizeof(Transform) != 38h");

inline const Vector3& Transform::GetOffset() const
{
	return mOffset;
}
inline Transform& Transform::SetOffset(const Vector3& value)
{
	mOffset = value;
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

inline const Matrix3& Transform::GetRotation() const
{
	return mRotation;
}
inline Transform& Transform::SetRotation(Matrix3& value)
{
	mRotation = value;
	mnFlags |= kTransformFlagRotation;

	return *this;
}

inline Transform& Transform::operator*(const Transform& other)
{
	return CALL(GetAddress(0x40CC10, 0x40CCB0, 0x40CCB0), Transform&, PARAMS(const Transform&), PARAMS(other));
}