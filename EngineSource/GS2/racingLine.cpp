#include "precom.h"
#include "racingLine.h"
#include "utilities.h"


//Constructor
racingLine::racingLine()
{
}


//Destructor
racingLine::~racingLine(void)
{
	//Destroy racing line nodes
	//for( std::deque<racingLineNode>::iterator it = m_vNode.begin(); it < m_vNode.end(); it++ )
	//	delete *it;
}


void racingLine::readRacingLineNodes( std::string filename )
{
	/*Racing Line Node data is stored in the following way (all floats)
	1. X position of node
	2. Y position of node
	3. Z position of node
	4. direction to next node
	5. desired speed at node
	6. X position of left edge node
	7. Y position of left edge node
	8. Z position of left edge node
	9. X position of right edge node
	10. Y position of right edge node
	11. Z position of right edge node*/
	


	std::ofstream myfile;
	myfile.open("Craigs_Node_Info.txt");


	std::string line;
	std::ifstream levelFile( "Racing Line Files/Tokyo.rln" );
	if( levelFile.is_open() )
	{
		myfile << "File is Open\n";
		while (levelFile.good() )	
		{
			//create temporary variables for node data
			racingLineNode rln;
			vec3::Vector3 left;
			vec3::Vector3 right;


			//READ 1. X position of node
			getline( levelFile, line );
			rln.position.x = atof( line.c_str() );


			//READ 2. Y position of node
			getline( levelFile, line );
			rln.position.y = atof( line.c_str() );


			//READ 3. Z position of node
			getline( levelFile, line );
			rln.position.z = atof( line.c_str() );


			//READ 4. direction to next node
			getline( levelFile, line );
			rln.directionToNextNode = atof( line.c_str() );


			//READ 5. desired speed at node
			getline( levelFile, line );
			rln.desiredSpeed = atof( line.c_str() );


			//READ 6. X position of left edge node
			getline( levelFile, line );
			left.x = atof( line.c_str() );


			//READ 7. Y position of left edge node
			getline( levelFile, line );
			left.y = atof( line.c_str() );


			//READ 8. Z position of left edge node
			getline( levelFile, line );
			left.z = atof( line.c_str() );


			//READ 9. X position of right edge node
			getline( levelFile, line );
			right.x = atof( line.c_str() );


			//READ 10. Y position of right edge node
			getline( levelFile, line );
			right.y = atof( line.c_str() );


			//READ 11. Z position of right edge node
			getline( levelFile, line );
			right.z = atof( line.c_str() );


			//Create nodes from read data
			m_vNode.push_back( rln );
			m_vLeftEdgeNode.push_back( left );
			m_vRightEdgeNode.push_back( right );
		};
	}
	
	racingLineSector sector;
	for( int n=0; n<m_vNode.size()-1; ++n )
	{
		sector.leftRear = m_vLeftEdgeNode[n];
		sector.rightRear = m_vRightEdgeNode[n];
		sector.leftFront = m_vLeftEdgeNode[n+1];
		sector.rightFront = m_vRightEdgeNode[n+1];


		m_vSector.push_back( sector );
	}
	myfile.close();
}