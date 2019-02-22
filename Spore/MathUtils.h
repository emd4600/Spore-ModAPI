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

namespace InternalAddressList(Math)
{
	DefineAddress(MultiplyVectorScalar, GetAddress(0x41DB70, 0x41DC60, 0x41DC60));
	DefineAddress(EulerToMatrix, GetAddress(0x453AD0, 0x453DF0, 0x453DF0));
	DefineAddress(MatrixToEuler, GetAddress(0x6A3BA0, 0x6A3920, 0x6A3920));

	DefineAddress(RandomNumberGenerator_ptr, GetAddress(0x16059E8, NO_ADDRESS, 0x1601760));
}

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

		inline float length() const {
			sqrtf(x*x + y*y);
		}
	};

	/// A vector of 3 float values (x, y, z).
	struct Vector3 {
		float x;
		float y;
		float z;
		Vector3();
		Vector3(const Vector3& other);
		Vector3(float x, float y, float z);

		inline float length() const {
			return sqrtf(x*x + y*y + z*z);
		}

		inline Vector3& operator+=(const Vector3& b) {
			x += b.x;
			y += b.y;
			z += b.z;
			return *this;
		}

		inline Vector3& operator+=(const float b) {
			x += b;
			y += b;
			z += b;
			return *this;
		}

		friend Vector3 operator+(Vector3 a, const Vector3& b) {
			return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
		}

		friend Vector3 operator+(Vector3 a, float b) {
			return Vector3(a.x + b, a.y + b, a.z + b);
		}

		inline Vector3& operator-=(const Vector3& b) {
			x -= b.x;
			y -= b.y;
			z -= b.z;
			return *this;
		}

		inline Vector3& operator-=(const float b) {
			x -= b;
			y -= b;
			z -= b;
			return *this;
		}

		friend Vector3 operator-(Vector3 a, const Vector3& b) {
			return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		}

		friend Vector3 operator-(Vector3 a, float b) {
			return Vector3(a.x - b, a.y - b, a.z - b);
		}

		inline Vector3& operator*=(float b) {
			x *= b;
			y *= b;
			z *= b;
			return *this;
		}

		friend Vector3 operator*(Vector3 a, float b) {
			return Vector3(a.x * b, a.y * b, a.z * b);
		}

		inline Vector3& operator/=(float b) {
			x /= b;
			y /= b;
			z /= b;
			return *this;
		}

		friend Vector3 operator/(Vector3 a, float b) {
			return Vector3(a.x / b, a.y / b, a.z / b);
		}

		inline Vector3 normalized() {
			return *this / length();
		}
	};

	/// A vector of 3 float values representing euler angles; it's the same as a Vector3.
	typedef Vector3 Euler;

	/// A vector of 4 float values (x, y, z, w).
	struct Vector4 {
		float x;
		float y;
		float z;
		float w;
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector4& other);
		Vector4();
	};

	/// A vector of 4 float values (x, y, z, w) representing a quaternion rotation; same as a Vector4.
	/// Hasa value of (0, 0, 0, 1) by default.
	struct Quaternion : Vector4
	{
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Quaternion& other);
		Quaternion();
	};

	/// Represents a point in the space, defined by two float coordinates (x, y).
	struct Point {
		float x;
		float y;
		Point(float x, float y);
		Point(const Point& other);
		Point();
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

		inline void SetValue(float r, float g, float b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		/// Returns the integer representation of the given color (in the form of a Color value).
		static Color ToIntColor(const ColorRGB& color);
	};
	/// Four float values in the range [0, 1] that represent a color (the red, green, blue and alpha components).
	/// The alpha component defines the opacity of the color: 0 alpha is fully transparent, 1 alpha is fully opaque.
	struct ColorRGBA {
		float r;
		float g;
		float b;
		float a;
		ColorRGBA(float r, float g, float b, float a);
		ColorRGBA();

		/// Returns the integer representation of the given color (in the form of a Color value).
		static Color ToIntColor(const ColorRGBA& color);
	};
	/// Three float values that represent a color (the hue, saturation and value/brightness values).
	struct ColorHSV {
		float h;
		float s;
		float v;
		ColorHSV(float h, float s, float v);
		ColorHSV();

		inline void SetValue(float h, float s, float v) {
			this->h = h;
			this->s = s;
			this->v = v;
		}

	};

	/// A 3x3 matrix.
	struct Matrix3 {
		float m[3][3];
		Matrix3();
		Matrix3(const Matrix3& other) {
			CALL(GetAddress(0x41CA90, 0x41CB30, 0x41CB30), void,
				PARAMS(Matrix3*, const Matrix3&), PARAMS(this, other));
		}

		void SetIdentity();
	};

	/// A 4x4 matrix.
	struct Matrix4 {
		float m[4][4];
		Matrix4();

		void SetIdentity();
	};

	/// A pair of two Vector3 that define the boundaries of an object (the minimum point and the maximum point in the space).
	struct BoundingBox {
		BoundingBox();

		/* 00h */ Vector3 min;
		/* 0Ch */ Vector3 max;
	};

	///
	/// Multiplies the given vector with a scalar value and puts the result in a new Vector3. 
	/// Scalar multiplication is just multiplying all the components of the vector with the number
	/// @param source The source Vector3 to multiply.
	/// @param scalar The float multiplicand.
	/// @returns A new Vector3 with the result.
	///
	Vector3 MultiplyVectorScalar(const Vector3& source, float& scalar);

	///
	/// Converts the given euler angles into a 3x3 rotation matrix. The euler angles is 
	/// a vector of 3 values, which are the X, Y and Z axis rotations respectively. The
	/// angles must be in radians.
	/// @param angles The 3 euler angles, in radians.
	/// @returns A new 3x3 rotation matrix with the result.
	///
	Matrix3 EulerToMatrix(const Euler& angles);

	///
	/// Converts the given 3x3 rotation matrix to the 3 corresponding euler angles, in radians.
	/// @param matrix The 3x3 rotation matrix to convert.
	/// @returns The 3 euler angles (for the X, Y and Z axis), in radians.
	///
	Euler MatrixToEuler(const Matrix3& matrix);

	/// Converts the given HSV color into a RGB color.
	ColorRGB HSVtoRGB(const ColorHSV& hsv);

	/// Converts the given RGB color into a HSV color.
	ColorHSV RGBtoHSV(const ColorRGB& rgb);

	struct RandomNumberGenerator {
		int GenerateRandomInt(int range);
	};

	inline RandomNumberGenerator& GetRNG() {
		return *(RandomNumberGenerator*)(GetMethodAddress(Math, RandomNumberGenerator_ptr));
	}

	/// Generates a random integer between 0 and the given parameter, included.
	/// @param range The maximum value that can be generated.
	inline int random(int range) {
		return GetRNG().GenerateRandomInt(range);
	}

	namespace InternalAddressList(RandomNumberGenerator) {
		DefineAddress(GenerateRandomInt, GetAddress(0xA68FA0, NO_ADDRESS, 0xA68F70));
	}
};