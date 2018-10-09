/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	TODO: Add Slerp
*/

#ifndef QUATERNION
#define QUATERNION

#include "precom.h"
#include "MathLib.h"
#include "MatrixLib.h"
#include "Vector3.h"

namespace quat
{
	//Quaternion
	class Quaternion
	{
	public:
		float w;
		vec3::Vector3 v;

		MP_INLINE Quaternion()
		{
			w = .0f;
			v.x = .0f;
			v.y = .0f;
			v.z = .0f;
		}

		MP_INLINE Quaternion(float iw, float ix, float iy, float iz)
		{
			w = iw;
			v.x = ix;
			v.y = iy;
			v.z = iz;
		}

		MP_INLINE Quaternion& operator*(const Quaternion& rhs)
		{
			const vec3::Vector3 c = vec3::CrossProduct(v, rhs.v);
			return Quaternion(rhs.w - vec3::DotProduct(v, rhs.v),
							  w * rhs.v.x + rhs.w * v.x + c.x,
							  w * rhs.v.y + rhs.w * v.y + c.y,
							  w * rhs.v.z + rhs.w * v.z + c.z);
		}

		MP_INLINE Quaternion& operator*=(const Quaternion& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		MP_INLINE Quaternion& operator*(const float rhs)
		{
			w *= rhs;
			v.x *= rhs;
			v.y *= rhs;
			v.z *= rhs;
		}

		MP_INLINE Quaternion& operator=(const float rhs)
		{
			w = rhs;
			v.x = rhs;
			v.y = rhs;
			v.z = rhs;
		}

		MP_INLINE vec3::Vector3 Quaternion::operator*(const vec3::Vector3& rhs)
		{
			const vec3::Vector3 vn = vec3::I_Normalize(rhs);
			const Quaternion resQuat = *this * (Quaternion(0.f, vn.x, vn.y, vn.z) * Quaternion(this->w, -this->v.x, -this->v.y, -this->v.z));
			return vec3::Vector3(resQuat.v.x, resQuat.v.y, resQuat.v.z);
		}
	};

	//Quaternion Operations
	Quaternion EulerToQuaternion(float x, float y, float z);
	vec3::Vector3 QuaternionToEuler(const Quaternion& q);
	Quaternion MatrixToQuaternion(const mat4::MATRIX4& m);
	mat4::MATRIX4 QuaternionToMatrix(const Quaternion& q);
	Quaternion QuaternionFromAngle(const vec3::Vector3& v, float angle);
	Quaternion DirectionToQuaternion(const vec3::Vector3& dir);

	//Quat Angle (looks nicer)
	MP_INLINE Quaternion QuatAngle(float angle, float x, float y, float z)
	{
		return QuaternionFromAngle(vec3::Vector3(x, y, z), angle);
	}

	//Invert Quaternion
	MP_INLINE Quaternion Invert(const Quaternion& q)
	{
		return Quaternion(q.w, -q.v.x, -q.v.y, -q.v.z);
	}

	//Quaternion Dot Product
	MP_INLINE float QDot(const Quaternion& a, const Quaternion& b)
	{
		return a.w * b.w + vec3::DotProduct(a.v, b.v);
	}

	//Normalize Quaternion
	MP_INLINE Quaternion QNormalize(const Quaternion& in)
	{
		const float mod = 1.0f/sqrt(in.w*in.w + in.v.x*in.v.x + in.v.y*in.v.y + in.v.z*in.v.z);
		return Quaternion(in.w * mod, in.v.x * mod, in.v.y * mod, in.v.z * mod);
	}

	//Normalize Quaternion (InvSqrt())
	MP_INLINE Quaternion QFastNormalize(const Quaternion& in)
	{
		const float mod = math::InvSqrt(in.w*in.w + in.v.x*in.v.x + in.v.y*in.v.y + in.v.z*in.v.z);
		return Quaternion(in.w * mod, in.v.x * mod, in.v.y * mod, in.v.z * mod);
	}

	//Normalize Quaternion (Intrinsics)
	MP_INLINE Quaternion QI_Normalize(const Quaternion& in)
	{
		const float mod = math::irsqrt(in.w*in.w + in.v.x*in.v.x + in.v.y*in.v.y + in.v.z*in.v.z);
		return Quaternion(in.w * mod, in.v.x * mod, in.v.y * mod, in.v.z * mod);
	}

	//Quaternion ACOS
	MP_INLINE float Qacos(const Quaternion& a, const Quaternion& b)
	{
		return acos(QDot(QFastNormalize(a), QFastNormalize(b)));
	}
};

#endif


