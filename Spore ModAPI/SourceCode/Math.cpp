#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>
#include <cmath>
#include <EASTL\string.h>

namespace Math
{
	Vector2::Vector2(const Vector2& other) : Vector2(other.x, other.y) {}
	Vector3::Vector3(const Vector3& other) : Vector3(other.x, other.y, other.z) {}
	Vector4::Vector4(const Vector4& other) : Vector4(other.x, other.y, other.z, other.w) {}
	Quaternion::Quaternion(const Quaternion& other) : Quaternion(other.x, other.y, other.z, other.w) {}
	Point::Point(const Point& other) : Point(other.x, other.y) {}

	Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
	{
	}
	Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{
	}
	Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}
	Quaternion::Quaternion(float _x, float _y, float _z, float _w) : Vector4(_x, _y, _z, _w)
	{
	}
	Rectangle::Rectangle(float _x1, float _y1, float _x2, float _y2) : 
		x1(_x1), y1(_y1), x2(_x2), y2(_y2)
	{
	}
	Point::Point(float _x, float _y) :
		x(_x), y(_y)
	{
	}
	Dimensions::Dimensions(float _width, float _height) :
		width(_width), height(_height)
	{
	}
	IntDimensions::IntDimensions(int _width, int _height) :
		width(_width), height(_height)
	{
	}
	ColorHSV::ColorHSV(float _h, float _s, float _v) : h(_h), s(_s), v(_v)
	{
	}
	ColorRGB::ColorRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{
	}
	ColorRGBA::ColorRGBA(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
	{
	}
	ColorRGBA::ColorRGBA(ColorRGB color, float _a) : r(color.r), g(color.g), b(color.b), a(_a)
	{}

	Vector2::Vector2() : x(0), y(0) {}
	Vector3::Vector3() : x(0), y(0), z(0) {}
	Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
	Quaternion::Quaternion() : Vector4(0, 0, 0, 1.0f) {}
	Rectangle::Rectangle() : x1(0), y1(0), x2(0), y2(0) {}
	Point::Point() : x(0), y(0) {}
	Dimensions::Dimensions() : width(0), height(0) {}
	IntDimensions::IntDimensions() : width(0), height(0) {}
	ColorHSV::ColorHSV() : h(0), s(0), v(0) {}
	ColorRGB::ColorRGB() : r(0), g(0), b(0) {}
	ColorRGBA::ColorRGBA() : r(0), g(0), b(0), a(0) {}

	BoundingBox::BoundingBox()
		: min(-1.0f, -1.0f, -1.0f)
		, max(1.0f, 1.0f, 1.0f)
	{

	}

	Matrix3::Matrix3() : m() {}
	Matrix4::Matrix4() : m() {}

	Matrix3::Matrix3(const Matrix3& other) {
		memcpy_s(m, sizeof(float) * 3 * 3, other.m, sizeof(float) * 3 * 3);
	}
	Matrix4::Matrix4(const Matrix4& other) {
		memcpy_s(m, sizeof(float) * 4 * 4, other.m, sizeof(float) * 4 * 4);
	}

	Color::Color() : value(0) {}
	Color::Color(const Color& color) : value(color.value) {}
	Color::Color(uint32_t color) : value(color) {}
	Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
		: r(_r), g(_g), b(_b), a(_a)
	{

	}

	const Color Color::RED =	Color(255, 0, 0, 255);
	const Color Color::BLUE =	Color(0, 0, 255, 255);
	const Color Color::GREEN =	Color(0, 255, 0, 255);
	const Color Color::WHITE =	Color(255, 255, 255, 255);
	const Color Color::BLACK =	Color(0, 0, 0, 255);

	Matrix3& Matrix3::SetIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
		return *this;
	}

	void Matrix4::SetIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	Color ColorRGBA::ToIntColor(const ColorRGBA& color)
	{
		Math::Color dstColor;
		dstColor.r = (uint8_t)roundf(color.r * 255.0f);
		dstColor.g = (uint8_t)roundf(color.g * 255.0f);
		dstColor.b = (uint8_t)roundf(color.b * 255.0f);
		dstColor.a = (uint8_t)roundf(color.a * 255.0f);

		return dstColor;
	}

	Color ColorRGB::ToIntColor(const ColorRGB& color)
	{
		Math::Color dstColor;
		dstColor.r = (uint8_t)roundf(color.r * 255.0f);
		dstColor.g = (uint8_t)roundf(color.g * 255.0f);
		dstColor.b = (uint8_t)roundf(color.b * 255.0f);
		dstColor.a = 255;

		return dstColor;
	}

	ColorRGB Math::HSVtoRGB(const ColorHSV& hsv)
	{
		ColorRGB dst;
		float      hh, p, q, t, ff;
		long        i;

		if (hsv.s <= 0.0f) {       // < is bogus, just shuts up warnings
			dst.r = hsv.v;
			dst.g = hsv.v;
			dst.b = hsv.v;
			return dst;
		}
		hh = hsv.h;
		if (hh >= 360.0f) hh = 0.0f;
		hh /= 60.0f;
		i = (long)hh;
		ff = hh - i;
		p = hsv.v * (1.0f - hsv.s);
		q = hsv.v * (1.0f - (hsv.s * ff));
		t = hsv.v * (1.0f - (hsv.s * (1.0f - ff)));

		switch (i) {
		case 0:
			dst.r = hsv.v;
			dst.g = t;
			dst.b = p;
			break;
		case 1:
			dst.r = q;
			dst.g = hsv.v;
			dst.b = p;
			break;
		case 2:
			dst.r = p;
			dst.g = hsv.v;
			dst.b = t;
			break;

		case 3:
			dst.r = p;
			dst.g = q;
			dst.b = hsv.v;
			break;
		case 4:
			dst.r = t;
			dst.g = p;
			dst.b = hsv.v;
			break;
		case 5:
		default:
			dst.r = hsv.v;
			dst.g = p;
			dst.b = q;
			break;
		}
		return dst;
	}

	ColorHSV Math::RGBtoHSV(const ColorRGB& rgb) {
		float fCMax = fmax(fmax(rgb.r, rgb.g), rgb.b);
		float fCMin = fmin(fmin(rgb.r, rgb.g), rgb.b);
		float fDelta = fCMax - fCMin;
		ColorHSV dst;

		if (fDelta > 0) {
			if (fCMax == rgb.r) {
				dst.h = 60.0f * (fmod(((rgb.g - rgb.b) / fDelta), 6.0f));
			}
			else if (fCMax == rgb.g) {
				dst.h = 60.0f * (((rgb.b - rgb.r) / fDelta) + 2.0f);
			}
			else if (fCMax == rgb.b) {
				dst.h = 60.0f * (((rgb.r - rgb.g) / fDelta) + 4.0f);
			}

			if (fCMax > 0) {
				dst.s = fDelta / fCMax;
			}
			else {
				dst.s = 0;
			}

			dst.v = fCMax;
		}
		else {
			dst.h = 0;
			dst.s = 0;
			dst.v = fCMax;
		}

		if (dst.h < 0) {
			dst.h = 360.0f + dst.h;
		}

		return dst;
	}

	ColorRGB::ColorRGB(Color color)
	{
		r = color.r / 255.0f;
		g = color.g / 255.0f;
		b = color.b / 255.0f;
	}

	auto_STATIC_METHOD(Math, Vector3, MultiplyVectorScalar,
		Args(const Vector3& src, float& scalar), Args(src, scalar));

	auto_STATIC_METHOD(Math, Matrix3, EulerToMatrix,
		Args(const Euler& vector), Args(vector));

	auto_STATIC_METHOD(Math, Euler, MatrixToEuler,
		Args(const Matrix3& matrix), Args(matrix));

	auto_METHOD(RandomNumberGenerator, int, GenerateRandomInt, Args(int range), Args(range));

	auto_METHOD_VOID(BoundingBox, ApplyTransform, Args(const Transform& t), Args(t));

}

Transform::Transform()
	: mnFlags(0)
	, mnTransformCount(0)
	, mOffset()
	, mfScale(1.0f)
	, mRotation()
{
	mRotation.SetIdentity();
}

auto_METHOD_const_(Transform, Math::Matrix4, ToMatrix4);
#endif
