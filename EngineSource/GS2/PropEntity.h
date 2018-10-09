/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef PROPENTITY_H
#define PROPENTITY_H

#include "precom.h"
#include "BaseEntity.h"
#include "SceneNodeGraph.h"
#include "BulletPhysics.h"

//Prop Entity Class
class PropEntity : public BaseEntity
{
public:

	//Destructor
	~PropEntity();
	
	//Render Physics Prop
	void Render();

	//Init Physics Prop
	void Init(std::string uidname, pMODEL modelid, vec3::Vector3 offset, float mass, bool usebox);

	//Accessors
	std::string GetName();

	SceneNode* GetSceneNode();
	PhysicsShape* GetPhysicsShape();

private:

	//Prop Info
	std::string m_name;
	PhysicsShape* m_physicsshape;

	//Scene Nodes
	SceneNode* m_prop_node;

	//Bullet PhysicsShape ID
	pBTSHAPE m_bulletprop;

};

MP_INLINE void PropEntity::Render()
{
	//If visible within the frustum, update scene graph positions
	if(m_prop_node->IsMeshWithinSphereFrustum() == true)
	{
		m_prop_node->SetTransform(m_physicsshape->GetWorldTransform());
	}
}

MP_INLINE std::string PropEntity::GetName()
{
	return m_name;
}

MP_INLINE SceneNode* PropEntity::GetSceneNode()
{
	return m_prop_node;
}

MP_INLINE PhysicsShape* PropEntity::GetPhysicsShape()
{
	return m_physicsshape;
}

#endif


