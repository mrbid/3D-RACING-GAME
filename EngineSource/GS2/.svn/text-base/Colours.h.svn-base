/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef COLOURS_H
#define COLOURS_H

#include "precom.h"
#include "GlobalMacros.h"

namespace clr
{
	/*
		******************************************************************************************************************
													COLOUR CLASS
		******************************************************************************************************************
	*/
	class mColour
	{
	public:
		float r,g,b; //h,s,l - h,s,v - y,u,v

		MP_INLINE mColour(){r = 0.f, g = 0.f, b = 0.f;}
		MP_INLINE mColour(float igrey){r = igrey, g = igrey, b = igrey;}
		MP_INLINE mColour(float ir, float ig, float ib){r = ir, g = ig, b = ib;}

		MP_INLINE mColour& operator+=(const mColour& in){r += in.r, g += in.g, b += in.b; return *this;}
		MP_INLINE mColour& operator-=(const mColour& in){r -= in.r, g -= in.g, b -= in.b; return *this;}
		MP_INLINE mColour& operator*=(const mColour& in){r *= in.r, g *= in.g, b *= in.b; return *this;}
		MP_INLINE mColour& operator/=(const mColour& in){r /= in.r, g /= in.g, b /= in.b; return *this;}

		MP_INLINE mColour& operator+=(const float scale){r += scale, g += scale, b += scale; return *this;}
		MP_INLINE mColour& operator-=(const float scale){r -= scale, g -= scale, b -= scale; return *this;}
		MP_INLINE mColour& operator*=(const float scale){r *= scale, g *= scale, b *= scale; return *this;}
		MP_INLINE mColour& operator/=(const float scale){r /= scale, g /= scale, b /= scale; return *this;}

		MP_INLINE bool operator==(mColour& in) const{if(r == in.r && g == in.g && b == in.b){return 1;} return 0;}
		MP_INLINE bool operator!=(mColour& in) const{if(r == in.r && g == in.g && b == in.b){return 0;} return 1;}
		MP_INLINE bool operator<=(mColour& in) const{if(r <= in.r && g <= in.g && b <= in.b){return 1;} return 0;}
		MP_INLINE bool operator>=(mColour& in) const{if(r >= in.r && g >= in.g && b >= in.b){return 1;} return 0;}
	};

	MP_INLINE mColour operator+(const mColour& lhs, const mColour& rhs){return mColour(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);}
	MP_INLINE mColour operator-(const mColour& lhs, const mColour& rhs){return mColour(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);}
	MP_INLINE mColour operator*(const mColour& lhs, const mColour& rhs){return mColour(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);}
	MP_INLINE mColour operator/(const mColour& lhs, const mColour& rhs){return mColour(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b);}

	MP_INLINE mColour operator+(const mColour& lhs, const float rhs){return mColour(lhs.r + rhs, lhs.g + rhs, lhs.b + rhs);}
	MP_INLINE mColour operator-(const mColour& lhs, const float rhs){return mColour(lhs.r - rhs, lhs.g - rhs, lhs.b - rhs);}
	MP_INLINE mColour operator*(const mColour& lhs, const float rhs){return mColour(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);}
	MP_INLINE mColour operator/(const mColour& lhs, const float rhs){return mColour(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs);}

	MP_INLINE mColour operator+(const float lhs, const mColour& rhs){return mColour(lhs + rhs.r, lhs + rhs.g, lhs + rhs.b);}
	MP_INLINE mColour operator-(const float lhs, const mColour& rhs){return mColour(lhs - rhs.r, lhs - rhs.g, lhs - rhs.b);}
	MP_INLINE mColour operator*(const float lhs, const mColour& rhs){return mColour(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b);}
	MP_INLINE mColour operator/(const float lhs, const mColour& rhs){return mColour(lhs / rhs.r, lhs / rhs.g, lhs / rhs.b);}

	class mColour4 : public mColour
	{
	public:
		mColour4()
		{
			r = 0.f, g = 0.f, b = 0.f, a = 0.f;
		}

		mColour4(float ir, float ig, float ib, float ia)
		{
			r = ir, g = ig, b = ib, a = ia;
		}

		float a;
	};

	static mColour COLOUR_NULL(0.f, 0.f, 0.f);

	mColour RGBtoHSL(mColour c); //Convert RGB to HSL
	mColour HSLtoRGB(mColour c); //Convert HSL to RGB

	mColour RGBtoHSV(mColour c); //Convert RGB to HSV
	mColour HSVtoRGB(mColour c); //Convert HSV to RGB

	mColour RGBtoYUV(mColour c); //Convert RGB to YUV
	mColour YUVtoRGB(mColour c); //Convert YUV to RGB

	//Neater implementation option for HSL
	MP_INLINE mColour ModifyHSL(mColour c, float h, float s, float l)
	{
		mColour t = RGBtoHSL(c);
		t.r += h;
		t.g += s;
		t.b += l;
		return HSLtoRGB(t);
	}

	//Neater implementation option for HSV
	MP_INLINE mColour ModifyHSV(mColour c, float h, float s, float v)
	{
		mColour t = RGBtoHSV(c);
		t.r += h;
		t.g += s;
		t.b += v;
		return HSVtoRGB(t);
	}

	//Clamp Function (colour)
	MP_INLINE mColour clamp(mColour c)
	{
		mColour t(c);

		if(c.r < 0.f){t.r = 0.0f;}
		if(c.r > 1.f){t.r = 1.0f;}

		if(c.g < 0.f){t.g = 0.0f;}
		if(c.g > 1.f){t.g = 1.0f;}

		if(c.b < 0.f){t.b = 0.0f;}
		if(c.b > 1.f){t.b = 1.0f;}

		return t;
	}
};

#endif






