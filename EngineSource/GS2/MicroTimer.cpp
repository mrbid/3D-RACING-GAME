/*
	Code written by James Fletcher. 
	Copyright 2011 - 2012. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	Limit the timer code to one CPU so that we dont get any thread switching problems.
*/
#include "precom.h"

#include "MicroTimer.h"

MicroTimer::MicroTimer()
{
	start.QuadPart = 0;
	stop.QuadPart = 0;

	DWORD_PTR threadAffMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceFrequency(&frequency);
	SetThreadAffinityMask(GetCurrentThread(), threadAffMask);
}

void MicroTimer::Start()
{
	DWORD_PTR threadAffMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), threadAffMask);
}

void MicroTimer::Stop()
{
	DWORD_PTR threadAffMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), threadAffMask);
}








