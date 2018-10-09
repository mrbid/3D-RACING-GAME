/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef TRACKCONTROLLER_H
#define TRACKCONTROLLER_H

#include "precom.h"
#include "BaseController.h"
#include "PropEntity.h"
#include "BulletPhysics.h"
#include "BlimpEntity.h"


//Track Controllor Class
class TrackController : public BaseController
{
public:
	
	//Constructor
	TrackController() : skydome_node(NULL) {}

	//Destructor
	~TrackController();

	//Tick Controller
	void Render();

	//Get a list of avalible tracks
	void GetAvalibleTracks(std::vector<std::string>* track);

	//Load Track
	void LoadTrack(std::string level);

	//Unload Track
	void UnloadTrack();

	//Accessors
	std::string GetTrackName();
	void AddStaticProp(SceneNode* node);
	void AddPhysicsProp(PropEntity* prop);


private:

	//Load GPD File
	void LoadGPD(std::string level);

	//Loaded Track Name
	std::string m_level;

	//Static Objects Array
	std::vector<SceneNode*> m_staticprops;

	//Physics Prop Array
	std::vector<PropEntity*> m_physprops;

	//Blimp Entity
	BlimpEntity m_blimp;

	//Skydome Node
	SceneNode* skydome_node;

};

MP_INLINE std::string TrackController::GetTrackName()
{
	return m_level;
}

MP_INLINE void TrackController::AddStaticProp(SceneNode* node)
{
	m_staticprops.push_back(node);
}

MP_INLINE void TrackController::AddPhysicsProp(PropEntity* prop)
{
	m_physprops.push_back(prop);
}

#endif

