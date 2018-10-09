/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef COLLISION_H
#define COLLISION_H

#include "precom.h"
#include "Vector3.h"
#include "Vector2.h"

namespace coll
{
	//Axis Aligned Bounding Box
	struct AABox
	{
		AABox()
		{
			m_min = vec3::VECTOR_NULL;
			m_max = vec3::VECTOR_NULL;
		}

		vec3::Vector3 m_min;
		vec3::Vector3 m_max;
	};

	//Oriented Bounding Box
	struct OBox
	{
		OBox()
		{
			ntl = vec3::VECTOR_NULL;
			ntr = vec3::VECTOR_NULL;
			nbl = vec3::VECTOR_NULL;
			nbr = vec3::VECTOR_NULL;
			ftl = vec3::VECTOR_NULL;
			ftr = vec3::VECTOR_NULL;
			fbl = vec3::VECTOR_NULL;
			fbr = vec3::VECTOR_NULL;
		}

		vec3::Vector3 ntl;
		vec3::Vector3 ntr;
		vec3::Vector3 nbl;
		vec3::Vector3 nbr;
		vec3::Vector3 ftl;
		vec3::Vector3 ftr;
		vec3::Vector3 fbl;
		vec3::Vector3 fbr;
	};

	//SphereBound
	struct Sphere
	{
		Sphere()
		{
			center = vec3::VECTOR_NULL;
			radius = 0.f;
		}

		float radius;
		vec3::Vector3 center; //an offset
	};

	//Circle
	struct Circle
	{
		Circle()
		{
			center = vec2::VECTOR_NULL;
			radius = 0.f;
		}

		float radius;
		vec2::Vector2 center; //an offset
	};

	//Check for an AABox Collision (world pos, bounding box)
	MP_INLINE bool AABoxCollision(vec3::Vector3 ap, AABox* a, vec3::Vector3 bp, AABox* b)
	{
		if((ap.x + a->m_max.x) > (bp.x + b->m_min.x) && (ap.x + a->m_min.x) < (bp.x + b->m_max.x) &&
			(ap.y + a->m_max.y) > (bp.y + b->m_min.y) && (ap.y + a->m_min.y) < (bp.y + b->m_max.y) &&
			(ap.z + a->m_max.z) > (bp.z + b->m_min.z) && (ap.z + a->m_min.z) < (bp.z + b->m_max.z))
		{
			return true;
		}

		return false;
	}

	//Check for a SphereBound Collision
	MP_INLINE bool SphereBoundCollision(vec3::Vector3 ap, const Sphere* a, vec3::Vector3 bp, const Sphere* b)
	{
		const float radius = a->radius + b->radius;
		if(vec3::LengthSq((ap + a->center) - (bp + b->center)) < (radius * radius)){return true;}
		return false;
	}

	//Check for a CircleBound Collision
	MP_INLINE bool CircleBoundCollision(vec2::Vector2 ap, const Circle* a, vec2::Vector2 bp, const Circle* b)
	{
		const float radius = a->radius + b->radius;
		if(vec2::LengthSq((ap + a->center) - (bp + b->center)) < (radius * radius)){return true;}
		return false;
	}

	//Sphere bound to circle bound
	MP_INLINE Circle SphereToCircle(Sphere* s)
	{
		Circle ret;
		ret.center.x = s->center.x;
		ret.center.y = s->center.z;
		ret.radius = s->radius;
		return ret;
	}
};

#endif