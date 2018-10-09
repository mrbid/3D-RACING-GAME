/*
	Code written by James Fletcher. 
	Copyright 2011 - 2012. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef MICROTIMER_H
#define MICROTIMER_H

#include "precom.h"

//Micro Timer Class
class MicroTimer
{
public:

	//Constructor
	MicroTimer();

	//Functions
	void Start();
	void Stop();
	double GetElapsedTime();

private:

	//Variables
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	LARGE_INTEGER frequency;

};

__forceinline double MicroTimer::GetElapsedTime()
{
	return (double)(stop.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
}

#endif




