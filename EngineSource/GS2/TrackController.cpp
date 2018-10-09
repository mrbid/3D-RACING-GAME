/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "TrackController.h"
#include "GameWorld.h"
#include "Components\Managers\Screen\cScreenManager.hpp"


//Destructor
TrackController::~TrackController()
{
	UnloadTrack();
}

//Tick Controller
void TrackController::Render()
{
	//Update Props
	for(std::vector<PropEntity*>::iterator iter = m_physprops.begin(); iter != m_physprops.end(); ++iter)
		(*iter)->Render();

	//Update Blimp
	if(skydome_node != NULL)
		m_blimp.Render();
}

//Get a list of available tracks
void TrackController::GetAvalibleTracks(std::vector<std::string>* track)
{
	WIN32_FIND_DATA fdat;
	HANDLE srch = FindFirstFile("models/maps/*.*", &fdat);
	do
	{
		if(strcmp(fdat.cFileName, ".") != 0 && strcmp(fdat.cFileName, "..") != 0)
			track->push_back(fdat.cFileName);
	}
	while(FindNextFile(srch, &fdat));
}

//Load Track
void TrackController::LoadTrack(std::string level)
{
	//Paths
	std::string rootpath = "models/maps/";
	rootpath.append(level);
	std::string skydomepath = rootpath;
	skydomepath.append("/skydome.X");
	std::string terrainmodel = rootpath;
	terrainmodel.append("/road.X");
	std::string barriermodel = rootpath;
	barriermodel.append("/invisbarriers.X");

	//Create Skydome
	pMODEL skydome = ContentManager().LoadXModel(skydomepath, true, true, false);
	ContentManager().meshScale(skydome, GLOBAL_MESHSCALE);
	skydome_node = SceneGraph().AddChild("StaticProp skydome_node");
	skydome_node->SetModel(skydome);

	//Add terrain to bullet physics
	pMODEL visterrain = ContentManager().LoadXModel(terrainmodel, true, true, true);
	ContentManager().meshScale(visterrain, GLOBAL_MESHSCALE);
	pMODEL invisterrain = ContentManager().LoadXModel(barriermodel.c_str(), false, false, true);
	ContentManager().meshScale(invisterrain, GLOBAL_MESHSCALE);
	BulletPhysics().CreateTerrain(vec3::VECTOR_NULL, visterrain, invisterrain);

	//Temp Terrain
	SceneNode* terrain_node = SceneGraph().AddChild("StaticProp terrain_node");
	terrain_node->SetModel(visterrain);

	//Load Props
	LoadGPD(level);
	//SMG->SetProgressbar(100);

	//Init Blimp
	m_blimp.Init("StaticProp blimp");

	//Set Red Light
	GameWorld().GetRaceController()->SetRedLight();
}

//GPD Thread
DWORD WINAPI ThreadGPD(void* param)
{
	SMG->RenderLoadScreen();
	ExitThread(0);
	return 0;
}

//Load GPD File
void TrackController::LoadGPD(std::string level)
{
	m_level = level;
	
	std::string rootpath = "models/maps/";
	rootpath.append(GameWorld().GetTrackController()->GetTrackName());
	std::string gpdfile = rootpath;
	gpdfile.append("/export.gpd");

	FILE* file = fopen(gpdfile.c_str(), "r");
	if(file != NULL)
	{
		char name[256];
		char model[256];
		char modelpath[256];
		vec3::Vector3 pos;


		//Load Static Mesh
		fscanf(file, "STATIC\n");

		const float percentage = 100.f / 1417.f;
		int itteration = 0;

		while(1)
		{
			//Get Prop Name
			fscanf(file, "%s\n", &name);

			//Have we reached the end of the list?
			if(strcmp(name, "END") == 0)
				break;

			//Load model name and world offset
			fscanf(file, "%s\n", &model);
			fscanf(file, "pos [%f,%f,%f]\n", &pos.x, &pos.z, &pos.y);

			//Load model
			sprintf(modelpath, "%s/%s", rootpath.c_str(), model);
			pMODEL model = ContentManager().LoadXModel(modelpath, true, true, true);
			ContentManager().meshScale(model, GLOBAL_MESHSCALE);
			SceneNode* node = SceneGraph().AddChild(name);
			node->SetModel(model);
			node->SetLocalPosition(pos.x * GLOBAL_MESHSCALE, pos.y * GLOBAL_MESHSCALE, pos.z * GLOBAL_MESHSCALE);

			//Add scene node pointer to props array
			GameWorld().GetTrackController()->AddStaticProp(node);
			itteration++;
			SMG->SetProgressbar( (int) ( percentage * (float)itteration ) );
			//DWORD tid;
			//HANDLE m_gpdthread;
			//m_gpdthread = CreateThread(NULL, 0, ThreadGPD, NULL, 0, &tid);
		}

		//Load Physics Props
		fscanf(file, "\nPHYSICS\n");

		while(1)
		{
			//Get Prop Name & Mass
			float mass = 0.f;
			fscanf(file, "%s %f\n", &name, &mass);

			//Have we reached the end of the list?
			if(strcmp(name, "END") == 0)
				break;

			//Load model name and world offset
			fscanf(file, "%s\n", &model);
			fscanf(file, "pos [%f,%f,%f]\n", &pos.x, &pos.z, &pos.y);

			//Load model
			sprintf(modelpath, "%s/%s", rootpath.c_str(), model);
			pMODEL model = ContentManager().LoadXModel(modelpath, true, true, true);
			ContentManager().meshScale(model, GLOBAL_MESHSCALE);
			PropEntity* prop = new PropEntity;
			prop->Init(name, model, vec3::Vector3(pos.x * GLOBAL_MESHSCALE, pos.y * GLOBAL_MESHSCALE, pos.z * GLOBAL_MESHSCALE), mass, true);

			//Add scene node pointer to props array
			GameWorld().GetTrackController()->AddPhysicsProp(prop);
			itteration++;
			SMG->SetProgressbar( (int) ( percentage * (float)itteration ) );
			//DWORD tid;
			//HANDLE m_gpdthread;
			//m_gpdthread = CreateThread(NULL, 0, ThreadGPD, NULL, 0, &tid);
		}
			
		//Close File
		fclose(file);
	}

	SMG->SetProgressbar( (int) 100 );
}

//Unload Track
void TrackController::UnloadTrack()
{
	//Delete All Static Nodes
	bool  found = true;
	while(found == true)
		found = SceneGraph().DeleteSceneNodeWild("StaticProp");

	//Delete All Physics Prop Nodes
	found = true;
	while(found == true)
		found = SceneGraph().DeleteSceneNodeWild("PhysProp");

	//Delete all Prop Entities
	for(std::vector<PropEntity*>::iterator iter = m_physprops.begin(); iter != m_physprops.end(); ++iter)
		delete (*iter);

	//Clear props array
	m_physprops.clear();

	//Null Pointers
	skydome_node = NULL;
}

