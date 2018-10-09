#include "RaceTrack_Sector.h"
#include "precom.h"

RaceTrack_Sector::RaceTrack_Sector( vec3::Vector3, leftRear, vec3::Vector3 rightRear, vec3::Vector3 leftFront, vec3::Vector3 rightFront ) : 
m_Sector[0](leftRear), 
m_Sector[1](rightRear), 
m_Sector[2](leftFront),
m_Sector[3](rightFront)
{
}


RaceTrack_Sector::~RaceTrack_Sector(void)
{
}
