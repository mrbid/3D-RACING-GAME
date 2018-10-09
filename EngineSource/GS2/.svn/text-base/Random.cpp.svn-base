/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "Random.h"

#define archive_size 1000
int rand_list[archive_size]; //Uniniting it helps our case
bool nozeros = 0;

unsigned int rand_regulator;
unsigned int rand_interval;


//Get's random from list
MP_INLINE int GetFromList()
{
	return rand_list[rand()%archive_size];
}

//Readys the random list
void ReadyGenerator()
{
	while(nozeros == 0)
	{
		int rnd_pos = 0;

		for(int i = 0; i < archive_size; i++)
		{
			if(rand_list[i] == 0)
			{
				rnd_pos = i;
			} 
		}

		if(rnd_pos != 0)
		{
			rand_list[rnd_pos] = rand()+1;
		}else{
			rand_list[rand()%archive_size] = rand()+1;
			nozeros = 1;
		}

		//Set new Srand
		const int rnd = rand()%300;

		if(rnd >= 0 && rnd <= 100){srand(static_cast<unsigned int>(time(0)));}
		if(rnd > 100 && rnd <= 200){srand(GetTickCount());}
		if(rnd > 200 && rnd <= 300){srand(GetFromList());}
		for(int i = 0; i < rand()%1000; i++){rand();}
	}
}

//Adds random to list
void rnd_AddList()
{
	if(GetTickCount() < rand_regulator+rand_interval){return;}

	if(nozeros == 0)
	{
		nozeros = 1;

		for(int i = 0; i < archive_size; i++)
		{
			if(rand_list[i] == 0)
			{
				rand_list[i] = rand()+1;
				nozeros = 0;
			} 
		}
	}
	else
	{
		rand_list[rand()%archive_size] = rand()+1;
	}

	//Set new Srand
	const int rnd = rand()%300; //resolution could be improved

	if(rnd >= 0 && rnd <= 100){srand(static_cast<unsigned int>(time(0)));}
	if(rnd > 100 && rnd <= 200){srand(GetTickCount());}
	if(rnd > 200 && rnd <= 300){srand(GetFromList());}
	/*if(rnd > 300 && rnd <= 400)
	{
		LARGE_INTEGER qp;
		QueryPerformanceCounter(&qp);
		srand(qp.HighPart);
	}*/

	rand_interval = qRand(100, 500);
	rand_regulator = GetTickCount();
}




