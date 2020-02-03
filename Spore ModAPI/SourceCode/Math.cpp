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
#include <ctime>
#include <EASTL\string.h>

namespace Math
{

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

	Matrix4& Matrix4::SetIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		return *this;
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

	Vector3 Matrix3::ToEuler() const {
		Vector3 dst;
		CALL(GetAddress(Math, MatrixToEuler), void, Args(Vector3&, const Matrix3&), Args(dst, *this));
		return dst;
	}

	Matrix3 Matrix3::FromEuler(const Vector3& angles) {
		Matrix3 dst;
		CALL(GetAddress(Math, EulerToMatrix), void, Args(Matrix3&, const Vector3&), Args(dst, angles));
		return dst;
	}

	Matrix3 Quaternion::ToMatrix() const {
		Matrix3 d;

		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;

		// invs (inverse square length) is only required if quaternion is not already normalised
		float invs = 1.0f / (sqx + sqy + sqz + sqw);
		d.m[0][0] = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
		d.m[1][1] = (-sqx + sqy - sqz + sqw) * invs;
		d.m[2][2] = (-sqx - sqy + sqz + sqw) * invs;

		float tmp1 = x * y;
		float tmp2 = z * w;
		d.m[1][0] = 2.0f * (tmp1 + tmp2) * invs;
		d.m[0][1] = 2.0f * (tmp1 - tmp2) * invs;

		tmp1 = x * z;
		tmp2 = y * w;
		d.m[2][0] = 2.0f * (tmp1 - tmp2) * invs;
		d.m[0][2] = 2.0f * (tmp1 + tmp2) * invs;
		tmp1 = y * z;
		tmp2 = x * w;
		d.m[2][1] = 2.0f * (tmp1 + tmp2) * invs;
		d.m[1][2] = 2.0f * (tmp1 - tmp2) * invs;

		return d;
	}

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


RandomNumberGenerator::RandomNumberGenerator(int32_t seed)
{
	if (seed == -1) seed = static_cast<int32_t>(time(0));
	this->seed = seed;
}

auto_METHOD(RandomNumberGenerator, int, RandomInt, Args(int range), Args(range));
auto_METHOD_(RandomNumberGenerator, float, RandomFloat);

#endif
