#pragma once
//-------------------------------------------//
#include "BaseGameObject.h"
#include "StaticObject.h"
//-------------------------------------------//
class MovingObject : virtual public BaseGameObject
{
public:
	virtual void Move() = 0;
	
	// Each moving object has the ability to check collision status with other objects as
	// part of the logical collision handling (default checking)
	virtual bool IsCollide(const MovingObject& GivenMovingObject) const;
	virtual bool IsCollide(const StaticObject& GivenStaticObject) const;
private:

};
//-------------------------------------------//