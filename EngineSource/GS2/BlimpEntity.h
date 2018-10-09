/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef BLIMPENTITY_H
#define BLIMPENTITY_H

#include "precom.h"
#include "BaseEntity.h"
#include "SceneNodeGraph.h"
#include "Bezier.h"
#include "MilliTimer.h"

//Blimp Entity Class
class BlimpEntity : public BaseEntity
{
public:

	//Render Blimp Entity
	void Render();

	//Init Blimp Entity
	void Init(std::string uidname)
	{
		//Load Blimp
		m_node = SceneGraph().AddChild(uidname);
		pMODEL model = ContentManager().LoadXModel("models/blimp.X", false, true, false);
		ContentManager().meshScale(model, GLOBAL_MESHSCALE);
		ContentManager().LoadDiffuse(model, 0, "textures/blimpmap.jpg");
		m_node->SetModel(model);

		//Create path
		const float scale = 1000.f;
		m_bez.AddCurve(BEZ_Curve(vec3::Vector3(0.f, 0.f, 0.f), vec3::Vector3(scale, 0.f, 0.f), vec3::Vector3(scale, 0.f, scale), vec3::Vector3(0.f, 0.f, scale)));
		m_bez.AddCurve(BEZ_Curve(vec3::Vector3(0.f, 0.f, scale), vec3::Vector3(-scale, 0.f, scale), vec3::Vector3(-scale, 0.f, 0.f), vec3::Vector3(0.f, 0.f, 0.f)));
		m_bez.CalculateLookupTable(100, 100);

		//Position on curve
		m_pos = 0.f;

		//Speed
		m_speed = 0.3f;
	}

private:

	//Bezier Path
	BezierComposite m_bez;
	float m_pos;

	//Motion Speed
	float m_speed;

	//Blimp Info
	std::string m_name;

	//Scene Nodes
	SceneNode* m_node;

};

MP_INLINE void BlimpEntity::Render()
{
	//Increment Position on Curve
	if(m_pos >= 100.f)
		m_pos = 0.f;
	else
		m_pos += m_speed;

	//If visible within the frustum, update scene graph positions
	if(m_node->IsMeshWithinSphereFrustum() == true)
	{
		m_node->SetLocalPosition(vec3::Vector3(-2800.f, -36.2f, -800.f) + m_bez.GetPoint(m_bez.DistanceToTime(m_pos)));
		m_node->SetLocalDirection(m_bez.GetDirection(m_bez.DistanceToTime(m_pos)), vec3::Vector3(0, 1, 0));
	}
}

#endif


