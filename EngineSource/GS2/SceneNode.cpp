/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	TODO: Painter Render
*/

#include "precom.h"
#include "SceneNode.h"
#include "GameWorld.h"
#include "SceneNodeGraph.h"

//Constructors
SceneNode::SceneNode()
{
	m_modelid = NULL_MODEL;
	m_camera = NULL;
	
	m_matrix_local_scale = mat4::Identity();
	m_matrix_local_rotate = mat4::Identity();
	m_matrix_local_translate = mat4::Identity();
	m_matrix_world = mat4::Identity();

	m_name = "rootnode";
}

SceneNode::SceneNode(std::string name)
{
	m_modelid = NULL_MODEL;
	m_camera = NULL;

	m_matrix_local_scale = mat4::Identity();
	m_matrix_local_rotate = mat4::Identity();
	m_matrix_local_translate = mat4::Identity();
	m_matrix_world = mat4::Identity();

	m_name = name;
}

//Set's model from content manager id
pMODEL SceneNode::SetModel(pMODEL modelid)
{
	m_modelid = modelid;
	return m_modelid;
}

//Removes all children from node
void SceneNode::RemoveAllChildren()
{
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		iter->RemoveAllChildren();
    }

	m_children.clear();
}

//Deletes a child node by Name
void SceneNode::RemoveChild(std::string name)
{
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.compare(name) == 0)
		{
			iter->RemoveAllChildren();
			iter = m_children.erase(iter);
			return;
		}
	}
}

//Deletes a child node by Name Wild
void SceneNode::RemoveChildWild(std::string namepart)
{
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.find(namepart) != string::npos)
		{
			iter->RemoveAllChildren();
			iter = m_children.erase(iter);
			return;
		}
	}
}

//Find's a Child Node
SceneNode* SceneNode::FindChildNode(std::string name)
{
	//Check my children for the node.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.compare(name) == 0){return (SceneNode*)&*iter;}
    }

	//Node not found in my children, check my childrens children.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
        SceneNode* n = iter->FindChildNode(name);
		if(n != NULL){return n;}else{return NULL;}
    }

	return NULL;
}

//Find's the parent of a node
SceneNode* SceneNode::FindParentNode(std::string name)
{
	//Check my children for the node.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.compare(name) == 0){return (SceneNode*)this;}
    }

	//Node not found in my children, check my childrens children.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		SceneNode* n = iter->FindParentNode(name);
		if(n != NULL){return n;}else{return NULL;}
    }

	return NULL;
}

//Find's a Child Node Wild
SceneNode* SceneNode::FindChildNodeWild(std::string namepart)
{
	//Check my children for the node.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.find(namepart) != string::npos){return (SceneNode*)&*iter;}
    }

	//Node not found in my children, check my childrens children.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
        SceneNode* n = iter->FindChildNodeWild(namepart);
		if(n != NULL){return n;}else{return NULL;}
    }

	return NULL;
}

//Find's the parent of a node Wild
SceneNode* SceneNode::FindParentNodeWild(std::string namepart)
{
	//Check my children for the node.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if(iter->m_name.find(namepart) != string::npos){return (SceneNode*)this;}
    }

	//Node not found in my children, check my childrens children.
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		SceneNode* n = iter->FindParentNodeWild(namepart);
		if(n != NULL){return n;}else{return NULL;}
    }

	return NULL;
}

//Add a Child Node
SceneNode* SceneNode::AddChild(std::string name)
{
	SceneNode n(name);
	n.m_matrix_world = m_matrix_local_scale * m_matrix_local_rotate * m_matrix_local_translate * m_matrix_world;
	n.m_parent = this;
	m_children.push_back(n);

	if(m_parent == NULL){
		UpdateChildren(mat4::Identity(), false);
	}else{
		UpdateChildren(m_parent->m_matrix_world, m_parent->IsScaled());
	}

	return &m_children.back();
}

//Update Scene Node
void SceneNode::UpdateChildren(const mat4::MATRIX4& worldmat, bool scaled)
{
	//Calculate Matrix
	mat4::MATRIX4 rottran = m_matrix_local_rotate;
	rottran._41 = m_matrix_local_translate._41;
	rottran._42 = m_matrix_local_translate._42;
	rottran._43 = m_matrix_local_translate._43;
	m_matrix_world = m_matrix_local_scale * rottran * worldmat;

	//Has this node been scaled?
	if(IsScaled() == true)
	{
		scaled = true;
	}
	
	//If camera is attached update transform
	if(m_camera != NULL)
	{
		//Remove scaling factor from world matrix and invert - that's the cam matrix
		//3 divides, 3 square roots, 18 multiplication
		if(scaled == true)
		{
			const float sx = math::rcp(math::isqrt( m_matrix_world._11*m_matrix_world._11 +
													m_matrix_world._12*m_matrix_world._12 +
													m_matrix_world._13*m_matrix_world._13 ));
			const float sy = math::rcp(math::isqrt( m_matrix_world._21*m_matrix_world._21 +
													m_matrix_world._22*m_matrix_world._22 +
													m_matrix_world._23*m_matrix_world._23 ));
			const float sz = math::rcp(math::isqrt( m_matrix_world._31*m_matrix_world._31 +
													m_matrix_world._32*m_matrix_world._32 +
													m_matrix_world._33*m_matrix_world._33 ));

			mat4::MATRIX4 world_noscale = m_matrix_world;
			world_noscale._11 = m_matrix_world._11 * sx;
			world_noscale._12 = m_matrix_world._12 * sx;
			world_noscale._13 = m_matrix_world._13 * sx;
			world_noscale._21 = m_matrix_world._21 * sy;
			world_noscale._22 = m_matrix_world._22 * sy;
			world_noscale._23 = m_matrix_world._23 * sy;
			world_noscale._31 = m_matrix_world._31 * sz;
			world_noscale._32 = m_matrix_world._32 * sz;
			world_noscale._33 = m_matrix_world._33 * sz;

			m_camera->ResetTransform();
			m_camera->SetTransform(&mat4::I_Invert(world_noscale));
			m_camera->Update();
		}
		else
		{
			m_camera->ResetTransform();
			m_camera->SetTransform(&mat4::I_Invert(m_matrix_world));
			m_camera->Update();
		}
	}

	//Update Children
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
    {
        iter->UpdateChildren(m_matrix_world, scaled);
    }
}

//Render Scene Node
void SceneNode::RenderNode()
{
	//Transform and render mesh.
	if(m_modelid != NULL_MODEL)
	{
		RenderSystem().SetWorldTransform(m_matrix_world);
		ContentManager().RenderModel(m_modelid);
		RenderSystem().SetWorldTransform(mat4::Identity());
	}
}

//Is node mesh within sphere frustum
MP_INLINE bool SceneNode::IsMeshWithinSphereFrustum()
{
	if(m_modelid == NULL_MODEL)
		return false;
	
	if(coll::SphereBoundCollision(GetWorldPosition(), &ContentManager().GetXModel(m_modelid)->spherebound, CameraSystem().GetFrustumSpherePosition(), &CameraSystem().FrustumSphereBound()) == false)
	{
		return false;
	}

	return true;
}

//Render Scene Node
void SceneNode::ChainRender()
{
	//Render Children
	for(std::list<SceneNode>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
    {
        iter->ChainRender();
    }

	//Is node mesh viewable in the frustum? (simple sphere bound check)
	if(IsMeshWithinSphereFrustum() == false)
	{
		return; //Node Mesh is Not Visible
	}

	//Transform and render mesh.
	if(m_modelid != NULL_MODEL)
	{
		RenderSystem().SetWorldTransform(m_matrix_world);
		ContentManager().RenderModel(m_modelid);
		RenderSystem().SetWorldTransform(mat4::Identity());
	}
}





