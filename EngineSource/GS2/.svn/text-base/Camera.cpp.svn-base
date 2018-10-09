/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	This includes Frustum, and Mouse Locking
*/

#include "precom.h"
#include "Camera.h"

//Constructor
Camera::Camera()
{
	matrix = mat4::Identity();
	mouse_sensitivity = 0.3f;
	ylooklimit = math::Degree(40.0f);
	MDX = 0.f, MDY = 0.f, TMDY = 0.f;
}

//Create Sphere Frustum
void Camera::CreateFrustum(float fov, float nearplane, float farplane)
{
	m_viewlen = farplane - nearplane;
	m_fwidhi = m_viewlen * tan(fov * 0.5f); //width and height (aspect 1)
	m_viewcenter = nearplane + (m_viewlen * 0.5f);
	m_bsphere.radius = vec3::Modulus(vec3::Vector3(0.f, 0.f, m_viewcenter) - vec3::Vector3(m_fwidhi, m_fwidhi, m_viewlen));
	m_bsphere.center = vec3::VECTOR_NULL;
}

//Update Mouse Delta and Lock to Screen
void Camera::UpdateMouseDelta(HWND hWnd, int x, int y, const int& window_width_2, const int& window_height_2)
{
	cts.x = 0, cts.y = 0;
	ClientToScreen(hWnd, &cts);

	float mMDY = math::Degree((y - window_height_2) * mouse_sensitivity);
	if(TMDY + mMDY < -ylooklimit){mMDY = 0.0f;}
	if(TMDY + mMDY > ylooklimit){mMDY = 0.0f;}

	MDX += math::Degree((x - window_width_2) * mouse_sensitivity);
	MDY += mMDY;
	TMDY += mMDY;

	SetCursorPos(cts.x + window_width_2, cts.y + window_height_2);
}








