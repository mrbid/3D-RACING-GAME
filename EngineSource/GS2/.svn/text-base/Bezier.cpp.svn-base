/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "Bezier.h"

//CubicBezier1D Constructor
CubicBezier1D::CubicBezier1D()
{
	p[0] = 0.f;
	p[1] = 0.f;
	p[2] = 0.f;
	p[3] = 0.f;
}

//BezierComposite Destructor
BezierComposite::~BezierComposite()
{
	if(m_lookuptable != 0){delete [] m_lookuptable;}
}

//Get point on a bezier composite curve
vec3::Vector3 BezierComposite::GetPoint(float p)
{
	float curve;
	float t = modf(p, &curve);
	int c = int(curve);

	//Have we exceeded the end of the curve?
	if(c >= m_maxtime){return vec3::Vector3(0,0,0);}

	//1.0 should be curve 0, at t 1.0 not curve 1 at t 0;
	if(t == 0)
	{
		if(c != 0)
		{
			c -= 1;
			t = 1.0f;
		}
	}

	//Base Functions
	const float tm1 = 1-t;
	const float x2tm1 = tm1 * tm1;
	const float tt = t*t;
	const float B[4] = {x2tm1 * tm1,
						3 * t * x2tm1,
						3 * tt * tm1,
						tt*t};

	return vec3::Vector3(
			   B[0] * m_curves[c].p[0].x
			 + B[1] * m_curves[c].p[1].x 
			 + B[2] * m_curves[c].p[2].x 
			 + B[3] * m_curves[c].p[3].x
			 ,
			   B[0] * m_curves[c].p[0].y 
			 + B[1] * m_curves[c].p[1].y 
			 + B[2] * m_curves[c].p[2].y 
			 + B[3] * m_curves[c].p[3].y
			 ,
			   B[0] * m_curves[c].p[0].z 
			 + B[1] * m_curves[c].p[1].z 
			 + B[2] * m_curves[c].p[2].z 
			 + B[3] * m_curves[c].p[3].z
			 );
}

//Get point on a bezier composite curve
float BezierComposite::GetPointY(float p)
{
	float curve;
	float t = modf(p, &curve);
	int c = int(curve);

	//Have we exceeded the end of the curve?
	if(c >= m_maxtime){return 0.f;}

	//1.0 should be curve 0, at t 1.0 not curve 1 at t 0;
	if(t == 0)
	{
		if(c != 0)
		{
			c -= 1;
			t = 1.0f;
		}
	}

	//Base Functions & Return
	const float tm1 = 1-t;
	const float x2tm1 = tm1 * tm1;
	const float tt = t*t;
	
	return (x2tm1 * tm1) *   m_curves[c].p[0].y 
		 + (3 * t * x2tm1) * m_curves[c].p[1].y 
		 + (3 * tt * tm1) *  m_curves[c].p[2].y 
		 + (tt*t) *		     m_curves[c].p[3].y;
}

//Get direction on a bezier composite curve
vec3::Vector3 BezierComposite::GetDirection(float p)
{
	float curve;
	float t = modf(p, &curve);
	int c = int(curve);

	//Have we exceeded the end of the curve?
	if(c >= m_maxtime){return vec3::Vector3(0,0,0);}

	//1.0 should be curve 0, at t 1.0 not curve 1 at t 0;
	if(t == 0)
	{
		if(c != 0)
		{
			c -= 1;
			t = 1.0f;
		}
	}

	//Differentiated Base Functions
	const float tm1 = 1-t;
	const float x2tm1 = tm1 * tm1;
	const float tt = t*t;
	const float B[4] = {-3 * x2tm1, //-3 + 6*t - 3 * (t*t)
						9 * tt - (12 * t) + 3,
						(6 * t) - 9 * tt, //Can simplify BUT to the power of t, which would use pow(), possible problem.
						3*tt};

	return vec3::I_Normalize(vec3::Vector3(
			   B[0] * m_curves[c].p[0].x
			 + B[1] * m_curves[c].p[1].x 
			 + B[2] * m_curves[c].p[2].x 
			 + B[3] * m_curves[c].p[3].x
			 ,
			   B[0] * m_curves[c].p[0].y 
			 + B[1] * m_curves[c].p[1].y 
			 + B[2] * m_curves[c].p[2].y 
			 + B[3] * m_curves[c].p[3].y
			 ,
			   B[0] * m_curves[c].p[0].z 
			 + B[1] * m_curves[c].p[1].z 
			 + B[2] * m_curves[c].p[2].z 
			 + B[3] * m_curves[c].p[3].z
			 ));
}

//Returns a bezier curve
BezierCurve BEZ_Curve(vec3::Vector3 p1, vec3::Vector3 p2, vec3::Vector3 p3, vec3::Vector3 p4)
{
	BezierCurve c;

	c.p[0].x = p1.x;
	c.p[0].y = p1.y;
	c.p[0].z = p1.z;

	c.p[1].x = p2.x;
	c.p[1].y = p2.y;
	c.p[1].z = p2.z;

	c.p[2].x = p3.x;
	c.p[2].y = p3.y;
	c.p[2].z = p3.z;

	c.p[3].x = p4.x;
	c.p[3].y = p4.y;
	c.p[3].z = p4.z;

	return c;
}

//Loads bezier composite curves from file
bool BezierComposite::LoadCompositeCurvesFromFile(char* file)
{
	//Open File
	FILE* fin = fopen(file, "r");
	if(fin != NULL)
	{
		//Store Control Points here
		vec3::Vector3 m_cp[4];

		//Load first four control points
		for(int i = 0; i < 4; ++i)
			fscanf(fin, "v  %f %f %f\n", &m_cp[i].x,  &m_cp[i].y,  &m_cp[i].z);

		//Add them to composite curve
		AddCurve(BEZ_Curve(m_cp[0], m_cp[1], m_cp[2], m_cp[3]));
		
		//Loop through the rest untill there's no more control points
		while(m_cp[0] != vec3::VECTOR_NULL && m_cp[1] != vec3::VECTOR_NULL && m_cp[2] != vec3::VECTOR_NULL && m_cp[3] != vec3::VECTOR_NULL)
		{
			//Set the last control point to the first
			m_cp[0] = m_cp[3];

			//Load control points
			for(int i = 1; i < 4; ++i)
			{
				fscanf(fin, "v  %f %f %f\n", &m_cp[i].x,  &m_cp[i].y,  &m_cp[i].z);
			}

			//Add it to composite curve
			AddCurve(BEZ_Curve(m_cp[0], m_cp[1], m_cp[2], m_cp[3]));
		}

		//Close File
		fclose(fin);
	}
	else
	{
		//Failed
		return false;
	}

	//Succeeded
	return true;
}

//Adjust all points in composite by scalar
void BezierComposite::ScaleComposite(float scale)
{
	for(vector<BezierCurve>::iterator iter = m_curves.begin(); iter != m_curves.end(); ++iter)
	{
		iter->p[0] *= scale;
		iter->p[1] *= scale;
		iter->p[2] *= scale;
		iter->p[3] *= scale;
	}
}

//Calculates lookup table for Distance to Time
void BezierComposite::CalculateLookupTable(int samplespercurve, float maxval)
{
	//Create lookup table to the total size of samples across the composite curve
	m_tablesize = samplespercurve * m_totalcurves;
	m_lookuptable = new table[m_tablesize+1];

	//Set First Element
	m_lookuptable[0].distance = 0.f;
	m_lookuptable[0].recip_distancediff = 0.f;
	m_lookuptable[0].time = 0.f;

	//Increment position across the composite curve in sample chunks
	const float increment = 1.0f / samplespercurve;

	//End time value
	const float curve_end_time = 1.0f * m_totalcurves;

	//Set max distance
	m_maxdistance = maxval;

	//Some Variables
	vec3::Vector3 last_pos(0,0,0);
	int lookup_pos = 0;
	float totallength = 0.0f;
	float length = 0.0f;

	//Calculate Total Length
	for(float f = .0f; f < curve_end_time; f += increment)
	{
		const vec3::Vector3 pos = GetPoint(f);

		if(f != .0f)
		{
			const float mag = vec3::Distance(last_pos, pos);
			totallength += mag;
		}

		last_pos = pos;
	}

	//Reset
	last_pos = vec3::VECTOR_NULL;

	//Distance Scale
	const float scale = maxval/totallength;

	//Input all values into the lookup table
	for(float f = .0f; f < curve_end_time; f += increment)
	{
		const vec3::Vector3 pos = GetPoint(f);

		//Add value to lookup table
		if(f != .0f) //For the first instance; last_pos will not contain a valid position for the calculation
		{
			length += vec3::Distance(last_pos, pos);
			m_lookuptable[lookup_pos].time = f;
			m_lookuptable[lookup_pos].distance = scale * length;

			//Pre-Calculate reciprocal difference between the distance of this table and the last one for linear interpolation
			m_lookuptable[lookup_pos].recip_distancediff = 1.f / (m_lookuptable[lookup_pos].distance - m_lookuptable[lookup_pos-1].distance);
		}

		last_pos = pos;
		lookup_pos++;
	}
}

//Returnes value from lookup table
float BezierComposite::DistanceToTime(float d)
{
	//If distance is 0 then we are at the beginning of the curve
	if(d == 0.0f)
	{
		return 0.0f;
	}

	//If distance is the highest distance in the lookup table
	if(d >= m_maxdistance)
	{
		return 1.0f * m_totalcurves;
	}

	//If distance is near the beginning of the curve
	if(d < m_lookuptable[0].distance)
	{
		table t;
		t.distance = 0;
		t.time = 0;
		return Lerp(&t, &m_lookuptable[1], d);
	}

	//find distance in lookup table
	for(int i = 0; i < m_tablesize-1; i++)
	{
		//found
		if(d >= m_lookuptable[i].distance && d <= m_lookuptable[i+1].distance)
		{
			return Lerp(&m_lookuptable[i], &m_lookuptable[i+1], d);
		}
	}

	//no result?
	return 0.f;
}


