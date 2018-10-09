/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "precom.h"
#include "SceneNodeGraph.h"

//Base Controller Class
class BaseController
{
public:
	
	virtual void Update(float dt){}
	virtual void Render(){}

};

#endif



