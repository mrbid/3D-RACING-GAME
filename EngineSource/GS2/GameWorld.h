/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "precom.h"

#include "D3DRenderer.h"
#include "SceneNodeGraph.h"
#include "CellularAutomata.h"
#include "Camera.h"
#include "MilliTimer.h"
#include "ContentManager.h"
#include "BaseEntity.h"
#include "VehicleEntity.h"
#include "PropEntity.h"
#include "BaseController.h"
#include "VehicleController.h"
#include "TrackController.h"
#include "CameraController.h"
#include "RaceController.h"
#include "MicroTimer.h"
#include "AI.h"
#include "Components/Managers/Input/InputAction.hpp"

#define STARTGRID 0
#define RACING 1

//GameWorld Class
class GameWorld
{
public:

	//Singleton
	static GameWorld& Inst()
	{
		static GameWorld singleton;
		return singleton;
	}
	~GameWorld();

	//Functions
	void Init(HWND hwnd);
	void Load();
	void Render();
	void Update(float dt);
	void SetProjection();
	void Messages( flex::components::sInputState* wButtons );

	//void LoadTrack(int id)
	//{
	//	//Stunt
	//	if(id == 0)
	//	{
	//		GameWorld().GetTrackController()->LoadTrack("stunt");
	//		RenderSystem().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//		GameWorld().GetVehicleController()->AddVehicle("clio", "textures/clioblue.jpg", Vector3(40.f, 30.2f, 0.f), Vector3(-0.52f,0,0.85f));
	//	}

	//	//Shib
	//	if(id == 1)
	//	{
	//		GameWorld().GetTrackController()->LoadTrack("shib");
	//		RenderSystem().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//		GameWorld().GetAIController()->AddAIVechicles();
	//		GameWorld().GetVehicleController()->AddVehicle("clio", "textures/clioblue.jpg", Vector3(-2335.f, -26.2f, -1335.f), Vector3(-0.52f,0,0.85f));
	//	}
	//}

	//Accessors
	VehicleController* GetVehicleController();
	RaceController* GetRaceController();
	TrackController* GetTrackController();
	AIController* GetAIController();

	//No time...
	CameraController* m_cameracontroller;

private:

	GameWorld() : m_switchreg(0.f) {} //Constructor
	GameWorld(const GameWorld&); //Prevent Copy
	GameWorld& operator=(const GameWorld&); //Prevent Assignment
	
	//Array of Controllers
	std::vector<BaseController*> m_controllers;

	//Controllers
	VehicleController* m_vehiclecontroller;
	TrackController* m_trackcontroller;
	RaceController* m_racecontroller;
	AIController* m_AIcontroller;

	//Variables
	int m_selectedvehicle;
	int m_gameState;
	double m_switchreg;
	
	//Timer
	MicroTimer m_timer;

};

MP_INLINE VehicleController* GameWorld::GetVehicleController()
{
	return m_vehiclecontroller;
}

MP_INLINE TrackController* GameWorld::GetTrackController()
{
	return m_trackcontroller;
}

MP_INLINE RaceController* GameWorld::GetRaceController()
{
	return m_racecontroller;
}

MP_INLINE AIController* GameWorld::GetAIController()
{
	return m_AIcontroller;
}

//Game World Instance
MP_INLINE GameWorld& GameWorld(){return GameWorld::Inst();}

#endif








