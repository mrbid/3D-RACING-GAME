/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	It's dangerous to ever manipulate the root node
	with transformations and the likes, so I have
	black boxed the functionality for that node.

	If you try to get the root node by asking one
	of the roots childen for a pointer to the parent
	it will tell you that it doesnt have a parent.

	TODO Improvements:
	- When rendering, render by texture so models
	  sharing the same texture get rendered at the
	  same time. (easy method: loop multiple times for each texture)
*/

#ifndef SCENENODEGRAPH_H
#define SCENENODEGRAPH_H

#include "precom.h"
#include "SceneNode.h"

//Scene Node Management Class
class SceneNodeGraph
{
public:

	friend SceneNode;

	//Return Singleton Instance
	static SceneNodeGraph& Inst()
	{
		static SceneNodeGraph singleton;
		return singleton;
	}

	//Deletes a Scene Node by name
	bool DeleteSceneNode(std::string name);

	//Deletes a Scene Node if string is found in name
	bool DeleteSceneNodeWild(std::string namepart);

	//Render Functions
	void ChainRender();

	//Utilities
	void RemoveChild(std::string name);
	void DeleteAllNodes();
	SceneNode* AddChild(std::string name);
	SceneNode* FindChildNode(std::string name);
	
private:

	SceneNodeGraph(){} //Constructor
	SceneNodeGraph(const SceneNodeGraph&); //Prevent Copy
	SceneNodeGraph& operator=(const SceneNodeGraph&); //Prevent Assignment

	//Sort Predicate
	static bool MyDataSortPredicate(SceneNode* d1, SceneNode* d2);

	//Root of Scene Graph
	SceneNode m_rootnode;

};

MP_INLINE bool SceneNodeGraph::MyDataSortPredicate(SceneNode* d1, SceneNode* d2)
{
	return vec3::DistanceSq(d1->GetWorldPosition(), CameraSystem().GetWorldPosition()) < vec3::DistanceSq(d2->GetWorldPosition(), CameraSystem().GetWorldPosition());
}

MP_INLINE bool SceneNodeGraph::DeleteSceneNode(std::string name)
{
	SceneNode* p = m_rootnode.FindParentNode(name);
	if(p != NULL){p->RemoveChildWild(name); return true;}
	return false;
}

MP_INLINE bool SceneNodeGraph::DeleteSceneNodeWild(std::string namepart)
{
	SceneNode* p = m_rootnode.FindParentNodeWild(namepart);
	if(p != NULL){p->RemoveChildWild(namepart); return true;}
	return false;
}

MP_INLINE void SceneNodeGraph::ChainRender()
{
	m_rootnode.ChainRender();
}

MP_INLINE void SceneNodeGraph::RemoveChild(std::string name)
{
	m_rootnode.RemoveChild(name);
}

MP_INLINE void SceneNodeGraph::DeleteAllNodes()
{
	m_rootnode.RemoveAllChildren();
}

MP_INLINE SceneNode* SceneNodeGraph::AddChild(std::string name)
{
	return m_rootnode.AddChild(name);
}

MP_INLINE SceneNode* SceneNodeGraph::FindChildNode(std::string name)
{
	return m_rootnode.FindChildNode(name);
}

//Return Instance to Singleton
MP_INLINE SceneNodeGraph& SceneGraph(){return SceneNodeGraph::Inst();}

#endif

