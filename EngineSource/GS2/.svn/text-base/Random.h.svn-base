/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef RANDOM_H
#define RANDOM_H

#include "precom.h"
#include "GlobalMacros.h"

//Some constants
const float F_RAND_MAX = RAND_MAX;
const int RANDMAX_HALF = RAND_MAX / 2;
const float RANDMAX_UNIT = 1.0f / RAND_MAX;
const float RANDMAX_UNIT2 = 1.0f / (RAND_MAX + 1.0f);

//Functions to spice up the seed
void ReadyGenerator();
void rnd_AddList();

//From Numerical Recipies
struct Rand64
{
	__int64 v;
	
	Rand64(__int64 seed) : v(4101842887655102017LL){
		v ^= seed; v = int64();
	}
	
	MP_INLINE __int64 int64(){
		v ^= v >> 21; v ^= v << 35; v ^= v >> 4;
		return v * 2685821657736338717LL;
	}

	MP_INLINE double doub(){
		return 5.42101086242752217E-20 * int64();
	}
};

//Various Noise Algorithms
MP_INLINE float qSinNoise2D(float x, float y)
{
	float i=0;
	return 0.5f + modf(sinf((x * 12.9898f) + (y * 78.233f)) * 43758.5453f, &i) * 0.5f;
}

MP_INLINE float qNoise2D(int x, int y, int random)
{
	const int n = (int(x+y*57 + random * 131)<<13)^n;
    return (1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589)&0x7fffffff)* 0.000000000931322574615478515625f);
}

MP_INLINE float qNoise2D(int x, int y)
{
	const int n = (int(x+y*57)<<13)^n;
	return 1.0f-(int((n*(n*n*60493+19990303)+1376312589)&0x7fffffff)/1073741824.0f);
}

MP_INLINE float qNoise1D(int ix)
{
	const int x = (ix<<13) ^ ix;
	return (1.0f - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);    
}

MP_INLINE float qNoise1D(int x, int random)
{
    const int n = (int((x * 57 + random * 131)) << 13) ^ n;
    return (1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589)&0x7fffffff) * 0.000000000931322574615478515625f);
}

//Quick Random
MP_INLINE int qRand(const int min, const int max)
{
	return (rand()%(max-min))+min;
}

//Quick random float
MP_INLINE float qRandFloat(const float min, const float max)
{
	return (float)(static_cast<float>(rand()) * RANDMAX_UNIT2) * (max - min) + min;
}

//Quick Random 1 - 0
MP_INLINE bool qRandBool()
{
	const int r = rand();
	return r < RANDMAX_HALF ? true : false;
}

//Float Random
MP_INLINE float fRand()
{
	return rand() * RANDMAX_UNIT;
}

#endif




