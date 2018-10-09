/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef MILLITIMER_H
#define MILLITIMER_H

#pragma comment(lib, "Winmm.lib")
#include "precom.h"

//Get Current Time
__forceinline unsigned int GetTimeUINT(){return static_cast<unsigned int>(timeGetTime());}
__forceinline float GetTimeFLOAT(){return static_cast<float>(timeGetTime());}
__forceinline double GetTime(){return timeGetTime();}

#endif



