/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	The randoms are very very fast, for performance crittical code.
*/

#ifndef IRANDOM_H
#define IRANDOM_H

#pragma comment(lib, "Winmm.lib")
#include "precom.h"
#include "MathLib.h"


//Rand Max
const int I_RAND_MAX = int((std::numeric_limits< unsigned __int64 >::max)());
const float I_F_RAND_MAX = float((std::numeric_limits< unsigned __int64 >::max)());
const float RCP_RAND_MAX = 1.0f / I_F_RAND_MAX;
const float RCP_RAND_MAX2 = 1.0f / (I_F_RAND_MAX+1.0f);

//Fast Random (this is more than seven times faster than rand()) (referenced from OGRE3D src)
MP_INLINE float arand()
{
	static unsigned __int64 q = timeGetTime();

	_asm
	{
		movq mm0, q
		pshufw mm1, mm0, 0x1E
		paddd mm0, mm1
		movq q, mm0
		emms
	}

	return float(q);
}

//Quick random float
MP_INLINE float i_qRandFloat(const float min, const float max)
{
	return (arand() * RCP_RAND_MAX2) * (max - min) + min;
}

//Quick Random
MP_INLINE int i_qRand(const int min, const int max)
{
	return int(i_qRandFloat(float(min), float(max)) + 0.5f);
}

//Random between -1 and 1
MP_INLINE float i_fRand()
{
	return arand() * RCP_RAND_MAX;
}

#endif




