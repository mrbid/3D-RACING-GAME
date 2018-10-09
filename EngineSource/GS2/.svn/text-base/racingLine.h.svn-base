#pragma once
#ifndef RACINGLINE_H
#define RACINGLINE_H


#include "precom.h"
#include "Vector3.h"


class racingLine
{
public:
	racingLine();
	~racingLine();


	void readRacingLineNodes( std::string filename );
	inline int qtyNodes()											const { return m_vNode.size(); }
	inline vec3::Vector3 getNodePosition( const int& node )			const { return m_vNode[node].position; }
	inline float getNodeDirectionToNext( const int& node )			const { return m_vNode[node].directionToNextNode; }
	inline float getNodeDesiredSpeed( const int& node )				const { return m_vNode[node].desiredSpeed; }
	inline vec3::Vector3 getNodeLeft( const int& node )				const { return m_vLeftEdgeNode[node]; }
	inline vec3::Vector3 getNodeRight( const int& node )			const { return m_vRightEdgeNode[node]; }

	//Write a get sector function 
	inline vec3::Vector3 getSectorLeftRear( const int& node )		const { return m_vSector[node].leftRear; }
	inline vec3::Vector3 getSectorLeftFront( const int& node )		const { return m_vSector[node].leftFront; }
	inline vec3::Vector3 getSectorRightRear( const int& node )		const { return m_vSector[node].rightRear; }
	inline vec3::Vector3 getSectorRightFront( const int& node )		const { return m_vSector[node].rightFront; }


private:
	struct racingLineNode{ 
		vec3::Vector3 position;
		float directionToNextNode;
		float desiredSpeed;
	};


	struct racingLineSector{
		vec3::Vector3 leftRear;
		vec3::Vector3 rightRear;
		vec3::Vector3 leftFront;
		vec3::Vector3 rightFront;
	};


	std::deque<racingLineNode> m_vNode;
	std::deque<vec3::Vector3> m_vLeftEdgeNode;
	std::deque<vec3::Vector3> m_vRightEdgeNode;
	std::deque<racingLineSector> m_vSector;

};


#endif //RACINGLINE_H