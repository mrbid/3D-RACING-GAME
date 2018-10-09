/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "precom.h"
#include "BaseController.h"
#include "VehicleEntity.h"
#include "Camera.h"

//Track Controllor Class
class CameraController : public BaseController
{
public:

	//Constructor
	CameraController() : m_vehicle(NULL), m_min_distance(10.0f), m_max_distance(35.0f), m_cameraHeight(20.0f){}

	//Tick Controller
	void Render();

	//Set Target Vehicle
	void SetTargetVehicle(VehicleEntity* vehicle);

private:

	//Vehicle camera is to follow
	VehicleEntity* m_vehicle;

	//Camera Interpolation
	vec3::Vector3 m_interpolated_pos;
	float m_min_distance;
	float m_max_distance;
	float m_cameraHeight;
};

MP_INLINE void CameraController::SetTargetVehicle(VehicleEntity* vehicle)
{
	m_vehicle = vehicle;
	m_interpolated_pos = vec3::Vector3(m_vehicle->GetPosition().x, m_vehicle->GetPosition().y + m_cameraHeight, m_vehicle->GetPosition().z) - (m_vehicle->GetDirection() * m_max_distance);
}

#endif

