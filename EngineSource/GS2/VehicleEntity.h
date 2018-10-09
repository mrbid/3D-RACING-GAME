#ifndef VEHICLEENTITY_H
#define VEHICLEENTITY_H


#include "precom.h"
#include "BaseEntity.h"
#include "SceneNodeGraph.h"
#include "BulletPhysics.h"
#include "Camera.h"


//Vehicle Entity Class
class VehicleEntity : public BaseEntity
{
public:


	//Destructor
	~VehicleEntity();

	//Update Vehicle Entity
	void Update(float dt);


	//Render Vehicle Entity
	void Render();


	//Init Vehicle Entity
	void Init(std::string uidname, std::string chassismodel, std::string wheelmodelfrontleft, std::string wheelmodelfrontright,
		std::string wheelmodelrearleft, std::string wheelmodelrearright, std::string texmap, CarInfo carinfo);


	//Reset Car
	void Reset(vec3::Vector3 origin);


	//Fire a general raycast for anything collidable
	CarRaycastResult RayCast(vec3::Vector3 from, vec3::Vector3 to);


	//Accessors
	void FreezeMotion();
	void UnFreezeMotion();


	void SetEngineForce(float force);
	float GetEngineForce();


	void SetBreakingForce(float force);
	float GetBreakingForce();


	void SetSteering(float steering);
	void IncrementSteering(float steering);
	void NeutralizeSteering(float speed);
	float GetSteering();


	std::string GetName();


	float GetSpeedKPH();


	vec3::Vector3 GetPosition();
	vec3::Vector3 GetDirection();
	quat::Quaternion GetOrientation();


	SceneNode* GetChassisNode();
	SceneNode* GetWheelNode(const int wheel);
	CarInfo* GetCarInfo();


	inline int getNextRLnode( void )			const	{ return m_nextRLnode; }
	inline int getPrevRLnode( void )			const	{ return m_prevRLnode; }
	void setRacingLineNode( const int node )			{ m_nextRLnode = node; m_prevRLnode = node-1; }
	void increaseRacingLineNode( void )					{ ++m_nextRLnode; ++m_prevRLnode; }


private:


	//Car Info
	std::string m_name;
	CarInfo* m_carinfo;


	//Scene Nodes
	SceneNode* m_chassis_node;
	SceneNode* m_wheel_node[4];


	//Bullet Physics Car ID
	pBTCAR m_bulletcar;


	//Racing Line Nodes
	int m_nextRLnode;
	int m_prevRLnode;


};




MP_INLINE void VehicleEntity::Update(float dt)
{
	//Update Engine Force, Breaking Force and Steering
	m_carinfo->UpdateHandelling();
}


MP_INLINE void VehicleEntity::Render()
{
	//If visible within the frustum, update scene graph positions
	if(m_chassis_node->IsMeshWithinSphereFrustum() == true)
	{
		//Update Chassis Position
		m_chassis_node->SetTransform(m_carinfo->GetChassisMatrix());


		//Update Wheels Positions
		m_wheel_node[0]->SetTransform(m_carinfo->GetWheelMatrix(0));
		m_wheel_node[1]->SetTransform(m_carinfo->GetWheelMatrix(1));
		m_wheel_node[2]->SetTransform(m_carinfo->GetWheelMatrix(2));
		m_wheel_node[3]->SetTransform(m_carinfo->GetWheelMatrix(3));
	}
}


MP_INLINE void VehicleEntity::Reset(vec3::Vector3 origin)
{
	BulletPhysics().ResetVehicle(m_bulletcar, origin);
}


MP_INLINE void VehicleEntity::SetEngineForce(float force)
{
	//Limit Speed
	if(GetSpeedKPH() >= m_carinfo->m_maxSpeedKPH || GetSpeedKPH() <= -100.f)
		m_carinfo->m_EngineForce = 0.f;
	else
		m_carinfo->m_EngineForce = m_carinfo->m_maxEngineForce * force;


	//Set Acceleration Force
	if(m_carinfo->m_EngineForce == 0.f)
	{
		m_carinfo->SetAccelerationForce(0.f);
	}
	else
	{
		if(m_carinfo->m_EngineForce > 0.f)
			m_carinfo->SetAccelerationForce(m_carinfo->m_accelerationForce);


		if(m_carinfo->m_EngineForce < -0.f)
			m_carinfo->SetAccelerationForce(-6000.f);
	}
}


MP_INLINE float VehicleEntity::GetEngineForce()
{
	return m_carinfo->m_EngineForce * m_carinfo->m_maxEngineForceRecip;
}


MP_INLINE float VehicleEntity::GetBreakingForce()
{
	return m_carinfo->m_BreakingForce * m_carinfo->m_maxBreakingForceRecip;
}


MP_INLINE void VehicleEntity::SetBreakingForce(float force)
{
	m_carinfo->m_BreakingForce = m_carinfo->m_maxBreakingForce * force;
}


MP_INLINE void VehicleEntity::SetSteering(float steering)
{
	m_carinfo->m_VehicleSteering = m_carinfo->m_maxSteering * steering;
}


MP_INLINE void VehicleEntity::NeutralizeSteering(float speed)
{
	if( m_carinfo->m_VehicleSteering < 0.01f && m_carinfo->m_VehicleSteering > -0.01f )
		m_carinfo->m_VehicleSteering = 0.f;
	else
		m_carinfo->m_VehicleSteering = m_carinfo->m_VehicleSteering *= speed;
}


MP_INLINE void VehicleEntity::IncrementSteering(float steering)
{
	const float nsv = m_carinfo->m_VehicleSteering + (m_carinfo->m_maxSteering * steering);


	if(nsv > m_carinfo->m_maxSteering)
	{
		m_carinfo->m_VehicleSteering = m_carinfo->m_maxSteering;
		return;
	}


	if(nsv < -m_carinfo->m_maxSteering)
	{
		m_carinfo->m_VehicleSteering = -m_carinfo->m_maxSteering;
		return;
	}


	m_carinfo->m_VehicleSteering = nsv;
}


MP_INLINE float VehicleEntity::GetSteering()
{
	return m_carinfo->m_VehicleSteering;
}


MP_INLINE std::string VehicleEntity::GetName()
{
	return m_name;
}


MP_INLINE SceneNode* VehicleEntity::GetChassisNode()
{
	return m_chassis_node;
}


MP_INLINE SceneNode* VehicleEntity::GetWheelNode(const int wheel)
{
	return m_wheel_node[wheel];
}


MP_INLINE CarInfo* VehicleEntity::GetCarInfo()
{
	return m_carinfo;
}


MP_INLINE float VehicleEntity::GetSpeedKPH()
{
	return m_carinfo->GetSpeed();
}


MP_INLINE vec3::Vector3 VehicleEntity::GetPosition()
{
	return m_carinfo->GetPosition();
}


MP_INLINE vec3::Vector3 VehicleEntity::GetDirection()
{
	return m_chassis_node->GetWorldDirection();
}


MP_INLINE quat::Quaternion VehicleEntity::GetOrientation()
{
	return m_carinfo->GetOrientation();
}


MP_INLINE CarRaycastResult VehicleEntity::RayCast(vec3::Vector3 from, vec3::Vector3 to)
{
	return m_carinfo->CastRay(from, to);
}


MP_INLINE void VehicleEntity::FreezeMotion()
{
	GetCarInfo()->FreezeMotion();
}


MP_INLINE void VehicleEntity::UnFreezeMotion()
{
	GetCarInfo()->UnFreezeMotion();
}


#endif