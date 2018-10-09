/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/


#include "precom.h"
#include "Colours.h"
#include "MathLib.h"

using namespace std;


//Convert RGB to HSL
clr::mColour clr::RGBtoHSL(mColour c)
{
	const float minc = min(min(c.r, c.g), c.b);
	const float maxc = max(max(c.r, c.g), c.b);
	
	if(minc == maxc){return clr::mColour(0.f, 0.f, (maxc + minc)*0.5f);} //Colour is Greyscale

	const float L = (maxc + minc)*0.5f;
	return clr::mColour((c.r == maxc) ? (c.g-c.b)/(maxc-minc) : (c.g == maxc) ? 2.0f + (c.b-c.r)/(maxc-minc) : 4.0f + (c.r-c.g)/(maxc-minc),
						 (L < 0.5f) ? (maxc-minc)/(maxc+minc) : (maxc-minc)/(2.0f-maxc-minc),
						 L);
}

//Convert HSL to RGB
clr::mColour clr::HSLtoRGB(mColour c)
{
	if(c.g == 0){return clr::mColour(c.b, c.b, c.b);} //Greyscale

	const float t2 = (c.b < 0.5f) ? c.b * (1.0f + c.g) : c.b + c.g - c.b * c.g;
	const float t1 = 2.0f * c.b - t2;

	const float Rt3 = math::wrap(c.r + 0.333333333f);
	const float Gt3 = math::wrap(c.r);
	const float Bt3 = math::wrap(c.r - 0.333333333f);

	return clr::mColour((6.0f * Rt3 < 1) ? t1 + (t2-t1) * 6.0f * Rt3 : (2.0f * Rt3 < 1) ? t2 : (3.0f * Rt3 < 2) ? t1 + (t2-t1) * (0.666666666f - Rt3) * 6.0f : t1,
						 (6.0f * Gt3 < 1) ? t1 + (t2-t1) * 6.0f * Gt3 : (2.0f * Gt3 < 1) ? t2 : (3.0f * Gt3 < 2) ? t1 + (t2-t1) * (0.666666666f - Gt3) * 6.0f : t1,
						 (6.0f * Bt3 < 1) ? t1 + (t2-t1) * 6.0f * Bt3 : (2.0f * Bt3 < 1) ? t2 : (3.0f * Bt3 < 2) ? t1 + (t2-t1) * (0.666666666f - Bt3) * 6.0f : t1);
}


//Convert RGB to HSV
clr::mColour clr::RGBtoHSV(mColour c)
{	
	const float x = min(min(c.r, c.g), c.b);
	const float v = max(max(c.r, c.g), c.b);
	if(v == x){clr::mColour(-1.f, 0.f, v);}
	return clr::mColour(((c.r == x) ? 3 : ((c.g == x) ? 5 : 1)) - ((c.r == x) ? c.g - c.b : ((c.g == x) ? c.b - c.r : c.r - c.g)) /(v - x), (v - x)/v, v);
}

//Convert HSV to RGB
clr::mColour clr::HSVtoRGB(mColour c)
{
	if(c.r == -1.f){return clr::mColour(c.b, c.b, c.b);}

	const int i = (int)floor(c.r);
	const float f = !(i&1) ? 1.0f - (c.r - i) : c.r - i;

	switch(i)
	{
		case 6:
		case 0: return clr::mColour(c.b, c.b * (1 - c.g * f), c.b * (1 - c.g));
		case 1: return clr::mColour(c.b * (1 - c.g * f), c.b, c.b * (1 - c.g));
		case 2: return clr::mColour(c.b * (1 - c.g), c.b, c.b * (1 - c.g * f));
		case 3: return clr::mColour(c.b * (1 - c.g), c.b * (1 - c.g * f), c.b);
		case 4: return clr::mColour(c.b * (1 - c.g * f), c.b * (1 - c.g), c.b);
		case 5: return clr::mColour(c.b, c.b * (1 - c.g), c.b * (1 - c.g * f));
	}
}


//Convert RGB to YUV
clr::mColour clr::RGBtoYUV(mColour c)
{
	/*const float y = 0.299f * c.r + 0.587f * c.g + 0.114f * c.b;
	return clr::mColour(y,
						0.436f * ((c.b - y) / (1.0f - 0.114f)),
						0.615f * ((c.r - y) / (1.0f - 0.299f)));*/

	const float y = 0.299f * c.r + 0.587f * c.g + 0.114f * c.b;
	return clr::mColour(y,
						0.436f * ((c.b - y) * 1.128668171f),
						0.615f * ((c.r - y) * 1.426533523f));
}


//Convert YUV to RGB
clr::mColour clr::YUVtoRGB(mColour c)
{
	/*return clr::mColour(c.r + c.b * ( (1.0f - 0.299f) / 0.615f ),
						c.r - c.g * ( (0.114f * (1.0f - 0.114f)) / (0.436f * 0.587f) ) - c.b * ( (0.299f * (1.0f - 0.299f)) / (0.615f * 0.587f) ),
						c.r + c.g * ( (1.0f - 0.114f) / 0.436f));*/

	return clr::mColour(c.r + c.b * 1.139837398f,
						c.r - c.g * (0.394651704f - c.b * 0.580598606f),
						c.r + c.g * 2.103211009f);
}














