#include "precom.h"
#include "AI.h"
#include "GameWorld.h"
#include "MatrixLib.h"


AIController::AIController()
{
	m_racingLine.readRacingLineNodes( "Racing Line Files/Tokyo.rln" );
	AIdebugFile.open("AI_Debug_Info.txt");
}

AIController::~AIController()
{
	AIdebugFile.close();
}

void AIController::Update(float dt)
{
	for( int v=1;v<m_vehiclecontroller->GetVehicleCount(); v++ )
	{
		m_TempNextNode[v] = m_vehiclecontroller->GetVehicle(v)->getNextRLnode();
		m_TempPrevNode[v] = m_TempNextNode[v]-1;

		m_vehiclecontroller->GetVehicle(v)->SetEngineForce(getAccelerationValue(v));
		m_vehiclecontroller->GetVehicle(v)->SetSteering(getSteeringValue(v));

		if( vehicleInSector(v, m_TempNextNode[v] ) )
		{
			m_vehiclecontroller->GetVehicle(v)->increaseRacingLineNode();
			++m_TempNextNode[v];
			++m_TempPrevNode[v];
		}
		AIdebugFile << "Vehicle " << v << " is in sector: " << m_TempNextNode[v] <<"\n";
	}
	AIdebugFile << std::endl;
}

void AIController::AddAIVechicles()
{
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_Orange.jpg", vec3::Vector3(-2391, -36.3, -1247), vec3::Vector3(-0.57,0.01,0.81));
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_Pink.jpg", vec3::Vector3(-2391, -36.3, -1265), vec3::Vector3(-0.54,0.01,0.83));
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_Red.jpg", vec3::Vector3(-2371, -36.3, -1275), vec3::Vector3(-0.55,0.01,0.83));
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_Green.jpg", vec3::Vector3(-2354, -36.3, -1326), vec3::Vector3(-0.5,0,0.86));
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_White.jpg", vec3::Vector3(-2370, -36.1, -1296), vec3::Vector3(-0.46,0,0.88));
	m_vehiclecontroller->AddVehicle("viper", "textures/Viper_Black.jpg", vec3::Vector3(-2354, -36.1, -1308), vec3::Vector3(-0.5,0,0.86));

	for( int v=1;v<m_vehiclecontroller->GetVehicleCount(); v++ )
		m_vehiclecontroller->GetVehicle(v)->setRacingLineNode(placeVehicleInSector(v));
}

//VERY EXPENSIVE code to find which sector of the track a vehicle is in
//ONLY use it before the start of the race!
int AIController::getUnknownNode( const int& vehicle )
{
	vec3::Vector3 position = m_vehiclecontroller->GetVehicle(vehicle)->GetPosition();
	float nearest = 99999999.9;
	int nearestNode = -1;
	for( int n=0; n<m_racingLine.qtyNodes()-1; ++n )
	{
		float d = getSquaredDistance( position, m_racingLine.getNodePosition(n));
		if( d < nearest )
		{
			nearest = d;
			nearestNode = n;
		}
	}
	return nearestNode + 1;
}

float AIController::getAccelerationValue( const int& vehicle )
{
	const float nextSpeed = m_racingLine.getNodeDesiredSpeed(m_TempNextNode[vehicle]);
	const float prevSpeed = m_racingLine.getNodeDesiredSpeed(m_TempPrevNode[vehicle]);

	if(nextSpeed == prevSpeed)
		return nextSpeed;

	m_VehiclesPositionBetweenNodes[vehicle] = interpolate(  m_racingLine.getNodePosition( m_TempPrevNode[vehicle] ), m_racingLine.getNodePosition( m_TempNextNode[vehicle] ), m_distanceToNextNode[vehicle] );

	return interpolate( nextSpeed, prevSpeed, getDistanceToNextNode(vehicle) );
}

float AIController::getSteeringValue( const int& vehicle )
{
	//const float directionToNextNode = (m_racingLine.getNodeDirectionToNext( m_TempPrevNode ) / 360)-1 ;
	//float currentSteering = m_vehiclecontroller->GetVehicle(vehicle)->GetSteering();
	//float currentDirection = m_vehiclecontroller->GetVehicle(vehicle)->GetDirection().y;

	//return interpolate( directionToNextNode, currentDirection, m_distanceToNextNode );

	//vec3::Vector3 currentPosition	=  m_vehiclecontroller->GetVehicle(vehicle)->GetPosition();
	//currentPosition.y = 0.f;
	//currentPosition = utils::Normalise( currentPosition );

	//const vec3::Vector3 destination		=  m_racingLine.getNodePosition(m_TempNextNode[vehicle]);
	//vec3::Vector3 destForward = destination - currentPosition;
	//destForward.y = 0.f;
	//destForward = utils::Normalise( destForward);

	//vec3::Vector3 cp = utils::crossProduct( currentPosition, destForward );
	//float steer = utils::length( cp );

	//if( steer > 0.f )  steer = -steer;
	//steer = utils::clamp( steer, -1.f, 1.f );

	const vec3::Vector3 currentPosition	=  m_vehiclecontroller->GetVehicle(vehicle)->GetPosition();
	const vec3::Vector3 destination		=  m_racingLine.getNodePosition( m_TempNextNode[vehicle] );

	const float angle = utils::dotProduct( currentPosition, destination );
	float steerAngle;

	if (angle < 180.f)
		steerAngle = max( 45.f, angle );
	else{
		steerAngle = max( 45.f, 360.f-angle );
		steerAngle = -steerAngle;
	}
	const float steer = 1.f+steerAngle/45.f;

	return steer;
}

float AIController::getDistanceToLeftNode( const int& vehicle )
{
	vec3::Vector3 left = m_racingLine.getNodeLeft(m_TempNextNode[vehicle]);
	return getSquaredDistance( m_vehiclecontroller->GetVehicle(vehicle)->GetPosition(), left );
}


float AIController::getDistanceToRightNode( const int& vehicle )
{
	vec3::Vector3 right = m_racingLine.getNodeRight(m_TempNextNode[vehicle]);
	return getSquaredDistance( m_vehiclecontroller->GetVehicle(vehicle)->GetPosition(), right );
}


bool AIController::vehicleInSector( const int& vehicle, const int& sector )
{
	const float x = m_vehiclecontroller->GetVehicle(vehicle)->GetPosition().x;
	const float z = m_vehiclecontroller->GetVehicle(vehicle)->GetPosition().z;

	const vec3::Vector3 leftRear	= m_racingLine.getSectorLeftRear(   sector );
	const vec3::Vector3 rightRear	= m_racingLine.getSectorRightRear(  sector );
	const vec3::Vector3 leftFront	= m_racingLine.getSectorLeftFront(  sector );
	const vec3::Vector3 rightFront	= m_racingLine.getSectorRightFront( sector );

	//(z - z0) (x1 - x0) - (x - x0) (z1 - z0)

	if( (z-leftRear.z)*(leftFront.x-leftRear.x)-(x-leftRear.x)*(leftFront.z-leftRear.z) > 0 )
		if( (z-leftFront.z)*(rightFront.x-leftFront.x)-(x-leftFront.x)*(rightFront.z-leftFront.z) > 0 )
			if( (z-rightFront.z)*(rightRear.x-rightFront.x)-(x-rightFront.x)*(rightRear.z-rightFront.z) > 0 )
				//if( (z-rightRear.z)*(leftRear.x-rightRear.x)-(x-rightRear.x)*(leftRear.z-rightRear.z) > 0 )
					return true;		
				
	return false;
}


int AIController::placeVehicleInSector( const int& vehicle )
{
	for( int sector=0; sector<m_racingLine.qtyNodes(); ++sector )
		if( vehicleInSector(vehicle, sector) )
			return sector;

	return 1;
}