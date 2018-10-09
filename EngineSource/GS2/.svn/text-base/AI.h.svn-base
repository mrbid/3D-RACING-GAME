#ifndef AI_H
#define AI_H


#include "precom.h"
#include "racingLine.h"
#include "BaseController.h"
#include "VehicleController.h"
#include "utilities.h"


class AIController : public BaseController
{
public:
	AIController();
	~AIController();

	void Update(float dt);

	float getAccelerationValue( const int& vehicle );
	float getSteeringValue( const int& vehicle );
	float getDistanceToLeftNode( const int& vehicle );
	float getDistanceToRightNode( const int& vehicle );

	void AddAIVechicles();
	void settrackcontroller( VehicleController* vehiclecontroller ){ m_vehiclecontroller = vehiclecontroller; }
	int getUnknownNode( const int& vehicle );
	bool vehicleInSector( const int& vehicle, const int& sector );
	int placeVehicleInSector( const int& vehicle );

	inline float getDistance( vec3::Vector3& p1, vec3::Vector3& p2 )			{ return sqrt((p1.x-p2.x)*(p2.x-p2.x) + (p1.y-p2.y)*(p2.y-p2.y) + (p1.z-p2.z)*(p2.z-p2.z)); }
	inline float getSquaredDistance( vec3::Vector3& p1, vec3::Vector3& p2 )		{ return (p1.x-p2.x)*(p2.x-p2.x) + (p1.y-p2.y)*(p2.y-p2.y) + (p1.z-p2.z)*(p2.z-p2.z);	}
	inline float getDistanceToNextNode( const int v )							{ return getSquaredDistance( m_racingLine.getNodePosition( m_TempPrevNode[v] ), m_racingLine.getNodePosition( m_TempNextNode[v] ) ); }

	template< class T >
	inline T interpolate( const T& p1, const T& p2, const float t )
	{ return (1-t) * p1 + t * p2; };

private:
	enum AIstates{ GRID, RACING, RACEOVER };

	VehicleController*	m_vehiclecontroller;
	AIstates			m_AIstate;
	racingLine			m_racingLine;

	int					m_TempNextNode[16];
	int					m_TempPrevNode[16];
	float				m_distanceToNextNode[16];
	vec3::Vector3		m_VehiclesPositionBetweenNodes[16];
	std::ofstream		AIdebugFile;
};


#endif