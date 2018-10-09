/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "CameraController.h"
#include "BulletPhysics.h"
#include "MilliTimer.h"

//Render Controller
void CameraController::Render()
{
	if(m_vehicle != NULL)
	{
		//Pre Compute
		const vec3::Vector3 cam_to_object = m_vehicle->GetPosition() - m_interpolated_pos;
		const float interpolate_distance = vec3::I_Modulus(cam_to_object);

		//Calculate Interpolated Distance
        m_interpolated_pos -= (interpolate_distance < m_min_distance ? (m_min_distance - interpolate_distance) / interpolate_distance
							: interpolate_distance > m_max_distance ? (m_max_distance - interpolate_distance) / interpolate_distance
							: 0.0f) * cam_to_object;

		//Set camera transform
		CameraSystem().ResetTransform();
		CameraSystem().SetTransform(&mat4::LookAt(
										vec3::Vector3(m_interpolated_pos.x, m_interpolated_pos.y + 7.5f, m_interpolated_pos.z),
										m_vehicle->GetPosition(),
										vec3::Vector3(0, 1, 0))
										);
		CameraSystem().Update();
	}
}



