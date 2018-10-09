/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	This includes Frustum, and Mouse Locking
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "precom.h"

#include "MatrixLib.h"
#include "Collision.h"
#include "D3DRenderer.h"

//Camera Class
class Camera
{
public:

	//Singleton
	static Camera& Inst()
	{
		static Camera singleton;
		return singleton;
	}
	~Camera(){} //Destructor

	//Update Camera
	void Update();

	//Get Matricies
	mat4::MATRIX4 GetMatrix();
	mat4::MATRIX4 GetInverseMatrix();

	//Set or Reset transfromation matrix
	void SetTransform(mat4::MATRIX4* t);
	void ResetTransform();

	//Configure Camera
	void SetSensitivity(float in);
	void SetYLookLimit(float in);

	//Set or Get Position
	void SetWorldPosition(vec3::Vector3 p);
	vec3::Vector3 GetWorldPosition();
	vec3::Vector3 GetLocalPosition();

	//Get's position of frustum sphere
	vec3::Vector3 GetFrustumSpherePosition();

	//Get Direction
	vec3::Vector3 GetLocalDirection();
	vec3::Vector3 GetWorldDirection();
	
	//Update Mouse Delta and Lock to Screen
	void UpdateMouseDelta(HWND hWnd, int x, int y, const int& window_width_2, const int& window_height_2);

	//Creates Frustum
	void CreateFrustum(float fov, float nearplane, float farplane);

	//Returns center of frustum sphere
	coll::Sphere FrustumSphereBound();

	//Get Mouse Delta X (clearing the old value)
	float GetMDX();

	//Get Mouse Delta Y (clearing the old value)
	float GetMDY();

	//Mouse Delta Positions
	float MDX, MDY;

	//Is the camera attached to a scene node?
	bool attached;

private:

	Camera(); //Constructor
	Camera(const Camera&); //Prevent Copy
	Camera& operator=(const Camera&); //Prevent Assignment

	mat4::MATRIX4 matrix; //Camera / View Matrix
	mat4::MATRIX4 invmatrix;
	tagPOINT cts; //Client To Screen
	float TMDY; //Track Rotation Amount in Y axis

	//Sensitivity and max look up/down
	float mouse_sensitivity;
	float ylooklimit;

	//Frustum Culling
	float m_viewcenter;
	coll::Sphere m_bsphere;
	float m_viewlen;
	float m_fwidhi; //Half of the far plane width/height

};

MP_INLINE void Camera::SetTransform(mat4::MATRIX4* t){matrix *= *t;}
MP_INLINE void Camera::ResetTransform(){matrix = mat4::Identity();}
MP_INLINE void Camera::SetSensitivity(float in){mouse_sensitivity = in;}
MP_INLINE void Camera::SetYLookLimit(float in){ylooklimit = math::Degree(in);}
MP_INLINE mat4::MATRIX4 Camera::GetMatrix(){return matrix;}
MP_INLINE mat4::MATRIX4 Camera::GetInverseMatrix(){return invmatrix;}
MP_INLINE coll::Sphere Camera::FrustumSphereBound(){return m_bsphere;}

MP_INLINE void Camera::Update()
{
	RenderSystem().SetViewTransform(matrix);
	invmatrix = mat4::I_Invert(matrix);
}

MP_INLINE float Camera::GetMDX()
{
	const float r = MDX;
	MDX = 0.f;
	return r;
}

MP_INLINE float Camera::GetMDY()
{
	const float r = MDY;
	MDY = 0.f;
	return r;
}

MP_INLINE void Camera::SetWorldPosition(vec3::Vector3 p)
{
	matrix._41 = p.x;
	matrix._42 = p.y;
	matrix._43 = p.z;
}

MP_INLINE vec3::Vector3 Camera::GetWorldPosition()
{
	return vec3::Vector3(invmatrix._41, invmatrix._42, invmatrix._43);
}

MP_INLINE vec3::Vector3 Camera::GetLocalPosition()
{
	return vec3::Vector3(matrix._41, matrix._42, matrix._43);
}

MP_INLINE vec3::Vector3 Camera::GetLocalDirection()
{
	return vec3::Vector3(matrix._31, matrix._32, matrix._33);
}

MP_INLINE vec3::Vector3 Camera::GetWorldDirection()
{
	return vec3::Vector3(invmatrix._31, invmatrix._32, invmatrix._33);
}

MP_INLINE vec3::Vector3 Camera::GetFrustumSpherePosition()
{
	return vec3::Vector3(
		vec3::Vector3(invmatrix._41, invmatrix._42, invmatrix._43) +
		(vec3::Vector3(invmatrix._31, invmatrix._32, invmatrix._33) *
		m_viewcenter));
}

//Return Instance to Sound Singleton
MP_INLINE Camera& CameraSystem(){return Camera::Inst();}

#endif