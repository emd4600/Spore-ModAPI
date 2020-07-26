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

#include <stdint.h>
#include <cmath>
#include <Spore\Internal.h>

namespace Addresses(Math)
{
	DeclareAddress(MultiplyVectorScalar);
	DeclareAddress(EulerToMatrix);
	DeclareAddress(MatrixToEuler);

	DeclareAddress(RandomNumberGenerator_ptr);
}

class Transform;

/// 
/// @brief Basic mathematical objects and functions, such as vectors, random numbers,...
///
namespace Math
{
	const float PI = 3.14159f;

	/// Converts the given angle in degrees into the angle in radians.
	/// @param degrees The angle, in degrees.
	/// @returns The angle in radians.
	inline float ToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	/// Converts the given angle in radians into the angle in degrees.
	/// @param radians The angle, in radians.
	/// @returns The angle in degrees.
	inline float ToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}

	/// Ensures that the given number stays in the range `[a, b]`, included; `a <= b`.
	/// If `value > b`, it returns b; if `value < a`, it returns `a`.
	/// @param value The value to clamp
	/// @param a The minimum value
	/// @param b The maximum value
	template <typename T>
	inline T clamp(T value, T a, T b) {
		return min(max(value, a), b);
	}

	/// Linear interpolation between two values, which can be integers, floats, vectors or colors.
	/// A `mix` value of 0 returns `a`, a value of `1` returns `b`.
	/// 
	/// The returned value will be equal to `mix*a + (1-mix)*b`
	/// @param a The first value
	/// @param b The second value
	/// @param mix The mix factor, between 0.0 and 1.0
	template <typename T>
	inline T lerp(const T& a, const T& b, float mix) {
		return a + (b - a) * mix;
	}

	/// Returns the shortest difference between two angles (in radians), the result is always in the range [0, PI].
	/// The order of the angles does not matter.
	/// @param angle1
	/// @param angle2
	float GetAngleDifference(float angle1, float angle2);

	/// Returns `angle1 + inc` or `angle2 - inc`, in the range [-PI, PI], depending on what's the shortest
	/// way to get from `angle1` to `angle2`. All the angles are in radians.
	/// @param angle1 "Source" angle
	/// @param angle2 "Dest" angle
	/// @param inc How many radians are incremented.
	float IncrementAngleTo(float angle1, float angle2, float inc);

	/// Converts the given angle to the [-PI, PI] range, everything in radians.
	/// @param angle
	float CorrectAngleRange(float angle);

	/// An ARGB color represented by a 32 bit integer value.
	struct Color
	{
		union {
			uint32_t value;
			struct
			{
				uint8_t b;
				uint8_t g;
				uint8_t r;
				uint8_t a;
			};
		};

		Color();
		Color(const Color& color);
		Color(uint32_t color);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		inline bool operator==(const Color& b) const {
			return value == b.value;
		}

		inline bool operator!=(const Color& b) const {
			return value != b.value;
		}

		static const Color RED;
		static const Color BLUE;
		static const Color GREEN;
		static const Color WHITE;
		static const Color BLACK;
	};
	static_assert(sizeof(Color) == 0x4, "sizeof(Color) != 04h");

	/// A vector of 2 float values (x, y).
	struct Vector2 {
		float x;
		float y;

		Vector2(float x, float y);
		Vector2(const Vector2& other);
		Vector2();

		/// Returns the length of the vector, computed as the square root of then sum of its components squared.
		float Length() const;

		/// Returns a normalized version of this vector. Being normalized means it has a length of 1.0
		Vector2 Normalized() const;

		/// Computes the dot product between this vector and `other`.
		/// The dot product is computed as `a.x * b.x + a.y * b.y + a.z * b.z`
		/// @param other
		float Dot(const Vector2& other) const;

		Vector2& operator+=(const Vector2&);
		Vector2& operator+=(float);
		Vector2& operator-=(const Vector2&);
		Vector2& operator-=(float);
		Vector2& operator*=(float);
		Vector2& operator/=(float);

		bool operator==(const Vector2& b) const;
		bool operator!=(const Vector2& b) const;
	};

	/// A vector of 3 float values (x, y, z).
	struct Vector3 {
		float x;
		float y;
		float z;

		Vector3();
		Vector3(const Vector3& other);
		Vector3(float x, float y, float z);

		/// Returns the length of the vector, computed as the square root of then sum of its components squared.
		float Length() const;

		/// Similar to Length(), but without applying the square root.
		float SquaredLength() const;

		/// Returns a normalized version of this vector. Being normalized means it has a length of 1.0
		Vector3 Normalized() const;

		/// Computes the dot product between this vector and `other`.
		/// The dot product is computed as `a.x * b.x + a.y * b.y + a.z * b.z`
		/// @param other
		float Dot(const Vector3& other) const;

		/// Computes the cross product between this vector and `other`.
		/// This will return a vector that is perpendicular to both vectors.
		/// @param other
		Vector3 Cross(const Vector3& other) const;

		/// Returns the angle between two vectors.
		/// @param other
		float AngleTo(const Vector3& other) const;

		/// Returns the oriented angle between the vectors `v1` and `v2`, in the range [0, 2pi).
		/// An additional vector must be passed to determine which is the orientation (i.e. whether a 
		/// positive angle moves from `v1` to `v2` or the other way around), following the "right hand rule".
		/// @param v1
		/// @param v2
		/// @param orientationAxis
		static float OrientedAngle(const Vector3& v1, const Vector3& v2, const Vector3& orientationAxis);

		Vector3& operator+=(const Vector3&);
		Vector3& operator+=(float);
		Vector3& operator-=(const Vector3&);
		Vector3& operator-=(float);
		Vector3& operator*=(float);
		Vector3& operator/=(float);

		bool operator==(const Vector3& b) const;
		bool operator!=(const Vector3& b) const;

		static const Vector3 ZERO;
	};

	const Vector3 X_AXIS = { 1, 0, 0 };
	const Vector3 Y_AXIS = { 0, 1, 0 };
	const Vector3 Z_AXIS = { 0, 0, 1 };

	struct Matrix3;
	/// A vector of 4 float values (x, y, z, w).
	struct Vector4 {
		float x;
		float y;
		float z;
		float w;
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector4& other);
		Vector4();

		/// Returns the length of the vector, computed as the square root of then sum of its components squared.
		float Length() const;

		/// Returns a normalized version of this vector. Being normalized means it has a length of 1.0
		Vector4 Normalized() const;

		/// Computes the dot product between this vector and `other`.
		/// The dot product is computed as `a.x * b.x + a.y * b.y + a.z * b.z`
		/// @param other
		float Dot(const Vector4& other) const;

		Vector4& operator+=(const Vector4&);
		Vector4& operator+=(float);
		Vector4& operator-=(const Vector4&);
		Vector4& operator-=(float);
		Vector4& operator*=(float);
		Vector4& operator/=(float);

		bool operator==(const Vector4& b) const;
		bool operator!=(const Vector4& b) const;
	};

	/// A vector of 4 float values (x, y, z, w) representing a quaternion rotation, similar to a Vector4.
	/// Quaternions an be multiplied to chain rotations: `q1 * q2` means applying rotation `r2` followed by rotation `r2`.
	/// You can use the Quaternion::FromRotation() and Quaternion::FromEuler() to build quaternion rotations.
	/// It has a value of (0, 0, 0, 1) by default.
	struct Quaternion : public Vector4
	{
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Quaternion& other);
		Quaternion();

		/// Returns the inverse to this quaternion: that's another quaternion that, when multiplied with this one,
		/// gives the identity.
		Quaternion Inverse() const;

		/// Builds a 3x3 rotation matrix equivalent to this quaternion rotation.
		Matrix3 ToMatrix() const;

		/// Returns the euler angles (in radians) that represent the same rotation as
		/// this quaternion. It returns a vector with the rotation around the X (roll),
		/// Y (pitch) and Z (yaw) axes.
		Vector3 ToEuler() const;

		/// Constructs a Quaternion that represents a rotation of the given angle (in radians)
		/// around a certain axis.
		/// @param axis The axis of rotation. Only the direction matters, the length is ignored.
		/// @param angle The angle of rotation, in radians.
		static Quaternion FromRotation(const Vector3& axis, float angle);

		/// Constructs a Quaternion that represents a rotation, given in euler angles in radians.
		/// The quaternion will be constructed as if the rotations were applied in Z, Y, X order.
		/// @param angles Rotation around X (roll), Y (pitch) and Z (yaw) axes, in radians
		static Quaternion FromEuler(const Vector3& angles);

		/// Returns the quaternion the rotation between two vectors. 
		/// This means that applying the returned quaternion to the vector `from` produces the vector `to`
		/// (assuming they have the same length).
		///
		/// The operation will be applied to normalized versions of the vectors, so their length does not matter.
		///
		/// @param from Vector to rotate from.
		/// @param to Vector to rotate to.
		/// @param fallbackAxis If the two vectors are parallel but opposite, this method returns a 180 degrees rotation around the fallback axis.
		static Quaternion GetRotationTo(const Vector3& from, const Vector3& to, const Vector3& fallbackAxis = Vector3::ZERO);
	};

	/// Represents a point in the space, defined by two float coordinates (x, y).
	struct Point {
		float x;
		float y;

		Point(float x, float y);
		Point(const Point& other);
		Point();

		Point& operator+=(const Point&);
		Point& operator+=(float);
		Point& operator-=(const Point&);
		Point& operator-=(float);
		Point& operator*=(float);
		Point& operator/=(float);

		bool operator==(const Point& b) const;
		bool operator!=(const Point& b) const;
	};

	/// Represents a rectangular space, defined by two points or by the four edges.
	/// (x1, y1) represents the point on the top-left corner; (x2, y2) represents the point on the bottom-right corner.
	/// The variables 'left', 'top', 'right' and 'bottom' can also be used to define the horizontal or vertical coordinates
	/// where each border is at.
	union Rectangle {
		struct
		{
			float x1;
			float y1;
			float x2;
			float y2;
		};
		struct
		{
			float left;
			float top;
			float right;
			float bottom;
		};
		Rectangle(float x1, float y1, float x2, float y2);
		Rectangle();

		/// Returns the width of the rectangle.
		inline float GetWidth() const {
			return x2 - x1;
		}
		/// Returns the height of the rectangle.
		inline float GetHeight() const {
			return y2 - y1;
		}
		/// Returns the X coordinate that falls in the center of the rectangle.
		inline float GetCenterX() const {
			return x1 + (x2 - x1);
		}
		/// Returns the Y coordinate that falls in the center of the rectangle.
		inline float GetCenterY() const {
			return y1 + (y2 - y1) / 2;
		}
		/// Returns the point at the center of the rectangle.
		inline Point GetCenter() const {
			return Point(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
		}
		/// Returns the point at the top-left corner of the rectangle.
		inline Point GetTopLeft() const {
			return Point(x1, y1);
		}
		/// Returns the point at the top-right corner of the rectangle.
		inline Point GetTopRight() const {
			return Point(x2, y1);
		}
		/// Returns the point at the bottom-left corner of the rectangle.
		inline Point GetBottomLeft() const {
			return Point(x1, y2);
		}
		/// Returns the point at the bottom-right corner of the rectangle.
		inline Point GetBottomRight() const {
			return Point(x2, y2);
		}
		/// Returns true if the given point is contained inside this rectangle.
		inline bool Contains(float x, float y) const {
			return x >= x1 && x <= x2 && y >= y1 && y <= y2;
		}
		/// Returns true if the given point is contained inside this rectangle.
		inline bool Contains(const Point& p) const {
			return Contains(p.x, p.y);
		}
	};

	/// A pair of two float values that represents the dimensions of an image (width, height).
	struct Dimensions {
		float width;
		float height;
		Dimensions(float width, float height);
		Dimensions();
	};

	/// A pair of two integer values that represents the dimensions of an image (width, height).
	struct IntDimensions {
		int width;
		int height;
		IntDimensions(int width, int height);
		IntDimensions();
	};

	/// Three float values in the range [0, 1] that represent a color (the red, green and blue components).
	struct ColorRGB {
		float r;
		float g;
		float b;
		ColorRGB(float r, float g, float b);
		ColorRGB(Color color);
		ColorRGB();

		ColorRGB& Set(float r, float g, float b);

		/// Returns the integer representation of the given color (in the form of a Color value).
		Color ToIntColor();

		bool operator==(const ColorRGB& b) const;
		bool operator!=(const ColorRGB& b) const;
	};

	/// Four float values in the range [0, 1] that represent a color (the red, green, blue and alpha components).
	/// The alpha component defines the opacity of the color: 0 alpha is fully transparent, 1 alpha is fully opaque.
	struct ColorRGBA {
		ColorRGBA(float r, float g, float b, float a);
		ColorRGBA(ColorRGB color, float a);
		ColorRGBA();

		ColorRGBA& Set(float r, float g, float b, float a);

		/// Returns the integer representation of the given color (in the form of a Color value).
		Color ToIntColor();

		bool operator==(const ColorRGBA& b) const;
		bool operator!=(const ColorRGBA& b) const;

		float r;
		float g;
		float b;
		float a;
	};

	/// Three float values that represent a color (the hue, saturation and value/brightness values).
	struct ColorHSV {
		ColorHSV(float h, float s, float v);
		ColorHSV();

		ColorHSV& Set(float h, float s, float v);

		float h;
		float s;
		float v;
	};

	/// A 3x3 matrix.
	struct Matrix3 {
		float m[3][3];
		Matrix3();
		Matrix3(const Matrix3& other);

		/// Turns this matrix into the identity matrix (1.0s in the diagonal, everything else 0.0s).
		/// Multiplying a matrix/vector with an identity matrix has no effect.
		Matrix3& SetIdentity();

		/// Returns the euler angles (in radians) equivalent to the rotation of this matrix.
		/// The euler angles are a vector of 3 values that represent the rotation around the
		/// X, Y and Z axes respectively.
		Vector3 ToEuler() const;

		/// Returns a Quaternion that represents the same rotation as this matrix.
		Quaternion ToQuaternion() const;

		/// Returns the transpose of this matrix, switching the rows and columns. `transposed[i][j] = matrix[j][i]`
		Matrix3 Transposed() const;

		/// Builds a 3x3 rotation matrix equivalent to the euler angles provided.
		/// The euler angles must be in radians, and each value represents the rotation
		/// around the X, Y and Z axes respectively.
		/// @param angles The euler angles, in radians.
		static Matrix3 FromEuler(const Vector3& angles);

		/// Builds a 3x3 rotation matrix that rotates `angle` radians around the given `axis`.
		/// This is equivalent to `Quaternion::FromRotation(axis, angle).ToMatrix()`.
		/// @param axis The axis of rotation, which stays fixed.
		/// @param angle The angle, in radians.
		static Matrix3 FromAxisAngle(const Vector3& axis, float angle);

		/// Builds a rotation matrix that can be used in cameras, for a camera at `position`
		/// looking towards `target`. Optionally, the vector that represents the up direction in the world
		/// (which usually is the Z axis) can be specified.
		///
		/// This method might give unexpected results if target and position are aligned.
		/// @param position The "eye" position
		/// @param target The position where the "eye" is looking at
		/// @param up [Optional] The up vector, Z axis by default.
		static Matrix3 LookAt(const Vector3& position, const Vector3& target, const Vector3& up = Z_AXIS);
	};

	/// A 4x4 matrix.
	struct Matrix4 {
		float m[4][4];
		Matrix4();
		Matrix4(const Matrix4& other);

		/// Turns this matrix into the identity matrix (1.0s in the diagonal, everything else 0.0s)
		/// Multiplying a matrix/vector with an identity matrix has no effect.
		Matrix4& SetIdentity();

		/// Returns the transpose of this matrix, switching the rows and columns. `transposed[i][j] = matrix[j][i]`
		Matrix4 Transposed() const;

		/// Returns the 3x3 part of this matrix, leaving the last column and row.
		Matrix3 To3x3() const;
	};

	/// A pair of two Vector3 that define the boundaries of an object (the minimum point and the maximum point in the space).
	/// The two vectors are the lower (minumum) bound and the upper (maximum) bound.
	struct BoundingBox {
		BoundingBox();
		BoundingBox(const Vector3& lower, const Vector3& upper);

		/* 00h */ Vector3 lower;
		/* 0Ch */ Vector3 upper;

		/// Recalculates the bounding box after having applied the given transform.
		/// @param transform The transformation to apply to the bounding box.
		void ApplyTransform(const Transform& transform);

		/// Returns the center of this bounding box.
		Vector3 GetCenter() const;

		/// Tells whether this bounding box contains the given point.
		/// @param point
		bool Contains(const Vector3& point) const;

		/// Finds the intersection between two bounding boxes. The return value will indicate
		/// whether this bbox and the other intersect anywhere (`true`) or not (`false`);
		/// optionally, you can pass another bounding box where the intersection will be written.
		///
		/// The method will return true if the resulting intersection box is degenerate, that is, has volume 0;
		/// this means taht bounding boxes that only intersect in one point, line or plane return false.
		///
		/// @param other The other bounding box to intersect with.
		/// @param[out] dst [Optional] Where the intersection will be written. Points inside this bbox are contained in both bbox.
		/// @return `true` if the bounding boxes intersect, `false` otherwise.
		bool Intersect(const BoundingBox& other, BoundingBox& dst = BoundingBox()) const;
	};

	namespace Addresses(BoundingBox) {
		DeclareAddress(ApplyTransform);
	}

	/// Converts the given HSV color into a RGB color.
	ColorRGB HSVtoRGB(const ColorHSV& hsv);

	/// Converts the given RGB color into a HSV color.
	ColorHSV RGBtoHSV(const ColorRGB& rgb);

	struct RandomNumberGenerator {
		RandomNumberGenerator(int32_t seed = -1);

		/// Generates a random integer between 0 and the given parameter, included.
		/// @param range The maximum value that can be generated.
		int RandomInt(int range);

		/// Generates a random float number between 0.0 and 1.0.
		float RandomFloat();

		int32_t seed;
	};

	/// Returns the generic random number generator.
	inline RandomNumberGenerator& GetRNG() {
		return *(RandomNumberGenerator*)(GetAddress(Math, RandomNumberGenerator_ptr));
	}

	/// Generates a random integer between 0 and the given parameter, included.
	/// This uses the default RNG, which uses the time stamp as seed.
	/// @param range The maximum value that can be generated.
	inline int rand(int range) {
		return GetRNG().RandomInt(range);
	}

	/// Generates a random float number between 0.0 and 1.0.
	/// This uses the default RNG, which uses the time stamp as seed.
	inline float randf() {
		return GetRNG().RandomFloat();
	}

	/// Generates a random float number between minValue and maxValue.
	/// This uses the default RNG, which uses the time stamp as seed.
	/// @param minValue The minimum possible value.
	/// @param maxValue The maximum possible value.
	inline float randf(float minValue, float maxValue) {
		return GetRNG().RandomFloat() * (maxValue - minValue) + minValue;
	}

	namespace Addresses(RandomNumberGenerator) {
		DeclareAddress(RandomInt);
		DeclareAddress(RandomFloat);
	}
};

namespace Math
{
	inline ColorRGB::ColorRGB(Color color)
	{
		r = color.r / 255.0f;
		g = color.g / 255.0f;
		b = color.b / 255.0f;
	}

	inline ColorRGB& ColorRGB::Set(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		return *this;
	}
	inline ColorRGBA& ColorRGBA::Set(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		return *this;
	}
	inline ColorHSV& ColorHSV::Set(float h, float s, float v) {
		this->h = h;
		this->s = s;
		this->v = v;
		return *this;
	}

	inline Color ColorRGBA::ToIntColor()
	{
		Math::Color dstColor;
		dstColor.r = (uint8_t)roundf(r * 255.0f);
		dstColor.g = (uint8_t)roundf(g * 255.0f);
		dstColor.b = (uint8_t)roundf(b * 255.0f);
		dstColor.a = (uint8_t)roundf(a * 255.0f);

		return dstColor;
	}

	inline Color ColorRGB::ToIntColor()
	{
		Math::Color dstColor;
		dstColor.r = (uint8_t)roundf(r * 255.0f);
		dstColor.g = (uint8_t)roundf(g * 255.0f);
		dstColor.b = (uint8_t)roundf(b * 255.0f);
		dstColor.a = 255;

		return dstColor;
	}

	inline Color::Color() : value(0) {}
	inline Color::Color(const Color& color) : value(color.value) {}
	inline Color::Color(uint32_t color) : value(color) {}
	inline Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
		: r(_r), g(_g), b(_b), a(_a) {}

	inline Vector2::Vector2(const Vector2& other) : Vector2(other.x, other.y) {}
	inline Vector3::Vector3(const Vector3& other) : Vector3(other.x, other.y, other.z) {}
	inline Vector4::Vector4(const Vector4& other) : Vector4(other.x, other.y, other.z, other.w) {}
	inline Quaternion::Quaternion(const Quaternion& other) : Quaternion(other.x, other.y, other.z, other.w) {}
	inline Point::Point(const Point& other) : Point(other.x, other.y) {}

	inline Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
	{
	}
	inline Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{
	}
	inline Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}
	inline Quaternion::Quaternion(float _x, float _y, float _z, float _w) : Vector4(_x, _y, _z, _w)
	{
	}
	inline Rectangle::Rectangle(float _x1, float _y1, float _x2, float _y2) :
		x1(_x1), y1(_y1), x2(_x2), y2(_y2)
	{
	}
	inline Point::Point(float _x, float _y) :
		x(_x), y(_y)
	{
	}
	inline Dimensions::Dimensions(float _width, float _height) :
		width(_width), height(_height)
	{
	}
	inline IntDimensions::IntDimensions(int _width, int _height) :
		width(_width), height(_height)
	{
	}
	inline ColorHSV::ColorHSV(float _h, float _s, float _v) : h(_h), s(_s), v(_v)
	{
	}
	inline ColorRGB::ColorRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{
	}
	inline ColorRGBA::ColorRGBA(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
	{
	}
	inline ColorRGBA::ColorRGBA(ColorRGB color, float _a) : r(color.r), g(color.g), b(color.b), a(_a)
	{}

	inline Vector2::Vector2() : x(0), y(0) {}
	inline Vector3::Vector3() : x(0), y(0), z(0) {}
	inline Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
	inline Quaternion::Quaternion() : Vector4(0, 0, 0, 1.0f) {}
	inline Rectangle::Rectangle() : x1(0), y1(0), x2(0), y2(0) {}
	inline Point::Point() : x(0), y(0) {}
	inline Dimensions::Dimensions() : width(0), height(0) {}
	inline IntDimensions::IntDimensions() : width(0), height(0) {}
	inline ColorHSV::ColorHSV() : h(0), s(0), v(0) {}
	inline ColorRGB::ColorRGB() : r(0), g(0), b(0) {}
	inline ColorRGBA::ColorRGBA() : r(0), g(0), b(0), a(0) {}

	inline BoundingBox::BoundingBox()
		: lower(-1.0f, -1.0f, -1.0f)
		, upper(1.0f, 1.0f, 1.0f)
	{
	}
	inline BoundingBox::BoundingBox(const Vector3& l, const Vector3& u)
		: lower(l)
		, upper(u)
	{
	}

	inline Matrix3::Matrix3() : m() {}
	inline Matrix4::Matrix4() : m() {}

	inline Matrix3::Matrix3(const Matrix3& other) {
		memcpy_s(m, sizeof(float) * 3 * 3, other.m, sizeof(float) * 3 * 3);
	}
	inline Matrix4::Matrix4(const Matrix4& other) {
		memcpy_s(m, sizeof(float) * 4 * 4, other.m, sizeof(float) * 4 * 4);
	}

	inline Vector3 operator*(Matrix3 a, const Vector3& b) {
		return {
			a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z,
			a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z,
			a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z,
		};
	}

	inline Matrix3 operator*(Matrix3 a, const Matrix3& b) {
		Matrix3 r;
		r.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0];
		r.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1];
		r.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2];

		r.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0];
		r.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1];
		r.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2];

		r.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0];
		r.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1];
		r.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2];
		return r;
	}

	inline Quaternion operator*(Quaternion a, const Quaternion& b) {
		Quaternion q;
		q.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
		q.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
		q.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
		q.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
		return q;
	}


	/// POINT 

	inline Point& Point::operator+=(const Point& b) {
		x += b.x;
		y += b.y;
		return *this;
	}
	inline Point& Point::operator+=(float b) {
		x += b;
		y += b;
		return *this;
	}
	inline Point& Point::operator-=(const Point& b) {
		x -= b.x;
		y -= b.y;
		return *this;
	}
	inline Point& Point::operator-=(const float b) {
		x -= b;
		y -= b;
		return *this;
	}
	inline Point& Point::operator*=(float b) {
		x *= b;
		y *= b;
		return *this;
	}
	inline Point& Point::operator/=(float b) {
		x /= b;
		y /= b;
		return *this;
	}

	inline Point operator+(Point a, const Point& b) {
		return a += b;
	}
	inline Point operator+(Point a, float b) {
		return a += b;
	}
	inline Point operator-(Point a, const Point& b) {
		return a -= b;
	}
	inline Point operator-(Point a, float b) {
		return a -= b;
	}
	inline Point operator*(Point a, float b) {
		return a *= b;
	}
	inline Point operator/(Point a, float b) {
		return a /= b;
	}

	inline Point operator-(const Point& a) {
		return { -a.x, -a.y };
	}

	inline Point operator+(float a, const Point& b) {
		return b + a;
	}
	inline Point operator-(float a, const Point& b) {
		return -b + a;
	}
	inline Point operator*(float a, const Point& b) {
		return b * a;
	}

	/// VECTOR 2

	inline Vector2& Vector2::operator+=(const Vector2& b) {
		x += b.x;
		y += b.y;
		return *this;
	}
	inline Vector2& Vector2::operator+=(float b) {
		x += b;
		y += b;
		return *this;
	}
	inline Vector2& Vector2::operator-=(const Vector2& b) {
		x -= b.x;
		y -= b.y;
		return *this;
	}
	inline Vector2& Vector2::operator-=(const float b) {
		x -= b;
		y -= b;
		return *this;
	}
	inline Vector2& Vector2::operator*=(float b) {
		x *= b;
		y *= b;
		return *this;
	}
	inline Vector2& Vector2::operator/=(float b) {
		x /= b;
		y /= b;
		return *this;
	}

	inline Vector2 operator+(Vector2 a, const Vector2& b) {
		return a += b;
	}
	inline Vector2 operator+(Vector2 a, float b) {
		return a += b;
	}
	inline Vector2 operator-(Vector2 a, const Vector2& b) {
		return a -= b;
	}
	inline Vector2 operator-(Vector2 a, float b) {
		return a -= b;
	}
	inline Vector2 operator*(Vector2 a, float b) {
		return a *= b;
	}
	inline Vector2 operator/(Vector2 a, float b) {
		return a /= b;
	}

	inline Vector2 operator-(const Vector2& a) {
		return { -a.x, -a.y };
	}

	inline Vector2 operator+(float a, const Vector2& b) {
		return b + a;
	}
	inline Vector2 operator-(float a, const Vector2& b) {
		return -b + a;
	}
	inline Vector2 operator*(float a, const Vector2& b) {
		return b * a;
	}

	inline float Vector2::Length() const {
		return sqrtf(x * x + y * y);
	}

	inline Vector2 Vector2::Normalized() const {
		return *this / Length();
	}

	inline float Vector2::Dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	/// VECTOR 3

	inline Vector3& Vector3::operator+=(const Vector3& b) {
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}
	inline Vector3& Vector3::operator+=(float b) {
		x += b;
		y += b;
		z += b;
		return *this;
	}
	inline Vector3& Vector3::operator-=(const Vector3& b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
	inline Vector3& Vector3::operator-=(const float b) {
		x -= b;
		y -= b;
		z -= b;
		return *this;
	}
	inline Vector3& Vector3::operator*=(float b) {
		x *= b;
		y *= b;
		z *= b;
		return *this;
	}
	inline Vector3& Vector3::operator/=(float b) {
		x /= b;
		y /= b;
		z /= b;
		return *this;
	}

	inline Vector3 operator+(Vector3 a, const Vector3& b) {
		return a += b;
	}
	inline Vector3 operator+(Vector3 a, float b) {
		return a += b;
	}
	inline Vector3 operator-(Vector3 a, const Vector3& b) {
		return a -= b;
	}
	inline Vector3 operator-(Vector3 a, float b) {
		return a -= b;
	}
	inline Vector3 operator*(Vector3 a, float b) {
		return a *= b;
	}
	inline Vector3 operator/(Vector3 a, float b) {
		return a /= b;
	}

	inline Vector3 operator-(const Vector3& a) {
		return {-a.x, -a.y, -a.z};
	}

	inline Vector3 operator+(float a, const Vector3& b) {
		return b + a;
	}
	inline Vector3 operator-(float a, const Vector3& b) {
		return -b + a;
	}
	inline Vector3 operator*(float a, const Vector3& b) {
		return b * a;
	}


	inline float Vector3::Length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	inline float Vector3::SquaredLength() const {
		return x * x + y * y + z * z;
	}

	inline Vector3 Vector3::Normalized() const {
		return *this / Length();
	}

	inline float Vector3::Dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	inline Vector3 Vector3::Cross(const Vector3& b) const {
		return {
			y * b.z - z * b.y,
			z * b.x - x * b.z,
			x * b.y - y * b.x
		};
	}


	/// VECTOR 4

	inline Vector4& Vector4::operator+=(const Vector4& b) {
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return *this;
	}
	inline Vector4& Vector4::operator+=(float b) {
		x += b;
		y += b;
		z += b;
		w += b;
		return *this;
	}
	inline Vector4& Vector4::operator-=(const Vector4& b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return *this;
	}
	inline Vector4& Vector4::operator-=(const float b) {
		x -= b;
		y -= b;
		z -= b;
		w -= b;
		return *this;
	}
	inline Vector4& Vector4::operator*=(float b) {
		x *= b;
		y *= b;
		z *= b;
		w *= b;
		return *this;
	}
	inline Vector4& Vector4::operator/=(float b) {
		x /= b;
		y /= b;
		z /= b;
		w /= b;
		return *this;
	}

	inline Vector4 operator-(const Vector4& a) {
		return { -a.x, -a.y, -a.z, -a.w };
	}

	inline Vector4 operator+(Vector4 a, const Vector4& b) {
		return a += b;
	}
	inline Vector4 operator+(Vector4 a, float b) {
		return a += b;
	}
	inline Vector4 operator-(Vector4 a, const Vector4& b) {
		return a -= b;
	}
	inline Vector4 operator-(Vector4 a, float b) {
		return a -= b;
	}
	inline Vector4 operator*(Vector4 a, float b) {
		return a *= b;
	}
	inline Vector4 operator/(Vector4 a, float b) {
		return a /= b;
	}

	inline Vector4 operator+(float a, const Vector4& b) {
		return b + a;
	}
	inline Vector4 operator-(float a, const Vector4& b) {
		return -b + a;
	}
	inline Vector4 operator*(float a, const Vector4& b) {
		return b * a;
	}


	inline float Vector4::Length() const {
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	inline Vector4 Vector4::Normalized() const {
		return *this / Length();
	}

	inline float Vector4::Dot(const Vector4& other) const {
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}



	template <>
	inline ColorRGB lerp<ColorRGB>(const ColorRGB& a, const ColorRGB& b, float mix) {
		return { lerp(a.r, b.r, mix), lerp(a.g, b.g, mix), lerp(a.b, b.b, mix) };
	}

	template <>
	inline ColorRGBA lerp<ColorRGBA>(const ColorRGBA& a, const ColorRGBA& b, float mix) {
		return { lerp(a.r, b.r, mix), lerp(a.g, b.g, mix), lerp(a.b, b.b, mix), lerp(a.a, b.a, mix) };
	}


	inline Vector3 BoundingBox::GetCenter() const {
		return (lower + upper) / 2.0f;
	}



	inline bool Vector2::operator==(const Vector2& b) const {
		return x == b.x && y == b.y;
	}
	inline bool Vector2::operator!=(const Vector2& b) const {
		return x != b.x || y != b.y;
	}

	inline bool Vector3::operator==(const Vector3& b) const {
		return x == b.x && y == b.y && z == b.z;
	}
	inline bool Vector3::operator!=(const Vector3& b) const {
		return x != b.x || y != b.y || z != b.z;
	}

	inline bool Vector4::operator==(const Vector4& b) const {
		return x == b.x && y == b.y && z == b.z && w == b.w;
	}
	inline bool Vector4::operator!=(const Vector4& b) const {
		return x != b.x || y != b.y || z != b.z || w != b.w;
	}

	inline bool Point::operator==(const Point& b) const {
		return x == b.x && y == b.y;
	}
	inline bool Point::operator!=(const Point& b) const {
		return x != b.x || y != b.y;
	}

	inline bool ColorRGB::operator==(const ColorRGB& b) const {
		return r == b.r && g == b.g && this->b == b.b;
	}
	inline bool ColorRGB::operator!=(const ColorRGB& b) const {
		return r != b.r || g != b.g || this->b != b.b;
	}

	inline bool ColorRGBA::operator==(const ColorRGBA& b) const {
		return r == b.r && g == b.g && this->b == b.b && a == b.a;
	}
	inline bool ColorRGBA::operator!=(const ColorRGBA& b) const {
		return r != b.r || g != b.g || this->b != b.b || a != b.a;
	}
}