/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	All this is just from looking at what
	was done in the Bullet Vehicle Demo.
*/

#include "precom.h"
#include "BulletPhysics.h"
#include "Vector3.h"
using namespace vec3;


//Destructor
BulletPhysics::~BulletPhysics()
{
	//remove the rigidbodies from the dynamics world and delete them
	for(int i = m_dynamicsWorld->getNumCollisionObjects()-1; i >= 0; --i)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if(body && body->getMotionState())
			delete body->getMotionState();

		m_dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for(int j = 0; j < m_collisionShapes.size(); j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}

	//delete vehicles
	for(std::vector<CarInfo*>::iterator iter = m_cars.begin(); iter != m_cars.end(); ++iter)
			delete (*iter);

	//delete shapes
	for(std::vector<PhysicsShape*>::iterator iter = m_shapes.begin(); iter != m_shapes.end(); ++iter)
			delete (*iter);

	//delete dynamics world
	delete m_dynamicsWorld;

	//delete solver
	delete m_constraintSolver;

	//delete broadphase
	delete m_overlappingPairCache;

	//delete dispatcher
	delete m_dispatcher;

	//delete collision configuration
	delete m_collisionConfiguration;
}

//Init Bullet Physics
void BulletPhysics::Init(Vector3 worldMin, Vector3 worldMax, float gravity)
{
	//Use defualt collision configuration
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	//Create collision dispatcher
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	//Create overlapping pair cache (use broadphase?)
	m_overlappingPairCache = new btAxisSweep3(btVector3(worldMin.x, worldMin.y, worldMin.z),
											  btVector3(worldMax.x, worldMax.y, worldMax.z));

	//Use Sequential Impulse Constraint Solver
	m_constraintSolver = new btSequentialImpulseConstraintSolver();

	//Create Dynamics World
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,
												  m_overlappingPairCache,
												  m_constraintSolver,
												  m_collisionConfiguration);

	//Register Collision Dispatcher with GImpact
	btCollisionDispatcher* dispatcher = static_cast<btCollisionDispatcher*>(m_dynamicsWorld->getDispatcher());
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

	//Set Gravity
	m_dynamicsWorld->setGravity(btVector3(0, gravity, 0));
}

//Init Collision Terrain
void BulletPhysics::CreateTerrain(Vector3 origin, pMODEL vismodel, pMODEL invismodel)
{
	//Standard Strides
	const int vertStride = sizeof(Vector3);
	const int indexStride = 3*sizeof(int);
	const bool useQuantizedAabbCompression = false;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));

	////////////////////////////////////////////////////////////

	//Load Model Info from Content Manager
	m_visterraininfo = new ModelInfo;
	ContentManager().GetXModelInfo(vismodel, m_visterraininfo);

	//Create Triangle Index/Vertex Array
	m_visIndexVertexArrays = new btTriangleIndexVertexArray(m_visterraininfo->NumTriangles,
															m_visterraininfo->IndexBuff,
															indexStride,
															m_visterraininfo->NumVerts,
															(btScalar*)&m_visterraininfo->VertBuff[0],
															vertStride);

	//Create Collision Shape
	m_visGroundShape = new btBvhTriangleMeshShape(m_visIndexVertexArrays, useQuantizedAabbCompression);

	//Create Rigid Body
	m_visTerrainrigidbody = localCreateRigidBody(0, tr, m_visGroundShape);

	////////////////////////////////////////////////////////////

	//Load Model Info from Content Manager
	m_invisterraininfo = new ModelInfo;
	ContentManager().GetXModelInfo(invismodel, m_invisterraininfo);

	//Create Triangle Index/Vertex Array
	m_invisIndexVertexArrays = new btTriangleIndexVertexArray(m_invisterraininfo->NumTriangles,
															m_invisterraininfo->IndexBuff,
															indexStride,
															m_invisterraininfo->NumVerts,
															(btScalar*)&m_invisterraininfo->VertBuff[0],
															vertStride);

	//Create Collision Shape
	m_invisGroundShape = new btBvhTriangleMeshShape(m_invisIndexVertexArrays, useQuantizedAabbCompression);

	//Create Rigid Body
	m_invisTerrainrigidbody = localCreateRigidBody(0, tr, m_invisGroundShape);
}

//Cleanup Terrain
void BulletPhysics::DestroyTerrain()
{
	//Delete Terrain Info
	if(m_visterraininfo != NULL)
		delete m_visterraininfo;

	if(m_invisterraininfo != NULL)
		delete m_invisterraininfo;

	//Delete Index/Vertex Array
	if(m_visIndexVertexArrays != NULL)
		delete m_visIndexVertexArrays;

	if(m_invisIndexVertexArrays != NULL)
		delete m_invisIndexVertexArrays;

	//Delete Rigid Body
	m_dynamicsWorld->removeRigidBody(m_visTerrainrigidbody);
	m_dynamicsWorld->removeRigidBody(m_invisTerrainrigidbody);

	//Delete ground collision shape
	if(m_visGroundShape != NULL)
		delete m_visGroundShape;

	if(m_invisGroundShape != NULL)
		delete m_invisGroundShape;
}

//Add's a new physics box
int BulletPhysics::AddBox(Vector3 origin, float mass, Vector3 box)
{
	//Create new physics shape struct
	PhysicsShape* new_shape = new PhysicsShape;

	//Create Collision Shape
	const bool useQuantizedAabbCompression = true;
	btCollisionShape* shape = new btBoxShape(btVector3(box.x, box.y, box.z));
	m_collisionShapes.push_back(shape);

	//Create Rigid Body
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));
	new_shape->m_rigidbody = localCreateRigidBody(mass, tr, shape);

	//Add to m_shapes and return array pos (id)
	int cid = 0;

	if(m_shapedeleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_shapedeleteflags.begin();
        m_shapedeleteflags.erase(m_shapedeleteflags.begin());
		std::vector<PhysicsShape*>::iterator iter = m_shapes.begin()+cid;
		delete (*iter);
        m_shapes.erase(iter);
		m_shapes.insert(iter, new_shape);
	}
	else
	{
		//If not, add a new slot
		cid = m_shapes.size();
		m_shapes.push_back(new_shape);
	}

	return cid;
}

//Add's a new physics model using Convex Hull
int BulletPhysics::AddModelConvex(Vector3 origin, float mass, pMODEL model)
{
	//Create new physics shape struct
	PhysicsShape* new_shape = new PhysicsShape;

	//Standard Stride
	const int vertStride = sizeof(Vector3);

	//Load Model Info from Content Manager
	ModelInfo modelinfo;
	ContentManager().GetXModelInfo(model, &modelinfo);

	//Create Convex Hull Collision Shape
	const bool useQuantizedAabbCompression = false;
	btConvexHullShape* shape = new btConvexHullShape((btScalar*)&modelinfo.VertBuff[0], modelinfo.NumVerts, vertStride);

	//Create simplified hull
	btShapeHull* hullshape = new btShapeHull(shape);
	btScalar margin = shape->getMargin();
	hullshape->buildHull(margin);
	btConvexHullShape* simplesshape = new btConvexHullShape((btScalar*)hullshape->getVertexPointer(), hullshape->numVertices());
	m_collisionShapes.push_back(simplesshape);

	//Delete original hull
	delete shape;

	//Create Rigid Body
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));
	new_shape->m_rigidbody = localCreateRigidBody(mass, tr, simplesshape);

	//Add to m_shapes and return array pos (id)
	int cid = 0;

	if(m_shapedeleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_shapedeleteflags.begin();
        m_shapedeleteflags.erase(m_shapedeleteflags.begin());
		std::vector<PhysicsShape*>::iterator iter = m_shapes.begin()+cid;
		delete (*iter);
        m_shapes.erase(iter);
		m_shapes.insert(iter, new_shape);
	}
	else
	{
		//If not, add a new slot
		cid = m_shapes.size();
		m_shapes.push_back(new_shape);
	}

	return cid;
}

//Add's a new physics cylinder
int BulletPhysics::AddCylinder(Vector3 origin, float mass, float width, float radius1, float radius2)
{
	//Create new physics shape struct
	PhysicsShape* new_shape = new PhysicsShape;

	//Create Collision Shape
	const bool useQuantizedAabbCompression = true;
	btCollisionShape* shape = new btCylinderShapeX(btVector3(width, radius1, radius2));
	m_collisionShapes.push_back(shape);

	//Create Rigid Body
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));
	new_shape->m_rigidbody = localCreateRigidBody(mass, tr, shape);

	//Add to m_shapes and return array pos (id)
	int cid = 0;

	if(m_shapedeleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_shapedeleteflags.begin();
        m_shapedeleteflags.erase(m_shapedeleteflags.begin());
		std::vector<PhysicsShape*>::iterator iter = m_shapes.begin()+cid;
		delete (*iter);
        m_shapes.erase(iter);
		m_shapes.insert(iter, new_shape);
	}
	else
	{
		//If not, add a new slot
		cid = m_shapes.size();
		m_shapes.push_back(new_shape);
	}

	return cid;
}

//Add's a new physics sphere
int BulletPhysics::AddSphere(Vector3 origin, float mass, float radius)
{
	//Create new physics shape struct
	PhysicsShape* new_shape = new PhysicsShape;

	//Create Collision Shape
	const bool useQuantizedAabbCompression = true;
	btCollisionShape* shape = new btSphereShape(btScalar(radius));
	m_collisionShapes.push_back(shape);

	//Create Rigid Body
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));
	new_shape->m_rigidbody = localCreateRigidBody(mass, tr, shape);

	//Add to m_shapes and return array pos (id)
	int cid = 0;

	if(m_shapedeleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_shapedeleteflags.begin();
        m_shapedeleteflags.erase(m_shapedeleteflags.begin());
		std::vector<PhysicsShape*>::iterator iter = m_shapes.begin()+cid;
		delete (*iter);
        m_shapes.erase(iter);
		m_shapes.insert(iter, new_shape);
	}
	else
	{
		//If not, add a new slot
		cid = m_shapes.size();
		m_shapes.push_back(new_shape);
	}

	return cid;
}

//Delete a Shape
void BulletPhysics::RemoveShape(const int id)
{
	//Delete Rigid Body
	m_dynamicsWorld->removeRigidBody(m_shapes[id]->m_rigidbody);
    delete m_shapes[id]->m_rigidbody->getMotionState();
    delete m_shapes[id]->m_rigidbody;

	//Delete Shape
	delete m_shapes[id];

	//Add deleted flag
	m_shapedeleteflags.push_back(id);
}

//Add a vehicle to dynamics world
int BulletPhysics::CreateVehicle(CarInfo inew_car)
{
	//Create car info
	CarInfo* new_car = new CarInfo;
	memcpy(new_car, &inew_car, sizeof(CarInfo));
	
	//Standard Strides
	const int vertStride = sizeof(Vector3);

	//Standard Coordinate space
	const int rightIndex = 0;
	const int upIndex = 1;
	const int forwardIndex = 2;
	const btVector3 wheelDirectionCS0(0,-1,0);
	const btVector3 wheelAxleCS(-1,0,0);

	//Load Collision Chassis ModelInfo from Content Manager
	ModelInfo mi;
	ContentManager().GetXModelInfo(new_car->m_chassisModel, &mi);

	//Create collision shape from Triangle Index/Vertex Array
	const bool useQuantizedAabbCompression = true;
	btConvexHullShape* chassisshape = new btConvexHullShape((btScalar*)&mi.VertBuff[0], mi.NumVerts, vertStride);

	//Create simplified hull
	new_car->m_chassisHull = new btShapeHull(chassisshape);
	btScalar margin = chassisshape->getMargin();
	new_car->m_chassisHull->buildHull(margin);
	new_car->m_chassisShape = new btConvexHullShape((btScalar*)new_car->m_chassisHull->getVertexPointer(), new_car->m_chassisHull->numVertices());
	m_collisionShapes.push_back(new_car->m_chassisShape);

	//Delete original hull
	delete chassisshape;

	//Create chassis compound shape
	btCompoundShape* compound = new btCompoundShape();
	m_collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 1, 0)); //Shifts the center of mass with respect to the chassis

	//Create chassis Rigid Body
	compound->addChildShape(localTrans, new_car->m_chassisShape);
	localTrans.setOrigin(btVector3(new_car->m_startOrigin.x, new_car->m_startOrigin.y, new_car->m_startOrigin.z));
	new_car->m_carChassis = localCreateRigidBody(new_car->m_chassisMass, localTrans, compound);

	//Create vehicle Ray Caster for terrain collision
	new_car->m_vehicleRayCaster = new btDefaultVehicleRaycaster(m_dynamicsWorld);

	//Create vehicle
	new_car->m_vehicle = new btRaycastVehicle(new_car->m_tuning, new_car->m_carChassis, new_car->m_vehicleRayCaster);
	
	//Never allow vehicle deactivation
	new_car->m_carChassis->setActivationState(DISABLE_DEACTIVATION);

	//Add vehicle to dynamics world
	m_dynamicsWorld->addVehicle(new_car->m_vehicle);

	//Setup coordinate system
	new_car->m_vehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

	//Add Front Wheels to vehicle
	btVector3 connectionPointCS0(new_car->m_wheelPosition[0].x,
								 new_car->m_wheelPosition[0].y,
								 new_car->m_wheelPosition[0].z);

	new_car->m_vehicle->addWheel(connectionPointCS0,
								wheelDirectionCS0,
								wheelAxleCS,
								new_car->m_suspensionRestLength,
								new_car->m_frontWheelRadius,
								new_car->m_tuning,
								true);


	connectionPointCS0 = btVector3(new_car->m_wheelPosition[1].x,
								   new_car->m_wheelPosition[1].y,
								   new_car->m_wheelPosition[1].z);

	new_car->m_vehicle->addWheel(connectionPointCS0,
								wheelDirectionCS0,
								wheelAxleCS,
								new_car->m_suspensionRestLength,
								new_car->m_frontWheelRadius,
								new_car->m_tuning,
								true);

	//Add Rear Wheels to vehicle
	connectionPointCS0 = btVector3(new_car->m_wheelPosition[2].x,
								   new_car->m_wheelPosition[2].y,
								   new_car->m_wheelPosition[2].z);

	new_car->m_vehicle->addWheel(connectionPointCS0,
								wheelDirectionCS0,
								wheelAxleCS,
								new_car->m_suspensionRestLength,
								new_car->m_backWheelRadius,
								new_car->m_tuning,
								false);

	
	connectionPointCS0 = btVector3(new_car->m_wheelPosition[3].x,
								   new_car->m_wheelPosition[3].y,
								   new_car->m_wheelPosition[3].z);

	new_car->m_vehicle->addWheel(connectionPointCS0,
								wheelDirectionCS0,
								wheelAxleCS,
								new_car->m_suspensionRestLength,
								new_car->m_backWheelRadius,
								new_car->m_tuning,
								false);
	
	//Set wheel's infos
	for(int i = 0; i < new_car->m_vehicle->getNumWheels(); i++)
	{
		btWheelInfo& wheel = new_car->m_vehicle->getWheelInfo(i);
		wheel.m_suspensionStiffness = new_car->m_suspensionStiffness;
		wheel.m_wheelsDampingRelaxation = new_car->m_suspensionRelaxation;
		wheel.m_wheelsDampingCompression = new_car->m_suspensionCompression;
		wheel.m_frictionSlip = new_car->m_wheelFriction;
		wheel.m_rollInfluence = new_car->m_rollInfluence;
		wheel.m_maxSuspensionForce = new_car->m_maxSuspensionForce;
		wheel.m_maxSuspensionTravelCm = new_car->m_maxSuspensionTravelCm;
		wheel.m_frictionSlip = new_car->m_frictionSlip;
		wheel.m_skidInfo = new_car->m_skidForce;
	}

	//Reset Vehicle
	ResetVehicle(new_car);

	//Add new_car to array of cars and return array pos (id)
	int cid = 0;

	if(m_cardeleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_cardeleteflags.begin();
        m_cardeleteflags.erase(m_cardeleteflags.begin());
		std::vector<CarInfo*>::iterator iter = m_cars.begin()+cid;
		delete (*iter);
        m_cars.erase(iter);
		m_cars.insert(iter, new_car);
	}
	else
	{
		//If not, add a new slot
		cid = m_cars.size();
		m_cars.push_back(new_car);
	}

	return cid;
}

//Update Vehicle Handelling
void CarInfo::UpdateTuning()
{
	for(int i = 0; i < m_vehicle->getNumWheels(); i++)
	{
		btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
		wheel.m_suspensionStiffness = m_suspensionStiffness;
		wheel.m_wheelsDampingRelaxation = m_suspensionRelaxation;
		wheel.m_wheelsDampingCompression = m_suspensionCompression;
		wheel.m_frictionSlip = m_wheelFriction;
		wheel.m_rollInfluence = m_rollInfluence;
		wheel.m_maxSuspensionForce = m_maxSuspensionForce;
		wheel.m_maxSuspensionTravelCm = m_maxSuspensionTravelCm;
		wheel.m_frictionSlip = m_frictionSlip;
		wheel.m_skidInfo = m_skidForce;
	}
}

//Delete Vehicle
void BulletPhysics::DestroyVehicle(const int id)
{
	//Remove Rigid Body
	m_dynamicsWorld->removeRigidBody(m_cars[id]->m_carChassis);
    delete m_cars[id]->m_carChassis->getMotionState();
    delete m_cars[id]->m_carChassis;
	
	//Delete car
	delete m_cars[id];

	//Add deleted flag
	m_cardeleteflags.push_back(id);
}

//Resets Vehicle
void BulletPhysics::ResetVehicle(CarInfo* ci)
{
	ci->m_carChassis->setLinearVelocity(btVector3(0,0,0));
	ci->m_carChassis->setAngularVelocity(btVector3(0,0,0));
	m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(ci->m_carChassis->getBroadphaseHandle(), m_dynamicsWorld->getDispatcher());
	
	if(ci->m_vehicle != NULL)
	{
		ci->m_vehicle->resetSuspension();

		for(int i = 0; i < ci->m_vehicle->getNumWheels(); ++i)
			ci->m_vehicle->updateWheelTransform(i, true);
	}
}

//Resets Vehicle
void BulletPhysics::ResetVehicle(const int id, vec3::Vector3 pos)
{
	m_cars[id]->m_VehicleSteering = 0.f;
	btTransform t;
	t.setOrigin(btVector3(pos.x, pos.y, pos.z));
	m_cars[id]->m_carChassis->setCenterOfMassTransform(t);
	m_cars[id]->m_carChassis->setLinearVelocity(btVector3(0,0,0));
	m_cars[id]->m_carChassis->setAngularVelocity(btVector3(0,0,0));
	m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(m_cars[id]->m_carChassis->getBroadphaseHandle(), m_dynamicsWorld->getDispatcher());
	
	if(m_cars[id]->m_vehicle != NULL)
	{
		m_cars[id]->m_vehicle->resetSuspension();

		for(int i = 0; i < m_cars[id]->m_vehicle->getNumWheels(); ++i)
			m_cars[id]->m_vehicle->updateWheelTransform(i, true);
	}
}

//Add's a new physics model
/*int BulletPhysics::AddModel(Vector3 origin, float mass, pMODEL model)
{
	//Create new physics shape struct
	PhysicsShape new_shape;

	//Standard Strides
	const int vertStride = sizeof(Vector3);
	const int indexStride = 3*sizeof(int);

	//Load Model Info from Content Manager
	ModelInfo* modelinfo = new ModelInfo; //TODO: Cleanup
	ContentManager().GetXModelInfo(model, modelinfo);

	//Create Triangle Index/Vertex Array TODO: Cleanup
	btTriangleIndexVertexArray* indexVertexArrays = new btTriangleIndexVertexArray(modelinfo->NumTriangles,
																				   modelinfo->IndexBuff,
																				   indexStride,
																				   modelinfo->NumVerts,
																				   (btScalar*)&modelinfo->VertBuff[0],
																				   vertStride);

	//Create Collision Shape
	const bool useQuantizedAabbCompression = false;
	btCollisionShape* shape = new btBvhTriangleMeshShape(indexVertexArrays, useQuantizedAabbCompression);
	m_collisionShapes.push_back(shape);

	//Create GImpactMeshShape
	btGImpactMeshShape* trimesh = new btGImpactMeshShape(indexVertexArrays); //TODO: Cleanup
	trimesh->setMargin(0.09f);
	trimesh->updateBound();
	shape = trimesh;

	//Create Rigid Body
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(origin.x, origin.y, origin.z));
	new_shape->m_rigidbody = localCreateRigidBody(mass, tr, shape);

	//Add to m_shapes and return array pos (id)
	const int ap = m_shapes.size();
	m_shapes.push_back(new_shape);
	return ap;
}*/

//Fire raycast and return rigidbody
btRigidBody* BulletPhysics::ClosestRayCast(vec3::Vector3 ifrom, vec3::Vector3 ito, float* distout)
{
	const btVector3 from(ifrom.x, ifrom.y, ifrom.z);
	const btVector3 to(ito.x, ito.y, ito.z);

	btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);
	m_dynamicsWorld->rayTest(from, to, rayCallback);

	if(rayCallback.hasHit() == true)
	{
		btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);
		
		if(body != NULL)
		{
			*distout = rayCallback.m_hitPointWorld.distance(rayCallback.m_rayFromWorld);
			return body;
		}
	}

	return NULL;
}

//Create Rigid Body
btRigidBody* BulletPhysics::localCreateRigidBody(float mass, btTransform& startTransform, btCollisionShape* shape)
{
	btVector3 localInertia(0,0,0);

	if(mass != 0.f) //is non static?
		shape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(cInfo);
	body->setContactProcessingThreshold(BT_LARGE_FLOAT); //
	m_dynamicsWorld->addRigidBody(body);
	return body;
}

//Convert btMatrix to mat4::MATRIX4
/*void btConvertMatrix(mat4::MATRIX4* m, const btTransform* transform)
{
	btTransform t = *transform;

	btMatrix3x3 bm = t.getBasis().transpose();
	btVector3 p[4];

	p[0] = bm.getRow(0);
	p[1] = bm.getRow(1);
	p[2] = bm.getRow(2);
	p[3] = t.getOrigin();

	m->_11 = p[0].getX(); m->_12 = p[0].getY(); m->_13 = p[0].getZ(); // X axis
	m->_21 = p[1].getX(); m->_22 = p[1].getY(); m->_23 = p[1].getZ(); // Y axis
	m->_31 = p[2].getX(); m->_32 = p[2].getY(); m->_33 = p[2].getZ(); // Z axis

	m->_41 = p[3].getX();
	m->_42 = p[3].getY();
	m->_43 = p[3].getZ();
}*/

//Convert btMatrix to mat4::MATRIX4
mat4::MATRIX4 btConvertMatrix(const btTransform* transform)
{
	mat4::MATRIX4 m;
	btTransform t = *transform;

	btMatrix3x3 bm = t.getBasis().transpose();
	btVector3 p[4];

	p[0] = bm.getRow(0);
	p[1] = bm.getRow(1);
	p[2] = bm.getRow(2);
	p[3] = t.getOrigin();

	m._11 = p[0].getX(); m._12 = p[0].getY(); m._13 = p[0].getZ(); // X axis
	m._21 = p[1].getX(); m._22 = p[1].getY(); m._23 = p[1].getZ(); // Y axis
	m._31 = p[2].getX(); m._32 = p[2].getY(); m._33 = p[2].getZ(); // Z axis

	m._41 = p[3].getX();
	m._42 = p[3].getY();
	m._43 = p[3].getZ();

	return m;
}

/*mat4::MATRIX4 btConvertMatrix(const btTransform* trn)
{
   btVector3 R = trn->getBasis().getColumn(0);
   btVector3 U = trn->getBasis().getColumn(1);
   btVector3 L = trn->getBasis().getColumn(2);
   btVector3 P = trn->getOrigin();

   vec3::Vector3 vR, vU, vL, vP;
   vR.x = R.x(); vR.y = R.y(); vR.z = R.z();
   vU.x = U.x(); vU.y = U.y(); vU.z = U.z();
   vL.x = L.x(); vL.y = L.y(); vL.z = L.z();
   vP.x = P.x(); vP.y = P.y(); vP.z = P.z();

   mat4::MATRIX4 matOutput;
   matOutput._11 = vR.x;matOutput._12 = vR.y;matOutput._13 = vR.z;matOutput._14 = 0.f;
   matOutput._21 = vU.x;matOutput._22 = vU.y;matOutput._23 = vU.z;matOutput._24 = 0.f;
   matOutput._31 = vL.x;matOutput._32 = vL.y;matOutput._33 = vL.z;matOutput._34 = 0.f;
   matOutput._41 = vP.x;matOutput._42 = vP.y;matOutput._43 = vP.z;matOutput._44 = 1.f;

   return matOutput;
}*/

void XPrepareMatrixFromRULP(mat4::MATRIX4& matOutput, vec3::Vector3* R, vec3::Vector3* U, vec3::Vector3* L, vec3::Vector3* P)
{
    matOutput._11 = R->x;matOutput._12 = R->y;matOutput._13 = R->z;matOutput._14 = 0.f;
    matOutput._21 = U->x;matOutput._22 = U->y;matOutput._23 = U->z;matOutput._24 = 0.f;
    matOutput._31 = L->x;matOutput._32 = L->y;matOutput._33 = L->z;matOutput._34 = 0.f;
    matOutput._41 = P->x;matOutput._42 = P->y;matOutput._43 = P->z;matOutput._44 = 1.f;
}

mat4::MATRIX4 XConvertBulletTransform(const btTransform* bulletTransformMatrix)
{
   mat4::MATRIX4 world;
   btVector3 R = bulletTransformMatrix->getBasis().getColumn(0);
   btVector3 U = bulletTransformMatrix->getBasis().getColumn(1);
   btVector3 L = bulletTransformMatrix->getBasis().getColumn(2);
   btVector3 P = bulletTransformMatrix->getOrigin();

   vec3::Vector3 vR, vU, vL, vP;
   vR.x = R.x();vR.y = R.y();vR.z = R.z();
   vU.x = U.x();vU.y = U.y();vU.z = U.z();
   vL.x = L.x();vL.y = L.y();vL.z = L.z();
   vP.x = P.x();vP.y = P.y();vP.z = P.z();

   XPrepareMatrixFromRULP(world, &vR, &vU, &vL, &vP);
   return world;
}

btTransform XConvertMatrix(mat4::MATRIX4* matrix)
{
   btTransform bulletTransformMatrix;
   btVector3 R,U,L,P;
   R.setX(matrix->_11); R.setY(matrix->_12); R.setZ(matrix->_13);
   U.setX(matrix->_21); U.setY(matrix->_22); U.setZ(matrix->_23);
   L.setX(matrix->_31); L.setY(matrix->_32); L.setZ(matrix->_33);
   P.setX(matrix->_41); P.setY(matrix->_42); P.setZ(matrix->_43);

   bulletTransformMatrix.getBasis().setValue( R.x(), U.x(), L.x(),
											  R.y(), U.y(), L.y(),
											  R.z(), U.z(), L.z() );
   bulletTransformMatrix.setOrigin(P);
   return bulletTransformMatrix;
}



