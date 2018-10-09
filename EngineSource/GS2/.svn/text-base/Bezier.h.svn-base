/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	I could take out the stl vector (for speed) and replace it with a normal
	array however all curves would have to be input through the constructor
*/

#ifndef BEZIER_H
#define BEZIER_H

#include "precom.h"
#include "MathLib.h"
#include "Vector3.h"
using namespace std;

//Bezier Curve
struct BezierCurve
{
	vec3::Vector3 p[4];
};

//Returns a Bezier Curve
BezierCurve BEZ_Curve(vec3::Vector3 p1, vec3::Vector3 p2, vec3::Vector3 p3, vec3::Vector3 p4);

//Lookup Table Entry
struct table
{
	float recip_distancediff;
	float distance;
	float time;
};

//Bezier Composite Class
class BezierComposite
{
public:

	//Constructor
	BezierComposite() : m_totalcurves(0) {}

	//Destructor
	~BezierComposite();

	//Get XYZ point on bezier curve
	vec3::Vector3 GetPoint(float t);

	//Get Direction Vector on composite curve
	vec3::Vector3 GetDirection(float t);

	//Get y point on bezier curve (required for keyframer FCURVE)
	float GetPointY(float t);

	//Load Composite Curve from File
	bool LoadCompositeCurvesFromFile(char* file);

	//Adjust all points in composite by scalar
	void ScaleComposite(float scale);

	//Add a cubic curve to composite
	void AddCurve(BezierCurve c);

	//Calculates lookup table for Distance to Time
	void CalculateLookupTable(int samplespercurve, float maxval);
	
	//Returnes a time value from lookup table
	float DistanceToTime(float d);

	//Returns max time value
	int GetMaxTime();

	//Total distance across the entire bezier composite
	float GetMaxDistance();

private:

	//Linear Interpolate
	float Lerp(table* a, table* b, float distance);

	//Array of cubic bezier curves
	vector<BezierCurve> m_curves;
	int m_totalcurves;

	//Lookup table for conversion from distance to time
	table* m_lookuptable;

	//Size of lookup table
	int m_tablesize;

	//Max distance value
	float m_maxdistance;

	//Max time value
	int m_maxtime;

};

MP_INLINE void BezierComposite::AddCurve(BezierCurve c)
{
	m_curves.push_back(c);
	m_totalcurves++;
	m_maxtime = m_totalcurves;
}

MP_INLINE int BezierComposite::GetMaxTime()
{
	return m_maxtime;
}

MP_INLINE float BezierComposite::GetMaxDistance()
{
	return m_maxdistance;
}

MP_INLINE float BezierComposite::Lerp(table* a, table* b, float distance)
{
	return a->time + (((distance - a->distance) * b->recip_distancediff) * (b->time - a->time));
}


//Simple 1D Cubic Bezier Class
class CubicBezier1D
{
public:

	//Contructor
	CubicBezier1D();
	
	//Get's a point on the curve using Bezier Base Functions
	float GetBezierPoint(float t);
	
	//Get's a point on the curve using Bezier Spline Base Functions
	float GetBSplinePoint(float t);
	
	//Modified B-Spline
    float GetSlidePoint(float t);
	
	//Set's the cubic bezier control points
	void Set(float p1, float p2, float p3, float p4);
	
	//Control Points
	float p[4];

};

inline float CubicBezier1D::GetBezierPoint(float t)
{
	const float tm1 = 1.0f - t;
	const float x2tm1 = tm1 * tm1;
	const float tt = t * t;
	return (x2tm1 * tm1)   * p[0] 
			+ (3 * t * x2tm1) * p[1] 
			+ (3 * tt * tm1)  * p[2] 
			+ (tt*t)          * p[3];
}

inline float CubicBezier1D::GetBSplinePoint(float t)
{						
	float tm1 = 1.0f - t;
	float tt = t * t;
	float ttt = tt * t;				
	return (0.1666666666666667f * (tm1 * tm1 * tm1))               * p[0] 
			+ (0.1666666666666667f * (3 * ttt - 6 * tt + 4))          * p[1] 
			+ (0.1666666666666667f * (-3 * ttt + 3 * tt + 3 * t + 1)) * p[2] 
			+ (0.1666666666666667f * ttt)                             * p[3];
}

inline float CubicBezier1D::GetSlidePoint(float t)
{						
    const float tm1 = 1 - t;
	const float x3t = 3 * t;
	const float x6t = 6 * t;
	const float x3tx3t = x3t * x3t;
	const float x3tx3tx3t = x3tx3t * x3t;						
	return (0.1666666666666667f * ( tm1 * tm1 * tm1 ))               * p[0] 
			+ (0.1666666666666667f * ( x3tx3tx3t - (x6t * x6t) + 4 ))   * p[1] 
			+ (0.1666666666666667f * ( -x3tx3tx3t + x3tx3t + x3t + 1 )) * p[2] 
			+ (0.1666666666666667f * ( t*t*t ))                         * p[3];
}
	
MP_INLINE void CubicBezier1D::Set(float p1, float p2, float p3, float p4)
{
	p[0] = p1, p[1] = p2, p[2] = p3, p[3] = p4;
}

#endif