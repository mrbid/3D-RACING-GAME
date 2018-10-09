/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "VehicleEntity.h"

//Destructor
VehicleEntity::~VehicleEntity()
{
	//Remove from Bullet Physics
	BulletPhysics().DestroyVehicle(m_bulletcar);

	//Remove from Scene Graph
	SceneGraph().DeleteSceneNode(m_chassis_node->GetName());
		
	for(int i = 0; i < 4; ++i)
		SceneGraph().DeleteSceneNode(m_wheel_node[i]->GetName());
}

//Init Physics Car
void VehicleEntity::Init(std::string uidname, std::string chassismodel, std::string wheelmodelfrontleft, std::string wheelmodelfrontright, std::string wheelmodelrearleft, std::string wheelmodelrearright, std::string texmap, CarInfo carinfo)
{
	//Set car name
	m_name = uidname;

	//Add car chassis to scene graph
	std::string nodename = m_name;
	nodename.append("_chassis_node");
	m_chassis_node = SceneGraph().AddChild(nodename);
	carinfo.m_chassisModel = ContentManager().LoadXModel(chassismodel, false, false, true);
	ContentManager().meshScale(carinfo.m_chassisModel, carinfo.m_chassisScale);
	m_chassis_node->SetModel(carinfo.m_chassisModel);

	//Load texture
	ContentManager().LoadDiffuse(carinfo.m_chassisModel, 0, texmap);
	ContentManager().GenerateMipLevels(carinfo.m_chassisModel, 0);

	//Add car wheels to scene graph
	for(int i = 0; i < 4; ++i)
	{
		char wheelname[256];
		sprintf(wheelname, "%s_wheel%i_node", m_name.c_str(), i);
		m_wheel_node[i] = SceneGraph().AddChild(wheelname);

		pMODEL mid = 0;

		if(i == 0)
		{
			mid = ContentManager().LoadXModel(wheelmodelfrontleft, false, false, true);
			ContentManager().meshScale(mid, carinfo.m_chassisScale);
			m_wheel_node[i]->SetModel(mid);
		}

		if(i == 1)
		{
			mid = ContentManager().LoadXModel(wheelmodelfrontright, false, false, true);
			ContentManager().meshScale(mid, carinfo.m_chassisScale);
			m_wheel_node[i]->SetModel(mid);
		}

		if(i == 2)
		{
			mid = ContentManager().LoadXModel(wheelmodelrearleft, false, false, true);
			ContentManager().meshScale(mid, carinfo.m_chassisScale);
			m_wheel_node[i]->SetModel(mid);
		}

		if(i == 3)
		{
			mid = ContentManager().LoadXModel(wheelmodelrearright, false, false, true);
			ContentManager().meshScale(mid, carinfo.m_chassisScale);
			m_wheel_node[i]->SetModel(mid);
		}

		//Load texture
		ContentManager().LoadDiffuse(mid, 0, texmap);
		ContentManager().GenerateMipLevels(mid, 0);
	}

	//Create Vehicle in Bullet Physics
	m_bulletcar = BulletPhysics().CreateVehicle(carinfo);

	//Get CarInfo Pointer
	m_carinfo = BulletPhysics().GetCar(m_bulletcar);
}


