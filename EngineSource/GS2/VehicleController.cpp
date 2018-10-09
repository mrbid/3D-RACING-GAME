/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "VehicleController.h"

//Destructor
VehicleController::~VehicleController()
{
	for(std::vector<VehicleEntity*>::iterator iter = m_vehicles.begin(); iter != m_vehicles.end(); ++iter)
		delete (*iter);

	m_vehicles.clear();
}

//Get a list of avalible vehicles
void VehicleController::GetAvalibleVehicles(std::vector<std::string>* vehicles)
{
	WIN32_FIND_DATA fdat;

	HANDLE srch = FindFirstFile("vehicles\\*.txt*", &fdat);
	do
	{
		for(unsigned int i = 0; i < strlen(fdat.cFileName); ++i)
		{
			if(fdat.cFileName[i] == '.')
			{
				fdat.cFileName[i] = 0x00;
				break;
			}
		}

		vehicles->push_back(fdat.cFileName);
	}
	while(FindNextFile(srch, &fdat));
}

//Add a vehicle
pVEHICLE VehicleController::AddVehicle(std::string vehicle, std::string texture, vec3::Vector3 origin, vec3::Vector3 direction)
{
	//Vehicle Info
	VehicleEntity* vehicleentity = new VehicleEntity;
	CarInfo car;
	char chassismodel[256];
	char leftfrontwheelmodel[256];
	char rightfrontwheelmodel[256];
	char leftrearwheelmodel[256];
	char rightrearwheelmodel[256];
	car.m_startOrigin = origin;

	//Load Vehicle Data
	std::string filename = "vehicles/";
	filename.append(vehicle);
	filename.append(".txt");

	FILE* fin = fopen(filename.c_str(), "r");
	if(fin != NULL)
	{
		fscanf(fin, "chassisModel: %s\n", chassismodel);
		fscanf(fin, "leftFrontWheelModel: %s\n", leftfrontwheelmodel);
		fscanf(fin, "rightFrontWheelModel: %s\n", rightfrontwheelmodel);
		fscanf(fin, "leftRearWheelModel: %s\n", leftrearwheelmodel);
		fscanf(fin, "rightRearWheelModel: %s\n", rightrearwheelmodel);
		fscanf(fin, "chassisScale: %f\n\n", &car.m_chassisScale);

		fscanf(fin, "wheelPositionFrontLeft: %f,%f,%f\n", &car.m_wheelPosition[0].x, &car.m_wheelPosition[0].y, &car.m_wheelPosition[0].z);
		fscanf(fin, "wheelPositionFrontRight: %f,%f,%f\n", &car.m_wheelPosition[1].x, &car.m_wheelPosition[1].y, &car.m_wheelPosition[1].z);
		fscanf(fin, "wheelPositionRearLeft: %f,%f,%f\n", &car.m_wheelPosition[2].x, &car.m_wheelPosition[2].y, &car.m_wheelPosition[2].z);
		fscanf(fin, "wheelPositionRearRight: %f,%f,%f\n\n", &car.m_wheelPosition[3].x, &car.m_wheelPosition[3].y, &car.m_wheelPosition[3].z);

		fscanf(fin, "maxSteering: %f\n", &car.m_maxSteering);
		fscanf(fin, "frontWheelRadius: %f\n", &car.m_frontWheelRadius);
		fscanf(fin, "backWheelRadius: %f\n", &car.m_backWheelRadius);
		fscanf(fin, "chassisMass: %f\n", &car.m_chassisMass);
		fscanf(fin, "maxBreakingForce: %f\n", &car.m_maxBreakingForce);
		car.m_maxBreakingForceRecip = 1.f / car.m_maxBreakingForce;
		fscanf(fin, "maxSpeedKPH: %f\n", &car.m_maxSpeedKPH);
		car.m_maxSpeedKPHRecip = 1.f / car.m_maxSpeedKPH;
		fscanf(fin, "maxEngineForce: %f\n", &car.m_maxEngineForce);
		car.m_maxEngineForceRecip = 1.f / car.m_maxEngineForce;
		fscanf(fin, "accelerationForce: %f\n", &car.m_accelerationForce);

		float accelerationStamina = 0.f;
		fscanf(fin, "accelerationStamina: %f\n", &accelerationStamina);
		car.m_accelerationFalloff.Set(1.f, accelerationStamina, accelerationStamina, 0.f);

		fscanf(fin, "skidForce: %f\n", &car.m_skidForce);
		fscanf(fin, "wheelFriction: %f\n", &car.m_wheelFriction);
		fscanf(fin, "rollInfluence: %f\n\n", &car.m_rollInfluence);

		fscanf(fin, "suspensionStiffness: %f\n", &car.m_suspensionStiffness);
		fscanf(fin, "suspensionRelaxation: %f\n", &car.m_suspensionRelaxation);
		fscanf(fin, "suspensionCompression: %f\n", &car.m_suspensionCompression);
		fscanf(fin, "suspensionRestLength: %f\n", &car.m_suspensionRestLength);
		fscanf(fin, "maxSuspensionForce: %f\n", &car.m_maxSuspensionForce);
		fscanf(fin, "maxSuspensionTravelCm: %f\n", &car.m_maxSuspensionTravelCm);
		fscanf(fin, "frictionSlip: %f\n", &car.m_frictionSlip);

		char wheeldrive[32];
		fscanf(fin, "wheelDrive: %s\n", wheeldrive);

		if(!strcmp(wheeldrive, "FRONTWHEEL"))
			car.m_wheelDrive = DRIVE_FRONTWHEEL;

		if(!strcmp(wheeldrive, "REARWHEEL"))
			car.m_wheelDrive = DRIVE_REARWHEEL;

		if(!strcmp(wheeldrive, "FOURWHEEL"))
			car.m_wheelDrive = DRIVE_FOURWHEEL;

		fclose(fin);
	}
	
	//Set paths
	char chassismodelpath[256];
	char leftfrontwheelmodelpath[256];
	char rightfrontwheelmodelpath[256];
	char leftrearwheelmodelpath[256];
	char rightrearwheelmodelpath[256];
	sprintf(chassismodelpath, "models/%s", chassismodel);
	sprintf(leftfrontwheelmodelpath, "models/%s", leftfrontwheelmodel);
	sprintf(rightfrontwheelmodelpath, "models/%s", rightfrontwheelmodel);
	sprintf(leftrearwheelmodelpath, "models/%s", leftrearwheelmodel);
	sprintf(rightrearwheelmodelpath, "models/%s", rightrearwheelmodel);
	
	//Add Vehicle
	char vehicleuid[128];
	sprintf(vehicleuid, "%s%i", vehicle.c_str(), m_vuid);
	m_vuid++;
	vehicleentity->Init(vehicleuid, chassismodelpath, leftfrontwheelmodelpath, rightfrontwheelmodelpath, leftrearwheelmodelpath, rightrearwheelmodelpath, texture, car);

	//Set Direction
	mat4::MATRIX4 mat1 = vehicleentity->GetCarInfo()->GetChassisMatrix();
	const vec3::Vector3 nup = vec3::Vector3(0,1,0);
	const vec3::Vector3 c = vec3::I_Normalize(vec3::CrossProduct(nup, direction));
	const vec3::Vector3 rup = vec3::CrossProduct(direction, c);
	mat1._11 = c.x;
	mat1._12 = c.y;
	mat1._13 = c.z;
	mat1._21 = rup.x;
	mat1._22 = rup.y;
	mat1._23 = rup.z;
	mat1._31 = direction.x;
	mat1._32 = direction.y;
	mat1._33 = direction.z;
	vehicleentity->GetCarInfo()->SetChassisMatrix(&mat1);

	//Add entity to vehicles list
	m_vehicles.push_back(vehicleentity);
	m_vehiclecount = m_vehicles.size();
	return m_vehicles.size()-1;
}

//Delete all vehicles
void VehicleController::RemoveAllVehicles()
{
	for(std::vector<VehicleEntity*>::iterator iter = m_vehicles.begin(); iter != m_vehicles.end(); ++iter)
		delete (*iter);

	m_vehicles.clear();
	m_vehiclecount = 0;
}

//Fire a ray and return which vehicle it hit
void VehicleController::RayCastForVehicles(vec3::Vector3 from, vec3::Vector3 to, pVEHICLE* vehicleout, float* distout)
{
	float distance = 0.f;
	const btRigidBody* body = BulletPhysics().ClosestRayCast(from, to, &distance);

	const long totalvehicles = m_vehiclecount;
	for(int i = 0; i < totalvehicles; ++i)
	{
		if(m_vehicles[i]->GetCarInfo()->GetRigidBody() == body)
		{
			*distout = distance;
			*vehicleout = i;
			return;
		}
	}

	*distout = 0.f;
	*vehicleout = RAY_HITNULL;
}

//Fire a ray and return distance for boundaries
void VehicleController::RayCastForBoundaries(vec3::Vector3 from, vec3::Vector3 to, float* distout)
{
	float distance = 0.f;
	const btRigidBody* body = BulletPhysics().ClosestRayCast(from, to, &distance);

	const long totalvehicles = m_vehiclecount;
	for(int i = 0; i < totalvehicles; ++i)
	{
		if(m_vehicles[i]->GetCarInfo()->GetRigidBody() == BulletPhysics().GetInvisGroundShapeRigidBody())
		{
			*distout = distance;
			return;
		}
	}

	*distout = 0.f;
}





