/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef MATHLIB_H
#define MATHLIB_H

#include "precom.h"
#include "GlobalMacros.h"

const float M_PI_180 = 57.295779513096f;
const float x2PI = 6.283185307178f;
const float M_RADIAN = 0.0174532925f;
const float M_PI = 3.141592653589f;
const float M_PI_2 = 1.570796326794f;

namespace math
{
	//Degrees to Radians
	MP_INLINE float Degree(float degrees)
	{
		return degrees * M_RADIAN;
	}

	//Wrap Functon
	MP_INLINE float wrap(float f)
	{
		if(f < 0.f){return f + 1.0f;}
		if(f > 1.f){return f - 1.0f;}
		return f;
	}

	//Clamp Function (float)
	MP_INLINE float clamp(float f)
	{
		if(f < 0.f){return 0.0f;}
		if(f > 1.f){return 1.0f;}
		return f;
	}

	//Fit Function from (-1 - 1) to (0 - 1)
	MP_INLINE float fit(float f)
	{
		return (f + 1.0f) * 0.5f;
	}

	//Linear Interpolation
	MP_INLINE float LinearInterpolate(float a, float b, float i)
	{
		return(a * (1.f - i) + b * i);
	}

	//Distance Attenuation
	MP_INLINE float Fatt(const float d, float c0, float c1, float c2)
	{
		return 1.0f / c0 + (c1 * d) + (c2 * (d*d));
	}

	//Reciprocal
	MP_INLINE float rcp(float f)
	{
		return 1.0f / f;
	}

	//InvSqrt (Quake 3)
	MP_INLINE float InvSqrt(float x)
	{
		float xhalf = 0.5f*x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i>>1);
		x = *(float*)&i;
		x = x*(1.5f - xhalf*x*x);
		return x;
	}

	//Squared
	MP_INLINE float Squared(float f)
	{
		return f*f;
	}

	//Fast Sqrt using InvSqrt()
	MP_INLINE float fsqrt(float f)
	{
		return f * InvSqrt(f);
	}

	//Fast Square Root (wikipedia)
	MP_INLINE float fastsqrt(float f)
	{
        union{
			int tmp;
			float val;
        } u;
        u.val = f;
        u.tmp -= 1<<23;
        u.tmp >>= 1;
        u.tmp += 1<<29;
        return u.val;
	}

	//Intrinsic Sqrt
	MP_INLINE float isqrt(float f)
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(f)));
	}

	//Intrinsic Reciprocal Sqrt
	MP_INLINE float irsqrt(float f)
	{
		return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(f)));
	}

	//SmoothStep Interpolation
	MP_INLINE float SmoothStep(float a, float b, float i)
	{
		if(i <= a){return 0.0f;}
		if(i >= b){return 1.0f;}
		const float v = i - a / b - a;
		return v * v * (3.f - 2.f * v);
	}
};

#endif








