/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef BULLETPHYSICS_H
#define BULLETPHYSICS_H

#include "precom.h"

#include "ContentManager.h"
#include "GlobalMacros.h"
#include "Vector3.h"
#include "MatrixLib.h"
#include "Quaternion.h"
#include "Bezier.h"

class BulletPhysics;


/* 
	###########################################################
					General Utility Functions
	########################################################### 
*/

//Matrix Conversion
//void btConvertMatrix(mat4::MATRIX4* m, const btTransform* transform);
mat4::MATRIX4 btConvertMatrix(const btTransform* transform);
btTransform XConvertMatrix(mat4::MATRIX4* matrix);
mat4::MATRIX4 XConvertBulletTransform(const btTransform* bulletTransformMatrix);


/* 
	###########################################################
				Physics Prop/Shape Classes / Functions
	########################################################### 
*/

//Define for Physics Shape ID
#define pBTSHAPE int

//Physics Shape
struct PhysicsShape
{
	btRigidBody* m_rigidbody;
	mat4::MATRIX4 GetWorldTransform();
};

MP_INLINE mat4::MATRIX4 PhysicsShape::GetWorldTransform()
{
	btTransform t;
	m_rigidbody->getMotionState()->getWorldTransform(t);
	return btConvertMatrix(&t);
}


/* 
	###########################################################
					Vehicle Functions / Classes
	########################################################### 
*/

//Define for car ID
#define pBTCAR int

//Wheel Drive
#define DRIVE_FRONTWHEEL 0
#define DRIVE_REARWHEEL 1
#define DRIVE_FOURWHEEL 2

//Car Raycast Result
struct CarRaycastResult
{
	float distFraction;
	vec3::Vector3 worldNormal;
	vec3::Vector3 worldPoint;
};

//Car Info
class CarInfo
{
public:

	//BulletPhysics class can access private data
	friend BulletPhysics;

	//Constructor
	CarInfo() : m_vehicle(NULL), m_startOrigin(0,0,0), m_VehicleSteering(0.f),
	m_EngineForce(0.f), m_BreakingForce(0.f), m_accelerationForce(0.f) {}

	//Update Handelling
	void UpdateHandelling();

	//Update Tuning
	void UpdateTuning();

	//Freeze Vehicle Motion
	void FreezeMotion();

	//UnFreeze Vehicle Motion
	void UnFreezeMotion();

	//Set Acceleration Force
	void SetAccelerationForce(float force);

	//Set Chassis Matrix
	void SetChassisMatrix(mat4::MATRIX4* matrix);

	//Get Chassis Matrix
	mat4::MATRIX4 GetChassisMatrix() const;

	//Get Camera Matrix
	mat4::MATRIX4 GetCameraMatrix() const;

	//Get Wheel Matrix
	mat4::MATRIX4 GetWheelMatrix(int wheelindex) const;

	//Get Position
	vec3::Vector3 GetPosition() const;

	//Get Camera Position
	vec3::Vector3 GetCameraPosition() const;

	//Get Orientation
	quat::Quaternion GetOrientation() const;

	//Get Speed (KPH)
	float GetSpeed() const;

	//Cast Ray
	CarRaycastResult CastRay(vec3::Vector3 from, vec3::Vector3 to) const;

	//return pointer to rigid body
	btRigidBody* GetRigidBody();

	//Current Steering, Engine and Breaking Value
	float m_VehicleSteering;
	float m_EngineForce;
	float m_BreakingForce;

	/*
		When adding a new car, you need to fill in all the
		below information before passing the struct to
		CreateVehicle()
	*/

	//ContentManager Model ID for Chassis Collision Model
	pMODEL m_chassisModel;
	float m_chassisScale;

	//Recip for faster calculations
	float m_maxEngineForceRecip;
	float m_maxBreakingForceRecip;

	//Vehicle Tuning Details
	float m_suspensionStiffness;
	float m_suspensionRelaxation;
	float m_suspensionCompression;
	float m_wheelFriction;
	float m_frontWheelRadius;
	float m_backWheelRadius;
	float m_maxSteering;
	float m_rollInfluence;
	float m_chassisMass;
	float m_maxSpeedKPH;
	float m_maxEngineForce;
	float m_maxBreakingForce;
	float m_maxSuspensionForce;
	float m_maxSuspensionTravelCm;
	float m_suspensionRestLength;
	float m_skidForce;
	float m_accelerationForce;
	CubicBezier1D m_accelerationFalloff;
	float m_maxSpeedKPHRecip;
	float m_frictionSlip;
	int m_wheelDrive;
	vec3::Vector3 m_wheelPosition[4];
	vec3::Vector3 m_startOrigin;

private:

	//Spring for camera
	btGeneric6DofSpringConstraint* m_cameraSpring;

	//Rigid body for camera position/collision
	btRigidBody* m_cameraBody;

	//Chassis Rigid Body
	btRigidBody* m_carChassis;

	//Chassis Shape
	btConvexHullShape* m_chassisShape;

	//Simplified convex hull
	btShapeHull* m_chassisHull;
	
	//Vehicle Raycaster
	btVehicleRaycaster* m_vehicleRayCaster;

	//Vehicle
	btRaycastVehicle* m_vehicle;

	//Wheel Tuning
	btRaycastVehicle::btVehicleTuning m_tuning;

};

MP_INLINE void CarInfo::UpdateHandelling()
{
	m_vehicle->setSteeringValue(m_VehicleSteering, 0);
	m_vehicle->setSteeringValue(m_VehicleSteering, 1);

	if(m_wheelDrive == DRIVE_FRONTWHEEL)
	{
		m_vehicle->applyEngineForce(m_EngineForce, 0);
		m_vehicle->applyEngineForce(m_EngineForce, 1);

		m_vehicle->setBrake(m_BreakingForce, 3);
		m_vehicle->setBrake(m_BreakingForce, 2);
	}
	else if(m_wheelDrive == DRIVE_REARWHEEL)
	{
		m_vehicle->applyEngineForce(m_EngineForce, 2);
		m_vehicle->applyEngineForce(m_EngineForce, 3);

		m_vehicle->setBrake(m_BreakingForce, 3);
		m_vehicle->setBrake(m_BreakingForce, 2);
	}
	else if(m_wheelDrive == DRIVE_FOURWHEEL)
	{
		m_vehicle->applyEngineForce(m_EngineForce, 0);
		m_vehicle->applyEngineForce(m_EngineForce, 1);
		m_vehicle->applyEngineForce(m_EngineForce, 2);
		m_vehicle->applyEngineForce(m_EngineForce, 3);

		m_vehicle->setBrake(m_BreakingForce, 2);
		m_vehicle->setBrake(m_BreakingForce, 3);
	}
}

MP_INLINE mat4::MATRIX4 CarInfo::GetChassisMatrix() const
{
	btTransform t;
	m_carChassis->getMotionState()->getWorldTransform(t);
	return btConvertMatrix(&t);
}

MP_INLINE mat4::MATRIX4 CarInfo::GetCameraMatrix() const
{
	btTransform t;
	m_cameraBody->getMotionState()->getWorldTransform(t);
	return btConvertMatrix(&t);
}

MP_INLINE mat4::MATRIX4 CarInfo::GetWheelMatrix(int wheelindex) const
{
	m_vehicle->updateWheelTransform(wheelindex, true);
	const btTransform t = m_vehicle->getWheelTransformWS(wheelindex);
	return btConvertMatrix(&t);
}

MP_INLINE float CarInfo::GetSpeed() const
{
	return m_vehicle->getCurrentSpeedKmHour();
}

MP_INLINE void CarInfo::SetChassisMatrix(mat4::MATRIX4* matrix)
{
	m_carChassis->setWorldTransform(XConvertMatrix(matrix));
}

MP_INLINE void CarInfo::FreezeMotion()
{
	m_carChassis->setLinearFactor(btVector3(0,0,0));
	m_carChassis->setAngularFactor(btVector3(0,0,0));
}

MP_INLINE void CarInfo::UnFreezeMotion()
{
	m_carChassis->setLinearFactor(btVector3(1,1,1));
	m_carChassis->setAngularFactor(btVector3(1,1,1));
}

MP_INLINE void CarInfo::SetAccelerationForce(float force)
{
	const float accelerationforce = force * m_accelerationFalloff.GetBezierPoint(m_vehicle->getCurrentSpeedKmHour() * m_maxSpeedKPHRecip);

	if(m_wheelDrive == DRIVE_FRONTWHEEL)
	{
		m_vehicle->getWheelInfo(0).m_engineForce = accelerationforce;
		m_vehicle->getWheelInfo(1).m_engineForce = accelerationforce;
	}
	else if(m_wheelDrive == DRIVE_REARWHEEL)
	{
		m_vehicle->getWheelInfo(2).m_engineForce = accelerationforce;
		m_vehicle->getWheelInfo(3).m_engineForce = accelerationforce;
	}
	else if(m_wheelDrive == DRIVE_FOURWHEEL)
	{
		m_vehicle->getWheelInfo(0).m_engineForce = accelerationforce;
		m_vehicle->getWheelInfo(1).m_engineForce = accelerationforce;
		m_vehicle->getWheelInfo(2).m_engineForce = accelerationforce;
		m_vehicle->getWheelInfo(3).m_engineForce = accelerationforce;
	}
}

MP_INLINE CarRaycastResult CarInfo::CastRay(vec3::Vector3 from, vec3::Vector3 to) const
{
	btVehicleRaycaster::btVehicleRaycasterResult r;
	m_vehicleRayCaster->castRay(btVector3(from.x, from.y, from.z), btVector3(to.x, to.y, to.z), r);

	CarRaycastResult ret;
	ret.distFraction = r.m_distFraction;
	ret.worldNormal = vec3::Vector3(r.m_hitNormalInWorld.getX(), r.m_hitNormalInWorld.getY(), r.m_hitNormalInWorld.getZ());
	ret.worldPoint = vec3::Vector3(r.m_hitPointInWorld.getX(), r.m_hitPointInWorld.getY(), r.m_hitPointInWorld.getZ());
	return ret;
}

MP_INLINE vec3::Vector3 CarInfo::GetPosition() const
{
	return vec3::Vector3(m_vehicle->getChassisWorldTransform().getOrigin().getX(),
						 m_vehicle->getChassisWorldTransform().getOrigin().getY(),
						 m_vehicle->getChassisWorldTransform().getOrigin().getZ());
}

MP_INLINE vec3::Vector3 CarInfo::GetCameraPosition() const
{
	return vec3::Vector3(m_cameraBody->getWorldTransform().getOrigin().getX(),
						 m_cameraBody->getWorldTransform().getOrigin().getY(),
						 m_cameraBody->getWorldTransform().getOrigin().getZ());
}

MP_INLINE quat::Quaternion CarInfo::GetOrientation() const
{
	quat::Quaternion n;
	n.v.x = m_carChassis->getOrientation().getX();
	n.v.y = m_carChassis->getOrientation().getY();
	n.v.z = m_carChassis->getOrientation().getZ();
	n.w = m_carChassis->getOrientation().getW();
	return n;
}

MP_INLINE btRigidBody* CarInfo::GetRigidBody()
{
	return m_carChassis;
}


/* 
	###########################################################
				Bullet Physics Black Box Singleton
	########################################################### 
*/

//Bullet Physics Class
class BulletPhysics
{
public:
	
	//Singleton Instance
	static BulletPhysics& Inst()
	{
		static BulletPhysics singleton;
		return singleton;
	}
	~BulletPhysics(); //Destructor


	/* ###################################
		General Bullet Physics Functions
	 ################################### */

	//Step Bullet Physics
	void Update(float dt);

	//Init Bullet Physics
	void Init(vec3::Vector3 worldMin, vec3::Vector3 worldMax, float gravity);

	//Fire Raycast and return RigidBody pointer
	btRigidBody* ClosestRayCast(vec3::Vector3 ifrom, vec3::Vector3 ito, float* distout);


	/* ###################################
		          For Terrain
	 ################################### */

	//Init Terrain
	void CreateTerrain(vec3::Vector3 origin, pMODEL vismodel, pMODEL invismodel);

	//Destroy Terrain
	void DestroyTerrain();

	//Get Terrain Matrix
	mat4::MATRIX4 GetTerrainTransform();

	//Get Invis Ground Shape Rigid Body
	btRigidBody* GetInvisGroundShapeRigidBody();


	/* ###################################
		       For Vehicle Objects
	 ################################### */

	//Add a vehicle to dynamics world and return id
	pBTCAR CreateVehicle(CarInfo new_car);

	//Deletes a vehicle
	void DestroyVehicle(const int id);

	//Resets a vehicle
	void ResetVehicle(const int id, vec3::Vector3 pos);

	//Car Array Accessors
	CarInfo* GetCar(pBTCAR id);


	/* ###################################
	For Physics Objects, barrels, crates etc
	 ################################### */

	//Add a physics box
	pBTSHAPE AddBox(vec3::Vector3 origin, float mass, vec3::Vector3 box);

	//Add a physics cylinder
	pBTSHAPE AddCylinder(vec3::Vector3 origin, float mass, float width, float radius1, float radius2);

	//Add a physics sphere
	pBTSHAPE AddSphere(vec3::Vector3 origin, float mass, float radius);

	//Add a physics model
	//int AddModel(vec3::Vector3 origin, float mass, pMODEL model);

	//Add a physics model using Convex Hull
	pBTSHAPE AddModelConvex(vec3::Vector3 origin, float mass, pMODEL model);

	//Delete a Shape
	void RemoveShape(const int id);

	//Shapes Array Accessors
	PhysicsShape* GetShape(pBTSHAPE id);


private:
	
	BulletPhysics(){}; //Constructor
	BulletPhysics(const BulletPhysics&); //Prevent Copy
	BulletPhysics& operator=(const BulletPhysics&); //Prevent Assignment

	//Array of Physics Shapes
	std::vector<PhysicsShape*> m_shapes;
	std::vector<int> m_shapedeleteflags;

	//Array of Cars
	std::vector<CarInfo*> m_cars;
	std::vector<int> m_cardeleteflags;

	//Reset vehicle
	void ResetVehicle(CarInfo* ci);

	//Create a rigid body
	btRigidBody* localCreateRigidBody(float mass, btTransform& startTransform, btCollisionShape* shape);

	//Dynamics World
	btDynamicsWorld* m_dynamicsWorld;

	//Collision Shapes Array
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	//Detect aabb overlapping
	btBroadphaseInterface* m_overlappingPairCache;

	//Handle ConvexConvex and ConvexConcave collisions
	btCollisionDispatcher* m_dispatcher;

	//Provides a constraint solver interface
	btConstraintSolver*	m_constraintSolver;

	//Configure collisions
	btDefaultCollisionConfiguration* m_collisionConfiguration;

	//Index & Vertex array for visible terrain
	btTriangleIndexVertexArray*	m_invisIndexVertexArrays;

	//Index & Vertex array for invisible terrain
	btTriangleIndexVertexArray*	m_visIndexVertexArrays;

	//Ground Collision Shape for terrain
	btCollisionShape* m_visGroundShape;
	btCollisionShape* m_invisGroundShape;

	//Terrain rigid body
	btRigidBody* m_visTerrainrigidbody;
	btRigidBody* m_invisTerrainrigidbody;

	//Terrain Model Info
	ModelInfo* m_visterraininfo;
	ModelInfo* m_invisterraininfo;

};

MP_INLINE btRigidBody* BulletPhysics::GetInvisGroundShapeRigidBody()
{
	return m_invisTerrainrigidbody;
}

MP_INLINE mat4::MATRIX4 BulletPhysics::GetTerrainTransform()
{
	btTransform t;
	m_visTerrainrigidbody->getMotionState()->getWorldTransform(t);
	return btConvertMatrix(&t);
}

MP_INLINE CarInfo* BulletPhysics::GetCar(int id)
{
	return m_cars[id];
}

MP_INLINE PhysicsShape* BulletPhysics::GetShape(int id)
{
	return m_shapes[id];
}

MP_INLINE void BulletPhysics::Update(float dt)
{
	m_dynamicsWorld->stepSimulation(0.01666666f, 0);
}

//Return Instance to Bullet Physics Singleton
MP_INLINE BulletPhysics& BulletPhysics(){return BulletPhysics::Inst();}

#endif




