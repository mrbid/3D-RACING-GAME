/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "PropEntity.h"

//Destructor
PropEntity::~PropEntity()
{
	//Remove from Bullet Physics
	BulletPhysics().RemoveShape(m_bulletprop);

	//Remove from Scene Graph
	SceneGraph().DeleteSceneNode(m_prop_node->GetName());
}

//Init Physics Prop
void PropEntity::Init(std::string uidname, pMODEL modelid, vec3::Vector3 offset, float mass, bool usebox)
{
	//Set prop name
	m_name = uidname;

	//Add prop to scene graph
	std::string nodename = m_name;
	nodename.append("_prop_node");
	m_prop_node = SceneGraph().AddChild(nodename);
	m_prop_node->SetModel(modelid);

	//Create Vehicle in Bullet Physics
	if(usebox == true)
	{
		const vec3::Vector3 boxscale = (ContentManager().GetXModel(modelid)->aaboxbound.m_max - ContentManager().GetXModel(modelid)->aaboxbound.m_min) * 0.5f;
		m_bulletprop = BulletPhysics().AddBox(offset, mass, boxscale);
	}
	else
	{
		m_bulletprop = BulletPhysics().AddModelConvex(offset, mass, modelid);
	}

	//Get Physics Shape Pointer
	m_physicsshape = BulletPhysics().GetShape(m_bulletprop);
}


