/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "Quaternion.h"

//Converts Euler to Quaternion
quat::Quaternion quat::EulerToQuaternion(float z, float x, float y)
{
	const float xh = x * 0.5f;
	const float yh = y * 0.5f;
	const float zh = z * 0.5f;
    const float c1 = cos(xh);
    const float s1 = sin(xh);
	const float c2 = cos(yh);
    const float s2 = sin(yh);
    const float c3 = cos(zh);
    const float s3 = sin(zh);
    const float c1c2 = c1 * c2;
    const float s1s2 = s1 * s2;

	return Quaternion(c1c2 * c3 - s1s2 * s3,
					  c1c2 * s3 + s1s2 * c3,
					  s1 * c2 * c3 + c1 * s2 * s3,
					  c1 * s2 * c3 - s1 * c2 * s3);
}

//Converts Quaternion to Euler (euclideanspace.com)
vec3::Vector3 quat::QuaternionToEuler(const Quaternion& q)
{
	float sqw, sqx, sqy, sqz, unit, test;

    sqw = q.w*q.w;
    sqx = q.v.x*q.v.x;
    sqy = q.v.y*q.v.y;
    sqz = q.v.z*q.v.z;

	unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	test = q.v.x*q.v.y + q.v.z*q.w;

	if (test > 0.499*unit) { // singularity at north pole
		return vec3::Vector3(2 * atan2(q.v.x, q.w), M_PI_2, 0);
	}

	if (test < -0.499*unit) { // singularity at south pole
		return vec3::Vector3(-2 * atan2(q.v.x, q.w), -M_PI_2, 0);
	}

	return vec3::Vector3(atan2(2*q.v.y*q.w-2*q.v.x*q.v.z, sqx - sqy - sqz + sqw),
					   asin(2*test/unit),
					   atan2(2*q.v.x*q.w-2*q.v.y*q.v.z, -sqx + sqy - sqz + sqw));
}

//Get a matrix from quaternion (normalize first)
mat4::MATRIX4 quat::QuaternionToMatrix(const Quaternion& q)
{
	float m00, m01, m02, m10, m11, m12, m20, m21, m22;

	const float sqw = q.w*q.w;
	const float sqx = q.v.x*q.v.x;
	const float sqy = q.v.y*q.v.y;
	const float sqz = q.v.z*q.v.z;

	m00 = ( sqx - sqy - sqz + sqw);
	m11 = (-sqx + sqy - sqz + sqw);
	m22 = (-sqx - sqy + sqz + sqw);

	float tmp1 = q.v.x*q.v.y;
	float tmp2 = q.v.z*q.w;
	m10 = 2.0f * (tmp1 + tmp2);
	m01 = 2.0f * (tmp1 - tmp2);

	tmp1 = q.v.x*q.v.z;
	tmp2 = q.v.y*q.w;
	m20 = 2.0f * (tmp1 - tmp2);
	m02 = 2.0f * (tmp1 + tmp2);
	tmp1 = q.v.y*q.v.z;
	tmp2 = q.v.x*q.w;
	m21 = 2.0f * (tmp1 + tmp2);
	m12 = 2.0f * (tmp1 - tmp2);

	return mat4::MATRIX4( m00, m01, m02, 0,
					m10, m11, m12, 0,
					m20, m21, m22, 0,
					0, 0, 0, 1 );
}

//Quaternion from axis angle
quat::Quaternion quat::QuaternionFromAngle(const vec3::Vector3& v, float angle)
{
	const vec3::Vector3 vn = vec3::I_Normalize(v);
	const float ha = angle * 0.5f;
	const float sa = sin(ha);
	return quat::Quaternion(cos(ha), vn.x * sa, vn.y * sa, vn.z * sa);
}

//Matrix to Quaternion
quat::Quaternion quat::MatrixToQuaternion(const mat4::MATRIX4& m)
{
	const float w = math::isqrt(1.0f + m._11 + m._22 + m._33) * 0.5f;
	const float rw4 = 1.0f / (4.0f * w);
	return quat::Quaternion(w, (m._32 - m._23) * rw4, (m._13 - m._31) * rw4, (m._21 - m._12) * rw4);
}

//Direction to Quaternion
quat::Quaternion quat::DirectionToQuaternion(const vec3::Vector3& dir)
{
	const vec3::Vector3 right = vec3::I_Normalize(vec3::CrossProduct(vec3::Vector3(0.f, 1.f, 0.f), dir));
	const vec3::Vector3 up = vec3::CrossProduct(dir, right);
	const float w = math::isqrt(1.0f + right.x + up.y + dir.z) * 0.5f;
	const float rw4 = 1.0f / (4.0f * w);
	return quat::Quaternion(w, (dir.y - up.z) * rw4, (right.z - dir.x) * rw4, (up.x - right.y) * rw4);
}