#include "precom.h"
#include "RaceController.h"
#include "GameWorld.h"


RaceController::RaceController()
{
	m_isredlight = false;
	m_greenlightwait = 0;
}

void RaceController::Update(float dt)
{
	//Is it a green light yet?
	if(GetTime() > m_greenlightwait)
	{
		VehicleController* vehiclecontroller = GameWorld().GetVehicleController();
		for(int i = 0; i < vehiclecontroller->GetVehicleCount(); ++i)
		{
			vehiclecontroller->GetVehicle(i)->UnFreezeMotion();
		}
	}
}

void RaceController::SetRedLight()
{
	//Set Redlight State to True
	m_isredlight = true;
	m_greenlightwait = GetTime() + 10000; //random value

	//Freeze all vehciles 
	VehicleController* vehiclecontroller = GameWorld().GetVehicleController();
	for(int i = 0; i < vehiclecontroller->GetVehicleCount(); ++i)
	{
		vehiclecontroller->GetVehicle(i)->FreezeMotion();
	}
}