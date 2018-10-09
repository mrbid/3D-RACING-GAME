/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef VECTOR2_H
#define VECTOR2_H

#include "precom.h"
#include "Random.h"
#include "iRandom.h"

#include "MathLib.h"

namespace vec2
{
	/*
		******************************************************************************************************************
													VECTOR2 CLASS
		******************************************************************************************************************
	*/
	class Vector2
	{
	public:
		float x,y;

		MP_INLINE Vector2(){x = 0.f, y = 0.f;}
		MP_INLINE Vector2(float ix, float iy){x = ix, y = iy;}

		MP_INLINE Vector2& operator+=(const Vector2& in){x += in.x, y += in.y; return *this;}
		MP_INLINE Vector2& operator-=(const Vector2& in){x -= in.x, y -= in.y; return *this;}
		MP_INLINE Vector2& operator*=(const Vector2& in){x *= in.x, y *= in.y; return *this;}
		MP_INLINE Vector2& operator/=(const Vector2& in){x /= in.x, y /= in.y; return *this;}

		MP_INLINE Vector2& operator+=(const float scale){x += scale, y += scale; return *this;}
		MP_INLINE Vector2& operator-=(const float scale){x -= scale, y -= scale; return *this;}
		MP_INLINE Vector2& operator*=(const float scale){x *= scale, y *= scale; return *this;}
		MP_INLINE Vector2& operator/=(const float scale){x /= scale, y /= scale; return *this;}

		MP_INLINE bool operator==(Vector2& in) const{if(x == in.x && y == in.y){return 1;} return 0;}
		MP_INLINE bool operator!=(Vector2& in) const{if(x == in.x && y == in.y){return 0;} return 1;}
		MP_INLINE bool operator<=(Vector2& in) const{if(x <= in.x && y <= in.y){return 1;} return 0;}
		MP_INLINE bool operator>=(Vector2& in) const{if(x >= in.x && y >= in.y){return 1;} return 0;}

		MP_INLINE bool operator<(Vector2& in) const{if(x < in.x && y < in.y){return 1;} return 0;}
		MP_INLINE bool operator>(Vector2& in) const{if(x > in.x && y > in.y){return 1;} return 0;}
	};

	MP_INLINE Vector2 operator+(const Vector2& lhs, const Vector2& rhs){return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);}
	MP_INLINE Vector2 operator-(const Vector2& lhs, const Vector2& rhs){return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);}
	MP_INLINE Vector2 operator*(const Vector2& lhs, const Vector2& rhs){return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);}
	MP_INLINE Vector2 operator/(const Vector2& lhs, const Vector2& rhs){return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);}

	MP_INLINE Vector2 operator+(const Vector2& lhs, const float rhs){return Vector2(lhs.x + rhs, lhs.y + rhs);}
	MP_INLINE Vector2 operator-(const Vector2& lhs, const float rhs){return Vector2(lhs.x - rhs, lhs.y - rhs);}
	MP_INLINE Vector2 operator*(const Vector2& lhs, const float rhs){return Vector2(lhs.x * rhs, lhs.y * rhs);}
	MP_INLINE Vector2 operator/(const Vector2& lhs, const float rhs){const float rd = 1.0f/rhs; return Vector2(lhs.x * rd, lhs.y * rd);}

	MP_INLINE Vector2 operator+(const float lhs, const Vector2& rhs){return Vector2(lhs + rhs.x, lhs + rhs.y);}
	MP_INLINE Vector2 operator-(const float lhs, const Vector2& rhs){return Vector2(lhs - rhs.x, lhs - rhs.y);}
	MP_INLINE Vector2 operator*(const float lhs, const Vector2& rhs){return Vector2(lhs * rhs.x, lhs * rhs.y);}
	MP_INLINE Vector2 operator/(const float lhs, const Vector2& rhs){return Vector2(lhs / rhs.x, lhs / rhs.y);}

	MP_INLINE bool operator==(const Vector2& in, const float rhs){if(rhs == in.x && rhs == in.y){return 1;} return 0;}
	MP_INLINE bool operator!=(const Vector2& in, const float rhs){if(rhs == in.x && rhs == in.y){return 0;} return 1;}
	MP_INLINE bool operator<=(const Vector2& in, const float rhs){if(rhs <= in.x && rhs <= in.y){return 1;} return 0;}
	MP_INLINE bool operator>=(const Vector2& in, const float rhs){if(rhs >= in.x && rhs >= in.y){return 1;} return 0;}
	
	MP_INLINE bool operator<(const Vector2& in, const float rhs){if(rhs < in.x && rhs < in.y){return 1;} return 0;}
	MP_INLINE bool operator>(const Vector2& in, const float rhs){if(rhs > in.x && rhs > in.y){return 1;} return 0;}

	static Vector2 VECTOR_NULL(0.f, 0.f);



	/*
		******************************************************************************************************************
													FUNCTIONS
		******************************************************************************************************************
	*/

	//Rotate Vector
	MP_INLINE Vector2 Rotate(const Vector2& a, float angle)
	{
		return Vector2( a.x * sin(angle), a.y * cos(angle) );
	}

	//Equal To Tolerance
	MP_INLINE bool EqualTolerance(const Vector2& a, const Vector2& b, float tol)
	{
		if( a.x >= b.x - tol && a.x <= b.x + tol &&
			a.y >= b.y - tol && a.y <= b.y + tol )
			return true;
		else
			return false;
	}

	//Equal To IntPart
	MP_INLINE bool EqualIntPart(const Vector2& a, const Vector2& b)
	{
		if(int(a.x+0.5f) == int(b.x+0.5f) && int(a.y+0.5f) == int(b.y+0.5f))
			return true;
		else
			return false;
	}

	//Reciprocal Vector
	MP_INLINE Vector2 Reciprocal(const Vector2& a)
	{
		return Vector2(1.0f / a.x, 1.0f / a.y);
	}

	//Negify Vector
	MP_INLINE Vector2 Negify(const Vector2& a)
	{
		return Vector2(-a.x, -a.y);
	}

	//Dot Product
	MP_INLINE float DotProduct(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	//Reflect a Vector
	MP_INLINE Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - ((2.f * n) * DotProduct(v,n));
	}

	//Length / Magnitude
	MP_INLINE float Distance(const Vector2& a, const Vector2& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		return math::fsqrt(xm*xm + ym*ym);
	}

	//Length / Magnitude Squared
	MP_INLINE float DistanceSq(const Vector2& a, const Vector2& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		return xm*xm + ym*ym;
	}

	//Length / Magnitude Manhattan
	MP_INLINE float DistanceManhattan(const Vector2& a, const Vector2& b)
	{
		return (a.x - b.x) + (a.y - b.y);
	}

	//Length / Magnitude using Intrinsics
	MP_INLINE float I_Distance(const Vector2& a, const Vector2& b)
	{
		const float xm = (a.x - b.x);
		const float ym = (a.y - b.y);
		return math::isqrt(xm*xm + ym*ym);
	}

	//Modulus (Length Square Root)
	MP_INLINE float Modulus(const Vector2& v)
	{
		return math::fsqrt((v.x * v.x) + (v.y * v.y));
	}

	//Modulus (Length Square Root) using Intrinsics
	MP_INLINE float I_Modulus(const Vector2& v)
	{
		return math::isqrt((v.x * v.x) + (v.y * v.y));
	}

	//Length (Squared)
	MP_INLINE float LengthSq(const Vector2& v)
	{
		return (v.x * v.x) + (v.y * v.y);
	}

	//Normalize (Accurate)
	MP_INLINE Vector2 Normalize(const Vector2& a)
	{
		const float len = 1.0f/sqrt(a.x*a.x + a.y*a.y);
		return Vector2(a.x*len, a.y*len);
	}

	//Normalize
	MP_INLINE Vector2 FastNormalize(const Vector2& a)
	{
		const float len = math::InvSqrt(a.x*a.x + a.y*a.y);
		return Vector2(a.x*len, a.y*len);
	}

	//Normalize using Intrinsics
	MP_INLINE Vector2 I_Normalize(const Vector2& a)
	{
		const float len = math::irsqrt(a.x*a.x + a.y*a.y);
		return Vector2(a.x*len, a.y*len);
	}

	//Random Unit Vector
	MP_INLINE Vector2 RandomUnitVector()
	{
		return FastNormalize(Vector2( i_qRandFloat(0.0f, 50.0f),
									  i_qRandFloat(0.0f, 50.0f) ));
	}

	//Random Unit Vector Trial-Error
	MP_INLINE Vector2 RandomUnitVectorTA()
	{
		while(1)
		{
			const Vector2 uv( i_qRandFloat(-1.0f, 1.0f),
							  i_qRandFloat(-1.0f, 1.0f) );
			const float len = LengthSq(uv);
			if(len <= 1.0f){return uv;}
		}
	}

	//Random Unit Vector Sphere
	MP_INLINE Vector2 RandomUnitVectorCircle()
	{
		const float deg = math::Degree(i_qRandFloat(-180.0f, 180.0f));
		return Vector2( sin(deg), cos(deg) );
	}
};

#endif


