/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H

#include "precom.h"
#include "BaseController.h"
#include "VehicleEntity.h"

//Vehicle ID
#define pVEHICLE int
#define RAY_HITNULL -1

//Vehicle Manager Class
class VehicleController : public BaseController
{
public:

	//Destructor
	~VehicleController();

	//Tick Controller
	void Update(float dt);

	//Render Controller
	void Render();

	//Get a list of avalible vehicles
	void GetAvalibleVehicles(std::vector<std::string>* vehicles);

	//Add a vehicle
	pVEHICLE AddVehicle(std::string vehicle, std::string texture, vec3::Vector3 origin, vec3::Vector3 direction);

	//fire a ray and return the vehicle it hit
	void RayCastForVehicles(vec3::Vector3 from, vec3::Vector3 to, pVEHICLE* vehicle, float* dist);

	//Fire ray and see how far you are from the map boundaries
	void RayCastForBoundaries(vec3::Vector3 from, vec3::Vector3 to, float* distout);

	//Remove all vehicles
	void RemoveAllVehicles();

	//Accessors
	VehicleEntity* GetVehicle(pVEHICLE vehicle);
	int GetVehicleCount();

private:
	
	//Array of vehicle entities
	std::vector<VehicleEntity*> m_vehicles;

	//Vehicle UID
	int m_vuid;

	//Vehicle Count (because calling m_vehicles.size() all the time is SLOW)
	int m_vehiclecount;

};

MP_INLINE int VehicleController::GetVehicleCount()
{
	return m_vehiclecount;
}

MP_INLINE void VehicleController::Update(float dt)
{
	for(std::vector<VehicleEntity*>::iterator iter = m_vehicles.begin(); iter != m_vehicles.end(); ++iter)
		(*iter)->Update(dt);
}

MP_INLINE void VehicleController::Render()
{
	for(std::vector<VehicleEntity*>::iterator iter = m_vehicles.begin(); iter != m_vehicles.end(); ++iter)
		(*iter)->Render();
}

MP_INLINE VehicleEntity* VehicleController::GetVehicle(pVEHICLE vehicle)
{
	return m_vehicles[vehicle];
}

#endif