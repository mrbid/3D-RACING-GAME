/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "PerformanceAnalysis.h"

//Destructor
PerformanceAnalysis::~PerformanceAnalysis()
{
	if(m_file != NULL)
		fclose(m_file);
}

//Init
void PerformanceAnalysis::Init()
{
	m_file = fopen("PerfomanceAnalysis.txt", "w");
	
	if(m_file != NULL)
	{
		m_timer.Start();
		m_starttime = GetTime();
	}
}

//Add Log
void PerformanceAnalysis::AddLog()
{
	//If file is null, do nothing
	if(m_file == NULL)
		return;

	//Stop Timer
	m_timer.Stop();

	//Time Constants
	const int time1 = int(GetTimeUINT() - m_starttime);
	const double elapsedtime = m_timer.GetElapsedTime();
	const double time2 = fabs(elapsedtime - m_lastdt);
	m_lastdt = elapsedtime;

	//Calc Threshold
	if(m_threshold_set == false)
	{
		//Dont log the first few sample
		if(m_threshold_count >= THRESHOLD_SKIP_SAMPLES)
		{
			//Add to Threshold
			m_threshold += time2;

			//Threshold Samples Logged
			if(m_threshold_count >= MAX_THRESHOLD_SAMPLES)
			{
				//Calc Threshold
				m_threshold /= float(MAX_THRESHOLD_SAMPLES-THRESHOLD_SKIP_SAMPLES);
				m_recip_threshold = 1.f / m_threshold;
				fprintf(m_file, "Threshold Calculated: %f\n", m_threshold);
				m_threshold_set = true;
			}
		}

		m_threshold_count++;
	}

	//Trigger Interest Point
	if(GetAsyncKeyState(VK_F1)&1)
	{
		fprintf(m_file, "%i: Interest Point Triggered.\n", time1 - m_lastip);
		m_lastip = time1;
	}

	//Write Statistics
	if(m_threshold_count >= MAX_THRESHOLD_SAMPLES)
	{
		if(time2 >= m_threshold)
		{
			fprintf(m_file, "ET: %i - DT: %f ", time1, m_timer.GetElapsedTime());

			//Print a star for the multiple of times the delta time is over the threshold.
			const int xOver = int(double((time2 * m_recip_threshold)+0.5f));
			for(int i = 0; i < xOver; i++)
				fprintf(m_file, "*");

			fprintf(m_file, "\n");
		}
		else
		{
			fprintf(m_file, "ET: %i - DT: %f\n", time1, m_timer.GetElapsedTime());
		}
	}
	else
	{
		fprintf(m_file, "ET: %i - DT: %f\n", time1, m_timer.GetElapsedTime());
	}
	
	
	//Start Timer
	m_timer.Start();
}
