/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef VECTOR3_H
#define VECTOR3_H

#include "precom.h"
#include "Random.h"
#include "iRandom.h"

#include "MathLib.h"

namespace vec3
{
	/*
		******************************************************************************************************************
													VECTOR3 CLASS
		******************************************************************************************************************
	*/
	class Vector3
	{
	public:
		float x,y,z;

		MP_INLINE Vector3(){x = 0.f, y = 0.f, z = 0.f;}
		MP_INLINE Vector3(float ix, float iy, float iz){x = ix, y = iy, z = iz;}

		MP_INLINE Vector3& operator+=(const Vector3& in){x += in.x, y += in.y, z += in.z; return *this;}
		MP_INLINE Vector3& operator-=(const Vector3& in){x -= in.x, y -= in.y, z -= in.z; return *this;}
		MP_INLINE Vector3& operator*=(const Vector3& in){x *= in.x, y *= in.y, z *= in.z; return *this;}
		MP_INLINE Vector3& operator/=(const Vector3& in){x /= in.x, y /= in.y, z /= in.z; return *this;}

		MP_INLINE Vector3& operator+=(const float scale){x += scale, y += scale, z += scale; return *this;}
		MP_INLINE Vector3& operator-=(const float scale){x -= scale, y -= scale, z -= scale; return *this;}
		MP_INLINE Vector3& operator*=(const float scale){x *= scale, y *= scale, z *= scale; return *this;}
		MP_INLINE Vector3& operator/=(const float scale){const float rd = 1.0f/scale; x *= rd, y *= rd, z *= rd; return *this;}

		MP_INLINE bool operator==(Vector3& in) const{if(x == in.x && y == in.y && z == in.z){return 1;} return 0;}
		MP_INLINE bool operator!=(Vector3& in) const{if(x == in.x && y == in.y && z == in.z){return 0;} return 1;}
		MP_INLINE bool operator<=(Vector3& in) const{if(x <= in.x && y <= in.y && z <= in.z){return 1;} return 0;}
		MP_INLINE bool operator>=(Vector3& in) const{if(x >= in.x && y >= in.y && z >= in.z){return 1;} return 0;}

		MP_INLINE bool operator<(Vector3& in) const{if(x < in.x && y < in.y && z < in.z){return 1;} return 0;}
		MP_INLINE bool operator>(Vector3& in) const{if(x > in.x && y > in.y && z > in.z){return 1;} return 0;}
	};

	MP_INLINE Vector3 operator+(const Vector3& lhs, const Vector3& rhs){return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);}
	MP_INLINE Vector3 operator-(const Vector3& lhs, const Vector3& rhs){return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);}
	MP_INLINE Vector3 operator*(const Vector3& lhs, const Vector3& rhs){return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);}
	MP_INLINE Vector3 operator/(const Vector3& lhs, const Vector3& rhs){return Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);}

	MP_INLINE Vector3 operator+(const Vector3& lhs, const float rhs){return Vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);}
	MP_INLINE Vector3 operator-(const Vector3& lhs, const float rhs){return Vector3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);}
	MP_INLINE Vector3 operator*(const Vector3& lhs, const float rhs){return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);}
	MP_INLINE Vector3 operator/(const Vector3& lhs, const float rhs){const float rd = 1.0f/rhs; return Vector3(lhs.x * rd, lhs.y * rd, lhs.z * rd);}

	MP_INLINE Vector3 operator+(const float lhs, const Vector3& rhs){return Vector3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);}
	MP_INLINE Vector3 operator-(const float lhs, const Vector3& rhs){return Vector3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);}
	MP_INLINE Vector3 operator*(const float lhs, const Vector3& rhs){return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);}
	MP_INLINE Vector3 operator/(const float lhs, const Vector3& rhs){return Vector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);}

	MP_INLINE bool operator==(const Vector3& in, const float rhs){if(rhs == in.x && rhs == in.y && rhs == in.z){return 1;} return 0;}
	MP_INLINE bool operator!=(const Vector3& in, const float rhs){if(rhs == in.x && rhs == in.y && rhs == in.z){return 0;} return 1;}
	MP_INLINE bool operator<=(const Vector3& in, const float rhs){if(rhs <= in.x && rhs <= in.y && rhs <= in.z){return 1;} return 0;}
	MP_INLINE bool operator>=(const Vector3& in, const float rhs){if(rhs >= in.x && rhs >= in.y && rhs >= in.z){return 1;} return 0;}
	
	MP_INLINE bool operator<(const Vector3& in, const float rhs){if(rhs < in.x && rhs < in.y && rhs < in.z){return 1;} return 0;}
	MP_INLINE bool operator>(const Vector3& in, const float rhs){if(rhs > in.x && rhs > in.y && rhs > in.z){return 1;} return 0;}

	static Vector3 VECTOR_NULL(0.f, 0.f, 0.f);



	/*
		******************************************************************************************************************
													FUNCTIONS
		******************************************************************************************************************
	*/

	//Rotate Vector in X
	MP_INLINE Vector3 RotateX(const Vector3& a, float angle)
	{
		return Vector3(a.x, a.y * cos(angle) + a.z * sin(angle), a.y * sin(angle) - a.z * cos(angle));
	}

	//Rotate Vector in Y
	MP_INLINE Vector3 RotateY(const Vector3& a, float angle)
	{
		return Vector3(a.z * sin(angle) - a.x * cos(angle), a.y, a.z * cos(angle) + a.x * sin(angle));
	}

	//Rotate Vector in Z
	MP_INLINE Vector3 RotateZ(const Vector3& a, float angle)
	{
		return Vector3(a.x * cos(angle) + a.y * sin(angle), a.x * sin(angle) - a.y * cos(angle), a.z);
	}

	//Equal To Tolerance
	MP_INLINE bool EqualTolerance(const Vector3& a, const Vector3& b, float tol)
	{
		if( a.x >= b.x - tol && a.x <= b.x + tol &&
			a.y >= b.y - tol && a.y <= b.y + tol &&
			a.z >= b.z - tol && a.z <= b.z + tol )
			return true;
		else
			return false;
	}

	//Equal To IntPart
	MP_INLINE bool EqualIntPart(const Vector3& a, const Vector3& b)
	{
		if(int(a.x+0.5f) == int(b.x+0.5f) && int(a.y+0.5f) == int(b.y+0.5f) && int(a.z+0.5f) == int(b.z+0.5f))
			return true;
		else
			return false;
	}

	//Reciprocal Vector
	MP_INLINE Vector3 Reciprocal(const Vector3& a)
	{
		return Vector3(1.0f / a.x, 1.0f / a.y, 1.0f / a.z);
	}

	//Negify Vector
	MP_INLINE Vector3 Negify(const Vector3& a)
	{
		return Vector3(-a.x, -a.y, - a.z);
	}

	//Dot Product
	MP_INLINE float DotProduct(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	//Cross Product
	MP_INLINE Vector3 CrossProduct(const Vector3& a, const Vector3& b)
	{
		return Vector3((a.y * b.z) - (b.y * a.z), -((a.x * b.z) - (b.x * a.z)), (a.x * b.y) - (b.x * a.y));
	}

	//Reflect a Vector
	MP_INLINE Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - ((2.f * n) * DotProduct(v,n));
	}

	//Length / Magnitude
	MP_INLINE float Distance(const Vector3& a, const Vector3& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		const float zm = (a.z - b.z);
		return math::fsqrt(xm*xm + ym*ym + zm*zm);
	}

	//Length / Magnitude Squared
	MP_INLINE float DistanceSq(const Vector3& a, const Vector3& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		const float zm = (a.z - b.z);
		return xm*xm + ym*ym + zm*zm;
	}

	//Length / Magnitude Manhattan
	MP_INLINE float DistanceManhattan(const Vector3& a, const Vector3& b)
	{
		return (a.x - b.x) + (a.y - b.y) + (a.z - b.z);
	}

	//Length / Magnitude using Intrinsics
	MP_INLINE float I_Distance(const Vector3& a, const Vector3& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		const float zm = (a.z - b.z);
		return math::isqrt(xm*xm + ym*ym + zm*zm);
	}

	//Modulus (Length Square Root)
	MP_INLINE float Modulus(const Vector3& v)
	{
		return math::fsqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	//Modulus (Length Square Root) using Intrinsics
	MP_INLINE float I_Modulus(const Vector3& v)
	{
		return math::isqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	//Length (Squared)
	MP_INLINE float LengthSq(const Vector3& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	//Normalize (Accurate)
	MP_INLINE Vector3 Normalize(const Vector3& a)
	{
		const float len = 1.0f/sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		return Vector3(a.x*len, a.y*len, a.z*len);
	}

	//Normalize
	MP_INLINE Vector3 FastNormalize(const Vector3& a)
	{
		const float len = math::InvSqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		return Vector3(a.x*len, a.y*len, a.z*len);
	}

	//Normalize using Intrinsics
	MP_INLINE Vector3 I_Normalize(const Vector3& a)
	{
		const float len = math::irsqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		return Vector3(a.x*len, a.y*len, a.z*len);
	}

	//Random Unit Vector
	MP_INLINE Vector3 RandomUnitVector()
	{
		return FastNormalize(Vector3(
			i_qRandFloat(0.0f, 50.0f),
			i_qRandFloat(0.0f, 50.0f),
			i_qRandFloat(0.0f, 50.0f)));
	}

	//Random Unit Vector Trial-Error
	MP_INLINE Vector3 RandomUnitVectorTA()
	{
		while(1)
		{
			const Vector3 uv(
				i_qRandFloat(-1.0f, 1.0f),
				i_qRandFloat(-1.0f, 1.0f),
				i_qRandFloat(-1.0f, 1.0f));
			const float len = LengthSq(uv);
			if(len <= 1.0f){return uv;}
		}
	}

	//Random Unit Vector Sphere
	MP_INLINE Vector3 RandomUnitVectorSphere()
	{
		return Vector3(
			sin(math::Degree(i_qRandFloat(-180.0f, 180.0f))),
			cos(math::Degree(i_qRandFloat(-90.0f, 90.0f))),
			2.f * i_fRand() - 1.f);
	}
};

#endif


