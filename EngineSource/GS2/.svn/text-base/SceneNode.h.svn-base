/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	DO NOT TRANSFORM THE ROOT NODE, EVER.
*/

#ifndef SCENENODE_H
#define SCENENODE_H

#include "precom.h"

#include "MathLib.h"
#include "MatrixLib.h"
#include "ContentManager.h"
#include "Camera.h"
#include "Collision.h"


//SceneNode Class
class SceneNode
{
public:
	friend SceneNode;

	//Constructor
	SceneNode();
	SceneNode(std::string name);

	//Functions
	void ChainRender(); //Renders all children
	void RenderNode(); //Renders an individual node
	void RemoveAllChildren();
	void RemoveChild(std::string name);
	SceneNode* AddChild(std::string name);
	SceneNode* FindChildNode(std::string name);
	SceneNode* FindParentNode(std::string name);
	SceneNode* GetParentNode() const;
	std::string GetName(); //Get's node name
	
	//Find Wild Scene Nodes (nodes with the same name)
	SceneNode* FindParentNodeWild(std::string namepart);
	SceneNode* FindChildNodeWild(std::string namepart);
	void RemoveChildWild(std::string name);
	
	//Collision / Volume Functions
	bool IsMeshWithinSphereFrustum();
	coll::Sphere GetBoundingSphere() const;

	//Get Direction
	vec3::Vector3 GetLocalDirection();
	vec3::Vector3 GetWorldDirection();

	//Set Direction
	void SetLocalDirection(vec3::Vector3 ndir, vec3::Vector3 nup);

	//Get Position
	vec3::Vector3 GetLocalPosition();
	vec3::Vector3 GetWorldPosition();

	//Set Position
	void SetLocalPosition(vec3::Vector3 v);
	void SetLocalPosition(float x, float y, float z);
	void SetWorldPosition(vec3::Vector3 v);
	void SetWorldPosition(float x, float y, float z);

	//Get Transformation Matrix
	mat4::MATRIX4 GetWorldMatrix();
	mat4::MATRIX4 GetLocalMatrix();

	//Set Transformation Matrix
	void SetTransform(const mat4::MATRIX4& mat);
	void SetRotateTransform(const mat4::MATRIX4& mat);
	void SetScaleTransform(const mat4::MATRIX4& mat);
	void SetTranslateTransform(const mat4::MATRIX4& mat);

	//Reset Matrix's
	void ResetAllTransformMatrix();
	void ResetTranslateMatrix();
	void ResetScaleMatrix();
	void ResetRotateMatrix();

	//Translate Scene Node
	void Translate(vec3::Vector3 v);
	void Translate(float x, float y, float z);

	//Scale Scene Node
	void SetScale(vec3::Vector3 v);
	void SetScale(float x, float y, float z);

	//Rotate Scene Node
	void SetRotate(vec3::Vector3 v);
	void SetRotate(float x, float y, float z);
	void Rotate(vec3::Vector3 v);
	void Rotate(float x, float y, float z);
	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);

	//Attach / Detatch camera
	bool AttachCamera(Camera* cam);
	bool DetachCamera(Camera* cam);

	//Set 3D mesh associated to node
	pMODEL SetModel(pMODEL modelid);
	pMODEL GetModel();
	

	//Set Node Flag
	void SetFlag(char newflag);

private:
	
	//Update nodes children matrix's
	void UpdateChildren(const mat4::MATRIX4& worldmat, bool scaled);

	//Check if node has been scaled
	bool IsScaled() const;

	//Name of Node
	std::string m_name;

	//ID of model this node represents
	pMODEL m_modelid;

	//Parent of this Node
	SceneNode* m_parent;

	//Children this node contains
	std::list<SceneNode> m_children;

	//Camera Attached to this node
	Camera* m_camera;

	//Local Matrices
	mat4::MATRIX4 m_matrix_local_translate;
	mat4::MATRIX4 m_matrix_local_scale;
	mat4::MATRIX4 m_matrix_local_rotate;
	mat4::MATRIX4 m_matrix_world;

};

MP_INLINE SceneNode* SceneNode::GetParentNode() const
{
	if(m_parent->m_parent == NULL)
	{
		//Your parent is the root node.
		return NULL;
	}

	return m_parent;
}

MP_INLINE coll::Sphere SceneNode::GetBoundingSphere() const
{
	return ContentManager().GetXModel(m_modelid)->spherebound;
}

MP_INLINE mat4::MATRIX4 SceneNode::GetWorldMatrix()
{
	return m_matrix_world;
}

MP_INLINE mat4::MATRIX4 SceneNode::GetLocalMatrix()
{
	return m_matrix_local_scale * m_matrix_local_rotate * m_matrix_local_translate;
}

MP_INLINE pMODEL SceneNode::GetModel()
{
	return m_modelid;
}

MP_INLINE std::string SceneNode::GetName()
{
	return m_name;
}

MP_INLINE vec3::Vector3 SceneNode::GetLocalPosition()
{
	return vec3::Vector3(m_matrix_local_translate._41, m_matrix_local_translate._42, m_matrix_local_translate._43);
}

MP_INLINE vec3::Vector3 SceneNode::GetWorldPosition()
{
	return vec3::Vector3(m_matrix_world._41, m_matrix_world._42, m_matrix_world._43);
}

MP_INLINE vec3::Vector3 SceneNode::GetLocalDirection()
{
	return vec3::Vector3(m_matrix_local_rotate._31, m_matrix_local_rotate._32, m_matrix_local_rotate._33);
}

MP_INLINE vec3::Vector3 SceneNode::GetWorldDirection()
{
	return vec3::Vector3(m_matrix_world._31, m_matrix_world._32, m_matrix_world._33);
}

MP_INLINE void SceneNode::SetLocalDirection(vec3::Vector3 ndir, vec3::Vector3 nup)
{
	const vec3::Vector3 dirn = ndir;
	const vec3::Vector3 c = vec3::I_Normalize(vec3::CrossProduct(nup, dirn));
	const vec3::Vector3 rup = vec3::CrossProduct(dirn, c);
	m_matrix_local_rotate._11 = c.x;
	m_matrix_local_rotate._12 = c.y;
	m_matrix_local_rotate._13 = c.z;
	m_matrix_local_rotate._21 = rup.x;
	m_matrix_local_rotate._22 = rup.y;
	m_matrix_local_rotate._23 = rup.z;
	m_matrix_local_rotate._31 = dirn.x;
	m_matrix_local_rotate._32 = dirn.y;
	m_matrix_local_rotate._33 = dirn.z;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetLocalPosition(vec3::Vector3 v)
{
	SetLocalPosition(v.x, v.y, v.z);
}

MP_INLINE void SceneNode::SetLocalPosition(float x, float y, float z)
{
	m_matrix_local_translate._41 = x;
	m_matrix_local_translate._42 = y;
	m_matrix_local_translate._43 = z;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetWorldPosition(vec3::Vector3 v)
{
	SetWorldPosition(v.x, v.y, v.z);
}

MP_INLINE void SceneNode::SetWorldPosition(float x, float y, float z)
{
	m_matrix_local_translate._41 = x - m_matrix_world._41;
	m_matrix_local_translate._42 = y - m_matrix_world._42;
	m_matrix_local_translate._43 = z - m_matrix_world._43;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetTransform(const mat4::MATRIX4& mat)
{
	m_matrix_local_rotate._11 = mat._11;
	m_matrix_local_rotate._12 = mat._12;
	m_matrix_local_rotate._13 = mat._13;

	m_matrix_local_rotate._21 = mat._21;
	m_matrix_local_rotate._22 = mat._22;
	m_matrix_local_rotate._23 = mat._23;

	m_matrix_local_rotate._31 = mat._31;
	m_matrix_local_rotate._32 = mat._32;
	m_matrix_local_rotate._33 = mat._33;

	m_matrix_local_translate._41 = mat._41;
	m_matrix_local_translate._42 = mat._42;
	m_matrix_local_translate._43 = mat._43;

	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetRotateTransform(const mat4::MATRIX4& mat)
{
	m_matrix_local_rotate = mat;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetScaleTransform(const mat4::MATRIX4& mat)
{
	m_matrix_local_scale = mat;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetTranslateTransform(const mat4::MATRIX4& mat)
{
	m_matrix_local_translate = mat;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::ResetAllTransformMatrix()
{
	m_matrix_local_translate = mat4::Identity();
	m_matrix_local_scale = mat4::Identity();
	m_matrix_local_rotate = mat4::Identity();
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::ResetTranslateMatrix()
{
	m_matrix_local_translate = mat4::Identity();
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::ResetScaleMatrix()
{
	m_matrix_local_scale = mat4::Identity();
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::ResetRotateMatrix()
{
	m_matrix_local_rotate = mat4::Identity();
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::Translate(vec3::Vector3 v)
{
	Translate(v.x, v.y, v.z);
}

MP_INLINE void SceneNode::Translate(float x, float y, float z)
{
	const mat4::MATRIX4 t = mat4::Translate(x, y, z) * m_matrix_local_rotate;
	m_matrix_local_translate._41 += t._41;
	m_matrix_local_translate._42 += t._42;
	m_matrix_local_translate._43 += t._43;
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetScale(vec3::Vector3 v)
{
	m_matrix_local_scale = mat4::Scale(v.x, v.y, v.z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetScale(float x, float y, float z)
{
	m_matrix_local_scale = mat4::Scale(x, y, z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetRotate(vec3::Vector3 v)
{
	m_matrix_local_rotate = mat4::Rotate(v.x, v.y, v.z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::SetRotate(float x, float y, float z)
{
	m_matrix_local_rotate = mat4::Rotate(x, y, z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::Rotate(vec3::Vector3 v)
{
	m_matrix_local_rotate *= mat4::Rotate(v.x, v.y, v.z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::Rotate(float x, float y, float z)
{
	m_matrix_local_rotate *= mat4::Rotate(x, y, z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::RotateX(float x)
{
	m_matrix_local_rotate *= mat4::RotateX(x);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::RotateY(float y)
{
	m_matrix_local_rotate *= mat4::RotateY(y);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE void SceneNode::RotateZ(float z)
{
	m_matrix_local_rotate *= mat4::RotateZ(z);
	UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
}

MP_INLINE bool SceneNode::AttachCamera(Camera* cam)
{
	if(m_camera != NULL){return false;} //A camera is already attached
	if(cam->attached == true){return false;} //Camera allready attached to something
	m_camera = cam;
	cam->attached = true;
	return true;
}

MP_INLINE bool SceneNode::DetachCamera(Camera* cam)
{
	if(m_camera != cam){return false;} //This camera is not attached.
	m_camera = NULL;
	cam->attached = false;
	return true;
}

MP_INLINE bool SceneNode::IsScaled() const
{
	if(m_matrix_local_scale._11 != 1 || m_matrix_local_scale._22 != 1 || m_matrix_local_scale._33 != 1)
	{
		return true;
	}

	return false;
}

#endif








