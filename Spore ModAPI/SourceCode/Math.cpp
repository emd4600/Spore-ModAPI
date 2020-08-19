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
#include <algorithm>

namespace Math
{
	const Vector2 Vector2::ZERO = { 0, 0 };
	const Vector3 Vector3::ZERO = { 0, 0, 0 };

	const Color Color::RED =	Color(255, 0, 0, 255);
	const Color Color::BLUE =	Color(0, 0, 255, 255);
	const Color Color::GREEN =	Color(0, 255, 0, 255);
	const Color Color::WHITE =	Color(255, 255, 255, 255);
	const Color Color::BLACK =	Color(0, 0, 0, 255);

	const float PI2 = 2 * PI;

	float GetAngleDifference(float angle1, float angle2)
	{

		angle1 = fmodf(angle1, PI2);
		// convert to [-PI, PI]
		if (angle1 >= PI) angle1 = angle1 - PI2;

		angle2 = fmodf(angle2, PI2);
		// convert to [-PI, PI]
		if (angle2 >= PI) angle2 = angle2 - PI2;

		float minAngle = min(angle1, angle2);
		float maxAngle = max(angle1, angle2);

		float result = PI2 - maxAngle + minAngle;
		if ((maxAngle - minAngle) <= result)
			result = maxAngle - minAngle;
		return result;
	}

	float IncrementAngleTo(float a1, float a2, float inc)
	{
		if (inc < GetAngleDifference(a1, a2))
		{
			float result;
			if (GetAngleDifference(a1 - inc, a2) <= GetAngleDifference(a1 + inc, a2)) {
				result = a1 - inc;
			}
			else {
				result = a1 + inc;
			}
			result = fmodf(result, PI2);
			if (result >= PI) result = result - PI2;
			return result;
		}
		else return a2;
	}

	float CorrectAngleRange(float angle)
	{
		angle = fmodf(angle, PI2);
		if (angle <= PI)
		{
			if (-PI > angle) return angle + PI2;
			return angle;
		}
		else {
			return angle - PI2;
		}
	}

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
		STATIC_CALL(GetAddress(Math, MatrixToEuler), void, Args(Vector3&, const Matrix3&), Args(dst, *this));
		return dst;
	}

	Matrix3 Matrix3::FromEuler(const Vector3& angles) {
		Matrix3 dst;
		STATIC_CALL(GetAddress(Math, EulerToMatrix), void, Args(Matrix3&, const Vector3&), Args(dst, angles));
		return dst;
	}

	Matrix3 Matrix3::FromAxisAngle(const Vector3& axis, float angle) {
		Vector3 a = axis.Normalized();
		Matrix3 dst;
		float c = cosf(angle);
		float s = sinf(angle);
		float cx = (1.0f - c) * a.x;
		float cy = (1.0f - c) * a.y;
		float cz = (1.0f - c) * a.z;

		dst.m[0][0] = a.x * cx + c;
		dst.m[0][1] = a.x * cy - a.z * s;
		dst.m[0][2] = a.x * cz + a.y * s;

		dst.m[1][0] = a.y * cx + a.z * s;
		dst.m[1][1] = a.y * cy + c;
		dst.m[1][2] = a.y * cz - a.x * s;

		dst.m[2][0] = a.z * cx - a.y * s;
		dst.m[2][1] = a.z * cy + a.x * s;
		dst.m[2][2] = a.z * cz + c;
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
		d.m[0][1] = 2.0f * (tmp1 + tmp2) * invs;
		d.m[1][0] = 2.0f * (tmp1 - tmp2) * invs;

		tmp1 = x * z;
		tmp2 = y * w;
		d.m[0][2] = 2.0f * (tmp1 - tmp2) * invs;
		d.m[2][0] = 2.0f * (tmp1 + tmp2) * invs;
		tmp1 = y * z;
		tmp2 = x * w;
		d.m[1][2] = 2.0f * (tmp1 + tmp2) * invs;
		d.m[2][1] = 2.0f * (tmp1 - tmp2) * invs;

		return d;
	}

	Quaternion Matrix3::ToQuaternion() const {
		Quaternion q;
		float trace = m[0][0] + m[1][1] + m[2][2];
		if (trace > 0) {  // maybe should use epsilon here
			float s = 0.5f / sqrtf(trace + 1.0f);
			q.w = 0.25f / s;
			q.x = (m[1][2] - m[2][1]) * s;
			q.y = (m[2][0] - m[0][2]) * s;
			q.z = (m[0][1] - m[1][0]) * s;
		}
		else {
			if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
				float s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
				q.w = (m[2][1] - m[1][2]) / s;
				q.x = 0.25f * s;
				q.y = (m[0][1] + m[1][0]) / s;
				q.z = (m[0][2] + m[2][0]) / s;
			}
			else if (m[1][1] > m[2][2]) {
				float s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
				q.w = (m[2][0] - m[0][2]) / s;
				q.x = (m[1][0] + m[0][1]) / s;
				q.y = 0.25f * s;
				q.z = (m[2][1] + m[1][2]) / s;
			}
			else {
				float s = 2.0f * sqrtf(1.0f + m[2][2] - m[0][0] - m[1][1]);
				q.w = (m[0][1] - m[1][0]) / s;
				q.x = (m[2][0] + m[0][2]) / s;
				q.y = (m[2][1] + m[1][2]) / s;
				q.z = 0.25f * s;
			}
		}
		return q;
	}

	Vector3 Matrix3::Row(int index) const
	{
		return { m[index][0], m[index][1], m[index][2] };
	}
	Vector3 Matrix3::Column(int index) const
	{
		return { m[0][index], m[1][index], m[2][index] };
	}

	auto_METHOD_VOID(BoundingBox, ApplyTransform, Args(const Transform& t), Args(t));


	Matrix3 Matrix3::Transposed() const {
		Matrix3 dst;

		dst.m[0][0] = m[0][0];
		dst.m[0][1] = m[1][0];
		dst.m[0][2] = m[2][0];
		dst.m[1][0] = m[0][1];
		dst.m[1][1] = m[1][1];
		dst.m[1][2] = m[2][1];
		dst.m[2][0] = m[0][2];
		dst.m[2][1] = m[1][2];
		dst.m[2][2] = m[2][2];

		return dst;
	}
	Matrix4 Matrix4::Transposed() const {
		Matrix4 dst;

		dst.m[0][0] = m[0][0];
		dst.m[0][1] = m[1][0];
		dst.m[0][2] = m[2][0];
		dst.m[0][3] = m[3][0];
		dst.m[1][0] = m[0][1];
		dst.m[1][1] = m[1][1];
		dst.m[1][2] = m[2][1];
		dst.m[1][3] = m[3][1];
		dst.m[2][0] = m[0][2];
		dst.m[2][1] = m[1][2];
		dst.m[2][2] = m[2][2];
		dst.m[2][3] = m[3][2];
		dst.m[3][0] = m[0][3];
		dst.m[3][1] = m[1][3];
		dst.m[3][2] = m[2][3];
		dst.m[3][3] = m[3][3];

		return dst;
	}

	Matrix3 Matrix3::LookAt(const Vector3& position, const Vector3& target, const Vector3& up) {
		auto dir = (target - position).Normalized();
		auto right = (up.Cross(dir)).Normalized();
		auto cameraUp = dir.Cross(right).Normalized();

		Matrix3 m;
		m.m[0][0] = -right.x;
		m.m[0][1] = -right.y;
		m.m[0][2] = -right.z;
		m.m[1][0] = dir.x;
		m.m[1][1] = dir.y;
		m.m[1][2] = dir.z;
		m.m[2][0] = cameraUp.x;
		m.m[2][1] = cameraUp.y;
		m.m[2][2] = cameraUp.z;

		return m;
	}

	Matrix3 Matrix4::To3x3() const {
		Matrix3 dst;
		dst.m[0][0] = m[0][0];
		dst.m[0][1] = m[0][1];
		dst.m[0][2] = m[0][2];
		dst.m[1][0] = m[1][0];
		dst.m[1][1] = m[1][1];
		dst.m[1][2] = m[1][2];
		dst.m[2][0] = m[2][0];
		dst.m[2][1] = m[2][1];
		dst.m[2][2] = m[2][2];
		return dst;
	}

	float Vector3::AngleTo(const Vector3& other) const {
		return acosf(this->Dot(other) / (other.Length() * this->Length()));
	}

	float Vector3::OrientedAngle(const Vector3& _v1, const Vector3& _v2, const Vector3& orientationAxis)
	{
		auto v1 = _v1.Normalized();
		auto v2 = _v2.Normalized();

		if (v1 == v2) return 0.0f;

		float angle = acosf(clamp(v1.Dot(v2), -1.0f, 1.0f));

		if (orientationAxis.Dot(v1.Cross(v2)) < 0) angle = 2 * PI - angle;
		return angle;
	}

	Quaternion Quaternion::FromRotation(const Vector3& axis, float angle) {
		Vector3 a = axis.Normalized();
		Quaternion q;
		q.w = cosf(angle / 2.0f);
		q.x = sinf(angle / 2.0f) * a.x;
		q.y = sinf(angle / 2.0f) * a.y;
		q.z = sinf(angle / 2.0f) * a.z;
		return q;
	}

	Quaternion Quaternion::FromEuler(const Vector3& angles) {
		float cy = cosf(angles.z * 0.5f);
		float sy = sinf(angles.z * 0.5f);
		float cp = cosf(angles.y * 0.5f);
		float sp = sinf(angles.y * 0.5f);
		float cr = cosf(angles.x * 0.5f);
		float sr = sinf(angles.x * 0.5f);

		Quaternion q;
		q.w = cy * cp * cr + sy * sp * sr;
		q.x = cy * cp * sr - sy * sp * cr;
		q.y = sy * cp * sr + cy * sp * cr;
		q.z = sy * cp * cr - cy * sp * sr;

		return q;
	}

	Vector3 Quaternion::ToEuler() const {
		Vector3 angles;

		// roll (x-axis rotation)
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		angles.x = std::atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		float sinp = 2 * (w * y - z * x);
		if (std::abs(sinp) >= 1)
			angles.y = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
		else
			angles.y = std::asin(sinp);

		// yaw (z-axis rotation)
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		angles.z = std::atan2(siny_cosp, cosy_cosp);

		return angles;
	}

	Quaternion Quaternion::Inverse() const {
		float a = 1.0f / (w * w + x * x + y * y + z * z);
		Quaternion q;
		q.w = w * a;
		q.x = -x * a;
		q.y = -y * a;
		q.z = -z * a;
		return q;
	}

	// from here https://bitbucket.org/sinbad/ogre/src/9db75e3ba05c/OgreMain/include/OgreVector3.h#cl-651
	Quaternion Quaternion::GetRotationTo(const Vector3& from, const Vector3& to, const Vector3& fallbackAxis)
	{
		Vector3 v0 = from.Normalized();
		Vector3 v1 = to.Normalized();

		float d = v0.Dot(v1);
		if (d >= 1.0f) return Quaternion();
		else if (d < (1e-6f - 1.0f))
		{
			// Parallel but opposite, rotate around fallback axis
			if (fallbackAxis == Vector3::ZERO)
			{
				// Generate an axis
				Vector3 axis = X_AXIS.Cross(v0);
				if (axis.Length() < 1e-8) // pick another if colinear
					axis = Y_AXIS.Cross(v1);
				axis = axis.Normalized();
			}

			return Quaternion::FromRotation(fallbackAxis, PI);
		}
		else
		{
			float s = sqrt((1 + d) * 2);
			float invs = 1 / s;

			Vector3 c = v0.Cross(v1);

			Quaternion q;
			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;

			float l = q.Length();
			q.x /= l;
			q.y /= l;
			q.z /= l;
			q.w /= l;
			
			return q;
		}
	}


	bool BoundingBox::Contains(const Vector3& point) const
	{
		return (point.x >= lower.x && point.x <= upper.x)
			&& (point.y >= lower.y && point.y <= upper.y)
			&& (point.z >= lower.z && point.z <= upper.z);
	}

	bool BoundingBox::Intersect(const BoundingBox& other, BoundingBox& dst) const
	{
		dst.lower.x = max(lower.x, other.lower.x);
		dst.upper.x = min(upper.x, other.upper.x);
		if (dst.lower.x >= dst.upper.x) return false;

		dst.lower.y = max(lower.y, other.lower.y);
		dst.upper.y = min(upper.y, other.upper.y);
		if (dst.lower.y >= dst.upper.y) return false;

		dst.lower.z = max(lower.z, other.lower.z);
		dst.upper.z = min(upper.z, other.upper.z);
		if (dst.lower.z >= dst.upper.z) return false;

		return true;
	}
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

RedirectMethod_noargs_structret_const(Transform, ToMatrix4, Math::Matrix4);


RandomNumberGenerator::RandomNumberGenerator(int32_t seed)
{
	if (seed == -1) seed = static_cast<int32_t>(time(0));
	this->seed = seed;
}

auto_METHOD(RandomNumberGenerator, int, RandomInt, Args(int range), Args(range));
auto_METHOD_(RandomNumberGenerator, float, RandomFloat);


void Transform::Invert()
{
	mfScale = 1.0f / mfScale;
	// We can transpose instead of inverting, as rotation matrices are ortogonal
	mRotation = mRotation.Transposed();
	mOffset = mRotation * (-mfScale * mOffset);
}


bool PlaneEquation::IsOnPlane(const Vector3& point, float epsilon) const {
	return abs(a * point.x + b * point.y + c * point.z + d) <= epsilon;
}

PlaneEquation::Intersection PlaneEquation::IntersectRay(const Vector3& point, const Vector3& direction, Vector3& dst)
{
	Vector3 pointOnPlane;
	if (a != 0.0f) pointOnPlane.x = -d / a;
	else if (b != 0.0f) pointOnPlane.y = -d / b;
	else if (c != 0.0f) pointOnPlane.z = -d / c;
	else return Intersection::None;  // invalid plane

	Vector3 normal = { a, b, c };
	float nominator = (pointOnPlane - point).Dot(normal);
	float denominator = direction.Dot(normal);
	if (denominator == 0.0f) {
		// line is parallel, two possible cases
		if (nominator == 0.0f) return Intersection::InPlane;
		else return Intersection::None;
	}
	else {
		float p = nominator / denominator;
		// We only do intersection with the positive ray
		if (p < 0.0f) return Intersection::None;
		
		dst = point + p * direction;
		return Intersection::Point;
	}
}