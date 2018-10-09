/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "precom.h"
#include "Bezier.h"
#include "Quaternion.h"
#include "MathLib.h"
using namespace std;

//Interpolation Methods
#define IP_LINEAR 0
#define IP_SMOOTHSTEP 1
#define IP_SPHERICAL 2
#define IP_FCURVE 3

//FCurve Interpolation Samples per cubic bezier
#define FCURVE_SAMPLES 30


//Keyframe Structure
template<class T>
struct Keyframe
{
	T data;
	float time;

	//fcurves
	vec3::Vector3 lhandle;
	vec3::Vector3 rhandle;
};

//Animation Class
template<class T>
class Animation
{
public:
	Animation();

	T Update(float time);

	void PlayAnimation(bool in);
	void ResetAnimation();
	void SetPosition(int in);
	void SetLooping(bool in);
	void SkipFirstFrame(bool in);
	void SetInterpolation(int in);

	void AddKeyframe(Keyframe<T> in);
	void DeleteKeyframe(int pos);


	//Linear Interpolation
	MP_INLINE T Lerp(Keyframe<T>* a, Keyframe<T>* b, float t) const
	{
		return a->data + (((t - a->time) / (b->time - a->time)) * (b->data - a->data));
	}

	//Smooth Interpolation
	MP_INLINE T SmoothStep(Keyframe<T>* a, Keyframe<T>* b, float t) const
	{
		const float v = (t - a->time) / (b->time - a->time);
		const float vv = v*v;
		return a->data + (3 * (vv)) - (2 * (vv*v)) * (b->data - a->data);
	}

	//Spherical Linear Interpolation
	MP_INLINE T Slerp(Keyframe<T>* a, Keyframe<T>* b, float t) const
	{
		const float angle = quatn::Qacos(a->data, b->data);
		return ((sin((1-t)*angle)/sin(angle)) * a->data) + ((sin(t*angle)/sin(angle)) * b->data);
		return 0;
	}

	//Bezier Interpolation
	MP_INLINE T FCURVE(Keyframe<T>* a, Keyframe<T>* b, float t) const
	{
		return m_bezier.GetPointY(m_bezier.DistanceToTime(t));
	}


private:
	std::vector<Keyframe<T>> m_keyframes;
	int m_pos;
	bool m_playing;
	bool m_loop;
	bool m_frameskip; //skips first frame
	float m_time;
	int m_interpolation;
	int m_timeoffset;

	BezierComposite m_bezier;
};


//Update
template<class T>
T Animation<T>::Update(float time)
{
	m_time = time; //Update the keyframe time
	if(m_playing == 0){return -1;} //Don't play the Animation (could return first keyframe data)
	if(time-m_timeoffset < m_keyframes[0].time){return -1;} //Don't play the Animation (could return first keyframe data)
	float retval = 0.0f;
	const int m_posnext = m_pos+1;

	//Interpolate
	if(m_interpolation == IP_LINEAR)
	{
		retval = Lerp(&m_keyframes[m_pos], &m_keyframes[m_posnext], time-m_timeoffset);
	}

	if(m_interpolation == IP_SMOOTHSTEP)
	{
		retval = SmoothStep(&m_keyframes[m_pos], &m_keyframes[m_posnext], time-m_timeoffset);
	}

	if(m_interpolation == IP_SPHERICAL)
	{
		retval = Slerp(&m_keyframes[m_pos], &m_keyframes[m_posnext], time-m_timeoffset);
	}

	if(m_interpolation == IP_FCURVE)
	{
		retval = FCURVE(&m_keyframes[m_pos], &m_keyframes[m_posnext], time-m_timeoffset);
	}

	//If next frame
	if(time-m_timeoffset > m_keyframes[m_posnext].time)
	{
		m_pos++;
	}

	//Have we played all the keyframes?
	if(m_pos >= m_keyframes.size()-1)
	{
		if(m_loop == 1)
		{
			m_playing = 1;
			m_pos = 0;
			m_timeoffset = time;

			if(m_frameskip == 1)
			{
				m_timeoffset = time - m_keyframes[1].time;
			}
		}
		else
		{
			m_playing = 0;
			ResetAnimation();
		}
	}

	//Clamp Value
	if(retval > m_keyframes[m_posnext].data)
	{
		retval = m_keyframes[m_posnext].data;
	}

	//Return Value
	return retval;
}


//Returns a Keyframe Struct
template<class T>
Keyframe<T> kf(T d, float t) const
{
	Keyframe<T> k;
	k.data = d;
	k.time = t;
	return k;
}

//Returns a Keyframe Struct
template<class T>
Keyframe<T> kf_fc(T d, float t, vec3::Vector3 lh, vec3::Vector3 rh) const
{
	Keyframe<T> k;
	k.data = d;
	k.time = t;
	k.lhandle.x = lh.x;
	k.lhandle.y = lh.y;
	k.lhandle.z = lh.z;
	k.rhandle.x = rh.x;
	k.rhandle.y = rh.y;
	k.rhandle.z = rh.z;
	return k;
}

//Constructor
template<class T>
Animation<T>::Animation()
{
	m_frameskip = 0;
	m_timeoffset = 0;
	m_interpolation = IP_LINEAR;
	ResetAnimation();
}

//Reset's animation
template<class T>
MP_INLINE void Animation<T>::ResetAnimation()
{
	m_pos = 0;
	m_playing = 0;
	m_loop = 0;
	m_timeoffset = m_time;
}

//Plays the Animation
template<class T>
MP_INLINE void Animation<T>::PlayAnimation(bool in)
{
	m_playing = in;
	m_timeoffset = m_time;
}

//Set's looping
template<class T>
MP_INLINE void Animation<T>::SetLooping(bool in)
{
	m_loop = in;
}

//Skips the first frame when looping
template<class T>
MP_INLINE void Animation<T>::SkipFirstFrame(bool in)
{
	m_frameskip = in;
}

//Set's animation position
template<class T>
MP_INLINE void Animation<T>::SetPosition(int in)
{
	m_pos = in;
}

//Adds a keyframe
template<class T>
MP_INLINE void Animation<T>::AddKeyframe(Keyframe<T> in)
{
	m_keyframes.push_back(in);
}

//Deletes a keyframe
template<class T>
MP_INLINE void Animation<T>::DeleteKeyframe(int pos)
{
	vector<Keyframe>::iterator iter = m_keyframes.begin()+pos;
	m_keyframes.erase(iter);
}


//Set's interpolation Method
template<class T>
void Animation<T>::SetInterpolation(int in)
{
	m_interpolation = in;

	if(m_interpolation == IP_FCURVE)
	{
		//Add keyframes to Bezier Composite
		for(int i = 0; i < m_keyframes.size()-1; i++)
		{
			m_bezier.AddCurve(BEZ_Curve(
				BVec(m_keyframes[i].time, m_keyframes[i].data, 0),
				m_keyframes[i].rhandle,
				m_keyframes[i+1].lhandle,
				BVec(m_keyframes[i+1].time, m_keyframes[i+1].data, 0)
				));
		}

		m_bezier.CalculateLookupTable(FCURVE_SAMPLES*m_keyframes.size(), m_keyframes[m_keyframes.size()-1].time);
	}
}

#endif


