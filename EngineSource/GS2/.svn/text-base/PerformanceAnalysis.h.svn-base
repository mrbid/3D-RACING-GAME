/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef PERFORMANCEANALYSIS_H
#define PERFORMANCEANALYSIS_H

#include "precom.h"

#include "GlobalMacros.h"
#include "MicroTimer.h"
#include "MilliTimer.h"

//Defines
#define MAX_THRESHOLD_SAMPLES 8000
#define THRESHOLD_SKIP_SAMPLES 8

//Perfomance Analysis Class
class PerformanceAnalysis
{
public:

	//Singleton
	static PerformanceAnalysis& Inst()
	{
		static PerformanceAnalysis singleton;
		return singleton;
	}
	~PerformanceAnalysis(); //Destructor

	//Init
	void Init();

	//Add Log
	void AddLog();

private:

	PerformanceAnalysis() : m_threshold(0.f), m_lastdt(0.f), m_lastip(0.f), m_threshold_set(false), m_threshold_count(0) {}; //Constructor
	PerformanceAnalysis(const PerformanceAnalysis&); //Prevent Copy
	PerformanceAnalysis& operator=(const PerformanceAnalysis&); //Prevent Assignment

	//Log File Handle
	FILE* m_file;

	//Timer
	MicroTimer m_timer;
	int m_starttime;

	//Delta Time Threshold
	bool m_threshold_set;
	int m_threshold_count;
	double m_threshold;
	double m_recip_threshold;
	double m_lastdt;

	//Interest Point
	int m_lastip;

};

//Return Instance to Performance Analysis Class
MP_INLINE PerformanceAnalysis& PerformanceAnalysis(){return PerformanceAnalysis::Inst();}

#endif



