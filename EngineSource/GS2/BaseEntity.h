/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "precom.h"
#include "Vector3.h"

//Base Entity Class
class BaseEntity
{
public:

	virtual void Update(float dt){}
	virtual void Render(){}

protected:

	//

};

#endif



